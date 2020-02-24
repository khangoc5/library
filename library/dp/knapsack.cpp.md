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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: Knapsack(個数制限なしナップサック問題) <small>(dp/knapsack.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#95687afb5d9a2a9fa39038f991640b0c">dp</a>
* <a href="{{ site.github.repository_url }}/blob/master/dp/knapsack.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-21 17:07:30+09:00




## 概要

個数制限なしナップサック問題を次に示す.

重さ $w_i$, 価値 $v_i$ であるような $N$ 種類の品物がある. 重さの和が $W$ 以下となるように選ぶとき, 価値の最大値を求めよ.

* `knapsack(w, v, W, NG, comp)`: `W` 以下の範囲で, 各重さについて価値の最大値を求める. `NG` は到達ができない場合の値で, `comp` は比較演算子.

## 計算量

* $O(NW)$


## Verified with

* :heavy_check_mark: <a href="../../verify/test/verify/aoj-dpl-1-c.test.cpp.html">test/verify/aoj-dpl-1-c.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief Knapsack(個数制限なしナップサック問題)
 * @docs docs/knapsack.md
 */
template< typename T, typename Compare = greater< T > >
vector< T > knapsack(const vector< int > &w, const vector< T > &v, const int &W, const T &NG, const Compare &comp = Compare()) {
  const int N = (int) w.size();
  vector< T > dp(W + 1, NG);
  dp[0] = T();
  for(int i = 0; i < N; i++) {
    for(int j = w[i]; j <= W; j++) {
      if(dp[j - w[i]] != NG) {
        if(comp(dp[j - w[i]] + v[i], dp[j])) {
          dp[j] = dp[j - w[i]] + v[i];
        }
      }
    }
  }
  return dp;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "dp/knapsack.cpp"
/**
 * @brief Knapsack(個数制限なしナップサック問題)
 * @docs docs/knapsack.md
 */
template< typename T, typename Compare = greater< T > >
vector< T > knapsack(const vector< int > &w, const vector< T > &v, const int &W, const T &NG, const Compare &comp = Compare()) {
  const int N = (int) w.size();
  vector< T > dp(W + 1, NG);
  dp[0] = T();
  for(int i = 0; i < N; i++) {
    for(int j = w[i]; j <= W; j++) {
      if(dp[j - w[i]] != NG) {
        if(comp(dp[j - w[i]] + v[i], dp[j])) {
          dp[j] = dp[j - w[i]] + v[i];
        }
      }
    }
  }
  return dp;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
