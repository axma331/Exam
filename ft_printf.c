#include <stdarg.h>
#include <unistd.h>
​
int	c, wdh, prc;
char *pfx;
​
int snlen(char *s, int n) {
	char *p = s;
	for (; n && s && *s; n--)
		s++;
	return s - p;
}
void putchn(char ch, int n) {
	for (; n > 0; n--)
		c += write(1, &ch, 1);
}
void putmem(char *p, int n) {
	c += write(1, p, n);
}
void putu(unsigned n, char b) {
	if (n) {
		putu(n / b, b);
		c += write(1, &"0123456789abcdef"[n % b], 1);
	}
}
void prn_s(char *s) {
	prc = snlen(s, prc);
	putchn(' ', wdh - prc);
	putmem(s, prc);
}
void prn_u(unsigned n, char b) {
	int	l = 0;
	for (unsigned d = n; d; d /= b)
		l++;
	if (prc < l)
		prc = l ?: 1;
	putchn(' ', wdh - prc - snlen(pfx, -1));
	putmem(pfx, snlen(pfx, -1));
	putchn('0', prc - l);
	putu(n, b);
}
void prn_d(int n) {
	unsigned u = n > 0 ? n : -n;
	if (n < 0)
		pfx = "-";
	prn_u(u, 10);
}
int prnf(const char *s, va_list *pap) {
	wdh = 0;
	prc = -1;
	pfx = "";
	const char *p = s;
	for (s++; '0' <= *s && *s <= '9'; s++)
		wdh = wdh * 10 + (*s - '0');
	if (*s == '.') {
		prc = 0;
		for (s++; '0' <= *s && *s <= '9'; s++)
			prc = prc * 10 + (*s - '0');
	}
	switch (*s) {
		case 's': prn_s(va_arg(*pap, char *) ?: "(null)"); break;
		case 'x': prn_u(va_arg(*pap, unsigned), 16); break;
		case 'd': prn_d(va_arg(*pap, int)); break;
		default: s--;
	}
	return ++s - p;
}
int ft_printf(const char *s, ...) {
	va_list ap;
	va_start(ap, s);
	c = 0;
	while (s && *s)
		if (*s == '%')
			s += prnf(s, &ap);
		else
			putchn(*s++, 1);
	va_end(ap);
	return c;
}
