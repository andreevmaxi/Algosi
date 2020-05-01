#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

struct Fen {

	std::vector<long long> s;

	Fen(long long n)
	{
		s = std::vector<long long>(n, 0);

		return;
	}

	long long PrSum(long long i) const {
		long long result = 0;
		for (i; i >= 0; i = (i & (i + 1)) - 1) {
			result += s[i];
		}
		return result;
	}

	long long RgSum(long long l, long long r) const {
    if (l == 0)
      return PrSum(r);
    else
      return PrSum(r) - PrSum(l - 1);
	}

	void Up(long long i, long long add) {
		for (i; i < s.size(); i = (i | (i + 1)))
			s[i] += add;

    return;
	}
};

int main()
{
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int ind = 0;
  long long ans = 0;
	Fen b(1000000);
	int n;
	std::cin >> n;
	std::vector <std::pair <long long, int>> a;
	std::vector <long long> Nw;
	Nw.resize(n);
	a.resize(n);
	long long p[n];
	long long s[n];
	for(int i = 0; i < n; ++i){
    std::cin >> a[i].first;
    a[i].second = i;
	}
	std::sort(a.begin(), a.end());

  Nw[a[0].second] = ind;
  for(int i = 1; i < n; ++i){
    if(a[i].first != a[i - 1].first)
      ++ind;
    Nw[a[i].second] = ind;
  }

	for(int i = 0; i < n; ++i){
    b.Up(Nw[i], 1);
    p[i] = i + 1 - b.PrSum(Nw[i]);
  }
	Fen RevB(1000000);

	for(int i = n - 1; i >= 0; --i){
    RevB.Up(Nw[i], 1);
    ans += p[i] * RevB.PrSum(Nw[i] - 1);
	}
	std::cout << ans;
}
