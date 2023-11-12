#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <fstream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Point          Point;

using namespace std;



int main(){
    cout<<"Reading input file..."<<endl;
    ifstream in("input.cin");
    int N;
    in >> N;
    int **matrix = new int*[N];
    for(int i = 0; i < N; i++){
        matrix[i] = new int[N];
        for(int j = 0; j < N; j++){
            in >> matrix[i][j];
        }
    }
    int **capacity = new int*[N];
    for(int i = 0; i < N; i++){
        capacity[i] = new int[N];
        for(int j = 0; j < N; j++){
            in >> capacity[i][j];
        }
    }

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
    //TSP


    //The company wants to know the maximum information flow from the initial node to the final node. 
    //This should also be displayed in the standard output.
    //Ford-Fulkerson

    //Given the geographic location of several "exchanges" to which new homes can be connected, the company wants
    //to have a way to decide, given a new service contract, which exchange is geographically closest to that new contract. 
    //There is not necessarily one exchange for each neighborhood. You can have neighborhoods with no central, and
    // neighborhoods with more than one central.
    //CGAL - Voronoi Diagram
    Triangulation T;
    T.insert(plants, plants+N);

}