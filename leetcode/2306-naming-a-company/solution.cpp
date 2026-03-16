class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        vector<unordered_set<string>> ideasByCharacter(26);
        for (const auto& idea : ideas) {
            ideasByCharacter[idea[0] - 'a'].insert(idea.substr(1));
        }

        long long res = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = i + 1; j < 26; ++j) {
                long long distinctWithFirst = 0L;
                long long distinctWithSecond = 0L;

                for (const auto& suffix : ideasByCharacter[i]) {
                    if (!ideasByCharacter[j].count(suffix)) {
                        ++distinctWithFirst;
                    }
                }

                for (const auto& suffix : ideasByCharacter[j]) {
                    if (!ideasByCharacter[i].count(suffix)) {
                        ++distinctWithSecond;
                    }
                }

                res += distinctWithFirst * distinctWithSecond;
            }
        }

        return res * 2;
    }
};
