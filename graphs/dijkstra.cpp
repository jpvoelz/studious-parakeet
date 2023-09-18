#include <iostream>
#include <unordered_map>
#include <random>

using namespace std;

class Graph {

    private:

        unordered_map<int, unordered_map<int, double> > adj_list;

    public:

        bool add_edge(int u, int v, double dist){
            if (adj_list.count(u) == 0 || adj_list.count(v) == 0)
                return false;
            adj_list[u][v] = dist;
            adj_list[v][u] = dist;
            return true;
        }

        void print_graph(){

            for (const auto& outerPair : adj_list) {
                cout << "Node: " << outerPair.first << endl;

                // Iterate through the inner map for each outer key
                for (const auto& innerPair : outerPair.second) {
                    cout << "    Neighbor: " << innerPair.first << " Edge Weight: " << innerPair.second << endl;
                }
            }

        }

        Graph(int n, double density, double dist_range){

            // Initialize a random number generator
            random_device rd;
            mt19937 gen(rd());  // Mersenne Twister engine

            // Define Bernoulli and uniform distributions
            bernoulli_distribution bernoulliDist(density);
            uniform_real_distribution<double> uniformDist(0.0, dist_range);

            // Randomly generate edges of the graph
            for(int i = 1; i <= n; ++i){
                for(int j = 1; j <= n; ++j){
                    if (i == j) continue;
                    bool result = bernoulliDist(gen);
                    if (result){
                        double dist = uniformDist(gen);
                        adj_list[i][j] = dist;
                        adj_list[j][i] = dist;
                    }
                }
            }

        }
};

int main(){

    Graph graph = Graph(10, 0.2, 1);
    graph.print_graph();
    return 0;

}

