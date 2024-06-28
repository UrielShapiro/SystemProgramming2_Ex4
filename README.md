# Personal Details

- Name: Uriel Shapiro
- Last digits of ID: 9745
- Email: <uriel1999@gmail.com>

# Tree Visualization and Iteration Documentation

## Overview

The Tree Iteration project shows a graphical tool designed to visualize tree data structures using various traversal methods for various tree types (binary/non-binary and of different data types). It provides an intuitive and user-friendly interface for exploring the behavior and structure of trees.

## Makefile Documentation

- To compile the `Demo` file, run the following command:
  
  ```bash
  make tree
  ```

  And to the demo use:

  ```bash
  ./tree
  ```

- To compile the `Test` file, run the following command:

  ```bash
  make Test
  ```

  And to run the tests, use:

  ```bash
  ./Test
  ```

## Iterators.hpp Documentation

### Iterator Class

   The `Iterator` class is an abstract base class designed to facilitate the iteration over tree data structures. It serves as the foundation for various specific       iterator implementations.

### PreOrderIterator Class

  The `PreOrderIterator` class is a template-based iterator designed to traverse tree data structures in pre-order fashion. This iterator supports both binary and non-binary trees, providing a DFS scan for non-binary trees.
  This iterator traverse the tree using a stack, it adds the root first (because it should be printed last). Then - for each operator++ operation, Each of the current node children is pushed to the stack - from the rightmost child to the leftmost.
  Each operator++ operation also pops one node from the stack (the top node) and returns it.
  When the stack is empty - the `p_current` pointer will be set to nullptr, to declare no nodes are left to traverse.

### PostOrderIterator Class

  The `PostOrderIterator` class provides an efficient way to traverse a tree in post-order. It accepts a root node upon initialization and distinguishes between binary and non-binary trees to set up the appropriate traversal mechanisms. For binary trees, it uses a stack to manage traversal state - Adding the root, then it's right subtree and only afterwards it's left subtree to the stack. while for non-binary trees, it uses a queue. The iterator's ++ operator advances the traversal, either popping nodes from the stack for binary trees or dequeuing nodes for non-binary trees. The current node is tracked using `p_current`, and subtree addition is handled by dedicated methods for each tree type.

### InOrderIterator Class

  The `InOrderIterator` class facilitates in-order traversal of a tree. Upon initialization with a root node, it distinguishes between binary and non-binary trees and sets up traversal accordingly, for binary tree it adds the subtree of the right node to the stack, afterwards it adds the root and only then it adds the left subtree to the stack. So that when popping the stack - we will get the nodes sorted by in-order iteration.  The iterator advances through the tree using the ++ operator, popping nodes from the stack for binary trees and dequeuing nodes for non-binary trees. The current node is tracked using `p_current`, and subtree addition is handled by specific methods for each tree type.

### BFSIterator Class

  The `BFSIterator` class facilitates breadth-first traversal of a tree. Upon initialization with a root node, the constructor checks if the root is non-null and, if so, adds it to a queue for traversal. As the iterator advances using the ++ operator, it processes nodes level-by-level by dequeuing the current node and enqueuing its children, if any. The current node is tracked using `p_current`.

### DFSIterator Class

  The `DFSIterator` class enables depth-first traversal of a tree. When instantiated with a root node, the constructor verifies the root's existence and initiates the subtree addition process using a queue. Nodes are added recursively, ensuring that each node and its descendants are included. The ++ operator advances the iterator by popping the next node from the queue. The current node is tracked using `p_current`.

### MinHeap Class

  The `MinHeap` class facilitates traversal of a tree while maintaining a min-heap structure. Upon initialization with a root node, the constructor checks if the root is non-null and then recursively adds all nodes in the subtree to a vector. This vector is then transformed into a min-heap using a custom comparator. The iterator advances using the ++ operator, which pops the smallest element from the heap and sets it as the current node `p_current`.

## Tree Class

  The `Tree` class represents a k-ary tree and provides various traversal methods. Upon instantiation, the tree initializes with a specified number of children per node (default is 2) and no root. The destructor is default since nodes are not dynamically allocated.

- The `add_root` method sets the root of the tree, while ensuring that a root is not already present.
- The `add_sub_node` method adds a child node to a specified parent node, checking that the parent does not exceed the maximum number of children and that the child node is not already part of the tree to avoid cycles.

  The class offers different traversal iterators, including pre-order, post-order, in-order, breadth-first (BFS), depth-first (DFS), and min-heap scans. Each traversal type has corresponding begin and end methods to create and return iterators initialized with the root or nullptr, respectively. For min-heap traversal, the tree ensures it is a binary tree before proceeding.

   The class also provides an overload for the output stream operator (`<<`) to show the tree in an intuitive GUI.

## Node Class

  The `Node` class represents a node in a tree, holding data and a vector of child nodes. It is templated to allow for various data types. The constructor initializes the node with data and an empty list of children. The copy constructor and a constructor for Complex types are also provided.

- The `add_child` method adds a child node to the current node's list of children.
- The `get_num_of_childs` method returns the number of children.
- The `get_data` method returns the node's data,
- The `get_children` method returns the list of child nodes.
- The `is_leaf` method checks if the node has no children.

  The class includes comparison operators (<, >, ==) to compare nodes based on their data. If a non-comparable type is used, a compilation error will occur.

## Complex Class

  The `Complex` class represents a complex number with real and imaginary parts. It is templated to support various numeric types. The class ensures type safety by using a compile-time check (`static_assert`) to confirm that the provided type is numeric.

The constructor initializes the complex number with real and imaginary components.

- The `get_data` method returns a string representation of the complex number.
- The `getReal` and `getImaginary` return the real and imaginary parts, respectively.

Comparison operators (`==, !=, <, >`) are defined to compare complex numbers based on their magnitude, calculated using the Euclidean norm.

 The class also provides an overload for the output stream operator (`<<`) to print the complex number.
