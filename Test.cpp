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

    Node<Complex> root_node_complex = Node(Complex(1.1, 1.1));
    Tree<Complex> tree_complex; // Binary tree that contains doubles.
    tree_complex.add_root(root_node_complex);
    Node<Complex> n1_complex = Node(Complex(1.2, 1.2));
    Node<Complex> n2_complex = Node(Complex(1.3, 1.3));
    Node<Complex> n3_complex = Node(Complex(1.4, 1.4));
    Node<Complex> n4_complex = Node(Complex(1.5, 1.5));
    Node<Complex> n5_complex = Node(Complex(1.6, 1.6));

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

        // post_order_index = 0;
        // for (auto node = tree_complex.begin_post_order(); node != tree_complex.end_post_order(); ++node)
        // {
        //     std::cout << node.get_value() << std::endl;
        //     CHECK_EQ(node.get_value(), Complex(post_order[post_order_index], post_order[post_order_index]));
        //     post_order_index++;
        // }

        post_order_index = 0;
        for (auto node = tree_string.begin_post_order(); node != tree_string.end_post_order(); ++node)
        {
            std::cout << node.get_value() << std::endl;

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