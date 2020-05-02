/**
  * uses of rope data structure:
  * Initialize                 : rope <data_type> Rope;
  * Insert single element      : Rope.push_back()
  * Insert a block of elements : Rope.insert(position after insert, newRope)
  * Erase a block of elements  : Rope.erase(starting position of deletion, size of deletion)
  * Other Operations           : Same as std::vector
  * Iterator                   : Rope.mutable_begin(), Rope.mutable_end(), Rope.mutable_rbegin(), Rope.mutable_rend()
  * Caution                    : Never use -- Rope.begin() iterator
**/

#include "ext/rope"
using namespace __gnu_cxx;
 
rope <int> Rope;
