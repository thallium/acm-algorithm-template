#include <limits>
template<typename T>
struct xor_basis {
    static constexpr int B = 8 * sizeof(T);
    T basis[B];
    int sz = 0;

    void insert(T x) {
        for (int i=B; i>=0; i--) {
            if (x>>i==0) continue;
            if (!basis[i]) {
                basis[i]=x;
                break;
            }
            x^=basis[i];
        }
    }

    T max_value(T start = 0) {
        for (int i=B; i>=0; i--) {
            if (basis[i]) {
                start = max(start, start^basis[i]);
            }
        }
        return start;
    }
};
