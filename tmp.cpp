#include <bits/stdc++.h>

using namespace std;

int main(){
  int a[2][2];
  a[0][0] = 0;a[0][1] = 1;
  a[1][0] = 2;a[1][1] = 3;

  cout << *(*(a + 1) + 1);
  return 0;
}
