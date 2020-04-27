struct Node {
      ll sum;
      Node *lchild, *rchild;
      Node(ll sum = 0)
            : sum(sum), lchild(nullptr), rchild(nullptr) {}
      ~Node() {
            delete lchild;
            delete rchild;
      }
};

typedef Node*        pnode;

void add(pnode root, int a, int b, int i, int j, ll val) {
      if (a > j or b < i) {
            return;
      }
      if (a >= i and b <= j) {
            root->sum += val;
            return;
      }
      int mid = (a + b) >> 1;
      if (root->lchild == nullptr) {
            root->lchild = new Node();
      }
      if (root->rchild == nullptr) {
            root->rchild = new Node();
      }
      add(root->lchild, a, mid, i, j, val);
      add(root->rchild, mid+1, b, i, j, val);
}

ll get(pnode root, int a, int b, int pos) {
      if (root == nullptr or a > pos or b < pos) {
            return 0;
      }
      if (a == b) {
            return root->sum;
      }
      int mid = (a + b) >> 1;
      return root->sum + get(root->lchild, a, mid, pos) + get(root->rchild, mid+1, b, pos);
}
