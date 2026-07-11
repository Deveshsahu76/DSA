class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited,
             int& nodeCount, int& edgeCount) {
        
        visited[node] = true;
        nodeCount++;

        edgeCount += graph[node].size();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, graph, visited, nodeCount, edgeCount);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> graph(n);

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> visited(n, false);

        int answer = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {

                int nodeCount = 0;
                int edgeCount = 0;

                dfs(i, graph, visited, nodeCount, edgeCount);

                edgeCount /= 2;

                int requiredEdges = nodeCount * (nodeCount - 1) / 2;

                if (edgeCount == requiredEdges) {
                    answer++;
                }
            }
        }

        return answer;
    }
};