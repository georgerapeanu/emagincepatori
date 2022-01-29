#include <iostream>

using namespace std;

int n, m;
float a[100][100];
int v[2][3][4][5];///citita cu 4 foruri
/// (i, j, k, l) <-> v[i][j][k][l], v[i][j][k][l] = 3

///int v2[1000][1000][1000]; /// Eroare, matrice prea mare

int main(){

  cin >> n >> m;
  for(int i = 1; i <= n;i++){
    for(int j = 1;j <= m;j++){
      cin >> a[i][j];
    }
  }

  

  return 0;
}
