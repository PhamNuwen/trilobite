#ifndef XP_H
#define XP_H
typedef unsigned char *xp_t;
extern int xp_add(int n, xp_t z, xp_t x, xp_t y, int carry);
extern int xp_sub(int n, xp_t z, xp_t x, xp_t y, int borrow);
extern int xp_mul(xp_t z, int n, xp_t x, int m, xp_t y);
extern int xp_div(int n, xp_t q, xp_t x, int m, xp_t y, xp_t r, xp_t tmp);
extern int xp_sum(int n, xp_t z, xp_t x, int y);
extern int xp_diff(int n, xp_t z, xp_t x, int y);
extern int xp_product(int n, xp_t z, xp_t x, int y);
extern int xp_quotient(int n, xp_t z, xp_t x, int y);
extern int xp_neg(int n, xp_t z, xp_t x, int carry);
extern int xp_cmp(int n, xp_t x, xp_t y);
extern void xp_lshift(int n ,xp_t z, int m, xp_t x, int s, int fill);
extern void xp_rshift(int n, xp_t z, int m, xp_t z, int s, int fill);
extern int xp_length(int n, xp_t x);
extern unsigned long xp_fromint(int n, xp_t z, unsigned long u);
extern unsigned long xp_toint(int n, xp_t x);
extern int xp_read(int n, xp_t z, const char *str, int base, char **end);
extern char *xp_show(char *str, int size, int base, int n, xp_t x);
#endif
