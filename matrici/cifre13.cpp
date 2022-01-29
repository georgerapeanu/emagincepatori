/*
  0: (i,j + 1);(i, j + 2); (i + 1, j); (i + 1, j + 3); ... (i + 5, j);(i + 5, j + 3);(i + 6,j + 1);(i + 6, j + 2);
  ....

*/

#include <fstream>

using namespace std;

ifstream f("cifre13.in");
ofstream g("cifre13.out");

int n, m, c;
bool v[1010][1010];

int main(){
  f >> n >> m >> c;

  for(int i = 1;i <= c;i++){
    int lin, col, x;
    f >> x >> lin >> col;

    if(x == 0){
      v[lin][col + 1] = 1; 
      v[lin][col + 2] = 1;  ///prima linie din 0 manual
      v[lin + 6][col + 1] = 1;
      v[lin + 6][col + 2] = 1; /// ultima linie din 0 manual
      for(int l = lin + 1;l <= lin + 5;l++){ ///liniile paralele din 0
        v[l][col] = 1;
        v[l][col + 3] = 1; 
      }
    }else if(x == 1){
      v[lin + 2][col] = 1;
      v[lin + 1][col + 1] = 1;///linia diagonala din 1

      v[lin + 6][col + 1] = 1;
      v[lin + 6][col + 3] = 1; /// baza 1-lui

      for(int l = lin;l <= lin + 6;l++){
        v[l][col + 2] = 1;
      }
    }else if(x == 2){
      for(int j = col;j <= col + 3;j++){ /// baza 2-ului
        v[lin + 6][j] = 1;
      }
      for(int l = lin + 5,j = col;j <= col + 3;j++,l--){///diagonala din 2
        v[l][j] = 1;
      }
      for(int l = lin + 1;l <= lin + 2;l++){ /// liniile verticale paralele din 2
        v[l][col] = v[l][col + 3] = 1;
      }
      v[lin][col + 1] = v[lin][col + 2] = 1; /// varful 2-ului
    }else if(x == 3){
      v[lin][col + 1] = v[lin][col + 2] = 1; ///varful 3-ului
      v[lin + 6][col + 1] = v[lin + 6][col + 2] = 1; ///baza 3-ului

      for(int i = lin + 1;i <= lin + 5;i++){ ///centrul 3-ului
        if(i == lin + 3){
          v[i][col + 2] = 1; ///caz particular la mijlocul 3-ului
        }else{
          v[i][col] = v[i][col + 3] = 1; ///lini paralele
        }
      }
    }else if(x == 4){
      for(int l = lin, j = col + 2;j >= col;j--,l++){ ///diagonala din 4
        v[l][j] = 1;      
      }
      for(int j = col;j <= col + 3;j++){    ///centrul din 4
        v[lin + 3][j] = 1;
      }
      for(int l = lin + 4;l <= lin + 6;l++){ ///piciorul din 4
        v[l][col + 2] = 1;
      }
    }else if(x == 5){
      for(int j = col + 1;j <= col + 3;j++){ ///varful 5-lui
        v[lin][j] = 1;
      }
      v[lin + 1][col] = v[lin + 2][col] = 1; 
      v[lin + 3][col + 1] = v[lin + 3][col + 2] = 1;
      v[lin + 4][col + 3] = 1;
      v[lin + 5][col] = v[lin + 5][col + 3] = 1;
      v[lin + 6][col + 1] = v[lin + 6][col + 2] = 1;
    }else if(x == 6){ 
      v[lin][col + 1] = v[lin][col + 2] = 1;
      v[lin + 1][col] = v[lin + 1][col + 3] = 1;
      v[lin + 2][col] = 1;
      v[lin + 3][col] = v[lin + 3][col + 1] = v[lin + 3][col + 2] = 1;
      v[lin + 4][col] = v[lin + 4][col + 3] = 1;
      v[lin + 5][col] = v[lin + 5][col + 3] = 1;
      v[lin + 6][col + 1] = v[lin + 6][col + 2] = 1;
    }else if(x == 7){
      for(int j = col;j <= col + 3;j++){
        v[lin][j] = 1; ///varful 7-lui
      }
      v[lin + 1][col + 3] = 1;
      v[lin + 2][col + 2] = 1;
      v[lin + 3][col + 2] = 1;
      for(int l = lin + 4;l <= lin + 6;l++){
        v[l][col + 1] = 1;
      }
    }else if(x == 8){
      for(int l = lin;l <= lin + 6;l++){
        if(l == lin || l == lin + 3 || l == lin + 6){
          v[l][col + 1] = v[l][col + 2] = 1;
        }else{
          v[l][col] = v[l][col + 3] = 1;
        }
      }

    }else if(x == 9){
      v[lin][col + 1] = v[lin][col + 2] = 1;
      v[lin + 1][col] = v[lin + 1][col + 3] = 1;
      v[lin + 2][col] = v[lin + 2][col + 3] = 1;
      v[lin + 3][col + 1] = v[lin + 3][col + 2] = v[lin + 3][col + 3] = 1;
      v[lin + 4][col + 3] = 1;
      v[lin + 5][col] = v[lin + 5][col + 3] = 1;
      v[lin + 6][col + 1] = v[lin + 6][col + 2] = 1;
    }
  }

  int cnt = 0;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      if(v[i][j] == 1){
        cnt++;
      }
    }
  }

  g << cnt;

  f.close();
  g.close();

  return 0;

}
