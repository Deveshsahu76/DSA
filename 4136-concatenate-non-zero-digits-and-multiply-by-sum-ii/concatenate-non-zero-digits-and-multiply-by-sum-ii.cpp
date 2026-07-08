class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007;

        vector<int> pos;
        vector<int> digits;

        int m = s.size();

        // Store only non-zero digits and their original positions
        for (int i = 0; i < m; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digits.push_back(s[i] - '0');
            }
        }

        int n = digits.size();

        vector<long long> pow10(n + 1, 1);
        vector<long long> prefixValue(n + 1, 0);
        vector<long long> prefixSum(n + 1, 0);

        // Precompute powers of 10
        for (int i = 1; i <= n; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        // prefixValue stores concatenated value modulo MOD
        for (int i = 0; i < n; i++) {
            prefixValue[i + 1] = (prefixValue[i] * 10 + digits[i]) % MOD;
            prefixSum[i + 1] = prefixSum[i] + digits[i];
        }

        vector<int> answer;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int start = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int end = upper_bound(pos.begin(), pos.end(), r) - pos.begin();

            // No non-zero digit in this range
            if (start >= end) {
                answer.push_back(0);
                continue;
            }

            int len = end - start;

            long long x = prefixValue[end] - (prefixValue[start] * pow10[len]) % MOD;

            if (x < 0) {
                x += MOD;
            }

            long long digitSum = prefixSum[end] - prefixSum[start];

            long long result = (x * (digitSum % MOD)) % MOD;

            answer.push_back((int)result);
        }

        return answer;
    }
};