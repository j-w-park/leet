#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

typedef pair<int, int> Point;

class Solution
{
private:
    void printMap(const vector<vector<int>> &m) const
    {
        cout << "MAP ====================" << endl;
        for (const auto &row : m)
        {
            for (int x = 0; x < row.size() - 1; ++x)
            {
                cout << row[x] << ", ";
            }
            cout << row[row.size() - 1] << endl;
        }
        cout << "========================" << endl;
    }

    void printPair(string &&label, const Point &p) const
    {
        cout << label << " (" << p.first << ", " << p.second << ")" << endl;
    }

    int heightAt(const Point &p, const vector<vector<int>> &m) const
    {
        return m[p.second][p.first];
    }

    bool isInner(const Point &p, const vector<vector<int>> &m) const
    {
        auto x{p.first}, y{p.second};
        auto numRows{m.size()}, numCols{m[0].size()};
        return (0 < x && x < numCols - 1) && (0 < y && y < numRows - 1);
    }

public:
    int trapRainWater(vector<vector<int>> &m)
    {
        priority_queue<pair<Point, int>, vector<pair<Point, int>>, greater<pair<Point, int>>> pq;

        int numRows = m.size();
        int numCols = m[0].size();
        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));

        for (int x = 0; x < numCols; ++x)
        {
            pq.push({{x, 0}, m[0][x]});
            visited[0][x] = true;

            pq.push({{x, numRows - 1}, m[numRows - 1][x]});
            visited[numRows - 1][x] = true;
        }

        for (int y = 1; y < numRows - 1; ++y)
        {
            pq.push({{0, y}, m[y][0]});
            visited[y][0] = true;

            pq.push({{y, numCols - 1}, m[y][numCols - 1]});
            visited[y][numCols - 1] = true;
        }

        cout << "visited: " << endl;
        for (int y = 0; y < numRows; ++y)
        {
            for (int x = 0; x < numCols - 1; ++x)
            {
                cout << visited[y][x] << ", ";
            }
            cout << visited[y][numCols - 1] << endl;
        }

        return 0;
    }
};

// this->printMap(heightMap);

// int maxHeight = -1;
// for (int y = 0; y < heightMap.size(); ++y) {
//     auto row = heightMap[y];
//     for (int x = 0; x < row.size(); ++x) {
//         if (maxHeight < heightMap[y][x]) {
//             maxHeight = heightMap[y][x];
//         }
//     }
// }
// cout << "max height: " << maxHeight << endl;

// int minHeight = maxHeight;
// for (int y = 0; y < heightMap.size(); ++y) {
//     auto row = heightMap[y];
//     for (int x = 0; x < row.size(); ++x) {
//         if (minHeight > heightMap[y][x]) {
//             minHeight = heightMap[y][x];
//         }
//     }
// }
// cout << "min height: " << minHeight << endl;

// vector<vector<int>> waterMap;
// waterMap.reserve(heightMap.size());
// for (int y = 0; y < heightMap.size(); ++y) {
//     vector<int> invRow;
//     invRow.reserve(heightMap[y].size());
//     for (int x = 0; x < heightMap[y].size(); ++x) {
//         invRow.push_back(0);
//     }
//     waterMap.push_back(invRow);
// }
// for (int y = 1; y < waterMap.size() - 1; ++y) {
//     auto& row = waterMap[y];
//     for (int x = 1; x < row.size() - 1; ++x) {
//         row[x] = maxHeight - heightMap[y][x];
//     }
// }
// this->printMap(waterMap);

// for (int y = 0; y < heightMap.size(); ++y) {
//     auto l = heightMap[y].size();
//     for (int x = 0; x < l - 1; ++x) {
//         cout << "(" << heightMap[y][x] << "," << waterMap[y][x]
//              << "), ";
//     }
//     cout << "(" << heightMap[y][l - 1] << ", " << waterMap[y][l - 1]
//          << ")" << endl;
// }

// for (int y = 1; y < heightMap.size() - 1; ++y) {
//     for (int x = 1; x < heightMap[y].size() - 1; ++x) {
//         int uh = heightMap[y - 1][x] + waterMap[y - 1][x];
//         int rh = heightMap[y][x + 1] + waterMap[y][x + 1];
//         int dh = heightMap[y + 1][x] + waterMap[y + 1][x];
//         int lh = heightMap[y][x - 1] + waterMap[y][x - 1];
//         int minh = min({uh, rh, dh, lh});
//         cout << "(" << x << ", " << y << "): " << minh << endl;
//     }
// }

// [10,40,30,10,30,20]
// [30,20,10,30,20,40]
// [20,30,30,20,30,10]

// [1,4,3,1,3,2]
// [3,2,1,4,2,4]
// [3,2,3,5,2,4]
// [3,2,1,4,2,4]
// [2,2,1,2,3,1]
//
// [1,4,3,1,3,2]
// [3,2,1,4,2,4]
// [3,2,3,5,2,4]
// [3,2,1,4,2,4]
// [2,2,1,2,3,1]
//
// [3,3,3,3,3]
// [3,2,2,2,3]
// [3,2,1,2,3]
// [3,2,2,2,3]
// [3,3,3,3,3]
//
// [3,3,3,3,3]
// [3,3,3,3,3]
// [3,3,2,3,3]
// [3,3,3,3,3]
// [3,3,3,3,3]
//
// [3,3,3,3,3]
// [3,3,2,3,3]
// [3,2,1,2,3]
// [3,2,2,2,3]
// [3,3,3,3,3]
//
//
// [3,3,3,3,3]
// [3,3,4,2,3]
// [3,2,4,2,3]
// [3,2,4,3,3]
// [3,3,3,3,3]
//
//
//
// [(1,0),(4,0),(3,0),(1,0),(3,0),(2,0)] [1,4,3,1,3,2]
// [(3,0),(2,2),(1,3),(3,1),(2,2),(4,0)] [3,4,4,4,4,4]
// [(2,0),(3,0),(3,0),(2,0),(3,0),(1,0)] [2,3,3,2,3,1]
//
// [(1,0),(4,0),(3,0),(1,0),(3,0),(2,0)] [1,4,3,1,3,2]
// [(3,0),(2,1),(1,2),(3,0),(2,1),(4,0)] [3,3,3,3,3,4]
// [(2,0),(3,0),(3,0),(2,0),(3,0),(1,0)] [2,3,3,2,3,1]

// bool checkTrapped(int x, int y,
//                   const vector<vector<int>>& heightMap) const {
//     int height = heightMap[y][x];
//     return height < heightMap[y - 1][x] && height < heightMap[y][x + 1] &&
//            height < heightMap[y + 1][x] && height < heightMap[y][x - 1];
// }

// vector<vector<int>> wateredMap{heightMap};
// while (true)
// {
//     this->printMap(wateredMap);

//     vector<set<pair<int, int>>> ponds;
//     for (int y = 1; y < wateredMap.size() - 1; ++y)
//     {
//         for (int x = 1; x < wateredMap[y].size() - 1; ++x)
//         {
//             auto start = make_pair(x, y);

//             auto up = make_pair(x, y - 1);
//             auto right = make_pair(x + 1, y);
//             auto down = make_pair(x, y + 1);
//             auto left = make_pair(x - 1, y);

//             auto h = this->heightAt(start, wateredMap);
//             auto uh = this->heightAt(up, wateredMap);
//             auto rh = this->heightAt(right, wateredMap);
//             auto dh = this->heightAt(down, wateredMap);
//             auto lh = this->heightAt(left, wateredMap);

//             bool shouldSkip = false;
//             for (const auto &pond : ponds)
//             {
//                 if (pond.contains(start))
//                 {
//                     shouldSkip = true;
//                     break;
//                 }
//             }
//             if (h == max({h, uh, rh, dh, lh}))
//             {
//                 shouldSkip = true;
//             }
//             if (shouldSkip)
//             {
//                 continue;
//             }

//             queue<pair<int, int>> toVisit;
//             set<pair<int, int>> visited;

//             toVisit.push(start);
//             visited.insert(start);
//             while (!toVisit.empty())
//             {
//                 auto &p = toVisit.front();
//                 toVisit.pop();

//                 auto h = this->heightAt(p, wateredMap);
//                 auto up = make_pair(p.first, p.second - 1);
//                 auto right = make_pair(p.first + 1, p.second);
//                 auto down = make_pair(p.first, p.second + 1);
//                 auto left = make_pair(p.first - 1, p.second);
//                 auto uh = this->heightAt(up, wateredMap);
//                 auto rh = this->heightAt(right, wateredMap);
//                 auto dh = this->heightAt(down, wateredMap);
//                 auto lh = this->heightAt(left, wateredMap);

//                 if (this->isInner(up, wateredMap) && uh <= h &&
//                     !visited.contains(up))
//                 {
//                     toVisit.push(up);
//                     visited.insert(up);
//                 }
//                 if (this->isInner(right, wateredMap) && rh <= h &&
//                     !visited.contains(right))
//                 {
//                     toVisit.push(right);
//                     visited.insert(right);
//                 }
//                 if (this->isInner(down, wateredMap) && dh <= h &&
//                     !visited.contains(down))
//                 {
//                     toVisit.push(down);
//                     visited.insert(down);
//                 }
//                 if (this->isInner(left, wateredMap) && lh <= h &&
//                     !visited.contains(left))
//                 {
//                     toVisit.push(left);
//                     visited.insert(left);
//                 }
//             }

//             set<pair<int, int>> *intersectedPond = nullptr;
//             for (auto &pond : ponds)
//             {
//                 for (const auto &p : pond)
//                 {
//                     if (visited.contains(p))
//                     {
//                         intersectedPond = &pond;
//                         break;
//                     }
//                 }
//                 if (intersectedPond != nullptr)
//                 {
//                     break;
//                 }
//             }
//             if (intersectedPond == nullptr)
//             {
//                 ponds.push_back(visited);
//             }
//             else
//             {
//                 for (const auto &p : visited)
//                 {
//                     intersectedPond->insert(p);
//                 }
//             }
//         }
//     }

//     vector<int> minPondHeights;
//     minPondHeights.reserve(ponds.size());
//     for (const auto &pond : ponds)
//     {
//         int minHeight = 0x7fffffff;
//         for (const auto &p : pond)
//         {
//             this->printPair("", p);
//             auto x{p.first}, y{p.second};
//             auto up = make_pair(x, y - 1);
//             auto right = make_pair(x + 1, y);
//             auto down = make_pair(x, y + 1);
//             auto left = make_pair(x - 1, y);
//             if (!pond.contains(up))
//             {
//                 minHeight =
//                     min({minHeight, this->heightAt(up, wateredMap)});
//             }
//             if (!pond.contains(right))
//             {
//                 minHeight =
//                     min({minHeight, this->heightAt(right, wateredMap)});
//             }
//             if (!pond.contains(down))
//             {
//                 minHeight =
//                     min({minHeight, this->heightAt(down, wateredMap)});
//             }
//             if (!pond.contains(left))
//             {
//                 minHeight =
//                     min({minHeight, this->heightAt(left, wateredMap)});
//             }
//         }
//         minPondHeights.push_back(minHeight);
//         cout << "min height: " << minHeight << endl;
//         cout << "=====" << endl;
//     }

//     vector<vector<int>> prevWateredMap{wateredMap};
//     for (int i = 0; i < minPondHeights.size(); ++i)
//     {
//         const auto &pond = ponds[i];
//         const auto &minHeight = minPondHeights[i];
//         for (const auto &p : pond)
//         {
//             wateredMap[p.second][p.first] =
//                 max({minHeight, wateredMap[p.second][p.first]});
//         }
//     }

//     bool volumeChanged = false;
//     for (int i = 0; i < ponds.size(); ++i)
//     {
//         const auto &pond = ponds[i];
//         for (const auto &p : pond)
//         {
//             volumeChanged = (prevWateredMap[p.second][p.first] !=
//                              wateredMap[p.second][p.first]);
//             if (volumeChanged)
//             {
//                 break;
//             }
//         }
//         if (volumeChanged)
//         {
//             break;
//         }
//     }

//     // this->printMap(wateredMap);
//     cout << "volume changed: " << volumeChanged << endl;

//     if (!volumeChanged)
//     {
//         break;
//     }
// }

// // cout << "WATERED ======" << endl;
// // this->printMap(wateredMap);

// int volume = 0;
// for (int y = 0; y < heightMap.size(); ++y)
// {
//     for (int x = 0; x < heightMap[y].size(); ++x)
//     {
//         volume += wateredMap[y][x] - heightMap[y][x];
//     }
// }

// cout << "volume: " << volume << endl;