class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2) {
            return n;
        }

        int power = 1;

        while (power <= n) {
            power *= 2;
        }

        return power;
    }
};