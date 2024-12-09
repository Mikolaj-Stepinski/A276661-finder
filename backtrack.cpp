#include <bits/stdc++.h>

using namespace std;

#define I uint32_t

#define active (sol.size())

vector<I> sol;
vector<set<I>> sets;

int exists(I x) {
  for (I i=0;i<active+1;i++) {
    if (sets[i].count(x)) {
      return 1;
    }
  }
  return 0;
}

int try_append(I x) {
  sets[active+1].clear();
  for (I i=0;i<active+1;i++) {
    for (I v:sets[i]) {
      if (exists(x+v)) {
        return -1;
      }
      sets[active+1].insert(x+v);
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

void backtrack(I N, I M) {
  sets.clear();
  sets.resize(N+1);
  sets[0] = {0};
  I next = 1;
  while (true) {
    if (next > M) {
      if (active == 0) {
        return;
      }
      I last = sol.back();
      next = last+1;
      sol.pop_back();
      continue;
    }
    if (try_append(next) != 0) {
      next++;
      continue;
    }
    sol.push_back(next);
    next++;
    if (active == N) {
      report_solution();
      sol.pop_back();
    }
  }
}

int main() {
  backtrack(8, 85);
}