#include <iostream>
using namespace std;
unsigned long long int fast_pow(unsigned long long int n, unsigned long long int a, unsigned long long int mod)
{
	if (a == 0) {
		return 1;
	}
	if (a % 2 == 0) {
		return (fast_pow(n, a / 2, mod) * fast_pow(n, a / 2, mod)) % mod;
	}
	else {
		return (n * fast_pow(n, a / 2, mod) * fast_pow(n, a / 2, mod)) % mod;
	}
}
void MILLER_RABIN_TEST(unsigned long long int n) {
	unsigned long long int d = n - 1,test1=0,test2=0,bad=0;
	int s = 0;
	while (d % 2 == 0)
	{
		d /= 2;
		s++;
	}
	for (unsigned long long int i = 1; i < n; i++) {
		unsigned long long int candidate = fast_pow(i, d, n);
		if (candidate == 1) {
			test1++;
			continue;
		}
		if (candidate == n - 1) {
			test2++;
			continue;
		}
		for (int r = 1; r < s; r++)
		{
			candidate = fast_pow(candidate,2,n);
			if (candidate == 1) {
				break;
			}
			if (candidate == n - 1) {
				test2++;
				break;
			}
		}
		if (candidate != n - 1) {
			bad++;
		}
	}
	if (bad == 0) {
		cout << "True " << bad << " " << test1 <<" " << test2<<endl;
	}
	else {
		cout << "False " << bad << " " << test1 << " " << test2<<endl;
	}
}
void FERMA_TEST(unsigned long long int n) {
	unsigned long long int bad = 0,good=0;
	for (unsigned long long int i = 1; i < n; i++) {
		if (!(fast_pow(i, n - 1, n) == 1)) {
			bad++;
		}
		else {
			good++;
		}
	}
	if (bad==0)
		cout << "True "<<bad<<" "<<good;
	else {
		cout << "False " << bad << " " << good;
	}
}
int main() {
	unsigned long long int n;
	cin >> n;
	cout << "Miller-Rabin test: ";
	MILLER_RABIN_TEST(n);
	cout << "Fermat test: ";
	FERMA_TEST(n);
}