struct Node {
      ll val, sum;
      int priority, sze;
      Node *lft, *rgt;
      Node(ll val = 0) {
            this->val = val;
            this->sum = val;
            this->priority = rand();
            this->sze = 1;
            this->lft = this->rgt = nullptr;
      }
};

typedef Node*             pnode;

int sz(pnode t) {
      return (t == nullptr ? 0 : t->sze);
}

void updateSize(pnode t) {
      if (t) {
            t->sze = sz(t->lft) + 1 + sz(t->rgt);
      }
}

void combine(pnode t) {
      t->sum = t->val;
      if (t->lft) {
            t->sum = (t->sum + t->lft->sum);
      }
      if (t->rgt) {
            t->sum = (t->sum + t->rgt->sum);
      }
}

void Split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
      // 'pos' goes to left subtree
      if (t == nullptr) {
            return void(l = r = nullptr);
      }
      int curr = sz(t->lft) + add;
      if (curr <= pos) {
            Split(t->rgt, t->rgt, r, pos, curr + 1);
            l = t;
      }
      else {
            Split(t->lft, l, t->lft, pos, add);
            r = t;
      }
      updateSize(t);
      combine(t);
}

void Merge(pnode &t, pnode l, pnode r) {
      if (l == nullptr or r == nullptr) {
            t = l ? l : r;
      }
      else if (l->priority < r->priority) {
            Merge(r->lft, l, r->lft);
            t = r;
      }
      else {
            Merge(l->rgt, l->rgt, r);
            t = l;
      }
      updateSize(t);
      combine(t);
}

pnode Insert(pnode t, pnode newnode, int pos) {  // 1 - indexed
      pnode L, R;
      Split(t, L, R, pos - 1);
      Merge(t, L, newnode);
      Merge(t, t, R);
      return t;
}

/*
      Note : If we want to erase whole array, then we should handle it
             separately as treap = nullptr. This Erase() function gives
             Runtime Error when we force it to erase whole array.
*/

pnode Erase(pnode t, int l, int r) { // 1 - indexed
      l--; // making 0 - indexed
      r--;
      pnode L, R, mid;
      Split(t, L, mid, l - 1);
      Split(mid, t, R, r - l);
      Merge(t, L, R);
      return t;
}

ll query(pnode t, int pos) {  // 1 - indexed
      if (t == nullptr || pos <= 0) {
            return 0;
      }
      pnode L, R;
      Split(t, L, R, pos-1);
      ll sum = L->sum;
      Merge(t, L, R);
      return sum;
}

ll kth(pnode t, int k) {   // 1 - indexed
      if (t == nullptr) {
            return -1;
      }
      int curr = sz(t->lft) + 1;
      if (curr == k) {
            return t->val;
      }
      if (curr < k) {
            return kth(t->rgt, k - curr);
      }
      else {
            return kth(t->lft, k);
      }
}

int binarySearch(pnode t, ll val) {
      int lo = 1;
      int hi = sz(t);
      int ans = 0;
      while (lo <= hi) {
            int mid = lo + hi >> 1;
            ll k = kth(t, mid);
            if (k <= val) {
                  ans = mid, lo = mid + 1;
            }
            else {
                  hi = mid - 1;
            }
      }
      return ans;
}

void display(pnode t) {
      if (t == nullptr) {
            return;
      }
      display(t->lft);
      cerr << t->val << " ";
      display(t->rgt);
}

void Display(pnode t) {
      cerr << "[";
      display(t);
      cerr << "]" << endl;
}

int less_equall(pnode t, ll val) {
      return binarySearch(t, val);
}

int greaterr(pnode t, ll val) {
      return sz(t) - less_equall(t, val);
}

ll less_equall_sum(pnode t, ll val) {
      int pos = less_equall(t, val);
      return query(t, pos);
}

ll greaterr_sum(pnode t, ll val) {
      int pos = less_equall(t, val);
      return t->sum - query(t, pos);
}

signed main()
{
      int n;
      cin >> n;
      pnode treap = nullptr;
      for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            int pos = less_equall(treap, x);
            treap = Insert(treap, new Node(x), pos);
      }
      Display(treap);
      for (int k = 1; k <= n; k++) {
            cerr << k << ": " << kth(treap, k) << endl;
      }
      treap = Erase(treap, 2, 2);
      Display(treap);
}
