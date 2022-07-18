#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T, class V=null_type> using Tree = tree<T, V, std::less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
