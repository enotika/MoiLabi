#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
const int kThird = 6;

int main() {
  const regex regular("^([A-Fa-f\\d]{2}:){5}[A-Fa-f\\d]{2}$");
  string s;
  cout << "enter name of file" << endl;
  cin >> s;
  ifstream fin;
  fin.open(s);
  if (!fin) {
    cout << "Can't find this file";
    return 0;
  }
  vector<string> adress;
  while (fin >> s) {
    const vector<smatch> matches{
        sregex_iterator{s.cbegin(), s.cend(), regular},
        sregex_iterator{}
    };
    for (auto to: matches) {
      adress.push_back(to.str());
    }
  }
  fin.close();
  string number;
  cout << "enter number " << endl;
  cin >> number;
  for (auto to: adress) {
    if (to[kThird] == number[0] && to[kThird + 1] == number[1]) {
      cout << to << endl;
    }
  }
  return 0;
}
