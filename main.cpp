#include <iostream>
#include <fstream>

using namespace std;

int main(){
// Input: 
// An integer N representing the number of neighborhoods in the city. 
// N x N square matrix representing the network with the distances in kilometers between the neighborhoods in the city. 
// N x N square matrix representing the maximum data flow capacities between neighborhood i and neighborhood j 
// list of N ordered pairs of the form (A,B) representing the location on a coordinate plane of the plants.
//Read an input file containing the information of a graph represented in the form of an adjacency 
// matrix with weighted graphs. 
//INPUT

//The program must also read another square matrix of N x N data representing the maximum capacity of data 
//transmission between neighborhood i and neighborhood j. 
//INPUT

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
int **plants = new int*[N];
for(int i = 0; i < N; i++){
    plants[i] = new int[2];
    for(int j = 0; j < 2; j++){
        in >> plants[i][j];
    }
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

}