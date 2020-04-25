int manacher(const string &s) {
      int n = s.size();
      vector < vector <int> > p(2, vector <int> (n, 0));
      for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0) {
            for (int i = 0; i < n; i++) {
                  if (i < r) {
                        p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
                  }
                  int L = i - p[z][i];
                  int R = i + p[z][i] - !z;
                  while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) {
                        p[z][i]++;
                        L--;
                        R++;
                  }
                  if (R > r) {
                        l = L;
                        r = R;
                  }
            }
      }
      int maxPal = *max_element(p[0].begin(), p[0].end()) * 2;
      maxPal = max(maxPal, *max_element(p[1].begin(), p[1].end()) * 2 + 1);
      return maxPal;
}
