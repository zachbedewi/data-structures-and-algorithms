class DisjointSet final {
public:
    explicit DisjointSet(size_t const sz_):
        mSets(sz_ + 1),
        mRanks(sz_ + 1)
    {
        // Initially each node is its own parent (separate set)
        std::iota(mSets.begin(), mSets.end(), 0uz);
    }

    [[nodiscard]]
    auto Find(size_t const val_) -> size_t {
        auto & set{mSets[val_]};
        // Path compression: recursively find root and attach current node directly to
        // the root
        if(val_ != set) {
            set = Find(set);
        }
        return set;
    }

    [[nodiscard]]
    auto Union(
        auto const val1_,
        auto const val2_
    ) -> bool {
        auto const set1{Find(val1_)};
        auto const set2{Find(val2_)};
        // Nodes already belong to the same set
        if(set1 == set2) {
            return false;
        }
        // Union by rank heuristic
        auto const rank1{mRanks[val1_]};
        auto const rank2{mRanks[val2_]};
        if(rank1 > rank2) {
            mSets[set2] = set1;
        } else {
            mSets[set1] = set2;
            // If ranks are equal, resulting root rank increases
            if(rank1 == rank2) {
                ++mRanks[set2];
            }
        }
        return true;
    }

private:
    std::vector<size_t> mRanks;
    std::vector<size_t> mSets;
};

class Solution final {
public:
    [[nodiscard]]
    auto minCostToSupplyWater(
        int const houseTotCnt_,
        std::vector<int> const & wellCostPerHouse_,
        std::vector<std::vector<int>> const & pipeAndCostList_
    ) const -> int;
};

auto Solution::minCostToSupplyWater(
    int const houseTotCnt_,
    std::vector<int> const & wellCostPerHouse_,
    std::vector<std::vector<int>> const & pipeAndCostList_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto pipeAndCostList{std::vector<std::array<int, 3>>()};
    pipeAndCostList.reserve(houseTotCnt_ + pipeAndCostList_.size());

    for(auto const houseIdx: vs::iota(0, std::ssize(wellCostPerHouse_))) {
        auto const houseFrom{0};
        auto const houseTo{houseIdx + 1};
        auto const cost{wellCostPerHouse_[houseIdx]};
        pipeAndCostList.emplace_back(std::array{houseFrom, houseTo, cost});
    }

    for(auto const & pipeAndCost: pipeAndCostList_) {
        auto const houseFrom{pipeAndCost[0]};
        auto const houseTo{pipeAndCost[1]};
        auto const cost{pipeAndCost[2]};
        pipeAndCostList.emplace_back(std::array{houseFrom, houseTo, cost});
    }

    rngs::sort(pipeAndCostList, std::less{},
        [] (auto const & edge_) {return edge_.back(); });
    auto dS{DisjointSet{static_cast<size_t>(houseTotCnt_)}};
    auto totalCost{0};

    for(auto const [houseFrom, houseTo, cost]: pipeAndCostList) {
        if(dS.Union(houseFrom, houseTo)) {
            totalCost += cost;
        }
    }
    return totalCost;
}
