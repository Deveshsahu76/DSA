class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string digits = "123456789";
        vector<int> answer;

        for (int length = 2; length <= 9; length++) {
            for (int start = 0; start + length <= 9; start++) {
                int number = stoi(digits.substr(start, length));

                if (number >= low && number <= high) {
                    answer.push_back(number);
                }
            }
        }

        sort(answer.begin(), answer.end());

        return answer;
    }
};