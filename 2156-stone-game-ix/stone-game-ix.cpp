class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // If the number of remainder-0 stones is even,
        // the game essentially depends on whether both
        // remainder-1 and remainder-2 stones exist.
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // If cnt[0] is odd, Alice can win if one side
        // has at least 2 stones and the other side exists.
        return abs(cnt[1] - cnt[2]) > 2;
    }
};