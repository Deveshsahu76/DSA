class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAX_XOR = 2048;

        vector<bool> pairXor(MAX_XOR, false);
        vector<bool> tripletXor(MAX_XOR, false);

        int n = nums.size();

        // All possible XOR values of two chosen elements
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                pairXor[nums[i] ^ nums[j]] = true;
            }
        }

        // Combine every pair XOR with a third element
        for (int value = 0; value < MAX_XOR; value++) {
            if (!pairXor[value]) {
                continue;
            }

            for (int num : nums) {
                tripletXor[value ^ num] = true;
            }
        }

        int answer = 0;

        for (bool present : tripletXor) {
            if (present) {
                answer++;
            }
        }

        return answer;
    }
};