class Solution {
public:
    int dp[50][35];

    vector<array<int, 4>> fac = {
        {0,0,0,0}, // 0 unused
        {0,0,0,0}, // 1
        {1,0,0,0}, // 2
        {0,1,0,0}, // 3
        {2,0,0,0}, // 4
        {0,0,1,0}, // 5
        {1,1,0,0}, // 6
        {0,0,0,1}, // 7
        {3,0,0,0}, // 8
        {0,2,0,0}  // 9
    };

    int min23(int a, int b) {
        return dp[a][b];
    }

    int minDigits(array<int,4> need) {
        return need[2] + need[3] + min23(need[0], need[1]);
    }

    array<int,4> useDigit(array<int,4> need, int d) {
        for (int p = 0; p < 4; p++) {
            need[p] = max(0, need[p] - fac[d][p]);
        }
        return need;
    }

    string buildSuffix(int len, array<int,4> need) {
        string ans;

        for (int pos = 0; pos < len; pos++) {
            int remaining = len - pos - 1;

            for (int d = 1; d <= 9; d++) {
                auto nxt = useDigit(need, d);

                if (minDigits(nxt) <= remaining) {
                    ans.push_back(char('0' + d));
                    need = nxt;
                    break;
                }
            }
        }

        return ans;
    }

    string smallestNumber(string num, long long t) {

        // Factorize t
        array<int,4> total = {0,0,0,0};

        int primes[4] = {2,3,5,7};

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                total[i]++;
                t /= primes[i];
            }
        }

        // impossible: digit products only contain primes 2,3,5,7
        if (t != 1)
            return "-1";

        // DP for minimum digits required to supply factors 2 and 3
        const int INF = 1e9;

        for (int a = 0; a < 50; a++)
            for (int b = 0; b < 35; b++)
                dp[a][b] = INF;

        dp[0][0] = 0;

        for (int a = 0; a < 50; a++) {
            for (int b = 0; b < 35; b++) {

                if (a == 0 && b == 0)
                    continue;

                for (int d : {2,3,4,6,8,9}) {
                    int na = max(0, a - fac[d][0]);
                    int nb = max(0, b - fac[d][1]);

                    dp[a][b] = min(dp[a][b], 1 + dp[na][nb]);
                }
            }
        }

        int n = num.size();

        // Remaining factors before every position
        vector<array<int,4>> before(n + 1);
        vector<bool> valid(n + 1, false);

        array<int,4> need = total;
        bool okPrefix = true;

        for (int i = 0; i <= n; i++) {
            before[i] = need;
            valid[i] = okPrefix;

            if (i == n)
                break;

            int d = num[i] - '0';

            if (d == 0) {
                okPrefix = false;
            } else if (okPrefix) {
                need = useDigit(need, d);
            }
        }

        // num itself already valid
        if (valid[n] && minDigits(before[n]) == 0) {
            return num;
        }

        // Try to increase the rightmost possible digit
        for (int i = n - 1; i >= 0; i--) {

            if (!valid[i])
                continue;

            int current = num[i] - '0';
            int suffixLength = n - i - 1;

            for (int d = max(1, current + 1); d <= 9; d++) {

                auto remainingNeed = useDigit(before[i], d);

                if (minDigits(remainingNeed) <= suffixLength) {

                    string answer = num.substr(0, i);
                    answer.push_back(char('0' + d));

                    answer += buildSuffix(
                        suffixLength,
                        remainingNeed
                    );

                    return answer;
                }
            }
        }

        // Need a number with more digits
        int length = max(
            n + 1,
            minDigits(total)
        );

        return buildSuffix(length, total);
    }
};