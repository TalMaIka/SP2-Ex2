// Tal Malka 315734616 Tal.coder@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <stack>
#include "Graph.hpp"

using namespace std;

namespace ariel
{

    class Algorithms
    {
    public:
        static bool isConnected(Graph &g);

        static string shortestPath(Graph &graph, int start, int dest);

        static string isContainsCycle(Graph &graph);
        
        static bool detectCycleDFS(Graph &graph, int start, vector<bool> &visited, int parent, stack<int> &cycleStack);

        static int negativeCycle(Graph g);

        static string isBipartite(Graph &graph) ;

        static string printBipartiteSets(const vector<int>& setA, const vector<int>& setB);
        
        static bool hasNegativeCycle(const vector<vector<int>> &graph);
    };
}
#endif