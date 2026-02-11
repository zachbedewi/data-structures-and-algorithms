class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        const int n = tiles.size();
        ranges::sort(tiles);

        int maxCovered = 0;
        int currentlyCovered = 0;
        int currentTile = 0;

        for (int carpetStart = 0; maxCovered < carpetLen && carpetStart < n; ++carpetStart) {
            while (currentTile < n && tiles[currentTile][1] - tiles[carpetStart][0] + 1 <= carpetLen) {
                currentlyCovered += tiles[currentTile][1] - tiles[currentTile][0] + 1;
                ++currentTile;
            }

            int partiallyCovered = 0;
            if (currentTile < n) {
                partiallyCovered = max(0, tiles[carpetStart][0] + carpetLen - (tiles[currentTile][0]));
            }
            maxCovered = max(maxCovered, currentlyCovered + partiallyCovered);
            currentlyCovered -= (tiles[carpetStart][1] - tiles[carpetStart][0] + 1);
        }

        return maxCovered;
    }
};
