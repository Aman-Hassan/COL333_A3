#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;

int main(int argc, char *argv[]){
    std::ifstream minisat_output(argv[1]);
    std::ifstream graph_file(argv[2]);
    std::ofstream output_file (argv[3]); 
    
    int N,E,K1,K2;
    if (graph_file.is_open()) {
        graph_file >> N >> E >> K1 >> K2;
        if (K1 == N || K2 == N){
            output_file << "0" << endl;
            return 0;
        }
        if ((K1*(K1-1)/2) + (K2*(K2-1)/2) > E){
            output_file << "0" << endl;
            return 0;
        }
    }


    std::string sat_line;

    if (minisat_output.is_open()){
        std::getline(minisat_output,sat_line);
        if (sat_line.compare("UNSAT") == 0){
            output_file << "0" << endl;
            return 0;
        }
    }

    output_file << "#1" << endl;
    std::string k1_literal;
    int k1 = 0; //The actual number of positive variables
    int total_k1_literal_count = 0; //Total number of variables
    while (total_k1_literal_count < N){
        minisat_output >> k1_literal;
        total_k1_literal_count += 1;
        if (atoi(k1_literal.c_str()) < 0){
            continue;
        }
        k1 += 1;
        if (k1 <= K1){
            if (k1 != 1){
                output_file << " ";
            }
            output_file << atoi(k1_literal.c_str());
        }
    }

    output_file << endl;

    output_file << "#2" << endl;
    std::string k2_literal;
    int k2 = 0;
    int total_k2_literal_count = 0;
    while (total_k2_literal_count < N){
        minisat_output >> k2_literal;
        total_k2_literal_count += 1;
        if (atoi(k2_literal.c_str()) < 0){
            continue;
        }
        k2+=1;
        if (k2 <= K2){
            if (k2 != 1){
                output_file << " ";
            }
            output_file << atoi(k2_literal.c_str()) - N;
        }
    }

    minisat_output.close();
    graph_file.close();
    output_file.close();
}