#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include "../../template/template.cpp"
#include "../../graph/graph-template.cpp"

#include "../../structure/heap/fibonacchi-heap.cpp"

#include "../../graph/mst/prim-fibonacchi-heap.cpp"

int main() {
  int V, E;
  cin >> V >> E;
  Graph<> g(V);
  g.read(E, 0, true);
  cout << prim_fibonacchi_heap(g).cost << "\n";
}
