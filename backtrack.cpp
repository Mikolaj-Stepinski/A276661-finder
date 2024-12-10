#include <bits/stdc++.h>

using namespace std;

#ifndef MAX_N
#error "MAX_N not defined"
#endif

#ifndef MAX_M
#error "MAX_M not defined"
#endif

#define MAX_ANS (MAX_M * MAX_N)

#define I int32_t

#define active (sol.size())

vector<I> ans = {0, 1, 2, 4, 7, 13, 24, 44, 84, 161, 10};

bitset<MAX_ANS> on;

vector<I> sol;
vector<vector<I>> vecs;

int try_append(I x) {
  bitset<MAX_ANS> added = on << x;
  if ((added & on).count()) {
    return -1;
  }
  on |= added;
  return 0;
}

void report_solution() {
  for(I i=0;i<active;i++) {
    printf("%u, ", sol[i]);
  }
  printf("\n");
  fflush(stdout);
}

void remove_last() {
  on &= on >> sol.back();
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
      // printf("refuted, active %lu next %u\n", active, next);
      if (active == 0) {
        return;
      }
      I last = sol.back();
      next = last-1;
      remove_last();
      continue;
    }
    if (active == 0) {
      printf("trying %u\n", next);
      fflush(stdout);
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
  backtrack(MAX_N, MAX_M);
}