#include <vector>
#include <iostream>
#include <iomanip>

struct Fen {

	std::vector< std::vector < std::vector<int> > > s;

	Fen(int n)
	{
		s = std::vector<std::vector<std::vector<int>>>(n, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));
		return;
	}

	int PrSum(int i1, int j1, int k1) const {
		int result = 0;

		for (int i = i1; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = j1; j >= 0; j = (j & (j + 1)) - 1)
        for (int k = k1; k >= 0; k = (k & (k + 1)) - 1)
          result += s[i][j][k];
		return result;
	}

	int RgSum(int li, int lj, int lk, int ri, int rj, int rk) const {
    if (li == 0 && lj == 0 && lk == 0)
      return PrSum(ri, rj, rk);
    else{
      int BigCube = PrSum(ri, rj, rk);

      int MiddleCubes = PrSum(li - 1, rj, rk) + PrSum(ri, lj - 1, rk) + PrSum(ri, rj, lk - 1);
      int SmallCubes = PrSum(li - 1, lj - 1, rk) + PrSum(li - 1, rj, lk - 1) + PrSum(ri, lj - 1, lk - 1);

      int MittleCube = PrSum(li - 1, lj - 1, lk - 1);
      return BigCube - MiddleCubes + SmallCubes - MittleCube;
    }
	}

	void Up(int i1, int j1, int k1, int add) {
		for (int i = i1; i < s.size(); i = (i | (i + 1)))
      for (int j = j1; j < s.size(); j = (j | (j + 1)))
        for (int k = k1; k < s.size(); k = (k | (k + 1)))
          s[i][j][k] += add;

    return;
	}
};

int main()
{
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
	Fen Sky(n);
	int cmd = 0;
	int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	std::cin >> cmd;
	while(cmd != 3){
    if(cmd == 2) {
      std::cin >> tmp1 >> tmp2 >> tmp3 >> tmp4 >> tmp5 >> tmp6;
      std::cout << Sky.RgSum(tmp1, tmp2, tmp3, tmp4, tmp5, tmp6) << std::endl;
    } else {
      std::cin >> tmp1 >> tmp2 >> tmp3 >> tmp4;
      Sky.Up(tmp1, tmp2, tmp3, tmp4);
    }
    std::cin >> cmd;
	}

	return 0;
}
