/*
    To run the program run following command.
    => $ g++ bfs.cpp -std=c++11  
    => $ ./a.out < maze.txt
*/


#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef pair<int,int> node;

const int N = 20;
string maze[N];
node start, goal;

// Representation of a graph....
map<node, vector<node> > nbrs;
map<node, int> dist;
map<node, node> pred;

void buildGraph(){
    int di[4] = {-1, +1, 0,  0 };
    int dj[4] = { 0,  0, -1,+1 };
    for (int i = 1; i < N-1; i++){
        for (int j = 1; j < maze[i].length()-1; j++){
            for (int k = 0; k < 4; k++){
                int nbr_i = i + di[k];
                int nbr_j = j + dj[k];
                node currNode = make_pair(i,j);
                node nbrNode = make_pair(nbr_i,nbr_j);
                if (maze[nbr_i][nbr_j] != '#'){ 
                    nbrs[currNode].push_back(nbrNode);
                }
            }   
        }
    }
}
void bfs(node start){

    queue<node> to_visit;
    to_visit.push(start);
    dist[start] = 0;

    while(!to_visit.empty()){

        node n = to_visit.front();
        to_visit.pop();

        // for node at front of queue, go through every node in it's associated vector of neighboring
        // nodes.  if any neighbors are not found in the map of distances (only the start has been initialized), 
        // the distance is set to be 1 more than the front node's distance value.  the neighbor's predecessor is 
        // then set to n (front of queue), and the neighbor is pushed to the list of nodes to visit.  The process re-starts 
        // with that node to visit next
        for (node nbr : nbrs[n]){
            if (dist.find(nbr) == dist.end()){    
                dist[nbr] = dist[n] + 1;
                pred[nbr] = n;
                to_visit.push(nbr);
            }
        }
    }
}


// make trace
void mark_trace(node start, node goal){
    if (start != goal) mark_trace(start, pred[goal]);   
    maze[goal.first][goal.second] = '.';
}

int main(){

    for (int i = 0; i < N; i++) getline(cin, maze[i]);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < maze[i].length(); j++){
            if (maze[i][j] == 'A') start = make_pair(i,j);
            if (maze[i][j] == 'B') goal = make_pair(i,j);
        }
    }

    buildGraph();
    bfs(start);
    mark_trace(start, goal);

    for (int i=0; i<N; i++) {
        for (int j=0; j<maze[i].length(); j++) {
            if (maze[i][j] == ' ') cout << "\e[37;40m";
            if (maze[i][j]  == '.') cout << "\e[37;41m";
            if (maze[i][j] == '#') cout << "\e[37;44m";
            cout << maze[i][j];
        }
        cout << "\e[37;40m\n";
    }

  return 0;
}
