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
    vector<vector<int>> cnf;
    // Constraint 1 : each vertex either in G1 or G2 but not in both
    for(int i=1;i<=N;i++){
        vector<int> clauses;
        clauses.push_back(i);       
        clauses.push_back(i+N);
        cnf.push_back(clauses);
    }
    //constraint 2: if edges is not present in the original graph then that this vertices cannot be present in the same subgraph
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            int new_edge = make_pair(i,j);
            if(edges.find(new_edge)==edges.end()){
                vector<int> clauses;
                clauses.push_back(-(i));   // i and j are present in different subgraphs
                clauses.push_back(-(j));   
                cnf.push_back(clauses);  
                clauses.clear();
                clauses.push_back(i+N);
                clauses.push_back(j+N);
                 cnf.push_back(clauses); 
            }
        }
    }
    //constraint 3 : ensuring the size of subgraphs as K1 and K2 
    // for G1 graph
    vector<vector<bool>> S;   //making a counter Sij hat represent that at least j of the variables x1,x2,x3...xi are assigned to true.
    for(int i=0;i<=N;i++){
        S[i][0] = 1;         // when subgraph of size 0 is selected form graph having 0...N vertices
    }
    for(int j=1;j<=K1;j++){
       S[0][j] = 0;        //when G has size 0 , then no subgraph is possible
    }
    // Converted the relation sij iff (s(i-1)(j) | (i & s(i-1)(j-1))) for 1<=i<=N and 1<=j<=K1  into CNF form 
    for(int i=1;i<=N;i++){
        for(int j=1;j<=K1;j++){
            vector<int> clauses;
            clauses.push_back(-(S[i][j]));
            clauses.push_back((S[i-1][j]));
            clauses.push_back(i);
            cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(S[i][j]));
             clauses.push_back(S[i-1][j]);
              clauses.push_back((S[i-1][j-1]));
               cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(S[i-1][j]));
            clauses.push_back(S[i][j]);
             cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(i));
            clauses.push_back(-(S[i-1][j-1]));
            clauses.push_back(S[i][j]);
             cnf.push_back(clauses);

        }
    }
    // for G2 graph 
   for(int i=1;i<=N;i++){
        S[i+N][0] = 1;         // when subgraph of size 0 is selected form graph having 0...N vertices
    }
    //as K1 >= K2 hence second condition is already done for K2
     for(int i=2;i<=N;i++){
        for(int j=1;j<=K2;j++){
            vector<int> clauses;
            clauses.push_back(-(S[i+N][j]));
            clauses.push_back((S[i-1+N][j]));
            clauses.push_back(i+N);
            cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(S[i+N][j]));
             clauses.push_back(S[i-1+N][j]);
              clauses.push_back((S[i-1+N][j-1]));
               cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(S[i-1+N][j]));
            clauses.push_back(S[i+N][j]);
             cnf.push_back(clauses);
            clauses.clear();
            clauses.push_back(-(i+N));
            clauses.push_back(-(S[i-1+N][j-1]));
            clauses.push_back(S2[i+N][j]);
             cnf.push_back(clauses);
        }
    }
    cout << "p cnf " << 2*N << " " << cnf.size() << endl;
    for (const vector<int>& it : cnf) {
        for (int v : it) {
            cout << v << " ";
        }
        cout << "0" << endl;
    }
}