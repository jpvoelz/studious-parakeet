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
            //printf("Vertex Distance from Source\n");
            //for (int i = 0; i < n; ++i)
                //printf("%d \t\t %d\n", i, distance[i]);

            return distance;
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

template <typename T>
double arr_average(vector<T> arr){

    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    double average = static_cast<double>(sum) / arr.size();
    return average;
}

void simulation(){
    int n_nodes = 50;
    int max_dist = 10;
    vector<double> avg_20;
    vector<double> avg_40;
    for(int i = 0; i < 50; i++){
        Graph graph_20 = Graph(n_nodes, 0.2, max_dist);
        Graph graph_40 = Graph(n_nodes, 0.4, max_dist);
        vector<int> distance_20 = graph_20.dijkstra(0);
        vector<int> distance_40 = graph_40.dijkstra(0);
        avg_20.push_back(arr_average(distance_20));
        avg_40.push_back(arr_average(distance_40));
    }
    
    cout << "The average path for the graph of density 0.2 is " << arr_average(avg_20) << endl;
    cout << "The average path for the graph of density 0.4 is " << arr_average(avg_40) << endl;
}

int main(){

    simulation();
    return 0;

}

