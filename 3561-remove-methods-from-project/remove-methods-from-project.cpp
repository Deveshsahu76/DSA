class Solution {
public:
    vector<int> remainingMethods(
        int n,
        int k,
        vector<vector<int>>& invocations
    ) {
        vector<vector<int>> graph(n);

        for (const auto& edge : invocations) {
            int from = edge[0];
            int to = edge[1];

            graph[from].push_back(to);
        }

        vector<bool> suspicious(n, false);
        queue<int> q;

        q.push(k);
        suspicious[k] = true;

        // Find every method reachable from k
        while (!q.empty()) {
            int method = q.front();
            q.pop();

            for (int nextMethod : graph[method]) {
                if (!suspicious[nextMethod]) {
                    suspicious[nextMethod] = true;
                    q.push(nextMethod);
                }
            }
        }

        // Check whether an outside method invokes a suspicious method
        for (const auto& edge : invocations) {
            int from = edge[0];
            int to = edge[1];

            if (!suspicious[from] && suspicious[to]) {
                vector<int> allMethods;

                for (int method = 0; method < n; method++) {
                    allMethods.push_back(method);
                }

                return allMethods;
            }
        }

        // Removal is possible
        vector<int> answer;

        for (int method = 0; method < n; method++) {
            if (!suspicious[method]) {
                answer.push_back(method);
            }
        }

        return answer;
    }
};