#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    std::string filename = argv[1];
    std::string graph_file = filename + ".graph";
    std::string minisat_input = filename + ".satinput";
    std::string minisat_output = filename + ".satoutput";
    std::string mapping = filename + ".mapping";

    std::ifstream graph(graph_file);
    map<pair<int,int>,int> edges; // map which can help to check which edges are present in the original graph
    int N,E;
    graph>>N>>E;
    for(int i=0;i<E;i++){
        pair<int,int> edge;
        int x , y ;
        graph>>x>>y;
        edge.first = x;
        edge.second = y;
        edges[edge] = 3;  // initially assuming all edges are mappend in G1
    }
    graph.close();



    // Run until we get a satisfiable clique of size k (starting from N and going down to 1) = Use binary search;
    int upper = N;
    int lower = 1;
    int K = 0;
    int K_best = 0;
    int iter = 0;
    std::string minisat_output_temp = "temp.satoutput";

    // After reaching the lower = upper -> still possibilities exist
    // if the terminating value of lower = upper = K is SAT then we need run the loop again -> Use iter for running this
    // if the terminating value is not SAT then the outputsat file should have the values obtained during run of K_best -> Copy contents of minisat output_temp of best K into req output file

    while (upper-lower > 0 || iter == 1){
        if (iter == 1){  //Once we reach the iter case, we only need to run it once and so we increment iter to never use this loop again
            iter += 1;
        }
        K = (int) (upper + lower)/2;
        std::ofstream minisat_input_file{minisat_input};
        int total_variables;
        total_variables= 2*N + (N-1)*K;
        int total_clauses  = N + N*(N-1)/2 - E + 2*N*K + N - 3*K +1;
        minisat_input_file << "c" << " " << "comment" << endl;
        minisat_input_file << "p cnf" << " " << total_variables << " " << total_clauses << endl;
        int K1=N-K;
        int offset1 = N*K;
        int offset2 = offset1 + N + 2*K*N;


        // // constraint 1: if edges is not present in the original graph then that this vertices cannot be present in the same subgraph
        for(int i=1;i<=N;i++){
            for(int j=i+1;j<=N;j++){
                pair<int,int> edge1;
                pair<int,int> edge2;
                edge1.first = i;
                edge1.second = j;
                edge2.first = j;
                edge2.second = i;
                if(edges.find(edge1) == edges.end() && edges.find(edge2)==edges.end()){             // edge not present in the original graph 
                    minisat_input_file << -i << " " << -j << " " << 0 << endl ;
                }
            }
        }


        // at least K is true  
        // N- K variables 
        minisat_input_file << 1 << " " << 1 + 1*N + offset2 << " " << 0 << endl;       
        for(int j=2;j<=K1;j++){
            minisat_input_file << -(1 + j*N + offset2 ) << " " << 0 << endl;          
        }
        for(int i=2;i<N;i++){
        minisat_input_file << i << " " << i + 1*N + offset2 << " " << 0 << endl;
        } 
        for(int i=2;i<N;i++){
            minisat_input_file << -(i-1 + 1*N + offset2) << " " << i + 1*N + offset2 << " " << 0 << endl;
        }
        for(int i=2;i<N;i++){
            for(int j=2;j<=K1;j++){
                minisat_input_file << -(i -1 +(j)*N+offset2) << " " << i+j*N+offset2 << " " << 0 << endl;
            }
        }
        for(int i=2;i<N;i++){
            for(int j=2;j<=K1;j++){
            minisat_input_file << i << " " << -(i-1 + (j-1)*N + offset2) << " " << i + j*N + offset2 << " " << 0 << endl;
            }
        }
        for(int i=2;i<=N;i++){
            minisat_input_file << i << " " << -(i-1 + K1*N + offset2) << " " << 0 << endl;
        }
        
        minisat_input_file.close();

        // Run minisat on the output file
        std::string minisat_command = "./minisat " + minisat_input + " " + minisat_output_temp;
        system(minisat_command.c_str()); //._c_str to convert into const char* type that system() requires
        
        std::ifstream minisat_temp_file(minisat_output_temp);
        std::string sat_line;

        // Read first line of result file
        if (minisat_temp_file.is_open() ) { 
            minisat_temp_file >> sat_line; 
        }
        minisat_temp_file.close();
        //If first line is SAT then we have obtained our required max clique

        if (sat_line.compare("SAT")==0) {
            lower = K+1;

            // If the K we have is the best K till now then copy contents of minisat_output_temp into minisat_output
            if (K > K_best){
                K_best = K;
                std::ifstream minisat_temp_file(minisat_output_temp);
                std::ofstream minisat_output_file(minisat_output);
                std::string line;
                while(getline(minisat_temp_file,line)){
                    minisat_output_file << line << "\n";
                }
                minisat_temp_file.close();
                minisat_output_file.close();
            }
        }
        else {upper = K-1;}
    

        if (upper == lower){
            iter += 1; // iter only updated if upper == lower => loop will be run only once more
        }
    }

    //Now write onto mapping
    std::ifstream minisat_output_file(minisat_output);
    std::ofstream mapping_file(mapping); 

    std::string sat_line;
    minisat_output_file >> sat_line; 

    mapping_file << "#1" << endl;
    std::string literal;
    int k = 0;
    int literal_count = 0;
    while (literal_count < N){
        minisat_output_file >> literal;
        literal_count += 1;
        if (atoi(literal.c_str()) < 0){
            continue;
        }
        k += 1;
        if (k != 1){
            mapping_file << " ";
        }
        mapping_file << atoi(literal.c_str());
    }

    mapping_file << endl;
    minisat_output_file.close();
    mapping_file.close();

}