static const int maxn = 2e5 + 5;
static const int mod = 1e9 + 123;

int gen_base(const int before, const int after) {
      auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
      mt19937 mt_rand(seed);
      int base = uniform_int_distribution <int> (before, after)(mt_rand);
      return base % 2 == 0 ? base - 1 : base;
}

long long pow1[maxn];
unsigned long long pow2[maxn];
int base;

void preCalc() {
      assert(base < mod);
      pow1[0] = 1;
      pow2[0] = 1;
      for (int i = 1; i < maxn; i++) {
            pow1[i] = (1LL * pow1[i - 1] * base) % mod;
            pow2[i] = (pow2[i - 1] * base);
      }
}

struct Hash {
      vector <long long> pref1;
      vector <unsigned long long> pref2;
      Hash() {}
      Hash(const string &s) : pref1(s.size() + 1u, 0), pref2(s.size() + 1u, 0) {
            assert(base < mod);
            int n = s.size();
            for (int i = 0; i < n; i++) {
                  assert(base > s[i]);
                  pref1[i + 1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
                  pref2[i + 1] = pref2[i] + s[i] * pow2[i];
            }
      }
      // Polynomial hash of subsequence [pos, pos+len)
      // If mxPow != 0, value automatically multiply on base in needed power.
      // Finally base ^ mxPow
      // 0 - Indexed
      pair <long long, unsigned long long> getHash(int pos, int len, int mxPow = 0) {
            long long hash1 = pref1[pos + len] - pref1[pos];
            unsigned long long hash2 = pref2[pos + len] - pref2[pos];
            if (hash1 < 0) hash1 += mod;
            if (mxPow != 0) {
                  hash1 = 1LL * hash1 * pow1[mxPow - (pos + len - 1)] % mod;
                  hash2 = hash2 * pow2[mxPow - (pos + len - 1)];
            }
            return make_pair(hash1, hash2);
      }
};
