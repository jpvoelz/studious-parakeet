#include <iostream>
#include <unordered_map>
#include <random>
#include <vector>

using namespace std;

class Graph {

    private:

        vector<vector<pair<int, int> > > adj_list;

    public:

        void add_edge(int u, int v, int dist){
            adj_list[u].push_back(make_pair(v, dist));
            adj_list[v].push_back(make_pair(u, dist));
        }

        void print_graph(){

            for (int i = 0; i < adj_list.size(); ++i) {
                cout << "Node: " << i << endl;
                for (const auto& edge : adj_list[i]) {
                    cout << "    Neighbor: " << edge.first << " Edge Weight: " << edge.second << endl;
                }
            }

        }

        Graph(int n, double density, int dist_range){

            // Initialize adjacency list
            vector<vector<pair<int, int> > > graph(n);
            adj_list = graph;

            // Initialize a random number generator
            random_device rd;
            mt19937 gen(rd());

            // Define Bernoulli and uniform distributions
            bernoulli_distribution bernoulliDist(density);
            uniform_int_distribution<int> uniformDist(1, dist_range);

            // Randomly generate edges of the graph
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    if (i == j) continue;
                    bool result = bernoulliDist(gen);
                    if (result){
                        int dist = uniformDist(gen);
                        this->add_edge(i, j, dist);
                    }
                }
            }

        }
};

int main(){

    Graph graph = Graph(10, 0.2, 5);
    graph.print_graph();
    return 0;

}

