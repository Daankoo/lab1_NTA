#include "header.h"

int gcd(int a, int b) {
	while (b != 0) { // a = q*b + r
		int q = a / b;
		int r = a % b;

		a = b;
		b = r;
	}

	return a;
}

int gcd_uv(int a, int b, int& u, int& v) {
	int u0 = 1, u1 = 0;
	int v0 = 0, v1 = 1;

	while (b != 0) { // a = q*b + r
		int q = a / b;
		int r = a % b;

		a = b;
		b = r;

		int u_n = u0 - q * u1;
		int v_n = v0 - q * v1;

		u0 = u1;
		u1 = u_n;

		v0 = v1;
		v1 = v_n;
	}

	u = u0;
	v = v0;

	return a;
}

int inverse(int a, int n) {
	int u, v;

	if (gcd_uv(a, n, u, v) != 1) {
		//cout << "Error: Inverse element is not found";
		return -1;
	}

	return (u % n + n) % n;
}

int step(int a, int b) {
	int c = a;

	for (int i = 0; i < b - 1; i++) {
		c *= a;
	}

	return c;
}

int mod(int a, int b) {
	int c = ((a % b) + b) % b;
	return c;
}

int mod_step(int a, int b, int n) {

	int c = mod(step(a, b), n);

	return c;
}