#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph {

    private:
        int n;
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

        vector<int> dijkstra(int s){

            // Create vector for distances and priority queue
            vector<int> distance(n, numeric_limits<int>::max());
            priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

            // Add the source vertex to the priority queue and set its distance to 0
            pq.push(make_pair(0, s));
            distance[s] = 0;

            while(!pq.empty()){

                // Get the vertex at the top of the queue and its distance
                // Then remove it from the priority queue
                int u = pq.top().second;
                int dist_u = pq.top().first;
                pq.pop();

                // Now iterate through every neighbor of u
                for (const pair<int,int>& edge: adj_list[u]){
                    int v = edge.first;
                    int edge_weight = edge.second;
                    int new_distance = edge_weight + distance[u];
                    // Check for relaxation
                    if(new_distance < distance[v]){
                        distance[v] = new_distance;
                        pq.push(make_pair(distance[v], v));
                    }
                }

            }

            // Print shortest distances
            printf("Vertex Distance from Source\n");
            for (int i = 0; i < n; ++i)
                printf("%d \t\t %d\n", i, distance[i]);
        }

        Graph(int n, double density, int dist_range){

            // Initialize adjacency list
            this->n = n;
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
    graph.dijkstra(0);
    return 0;

}

