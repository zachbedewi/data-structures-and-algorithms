class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times)
        : times(times)
        , leaders(persons.size(), -1) {
        unordered_map<int, int> count;
        int lead = -1;

        for (int i = 0; i < persons.size(); ++i) {
            if (++count[persons[i]] >= count[lead]) {
                lead = persons[i];
            }
            leaders[i] = lead;
        }
    }

    int q(int t) {
        const auto it = --ranges::upper_bound(times, t);
        const auto index = distance(times.begin(), it);

        return leaders[index];
    }
private:
    const vector<int> times;
    vector<int> leaders;
};
