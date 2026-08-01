class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();

        vector<vector<long long>> dp(
            n,
            vector<long long>(n, 0)
        );

        // Single element remaining
        for (int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
        }

        for (int length = 2; length <= n; length++) {
            for (int left = 0; left + length - 1 < n; left++) {
                int right = left + length - 1;

                long long takeLeft =
                    nums[left] - dp[left + 1][right];

                long long takeRight =
                    nums[right] - dp[left][right - 1];

                dp[left][right] = max(takeLeft, takeRight);
            }
        }

        // Tie bhi Player 1 ki victory hai
        return dp[0][n - 1] >= 0;
    }
};