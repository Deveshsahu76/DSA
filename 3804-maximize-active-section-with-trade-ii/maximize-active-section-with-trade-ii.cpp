class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        int totalOnes = 0;
        for (char ch : s) {
            totalOnes += (ch == '1');
        }

        // Run-length encoding
        vector<int> start, finish, length;
        vector<char> type;
        vector<int> runId(n);

        for (int i = 0; i < n; ) {
            int j = i;

            while (j < n && s[j] == s[i]) {
                j++;
            }

            int id = type.size();

            start.push_back(i);
            finish.push_back(j - 1);
            length.push_back(j - i);
            type.push_back(s[i]);

            for (int p = i; p < j; p++) {
                runId[p] = id;
            }

            i = j;
        }

        int runs = type.size();

        /*
            candidate[j] stores gain when run j is a block of 1s
            between two zero-runs:

                000 111 00
                gain = 3 + 2
        */
        vector<int> candidate(runs, 0);

        for (int j = 1; j + 1 < runs; j++) {
            if (type[j] == '1' &&
                type[j - 1] == '0' &&
                type[j + 1] == '0') {

                candidate[j] =
                    length[j - 1] + length[j + 1];
            }
        }

        // Iterative segment tree for range maximum
        int size = 1;

        while (size < runs) {
            size *= 2;
        }

        vector<int> segmentTree(2 * size, 0);

        for (int i = 0; i < runs; i++) {
            segmentTree[size + i] = candidate[i];
        }

        for (int i = size - 1; i >= 1; i--) {
            segmentTree[i] = max(
                segmentTree[2 * i],
                segmentTree[2 * i + 1]
            );
        }

        auto rangeMaximum = [&](int left, int right) {
            if (left > right) {
                return 0;
            }

            left += size;
            right += size;

            int result = 0;

            while (left <= right) {
                if (left % 2 == 1) {
                    result = max(result, segmentTree[left]);
                    left++;
                }

                if (right % 2 == 0) {
                    result = max(result, segmentTree[right]);
                    right--;
                }

                left /= 2;
                right /= 2;
            }

            return result;
        };

        // Calculates candidate when boundary zero-runs are partial
        auto boundaryGain = [&](int center, int l, int r) {
            if (center <= 0 || center + 1 >= runs) {
                return 0;
            }

            if (type[center] != '1' ||
                type[center - 1] != '0' ||
                type[center + 1] != '0') {
                return 0;
            }

            // Entire 1-run must be inside the query
            if (start[center] < l || finish[center] > r) {
                return 0;
            }

            int leftZeros =
                min(finish[center - 1], r) -
                max(start[center - 1], l) + 1;

            int rightZeros =
                min(finish[center + 1], r) -
                max(start[center + 1], l) + 1;

            if (leftZeros <= 0 || rightZeros <= 0) {
                return 0;
            }

            return leftZeros + rightZeros;
        };

        vector<int> answer;
        answer.reserve(queries.size());

        for (auto& query : queries) {
            int l = query[0];
            int r = query[1];

            int leftRun = runId[l];
            int rightRun = runId[r];

            int bestGain = 0;

            // Fully contained internal runs
            bestGain = max(
                bestGain,
                rangeMaximum(leftRun + 2, rightRun - 2)
            );

            // Candidate touching left boundary
            bestGain = max(
                bestGain,
                boundaryGain(leftRun + 1, l, r)
            );

            // Candidate touching right boundary
            bestGain = max(
                bestGain,
                boundaryGain(rightRun - 1, l, r)
            );

            answer.push_back(totalOnes + bestGain);
        }

        return answer;
    }
};