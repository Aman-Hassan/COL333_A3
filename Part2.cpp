 #include <bits/stdc++.h>
using namespace std;

void sort_edge(pair<int,int> e){
	if(e.first > e.second) swap(e.first , e.second);
}

int main(){
map<pair<int,int>,int> edges; // map which can help to check which edges are present in the original graph
    int N,E;
    cin>>N>>E;
    for(int i=0;i<E;i++){
        pair<int,int> egde;
        cin>>egde.first>>egde.second;
        sort_edge(egde);
        edges[egde] = 1;  
    }
    cout << c << " " << "comment" << endl;
    cout << "p cnf" << " " << N << " " << N*(N-1)/2 << endl;
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            pair<int,int> egde;
            egde.first = i;
            egde.second = j;
            sort_edge(egde);
            if(edges.find(egde) == edges.end()){             // egde not present in the original graph 
                cout << -i << " " << -j << " " << 0 << endl ;   
            }
            else{                                          
                cout << j << " " << 0 << endl;
            }
        }
    }
}