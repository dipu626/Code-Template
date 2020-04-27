static const int maxn = 2e5 + 5;
static const int Max  = 2e6 + 6;

struct Node {
      int st;
      int lchild, rchild;
      Node(int st = 0, int lchild = 0, int rchild = 0) :
            st(st), lchild(lchild), rchild(rchild) {}
} Tree[Max];

int version[maxn];
int NODES;
int N = 100000;

int update(int root, int a, int b, int pos, int val) {
      int newNode = ++NODES;
      Tree[newNode] = Tree[root];
      if (a == b) {
            Tree[newNode].st += val;
            return newNode;
      }
      int mid = (a + b) / 2;
      if (pos <= mid) {
            Tree[newNode].lchild = update(Tree[newNode].lchild, a, mid, pos, val);
      }
      else {
            Tree[newNode].rchild = update(Tree[newNode].rchild, mid + 1, b, pos, val);
      }
      Tree[newNode].st = Tree[ Tree[newNode].lchild ].st + Tree[ Tree[newNode].rchild ].st;
      return newNode;
}

long long query(int proot, int root, int a, int b, int i, int j) {
      if (a > j or b < i) {
            return 0;
      }
      if (a >= i and b <= j) {
            return Tree[root].st - Tree[proot].st;
      }
      int mid = (a + b) / 2;
      long long p = query(Tree[proot].lchild, Tree[root].lchild, a, mid, i, j);
      long long q = query(Tree[proot].rchild, Tree[root].rchild, mid + 1, b, i, j);
      return p + q;
}

int kth(int proot, int root, int a, int b, int k) {
      if (a == b) {
            return a;
      }
      int mid = (a + b) / 2;
      int sizeLeftChild = Tree[ Tree[root].lchild ].st - Tree[ Tree[proot].lchild ].st;
      if (k <= sizeLeftChild) {
            return kth(Tree[proot].lchild, Tree[root].lchild, a, mid, k);
      }
      else {
            return kth(Tree[proot].rchild, Tree[root].rchild, mid + 1, b, k - sizeLeftChild);
      }
}

void init() {
      NODES = 0;
      version[0] = 0;
      for (int i = 0; i < Max; i++) {
            Tree[i] = Node();
      }
}

/* NOTES:
            1. map the value of the array
            2. check the value of Max
            3. check the value of N
*/
