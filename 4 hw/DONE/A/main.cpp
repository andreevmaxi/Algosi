#include <vector>
#include <iostream>
#include <iomanip>

struct Fen{
	std::vector<int> s;

	Fen(std::vector<int> ar){
		s = std::vector<int>(ar.size() + 1, 0);
		for (int i = 0; i < ar.size(); i++)
			s[i + 1] = ar[i];

		for (int i = 1; i < s.size(); i++)
		{
			int i2 = i + (i & -i);
			if (i2 < s.size())
				s[i2] += s[i];
		}

		return;
	}

	int PrSum(int i){
		int result = 0;
		for (++i; i > 0; i -= i & -i) {
			result += s[i];
		}
		return result;
	}

	int RgSum(int l, int r){
    if (l == 0)
      return PrSum(r);
    else
      return PrSum(r) - PrSum(l - 1);
	}

  int NillSr(int l, int r, int k, int Start){
    int NowK;
    if(Start){
      NowK = Start;
    } else {
      NowK = RgSum(l, r);
    }
    if(Start > 0 || NowK >= k) {
      if(l == r){
        return l;
      }
      int delta = RgSum(l, (r+l)/2);
      if(delta >= k){
        return NillSr(l, (r+l)/2, k, delta);
      } else {
        return NillSr((r+l)/2 + 1, r, k - delta, NowK - delta);
      }
    } else {
      return -2;
    }
  }

	void Up(int i, int New, int Old){
    if(New != Old){
      int add;
      if(New == 1){
        add = 1;
      } else {
        add = -1;
      }

      for (++i; i < s.size(); i += i & -i)
        s[i] += add;

    }
    return;
	}
};

int main()
{
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int N;
  std::cin >> N;
  std::vector<int> a;
  a.resize(N);
  for(int i = 0; i < N; ++i){
    int tmp;
    std::cin >> tmp;
    if(tmp == 0){
      a[i] = 1;
    } else {
      a[i] = 0;
    }
  }
	Fen tr(a);
  int M;
  std::cin >> M;
  for(int i = 0; i < M; ++i){
    char tmp;
    std::cin >> tmp;

    int t1, t2, t3;
    if(tmp == 'u'){
      std::cin >> t1 >> t2;
      if(t2 == 0){
        t2 = 1;
      } else {
        t2 = 0;
      }
      tr.Up(t1-1, t2, a[t1-1]);
      a[t1-1] = t2;
    } else {
      std::cin >> t1 >> t2 >> t3;
      std::cout << tr.NillSr(t1 - 1, t2 - 1, t3, 0) + 1 << " ";
    }
  }

  return 0;
}
