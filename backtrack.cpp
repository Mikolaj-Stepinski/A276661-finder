#include <bits/stdc++.h>

using namespace std;

#define I int32_t

#define active (sol.size())

vector<I> ans = {0, 1, 2, 4, 7, 13, 24, 44, 84, 161, 10};

I on[4234];

vector<I> sol;
vector<vector<I>> vecs;

int try_append(I x) {
  vecs[active+1].clear();
  for (I i=0;i<active+1;i++) {
    for (I v:vecs[i]) {
      I here=x+v;
      if (on[here]) {
        for (I d:vecs[active+1]) {
          on[d] = 0;
        }
        vecs[active+1].clear();
        return -1;
      }
      vecs[active+1].push_back(here);
      on[here]=1;
    }
  }
  return 0;
}

void report_solution() {
  for(I i=0;i<active;i++) {
    printf("%u, ", sol[i]);
  }
  printf("\n");
}

void remove_last() {
  for (I v:vecs[active]) {
    on[v] = 0;
  }
  sol.pop_back();
}

void backtrack(I N, I M) {
  vecs.clear();
  vecs.resize(N+1);
  vecs[0] = {0};
  on[0] = 1;
  I next = M;
  while (true) {
    if (next - ans[N - active] < 0) {
      // printf("refuted, active %u next %u\n", active, next);
      if (active == 0) {
        return;
      }
      I last = sol.back();
      next = last-1;
      remove_last();
      continue;
    }
    if (try_append(next) != 0) {
      next--;
      continue;
    }
    sol.push_back(next);
    next--;
    if (active == N) {
      report_solution();
      remove_last();
    }
  }
}

int main() {
  backtrack(9, 161);
}