#include <iostream>

using namespace std;

int n, q;

int v[505][505];

int main(){

  cin >> n;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= n;j++){
      int val;
      cin >> val; /// valoarea asta <=> a adauga pe i j i j valoarea

      v[i][j] += val;
      v[i + 1][j] -= val;
      v[i][j + 1] -= val;
      v[i + 1][j + 1] += val;
    }
  }

  cin >> q;
  while(q--){
    int l1, c1, l2, c2, x;
    cin >> l1 >> c1 >> l2 >> c2 >> x;
    v[l1][c1] += x;
    v[l2 + 1][c1] -= x;
    v[l1][c2 + 1] -= x;
    v[l2 + 1][c2 + 1] += x;
  }

  for(int i = 1; i <= n;i++){
    for(int j = 1;j <= n;j++){
      v[i][j] = v[i][j] + v[i][j - 1] + v[i - 1][j] - v[i - 1][j - 1]; /// (i - 1,j), (i, j - 1), (i - 1, j - 1) au fost parcurse deja
                                                                       /// asadar, ele reprezinta acum sume pe prefix
      cout << v[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}

