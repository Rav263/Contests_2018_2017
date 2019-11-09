#include <limits.h>

STYPE bit_reverse(STYPE value){
    UTYPE type = value;
    UTYPE ans = 0;

    for (int i = 0; i < sizeof(type) * CHAR_BIT; i++) {
        ans <<= 1;
        ans += type & 1;
        type >>= 1;
    }

    return ans;
}
