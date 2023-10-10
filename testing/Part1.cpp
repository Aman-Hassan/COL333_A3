#include <bits/stdc++.h>
using namespace std;


int main(){
    map<pair<int,int>,int> edges; // map which can help to check which edges are present in the original graph
    int N,E,K1,K2;
    cin>>N>>E>>K1>>K2;
    for(int i=0;i<E;i++){
        pair<int,int> edge;
        int x , y ;
        cin>>x>>y;
        edge.first = x;
        edge.second = y;
        edges[edge] = 3;  // initially assuming all edges are mappend in G1
    }
    
    int total_variables;
    total_variables= 2*N + (N-1)*K1 + (N-1)*K2 ;
    int total_clauses  = N + N*(N-1)/2 - E + 2*N*K1 + N - 3*K1 +1 + 2*N*K2 + N - 3*K2 + 1 ;
    cout << "c" << " " << "comment" << endl;
    cout << "p cnf" << " " << total_variables << " " << total_clauses << endl;
    int K11=N-K1;
    int offset2 = K1*N ;
    int offset4 =  N*(K11) +  N  +  offset2;
    int K22 = N - K2;
    // Constraint 1 : each vertex either in G1 or G2 but not in both
    cout << "c" << " " << "Constraint 1 starts here:" << endl;
    for(int i=1;i<=N;i++){
        cout << -i << " " << -(i+N) << " " << 0 << endl;  // -xi | -yi
    }

    cout << "c" << " " << "Constraint 2 starts here:" << endl;
    // // constraint 2: if edges is not present in the original graph then that this vertices cannot be present in the same subgraph
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            pair<int,int> edge1;
            pair<int,int> edge2;
            edge1.first = i;
            edge1.second = j;
            edge2.first = j;
            edge2.second = i;
            if(edges.find(edge1) == edges.end() && edges.find(edge2)==edges.end()){             // edge not present in the original graph 
                cout << -i << " " << -j << " " << 0 << endl;   
                cout << -(i+N) << " " << -(j+N) << " " << 0 << endl;
            }
        }
    }

    //constraint 3 : ensuring the size of subgraphs as K1 and K2 
    // for G1 graph   at most condition K1
    // implemented si,j = i+j*N+offset1  
    // cout << "c" << " " << "Constraint 3: Atmost K1" << endl;

    // cout << -1 << " " << 1 + 1*N + offset1 << " " << 0 << endl; // -x1 | si,i
    // for(int j=2;j<=K1;j++){
    //     cout << - (1 + j*N + offset1 ) << " " << 0 << endl;       // -s1,j
    // }
    // for(int i=2;i<N;i++){
    //    cout << -i << " " << i + 1*N + offset1 << " " << 0 << endl;  // -xi | si,1
    // } 
    // for(int i=2;i<N;i++){
    //       cout << -(i-1 + 1*N + offset1) << " " << i + 1*N + offset1 << " " << 0 << endl;  // -s(i-1,1) | s(i,1)
    // }
    // for(int i=2;i<N;i++){
    //     for(int j=2;j<=K1;j++){
    //         cout << -(i -1 +(j)*N+offset1) << " " << i+j*N+offset1 << " " << 0 << endl;   // -s(i-1,j) | s(i,j)
    //     }
    // for(int j=2;j<=K1;j++){
    //        cout << -i << " " << -(i-1 + (j-1)*N + offset1) << " " << i + j*N + offset1 << " " << 0 << endl;  // -xi | -s(i-1,j-1) | s(i,j)
    // }
    // }
    // for(int i=2;i<=N;i++){
    //     cout << -i << " " << -(i-1 + K1*N + offset1) << " " << 0 << endl;  // -xi | -s(i-1,K1)
    // }
   // at least K1 is true  
   // N- k1 variables 
    cout << "c" << " " << "Constraint 3: Atleast K1" << endl;
    cout << 1 << " " << 1 + 1*N + offset2 << " " << 0 << endl;       
   for(int j=2;j<=K11;j++){
        cout << -(1 + j*N + offset2 ) << " " << 0 << endl;          
    }
    for(int i=2;i<N;i++){
       cout << i << " " << i + 1*N + offset2 << " " << 0 << endl;
    } 
     for(int i=2;i<N;i++){
          cout << -(i-1 + 1*N + offset2) << " " << i + 1*N + offset2 << " " << 0 << endl;
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K11;j++){
            cout << -(i -1 +(j)*N+offset2) << " " << i+j*N+offset2 << " " << 0 << endl;
        }
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K11;j++){
           cout << i << " " << -(i-1 + (j-1)*N + offset2) << " " << i + j*N + offset2 << " " << 0 << endl;
        }
    }
     for(int i=2;i<=N;i++){
        cout << i << " " << -(i-1 + K11*N + offset2) << " " << 0 << endl;
    }

    // cout << "c" << " " << "Constraint 3: Atmost K2" << endl;

    //at most K2 is true
    // implemented si,j = i+j*N+offset3 
    // cout << -(1+N) << " " << 1 + N + 1*N + offset3 << " " << 0 << endl; // -x1 | si,i
    // for(int j=2;j<=K2;j++){
    //     cout << -(1 + N + j*N + offset3) << " " << 0 << endl;          
    // }
    // for(int i=2;i<N;i++){
    //    cout << -(i+N) << " " << i + N  + 1*N + offset3 << " " << 0 << endl;
    // } 
    // for(int i=2;i<N;i++){
    //       cout << -(i-1 + N + 1*N + offset3) << " " << i + N + 1*N + offset3 << " " << 0 << endl;
    // }
    // for(int i=2;i<N;i++){
    //     for(int j=2;j<=K2;j++){
    //         cout << -(i -1 + N +(j)*N+offset3) << " " << i+N+j*N+offset3 << " " << 0 << endl;
    //     }
    // }
    // for(int i=2;i<N;i++){
    //     for(int j=2;j<=K2;j++){
    //        cout << -(i+N) << " " << -(i-1 + N + (j-1)*N + offset3) << " " << i + N + j*N + offset3 << " " << 0 << endl;
    //     }
    // }
    // for(int i=2;i<=N;i++){
    //     cout << -(i+N) << " " << -(i-1 + N + K2*N + offset3) << " " << 0 << endl;
    // }
    // at least K2 is true  
    // N- k2 variables

    cout << "c" << " " << "Constraint 3: Atleast K2" << endl;

    cout << 1+N << " " << 1 + N + 1*N + offset4 << " " << 0 << endl; // -x1 | s1,1
    for(int j=2;j<=K22;j++){
        cout << -(N + j*N + offset4) << " " << 0 << endl;          
    }
    for(int i=2;i<N;i++){
       cout << i+N << " " << i + N  + 1*N + offset4 << " " << 0 << endl;
    }
    for(int i=2;i<N;i++){
          cout << -(i-1 + N + 1*N + offset4) << " " << i + N + 1*N + offset4 << " " << 0 << endl;
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K22;j++){
            cout << -(i -1 + N +(j)*N+offset4) << " " << i+N+j*N+offset4 << " " << 0 << endl;
        }
    }
    for(int i=2;i<N;i++){
        for(int j=2;j<=K22;j++){
           cout << i+N << " " << -(i-1 + N + (j-1)*N + offset4) << " " << i + N + j*N + offset4 << " " << 0 << endl;
        }
    }
    for(int i=2;i<=N;i++){
        cout << i+N << " " << -(i-1 + N + K22*N + offset4) << " " << 0 << endl;
    }

}