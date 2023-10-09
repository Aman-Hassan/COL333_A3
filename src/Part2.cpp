#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void sort_edge(pair<int,int> e){
	if(e.first > e.second) swap(e.first , e.second);
}

int main(){
    map<pair<int,int>,int> edges; // map which can help to check which edges are present in the original graph
    int N,E;
    cin>>N>>E;
    for(int i=0;i<E;i++){
        pair<int,int> edge;
        int x , y ;
        cin>>x>>y;
        edge.first = x;
        edge.second = y;
        edges[edge] = 3;  // initially assuming all edges are mappend in G1
    }

    // Run until we get a satisfiable clique of size k (starting from N and going down to 1)
    for (int K1=N-1;K1>0;K1--){
        std::ofstream f_out{"./src/output2.txt"};
        int total_variables;
        total_variables= 2*N + (N-1)*K1;
        int total_clauses  = N + N*(N-1)/2 - E + 2*N*K1 + N - 3*K1 +1;
        f_out << "c" << " " << "comment" << endl;
        f_out << "p cnf" << " " << total_variables << " " << total_clauses << endl;
        int K11=N-K1;
        int offset1 = N*K1;
        int offset2 = offset1 + N + K1*N;


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
                    f_out << -i << " " << -j << " " << 0 << endl ;
                }
            }
        }

        //constraint 2 : ensuring the size of subgraphs as K1 and K2 
        // for G1 graph at most condition K1
        // implemented si,j = i+j*N+offset1  
        f_out << -1 << " " << 1 + 1*N + offset1 << " " << 0 << endl; // -x1 | si,i
        for(int j=2;j<=K1;j++){
            f_out << - (1 + j*N + offset1 ) << " " << 0 << endl;       // -s1,j
        }
        for(int i=2;i<N;i++){
        f_out << -i << " " << i + 1*N + offset1 << " " << 0 << endl;  // -xi | si,1
        } 
        for(int i=2;i<N;i++){
            f_out << -(i-1 + 1*N + offset1) << " " << i + 1*N + offset1 << " " << 0 << endl;  // -s(i-1,1) | s(i,1)
        }
        for(int i=2;i<N;i++){
            for(int j=2;j<=K1;j++){
                f_out << -(i -1 +(j)*N+offset1) << " " << i+j*N+offset1 << " " << 0 << endl;   // -s(i-1,j) | s(i,j)
            }
        for(int j=2;j<=K1;j++){
            f_out << -i << " " << -(i-1 + (j-1)*N + offset1) << " " << i + j*N + offset1 << " " << 0 << endl;  // -xi | -s(i-1,j-1) | s(i,j)
        }
        }
        for(int i=2;i<=N;i++){
            f_out << -i << " " << -(i-1 + K1*N + offset1) << " " << 0 << endl;  // -xi | -s(i-1,K1)
        }

        // at least K1 is true  
        // N- k1 variables 
        f_out << 1 << " " << 1 + 1*N + offset2 << " " << 0 << endl;       
        for(int j=2;j<=K11;j++){
            f_out << -(1 + j*N + offset2 ) << " " << 0 << endl;          
        }
        for(int i=2;i<N;i++){
        f_out << i << " " << i + 1*N + offset2 << " " << 0 << endl;
        } 
        for(int i=2;i<N;i++){
            f_out << -(i-1 + 1*N + offset2) << " " << i + 1*N + offset2 << " " << 0 << endl;
        }
        for(int i=2;i<N;i++){
            for(int j=2;j<=K11;j++){
                f_out << -(i -1 +(j)*N+offset2) << " " << i+j*N+offset2 << " " << 0 << endl;
            }
        }
        for(int i=2;i<N;i++){
            for(int j=2;j<=K11;j++){
            f_out << i << " " << -(i-1 + (j-1)*N + offset2) << " " << i + j*N + offset2 << " " << 0 << endl;
            }
        }
        for(int i=2;i<=N;i++){
            f_out << i << " " << -(i-1 + K11*N + offset2) << " " << 0 << endl;
        }
        
        // Run minisat on the output file
        int minisat_output = system("minisat ./src/output2.txt ./debug/result2.txt");
        std::ifstream resultfile ("./debug/result2.txt"); // this is equivalent to the above method
        std::string result;

        // Read first line of result file
        if ( resultfile.is_open() ) { 
            resultfile >> result; 
        }

        //If first line is SAT then we have obtained our required max clique
        if (result.compare("SAT")==0){
            break;
        }
        f_out.close();
    }
}