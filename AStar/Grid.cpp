#include "Grid.hpp"

#include <iostream>


using namespace std;


Grid::Grid(int w = 50, int h = 40) :
  width(w),
  height(h)
{}


 vector<pair<int, int>> Grid::neighbors(pair<int, int> pos) {
  vector<pair<int, int>> result;
  int x = pos.first;
  int y = pos.second;

  if (x + 1 < width && empty(make_pair(x + 1, y))) {
    result.push_back(make_pair(x + 1, y));
  }
  if (x - 1 >= 0 && empty( make_pair(x - 1, y))) {
    result.push_back(make_pair(x - 1, y));
  }
  if (y + 1 < height && empty(make_pair(x, y + 1))) {
    result.push_back(make_pair(x, y + 1));
  }
  if (y - 1 >= 0 && empty(make_pair(x, y - 1))) {
    result.push_back(make_pair(x, y - 1));
  }

  return result;
}

bool Grid::empty(pair<int, int> pos) {
  return walls.find(pos) == walls.end();
}

int Grid::heuristic(pair<int, int> posa, pair<int, int> posb) {
  return  abs(posa.first - posb.first) +  abs(posa.second - posb.second);
}

void Grid::setWall(pair<int, int> pos, bool blocked) {
  if (blocked) {
    if (walls.find(pos) == walls.end()) {
      walls.insert(pos);
    }
  } else {
    if (walls.find(pos) == walls.end()) {
      walls.erase(pos);
    }
  }
}

void Grid::invertWall(pair<int, int> pos) {
  if (pos.first < 0 || pos.first >= width || pos.second < 0 || pos.second >= height) {
    cout << "wall coordinates out of bounds" << endl;
    return;
  }
  if (walls.find(pos) == walls.end()) {
    walls.insert(pos);
  } else {
    walls.erase(pos);
  }
}

vector<vector<int>> Grid::getGridState() {
  vector<vector<int>> grid(width, vector<int>(height, 0));
  for (auto wall : walls) {
    if (wall.first >= 0 &&
      wall.first < width &&
      wall.second >= 0 &&
      wall.second < height) {
      grid[wall.first][wall.second] = 1;
    }
  }

  return grid;
}

unordered_set<pair<int, int>, pair_hash> Grid::getWalls() {
  return walls;
}
