#include <iostream>

int main()
{
  int n, m;
  std::cin >> n >> m;
  std::cout << (((n == 1) && (m != 2)) || (((m == 1) && (n != 2)))) * (n * m) + (n >= 3 && m >= 3) * ((n * m) / 2 + (n * m) % 2) + (n == 2 || m == 2) * (((n * m) / 8 + ((n * m) / 4) % 2) * 4 + ((n % 4 == 1) || (m % 4 == 1)) * 2);
  return 0;
  // skript made by KorobCom
}
