class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int minimum = *min_element(nums.begin(), nums.end());
        int maximum = *max_element(nums.begin(), nums.end());

        unordered_set<int> present(nums.begin(), nums.end());
        vector<int> answer;

        for (int value = minimum + 1; value < maximum; value++) {
            if (!present.count(value)) {
                answer.push_back(value);
            }
        }

        return answer;
    }
};