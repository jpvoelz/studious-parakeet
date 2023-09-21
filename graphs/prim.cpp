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

        int prim(){

            // Create priority queue
            priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
            // Create vector to keep track of whether nodes are in the MST
            vector<bool> inMST(n, false);
            // Create vector for keys, initialized to infinity
            vector<int> key(n,numeric_limits<int>::max());
            // Create vector to store parents, and thus the MST
            vector<int> parent(n, -1);

            // Pick first vertex as source and set its key to zero. Add to pq
            int s = 0;
            pq.push(make_pair(0, s));
            key[s] = 0;

            int cost = 0;

            while(!pq.empty()){

                // Get the node at the top of the queue and remove it
                int u = pq.top().second;
                pq.pop();

                // Ignore the node if we have already added it to the MST
                if(inMST[u] == true) continue;

                // Include node in MST and add the cost
                inMST[u] = true;
                cost += key[u];

                // Iterate through all of the neighbors of the node
                for(const pair<int,int>& edge: adj_list[u]){
                    int v = edge.first;
                    int edge_weight = edge.second;
                    // If the node is not in the MST, and this edge weight
                    // is lower than the current key, then update the key
                    // and add to the priority queue
                    if (inMST[v] == false && key[v] > edge_weight){
                        key[v] = edge_weight;
                        pq.push(make_pair(key[v], v));
                        parent[v] = u;
                    }

                }

            }

            cout << "The min cost spanning tree has cost " << cost << "." << endl;
            cout << "Its edges are:" << endl;
            for (int i = 1; i < n; ++i)
                cout << i << " - " << parent[i] << endl;

            return cost;
 
        }

        Graph(string filename){

            ifstream inputFile(filename);
            string line;
            // Use the first line to create the graph
            getline(inputFile, line);
            this->n = stoi(line);
            vector<vector<pair<int, int> > > graph(n);
            adj_list = graph;

            // Iterate through the rest of the lines
            // Split them with a space delimiter and create edges
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
    graph.prim();
    return 0;

}