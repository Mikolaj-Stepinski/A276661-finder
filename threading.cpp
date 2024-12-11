#include <bits/stdc++.h>

using namespace std;

#ifndef MAX_N
#error "MAX_N not defined"
#endif

#ifndef MAX_M
#error "MAX_M not defined"
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef DEPTH
#define DEPTH 1
#endif

#ifndef JOBS
#define JOBS 1
#endif

uint64_t tries = 0;
uint64_t found = 0;
thread_local uint64_t thread_tries = 0;
thread_local uint32_t thread_found = 0;

#define I int32_t

constexpr I MAX_ANS = MAX_M * MAX_N - (MAX_N - 1) * (MAX_N) / 2;

#define active (sol.size())

vector<I> ans = {0, 1, 2, 4, 7, 13, 24, 44, 84, 161, 309, 594, 1159};

thread_local bitset<MAX_ANS> on;

thread_local vector<I> sol;

struct thread_status {
  uint64_t tries;
  uint32_t found;
  bool running;
  bool done;
};

int try_append(I x) {
  thread_tries++;
  bitset<MAX_ANS> added = on << x;
  if ((added & on).count()) {
    return -1;
  }
  on |= added;
  return 0;
}

void report_solution() {
  thread_found++;
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

void launch_thread(vector<I> start, I N, I M, thread_status *status) {
  // printf("started with %u\n", start[0]);
  sol = start;
  on.set(1);
  status->tries = 0;
  status->found = 0;
  for (I x:start) {
    if (try_append(x)) {
      status->running = 0;
      // printf("finished with %u\n", start[0]);
      return;
    }
  }
  I next = sol.back() - 1;
  while (true) {
    if (next - ans[N - active] < 0) {
      // printf("refuted, active %lu next %u\n", active, next);
      if (active == 0) {
        break;
      }
      I last = sol.back();
      next = last-1;
      remove_last();
      continue;
    }
    if (active == start.size() - 1) {
      break;
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
  status->tries = thread_tries;
  status->found = thread_found;
  status->running = 0;
  // printf("finished with %u\n", start[0]);
}

int get_next(I N, I M, I depth, vector<I> &vec) {
  if (vec.empty()) {
    for (I i=0;i<depth;i++) {
      vec.push_back(M-i);
    }
    return 0;
  }
  vec.back()--;
  if (vec.back() + depth - N > 0) {
    return 0;
  }
  vec.pop_back();
  while(vec.size() > 0) {
    if (vec.back() - N + vec.size() - 1 <= 0) {
      vec.pop_back();
    } else {
      break;
    }
  }
  if (vec.size() == 0) {
    return -1;
  }
  vec.back()--;
  while (vec.size() < depth) {
    vec.push_back(vec.back()-1);
  }
  return 0;
}

// void f(I N, vector<I> v, thread_status &status) {
//   printf("started thread with %u\n", N);
//   return;
// }

void backtrack(I N, I M, I num_jobs) {
  vector<thread_status> jobs(num_jobs);
  // pthread_t *threads = (pthread_t *)malloc(num_jobs*sizeof(pthread_t));

  vector<I> next;
  get_next(N, M, DEPTH, next);
  while (true) {
    I i=0;
    bool action = 0;
    for (thread_status &status : jobs) {
      if (status.done == 0) {
        action = 1;
      }
      if (status.running == 0) {
        tries += status.tries;
        found += status.found;
        status.running = 1;
        // printf("got thread %u with %lu tries\n", i, status.tries);
        fflush(stdout);
        if (next.size()) {
          // printf("spawning thread %u\n", i);
          // fflush(stdout);
          thread th(launch_thread, next, N, M, &status);
          // thread th(f, i, next, &&status);
          th.detach();
          get_next(N, M, DEPTH, next);
        } else {
          // printf("retiring thread %u\n", i);
          status.done = 1;
        }
      }
      i++;
    }
    // for (I j=0;j<num_jobs;j++) {
    //   printf("thread %u: running %u done %u\n", j, jobs[j].running, jobs[j].done);
    // }
    if (action == 0) {
      break;
    }
  }

}

int main() {
  ans[MAX_N] = ans[MAX_N-1]-1;
  backtrack(MAX_N, MAX_M, JOBS);
}
