#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

using namespace std;
using namespace __gnu_pbds;

template <typename T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T1, typename T2> using ordered_map = tree <T1, T2, less <T1>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_trie = trie <T, null_type, trie_string_access_traits <>, pat_trie_tag, trie_prefix_search_node_update>;

#define ook                order_of_key
#define fbo                find_by_order

/*
      ordered_set <int> os;
      os.insert(x)         : insert x into the set
      *os.find_by_order(k) : k'th element
      os.order_of_key(k)   : no of elements less than k

      ordered_trie <string> ot;
      auto range = ot.prefix_range(prefix) : range of the string with prefix
      for (auto it = range.first; it != range.second; it++) { // print all
            cout << *it << endl;
      }
*/


template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_update_policy
{
      virtual Node_CItr node_begin() const = 0;
      virtual Node_CItr node_end() const = 0;
      typedef int metadata_type;

      int prefix_sum(int x)  // sum of indices <= x
      {
            int ans = 0;
            auto it = node_begin();

            while (it != node_end())
            {
                  auto l = it.get_l_child();
                  auto r = it.get_r_child();

                  if (Cmp_Fn()(x, (*it)->first))
                  {
                        it = l;
                  }
                  else
                  {
                        ans += (*it)->second;
                        if (l != node_end()) ans += l.get_metadata();
                        it = r;
                  }
            }
            return ans;
      }
      void operator()(Node_Itr it, Node_CItr end_it)
      {
            auto l = it.get_l_child();
            auto r = it.get_r_child();
            int lft = 0;
            int rgt = 0;
            if (l != node_end()) lft = l.get_metadata();
            if (r != node_end()) rgt = r.get_metadata();
            const_cast <int&> (it.get_metadata()) = (lft + rgt + (*it)->second);
      }
};

template <class T> using ordermap = tree <T, T, less <T>, rb_tree_tag, my_update_policy>;

/* Usage:
            ordermap <int> om;
            om.insert(x)
            om.prefix_sum(x)
*/
