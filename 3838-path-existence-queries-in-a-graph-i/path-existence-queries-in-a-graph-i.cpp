class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        
        vector<int> component(n);
        int compId = 0;

        component[0] = compId;

        for (int i = 1; i < n; i++) {
            if (nums[i] - nums[i - 1] > maxDiff) {
                compId++;
            }

            component[i] = compId;
        }

        vector<bool> answer;

        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];

            answer.push_back(component[u] == component[v]);
        }

        return answer;
    }
};