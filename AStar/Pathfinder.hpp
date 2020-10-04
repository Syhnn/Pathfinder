#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include <deque>
#include <map>
#include <set>
#include <unordered_map>

#include "Grid.hpp"


// forcing empty at 0 and wall at 1 to be in sync with the Grid class
enum node_state { empty = 0, wall = 1, discovered, visited, start, finish, path };


class Pathfinder {
public:
  Pathfinder(Grid* g, std::pair<int, int> s, std::pair<int, int> f);
  bool breadthFirstSearchStep();
  std::vector<std::vector<int>> getGridState();
  void setStart(std::pair<int, int> s);
  void setFinish(std::pair<int, int> f);
  std::set<std::pair<int, int>> getVisited() { return visited; }
  std::deque<std::pair<int, int>> getDiscovered() { return discovered; }
  std::vector<std::pair<int, int>> getPath() { return path; }
  void reset() { started = false; path_found = false; }

private:
  void initBFS();

  bool started;
  bool path_found;

  Grid* graph;

  std::pair<int, int> start;
  std::pair<int, int> finish;
  std::vector<std::pair<int, int>> path;
  std::deque<std::pair<int, int>> discovered;
  //std::unordered_set<std::pair<int, int>, pair_hash> visited;
  std::set<std::pair<int, int>> visited;
  //std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> came_from;
  std::map<std::pair<int, int>, std::pair<int, int>> came_from;
};

#endif // _PATHFINDER_HPP_

