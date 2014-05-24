//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// Includes
//

#include "common.h"
#include "modular.h"
#include "primesieve.h"
#include "Rational.h"
#include "Karatsuba.h"
#include "chineseremainder.h"

#ifdef WINDOWS
#include <cstdlib>
#endif

//
// Lab 2
//

// KATTIS input/output functions
void KATTIS_modular();
void KATTIS_primesieve();
void KATTIS_rational();
void KATTIS_chineseremainder();
void KATTIS_karatsuba();

int main() {
    KATTIS_modular();
    // KATTIS_rational();
    // KATTIS_chineseremainder();
    // KATTIS_karatsuba();
	// KATTIS_primesieve();
    return 0;
}

void KATTIS_karatsuba()
{
    int t,A,B;
    scanf("%d", &t);
    
    while(t--) {
        int a[131072];
        int b[131072];
        int res[262144];
        scanf("%d", &A); ++A;
        for (int i = 0; i < A; ++i) {
            scanf("%d", &a[i]);
        }
        scanf("%d", &B); ++B;
        for (int i = 0; i < B; ++i) {
            scanf("%d", &b[i]);
        }
        int N = max(A,B);
        karatsuba(a,b,res,N);
        printf("%d\n", A+B-2);
        for (int i = 0; i < A+B-1; ++i) {
            printf("%d ", res[i]);
        }
        printf("\n");
    }
}

void KATTIS_chineseremainder()
{
	int _t;
	//scanf("%d", &_t);
	cin >> _t;

	long long a, n, b, m;
	while (_t--)
	{
		// x = a (mod n)
		// x = b (mod m)
		//scanf("%lld %lld %lld %lld", &a, &n, &b, &m);
		cin >> a >> n >> b >> m;
		long long x = CRT(a, n, b, m);
		cout << x << " " << n*m << endline;
	}
}

typedef Rational<long long> Rlong;
void KATTIS_rational() 
{
    int N;
    scanf("%d", &N);

    rep(i, 0, N)
    {
        char op;
        int n, d, n2, d2;
        scanf("%d %d %c %d %d\n", &n, &d, &op, &n2, &d2);

        Rlong a(n, d), b(n2, d2);
        switch (op)
        {
        case '+':
            cout << a + b << endline;
            break;
        case '-':
            cout << a - b << endline;
            break;
        case '*':
            cout << a * b << endline;
            break;
        case '/':
            cout << a / b << endline;
            break;
        }
        

    }

}

void KATTIS_primesieve()
{
    int iterations = 10;
    int N, q;
    //scanf("%ud%ud", &N, &q);
    cin >> N >> q;

    vector<bool> sieve(N + 1, true);
    int nprimes = primesieve(sieve, N, iterations);

    cout << nprimes << endline;
    int p;
    rep(i, 0, q)
    {
        scanf("%d", &p);
        cout << sieve[p] << endline;
    }

    int stop = 1;

}

void KATTIS_modular() 
{
    long long n;
    int t;
    while(scanf("%lld %d", &n, &t) == 2) {
        if (n == 0 && t == 0)
            break;
        long long x,y;
        char c;
        for (int i = 0; i < t; ++i) {
            long long res;
            scanf("%lld %c %lld", &x, &c, &y);
            if (c == '+')
                res = mod_add(x,y,n);   
            else if (c == '-')
                res = mod_sub(x,y,n);
            else if (c == '/')
                res = mod_div(x,y,n);
            else if (c == '*')
                res = mod_mult(x,y,n);
            cout << res << endl;
        }
    }    
}
