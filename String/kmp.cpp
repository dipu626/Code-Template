vector <int> LPS(string &pat) {
      int len = pat.size();
      int i = 1;
      int j = 0;
      vector <int> lps;
      lps.emplace_back(0);
      while (i < len) {
            if (pat[i] == pat[j]) {
                  i++;
                  j++;
                  lps.emplace_back(j);
            }
            else {
                  if (j) {
                        j = lps[j - 1];
                  }
                  else {
                        lps.emplace_back(0);
                        i++;
                  }
            }
      }
      return lps;
}

int kmp(string &s, string &pat) {
      vector <int> lps = LPS(pat);
      int id = 0;
      int cnt = 0;
      for (int i = 0; i < s.size(); i++) {
            while (id > 0 and s[i] != pat[id]) {
                  id = lps[id - 1];
            }
            if (s[i] == pat[id]) {
                  ++id;
            }
            if (id == pat.size()) {
                  cnt++;
                  id = lps[id - 1];
            }
      }
      return cnt;
}
