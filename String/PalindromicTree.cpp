const int maxn = 2e5 + 5;

struct PTree {
      int child[27], len, sufflink;
      long long numPal;
      PTree(int len = 0, int sufflink = 0, long long numPal = 0LL)
            : len(len) , sufflink(sufflink) , numPal(numPal) {
                  memset(child, 0, sizeof child);
            }
};

PTree Tree[maxn];
int num;  // total nodes in the tree
int suff; // current node 
string s;

void init() {
      for (int i = 0; i < maxn; i++) {
            Tree[i] = PTree();
      }
      num = suff = 2;
      Tree[1].len = -1; Tree[1].sufflink = 1;
      Tree[2].len = 0; Tree[2].sufflink = 1;
}

bool addLetter(string &s, int pos) {
      int cur = suff, curlen = 0;
      int let = s[pos] - 'a';
      while (true) {
            curlen = Tree[cur].len;
            if (pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) {
                  break;
            }
            cur = Tree[cur].sufflink;
      }
      if (Tree[cur].child[let]) {
            suff = Tree[cur].child[let];
            return false;
      }
      ++num;
      suff = num;
      Tree[num].len = Tree[cur].len + 2;
      Tree[cur].child[let] = num;
      if (Tree[num].len == 1) {
            Tree[num].sufflink = 2;
            Tree[num].numPal = 1;
            return true;
      }
      while (true) {
            cur = Tree[cur].sufflink;
            curlen = Tree[cur].len;
            if (pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) {
                  Tree[num].sufflink = Tree[cur].child[let];
                  break;
            }
      }
      Tree[num].numPal = 1 + Tree[ Tree[num].sufflink ].numPal;
      return true;
}
