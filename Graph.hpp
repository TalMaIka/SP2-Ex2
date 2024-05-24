// Tal Malka 315734616 Tal.coder@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <stack>
#include <sstream>

using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int> > Grid; // Adj Matrix

    public:
        Graph();
        void loadGraph(vector<vector<int> > &graph);
        string printGraph();

        vector<vector<int>>& getGrid(){
        return Grid;
        }
        friend ostream& operator<<(ostream& os, const Graph& graph);

        friend Graph operator+(Graph& graph, Graph& other); // Add two graphs together.
        friend Graph operator+=(Graph& graph, int number); // Add a number to all the elements in the graph.
        friend Graph operator+(Graph& graph); // Return the graph as is. (Unary)

        friend Graph operator-(Graph& graph, Graph& other); // Subtract two graphs together.
        friend Graph operator-=(Graph& graph, int number); // Subtract a number from all elements in the graph.
        friend Graph operator-(Graph& graph); // Return the graph as is. (Unary)

        friend Graph operator*=(Graph& graph,int number); // Multiply the graph by a number.
        friend Graph operator/=(Graph& graph, int number); // Divide the graph by a number. 
        friend Graph operator*(Graph& graph, Graph& other); // Multiply two graphs together.

        bool contains(Graph& other);
        int countEdges();
        friend bool operator>(Graph& graph, Graph& other); // Return the graph with the bigger sum of elements.
        friend bool operator>=(Graph& graph, Graph& other); // Return the graph with the bigger or equal sum of elements.
        friend bool operator<(Graph& graph, Graph& other); // Return the graph with the smaller sum of elements.
        friend bool operator<=(Graph& graph, Graph& other); // Return the graph with the smaller or equal sum of elements.
        friend bool operator==(Graph& graph, Graph& other);

        friend void operator++(Graph& graph); // Increment all the elements in the graph by 1.
        friend void operator--(Graph& graph); // Decrements all the elements in the graph by 1.

        friend bool operator!=(Graph& graph, Graph& other);
    };
}
#endif
