#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <fstream>
#include <limits>
#include <cmath>
#include <string.h>
#include <limits.h>
#include <queue>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Point          Point;

using namespace std;

//kruskal

//nearest neighbor
void nearestNeighbor(int **matrix,int N){
    int *visited =new int[N];
    for(int i=0;i<N;i++){
        visited[i]=0;
    }
    int current=0;
    visited[current]=1;
    
    int *path=new int[N];
    path[0]=current;
    
    int next=0;
    for(int i=1;i<N;i++){
        double min=numeric_limits<double>::max();
        // for each neighbor of current
        for(int j=0;j<N;j++){
            // if neighbor is not visited and distance is less than min
            if(matrix[current][j]!=0 && visited[j]==0){
                if(matrix[current][j]<min){
                    min=matrix[current][j];
                    next=j;
                }
            }
        }
        path[i]=next; // add next to path
        visited[next]=1; 
        current=next; // set current to next
    }
    cout<<"Path: ";
    for(int i=0;i<N;i++){
        cout<<path[i]<<" ";
    }
    cout<<endl;
    double total=0;
    for(int i=0;i<N-1;i++){
        total+=matrix[path[i]][path[i+1]];
    }
    total+=matrix[path[N-1]][path[0]];
    cout<<"Total: "<<total<<endl;
}
//ford-fulkerson
bool BFs(int rGraph[V][V], int s, int, t, int parent[]){
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
   visited[s] = true;
   parent[s] = -1;
   while (!q.empty()) {
       int u = q.front();
       q.pop();
       for (int v = 0; v < V; v++) {
           if (visited[v] == false && rGraph[u][v] > 0) {
               q.push(v);
               parent[v] = u;
               visited[v] = true;
           }
       }
   }
   return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t) {
   int u, v;
   int rGraph[V][V];
   for (u = 0; u < V; u++)
       for (v = 0; v < V; v++)
           rGraph[u][v] = graph[u][v];
   int parent[V];
   int max_flow = 0;
   while (bfs(rGraph, s, t, parent)) {
       int path_flow = INT_MAX;
       for (v = t; v != s; v = parent[v]) {
           u = parent[v];
           path_flow = min(path_flow, rGraph[u][v]);
       }
       for (v = t; v != s; v = parent[v]) {
           u = parent[v];
           rGraph[u][v] -= path_flow;
           rGraph[v][u] += path_flow;
       }
       max_flow += path_flow;
   }
   return max_flow;
}


int main(){
    ifstream in("input.cin");
    int N;
    in >> N;
    //matrix of distances
    int **matrix = new int*[N];
    for(int i = 0; i < N; i++){
        matrix[i] = new int[N];
        for(int j = 0; j < N; j++){
            in >> matrix[i][j];
        }
    }
    //matrix of capacities / flow
    int **capacity = new int*[N];
    for(int i = 0; i < N; i++){
        capacity[i] = new int[N];
        for(int j = 0; j < N; j++){
            in >> capacity[i][j];
        }
    }
    // matrix of points
    Point **plants = new Point*[N];
    for(int i = 0; i < N; i++){
        double x,y;
        char c;
        in>>c>>x>>c>>y>>c;
        plants[i] = new Point(x,y);    
    }
    // The program must display which is the optimal way to wire with optical fiber connecting neighborhoods 
    //in such a way that information can be shared between any two neighborhoods.
    //Kruskal

    //What is the shortest possible route that visits each neighborhood exactly once and returns to
    //the neighborhood of origin? 
    //TSP - Nearest Neighbor repeated
    nearestNeighbor(matrix, N);
    
    //The company wants to know the maximum information flow from the initial node to the final node. 
    //This should also be displayed in the standard output.
    //Ford-Fulkerson

    //Given the geographic location of several "exchanges" to which new homes can be connected, the company wants
    //to have a way to decide, given a new service contract, which exchange is geographically closest to that new contract. 
    //There is not necessarily one exchange for each neighborhood. You can have neighborhoods with no central, and
    // neighborhoods with more than one central.
    //CGAL - Voronoi Diagram
    Triangulation T;

}