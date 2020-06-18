---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: Kruskal(最小全域木) <small>(graph/mst/kruskal.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#51f95ed2fd9ed3be34f576d38fbd25a2">graph/mst</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/mst/kruskal.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-30 02:08:59+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/verify/aoj-grl-2-a-2.test.cpp.html">test/verify/aoj-grl-2-a-2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief Kruskal(最小全域木)
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const Edge< T > &a, const Edge< T > &b) {
    return a.cost < b.cost;
  });
  UnionFind tree(V);
  T total = T();
  Edges< T > es;
  for(auto &e : edges) {
    if(tree.unite(e.from, e.to)) {
      es.emplace_back(e);
      total += e.cost;
    }
  }
  return {total, es};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/mst/kruskal.cpp"
/**
 * @brief Kruskal(最小全域木)
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const Edge< T > &a, const Edge< T > &b) {
    return a.cost < b.cost;
  });
  UnionFind tree(V);
  T total = T();
  Edges< T > es;
  for(auto &e : edges) {
    if(tree.unite(e.from, e.to)) {
      es.emplace_back(e);
      total += e.cost;
    }
  }
  return {total, es};
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
