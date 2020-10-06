#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include <deque>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "Grid.hpp"


// forcing empty at 0 and wall at 1 to be in sync with the Grid class
enum node_state { empty = 0, wall = 1, discovered, visited, start, finish, path };


class Pathfinder {
public:
  Pathfinder(Grid* g, std::pair<int, int> s, std::pair<int, int> f);

  bool breadthFirstSearchStep();
  void resetBFS();

  bool aStarStep();
  void resetAStar();

  std::vector<std::vector<int>> getGridState();

  void setStart(std::pair<int, int> s);
  void setFinish(std::pair<int, int> f);

  std::unordered_set<std::pair<int, int>, pair_hash> getVisited() { return visited; }
  std::deque<std::pair<int, int>> getDiscovered() { return discovered; }
  std::vector<std::pair<int, int>> getPath() { return path; }
  std::unordered_map<std::pair<int, int>, int, pair_hash> getCost() { return cost; }
  std::unordered_map<std::pair<int, int>, int, pair_hash> getFrontier() { return frontier; }

private:
  void initBFS();
  void nextBFSStep();

  void initAStar();
  void nextAStarStep();

  bool reconstructPath();

  bool started;
  bool path_found;

  Grid* graph;

  std::pair<int, int> start;
  std::pair<int, int> finish;
  std::vector<std::pair<int, int>> path;
  std::deque<std::pair<int, int>> discovered;
  std::unordered_map<std::pair<int, int>, int, pair_hash> frontier;
  std::unordered_map<std::pair<int, int>, int, pair_hash> cost;
  std::unordered_set<std::pair<int, int>, pair_hash> visited;
  std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> came_from;
};

#endif // _PATHFINDER_HPP_

