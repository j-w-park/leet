#include "list_node.h"
#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    static void sumNodeRecursive(ListNode *n, ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr && l2 == nullptr)
        {
            return;
        }

        ListNode *l1Next = nullptr;
        if (l1 != nullptr)
        {
            l1Next = l1->next;
            n->val += l1->val;
        }

        ListNode *l2Next = nullptr;
        if (l2 != nullptr)
        {
            l2Next = l2->next;
            n->val += l2->val;
        }

        if (l1Next != nullptr || l2Next != nullptr || n->val >= 10)
        {
            n->next = new ListNode{n->val / 10};
        }
        n->val %= 10;

        return sumNodeRecursive(n->next, l1Next, l2Next);
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        using namespace std;
        auto ans = new ListNode{};
        sumNodeRecursive(ans, l1, l2);
        return ans;
    }
};

int main()
{
    auto cases = std::vector{
        std::make_pair(
            new ListNode(2, new ListNode(4, new ListNode(3))),
            new ListNode(5, new ListNode(6, new ListNode(4)))),
        std::make_pair(
            new ListNode(
                9,
                new ListNode(
                    9,
                    new ListNode(
                        9,
                        new ListNode(
                            9,
                            new ListNode(
                                9,
                                new ListNode(9)))))),
            new ListNode(
                9,
                new ListNode(
                    9,
                    new ListNode(
                        9,
                        new ListNode(9))))),
    };

    for (const auto &c : cases)
    {
        auto result = Solution().addTwoNumbers(std::get<0>(c), std::get<1>(c));
        for (auto node = result; node != nullptr; node = node->next)
        {
            std::cout << node->val << '\t';
        }
        std::cout << std::endl;
    }

    return 0;
}
