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


#let files = (
    "DataStructure/2d_pref_sum.cpp",
"DataStructure/fenwick.cpp",
"DataStructure/lazy_segtree.cpp",
"DataStructure/line_container.cpp",
"DataStructure/monotonic_dp_hull.cpp",
"DataStructure/persistent_seg.cpp",
"DataStructure/segtree.cpp",
"DataStructure/sliding_window.cpp",
"DataStructure/sparse-table.cpp",
"DataStructure/treap_split.cpp",
"DataStructure/union_find.cpp",
"DataStructure/wavelet-tree.hpp",
"DataStructure/xor_basis.hpp",
"Geometry/angle.h",
"Geometry/circle.h",
"Geometry/geometry.h",
"Geometry/line.h",
"Geometry/point.h",
"Geometry/polygon.h",
"Geometry/segment.h",
"Graph/2-sat.cpp",
"Graph/BellmanFord.cpp",
"Graph/MCMF.cpp",
"Graph/augmented_path_BPM.cpp",
"Graph/biconnected_components.cpp",
"Graph/binary_lifting.cpp",
"Graph/blossom.cpp",
"Graph/bridges.cpp",
"Graph/centroid-decomposition.cpp",
"Graph/count-cycles.cpp",
"Graph/dijkstra.cpp",
"Graph/dinic.cpp",
"Graph/dsu_on_tree.cpp",
"Graph/eulerian_path.cpp",
"Graph/eulerian_path_directed.cpp",
"Graph/hamiltonian-cycle.hpp",
"Graph/heavy-light_decomp.cpp",
"Graph/hungarian.cpp",
"Graph/push-relabel-mincost.hpp",
"Graph/push-relabel.cpp",
"Graph/tarjan_SCC.cpp",
"Graph/two_edge_connected_components.cpp",
"Graph/virtual_tree.hpp",
"Math/BSGS.cpp",
"Math/ChineseRT.cpp",
"Math/Lagrange_interpolation.hpp",
"Math/binomial.cpp",
"Math/euler.h",
"Math/exGCD.hpp",
"Math/factorization.cpp",
"Math/fft.hpp",
"Math/gauss.h",
"Math/inverse.h",
"Math/lucas.h",
"Math/nfft.hpp",
"Math/sieve.cpp",
"Math/simplex.h",
"Misc/Mo's_algorithm.cpp",
"string/ac-automaton.cpp",
"string/kmp.cpp",
"string/manacher.cpp",
"string/polyhash.cpp",
"string/suffix automaton.cpp",
"string/suffix_array.cpp",
"string/suffix_array_linear.cpp",
"string/trie.cpp",
"string/z-function.cpp",
"vimrc",
)

#outline()

#for name in files [
#let text = read("code/" + name)
== #name
#raw(text, lang: "txt")
]
