class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            int taken = 0;
            dp[i] = INT_MIN;

            for (int count = 1; count <= 3 && i + count <= n; count++) {
                taken += stoneValue[i + count - 1];

                dp[i] = max(
                    dp[i],
                    taken - dp[i + count]
                );
            }
        }

        if (dp[0] > 0) {
            return "Alice";
        }

        if (dp[0] < 0) {
            return "Bob";
        }

        return "Tie";
    }
};