#include <iostream>

using namespace std;

int n, m;
int v[200005];
//int l[200005];
//int r[200005];
//int x[200005];
int d[200005];

int main(){
  
  /* Varianta 1 -> O(n * m)
  cin >> n >> m;
  
  ///in cel mai rau caz O(n * m)
  ///in cazul asta n, m <= 200000
  /// ~ 4 * 10^10 operatii 
  /// ~ 10^8 operatii intra intr-o secunda
  ///4 * 10 ^ 10 operatii ar fi 400 de secunde

  for(int i = 1;i <= m;i++){
    int l, r, x;
    cin >> l >> r >> x;

    for(int j = l;j <= r;j++){ /// in cel mai rau caz, l = 1, r = n pentru toate operatiile
      v[j] += x;
    }
  }

  for(int i = 1;i <= n;i++){
    cout << v[i] << " ";
  }
  */
  
  /*Varianta 2. O(n * m)
  cin >> n >> m;

  for(int i = 1;i <= m;i++){
    cin >> l[i] >> r[i] >> x[i];
  }

  for(int i = 1;i <= n;i++){ /// Tot O(n * m) complexitate
    for(int j = 1;j <= m;j++){
      if(l[j] <= i && i <= r[j]){
        v[i] += x[j];
      }
    }
  }

  for(int i = 1;i <= n;i++){
    cout << v[i] << " ";
  }
  */
  
  ///Varianta 3 -> O(n + m)

  
  cin >> n >> m;
  for (int i = 1; i <=m; i ++)
  {
    int l, r, x;
    cin >> l >> r >> x;
    d[l] += x;
    d[r+1] -= x;
   }
  for (int i = 1; i <= n; i ++)
  {
    v[i] = d[i] + v[i - 1];
    cout << v[i] << " ";
  }
  return 0;
}

