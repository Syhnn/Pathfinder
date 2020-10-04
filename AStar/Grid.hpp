#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <set>
#include <unordered_set>
#include <utility>
#include <vector>


struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (std::pair<T1, T2> const& pair) const {
    std::size_t h1 = std::hash<T1>()(pair.first);
    std::size_t h2 = std::hash<T2>()(pair.second);
    // this is pretty bad, it needs to be replaced
    return h1 ^ h2;
  }
};


class Grid {
public:
  Grid(int w, int h);

  std::vector<std::pair<int, int>> neighbors(std::pair<int, int> pos);
  int heuristic(std::pair<int, int> posa, std::pair<int, int> posb);
  bool empty(std::pair<int, int> pos);
  void setWall(std::pair<int, int> pos, bool blocked);
  void invertWall(std::pair<int, int> pos);
  std::vector<std::vector<int>> getGridState();

private:
  int width;
  int height;
  //std::unordered_set<std::pair<int, int>, pair_hash> walls;
  std::set<std::pair<int, int>> walls;
};

#endif // _GRID_HPP_
