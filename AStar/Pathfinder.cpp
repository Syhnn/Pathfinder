#include "Pathfinder.hpp"

#include <iostream>
#include <utility>


using namespace std;


Pathfinder::Pathfinder(Grid* g, pair<int, int> s, pair<int, int> f) :
  graph(g),
  start(s),
  finish(f),

  started(false),
  path_found(false)
{}


bool Pathfinder::breadthFirstSearchStep() {
  if (!started) {
    initBFS();
    started = true;
  } else if (path_found) {
    if (came_from.find(path.back()) != came_from.end()) {
      path.push_back(came_from[path.back()]);
    } else {
      return false;
    }
  } else if (!discovered.empty()) {
    pair<int, int> current = discovered.front();
    discovered.pop_front();

    if (current == finish) {
      path_found = true;
      path.push_back(finish);
    }

    for (pair<int, int> node : graph->neighbors(current)) {
      if (visited.find(node) == visited.end()) {
        if (find(discovered.begin(), discovered.end(), node) == discovered.end())
          discovered.push_back(node);
        came_from.insert(make_pair(node, current));
      }
    }

    visited.insert(current);
  }

  return true;
}

void Pathfinder::initBFS() {
  discovered.clear();
  visited.clear();
  came_from.clear();
  path.clear();

  discovered.push_back(start);
}

vector<vector<int>> Pathfinder::getGridState() {
  if (graph) {
    vector<vector<int>> grid = graph->getGridState();
    for (auto n : visited) {
      grid[n.first][n.second] = node_state::visited;
    }
    for (int i(0); i < discovered.size(); ++i) {
      grid[discovered[i].first][discovered[i].second] = node_state::discovered;
    }
    for (auto n : path) {
      grid[n.first][n.second] = node_state::path;
    }
    grid[start.first][start.second] = node_state::start;
    grid[finish.first][finish.second] = node_state::finish;
    return grid;
  } else {
    return vector<vector<int>>();
  }
}

void Pathfinder::setStart(pair<int, int> s) {
  start = s;
  started = false;
  path_found = false;
}

void Pathfinder::setFinish(pair<int, int> f) {
  finish = f;
  started = false;
  path_found = false;
}
