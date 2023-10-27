#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    static std::vector<int> twoSum(std::vector<int> &nums, int target)
    {
        using namespace std;

        if (nums.size() == 2)
        {
            return {0, 1};
        }

        auto indexTable = unordered_map<int, int>(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            indexTable.emplace(nums[i], i);
        }

        for (size_t i = 0; i < indexTable.bucket_count(); ++i)
        {
            cout << indexTable.bucket_size(i) << endl;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            auto complement = target - nums[i];
            if (
                auto it = indexTable.find(complement);
                it != indexTable.end())
            {
                auto coIndex = get<1>(*it);
                if (coIndex != i)
                {
                    return {i, coIndex};
                }
            }
        }

        throw invalid_argument("failed :(");
    }
};

int main()
{
    auto target = 9;
    auto v = std::vector<int>{-2, 7, 11, 15};
    auto ans = Solution::twoSum(v, target);
    for (const auto &e : ans)
    {
        std::cout << e << '\t';
    }
    std::cout << std::endl;
}
