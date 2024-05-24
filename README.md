# Graph Algorithms

Solution for Ex-2 System Programming 2

## Summary of Methods

- **Graph Constructor:** Initializes an empty grid for the graph.
  
- **loadGraph Method:** Loads a graph into the object, checking for validity.
  
- **<< Operator Override (ostream):** Prints the graph in a formatted manner using the ostream operator.
  
- **printGraph Method:** Generates a string representation of the graph.
  
- **+ Operator Override (Graph Addition):** Adds two graphs element-wise, creating a new graph.
  
- **+= Operator Override (Graph Addition with Scalar):** Adds a scalar value to all elements of the graph.
  
- **Unary + Operator Override:** Returns the graph itself.
  
- **- Operator Override (Graph Subtraction):** Subtracts one graph from another element-wise, creating a new graph.
  
- **-= Operator Override (Graph Subtraction with Scalar):** Subtracts a scalar value from all elements of the graph.
  
- **Unary - Operator Override:** Returns the negated graph.
  
- ***= Operator Override (Graph Scalar Multiplication):** Multiplies all elements of the graph by a scalar value.
  
- **/= Operator Override (Graph Scalar Division):** Divides all elements of the graph by a scalar value.
  
- **\* Operator Override (Graph Multiplication):** Multiplies two graphs, resulting in a new graph.
  
- **contains Method:** Checks if the graph contains another graph as a subgraph.
  
- **countEdges Method:** Counts the number of edges in the graph.
  
- **> Operator Override (Graph Greater Than Comparison):** Compares two graphs based on size and edge count.
  
- **>= Operator Override (Graph Greater Than or Equal Comparison):** Compares two graphs based on size and edge count.
  
- **< Operator Override (Graph Less Than Comparison):** Compares two graphs based on size and edge count.
  
- **<= Operator Override (Graph Less Than or Equal Comparison):** Compares two graphs based on size and edge count.
  
- **== Operator Override (Graph Equality Comparison):** Checks if two graphs are equal.
  
- **!= Operator Override (Graph Inequality Comparison):** Checks if two graphs are not equal.
  
- **++ Operator Override (Increment Graph):** Increments all elements of the graph by 1.
  
- **-- Operator Override (Decrement Graph):** Decrements all elements of the graph by 1.

## Usage

- **make  ->  ./demo**
- **make test  ->  ./test**
