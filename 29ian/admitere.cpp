#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

const int NMAX = 2000;
const int MMAX = 2000;
const int VMAX = 4000; // nota maxima

/*

pair<>
vector<>

pair<T1,T2> a;
T1 si T2 sunt tipuri
pair<int,int> a;
pair<double, int> a;
pair<char*, int**> a;
a.first -> prima chestie
a.second -> a doua chestie

vector<T> v;
vector<int> v; ///tine inturi

v = {};

v.push_back(elem);

v.push_back(1); /// pe pozitia 0
v.push_back(2); /// pe pozitia 1
v.push_back(3); /// pe pozitia 2
v = {1,2,3};
for(int i = 0;i < v.size();i++){
  cout << v[i];
}

*/

int c;
int n, m;
pair<int,int> v[2][NMAX + MMAX + 5]; /// sa tina perechi de genul (nota elevului, 0 daca nu e privilegiat, altfel 1);
                                     /// v[i][j] -> al j-lea elev in ordine sortata de la clasa i(0 -> real, 1...n -> indicele elevului)
int pos[VMAX + 5];  /// pos[i] = indicele elevului privilegiat care are nota i la uman
bool active[NMAX + 5]; /// true daca elevul curent e considerat la real, false altfel
char ans[NMAX + 5];


ifstream f("admitere.in");
ofstream g("admitere.out");

int get_count(int n, pair<int,int> v[]){ ///cati elevi privilegiati pot sa intre aici
  int ans = 0;

  for(int i = 1;i <= n;i++){
    if(v[i].second > 0){
      ans++;
    }
  }
  return ans;
}

int get_count_of_uman(int n, pair<int,int> v[]){ /// n = dimensiunea, v = vector de perechi (nota, indice)
  int ans = 0;
  int available_space = m; ///vrem sa numaram si cei care initial intra la uman
  for(int i = 1;i <= n + m;i++){
    if(active[v[i].second] == true){
      continue; /// da skip la restul forului
    }
    available_space--;
    if(available_space < 0){
      break;
    }
    if(v[i].second > 0){
      ans++;
    }
  }
  return ans;
}

int main(){
  
  f >> c;
  f >> n >> m;

  for(int i = 1;i <= m;i++){
    f >> v[0][i].first;
    v[0][i].second = 0;
  }
  
  for(int i = 1;i <= m;i++){
    f >> v[1][i].first;
    v[1][i].second = 0;
  }

  for(int i = 1;i <= n;i++){
    int x, y;
    f >> x >> y;
    v[0][i + m] = {x, i}; ///pair se poate face atribuire si asa
                          ///{ {1,2},1} cateodata nu merge
    v[1][i + m] = make_pair(y, i); /// echivalent cu {y, i}
    pos[y] = i;
  }

  sort(v[0] + 1, v[0] + 1 + n + m);
  reverse(v[0] + 1, v[0] + 1 + n + m);
  
  sort(v[1] + 1, v[1] + 1 + n + m);
  reverse(v[1] + 1, v[1] + 1 + n + m);
 
  if(c == 1){
    for(int i = 1;i <= n;i++){
      ans[i] = 'X';
    }
    if(get_count(m, v[0]) > get_count(m, v[1])){
      g << get_count(m, v[0]) << "\n"; 
      for(int i = 1;i <= m;i++){
        ans[v[0][i].second] = 'R'; /// pentru ca la primele m le-am atribuit .second=0, nu ne incurca aici
      }
      g << (ans + 1);
    }else{
      g << get_count(m, v[1]) << "\n"; 
      for(int i = 1;i <= m;i++){
        ans[v[1][i].second] = 'U';
      }
      g << (ans + 1);
    }
  }else{
    ///putem observa ca un elev o data mutat de la real spre uman nu se mai muta inapoi
    int cnt_active = 0; /// numarul de elevi privilegiati de la real
    int best_split = m; /// va tine minte i-ul pentru care avem cat mai multi elevi admisi
    int best_value = 0; ///va tine minte numarul de elevi pentru best_i
    for(int i = 1;i <= m;i++){
      if(v[0][i].second > 0){
        active[v[0][i].second] = true;
        cnt_active++;
        best_value++;
      }
    }

    best_value += get_count_of_uman(n + m, v[1]);

    for(int i = m + 1;i <= n + m;i++){ ///variem ultima medie de la real
      ///sa bagam elevul actual in cei admisi
      if(v[0][i].second > 0){
        active[v[0][i].second] = true;
        cnt_active++;
      }
      ///trebuie sa dam afara un elev privilegiat
      if(cnt_active == 0){ ///daca nu mai avem elevi privilegiati
        break;
      }
      for(int i = VMAX;i >= 0;i--){
        if(pos[i] > 0 && active[pos[i]]){///daca am gasit un elev activ cu cea mai mare media la uman
          active[pos[i]] = false;
          cnt_active--;
          break;
        }
      }
      int local_ans = cnt_active + get_count_of_uman(n + m, v[1]); /// raspunsul pentru i-ul curent
      if(local_ans > best_value){
        best_value = local_ans;
        best_split = i;
      }
    }

    g << best_value << "\n";
  
    for(int i = 1;i <= m;i++){
      if(v[0][i].second > 0){
        active[v[0][i].second] = true;
      }
    }

    for(int i = m + 1;i <= best_split;i++){
      if(v[0][i].second > 0){
        active[v[0][i].second] = true;
      }
      for(int i = VMAX;i >= 0;i--){
        if(pos[i] > 0 && active[pos[i]]){///daca am gasit un elev activ cu cea mai mare media la uman
          active[pos[i]] = false;
          cnt_active--;
          break;
        }
      }
    }

    for(int i = 1;i <= n;i++){
      ans[i] = 'X';
    }

    int available_space = m;
    for(int i = 1; i <= n + m;i++){
      if(v[0][i].second > 0 && active[v[0][i].second] == false){
        continue;
      }
      available_space--;
      if(available_space < 0){
        break;
      }
      if(v[0][i].second > 0){
        ans[v[0][i].second] = 'R';
      }
    }
    available_space = m;
    for(int i = 1;i <= n + m;i++){
      if(v[1][i].second > 0 && active[v[1][i].second] == true){
        continue;
      }
      available_space--;
      if(available_space < 0){
        break;
      }
      if(v[1][i].second > 0){
        ans[v[1][i].second] = 'U';
      }
    }

    g << ans + 1;
  }

  f.close();
  g.close();

  return 0;
}
