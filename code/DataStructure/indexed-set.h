/* template <
 * typename Key, // key type
 * typename Mapped, // mapped-policy (null_type)
 * typename Cmp_Fn = std::less<Key>, // key comparison functor
 * typename Tag = rb_tree_tag, // underlying data structure (rb_tree_tag, splay_tree_tag, ov_tree_tag)
 * template <
 * typename Const_Node_Iterator, 
 * typename Node_Iterator,
 * typename Cmp_Fn_,
 * typename Allocator_>
 * class Node_Update = null_node_update, (null_node_update, tree_order_statistics_node_update)
 * typename Allocator = std::allocator<char> > // an allocator type
 * class tree;
 *
 * operations: find_by_order(), order_of_key()
 * see: https://opensource.apple.com/source/llvmgcc42/llvmgcc42-2336.9/libstdc++-v3/testsuite/ext/pb_ds/example/trie_prefix_search.cc
 * https://opensource.apple.com/source/llvmgcc42/llvmgcc42-2336.9/libstdc++-v3/testsuite/ext/pb_ds/example/tree_order_statistics.cc
 */
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
