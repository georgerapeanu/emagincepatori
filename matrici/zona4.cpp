///Varianta 1 - https://www.pbinfo.ro/probleme/1749/zona4
#include <iostream>

using namespace std;
int n, Z;
int v[205][205];

int main()
{
		cin >> n >> Z;
  for (int i = 1; i<=n; i++)
  {
    for (int j = 1; j<=n; j++)
    {
      cin >> v[i][j];
    }
  }

  int suma = 0;

  for(int i = 1; i <= n; i++)
  {
    for(int j = 1; j <= n; j++)
    {
      if(Z == 1)
      {
        if(j > i && j < n + 1 - i)
        {
          suma += v[i][j];
        }
      }
      else if(Z == 2)
      {
        if(j > i && j > n + 1 - i){
          suma += v[i][j];
        }
      }
      else if(Z == 3)
      {
        if(j < i && j > n + 1 - i){
          suma += v[i][j];
        }
      }
      else
      {
        if(j < i && j < n + 1 - i){
          suma += v[i][j];
        }
      }
    }
  }

  cout << suma << "\n";

  return 0;
}
