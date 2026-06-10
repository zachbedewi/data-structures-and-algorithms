class Solution {
  public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(to_string(num2)) - solve(to_string(num1 - 1));
    }

  private:
    // memo[i][isTight][direction][prevDigit+1][started] = {waviness, count}
    // direction: 0=none, 1=up, 2=down, 3=equal
    // prevDigit: -1..9 → stored as 0..10
    map<tuple<int, int, int, int, int>, pair<long long, long long>> memo;

    long long solve(const string &limit) {
        memo.clear();
        return dfs(limit, 0, 1, 0, -1, 0).first;
    }

    pair<long long, long long> dfs(const string &limit, int i, int isTight,
                                   int direction, int prevDigit, int started) {
        if (i == (int)limit.length()) {
            return {0, started ? 1 : 0};
        }

        auto key = make_tuple(i, isTight, direction, prevDigit, started);
        if (memo.count(key))
            return memo[key];

        long long waviness = 0, count = 0;
        int maxD = isTight ? (limit[i] - '0') : 9;

        for (int d = 0; d <= maxD; ++d) {
            int newTight = isTight && (d == maxD);
            int newStarted = started || (d != 0);

            int newDirection = 0;
            int newPrev = d;
            if (!newStarted) {
                newDirection = 0;
                newPrev = -1;
            } else if (!started) {
                // first real digit
                newDirection = 0;
            } else {
                if (d > prevDigit)
                    newDirection = 1;
                else if (d < prevDigit)
                    newDirection = 2;
                else
                    newDirection = 3;
            }

            auto [w, c] =
                dfs(limit, i + 1, newTight, newDirection, newPrev, newStarted);

            // A peak/valley occurs at prevDigit when direction changes
            if (started && newStarted) {
                if (isPeak(direction, prevDigit, d) ||
                    isValley(direction, prevDigit, d)) {
                    waviness += c;
                }
            }
            waviness += w;
            count += c;
        }

        return memo[key] = {waviness, count};
    }

    bool isPeak(int direction, int prevDigit, int d) {
        return direction == 1 && d < prevDigit;
    }

    bool isValley(int direction, int prevDigit, int d) {
        return direction == 2 && d > prevDigit;
    }
};
