class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());

        vector<int> rank(n);

        for (int i = 0; i < n; i++) {
            int originalIndex = arr[i].second;
            rank[originalIndex] = i;
        }

        // Component creation
        vector<int> comp(n, 0);
        int compId = 0;

        for (int i = 1; i < n; i++) {
            if (arr[i].first - arr[i - 1].first > maxDiff) {
                compId++;
            }

            comp[i] = compId;
        }

        // reach[i] = farthest sorted index reachable from i in one edge
        vector<int> reach(n);

        int right = 0;

        for (int i = 0; i < n; i++) {
            if (right < i) {
                right = i;
            }

            while (right + 1 < n && arr[right + 1].first - arr[i].first <= maxDiff) {
                right++;
            }

            reach[i] = right;
        }

        // Binary lifting
        int LOG = 20;

        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++) {
            up[0][i] = reach[i];
        }

        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                up[p][i] = up[p - 1][up[p - 1][i]];
            }
        }

        vector<int> answer;

        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];

            int a = rank[u];
            int b = rank[v];

            if (a == b) {
                answer.push_back(0);
                continue;
            }

            if (a > b) {
                swap(a, b);
            }

            if (comp[a] != comp[b]) {
                answer.push_back(-1);
                continue;
            }

            int steps = 0;
            int curr = a;

            for (int p = LOG - 1; p >= 0; p--) {
                if (up[p][curr] < b) {
                    curr = up[p][curr];
                    steps += (1 << p);
                }
            }

            answer.push_back(steps + 1);
        }

        return answer;
    }
};