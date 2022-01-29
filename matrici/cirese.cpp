#include <iostream>

using namespace std;

int n, m, k;
int v[105][105];
int p[105][105];

int main(){

  cin >> n >> m >> k;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      cin >> v[i][j];
      p[i][j] = v[i][j] + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1]; ///sume pe prefix
    }
  }

  int maxim = 0;

  while(k--){///face fix k pasi <=> for(int i = 1;i <= k;i++) cu exceptia faptului ca i nu este definit, si la final k devine 0
    int i1, i2, j1, j2;
    cin >> i1 >> j1 >> i2 >> j2;
    int suma = p[i2][j2] - p[i1 - 1][j2] - p[i2][j1 - 1] + p[i1 - 1][j1 - 1];
    if(suma > maxim){
      maxim = suma;
    }
  }

  cout << maxim;

  return 0;
}
