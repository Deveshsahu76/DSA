class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // right[j] = latest index in word1 from where
        // word2[j...] can be matched exactly as a subsequence
        vector<int> right(m, -1);

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }

            if (p < 0) break;

            right[j] = p;
            p--;
        }

        vector<int> answer;

        int j = 0;
        bool mismatchUsed = false;

        for (int i = 0; i < n && j < m; i++) {

            // Exact match: always take earliest possible index
            if (word1[i] == word2[j]) {
                answer.push_back(i);
                j++;
            }

            // Use our one allowed mismatch
            else if (!mismatchUsed &&
                     (j == m - 1 || right[j + 1] > i)) {

                answer.push_back(i);
                mismatchUsed = true;
                j++;
            }
        }

        if (j != m) {
            return {};
        }

        return answer;
    }
};