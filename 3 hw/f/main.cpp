#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
  int m,k,s;
  long long n,e;
  cin >> n >> m >> k;
  string ques;
  vector<set <long long>> base(m + 1);
  map <long long, set<int>> point;
  for(int i = 0; i < k; ++i){
    cin >> ques;

    if(ques == "ADD"){
      cin >> e >> s;
      base[e].insert(s);
      point[s].insert(e);
    } else if(ques == "DELETE") {
      cin >> e >> s;
      base[e].erase(s);
      point[s].erase(e);
    } else if(ques == "CLEAR") {
      cin >> s;
      for(auto j : base[s])
        point[j].erase(s);
      base[s].clear();
    } else if(ques == "LISTSET") {
      cin >> s;
      if(base[s].empty()){
        cout << -1;
      } else {
        for(auto j : base[s]){
          cout << j << " ";
          ++j;
        }
      }
      cout << endl;
    } else {
      cin >> e;
      if(point[e].empty()){
        cout << -1;
      } else {
        for(auto j : point[e])
          cout << j << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
