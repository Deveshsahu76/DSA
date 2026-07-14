class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;

        int maxValue = *max_element(nums.begin(), nums.end());

        // dp[g1][g2] = number of ways where
        // seq1 ka GCD = g1 and seq2 ka GCD = g2
        vector<vector<int>> dp(
            maxValue + 1,
            vector<int>(maxValue + 1, 0)
        );

        // Dono subsequences initially empty
        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<int>> next = dp; // num ko skip karna

            for (int gcd1 = 0; gcd1 <= maxValue; gcd1++) {
                for (int gcd2 = 0; gcd2 <= maxValue; gcd2++) {
                    int ways = dp[gcd1][gcd2];

                    if (ways == 0) {
                        continue;
                    }

                    // num ko seq1 me add karo
                    int newGcd1 = gcd(gcd1, num);

                    next[newGcd1][gcd2] =
                        (next[newGcd1][gcd2] + ways) % MOD;

                    // num ko seq2 me add karo
                    int newGcd2 = gcd(gcd2, num);

                    next[gcd1][newGcd2] =
                        (next[gcd1][newGcd2] + ways) % MOD;
                }
            }

            dp = move(next);
        }

        long long answer = 0;

        // gcd > 0 ensures both subsequences are non-empty
        for (int g = 1; g <= maxValue; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }

        return answer;
    }
};