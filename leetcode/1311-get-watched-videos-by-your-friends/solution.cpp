class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos,
                                          vector<vector<int>>& friends, int id,
                                          int level) {
        queue<int> q {{id}};
        vector<bool> seen(friends.size(), false);
        seen[id] = true;

        for (int i = 0; i < level; ++i) {
            for (int sz = q.size(); sz > 0; --sz) {
                for (const int friend_ : friends[q.front()]) {
                    if (!seen[friend_]) {
                        seen[friend_] = true;
                        q.push(friend_);
                    }
                }
                q.pop();
            }
        }

        unordered_map<string, int> count;
        while (!q.empty()) {
            for (const auto& video : watchedVideos[q.front()]) {
                ++count[video];
            }
            q.pop();
        }

        set<pair<int, string>> frequencyAndVideo;
        for (const auto& [video, frequency] : count) {
            frequencyAndVideo.insert({frequency, video});
        }

        vector<string> ans;
        for (const auto& [_, video] : frequencyAndVideo) {
            ans.push_back(video);
        }
        return ans;
    }
};
