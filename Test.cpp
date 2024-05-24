// Tal Malka 315734616 Tal.coder@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};

    // Test if the resulting graph matches the expected graph
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    ++g3;
    CHECK(g3.printGraph() == "[1, 3, 2]\n[3, 1, 4]\n[2, 4, 1]");
    --g3;
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    // Additional test: adding a graph to itself
    ariel::Graph g4 = g2 + g2;
    CHECK(g4.printGraph() == "[0, 2, 2]\n[2, 0, 4]\n[2, 4, 0]");
    --g4;++g4;
    CHECK(g4.printGraph() == "[0, 2, 2]\n[2, 0, 4]\n[2, 4, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};

    // Test if the resulting graph matches the expected graph
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");

    // Additional test: multiplying a graph by the identity matrix
    ariel::Graph g5 = g1 * g1;
    CHECK(g5.printGraph() == "[1, 0, 1]\n[0, 2, 0]\n[1, 0, 1]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);

    // Test if exception is thrown when trying to multiply graphs of incompatible dimensions
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Test if exception is thrown when trying to add graphs of different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Graph with all zeros")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);

    // Test if multiplying a graph with all zeros by itself gives a graph with all zeros
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    g+=1;
    result = result * g;
    CHECK(result.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Graph with all ones")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g.loadGraph(graph);

    // Test if adding a graph with all ones to itself gives a graph with values doubled
    ariel::Graph result = g + g;
    CHECK(result.printGraph() == "[2, 2, 2]\n[2, 2, 2]\n[2, 2, 2]");
    +result;
    CHECK(result.printGraph() == "[2, 2, 2]\n[2, 2, 2]\n[2, 2, 2]");
    result*=2;
    CHECK(result.printGraph() == "[4, 4, 4]\n[4, 4, 4]\n[4, 4, 4]");
    result/=2;
    CHECK(result.printGraph() == "[2, 2, 2]\n[2, 2, 2]\n[2, 2, 2]");
}

TEST_CASE("Graph with diagonal ones")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph);

    // Test if multiplying a graph with diagonal ones by itself gives the square of the graph
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[1, 0, 0]\n[0, 1, 0]\n[0, 0, 1]");
}

TEST_CASE("Empty graph")
{
    ariel::Graph g;

    // Test if multiplying an empty graph by another graph gives an empty graph
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[]");
}

TEST_CASE("Single node graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {1}};
    g.loadGraph(graph);

    // Test if multiplying a single node graph by itself gives the same single node graph
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[1]");
}

TEST_CASE("Graph with negative values")
{
    ariel::Graph g;
   vector<vector<int>> graph = {
        {-1, -2},
        {-3, -4}};
    g.loadGraph(graph);

    // Test if multiplying a graph with negative values by itself gives the correct result
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[7, 10]\n[15, 22]");
}

TEST_CASE("Graph with all identical values")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {2, 2},
        {2, 2}};
    g.loadGraph(graph);

    // Test if multiplying a graph with all identical values by itself gives the correct result
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[8, 8]\n[8, 8]");
}

TEST_CASE("Graph with random values")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {3, 5},
        {7, 2}};
    g.loadGraph(graph);

    // Test if multiplying a graph with random values by itself gives the correct result
    ariel::Graph result = g * g;
    CHECK(result.printGraph() == "[44, 25]\n[35, 39]");
}

TEST_CASE("Graph addition with zero matrix")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph);

    ariel::Graph g2;

    // Test if adding a graph with all zeros to another graph gives the correct result
    ariel::Graph result = g1 + g2;
    CHECK(result.printGraph() == "[1, 2]\n[3, 4]");
}

TEST_CASE("Graph multiplication with zero matrix")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph);

    ariel::Graph g2;

    // Test if multiplying a graph with all zeros by another graph gives the correct result
    ariel::Graph result = g1 * g2;
    CHECK(result.printGraph() == "[0, 0]\n[0, 0]");
}

TEST_CASE("Graph addition with random values")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {2, 3},
        {4, 5}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 1},
        {1, 1}};
    g2.loadGraph(graph2);

    // Test if adding two graphs with random values gives the correct result
    ariel::Graph result = g1 + g2;
    CHECK(result.printGraph() == "[3, 4]\n[5, 6]");
}

TEST_CASE("Graph multiplication with random values")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {2, 3},
        {4, 5}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 1},
        {1, 1}};
    g2.loadGraph(graph2);

    // Test if multiplying two graphs with random values gives the correct result
    ariel::Graph result = g1 * g2;
    CHECK(result.printGraph() == "[5, 5]\n[9, 9]");
}