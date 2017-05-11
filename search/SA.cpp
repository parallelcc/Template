#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
double eps = 1e-8;

int main() {
    default_random_engine e(time(NULL));
    uniform_real_distribution<double> u(0.0, 1.0);
    double t = ;  // step length
    // some init val
    double E = check();
    while (t > eps) {
        double nE = 0.0;
        for () {  // go around
            // use random make some change
            double ans = check();  // new
            if (nE < ans) {  // best
                nE = ans;
            }
        }
        double dE = nE - E;  // max, min: E - nE
        if (dE >= eps || exp(dE / t) > u(e)) {
            E = nE;
        }
        t *= 0.99;  // rate
    }
}
