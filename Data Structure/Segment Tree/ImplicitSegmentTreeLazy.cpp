struct Node {
      ll sum, lazy;
      Node *lchild, *rchild;

      Node(ll sum = 0, ll lazy = 0)
            : sum(sum), lazy(lazy), lchild(nullptr), rchild(nullptr) {}

      ~Node() {
            delete lchild;
            delete rchild;
      }
};

typedef Node*       pnode;

void updateLazy(pnode root, ll a, ll b, ll val) {
      root->sum += (b - a + 1) * val;
      root->lazy += val;
}

void updateNode(pnode root, ll a, ll b) {
      ll mid = (a + b) >> 1;
      if (root->lchild == nullptr) {
            root->lchild = new Node();
      }
      root->lchild->lazy += root->lazy;
      root->lchild->sum += (mid - a + 1) * root->lazy;
      if (root->rchild == nullptr) {
            root->rchild = new Node();
      }
      root->rchild->lazy += root->lazy;
      root->rchild->sum += (b - mid) * root->lazy;
      root->lazy = 0;
}

void update(pnode root, ll a, ll b, ll i, ll j, ll val) {
      if (a == i && b == j) {
            updateLazy(root, a, b, val);
            return;
      }
      if (root->lazy != 0) {
            updateNode(root, a, b);
      }
      ll mid = (a + b) >> 1;
      if (root->lchild == nullptr) {
            root->lchild = new Node();
      }
      if (root->rchild == nullptr) {
            root->rchild = new Node();
      }
      if (j <= mid) {
            update(root->lchild, a, mid, i, j, val);
      }
      else if (i > mid) {
            update(root->rchild, mid+1, b, i, j, val);
      }
      else {
            update(root->lchild, a, mid, i, mid, val);
            update(root->rchild, mid+1, b, mid+1, j, val);
      }
      root->sum = root->lchild->sum + root->rchild->sum;
}

ll query(pnode root, ll a, ll b, ll i, ll j) {
      if (a == i && b == j) {
            return root->sum;
      }
      if (root->lazy != 0) {
            updateNode(root, a, b);
      }
      ll mid = (a + b) >> 1;
      ll res = 0;
      if (root->lchild == nullptr) {
            root->lchild = new Node();
      }
      if (root->rchild == nullptr) {
            root->rchild = new Node();
      }
      if (j <= mid) {
            res += query(root->lchild, a, mid, i, j);
      }
      else if (i > mid) {
            res += query(root->rchild, mid+1, b, i, j);
      }
      else {
            res += query(root->lchild, a, mid, i, mid);
            res += query(root->rchild, mid+1, b, mid+1, j);
      }
      return res;
}

void clean(pnode root) {
      if (root == nullptr) {
            return;
      }
      clean(root->lchild);
      clean(root->rchild);
      delete root;
}

/*
  Usage:  pnode root = new Node();
*/
