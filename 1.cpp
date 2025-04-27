
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

// Parallel BFS using OpenMP
void parallel_bfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    
    #pragma omp parallel
    while (!q.empty()) {
        int node;
        #pragma omp critical
        if (!q.empty()) {
            node = q.front();
            q.pop();
        }

        if (node != -1) {
            cout << "Visited " << node << endl;
            #pragma omp for
            for (int i = 0; i < graph[node].size(); i++) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    #pragma omp critical
                    q.push(neighbor);
                }
            }
        }
    }
}

// Parallel DFS using OpenMP
void parallel_dfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);

    #pragma omp parallel
    while (!s.empty()) {
        int node;
        #pragma omp critical
        if (!s.empty()) {
            node = s.top();
            s.pop();
        }

        if (node != -1) {
            cout << "Visited " << node << endl;
            visited[node] = true;
            #pragma omp for
            for (int i = 0; i < graph[node].size(); i++) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    // Example graph represented as an adjacency list
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}};
    int start_node = 0;

    cout << "Parallel BFS starting from node " << start_node << ":\n";
    parallel_bfs(graph, start_node);

    cout << "\nParallel DFS starting from node " << start_node << ":\n";
    parallel_dfs(graph, start_node);

    return 0;
}










