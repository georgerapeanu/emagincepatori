#include <fstream>

using namespace std;

const int NMAX = 1000;
const int MMAX = 1000; /// constantele problemei

int c;
int n, m;
int h[NMAX + 5][MMAX + 5]; /// matricea de inaltimi pentru ace

ifstream f("ace.in");
ofstream g("ace.out");

/*

int a = 2, b = 6;

while(b != 0){
  int r = a % b;
  a = b;
  b = r;
}

///cmmdc = a

*/


int gcd(int a, int b){ ///gcd = greatest common divisor = cmmdc
  if(b == 0){ /// (a,0) = a
    return a;
  }
  return gcd(b, a % b); 
}

bool acopera(int x1, int y1, int x2, int y2){
  return x1 * y2 - x2 * y1 <= 0; /// prima data evalueaza x1 * y2 - x2 * y1
                                 /// evalueaza valoarea expresiei ^ si o compara cu 0
                                 ///if(conditie) /// if(a <= b)
                                 /// evalueaza a<=b -> returneaza true sau false
                                 ///if(true)
                                 ///in cazul asta, evalueaza conditia, si returneaza true sau false
}

int process(int dx, int dy){ /// returneaza numarul de ace vizibile, de pe directia (dx, dy)
                             /// (n - dx, m - dy)
  int best_ac_x = 0;
  int best_ac_y = 0;
  int raspuns = 0;
  int i = n - dx; /// suntem pe linia n - dx
  int j = m - dy; /// suntem pe coloana m - dy

  int current_x = 1;

  while(i >= 1 && j >= 1){ ///cat timp suntem in matrice
    ///coordonatele acului actual sunt current_x, h[i][j] in plan
    int x = current_x;
    int y = h[i][j];

    if(best_ac_x == 0){ ///daca primul ac nu a fost inca initializat
      raspuns++;
      best_ac_x = x;
      best_ac_y = y;
    }else if(acopera(best_ac_x, best_ac_y, x, y) == false){
      raspuns++;
      best_ac_x = x;
      best_ac_y = y;
    }

    current_x++;///pregatim coordonatele urmatorului ac
    i -= dx;
    j -= dy;
  }

  return raspuns;
}

int main(){

  f >> c;
  f >> n >> m;
  
  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      f >> h[i][j];
    }
  }
  
  if(c == 1){
    g << process(0, 1) + process(1, 0); /// 0, 1 le va procesa pe (n - 0, m - 1), (n - 0, m - 2), ... adica directia V
                                           /// 1, 0 le va procesa pe (n - 1, m - 0), (n - 2, m - 0), ... adica directia N
                                           /// O(n + m)
  }else{
    int raspuns = 0;///O(n * m)
    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= m;j++){
        if(gcd(n - i, m - j) == 1){ /// daca acul curent este primul de pe directia lui
          raspuns += process(n - i, m - j);
        }
      }
    }
    g << raspuns;
  }
  
  f.close();
  g.close();

  return 0;
}
