class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26);

        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<bool> used(26, false);
        string answer;

        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            int index = ch - 'a';

            if (used[index]) {
                continue;
            }

            while (!answer.empty() &&
                   answer.back() > ch &&
                   lastIndex[answer.back() - 'a'] > i) {

                used[answer.back() - 'a'] = false;
                answer.pop_back();
            }

            answer.push_back(ch);
            used[index] = true;
        }

        return answer;
    }
};