#include <iostream>
using namespace std;
int64_t Tmax(int64_t n) {
  int64_t res;
  if (n <= 1) {
    cerr << "wrong value of n" << endl;
    res = 0;
  } else if (n == 2) {
    res = 1;
  } else {
    res = n/2 + 2;
  }
  return res;
}
int64_t Tsum(int64_t n) {
  int64_t res, n_2, n_3;
  n_2 = n*n;
  n_3 = n_2*n;
  if (n <= 1) {
    cerr << "wrong value of n" << endl;
    res = 0;
  } else if (n == 2) {
    res = 1;
  } else if (n % 2 == 1){
    res = (4*n_3 + 27*n_2 - 124*n + 165)/24;
  } else {
    res = (4*n_3 + 27*n_2 - 130*n + 192)/24;
  }
  return res;
}
double Tmean(int64_t sum, int64_t num) {
  return double(sum) / double(num);
}
int guess(int64_t a, int64_t b, int depth) {
  int c = -1;
  while (c < 0 || c > 2) {
    cout << "AI " << depth << " times Guess " << a-1 << ", " << b-1 << endl;
    cout << "c = ? (0~2) -->";
    cin >> c;
  }
  return c;
}
void say_err() {
  cerr << "something error" << endl;
}
// S game solver when n <= 3
int Sgame3(int64_t a, int64_t n, int depth) {
  int c = guess(n, a, depth);
  if (n == 1) {
    if (c != 2) {
      say_err();
      return 0;
    }
  } else {
    if (c == 0) {
      say_err();
      return 0;
    }
    else if (c == 1) {
      return Sgame3(a, n-1, depth+1);
    }
  }
  return depth;
}
// S game solver
int Sgame(int64_t a, int64_t n, int depth) {
  int c;
  if (n <= 3) {
    return Sgame3(a, n, depth);
  }
  c = guess(n-1, n, depth);
  if (c == 2) {
    say_err();
    return 0;
  } else if (c == 1) {
    c = guess(n, a, depth+1);
    if (c == 2) {
      return depth+1;
    } else if (c == 1) {
      c = guess(n-1, a, depth+2);
      if (c != 2) {
        say_err();
        return 0;
      }
      return depth+2;
    }
  } else {
    return Sgame(a, n-2, depth+1);
  }
  return depth;
}
// SL game solver when n <= 4
int SLgame4(int64_t a, int64_t b, int64_t c, int64_t n, int depth) {
  int cc = guess(n, a, depth);
  if (cc == 0) {
    cc = guess(c, b, depth+1);
    if (cc != 2) {
      say_err();
      return 0;
    }
    return depth+1;
  } else if (cc == 1) {
    return Sgame(a, n-1, depth+1);
  }
  return depth;
}
// SL game solver
int SLgame(int64_t a, int64_t b, int64_t c, int64_t n, int depth) {
  if (n <= 4) {
    return SLgame4(a, b, c, n, depth);
  }
  return depth;
}
// SS game solver when SS game get 1c
int SSgame1c(int64_t a, int64_t b, int64_t c, int64_t d, int depth) {
  int cc = guess(a, c, depth);
  if (cc == 0) {
    cc = guess(b, c, depth+1);
    if (cc != 2) {
      say_err();
      return 0;
    }
    return depth+1;
  } else if (cc == 1) {
    cc = guess(a, d, depth+1);
    if (cc == 0) {
      cc = guess(b, c, depth+2);
      if (cc != 2) {
        say_err();
        return 0;
      }
      return depth+2;
    } else if (cc == 1) {
      say_err();
      return 0;
    }
    return depth+1;
  }
  return depth;
}
// SS game solver
int SSgame4(int64_t a, int64_t b, int64_t n, int depth) {
  int c;
  if (n == 1) {
    cerr << "not need" << endl;
    return 0;
  } else if (n == 2) {
    cerr << "not need but keep guess" << endl;
    return SSgame1c(a, b, 1, 2, depth);
  } else if (n == 3||n == 4) {
    c = guess(n, a, depth);
    if (c == 0) {
      return Sgame(b, n-1, depth+1);
    } else if (c == 1) {
      return SLgame(a, b, n, n-1, depth+1);
    }
  } else {
    say_err();
    return 0;
  }
  return depth;
}
// SS game solver
int SSgame(int64_t a, int64_t b, int64_t n, int depth) {
  int c;
  if (n <= 4) {
    return SSgame4(a, b, n, depth);
  }
  c = guess(n-1, n, depth);
  if (c == 0) {
    return SSgame(a, b, n-2, depth+1);
  } else if (c == 1) {
    return SSgame1c(a, b, n-1, n, depth+1);
  } else if (c == 2) {
    say_err();
    return 0;
  }
  return depth;
}
// C game solver when n <= 3
int Cgame3(int64_t n, int depth) {
  int c = guess(1, 2, depth);
  if (n == 2) {
    if (c != 2) {
      say_err();
      return 0;
    }
  } else if (n == 3) {
    if (c == 1) {
      return Sgame(3, 2, depth+1);
    } else if (c == 0) {
      say_err();
      return 0;
    }
  }
  return depth;
}
// C game solver
int Cgame(int64_t n, int depth) {
  int c;
  if (n <= 3) {
    return Cgame3(n, depth);
  }
  c = guess(n-1, n, depth);
  if (c == 0) {
    return Cgame(n-2, depth+1);
  } else if (c == 1) {
    return SSgame(n-1, n, n-2, depth+1);
  }
  return depth;
}
int64_t input() {
  int64_t n;
  while (true) {
    cout << "Please set value of n (0 for quit)-->";
    cin >> n;
    if (n == 0 || n >= 2) break;
    cout << "need n >= 2" << endl;
  }
  return n;
}
int main() {
  int64_t n, m, sum, num;
  double mean;
  while (true) {
    n = input();
    if (n == 0) {
      break;
    }
    m = Tmax(n);
    sum = Tsum(n);
    num = n*(n-1)/2;
    mean = Tmean(sum, num);
    cout << "max = " << m << endl;
    cout << "sum = " << sum << endl;
    cout << "mean = " << mean << endl;
    Cgame(n, 1);
  }
  return 0;
}