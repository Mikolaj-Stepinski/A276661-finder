#include <bits/stdc++.h>

using namespace std;

const int N=5;
const int B=15;

void check(vector <int> &vec)
{
  set<int> sums, sums2;
  sums = {0};
  for (int v : vec) {
    sums2 = set<int>(sums);
    for (int x : sums) {
      int next = x + v;
      if (sums.count(next)) {
        return;
      }
      sums2.insert(next);
    }
    swap(sums, sums2);
  }
  printf("found vec ");
  for (int v : vec) {
    printf("%u ", v);
  }
  printf("\n");
}

void check_all()
{
  vector<int> vec(N);
  for (int i1=1;i1<=B;i1++) {
  for (int i2=i1+1;i2<=B;i2++) {
  for (int i3=i2+1;i3<=B;i3++) {
  for (int i4=i3+1;i4<=B;i4++) {
  for (int i5=i4+1;i5<=B;i5++) {
  vec = {i1, i2, i3, i4, i5};
  check(vec);
  }}}}}
}

int main()
{
  check_all();
}
