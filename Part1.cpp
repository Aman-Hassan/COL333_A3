#include <bits/stdc++.h>
using namespace std;

void sort_edge(pair<int,int> e){
	if(e.first > e.second) swap(e.first , e.second);
}

int main(){
    map<pair<int,int>,int> edges; // map which can help to check which edges are present in the original graph
    int N,E,K1,K2;
    cin>>N>>E>>K1>>K2;
    for(int i=0;i<E;i++){
        pair<int,int> egde;
        cin>>egde.first>>egde.second;
        sort_edge(egde);
        edges[egde] = 1;  // initially assuming all edges are mappend in G1
    }
    cout << "c" << "comment" << endl;
    vector<vector<int>> clauses;
    // Constraint 1 : each vertex either IN G1 or G2 but not in both
    for(int i=1;i<=N;i++){
        vector<int> cnf;
        cnf.push_back(i);       
        cnf.push_back(i+N);
        clauses.push_back(cnf);
    }
    //constraint 2: if edges is not present in the original graph then that this vertices cannot be present in the same subgraph
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            int new_edge = make_pair(i,j);
            if(edges.find(new_edge)==edges.end()){
                vector<int> cnf;
                cnf.push_back(-(i));   // i and j are present in different subgraphs
                cnf.push_back(-(j));
                clauses.push_back(cnf);  
                clauses.clear();
                clauses.push_back(i+N);
                clauses.push_back(j+N);
                cnf.push_back(clauses);
            }
        }
    }
    //constraint 3 : ensuring the size of subgraphs as K1 and K2 
    
}