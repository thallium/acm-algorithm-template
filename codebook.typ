#set page(
    flipped: true,
    margin: 20pt,
    columns: 2,
    numbering: "1",
    footer: [
    #set align(right)
    #set text(8pt)
    #counter(page).display(
      "1",
    )
  ]
)

#set par(
    leading: 0.45em,
)

#set text(
    size: 10pt,
)

#let files = (
"code/DataStructure/2d_pref_sum.cpp",
"code/DataStructure/fenwick.cpp",
"code/DataStructure/lazy_segtree.cpp",
"code/DataStructure/line_container.cpp",
"code/DataStructure/monotonic_dp_hull.cpp",
"code/DataStructure/persistent_seg.cpp",
"code/DataStructure/segtree.cpp",
"code/DataStructure/sliding_window.cpp",
"code/DataStructure/sparse-table.cpp",
"code/DataStructure/treap_split.cpp",
"code/DataStructure/union_find.cpp",
"code/DataStructure/wavelet-tree.hpp",
"code/DataStructure/xor_basis.hpp",
"code/Geometry/angle.h",
"code/Geometry/circle.h",
"code/Geometry/geometry.h",
"code/Geometry/line.h",
"code/Geometry/point.h",
"code/Geometry/polygon.h",
"code/Geometry/segment.h",
"code/Graph/2-sat.cpp",
"code/Graph/BellmanFord.cpp",
"code/Graph/MCMF.cpp",
"code/Graph/augmented_path_BPM.cpp",
"code/Graph/biconnected_components.cpp",
"code/Graph/binary_lifting.cpp",
"code/Graph/blossom.cpp",
"code/Graph/bridges.cpp",
"code/Graph/centroid-decomposition.cpp",
"code/Graph/count-cycles.cpp",
"code/Graph/dijkstra.cpp",
"code/Graph/dinic.cpp",
"code/Graph/dsu_on_tree.cpp",
"code/Graph/eulerian_path.cpp",
"code/Graph/eulerian_path_directed.cpp",
"code/Graph/hamiltonian-cycle.hpp",
"code/Graph/heavy-light_decomp.cpp",
"code/Graph/hungarian.cpp",
"code/Graph/push-relabel-mincost.hpp",
"code/Graph/push-relabel.cpp",
"code/Graph/tarjan_SCC.cpp",
"code/Graph/two_edge_connected_components.cpp",
"code/Graph/virtual_tree.hpp",
"code/Math/BSGS.cpp",
"code/Math/ChineseRT.cpp",
"code/Math/Lagrange_interpolation.hpp",
"code/Math/binomial.cpp",
"code/Math/euler.h",
"code/Math/exGCD.hpp",
"code/Math/factorization.cpp",
"code/Math/fft.hpp",
"code/Math/gauss.h",
"code/Math/inverse.h",
"code/Math/lucas.h",
"code/Math/nfft.hpp",
"code/Math/sieve.cpp",
"code/Math/simplex.h",
"code/Misc/Mo's_algorithm.cpp",
"code/string/ac-automaton.cpp",
"code/string/kmp.cpp",
"code/string/manacher.cpp",
"code/string/polyhash.cpp",
"code/string/suffix automaton.cpp",
"code/string/suffix_array.cpp",
"code/string/suffix_array_linear.cpp",
"code/string/trie.cpp",
"code/string/z-function.cpp",
"code/vimrc",
)

#outline()

#for name in files [
#let text = read(name)
== #name
#raw(text, lang: "cpp")
]
