/**
 * Name: Uriel Shapiro
 * ID: 9745
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include <iomanip> // For std::fixed, std::setprecision
#include <string>

using std::string;

#define PRECISION 1

/**
 * @brief: This function sets the precision of (but not only) doubles and floats to PRECISION integers after the decimal dot.
 */
template <typename T>
string formatNumbers(T value)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(PRECISION) << value;
    return out.str();
}

TEST_CASE("Test Tree")
{
    SUBCASE("Test Constructor")
    {
        Tree<int> tree; // Binary tree that contains doubles.
        CHECK_EQ(tree.get_root(), nullptr);
    }

    SUBCASE("Test add_root - Valid operation")
    {
        Node<double> root_node = Node(1.1);
        Tree<double> tree; // Binary tree that contains doubles.
        tree.add_root(root_node);
        CHECK_EQ(tree.get_root(), &root_node);
    }

    SUBCASE("Test add_root - Adding a root to a tree that already has a root")
    {
        Node<int> root_node = Node(1);
        Tree<int, 3> tree;
        tree.add_root(root_node);
        Node<int> root_node2 = Node(2);
        CHECK_THROWS(tree.add_root(root_node2));
    }

    SUBCASE("Test add_sub_node - Valid operation")
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
    }

    SUBCASE("Test add_sub_node - Too many children")
    {
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
    }

    SUBCASE("Test add_sub_node - Creating a Cycle")
    {
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
        tree2.add_sub_node(n1_2, n5_2);
        tree2.add_sub_node(n1_2, n6_2);
        CHECK_THROWS(tree2.add_sub_node(n1_2, n3_2)); // Creating a cycle
    }

    SUBCASE("Test Empty Tree")
    {
        Tree<int> tree;
        CHECK_EQ(tree.get_root(), nullptr);
    }
}

TEST_CASE("Test Iterators On Binary trees")
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

    Tree<int> empty_tree;

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

        CHECK_EQ(empty_tree.begin_pre_order(), empty_tree.end_pre_order());
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

        CHECK_EQ(empty_tree.begin_post_order(), empty_tree.end_post_order());
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

        CHECK_EQ(empty_tree.begin_in_order(), empty_tree.end_in_order());
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

        CHECK_EQ(empty_tree.begin_dfs_scan(), empty_tree.end_dfs_scan());
    }

    SUBCASE("Test BFS")
    {
        double bfs[] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        size_t bfs_index = 0;

        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), bfs[bfs_index++]);
        }

        bfs_index = 0;
        for (auto node = tree_complex.begin_bfs_scan(); node != tree_complex.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(bfs[bfs_index], bfs[bfs_index]));
            bfs_index++;
        }

        bfs_index = 0;
        for (auto node = tree_string.begin_bfs_scan(); node != tree_string.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(bfs[bfs_index++]));
        }

        CHECK_EQ(empty_tree.begin_bfs_scan(), empty_tree.end_bfs_scan());
    }

    SUBCASE("Test MinHeap")
    {
        double min_heap[] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        size_t min_heap_index = 0;

        for (auto node = tree.begin_min_heap_scan(); node != tree.end_min_heap_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), min_heap[min_heap_index++]);
        }

        min_heap_index = 0;
        for (auto node = tree_complex.begin_min_heap_scan(); node != tree_complex.end_min_heap_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(min_heap[min_heap_index], min_heap[min_heap_index]));
            min_heap_index++;
        }

        min_heap_index = 0;
        for (auto node = tree_string.begin_min_heap_scan(); node != tree_string.end_min_heap_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(min_heap[min_heap_index++]));
        }

        CHECK_EQ(empty_tree.begin_min_heap_scan(), empty_tree.end_min_heap_scan());
    }
};

TEST_CASE("Test Iterators on Non-Binary Trees")
{
    Node<int> root_node = Node<int>(1);
    Tree<int, 3> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);

    // The tree should look like:
    /**
     *       root = 1
     *     /   |   \
     *    2    3    4
     *   /|\
     *  5 6 7
     */

    Node<Complex<int>> root_node_complex = Node<Complex<int>>(Complex<int>{1, 1});
    Tree<Complex<int>, 3> tree_complex; // Binary tree that contains doubles.
    tree_complex.add_root(root_node_complex);
    Node<Complex<int>> n1_complex = Node<Complex<int>>(Complex(2, 2));
    Node<Complex<int>> n2_complex = Node<Complex<int>>(Complex(3, 3));
    Node<Complex<int>> n3_complex = Node<Complex<int>>(Complex(4, 4));
    Node<Complex<int>> n4_complex = Node<Complex<int>>(Complex(5, 5));
    Node<Complex<int>> n5_complex = Node<Complex<int>>(Complex(6, 6));
    Node<Complex<int>> n6_complex = Node<Complex<int>>(Complex(7, 7));

    tree_complex.add_sub_node(root_node_complex, n1_complex);
    tree_complex.add_sub_node(root_node_complex, n2_complex);
    tree_complex.add_sub_node(root_node_complex, n3_complex);
    tree_complex.add_sub_node(n1_complex, n4_complex);
    tree_complex.add_sub_node(n1_complex, n5_complex);
    tree_complex.add_sub_node(n1_complex, n6_complex);

    // The tree should look like:
    /**
     *          root = 1 + 1i
     *     /        |        \
     *    2 + 2i    3 + 3i    4 + 4i
     *   /      |   \
     *  5 + 5i 6 + 6i 7+ 7i
     */

    Node<string> root_node_string = Node(string("1"));
    Tree<string, 4> tree_string; // Binary tree that contains doubles.
    tree_string.add_root(root_node_string);
    Node<string> n1_string = Node(string("2"));
    Node<string> n2_string = Node(string("3"));
    Node<string> n3_string = Node(string("4"));
    Node<string> n4_string = Node(string("5"));
    Node<string> n5_string = Node(string("6"));
    Node<string> n6_string = Node(string("7"));

    tree_string.add_sub_node(root_node_string, n1_string);
    tree_string.add_sub_node(root_node_string, n2_string);
    tree_string.add_sub_node(root_node_string, n3_string);
    tree_string.add_sub_node(n1_string, n4_string);
    tree_string.add_sub_node(n1_string, n5_string);
    tree_string.add_sub_node(n1_string, n6_string);

    // The tree should look like:
    /**
     *          root = "1"
     *     /        |        \
     *    "2"       "3"       "4"
     *   /      |   \
     *  "5"    "6"  "7"
     */

    Tree<int, 6> empty_tree;

    // All Binary Itrators should return DFS scan
    SUBCASE("Test Pre Order")
    {
        int pre_order[] = {1, 2, 5, 6, 7, 3, 4};
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

        CHECK_EQ(empty_tree.begin_pre_order(), empty_tree.end_pre_order());
    }

    SUBCASE("Test Post Order")
    {
        int post_order[] = {1, 2, 5, 6, 7, 3, 4};
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

        CHECK_EQ(empty_tree.begin_post_order(), empty_tree.end_post_order());
    }

    SUBCASE("Test In Order")
    {
        int in_order[] = {1, 2, 5, 6, 7, 3, 4};
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

        CHECK_EQ(empty_tree.begin_in_order(), empty_tree.end_in_order());
    }

    SUBCASE("Test DFS")
    {
        int dfs[] = {1, 2, 5, 6, 7, 3, 4};
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

        CHECK_EQ(empty_tree.begin_dfs_scan(), empty_tree.end_dfs_scan());
    }

    SUBCASE("Test BFS")
    {
        int bfs[] = {1, 2, 3, 4, 5, 6, 7};
        size_t bfs_index = 0;

        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), bfs[bfs_index++]);
        }

        bfs_index = 0;
        for (auto node = tree_complex.begin_bfs_scan(); node != tree_complex.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), Complex(bfs[bfs_index], bfs[bfs_index]));
            bfs_index++;
        }

        bfs_index = 0;
        for (auto node = tree_string.begin_bfs_scan(); node != tree_string.end_bfs_scan(); ++node)
        {
            CHECK_EQ(node.get_value(), formatNumbers(bfs[bfs_index++]));
        }

        CHECK_EQ(empty_tree.begin_bfs_scan(), empty_tree.end_bfs_scan());
    }

    SUBCASE("Test MinHeap") // Min  heap should not work on non binary trees
    {
        CHECK_THROWS(tree.begin_min_heap_scan());
        CHECK_THROWS(tree_complex.begin_min_heap_scan());
        CHECK_THROWS(tree_string.begin_min_heap_scan());
        CHECK_THROWS(tree.end_min_heap_scan());
        CHECK_THROWS(tree_complex.end_min_heap_scan());
        CHECK_THROWS(tree_string.end_min_heap_scan());
        CHECK_THROWS(empty_tree.begin_min_heap_scan());
        CHECK_THROWS(empty_tree.end_min_heap_scan());
    }
}

TEST_CASE("Test Node")
{
    SUBCASE("Test Constructor - Valid operation")
    {
        Node<int> n1(1);
        CHECK_EQ(n1.get_data(), 1);
        CHECK_EQ(n1.get_num_of_childs(), 0);

        Node<double> n2(1.1);
        CHECK_EQ(n2.get_data(), 1.1);
        CHECK_EQ(n2.get_num_of_childs(), 0);

        Node<float> n3(1.1);
        CHECK_EQ(n3.get_data(), (float)1.1);
        CHECK_EQ(n3.get_num_of_childs(), 0);

        Node<long> n4(1);
        CHECK_EQ(n4.get_data(), 1);
        CHECK_EQ(n4.get_num_of_childs(), 0);

        Node<short> n7(1);
        CHECK_EQ(n7.get_data(), 1);
        CHECK_EQ(n7.get_num_of_childs(), 0);

        Node<Complex<int>> n5(Complex<int>(1, 1));
        CHECK_EQ(n5.get_data(), Complex<int>(1, 1));
        CHECK_EQ(n5.get_num_of_childs(), 0);

        Node<bool> n6(true);
        CHECK_EQ(n6.get_data(), true);
        CHECK_EQ(n6.get_num_of_childs(), 0);

        Node<string> n8("1");
        CHECK_EQ(n8.get_data(), "1");
        CHECK_EQ(n8.get_num_of_childs(), 0);

        Node<char> n9('a');
        CHECK_EQ(n9.get_data(), 'a');
        CHECK_EQ(n9.get_num_of_childs(), 0);
    }

    SUBCASE("Test Copy Constructor")
    {
        Node<int> n1(1);
        Node<int> n2(n1);
        CHECK_EQ(n1.get_data(), n2.get_data());
        CHECK_EQ(n1.get_num_of_childs(), n2.get_num_of_childs());

        Node<double> n3(1.1);
        Node<double> n4(n3);
        CHECK_EQ(n3.get_data(), n4.get_data());
        CHECK_EQ(n3.get_num_of_childs(), n4.get_num_of_childs());

        Node<float> n5(1.1);
        Node<float> n6(n5);
        CHECK_EQ(n5.get_data(), n6.get_data());
        CHECK_EQ(n5.get_num_of_childs(), n6.get_num_of_childs());

        Node<long> n7(1);
        Node<long> n8(n7);
        CHECK_EQ(n7.get_data(), n8.get_data());
        CHECK_EQ(n7.get_num_of_childs(), n8.get_num_of_childs());

        Node<short> n9(1);
        Node<short> n10(n9);
        CHECK_EQ(n9.get_data(), n10.get_data());
        CHECK_EQ(n9.get_num_of_childs(), n10.get_num_of_childs());

        Node<bool> n13(true);
        Node<bool> n14(n13);
        CHECK_EQ(n13.get_data(), n14.get_data());
        CHECK_EQ(n13.get_num_of_childs(), n14.get_num_of_childs());

        Node<string> n15("1");
        Node<string> n16(n15);
        CHECK_EQ(n15.get_data(), n16.get_data());
        CHECK_EQ(n15.get_num_of_childs(), n16.get_num_of_childs());

        Node<char> n17('a');
        Node<char> n18(n17);
        CHECK_EQ(n17.get_data(), n18.get_data());
        CHECK_EQ(n17.get_num_of_childs(), n18.get_num_of_childs());
    }

    SUBCASE("Test Complex Copy Constructor")
    {
        Node<Complex<int>> n11(Complex<int>(1, 1));
        Node<Complex<int>> n12(n11);
        CHECK_EQ(n11.get_data(), n12.get_data());
        CHECK_EQ(n11.get_num_of_childs(), n12.get_num_of_childs());
    }

    SUBCASE("Test add_child")
    {
        Node<int> n1(1);
        Node<int> n2(2);
        n1.add_child(n2);
        CHECK_EQ(n1.get_num_of_childs(), 1);
        CHECK_EQ(n1.get_children()[0], &n2);
    }

    SUBCASE("Test get_num_of_childs")
    {
        Node<int> n1(1);
        CHECK_EQ(n1.get_num_of_childs(), 0);

        Node<int> n2(2);
        n1.add_child(n2);
        CHECK_EQ(n1.get_num_of_childs(), 1);

        Node<int> n3(3);
        n1.add_child(n3);
        CHECK_EQ(n1.get_num_of_childs(), 2);

        size_t runs = 50;
        for (size_t i = 3; i < runs; i++)
        {
            Node<int> node = Node<int>(i);
            n1.add_child(node);
            CHECK_EQ(n1.get_num_of_childs(), i);
        }
    }

    SUBCASE("Test get_data")
    {
        Node<int> n1(1);
        CHECK_EQ(n1.get_data(), 1);

        Node<double> n2(1.1);
        CHECK_EQ(n2.get_data(), 1.1);

        Node<float> n3(1.1);
        CHECK_EQ(n3.get_data(), (float)1.1);

        Node<long> n4(1);
        CHECK_EQ(n4.get_data(), 1);

        Node<short> n7(1);
        CHECK_EQ(n7.get_data(), 1);

        Node<Complex<int>> n5(Complex<int>(1, 1));
        CHECK_EQ(n5.get_data(), Complex<int>(1, 1));

        Node<bool> n6(true);
        CHECK_EQ(n6.get_data(), true);

        Node<string> n8("1");
        CHECK_EQ(n8.get_data(), "1");

        Node<char> n9('a');
        CHECK_EQ(n9.get_data(), 'a');
    }

    SUBCASE("Test get_children")
    {
        Node<int> n1(1);
        Node<int> n2(2);
        Node<int> n3(3);
        n1.add_child(n2);
        n1.add_child(n3);
        CHECK_EQ(n1.get_children().size(), 2);
        CHECK_EQ(n1.get_children()[0], &n2);
        CHECK_EQ(n1.get_children()[1], &n3);
    }

    SUBCASE("Test is_leaf")
    {
        Node<int> n1(1);
        CHECK_EQ(n1.is_leaf(), true);

        Node<int> n2(2);
        n1.add_child(n2);
        CHECK_EQ(n1.is_leaf(), false);
    }

    SUBCASE("Test operator<")
    {
        Node<int> n1(1);
        Node<int> n2(2);
        CHECK_EQ(n1 < n2, true);

        Node<double> n3(1.1);
        Node<double> n4(1.2);
        CHECK_EQ(n3 < n4, true);

        Node<float> n5(1.1);
        Node<float> n6(1.2);
        CHECK_EQ(n5 < n6, true);

        Node<long> n7(1);
        Node<long> n8(2);
        CHECK_EQ(n7 < n8, true);

        Node<short> n9(1);
        Node<short> n10(2);
        CHECK_EQ(n9 < n10, true);

        Node<Complex<int>> n11(Complex<int>(1, 1));
        Node<Complex<int>> n12(Complex<int>(1, 2));
        CHECK_EQ(n11 < n12, true);
    }

    SUBCASE("Test operator>")
    {
        Node<int> n1(1);
        Node<int> n2(2);
        CHECK_EQ(n2 > n1, true);

        Node<double> n3(1.1);
        Node<double> n4(1.2);
        CHECK_EQ(n4 > n3, true);

        Node<float> n5(1.1);
        Node<float> n6(1.2);
        CHECK_EQ(n6 > n5, true);

        Node<long> n7(1);
        Node<long> n8(2);
        CHECK_EQ(n8 > n7, true);

        Node<short> n9(1);
        Node<short> n10(2);
        CHECK_EQ(n10 > n9, true);

        Node<Complex<int>> n11(Complex<int>(1, 1));
        Node<Complex<int>> n12(Complex<int>(1, 2));
        CHECK_EQ(n12 > n11, true);
    }

    SUBCASE("Test operator==")
    {
        Node<int> n1(1);
        Node<int> n2(1);
        CHECK_EQ(n1 == n2, true);

        Node<double> n3(1.1);
        Node<double> n4(1.1);
        CHECK_EQ(n3 == n4, true);

        Node<float> n5(1.1);
        Node<float> n6(1.1);
        CHECK_EQ(n5 == n6, true);

        Node<long> n7(1);
        Node<long> n8(1);
        CHECK_EQ(n7 == n8, true);

        Node<short> n9(1);
        Node<short> n10(1);
        CHECK_EQ(n9 == n10, true);

        Node<Complex<int>> n11(Complex<int>(1, 1));
        Node<Complex<int>> n12(Complex<int>(1, 1));
        CHECK_EQ(n11 == n12, true);
    }
}

TEST_CASE("Test Complex")
{
    SUBCASE("Test Constructor - Valid operation")
    {
        Complex<int> c1(1, 2);
        CHECK_EQ(c1.getReal(), 1);
        CHECK_EQ(c1.getImaginary(), 2);
    }

    SUBCASE("Test Constructor - Check Errors")
    {
        // CHECK_THROWS(Complex<string>("1", "2"));
        // CHECK_THROWS(Complex<bool>(true, true));
        // CHECK_THROWS(Complex<char>('a', 'b'));

        // Will fail to compile
    }

    SUBCASE("Test get_data")
    {
        Complex<int> c1(1, 2);
        CHECK_EQ(c1.get_data(), "1 + 2i");

        Complex<double> c2(1.1, 2.2);
        CHECK_EQ(c2.get_data(), "1.1 + 2.2i");

        Complex<float> c3(1.1, 2.2);
        CHECK_EQ(c3.get_data(), "1.1 + 2.2i");

        Complex<long> c4(1, 2);
        CHECK_EQ(c4.get_data(), "1 + 2i");

        Complex<short> c7(1, 2);
        CHECK_EQ(c7.get_data(), "1 + 2i");
    }

    SUBCASE("Test getReal")
    {
        Complex<int> c1(1, 2);
        CHECK_EQ(c1.getReal(), 1);

        Complex<double> c2(1.1, 2.2);
        CHECK_EQ(c2.getReal(), 1.1);

        Complex<float> c3(1.1, 2.2);
        CHECK_EQ(c3.getReal(), (float)1.1);

        Complex<long> c4(1, 2);
        CHECK_EQ(c4.getReal(), 1);

        Complex<short> c7(1, 2);
        CHECK_EQ(c7.getReal(), 1);
    }

    SUBCASE("Test getImaginary")
    {
        Complex<int> c1(1, 2);
        CHECK_EQ(c1.getImaginary(), 2);

        Complex<double> c2(1.1, 2.2);
        CHECK_EQ(c2.getImaginary(), 2.2);

        Complex<float> c3(1.1, 2.2);
        CHECK_EQ(c3.getImaginary(), (float)2.2);

        Complex<long> c4(1, 2);
        CHECK_EQ(c4.getImaginary(), 2);

        Complex<short> c7(1, 2);
        CHECK_EQ(c7.getImaginary(), 2);
    }

    SUBCASE("Test operator== - Are equal")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 2);
        CHECK_EQ(c1 == c2, true);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.2);
        CHECK_EQ(c3 == c4, true);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.2);
        CHECK_EQ(c5 == c6, true);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 2);
        CHECK_EQ(c7 == c8, true);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 2);
        CHECK_EQ(c9 == c10, true);
    }

    SUBCASE("Test operator== - Are not equal")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 3);
        CHECK_EQ(c1 == c2, false);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.3);
        CHECK_EQ(c3 == c4, false);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.3);
        CHECK_EQ(c5 == c6, false);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 3);
        CHECK_EQ(c7 == c8, false);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 3);
        CHECK_EQ(c9 == c10, false);
    }

    SUBCASE("Test operator!= - True")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 3);
        CHECK_EQ(c1 != c2, true);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.3);
        CHECK_EQ(c3 != c4, true);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.3);
        CHECK_EQ(c5 != c6, true);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 3);
        CHECK_EQ(c7 != c8, true);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 3);
        CHECK_EQ(c9 != c10, true);
    }

    SUBCASE("Test operator!= - False")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 2);
        CHECK_EQ(c1 != c2, false);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.2);
        CHECK_EQ(c3 != c4, false);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.2);
        CHECK_EQ(c5 != c6, false);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 2);
        CHECK_EQ(c7 != c8, false);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 2);
        CHECK_EQ(c9 != c10, false);
    }

    SUBCASE("Test operator> - False")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 3);
        CHECK_EQ(c1 > c2, false);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.3);
        CHECK_EQ(c3 > c4, false);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.3);
        CHECK_EQ(c5 > c6, false);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 3);
        CHECK_EQ(c7 > c8, false);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 3);
        CHECK_EQ(c9 > c10, false);
    }

    SUBCASE("Test operator> - True")
    {
        Complex<int> c1(1, 3);
        Complex<int> c2(1, 2);
        CHECK_EQ(c1 > c2, true);

        Complex<double> c3(1.1, 2.3);
        Complex<double> c4(1.1, 2.2);
        CHECK_EQ(c3 > c4, true);

        Complex<float> c5(1.1, 2.3);
        Complex<float> c6(1.1, 2.2);
        CHECK_EQ(c5 > c6, true);

        Complex<long> c7(1, 3);
        Complex<long> c8(1, 2);
        CHECK_EQ(c7 > c8, true);

        Complex<short> c9(1, 3);
        Complex<short> c10(1, 2);
        CHECK_EQ(c9 > c10, true);
    }

    SUBCASE("Test operator< - False")
    {
        Complex<int> c1(1, 2);
        Complex<int> c2(1, 3);
        CHECK_EQ(c1 < c2, true);

        Complex<double> c3(1.1, 2.2);
        Complex<double> c4(1.1, 2.3);
        CHECK_EQ(c3 < c4, true);

        Complex<float> c5(1.1, 2.2);
        Complex<float> c6(1.1, 2.3);
        CHECK_EQ(c5 < c6, true);

        Complex<long> c7(1, 2);
        Complex<long> c8(1, 3);
        CHECK_EQ(c7 < c8, true);

        Complex<short> c9(1, 2);
        Complex<short> c10(1, 3);
        CHECK_EQ(c9 < c10, true);
    }

    SUBCASE("Test operator< - True")
    {
        Complex<int> c1(1, 3);
        Complex<int> c2(1, 2);
        CHECK_EQ(c1 < c2, false);

        Complex<double> c3(1.1, 2.3);
        Complex<double> c4(1.1, 2.2);
        CHECK_EQ(c3 < c4, false);

        Complex<float> c5(1.1, 2.3);
        Complex<float> c6(1.1, 2.2);
        CHECK_EQ(c5 < c6, false);

        Complex<long> c7(1, 3);
        Complex<long> c8(1, 2);
        CHECK_EQ(c7 < c8, false);

        Complex<short> c9(1, 3);
        Complex<short> c10(1, 2);
        CHECK_EQ(c9 < c10, false);
    }

    SUBCASE("Test operator<<")
    {
        Complex<int> c1(1, 2);
        std::ostringstream oss;
        oss << c1;
        CHECK_EQ(oss.str(), "1 + 2i");

        Complex<double> c2(1.1, 2.2);
        std::ostringstream oss2;
        oss2 << c2;
        CHECK_EQ(oss2.str(), "1.1 + 2.2i");

        Complex<float> c3(1.1, 2.2);
        std::ostringstream oss3;
        oss3 << c3;
        CHECK_EQ(oss3.str(), "1.1 + 2.2i");

        Complex<long> c4(1, 2);
        std::ostringstream oss4;
        oss4 << c4;
        CHECK_EQ(oss4.str(), "1 + 2i");

        Complex<short> c5(1, 2);
        std::ostringstream oss5;
        oss5 << c5;
        CHECK_EQ(oss5.str(), "1 + 2i");
    }
}