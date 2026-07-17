class Solution {
public:
    vector<int> gcdValues(vector<int>& nums,
                          vector<long long>& queries) {
        
        int maxValue = *max_element(nums.begin(), nums.end());

        vector<long long> frequency(maxValue + 1, 0);

        for (int num : nums) {
            frequency[num]++;
        }

        // exactGcd[g] = number of pairs whose GCD is exactly g
        vector<long long> exactGcd(maxValue + 1, 0);

        for (int g = maxValue; g >= 1; g--) {

            long long divisibleCount = 0;

            // Count numbers divisible by g
            for (int multiple = g;
                 multiple <= maxValue;
                 multiple += g) {

                divisibleCount += frequency[multiple];
            }

            // All pairs where both numbers are divisible by g
            long long pairCount =
                divisibleCount * (divisibleCount - 1) / 2;

            // Remove pairs whose exact GCD is 2g, 3g, ...
            for (int multiple = 2 * g;
                 multiple <= maxValue;
                 multiple += g) {

                pairCount -= exactGcd[multiple];
            }

            exactGcd[g] = pairCount;
        }

        // prefix[g] = number of pairs having GCD <= g
        vector<long long> prefix(maxValue + 1, 0);

        for (int g = 1; g <= maxValue; g++) {
            prefix[g] = prefix[g - 1] + exactGcd[g];
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (long long query : queries) {

            // First GCD whose cumulative pair count is > query
            int gcdValue = upper_bound(
                prefix.begin(),
                prefix.end(),
                query
            ) - prefix.begin();

            answer.push_back(gcdValue);
        }

        return answer;
    }
};