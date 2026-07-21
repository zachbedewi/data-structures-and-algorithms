class Solution {
  public:
    int rectangleArea(vector<vector<int>> &rectangles) {
        vector<int> xs;
        xs.reserve(rectangles.size() * 2);
        for (auto const &rect : rectangles) {
            xs.push_back(rect[0]);
            xs.push_back(rect[2]);
        }
        ranges::sort(xs);
        auto const duplicates = ranges::unique(xs);
        xs.erase(duplicates.begin(), duplicates.end());

        auto slabIndex = [&](int x) {
            return ranges::lower_bound(xs, x) - xs.begin();
        };

        struct Event {
            int y{};
            int x1{};
            int x2{};
            int delta{};
        };
        vector<Event> events;
        for (auto const &rect : rectangles) {
            events.emplace_back(rect[1], rect[0], rect[2], 1);
            events.emplace_back(rect[3], rect[0], rect[2], -1);
        }
        ranges::sort(events, {}, &Event::y);

        vector<int> coverage(xs.size() - 1, 0);
        long long area = 0;
        long long coveredWidth = 0;
        long long prevY = events.front().y;

        for (auto const &[y, x1, x2, delta] : events) {
            area = (area + (y - prevY) % mod * coveredWidth) % mod;
            prevY = y;

            for (auto i = slabIndex(x1); i < slabIndex(x2); ++i) {
                coverage[i] += delta;
            }

            coveredWidth = 0;
            for (int i = 0; i < coverage.size(); ++i) {
                if (coverage[i]) {
                    coveredWidth += xs[i + 1] - xs[i];
                }
            }
        }

        return area;
    }

  private:
    static constexpr int mod{1'000'000'000 + 7};
};
