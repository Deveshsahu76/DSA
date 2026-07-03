class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int, int>>> graph(n);
        vector<int> indegree(n, 0);

        int maxCost = 0;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int cost = e[2];

            maxCost = max(maxCost, cost);

            // Offline node ke through path invalid hai
            if (!online[u] || !online[v]) continue;

            graph[u].push_back({v, cost});
            indegree[v]++;
        }

        // Topological Sort
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            topo.push_back(node);

            for (auto &edge : graph[node]) {
                int nextNode = edge.first;

                indegree[nextNode]--;

                if (indegree[nextNode] == 0) {
                    q.push(nextNode);
                }
            }
        }

        auto canReach = [&](int minEdgeCost) {
            const long long INF = 4e18;

            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int node : topo) {
                if (dist[node] == INF) continue;
                if (dist[node] > k) continue;

                for (auto &edge : graph[node]) {
                    int nextNode = edge.first;
                    int cost = edge.second;

                    if (cost < minEdgeCost) continue;

                    long long newCost = dist[node] + cost;

                    if (newCost < dist[nextNode]) {
                        dist[nextNode] = newCost;
                    }
                }
            }

            return dist[n - 1] <= k;
        };

        int low = 0;
        int high = maxCost;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canReach(mid)) {
                ans = mid;
                low = mid + 1;
            } 
            else {
                high = mid - 1;
            }
        }

        return ans;
    }
};