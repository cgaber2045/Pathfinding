/*
 * Name: Chris Gaber
 * Date Submitted: 4/24/19
 * Assignment Name: Pathfinding
 */

#pragma once

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "float.h"

using namespace std;

class node {
    public:
      int x;
      int y;
      double priority; // Total distance + heuristic.
};
node start; // starting node
node finish; // destination node

// Walk path function
template <size_t row, size_t cols>
vector<char> walkPath(node (&path)[row][cols]);

// A* algorithm
template <size_t row, size_t cols>
vector<char> aStar(char (&maze)[row][cols], double (&priorityMap)[row][cols],
                   node (&parentPath)[row][cols]);

// Main function
template <size_t row, size_t cols>
vector<char> pathfinder(char (&maze)[row][cols]);

// Heuristics
double getManhattan(node s, node d) {return abs(s.x-d.x) + abs(s.y-d.y);}
double getEuclidean(node s, node d) {return sqrt(pow(s.x-d.x,2) + pow(s.y-d.y,2));}
double djiksta(){return 0;}

// Compare nodes
bool operator<(const node& a, const node& b){return (a.priority > b.priority);}
bool operator==(const node& a, const node& b){return (a.x == b.x && a.y == b.y);}

template <size_t row, size_t cols>
vector<char> pathfinder(char (&maze)[row][cols]) {
    double priorityMap[row][cols];
    node parentPath[row][cols];

    // read through the map and find the start and end
    for (int x = 0; x < row; x++) {
      for (int y = 0; y < cols; y++) {
          if (maze[x][y] == 's') start = {x, y, 0}; // sets the start with priority
          if (maze[x][y] == 'f') finish = {x, y, DBL_MAX}; // sets the finish with priority
          priorityMap[x][y] = DBL_MAX; //Initialized all priorities to max
          parentPath[x][y] = {-1, -1}; //Sets all parents out of bounds
      }
    }

    // Sets priority (distance) to the source as 0
    // Sets parent of source as arbitrary -9, -9.
    parentPath[start.x][start.y] = {-9, -9};
    priorityMap[start.x][start.y] = 0;

    return aStar(maze, priorityMap, parentPath);
}

//Calculates the minimum distance from the <sourceNode>
//to all other nodes and prints
template <size_t row, size_t cols>
vector<char> aStar(char (&maze)[row][cols], double (&priorityMap)[row][cols],
                   node (&parentPath)[row][cols]) {

  priority_queue<node> priorityQ; // Priority queue for finding cheapest path.
  priorityQ.push(start); // Adds start node to queue.

  // find shortest distance to finish node
  while(!priorityQ.empty()) {
    // gets the first item in queue
    node current = priorityQ.top();

    // end search when we get to finish
    // if a path is found, walk the path backwards are return it
    if (current == finish) return walkPath(parentPath);

    // removes first item in queue
    priorityQ.pop();

    // finds the 4 neighbors of the current node (U, D, L, R)
    // makes sure they are in bounds and not a wall.
    // if its a bomb, add 20 to the priority.
    // if its gold subtract 4 from priority.
    node neighbors[4] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}};
    int neighPri[4] = {5,5,5,5};

    if (current.y > 0 && maze[current.x][current.y-1] != 'w') {
          neighbors[0] = current;
          neighbors[0].y--;
          if (maze[current.x][current.y-1] == 'b') neighPri[0] = 25;
          else if (maze[current.x][current.y-1] == 'g') neighPri[0] = 1;
    }
    if (current.x > 0 && maze[current.x-1][current.y] != 'w') {
        neighbors[1] = current;
        neighbors[1].x--;
        if (maze[current.x-1][current.y] == 'b') neighPri[1] = 25;
        else if (maze[current.x-1][current.y] == 'g') neighPri[1] = 1;
    }
    if (current.x < row && maze[current.x+1][current.y] != 'w') {
        neighbors[2] = current;
        neighbors[2].x++;
        if (maze[current.x+1][current.y] == 'b') neighPri[2] = 25;
        else if (maze[current.x+1][current.y] == 'g') neighPri[2] = 1;
    }
    if (current.y < cols && maze[current.x][current.y+1] != 'w') {
        neighbors[3] = current;
        neighbors[3].y++;
        if (maze[current.x][current.y+1] == 'b') neighPri[3] = 25;
        else if (maze[current.x][current.y+1] == 'g') neighPri[3] = 1;
    }

    // for each of the neighbors, update priority and add to matrix.
    // optimize gold and bomb system
    for (int i = 0; i < 4; i++) {
      // makes sure neighbor exists
      if (neighbors[i].x > -1 && neighbors[i].y > -1) {

        // current distance + the neighbor priority.
        double currPriority = priorityMap[current.x][current.y] + neighPri[i];

        // if the current Priority is less than what we have stored,
        // update node priority (Priority + heuristic) and push to the queue.
        if (currPriority < priorityMap[neighbors[i].x][neighbors[i].y]) {
          // Using manhattan distance as heuristic, since we only move
          // in 4 directions.
          neighbors[i].priority = currPriority + getManhattan(neighbors[i], finish);
          // push node to queue
          priorityQ.push(neighbors[i]);
          // update Priority to lower value
          priorityMap[neighbors[i].x][neighbors[i].y] = currPriority;
          // update parent
          parentPath[neighbors[i].x][neighbors[i].y] = current;
        }
      }
    }
  }

  // return an empty vector. (path not found)
  return {};
}

// Walks the path from A* backwards to find the directions.
template <size_t row, size_t cols>
vector<char> walkPath(node (&path)[row][cols]) {
  // vector to be returned
  vector<char> v;

  // start the walker at the end of the path
  node walker = finish;

  // while walker hasn't reached the beginning, keep going
  while (walker.x != -9) {
    // next point in the parent path.
    node nextPoint = path[walker.x][walker.y];

    // adds the appropriate character to the vector.
    if (walker.x + 1 == nextPoint.x) v.push_back('U');
    else if (walker.x - 1 == nextPoint.x) v.push_back('D');
    else if (walker.y + 1 == nextPoint.y) v.push_back('L');
    else if (walker.y - 1 == nextPoint.y) v.push_back('R');

    // walk to next point.
    walker = nextPoint;
  }

  // returns the reversed vector.
  reverse(v.begin(), v.end());
  return v;
}
