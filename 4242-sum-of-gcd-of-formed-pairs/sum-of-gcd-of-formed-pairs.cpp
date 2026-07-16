class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefixGcd(n);
        int currentMax = 0;

        // Step 1: Prefix maximum aur GCD calculate karo
        for (int i = 0; i < n; i++) {
            currentMax = max(currentMax, nums[i]);
            prefixGcd[i] = std::gcd(nums[i], currentMax);
        }

        // Step 2: Sort karo
        sort(prefixGcd.begin(), prefixGcd.end());

        // Step 3: Smallest ko largest ke saath pair karo
        long long answer = 0;

        for (int left = 0; left < n / 2; left++) {
            int right = n - 1 - left;

            answer += std::gcd(
                prefixGcd[left],
                prefixGcd[right]
            );
        }

        return answer;
    }
};