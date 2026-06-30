class Solution {
public:
    vector<vector<int>> ans;

    void backtrack(vector<int>& nums, vector<int>& curr, vector<bool>& visited) {

        if (curr.size() == nums.size()) {
            ans.push_back(curr);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {

            if (visited[i])
                continue;

            visited[i] = true;
            curr.push_back(nums[i]);

            backtrack(nums, curr, visited);

            curr.pop_back();
            visited[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {

        vector<int> curr;
        vector<bool> visited(nums.size(), false);

        backtrack(nums, curr, visited);

        return ans;
    }
};