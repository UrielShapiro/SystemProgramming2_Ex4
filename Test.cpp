#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include <sys/wait.h>
#include <unistd.h>
#include <string>

using std::string;

template <typename T>
std::string formatNumbers(T value)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << value;
    return out.str();
}

TEST_CASE("Test Tree")
{

    SUBCASE("Test add_root")
    {
        Node<double> root_node = Node(1.1);
        Tree<double> tree; // Binary tree that contains doubles.
        tree.add_root(root_node);
        CHECK_EQ(tree.get_root(), &root_node);
        Node<double> root_node2 = Node(1.2);
        CHECK_THROWS(tree.add_root(root_node2));
    }

    SUBCASE("Test add_sub_node")
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

        CHECK_EQ(root_node.get_num_of_childs(), 2);
        CHECK_EQ(n1.get_num_of_childs(), 2);
        CHECK_EQ(n2.get_num_of_childs(), 1);
        CHECK_EQ(n3.get_num_of_childs(), 0);
        CHECK_EQ(n4.get_num_of_childs(), 0);
        CHECK_EQ(n5.get_num_of_childs(), 0);


        Node<int> root_node2 = Node(1);
        Tree<int, 3> tree2;
        tree2.add_root(root_node2);
        Node<int> n1_2 = Node(2);
        Node<int> n2_2 = Node(3);
        Node<int> n3_2 = Node(4);
        Node<int> n4_2 = Node(5);
        Node<int> n5_2 = Node(6);
        Node<int> n6_2 = Node(7);

        tree2.add_sub_node(root_node2, n1_2);
        tree2.add_sub_node(root_node2, n2_2);
        tree2.add_sub_node(root_node2, n3_2);
        CHECK_THROWS(tree2.add_sub_node(root_node2, n4_2)); // Too many children
        tree2.add_sub_node(n1_2, n5_2);
        tree2.add_sub_node(n1_2, n6_2);
        CHECK_THROWS(tree2.add_sub_node(n1_2, n3_2));   // Creating a cycle
    }

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

    Node<Complex<double>> root_node_complex = Node<Complex<double>>(Complex<double>{1.1, 1.1});
    Tree<Complex<double>> tree_complex; // Binary tree that contains doubles.
    tree_complex.add_root(root_node_complex);
    Node<Complex<double>> n1_complex = Node<Complex<double>>(Complex(1.2, 1.2));
    Node<Complex<double>> n2_complex = Node<Complex<double>>(Complex(1.3, 1.3));
    Node<Complex<double>> n3_complex = Node<Complex<double>>(Complex(1.4, 1.4));
    Node<Complex<double>> n4_complex = Node<Complex<double>>(Complex(1.5, 1.5));
    Node<Complex<double>> n5_complex = Node<Complex<double>>(Complex(1.6, 1.6));

    tree_complex.add_sub_node(root_node_complex, n1_complex);
    tree_complex.add_sub_node(root_node_complex, n2_complex);
    tree_complex.add_sub_node(n1_complex, n3_complex);
    tree_complex.add_sub_node(n1_complex, n4_complex);
    tree_complex.add_sub_node(n2_complex, n5_complex);

    // The tree should look like:
    /**
     *       root = 1.1 + 1.1i
     *     /       \
     *    1.2 + 1.2i      1.3 + 1.3i
     *   /  \      /
     *  1.4 + 1.4i  1.5 + 1.5i  1.6 + 1.6i
     */

    Node<string> root_node_string = Node(string("1.1"));
    Tree<string> tree_string; // Binary tree that contains doubles.
    tree_string.add_root(root_node_string);
    Node<string> n1_string = Node(string("1.2"));
    Node<string> n2_string = Node(string("1.3"));
    Node<string> n3_string = Node(string("1.4"));
    Node<string> n4_string = Node(string("1.5"));
    Node<string> n5_string = Node(string("1.6"));

    tree_string.add_sub_node(root_node_string, n1_string);
    tree_string.add_sub_node(root_node_string, n2_string);
    tree_string.add_sub_node(n1_string, n3_string);
    tree_string.add_sub_node(n1_string, n4_string);
    tree_string.add_sub_node(n2_string, n5_string);

    // The tree should look like:
    /**
     *       root = "1.1"
     *     /       \
     *    "1.2"      "1.3"
     *   /  \      /
     *  "1.4"  "1.5"  "1.6"
     */

    SUBCASE("Test Pre Order")
    {
        double pre_order[] = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        size_t pre_order_index = 0;

        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK_EQ(node.get_value(), pre_order[pre_order_index++]);
        }

        pre_order_index = 0;
        for (auto node = tree_complex.begin_pre_order(); node != tree_complex.end_pre_order(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(pre_order[pre_order_index], pre_order[pre_order_index]));
            pre_order_index++;
        }

        pre_order_index = 0;
        for (auto node = tree_string.begin_pre_order(); node != tree_string.end_pre_order(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(pre_order[pre_order_index++]));
        }
    }

    SUBCASE("Test Post Order")
    {
        double post_order[] = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
        size_t post_order_index = 0;

        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK_EQ(node.get_value(), post_order[post_order_index++]);
        }

        post_order_index = 0;
        for (auto node = tree_complex.begin_post_order(); node != tree_complex.end_post_order(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(post_order[post_order_index], post_order[post_order_index]));
            post_order_index++;
        }

        post_order_index = 0;
        for (auto node = tree_string.begin_post_order(); node != tree_string.end_post_order(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(post_order[post_order_index++]));
        }
    }

    SUBCASE("Test In Order")
    {
        double in_order[] = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
        size_t in_order_index = 0;

        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK_EQ(node.get_value(), in_order[in_order_index++]);
        }

        in_order_index = 0;
        for (auto node = tree_complex.begin_in_order(); node != tree_complex.end_in_order(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(in_order[in_order_index], in_order[in_order_index]));
            in_order_index++;
        }

        in_order_index = 0;
        for (auto node = tree_string.begin_in_order(); node != tree_string.end_in_order(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(in_order[in_order_index++]));
        }
    }

    SUBCASE("Test DFS")
    {
        double dfs[] = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        size_t dfs_index = 0;

        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), dfs[dfs_index++]);
        }

        dfs_index = 0;
        for (auto node = tree_complex.begin_dfs_scan(); node != tree_complex.end_dfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(dfs[dfs_index], dfs[dfs_index]));
            dfs_index++;
        }

        dfs_index = 0;
        for (auto node = tree_string.begin_dfs_scan(); node != tree_string.end_dfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(dfs[dfs_index++]));
        }
    }

    // SUBCASE("Test BFS")
    // {
    //     double bfs[] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    //     size_t bfs_index = 0;

    //     for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    //     {
    //         CHECK_EQ(node.get_value(), bfs[bfs_index++]);
    //     }

    //     bfs_index = 0;
    //     for (auto node = tree_complex.begin_bfs_scan(); node != tree_complex.end_bfs_scan(); ++node)
    //     {
    //         CHECK_EQ(node.get_value(), Complex(bfs[bfs_index], bfs[bfs_index]));
    //         bfs_index++;
    //     }

    //     bfs_index = 0;
    //     for (auto node = tree_string.begin_bfs_scan(); node != tree_string.end_bfs_scan(); ++node)
    //     {
    //         CHECK_EQ(node.get_value(), formatNumbers(bfs[bfs_index++]));
    //     }
    // }

    // double pre_order[] = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
    // double post_order[] = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
    // double in_order[] = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
    // size_t pre_order_index = 0;
    // size_t post_order_index = 0;
    // size_t in_order_index = 0;

    // for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    // {
    //     CHECK_EQ(node.get_value(), pre_order[pre_order_index++]);
    // }

    // for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    // {
    //     CHECK_EQ(node.get_value(), post_order[post_order_index++]);
    // }

    // for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    // {
    //     CHECK_EQ(node.get_value(), in_order[in_order_index++]);
    // }

    // wait(NULL);
};