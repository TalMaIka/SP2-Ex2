// Tal Malka 315734616 Tal.coder@gmail.com

#include "Algorithms.hpp"

using namespace ariel;

// Method to check if the graph is connected
bool Algorithms::isConnected(Graph &graph)
{
    const vector<vector<int>> &Grid = graph.getGrid();
    size_t numVertices = Grid.size();

    // Empty graph means connected.
    if (numVertices == 0)
    {
        return true;
    }

    // Visited vertices array
    vector<bool> visited(numVertices, false);

    // BFS travers from vertex 0
    queue<int> queue;
    queue.push(0);
    visited[0] = true;
    int numVisited = 1; // Number of visited vertices
    while (queue.size() > 0)
    {
        int u = queue.front();
        queue.pop();
        for (size_t v = 0; v < numVertices; v++)
        {
            if (!visited[v] && Grid[u][v]) // If there is an edge and the vertex is not visited
            {
                visited[v] = true; // Mark as visited
                queue.push(v);
                numVisited++;
            }
        }
    }

    if (numVisited == numVertices) // All vertices are visited
    {
        
        return true;
    }
    
    return false;
}

// Method to find the shortest path between two vertices
string Algorithms::shortestPath(Graph &graph, int start, int dest)
{
    const vector<vector<int>> &Grid = graph.getGrid();
    size_t numVertices = Grid.size();
    if (numVertices == 0)
    {
        return "-1"; // Return -1 if the graph is empty.
    }

    vector<int> dist(numVertices, numeric_limits<int>::max()); // Stores distances to max value
    dist[start] = 0;

    // Perform Bellman-Ford algorithm
    for (size_t i = 0; i < numVertices - 1; i++)
    {
        for (size_t u = 0; u < numVertices; u++)
        {
            for (size_t v = 0; v < numVertices; v++)
            {
                if (Grid[u][v] != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + Grid[u][v] < dist[v])
                {
                    dist[v] = dist[u] + Grid[u][v];
                }
            }
        }
    }

    // Constructing the shortest path
    vector<int> path;
    int current = dest;
    while (current != start) // Traverse from destination to source
    {
        path.push_back(current);
        int nextNode = -1;
        int minDist = numeric_limits<int>::max();
        for (size_t v = 0; v < numVertices; v++)
        {
            if (Grid[v][current] != 0 && dist[v] != numeric_limits<int>::max() && dist[v] + Grid[v][current] == dist[current])
            {
                if (dist[v] < minDist)
                {
                    minDist = dist[v];
                    nextNode = v;
                }
            }
        }
        if (nextNode == -1)
        {
            return "-1"; // No path exists from source to destination.
        }
        current = nextNode;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    // Construct the string representing the shortest path
    string shortestPathStr;
    for (size_t i = 0; i < path.size(); i++)
    {
        shortestPathStr += to_string(path[i]);
        if (i != path.size() - 1)
        {
            shortestPathStr += "->";
        }
    }

    return shortestPathStr;
}



// Function to perform DFS and detect cycles
bool Algorithms::detectCycleDFS(Graph &graph, int start, vector<bool> &visited, int parent, stack<int> &cycleStack)
{
    const vector<vector<int>> &Grid = graph.getGrid();
    visited[start] = true;

    for (size_t i = 0; i < Grid[start].size();i++)
    { 
        if (Grid[start][i]) // If there is an edge
        {
            if (!visited[i])
            { // If the adjacent vertex is not visited, then call recursion
                if (detectCycleDFS(graph, i, visited, start, cycleStack))
                {                           
                    cycleStack.push(start); // Push the current vertex to stack
                    return true; // Cycle detected
                }
            }
            else if (i != parent)
            {                         
                cycleStack.push(i);     // Push the adjacent vertex to stack
                cycleStack.push(start); // Push the current vertex to stack
                return true;
            }
        }
    }

    return false;
}

// Function to detect cycles in the graph
string Algorithms::isContainsCycle(Graph &graph)
{
    const vector<vector<int>> &Grid = graph.getGrid();
    int V = Grid.size();
    vector<bool> visited(V, false);
    stack<int> cycleStack;
    string result;

    // Cycle detection using DFS
    for (size_t i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (detectCycleDFS(graph, i, visited, -1, cycleStack)) // If cycle detected
            { // Print the cycle
                result += "The cycle is: ";
                while (!cycleStack.empty())
                {
                    if (cycleStack.size() == 1)
                    { // Will print last element without ->
                        result += to_string(cycleStack.top());
                    }
                    else
                    {
                        result += to_string(cycleStack.top()) + "->";
                    }
                    cycleStack.pop();
                }
                return result;
            }
        }
    }
    
    return "0";
}


string Algorithms::isBipartite(Graph &graph) {
    const vector<vector<int>> &Grid = graph.getGrid();
    int n = Grid.size();
    if (n == 1) {
        // Single-vertex graph is always bipartite
        return "The graph is bipartite: A={0}";
    }
    vector<size_t> color(n, -1); // 0 and 1 represent two different colors
    queue<int> q;
    vector<int> setA, setB; // Stores vertices in the two sets

    for (size_t i = 0; i < n; i++) {
        if (color[i] != -1)
            continue; // Vertex has color assigned
        q.push(i);
        color[i] = 0; // Assign color 0 to the starting Vertex

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Add current vertex to its corresponding set
            if (color[curr] == 0)
                setA.push_back(curr);
            else
                setB.push_back(curr);

            for (size_t neighbor = 0; neighbor < n; neighbor++) {
                if (Grid[curr][neighbor] == 0)
                    continue; // No edge
                if (color[neighbor] == -1) { // Unvisited neighbor
                    color[neighbor] = 1 - color[curr]; // Assign other color
                    q.push(neighbor);
                } else if (color[neighbor] == color[curr]) { // Neighbor has same color
                    return "0"; // Graph is not bipartite
                }
            }
        }
    }
    // Print the bipartite sets
    string result = printBipartiteSets(setA, setB);
    return result;
}

string Algorithms::printBipartiteSets(const vector<int>& setA, const vector<int>& setB) {
    string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); i++) {
        result += to_string(setA[i]);
        if (i != setA.size() - 1)
            result += ", ";
    }
    result += "}, B={";
    for (size_t i = 0; i < setB.size(); i++) {
        result += to_string(setB[i]);
        if (i != setB.size() - 1)
            result += ", ";
    }
    result += "}";

    return result;
}



bool Algorithms::hasNegativeCycle(const vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> distance(n, 0); // Starting distances from 0
    // Relaxation for V-1 times
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t u = 0; u < n; u++)
        {
            for (size_t v = 0; v < n; v++)
            {
                if (graph[u][v] != 0)
                { // Edge exists
                    if (distance[v] > distance[u] + graph[u][v])
                    {
                        distance[v] = distance[u] + graph[u][v];
                    }
                }
            }
        }
    }
    // Check for negative cycle
    for (size_t u = 0; u < n; u++)
    {
        for (size_t v = 0; v < n; v++)
        {
            if (graph[u][v] != 0)
            { // Edge exists
                if (distance[v] > distance[u] + graph[u][v])
                {
                    return true; // Negative cycle detected
                }
            }
        }
    }
    return false; // No negative cycle found
}