int inv[maxn];
inv[1] = 1;
for(int i = 2; i < maxn; i++)
    inv[i] = (p - p / i) % p * inv[p % i];
