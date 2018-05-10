// Copyright 2017 Parallelc
// nex[i] 表示从0到i - 1的最长公共前后缀中前缀的下一位，如abcdabc，nex[7]为3，即在7失配时应该跳到3去匹配
#include <vector>
#include <string>
using namespace std;  // NOLINT
template <typename T>
class KMP {
 public:
     vector<T> sub_str;
     vector<int> nex;
     int sub_len;
     KMP() {}
     explicit KMP(const vector<T> &sub_str) {
         this->sub_str = sub_str;
         sub_len = sub_str.size();
         this->get_nex();
     }
     explicit KMP(const string &sub_str) {
         this->sub_str.assign(sub_str.begin(), sub_str.end());
         sub_len = sub_str.length();
         this->get_nex();
     }
     void get_nex() {
         nex.resize(sub_len + 1);
         int i = 0, j = -1;
         nex[0] = -1;
         while (i < sub_len) {
             if (-1 == j || sub_str[i] == sub_str[j]) {
                 i++;
                 j++;
              // if (sub_str[i] != sub_str[j]) nex[i] = j;
              // else nex[i] = nex[j];
                 nex[i] = j;
             } else {
                 j = nex[j];
             }
         }
     }
     int get_result(const vector<T> &ori_str, int ori_len, int pos = 0) {
         auto i = pos - 1, j = -1;
         while (i < ori_len) {
             if (-1 == j || ori_str[i] == sub_str[j]) {
                 i++;
                 j++;
                 if (j == sub_len) {
                    return i - sub_len;
                    j = nex[j];
                 }
             } else {
                 j = nex[j];
             }
         }
         return -1;
     }
     int get_cycle(int len) {
         if (len % (len - nex[len]) == 0)  return len / (len - nex[len]);
         else return 1;
     }
};
