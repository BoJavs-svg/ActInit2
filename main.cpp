#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <fstream>
#include <limits>
#include <cmath>
#include <string.h>
#include <limits.h>
#include <queue>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Point          Point;

using namespace std;

//kruskal
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

void kruskal (vector<Edge> edges, int N) {
    int cost = 0;
    vector<Edge> result;
    vector<int> tree_id(N);
    // initialize tree_id
    for (int i = 0; i < N; i++)
        tree_id[i] = i;
    // sort edges
    sort(edges.begin(), edges.end());
    for (Edge e : edges) {
        // if the edge doesn't create a cycle, add it to the result
        if (tree_id[e.u] != tree_id[e.v]) {
            cost += e.weight;
            result.push_back(e);
            int old_id = tree_id[e.u], new_id = tree_id[e.v];
            // update tree_id
            for (int i = 0; i < N; i++) {
                if (tree_id[i] == old_id)
                    tree_id[i] = new_id;
            }
        }
    }
    cout << "The minimum cost is: " << cost << endl;
    cout << "The minimum spanning tree is: " << endl;
    for (Edge e : result) {
        cout << e.u << " " << e.v << endl;
    }
}

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
bool BFs(std::vector<std::vector<int>>& rGraph, int s, int t, std::vector<int>& parent, int N) {
    bool visited[N];
    memset(visited, 0, sizeof(visited));//set visited to false
    queue <int> q;
    q.push(s);
   visited[s] = true;
   parent[s] = -1;
   while (!q.empty()) {
       int u = q.front();
       q.pop();
       for (int v = 0; v < N; v++) {
           if (visited[v] == false && rGraph[u][v] > 0) {
               q.push(v);
               parent[v] = u;
               visited[v] = true;
           }
       }
   }
   return (visited[t] == true);
}

int fordFulkerson(std::vector<std::vector<int>>& graph, int s, int t, int N) {
   std::vector<std::vector<int>> rGraph = graph;
   std::vector<int> parent(N, -1);
    int max_flow = 0;
    int u, v;
    // Augment the flow while there is path from source to sink
   while (BFs(rGraph, s, t, parent, N)) {
       int path_flow = INT_MAX;
       // find minimum residual capacity of the edges along the
       for (v = t; v != s; v = parent[v]) {
           u = parent[v];
           path_flow = min(path_flow, rGraph[u][v]);
       }
       // update residual capacities of the edges and reverse edges along the path
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
    vector<vector<int>> capacity(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            in >> capacity[i][j];
        }
    }
    // matrix of points
    vector<Point> plants; 
    for(int i = 0; i < N; i++){
        double x,y;
        char c;
        in>>c>>x>>c>>y>>c;
        plants.push_back(Point(x,y));
    }
    // The program must display which is the optimal way to wire with optical fiber connecting neighborhoods 
    //in such a way that information can be shared between any two neighborhoods.
    //Kruskal
    vector<Edge> edges;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(matrix[i][j]!=0){
                Edge e;
                e.u=i;
                e.v=j;
                e.weight=matrix[i][j];
                edges.push_back(e);
            }
        }
    }
    kruskal(edges, N);

    //What is the shortest possible route that visits each neighborhood exactly once and returns to
    //the neighborhood of origin? 
    //TSP - Nearest Neighbor repeated
    nearestNeighbor(matrix, N);
    
    //The company wants to know the maximum information flow from the initial node to the final node. 
    //This should also be displayed in the standard output.
    //Ford-Fulkerson
    cout<<"The maximum information flow is:"<<fordFulkerson(capacity, 0, N-1, N)<<endl;
    
    //Given the geographic location of several "exchanges" to which new homes can be connected, the company wants
    //to have a way to decide, given a new service contract, which exchange is geographically closest to that new contract. 
    //There is not necessarily one exchange for each neighborhood. You can have neighborhoods with no central, and
    // neighborhoods with more than one central.
    //CGAL - Voronoi Diagram
    Triangulation T;
    T.insert(plants.begin(), plants.end());

    int x,y;
    cin>>x>>y;
    Point p(x,y);
    Point nearest = T.nearest_vertex(p)->point();
    cout<<"The nearest exchange is: "<<nearest<<endl;
    return 0;

}