class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];   // same start, bigger end first
            }
            return a[0] < b[0];       // smaller start first
        });

        int count = 0;
        int maxRight = 0;

        for (auto &interval : intervals) {
            int right = interval[1];

            if (right > maxRight) {
                count++;
                maxRight = right;
            }
        }

        return count;
    }
};