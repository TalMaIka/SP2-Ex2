// Tal Malka 315734616 Tal.coder@gmail.com

#include "Graph.hpp"

using namespace ariel;
namespace ariel
{
    Graph::Graph(){
        Grid = vector<vector<int>>();
        int size = Grid.size();
    }
    // Load graph method
    void Graph::loadGraph(vector<vector<int>> &graph)
    {
        // Checking empty graph.
        int numVertices = graph.size();
        if (numVertices == 0)
            throw invalid_argument("Grid is empty");
        // Checking if the graph is a square (rows = coloumns).
        for (size_t i = 0; i < numVertices; i++)
        {
            if (graph[i].size() != numVertices)
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        // Assigning the valid graph to our's.
        Grid = graph;
    }

   // Overrideing the << operator to print the graph
    ostream& operator<<(ostream& os, const Graph& graph) {
        int numVertices = graph.Grid.size();
        for (size_t i = 0; i < numVertices; i++) {
            os << "[ ";
            for (size_t j = 0; j < numVertices; j++) {
                os << graph.Grid[i][j];
                if (j < numVertices - 1)
                    os << ", ";
            }
            if (i < numVertices - 1)
                os << " ], ";
            else{
                os << " ]";
            }
            
        }
        return os;
    }

    // Overrideing the << operator to print the graph
    string Graph::printGraph() {
        string result;
        int numVertices = Grid.size();
        for (size_t i = 0; i < numVertices; ++i) {
            result.append("[");
            for (size_t j = 0; j < Grid[i].size(); ++j) {
                result.append(to_string(Grid[i][j]));
                if (j < Grid[i].size() - 1) {
                    result.append(", ");
                }
            }
            result.append("]");
            if (i < numVertices - 1) {
                result.append("\n");
            }
        }
        return result;
    }

Graph operator+(Graph& graph, Graph& other) {
    //Double check if the graphs are the same size. (Even if already made in loadGraph)
    int graphSize = graph.Grid.size();
    int otherSize = other.Grid.size();
    if (graphSize != otherSize || graph.Grid[0].size() != other.Grid[0].size()) {
        throw invalid_argument("Diffrent dimension Graphs cannot be added together.");
    }

    Graph result;
    vector<std::vector<int>> resultGrid(graph.Grid.size(), vector<int>(graph.Grid[0].size(), 0));

    for (size_t i = 0; i < graphSize; i++) {
        for (size_t j = 0; j < graph.Grid[i].size(); j++) {
            resultGrid[i][j] = graph.Grid[i][j] + other.Grid[i][j];
        }
    }

    result.loadGraph(resultGrid);
    return result;
}

Graph operator+=(Graph& graph, int number) {
    int graphSize = graph.Grid.size();
    for (size_t i = 0; i < graphSize; ++i) {
        for (size_t j = 0; j < graph.Grid[i].size(); ++j) {
            graph.Grid[i][j] += number;
        }
    }
    return graph;
}
//Unary plus operator
Graph operator+(Graph& graph) {
    return graph;
}

Graph operator-(Graph& graph, Graph& other) {
    //Double check if the graphs are the same size. (Even if already made in loadGraph)
    int graphSize = graph.Grid.size();
    int otherSize = other.Grid.size();
    if (graphSize != otherSize || graph.Grid[0].size() != other.Grid[0].size()) {
        throw invalid_argument("Diffrent dimension Graphs cannot be added together.");
    }

    Graph result;
    vector<std::vector<int>> resultGrid(graph.Grid.size(), vector<int>(graph.Grid[0].size(), 0));

    for (size_t i = 0; i < graphSize; i++) {
        for (size_t j = 0; j < graph.Grid[i].size(); j++) {
            resultGrid[i][j] = graph.Grid[i][j] - other.Grid[i][j];
        }
    }

    result.loadGraph(resultGrid);
    return result;
}

Graph operator-=(Graph& graph, int number) {
    int graphSize = graph.Grid.size();
    for (size_t i = 0; i < graphSize; ++i) {
        for (size_t j = 0; j < graph.Grid[i].size(); ++j) {
            graph.Grid[i][j] -= number;
        }
    }
    return graph;
}

Graph operator-(Graph& graph) {
    return graph;
}

Graph operator*=(Graph& graph, int number) {
    int graphSize = graph.Grid.size();
    for (size_t i = 0; i < graphSize; ++i) {
        for (size_t j = 0; j < graph.Grid[i].size(); ++j) {
            graph.Grid[i][j] *= number;
        }
    }
    return graph;
}

Graph operator/=(Graph& graph, int number) {
    if(number == 0){
        throw invalid_argument("Cannot divide by zero.");
    }
    int graphSize = graph.Grid.size();
    for (size_t i = 0; i < graphSize; ++i) {
        for (size_t j = 0; j < graph.Grid[i].size(); ++j) {
            graph.Grid[i][j] /= number;
        }
    }
    return graph;
}

Graph operator*(Graph& graph, Graph& other) {
    if (graph.Grid.size() == 0 || other.Grid.size() == 0) {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    int graphSize = graph.Grid.size();
    int otherSize = other.Grid.size();
    if (graphSize != otherSize || graph.Grid[0].size() != other.Grid[0].size()) {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    Graph result;
    std::vector<std::vector<int>> resultGrid(graphSize, std::vector<int>(other.Grid[0].size(), 0));

    for (size_t i = 0; i < graphSize; i++) {
        for (size_t j = 0; j < other.Grid[0].size(); j++) {
            for (size_t k = 0; k < graph.Grid[i].size(); k++) {
                resultGrid[i][j] += graph.Grid[i][k] * other.Grid[k][j];
            }
        }
    }

    result.loadGraph(resultGrid);
    return result;
}

bool Graph::contains(Graph& other) {
        int graphSize = Grid.size();
        int otherSize = other.Grid.size();
        // If the other graph is larger than this graph, return false
        if (graphSize < otherSize)
            return false;

        // Iterate over each element in the other adjacency matrix
        for (size_t i = 0; i < otherSize; ++i) {
            for (size_t j = 0; j < other.Grid[i].size(); ++j) {
                // If the corresponding element in this adjacency matrix is not equal to the other, return false
                if (Grid[i][j] != other.Grid[i][j])
                    return false;
            }
        }

        return true;
    }

int Graph::countEdges() {
    int graphSize = Grid.size();
    int numEdges = 0;
    for (size_t i = 0; i < graphSize; i++) {
        for (size_t j = 0; j < graphSize; j++) {
            if (Grid[i][j] != 0)
                numEdges++;
        }
    }
    return numEdges;
}

bool operator>(Graph& graph, Graph& other) {
    if (graph.contains(other)) {
        return true; 
    } else if (other.contains(graph)) {
        return false; 
    } else {
        int numEdgesGraph = graph.countEdges();
        int numEdgesOther = other.countEdges();

        if (numEdgesGraph != numEdgesOther) {
            return numEdgesOther > numEdgesGraph; // Return bool value
        } else {
            return other.Grid.size() > graph.Grid.size();
        }
    }
}


bool operator>=(Graph& graph, Graph& other) {
    return graph > other || graph == other;
}

bool operator<(Graph& graph, Graph& other) {
    if (graph.contains(other)) {
        return true; 
    } else if (other.contains(graph)) {
        return false; 
    } else {
        int numEdgesGraph = graph.countEdges();
        int numEdgesOther = other.countEdges();

        if (numEdgesGraph != numEdgesOther) {
            return numEdgesOther < numEdgesGraph; // Return bool value
        } else {
            return other.Grid.size() < graph.Grid.size();
        }
    }
}

bool operator<=(Graph& graph, Graph& other) {
    return graph < other || graph == other;
}

bool operator==(Graph& graph, Graph& other) {
    int graphSize = graph.Grid.size();
    int otherSize = other.Grid.size();
    
     if (graphSize != otherSize)
            return false;

        // Check if the edges and their weights are the same
        for (size_t i = 0; i < graphSize; ++i) {
            for (size_t j = 0; j < graph.Grid[i].size(); ++j) {
                if (graph.Grid[i][j] != other.Grid[i][j])
                    return false;
            }
        }

        return true;
}

bool operator!=(Graph& graph, Graph& other) {
    return !(graph == other);
}

void operator++(Graph& graph) {
    for (size_t i = 0; i < graph.Grid.size(); i++) {
        for (size_t j = 0; j < graph.Grid[i].size(); j++) {
            graph.Grid[i][j]++;     
        }
    }
}

void operator--(Graph& graph) {
    for (size_t i = 0; i < graph.Grid.size(); i++) {
        for (size_t j = 0; j < graph.Grid[i].size(); j++) {
            graph.Grid[i][j]--;     
        }
    }
}
};
