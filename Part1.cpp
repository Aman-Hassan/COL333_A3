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
    int total_varibles = 2*N*K1 + 2*N*K2;
    int total_clauses;
    cout << "c" << " " << "comment" << endl;
    cout << "p cnf" << " " << total_varibles << " " << total_clauses << endl;
    // Constraint 1 : each vertex either in G1 or G2 but not in both
    for(int i=1;i<=N;i++){
        cout << i << " " << i+N << " " << 0 << endl;
    }
    //constraint 2: if edges is not present in the original graph then that this vertices cannot be present in the same subgraph
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            pair<int,int> new_edge = make_pair(i,j);
            if(edges.find(new_edge)==edges.end()){
                cout << -i << " " << -j << " " << 0 << endl;
                cout << -(i+N) << " " << -(j+N) << " " << 0 << endl;
            }
        }
    }
    //constraint 3 : ensuring the size of subgraphs as K1 and K2 
    // for G1 graph   at most condition
    int offset1 = N*K1;
    cout << -1 << " " << 1 + 1*N + offset1 << " " << 0 << endl;
    for(int j=2;j<=K1;j++){
        cout << - (1 + j*N + offset1 ) << " " << 0 << endl; 
    }
    for(int i=2;i<N;i++){
       cout << -i << " " << i + 1*N + offset1 << " " << 0 << endl;
    }
    for(int i=2;i<N;i++){
          cout << -(i-1 + 1*N + offset1) << " " << i + 1*N + offset1 << " " << 0 << endl;
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K1;j++){
            cout << -(i+(j)*N+offset1) << " " << i+j*N+offset1 << " " << 0 << endl;
        }
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K1;j++){
           cout << -i << " " << -(i-1 + (j-1)*N + offset1) << " " << i + j*N + offset1 << " " << 0 << endl;
        }
    }
    for(int i=2;i<=N;i++){
        cout << -i << " " << -(i-1 + K1*N + offset1) << " " << 0 << endl;
    }
    


}