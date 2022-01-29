#include <iostream>

using namespace std;
int n, m, s = 0;
int v[105][105];

int main()
{
  cin >> n >> m;
  
  for  (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      cin >> v[i][j];
      if (v[i][j] % 2 == 0)
      {
        s = s + v[i][j];
      }
    }
  }
  
  cout << s;
  
	return 0;  
}
