#include <bits/stdc++.h>

#include <ext/numeric>
#include <ext/rope>
using namespace __gnu_cxx;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
template<typename T>
using pbq = priority_queue<T>;
template<typename T, typename S = null_type>
using rbt = tree<T, S, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define Branch detail::branch_policy<Node_CItr, Node_Itr, _Alloc>
template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
class multi_node_update : private Branch {
 private:
     typedef typename Node_Itr::value_type Itr;
     typedef typename Branch::key_type key_type;
     typedef typename Branch::value_type::second_type val_type;
     virtual Node_CItr node_begin() const = 0;
     virtual Node_CItr node_end() const = 0;
     virtual Node_Itr node_begin() = 0;
     virtual Node_Itr node_end() = 0;

 protected:
     inline void operator() (Node_Itr it , Node_CItr end_it) const {
         Node_Itr l = it.get_l_child(), r = it.get_r_child();
         size_t left = 0, right = 0;
         if (l != end_it) left = l.get_metadata();
         if (r != end_it) right = r.get_metadata();
         const_cast<metadata_type &>(it.get_metadata()) = left + right + (*it)->second;
     }
     virtual ~multi_node_update() {};

 public:
     typedef size_t metadata_type;
     inline Itr find_by_order(size_t order) {
         Node_Itr it = node_begin();
         Node_Itr end_it = node_end();
         while (it != end_it) {
             Node_Itr l = it.get_l_child();
             size_t o = 0;
             if (l != end_it) o = l.get_metadata();
             if (order >= o && order < o + (*it)->second) return *it;
             else if (order < o) it = l;
             else {
                 order -= o + (*it)->second;
                 it = it.get_r_child();
             }
         }
         return Branch::end_iterator();
     }
     inline size_t order_of_key(const key_type& r_key) const {
         Node_CItr it = node_begin();
         Node_CItr end_it = node_end();
         size_t ord = 0;
         Cmp_Fn op;
         while (it != end_it) {
             Node_CItr l = it.get_l_child();
             if (op(r_key, (*it)->first)) it = l;
             else if (op((*it)->first, r_key)) {
                 ord += (l == end_it)? (*it)->second : (*it)->second + l.get_metadata();
                 it = it.get_r_child();
             } else {
                 ord += (l == end_it)? 0 : l.get_metadata();
                 it = end_it;
             }
         }
         return ord;
     }
};
template <typename T>
using multirbt = tree<T, size_t, std::less<T>, rb_tree_tag, multi_node_update>;

using namespace std;

#include <tr2/dynamic_bitset>
using namespace tr2;
using db = dynamic_bitset<>;
