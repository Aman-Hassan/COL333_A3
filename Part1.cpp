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
    int total_clauses  = N + N*(N-1)/2 - E + 3*(N-1) + K1 -1 + 6*(N-1)*(K1-1) + 3*(N-1) + K2 - 1 + 6*(N-1)*(K2-1)
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
    // for G1 graph   at most condition K1
    // implemented si,j = i+j*N+offset1
    int offset1 = N*K1;
    for(int j=2;j<=K1;j++){
        cout << - (1 + j*N + offset1 ) << " " << 0 << endl; 
    }
    for(int i=1;i<=N;i++){
       cout << -i << " " << i + 1*N + offset1 << " " << 0 << endl;
    } 
    for(int i=2;i<=N;i++){
          cout << -(i-1 + 1*N + offset1) << " " << i + 1*N + offset1 << " " << 0 << endl;
    }
    for(int i=2;i<=N;i++){
        for(int j=2;j<=K1;j++){
            cout << -(i+(j)*N+offset1) << " " << i+j*N+offset1 << " " << 0 << endl;
        }
    }
    for(int i=2;i<=N;i++){
        for(int j=2;j<=K1;j++){
           cout << -i << " " << -(i-1 + (j-1)*N + offset1) << " " << i + j*N + offset1 << " " << 0 << endl;
        }
    }
    for(int i=2;i<=N;i++){
        cout << -i << " " << -(i-1 + K1*N + offset1) << " " << 0 << endl;
    }
   // at least K1 is true  
    for(int i=2;i<=N;i++){
        for(int j=2;j<=N-K1;j++){
           cout << i << " " << -(i-1 + (j-1)*N + offset1) << " " << i + j*N + offset1 << " " << 0 << endl;
        }
    }
    if(K1 < N - K1){
         for(int j=K1+1;j<N-K1;j++){
        cout << - (1 + j*N + offset1 ) << " " << 0 << endl; 
    }
    }
     for(int i=1;i<=N;i++){
       cout << i << " " << i + 1*N + offset1 << " " << 0 << endl;
    } 
     for(int i=2;i<=N;i++){
        cout << i << " " << -(i-1 + K1*N + offset1) << " " << 0 << endl;
    }
    //at most K2 is true
   int offset2 = N*K2;  
    // for G2 graph   at most condition K2  
    // implemented si,j = i+ N +j*N+offset2
     for(int j=2;j<=K2;j++){
          cout << - (1+N + j*N + offset2 ) << " " << 0 << endl; 
     }
     for(int i=1;i<=N;i++){
         cout << -(i+N) << " " << (i+N) + 1*N + offset2 << " " << 0 << endl;
     }
     for(int i=2;i<=N;i++){
             cout << -(i-1+N + 1*N + offset2) << " " << i +N+ 1*N + offset2 << " " << 0 << endl;
     }
     for(int i=2;i<=N;i++){
          for(int j=2;j<=K2;j++){
                cout << -(i+ N +(j)*N+offset2) << " " << (i+N) +j*N+offset2 << " " << 0 << endl;
          }
     }
     for(int i=2;i<N;i++){
          for(int j=2;j<=K2;j++){
              cout << -(i+N) << " " << -(i-1 + N + (j-1)*N + offset2) << " " << (i + N + j*N + offset2) << " " << 0 << endl;
          }
     }
     for(int i=2;i<=N;i++){
          cout << -(i +N) << " " << -(i-1 + N + K2*N + offset2) << " " << 0 << endl;
     }
    // at least K2 is true  
    for(int i=2;i<=N;i++){
        for(int j=2;j<=N-K2;j++){
           cout << i+N << " " << -(i-1 + N + (j-1)*N + offset2) << " " << i + N + j*N + offset2 << " " << 0 << endl;
        }
    }
    if(K2 < N - K2){
         for(int j=K2+1;j<N-K2;j++){
        cout << - (1 + N + j*N + offset2 ) << " " << 0 << endl; 
    }
    }
     for(int i=1;i<=N;i++){
         cout << i+N << " " << (i+N) + 1*N + offset2 << " " << 0 << endl;
     }
     for(int i=2;i<=N;i++){
          cout << i+N << " " << -(i-1 + N + K2*N + offset2) << " " << 0 << endl;
     }   
}