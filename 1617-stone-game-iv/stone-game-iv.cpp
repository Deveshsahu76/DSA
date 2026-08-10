class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[0] = false
        // 0 stones -> current player cannot move -> loses

        for (int i = 1; i <= n; i++) {

            for (int x = 1; x * x <= i; x++) {

                // If after removing x*x stones,
                // opponent is in a losing position
                if (!dp[i - x * x]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};