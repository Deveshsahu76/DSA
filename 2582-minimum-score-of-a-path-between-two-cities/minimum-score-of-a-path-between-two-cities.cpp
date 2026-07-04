class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {

        vector<vector<pair<int, int>>> graph(n + 1);

        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int dist = road[2];

            graph[u].push_back({v, dist});
            graph[v].push_back({u, dist});
        }

        vector<bool> visited(n + 1, false);

        queue<int> q;
        q.push(1);
        visited[1] = true;

        int ans = INT_MAX;

        while (!q.empty()) {
            int city = q.front();
            q.pop();

            for (auto &edge : graph[city]) {
                int nextCity = edge.first;
                int distance = edge.second;

                ans = min(ans, distance);

                if (!visited[nextCity]) {
                    visited[nextCity] = true;
                    q.push(nextCity);
                }
            }
        }

        return ans;
    }
};