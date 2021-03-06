/* Solutia e un pic diferita de cea explicata la ora
  Mai exact, in loc sa punem la inceput maximu si dupa tot in jurul lui, punem minimul si punem crescator in jurul lui
  Ca si suma, solutia e la fel de buna.
  Acum in caz de egaliate, punem in dreapta orice valoare in plus. Este valid asa, deoarece pastram tot timpul in dreapta sirul "mai bun"

  Ca si completare, de obicei la chestiile legate de minim lexicografic, generezi de la stanga la dreapta, pentru ca atunci daca stii ca pe o pozitie pui minimul posibil stii ca e optim.

  O observatie importanta e ca sa pui tot timpul minimul posibil la stanga nu e tot timpul echivalent cu a pune tot timpul maximul posibile la dreapta

  Un exemplu pe alta problema, unde se vede mai clar, e urmatorul:

  Sa zicem ca avem o matrice de nxm cu valori de 0/1. Care e traseul minim lexicografic care trece doar prin 0-uri si o ia doar in jos sau in dreapta, si incepe din (1,1) si se termina in (n, n)
  (o celula (a,b) e considerata mai mica decat o celula(c,d) daca si numai daca a < c sau (a=c si b < d)).
  o ia doar in jos sau in dreapta, adica pentru oricare 2 celule consecutive (a,b) si (c,d), fie c = a + 1 si d = b, fie c = a si d = b + 1
  
  Sa zicem ca avem matricea asta
  0000
  0000
  0000
  0000

  pe matricea asta, daca punem tot timpul minimul posibil pe pozitia actuala, traseul ar fi
  (1,1) (1,2) (1,3) (1,4) (2,4) (3,4) (4,4)
  dar daca am lua de la sfarsit si am pune tot timpul maximul, ea ar fi:
  (1, 1), (2, 1), (3, 1), (4, 1), (4, 2), (4, 3), (4, 4)

  Acum daca tot v-am zis problema asta, va voi zice si cum sa o rezolvati:
  puteti defini un dp[i][j] = true daca din (i, j) poti ajunge in (n, m), false altfel
  Initial, peste tot unde v[i][j] = 1, dp[i][j] = false.
  Apoi, dp[i][j] = true daca dp[i + 1][j] sau dp[i][j + 1] sunt adevarate(adica daca ele pot ajunge, noi ne putem muta in ele si sa ajungem si noi).

  Acum ca sa generam traseul, pornim cu x=y=1
  daca dp[x][y + 1] = true, atunci o sa mergem in (x, y + 1) (pentru ca e mai mic lexicografic decat alternativa)
  daca dp[x + 1][y] = true, atunci mergem in (x + 1, y).
*/


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;///1e5=10^5
                     /// puteti folosi 1ek, cu precizarea ca cateodata doubleul nu e precis si nu da fix cat trebuie
                     /// 1e1,1e2,...,1e7 e perfect, mai merge 1e9, 1e8 nu sunt sigur, 1e18 merge, dar oricum pe acolo e cam imprecis
                     /// 1e17 = 999999999..
const int VMAX = 1e3;
int c;
int n;
int v[2 * NMAX + 5]; /// o sa il dublam
int a[NMAX + 5];
int tmp[NMAX + 5];

ifstream f("roboti2.in");
ofstream g("roboti2.out");

int best_orientation(int n,int a[], int l){ /// n e lungimea sirului, a e sirul, l e lungimea prefixului care contine valoarea minima
                                            /// functia va returna -1 daca prima orientare e mai buna
                                            /// 0 daca sunt echivalente(adica cazul 1,1,1,1,2)
                                            /// 1 daca a doua orientare e mai buna
  int i = l + 1; /// urmatoarea valoare din prima orientare
  int j = n;

  while(i <= n && j > l){
    if(a[i] != a[j]){
      if(a[i] < a[j]){
        return -1;
      }else{
        return 1;
      }
    }
    i++;
    j--;
  }
  return 0;
}

int main(){

  f >> c;
  f >> n;
  for(int i = 1; i <= n; i++) {
    f >> v[i];
  }

  for(int i = n + 1;i <= n * 2;i++){ ///dublam sirul
    v[i] = v[i - n];
  }

  if(c == 1){
    int ans = 0; /// ans de la answer adica raspuns
    int lungime_curenta = 0;

    for(int i = 1;i <= 2 * n;i++){
      if(v[i - 1] >= v[i]){
        lungime_curenta = 0;  ///am seta cat luam in continuare din lungemea anterioara
      }
      lungime_curenta++; ///am adauga valoarea curenta la secventa curenta
      ans = max(ans, lungime_curenta);
    }

    g << ans;
  }else{
    sort(v + 1, v + 1 + n); /// o sa luam in considerare doar primele n

    a[1] = v[1];
    int l = n;
    int r = 2;

    for(int i = 2;i <= n;i++){
      if(a[l % n + 1] < a[r - 1]){
        a[l--] = v[i];
      }else{
        a[r++] = v[i];
      }
    }

    int valoare_minima = 1005;
    l = r = 0;

    for(int i = 1;i <= n;i++){ ///extragem intevalul pe care se afla valoarea minima
      if(a[i] < valoare_minima){
        valoare_minima = a[i];
        l = r = i;
      }else if(a[i] == valoare_minima){
        r++;
      }
    }

    for(int i = 1;i <= n;i++){ ///muta secventa de minime la inceput
      tmp[i] = a[(i - 2 + l) % n + 1];/// vrem sa afla a k-a pozitie dintr-un sir circular
                                      /// avem indicii [1...n], si noi vrem pentru un k arbitrar sa afla a cata pozitie din sir e
                                      /// [1..3] si am vrea pozitia 10 -> pozitia 1
                                      /// mai intai scadem 1 din pozitia actuala, si ce face asta e ca indexeaza si sirul de la 0
                                      /// daca vrem sa afla a k-a pozitia indexata de la 1, e ca si cum am afla pozitia k - 1 indexata de la 0
                                      ///[0..n - 1] vrem sa aflam pozitia k - 1
                                      ///(k - 1) % n
                                      ///ca sa reindexam de la 1, atunci adaugam 1
                                      ///(k - 1) % n + 1
                                      ///ca sa aflam a k pozitie pornind de la un i
                                      ///vrem sa aflam pozitia i + k - 1(indexata de la 0)
                                      ///de exemplu, daca k = 1, vrem prima pozitie incepand de la i, adica pe i
                                      ///(i + k - 2) % n + 1
    }
    for(int i = 1;i <= n;i++){ ///copiem in sirul original
      a[i] = tmp[i];
    }

    ///intrebarea e care orientare e mai buna
    ///avem secventa [1..r - l + 1] fixata, in ambele va fi asa
    ///intr-o orientare o sa avem urmatorile valoari = a[r - l + 2], a[r - l + 3], ....
    ///in cealalta orientare avem urmatoarile valori = a[n], a[n - 1], a[n - 2], ...
    ///verificam a[r - l + 2] fata de a[n]
    ///verificam a[r - l + 3] fata de a[n - 1]
    ///...
    
    if(best_orientation(n, a, r - l + 1) <= 0){ /// prima orientare e mai buna sau sunt echivalente
      for(int i = 1;i <= n;i++){
        g << a[i] << " ";
      }
    }else{
      for(int i = 1;i <= r - l + 1;i++){ /// prefixul de minime
        g << a[i] << " ";
      }
      for(int i = n;i > r - l + 1;i--){
        g << a[i] << " ";
      }
    }
  }

  f.close();
  g.close();

  return 0;

}
    
    /* 

    for(int i = 2;i <= n;i++){
      if(a[l % n + 1] >= a[r - 1]){///l % n + 1 se evalueaza la indiciele din dreapta celui curent pe sir circular cu indici [1..n]
                                  ///l % n -> [1...n-1, 0]
                                  ///l % n + 1 -> [2...n, 1] putem observa ca e urmatoru indice
                                  ///la r nu e nevoie sa facem asta, deoarece r nu o sa fie niciodata 1
                                  ///daca totusi r putea sa fie 1, si doream valoarea din stanga lui
                                  ///pe asta am fi obtinut-o ca si (l + n - 2) % n + 1
                                  ///[1..n] -> [n + 1...2n] -> [n - 1, n, ... 2n - 2] -> [n - 1, 0, 1, ..., n - 2] -> [n, 1, 2, ..., n - 1]
        a[l--] = v[i];
      }else{
        a[r++] = v[i];
      }
    }
*/
