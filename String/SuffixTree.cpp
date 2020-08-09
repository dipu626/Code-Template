/*
      Algorithm : Suffix Tree
      Tutorial  : https://cp-algorithms.com/string/suffix-tree-ukkonen.html
                  https://www.geeksforgeeks.org/ukkonens-suffix-tree-construction-part-1/?ref=lbp
                  https://codeforces.com/blog/entry/16780
                  
      Visualization : https://brenden.github.io/ukkonen-animation/
      
      Structure Details : 
                              Root = 0
                              l    = starting index of the substring
                              r    = ending index of the substring + 1
                            
      Problem   : https://codeforces.com/contest/427/problem/D
      Statement : Given two strings s1 and s2 consist of lowercase Latin letters, find the smallest (by length) 
                  common substring p of both s1 and s2, where p is a unique substring in s1 and also in s2. 
      
*/

struct SuffixTree {
      struct Node {
            int l;
            int r;
            int par;
            int link;
            map <char, int> child;
            Node(int l = 0, int r = 0, int par = -1)
                  : l(l), r(r), par(par), link(-1) {
                        child.clear();
                  }

            void clean() {
                  l = 0;
                  r = 0;
                  par = -1;
                  link = -1;
                  child.clear();
            }
            int len() {
                  return r - l;
            }
            int &get(char c) {
                  if (child.count(c) == 0) {
                        child[c] = -1;
                  }
                  return child[c];
            }
      };

      struct State {
            int v;
            int pos;
            State() {}
            State(int v, int pos)
                  : v(v), pos(pos) {}
      };

      string s;
      int n;
      int SZ;
      vector <Node> stree;
      State ptr;

      SuffixTree() {}

      void init(string &str) {
            s = str;
            n = str.size();
            stree.clear(); stree.resize(4 * n + 5);
      }
      State go(State st, int l, int r) {
            while (l < r) {
                  if (st.pos == stree[st.v].len()) {
                        st = State(stree[st.v].get(s[l]), 0);
                        if (st.v == -1) {
                              return st;
                        }
                  }
                  else {
                        assert(stree[st.v].l + st.pos >= 0);
                        if (s[ stree[st.v].l + st.pos ] != s[l]) {
                              return State(-1, -1);
                        }
                        if (r - l < stree[st.v].len() - st.pos) {
                              return State(st.v, st.pos + r - l);
                        }
                        l += stree[st.v].len() - st.pos;
                        st.pos = stree[st.v].len();
                  }
            }
            return st;
      }
      int split(State st) {
            if (st.pos == stree[st.v].len()) {
                  return st.v;
            }
            if (st.pos == 0) {
                  return stree[st.v].par;
            }
            Node v = stree[st.v];
            int id = SZ++;
            stree[id] = Node(v.l, v.l + st.pos, v.par);
            stree[v.par].get(s[v.l]) = id;
            stree[id].get(s[v.l + st.pos]) = st.v;
            assert(st.v >= 0);
            stree[st.v].par = id;
            stree[st.v].l += st.pos;
            return id;
      }
      int get_link(int v) {
            if (stree[v].link != -1) {
                  return stree[v].link;
            }
            if (stree[v].par == -1) {
                  return 0;
            }
            int to = get_link(stree[v].par);
            return stree[v].link = split(go(State(to, stree[to].len()), stree[v].l + (stree[v].par == 0), stree[v].r));
      }
      void tree_extend(int pos) {
            for(;;) {
                  State nptr = go(ptr, pos, pos + 1);
                  if (nptr.v != -1) {
                        ptr = nptr;
                        return;
                  }
                  int mid = split(ptr);
                  int leaf = SZ++;
                  stree[leaf] = Node(pos, n, mid);
                  stree[mid].get(s[pos]) = leaf;
                  ptr.v = get_link(mid);
                  ptr.pos = stree[ptr.v].len();
                  if (!mid) {
                        break;
                  }
            }
      }
      void build_tree() {
            SZ = 1;
            ptr = {0, 0};
            for (int i = 0; i < stree.size(); i++) {
                        stree[i].clean();
            }
            for (int i = 0; i < n; i++) {
                  tree_extend(i);
            }
      }
};

SuffixTree st;
string s1;
string s2;
int len1;
int len2;

int dfs(int u = 0) {
      int mini = INF;
      vector <int> go;
      for (auto it : st.stree[u].child) {
            char ch = it.first;
            int v = it.second;
            go.push_back(v);
      }
      int len = go.size();
      if (len < 2) {
            return mini;
      }
      if (len == 2) {
            int pos1 = st.stree[ go[0] ].l;
            int pos2 = st.stree[ go[1] ].l;
            if (pos1 > pos2) {
                  swap(pos1, pos2);
            }
            if (st.stree[ go[0] ].r == st.n && st.stree[ go[1] ].r == st.n) {
                  if (pos1 <= len1 and pos2 > len1) {
                        return 1;
                  }
                  return mini;
            }
      }
      for (int v : go) {
            mini = min(mini, st.stree[u].len() + dfs(v));
      }
      return mini;
}

signed main()
{
      cin >> s1 >> s2;
      len1 = s1.size();
      len2 = s2.size();
      string str = s1 + "#" + s2 + "$";
      st.init(str);
      st.build_tree();
      int ans = dfs();
      if (ans == INF) {
            ans = -1;
      }
      cout << ans;
}
