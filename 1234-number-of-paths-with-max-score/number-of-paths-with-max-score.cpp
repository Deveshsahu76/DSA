class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;

        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        vector<pair<int, int>> dir = {
            {1, 0}, {0, 1}, {1, 1}
        };

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X') continue;

                if (i == n - 1 && j == n - 1) continue;

                int bestScore = -1;
                long long countWays = 0;

                for (auto d : dir) {
                    int ni = i + d.first;
                    int nj = j + d.second;

                    if (ni >= n || nj >= n) continue;
                    if (score[ni][nj] == -1) continue;

                    if (score[ni][nj] > bestScore) {
                        bestScore = score[ni][nj];
                        countWays = ways[ni][nj];
                    }
                    else if (score[ni][nj] == bestScore) {
                        countWays = (countWays + ways[ni][nj]) % MOD;
                    }
                }

                if (bestScore == -1) continue;

                int cellValue = 0;

                if (board[i][j] >= '1' && board[i][j] <= '9') {
                    cellValue = board[i][j] - '0';
                }

                score[i][j] = bestScore + cellValue;
                ways[i][j] = countWays % MOD;
            }
        }

        if (score[0][0] == -1) {
            return {0, 0};
        }

        return {score[0][0], ways[0][0]};
    }
};