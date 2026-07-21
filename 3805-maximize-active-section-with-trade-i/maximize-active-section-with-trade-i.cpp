class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int originalOnes = 0;

        for (char ch : s) {
            if (ch == '1') {
                originalOnes++;
            }
        }

        string t = "1" + s + "1";
        int n = t.size();

        vector<int> zeroBlocks;

        int i = 0;

        while (i < n) {
            if (t[i] == '0') {
                int j = i;

                while (j < n && t[j] == '0') {
                    j++;
                }

                zeroBlocks.push_back(j - i);
                i = j;
            } else {
                i++;
            }
        }

        int bestGain = 0;

        // A removable block of 1s lies between two zero blocks.
        // After removing it, those two zero blocks merge and can be
        // converted to 1s. Net gain = leftZeros + rightZeros.
        for (int j = 0; j + 1 < (int)zeroBlocks.size(); j++) {
            bestGain = max(
                bestGain,
                zeroBlocks[j] + zeroBlocks[j + 1]
            );
        }

        return originalOnes + bestGain;
    }
};