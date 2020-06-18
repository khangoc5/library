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


# :x: Reversible-Splay-Tree(反転可能Splay木) <small>(structure/bbst/reversible-splay-tree.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ac1922c227762d9e573c4f7aedc86899">structure/bbst</a>
* <a href="{{ site.github.repository_url }}/blob/master/structure/bbst/reversible-splay-tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-18 21:29:10+09:00




## Verified with

* :x: <a href="../../../verify/test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp.html">test/verify/yosupo-dynamic-tree-vertex-add-path-sum.test.cpp</a>
* :x: <a href="../../../verify/test/verify/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp.html">test/verify/yosupo-dynamic-tree-vertex-set-path-composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief Reversible-Splay-Tree(反転可能Splay木)
 */
template< typename Monoid = int, typename OperatorMonoid = void >
struct ReversibleSplayTree {
public:
  using F = function< Monoid(Monoid, Monoid) >;
  using S = function< Monoid(Monoid) >;

  struct Node {
    Node *l, *r, *p;
    Monoid key, sum;
    bool rev;
    size_t sz;

    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }

    Node(const Monoid &key) :
        key(key), sum(key), sz(1), rev(false),
        l(nullptr), r(nullptr), p(nullptr) {}
  };

  ReversibleSplayTree(const F &f, const Monoid &M1) :
      ReversibleSplayTree(f, [](const Monoid &a) { return a; }, M1) {}

  ReversibleSplayTree(const F &f, const S &s, const Monoid &M1) :
      f(f), s(s), M1(M1) {}


  inline size_t count(const Node *t) { return t ? t->sz : 0; }

  inline const Monoid &sum(const Node *t) { return t ? t->sum : M1; }

  Node *alloc(const Monoid &v = Monoid()) {
    return new Node(v);
  }

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *push_front(Node *t, const Monoid &v = Monoid()) {
    if(!t) {
      t = alloc(v);
      return t;
    } else {
      Node *cur = get_left(t), *z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->l = z;
      splay(z);
      return z;
    }
  }

  Node *push_back(Node *t, const Monoid &v = Monoid()) {
    if(!t) {
      t = alloc(v);
      return t;
    } else {
      Node *cur = get_right(t), *z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->r = z;
      splay(z);
      return z;
    }
  }

  Node *erase(Node *t) {
    splay(t);
    Node *x = t->l, *y = t->r;
    delete t;
    if(!x) {
      t = y;
      if(t) t->p = nullptr;
    } else if(!y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
    }
    return t;
  }

  Node *get_left(Node *t) const {
    while(t->l) t = t->l;
    return t;
  }

  Node *get_right(Node *t) const {
    while(t->r) t = t->r;
    return t;
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {nullptr, nullptr};
    push(t);
    if(k <= count(t->l)) {
      auto x = split(t->l, k);
      t->l = x.second;
      t->p = nullptr;
      if(x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split(t->r, k - count(t->l) - 1);
      t->r = x.first;
      t->p = nullptr;
      if(x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

  template< typename ... Args >
  Node *merge(Node *l, Args ...rest) {
    Node *r = merge(rest...);
    if(!l && !r) return nullptr;
    if(!l) return splay(r), r;
    if(!r) return splay(l), l;
    splay(l), splay(r);
    l = get_right(l);
    splay(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }

  void insert(Node *&t, int k, const Monoid &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  Monoid erase(Node *&t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    auto v = y.first->c;
    delete y.first;
    t = merge(x.first, y.second);
    return v;
  }

  Monoid query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, y.first, y.second);
    return ret;
  }

  Node *build(const vector< Monoid > &v) {
    return build(0, (int) v.size(), v);
  }

  void toggle(Node *t) {
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  Node *update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  void push(Node *t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

private:
  const Monoid M1;
  const F f;
  const S s;

  Node *build(int l, int r, const vector< Monoid > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  Node *merge(Node *l) {
    return l;
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "structure/bbst/reversible-splay-tree.cpp"
/**
 * @brief Reversible-Splay-Tree(反転可能Splay木)
 */
template< typename Monoid = int, typename OperatorMonoid = void >
struct ReversibleSplayTree {
public:
  using F = function< Monoid(Monoid, Monoid) >;
  using S = function< Monoid(Monoid) >;

  struct Node {
    Node *l, *r, *p;
    Monoid key, sum;
    bool rev;
    size_t sz;

    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }

    Node(const Monoid &key) :
        key(key), sum(key), sz(1), rev(false),
        l(nullptr), r(nullptr), p(nullptr) {}
  };

  ReversibleSplayTree(const F &f, const Monoid &M1) :
      ReversibleSplayTree(f, [](const Monoid &a) { return a; }, M1) {}

  ReversibleSplayTree(const F &f, const S &s, const Monoid &M1) :
      f(f), s(s), M1(M1) {}


  inline size_t count(const Node *t) { return t ? t->sz : 0; }

  inline const Monoid &sum(const Node *t) { return t ? t->sum : M1; }

  Node *alloc(const Monoid &v = Monoid()) {
    return new Node(v);
  }

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *push_front(Node *t, const Monoid &v = Monoid()) {
    if(!t) {
      t = alloc(v);
      return t;
    } else {
      Node *cur = get_left(t), *z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->l = z;
      splay(z);
      return z;
    }
  }

  Node *push_back(Node *t, const Monoid &v = Monoid()) {
    if(!t) {
      t = alloc(v);
      return t;
    } else {
      Node *cur = get_right(t), *z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->r = z;
      splay(z);
      return z;
    }
  }

  Node *erase(Node *t) {
    splay(t);
    Node *x = t->l, *y = t->r;
    delete t;
    if(!x) {
      t = y;
      if(t) t->p = nullptr;
    } else if(!y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
    }
    return t;
  }

  Node *get_left(Node *t) const {
    while(t->l) t = t->l;
    return t;
  }

  Node *get_right(Node *t) const {
    while(t->r) t = t->r;
    return t;
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {nullptr, nullptr};
    push(t);
    if(k <= count(t->l)) {
      auto x = split(t->l, k);
      t->l = x.second;
      t->p = nullptr;
      if(x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split(t->r, k - count(t->l) - 1);
      t->r = x.first;
      t->p = nullptr;
      if(x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

  template< typename ... Args >
  Node *merge(Node *l, Args ...rest) {
    Node *r = merge(rest...);
    if(!l && !r) return nullptr;
    if(!l) return splay(r), r;
    if(!r) return splay(l), l;
    splay(l), splay(r);
    l = get_right(l);
    splay(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }

  void insert(Node *&t, int k, const Monoid &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  Monoid erase(Node *&t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    auto v = y.first->c;
    delete y.first;
    t = merge(x.first, y.second);
    return v;
  }

  Monoid query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, y.first, y.second);
    return ret;
  }

  Node *build(const vector< Monoid > &v) {
    return build(0, (int) v.size(), v);
  }

  void toggle(Node *t) {
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  Node *update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  void push(Node *t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

private:
  const Monoid M1;
  const F f;
  const S s;

  Node *build(int l, int r, const vector< Monoid > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  Node *merge(Node *l) {
    return l;
  }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
