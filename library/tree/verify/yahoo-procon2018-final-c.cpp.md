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


# :warning: tree/verify/yahoo-procon2018-final-c.cpp
* category: tree/verify


[Back to top page](../../../index.html)



## Code
```cpp
int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  UnWeightedGraph g(N);
  for(int i = 1; i < N; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    --x, --y;
    g[x].emplace_back(y);
    g[y].emplace_back(x);
  }
  vector< pair< int, int > > ev[100000];
  for(int i = 0; i < Q; i++) {
    int v, k;
    scanf("%d %d", &v, &k);
    --v;
    ev[v].emplace_back(k, i);
  }
  vector< int > ans(Q);
  CentroidDecomposition< UnWeightedGraph > cd(g);
  UnWeightedGraph tree;
  int root = cd.build(tree);
  vector< int > used(N), sz(N);
 
  function< void(int, int, int, int) > add_path = [&](int idx, int par, int dep, int d) {
    sz[dep] += d;
    for(auto &to : g[idx]) {
      if(to == par || used[to]) continue;
      add_path(to, idx, dep + 1, d);
    }
  };
  function< void(int, int, int) > get_path = [&](int idx, int par, int dep) {
    for(auto &e : ev[idx]) {
      int rest = e.first - dep;
      if(rest < 0) continue;
      ans[e.second] += sz[rest];
    }
    for(auto &to : g[idx]) {
      if(to == par || used[to]) continue;
      get_path(to, idx, dep + 1);
    }
  };
  function< void(int) > beet = [&](int idx) {
    used[idx] = true;
    add_path(idx, -1, 0, 1);
    for(auto &e : ev[idx]) {
      int rest = e.first;
      if(rest < 0) continue;
      ans[e.second] += sz[rest];
    }
    for(auto &to : g[idx]) {
      if(used[to]) continue;
      add_path(to, idx, 1, -1);
      get_path(to, idx, 1);
      add_path(to, idx, 1, 1);
    }
    add_path(idx, -1, 0, -1);
    for(auto &to : tree[idx]) beet(to);
    used[idx] = false;
  };
  beet(root);
  for(auto &x : ans) printf("%d\n", x);
}

```

[Back to top page](../../../index.html)
