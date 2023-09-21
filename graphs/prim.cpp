#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Graph {

    private:
        int n;
        vector<vector<pair<int, int> > > adj_list;

    public:

        void add_edge(int u, int v, int dist){
            adj_list[u].push_back(make_pair(v, dist));
        }

        void print_graph(){

            for (int i = 0; i < adj_list.size(); ++i) {
                cout << "Node: " << i << endl;
                for (const auto& edge : adj_list[i]) {
                    cout << "    Neighbor: " << edge.first << " Edge Weight: " << edge.second << endl;
                }
            }

        }

        Graph(string filename){

            ifstream inputFile(filename);
            string line;
            // Use the first line to create the graph
            getline(inputFile, line);
            this->n = stoi(line);
            vector<vector<pair<int, int> > > graph(n);
            adj_list = graph;

            while(getline(inputFile, line)){
                istringstream iss(line);
                vector<int> tokens;
                string token;
                while (getline(iss, token, ' ')) {
                    tokens.push_back(stoi(token));
                }
                this->add_edge(tokens[0], tokens[1], tokens[2]);
            }
            inputFile.close();

        }
};


int main(){

    Graph graph = Graph("data/mst_data.txt");
    graph.print_graph();
    return 0;

}