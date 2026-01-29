int>> numToIndices;
        for (int i = 0; i < n; ++i) {
            numToIndices[arr[i]].push_back(i);
        }

        vector<bool> visited(n);
        visited[0] = true;
        queue<int> q {{0}};
        int numSteps = 0;
        while (!q.empty()) {
            for (int sz = q.size(); sz > 0; --sz) {
                const auto id = q.front();
                q.pop();
                if (id == n - 1) {
                    return numSteps;
                }

                vector<int> children = numToIndices[arr[id]];
                children.push_back(id - 1);
                children.push_back(id + 1);
                for (const auto child : children) {
                    if (child >= 0 && child < n && !visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
                numToIndices[arr[id]].clear();
            }

            ++numSteps;
        }

        return 0;
    }
};
