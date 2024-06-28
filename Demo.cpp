/**
 * Name: Uriel Shapiro
 * ID: 9745
 */
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"

using std::cout, std::endl;

int main()
{
    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "Pre Order Traversal: " << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << "Post Order Traversal: " << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    cout << "In Order Traversal: " << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    cout << "BFS Scan: " << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout << "DFS Scan: " << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << "MinHeap Traversal: " << endl;
    for (auto node = tree.begin_min_heap_scan(); node != tree.end_min_heap_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << "For Each Scan: " << endl;
    for (auto node : tree)
    {
        cout << node->get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    // MinHeap on Binary Tree of Complex Numbers
    Node<Complex<double>> root_node_complex = Node<Complex<double>>(Complex<double>(1.1, 1.1));
    Tree<Complex<double>> tree_complex; // Binary tree that contains complex numbers.
    tree_complex.add_root(root_node_complex);
    Node<Complex<double>> n1_complex = Node<Complex<double>>(Complex<double>(1.2, 1.2));
    Node<Complex<double>> n2_complex = Node<Complex<double>>(Complex<double>(1.3, 1.3));
    Node<Complex<double>> n3_complex = Node<Complex<double>>(Complex<double>(1.4, 1.4));
    Node<Complex<double>> n4_complex = Node<Complex<double>>(Complex<double>(1.5, 1.5));
    Node<Complex<double>> n5_complex = Node<Complex<double>>(Complex<double>(1.6, 1.6));

    tree_complex.add_sub_node(root_node_complex, n1_complex);
    tree_complex.add_sub_node(root_node_complex, n2_complex);
    tree_complex.add_sub_node(n1_complex, n3_complex);
    tree_complex.add_sub_node(n1_complex, n4_complex);
    tree_complex.add_sub_node(n2_complex, n5_complex);

    cout << "MinHeap Traversal on Complex Numbers: " << endl;
    for (auto node = tree_complex.begin_min_heap_scan(); node != tree_complex.end_min_heap_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1 + 1.1i, 1.2 + 1.2i, 1.3 + 1.3i, 1.4 + 1.4i, 1.5 + 1.5i, 1.6 + 1.6i
    cout << endl;

    Node<double> root_node1 = Node(1.1);
    Node<double> n11 = Node(1.2);
    Node<double> n21 = Node(1.3);
    Node<double> n31 = Node(1.4);
    Node<double> n41 = Node(1.5);
    Node<double> n51 = Node(1.6);
    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node1);
    three_ary_tree.add_sub_node(root_node1, n11);
    three_ary_tree.add_sub_node(root_node1, n21);
    three_ary_tree.add_sub_node(root_node1, n31);
    three_ary_tree.add_sub_node(n11, n41);
    three_ary_tree.add_sub_node(n11, n51);

    cout << "Trinary In Order Traversal: " << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.5, 1.6, 1.3, 1.4
    cout << endl;

    cout << "Trinary Post Order Traversal: " << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.5, 1.6, 1.3, 1.4
    cout << endl;

    cout << "Trinary Pre Order Traversal: " << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.5, 1.6, 1.3, 1.4
    cout << endl;

    cout << "Trinary BFS Scan: " << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout << three_ary_tree << endl;
    return 0;
}
