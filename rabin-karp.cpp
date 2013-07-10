#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// @include
const int base = 26, mod = 997;

int rabin_karp(const string &t, const string &s) {
  if (s.size() > t.size()) {
    return -1;  // s is not a substring of t
  }

  int t_hash = 0, s_hash = 0;  // hash codes for the substring of t and s
  int power_s = 1;  // the modulo result of base^|s|
  for (int i = 0; i < s.size(); ++i) {
    power_s = i ? power_s * base % mod : 1;
    t_hash = (t_hash * base + t[i]) % mod;
    s_hash = (s_hash * base + s[i]) % mod;
  }

  for(int i = s.size(); i < t.size(); ++i) {
    // In case of hash collision but two strings are not equal, check the
    // two substrings are actually equal or not
    if (t_hash == s_hash && !t.compare(i - s.size(), s.size(), s)) {
      return i - s.size();  // find a match
    }
    
    // Use rolling hash to compute the new hash code
    t_hash -= (t[i - s.size()] * power_s) % mod;
    if (t_hash < 0) {
      t_hash += mod;
    }
    t_hash = (t_hash * base + t[i]) % mod;
  }

  // Try to match s and t[t.size() - s.size() : t.size() - 1].
  if (t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0) {
    return t.size() - s.size();
  }
  return -1;  // s is not a substring of t
}
// @exclude

int check_answer(const string &t, const string &s) {
  for (int i = 0; i + s.size() - 1 < t.size(); ++i) {
    bool find = true;
    for (int j = 0; j < s.size(); ++j) {
      if (t[i + j] != s[j]) {
        find = false;
        break;
      }
    }
    if (find == true) {
      return i;
    }
  }
  return -1;  // find no matching
}

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += rand() % 26 + 'a';
  }
  return ret;
}

int main(int argc, char *argv[]) {
  //srand(time(nullptr));
  if (argc == 3) {
    string t = argv[1];
    string s = argv[2];
    cout << "t = " << t << endl;
    cout << "s = " << s << endl;
    assert(rabin_karp(t, s) == check_answer(t, s));
  } else {
    for (int times = 0; times < 100000; ++times) {
      string t = rand_string(1 + rand() % 1000);
      string s = rand_string(1 + rand() % 20);
      cout << "t = " << t << endl;
      cout << "s = " << s << endl;
      int ret1 = rabin_karp(t, s);
      int ret2 = check_answer(t, s);
      cout << ret1 << " " << ret2 << endl;
      assert(rabin_karp(t, s) == check_answer(t, s));
    }
  }
  return 0;
}
