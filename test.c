#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Example from https://bugs.llvm.org/show_bug.cgi?id=47727

void foo1(uint32_t * out) {
    uint64_t tmp64;
    tmp64 = 0;

    uint32_t * tmp32 = (uint32_t *)&tmp64;
    *out = tmp32[1];
}

void foo2(uint32_t * out) {
    uint64_t tmp64[1];
    tmp64[0] = 0;

    uint32_t * tmp32 = (uint32_t *)tmp64;
    *out = tmp32[1];
}

void foo3(uint32_t * out) {
    uint64_t tmp64[1];
    memset(tmp64, 0, sizeof(tmp64));

    uint32_t * tmp32 = (uint32_t *)tmp64;
    *out = tmp32[1];
}

void foo4(uint32_t * out) {
    uint64_t tmp64[1];
    memset(tmp64, 0, sizeof(tmp64));

    memcpy(out, ((uint32_t*)tmp64) + 1, sizeof(uint32_t));
}

int main(void) {
  uint32_t out1, out2, out3, out4;
  foo1(&out1);
  foo2(&out2);
  foo3(&out3);
  foo4(&out4);

  return out1 + out2 + out3 + out4;
}
