#include <bits/stdc++.h>
using namespace std;

void sort_edge(pair<int,int> e){
	if(e.first > e.second) swap(e.first , e.second);
}

int main(){
    pair<int,int> egde;     // edge between two vertices
    vector<pair<int,int>> edges;   // vector of edges
    map<pair<int,int>,int> to_which_subgraph; // map to which subgraph the edge belongs to which subgraph
    int N,E,K1,K2;
    cin>>N>>E>>K1>>K2;
    for(int i=0;i<E;i++){
        cin>>egde.first>>egde.second;
        sort_edge(egde);
        edges.push_back(egde);
        to_which_subgraph[egde] = 1;
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
    

}