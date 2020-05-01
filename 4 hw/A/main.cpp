#include <vector>
#include <iostream>
#include <iomanip>


struct Fen {

	std::vector<int> s;

	Fen(std::vector<int> ar)
	{
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

	int PrSum(int i) const {
		int result = 0;
		for (++i; i > 0; i -= i & -i) {i
			result += s[i];
		}
		return result;
	}

	int RgSum(int l, int r) const {
    if (l == 0)
      return PrSum(r);
    else
      return PrSum(r) - PrSum(l - 1);
	}

	void Up(int i, int add) {
		for (++i; i < s.size(); i += i & -i)
			s[i] += add;

    return;
	}
};

int main()
{
	Fen bit(array);
}
