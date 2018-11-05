#include <iostream>

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

int fibonacci(int n){
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fib(n - 1)+fib(n - 2);
}

int factoriel(int n) {
	return (n == 0) ? 1 : n * fact(n - 1);
}

int main() {
	
	return 0;
}
