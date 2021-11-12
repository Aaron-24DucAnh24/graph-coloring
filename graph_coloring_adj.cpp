#include <iostream>
#include <vector>

using namespace std;

class graph{
    int **matrix ;
    int v;
    vector<bool> passed;
public:
    graph(int);
    ~graph();
    void add();
    void coloring();
    void dfs(int);
};

graph::graph(int v){     

    this->v = v;
    vector<bool> a(v,false);
    this->passed = a;

    this->matrix = new int*[v];
    for(int i = 0; i < v; i++)
    {
        matrix[i] = new int[v];
        for(int j = 0; j < v; j++){
            matrix[i][j] = 0;
        }
    }
};

graph::~graph(){

    for(int i = 0; i < this->v; i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
};

void graph::add(){

    cout <<  "Enter the adjacency matrix (row by row) :" << endl ;
    for(int i = 0; i < this->v; i++){
        for(int j = 0; j < this->v; j++){
            int a;
            cin >> a; this->matrix[i][j] = a;
        }
    }
    cout << endl << "The DFS order : " << endl;
};

void graph::dfs(int start){

    cout << "v" << start << " ";
    this->passed[start] = true;

    for(int i = 0; i < this->v; i++){
        if(this->matrix[start][i] == 1 && (!this->passed[i])){
            this->dfs(i);
        }
    }
};

void graph::coloring(){
    cout << endl << endl;
    
    int  num = this->v;
    vector<int > result(num, -1);             // An array stored the color of vertices
    vector<bool> available(num, false);       // An array to check if the colors of adjacency
                                              // are available or not

    result[0] = 0;                            // Assign the first vertex the first color

    for(int i = 1; i < num; i++){             // Consider the others

        for(int j = 0; j < num; j++){         // Find adjacency vertices and check if
                                              // they were colored or not
            if(this->matrix[i][j] == 1 && result[j] != -1)    // if yes, note the color to be available
                available[result[j]] = true;
        }

        int color;
        for(color = 0; color < num; color++){
            if(available[color] == false)             // Find the smallest value 
                break;                                // of color for the vertex
        }                                             // if all the color are available,
                                                      // , get a new color
        result[i] = color;      // assign the color to current vertex

        for(int i = 0; i < this->v; i++){
            available[i] = false;                   // set all the color as unavailable
        }
    }

    {   int count = 0;
        cout << "Coloring of the graph :" << endl;
        for(int i = 0; i < this->v; i++){
            if(result[i] >= count) count = result[i];
        }
        for(int i = 0; i <= count; i++){
            cout << "Color " << i << " : ";
            for(int j = 0; j < this->v; j++){
                if(result[j] == i) cout << "V" << j << "  ";
            }
            cout << endl;
        }
        cout << endl << "The chromatic number is : " << count+1 <<endl;
    }
};

int main(){

    cout << "Enter the number of vertices :" << endl;
    int num_v;
    cin >> num_v;

    graph a(num_v);

    a.add();

    a.dfs(0);

    a.coloring();

}