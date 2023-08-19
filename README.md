# Pathfinding
This project is an implementation of the pathfinding algorithms BFS, DFS, Dijkstra, and A*, using C++ and SFML. The project enables users to select their desired algorithm, mark start and end nodes, and place obstacles on the map. Additionally, it includes a basic and simple animation that showcases how these algorithms could be employed for NPC movement in video games.

<img src="https://github.com/21zasker/Pathfinding/blob/main/Screenshots/mini-dungeon.gif" width="35%" alt="Gif of NPC pathfinder">

<img src="https://github.com/21zasker/Pathfinding/blob/main/Screenshots/pathfinder.gif" width="35%" alt="Gif of the working program">

---

# Breadth-First Search (BFS) Algorithm

The **Breadth-First Search (BFS)** algorithm is a widely used graph traversal technique that explores a graph or grid level by level, visiting all nodes at a given depth before moving on to nodes at the next level. BFS is particularly useful for searching paths in unweighted graphs or grids and finding the shortest path between two nodes.

## Queues

A **queue** is a data structure that follows the First-In-First-Out (FIFO) principle. Similar to a real-world queue, the first element added to the queue is the first one to be removed. This makes queues suitable for applications where the order of processing or visiting elements matters. In BFS, a queue is used to store nodes that need to be explored.

## Applying BFS in the Code

Here's how the algorithm is applied in the code:

1. A queue (`q`) is initialized with the starting node's position.
  
2. The algorithm enters a loop that continues until the queue is empty:
  
    a. The front node is dequeued from the queue, representing the current position being explored.
  
    b. The adjacent positions to the current position are obtained using the `getAdjacentNodes` function.
  
    c. For each adjacent position:
  
      i. If the position corresponds to the "End" node, the algorithm stores the parent node's coordinates and uses the `obtainPath` function to extract the path from the parent nodes and exits the loop.
  
      ii. If the position is valid (not a wall and not visited), it is enqueued, and the parent coordinates are stored in the corresponding node. The node's type is changed to "Visited" to prevent revisiting.
  
3. The path is obtained using the `obtainPath` function, which traces back from the "End" node to the "Start" node using the stored parent coordinates. The path positions are stored in `pathPositions`.

---

# Depth-First Search (DFS) Algorithm

The **Depth-First Search (DFS)** algorithm is a graph traversal technique that explores as far as possible along a branch before backtracking. DFS can be thought of as exploring vertically downward into the depth of a graph or grid. It is often used to search paths in graphs, detect cycles, and explore possible configurations.

## Stacks

A **stack** is a linear data structure that follows the Last-In-First-Out (LIFO) principle. The last element added to the stack is the first one to be removed, similar to a stack of items. Stacks are suitable for applications where the order of processing or visiting elements matters, such as depth-first exploration.

## Applying DFS in the Code

Here's how the algorithm is applied in the code:

1. A stack (`s`) is initialized with the starting node's position.
  
2. The algorithm enters a loop that continues until the stack is empty:
  
    a. The top node is popped from the stack, representing the current position being explored.
  
    b. The adjacent positions to the current position are obtained using the `getAdjacentNodes` function.
  
    c. For each adjacent position:
  
      i. If the position corresponds to the "End" node, the algorithm stores the parent node's coordinates and uses the `obtainPath` function to extract the path from the parent nodes and exits the loop.
  
      ii. If the position is valid (the node is not a wall and is not visited), it is pushed onto the stack, and the parent coordinates are stored in the corresponding node. The node's type is changed to "Visited" to prevent revisiting.
  
3. The path is obtained using the `obtainPath` function, which traces back from the "End" node to the "Start" node using the stored parent coordinates. The path positions are stored in `pathPositions`.
  
---

# Dijkstra's Algorithm

**Dijkstra's algorithm** is a widely used algorithm for finding the shortest path between nodes in a graph, with non-negative edge weights. It guarantees the shortest path from a single source node to all other nodes.

## Priority Queues

A **priority queue** is a data structure that maintains a collection of elements with priorities. Elements are removed from the queue based on their priority. Priority queues are particularly useful in algorithms like Dijkstra's, where the element with the smallest priority needs to be accessed efficiently.

## Applying Dijkstra in the Code

Here's how the algorithm is applied in the code:

1. A priority queue (`pq`) is initialized with pairs of distances and positions. The smallest distances are prioritized.
  
2. The algorithm enters a loop that continues until the priority queue is empty:
  
    a. The node is dequeued from the priority queue, representing the current position being explored.
  
    b. If the distance to the current position has already been updated with a shorter distance, the node is skipped.
  
    c. For each adjacent position of the current node:
  
      i. If the position corresponds to the "End" node, the algorithm stores the parent node's coordinates and uses the `obtainPath` function to extract the path from the parent nodes and exits the loop.
  
      ii. If the new distance is shorter than the previously recorded distance and the node is not a wall, the new distance is recorded, and the node is marked as visited. It's then pushed into the priority queue for further exploration.
  
3. The path is obtained using the `obtainPath` function, which traces back from the "End" node to the "Start" node using the stored parent coordinates. The path positions are stored in `pathPositions`.
  

---

# A* Algorithm

**A* algorithm** is a widely used pathfinding algorithm that finds the shortest path between two nodes in a graph while considering the cost associated with moving from one node to another. A* algorithm is particularly efficient and effective due to its use of both actual cost and heuristic estimates to guide the search process.

### G Score (Actual Cost):

The **G score** represents the actual cost of reaching a specific node from the starting node. It accumulates the cost of moving along the path from the start node to the current node.

### H Score (Heuristic Estimate):

The **H score** is the heuristic estimate of the cost to reach the goal from the current node. It provides an approximate cost based on a heuristic function.

### F Score (Total Estimated Cost):

The **F score** represents the total estimated cost of the path through the current node to the goal node. It's the sum of the G score and the H score: `f(n) = g(n) + h(n)`.

## Applying A* Algorithm in the Code

Here's how the algorithm is applied in the code:

1. A priority queue (`openSet`) is initialized with pairs of F scores and positions. The smallest F scores are prioritized.
  
2. The algorithm enters a loop that continues until the priority queue is empty:
  
    a. The node with the smallest F score is dequeued from the priority queue, representing the current position being explored.
  
    b. If the current node is the "End" node, the algorithm uses the `obtainPath` function to extract the path from parent nodes and exits the loop.
  
    c. The algorithm updates the type of the current node if it's not the start node, marking it as visited.
  
    d. For each adjacent node position, the algorithm calculates tentative G and F scores. If the tentative G score is better than the current G score, the node is added to the `openSet` with updated scores.
  
3. The path is obtained using the `obtainPath` function, which traces back from the "End" node to the "Start" node using the stored parent coordinates. The path positions are stored in `pathPositions`.
