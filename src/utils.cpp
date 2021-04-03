#include "../include/utils.h"

namespace RSA
{
    template<class T>
    T mod_exp(const T& base, const T& exp,const T& mod) 
    {
        T e = exp;
        T b = base;
        T res = 1;
        
        while(e)
        {
            if(e & 1)
            {
                res  = res * b;
                res %= mod;
            }
            b   = b * b;
            b  %= mod;
            e >>= 1;
        }

        return res;
    }
    
    template<class T> //O(b) ou O(log(n))
    T gcd(T a, T b, T& x, T& y) {
        x = 1, y = 0;
        T x1 = 0, y1 = 1, a1 = a, b1 = b;
        while (b1)
        {
            T q = a1 / b1;
            std::tie(x, x1)  = std::make_tuple(x1, x - q * x1);
            std::tie(y, y1)  = std::make_tuple(y1, y - q * y1);
            std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
        }
        return a1;
    }

    template<class T>
    T gcd(T a, T b)
    {
        while(b)
        {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template<class T>
    T gcd_fast(T a, T b)
    {
        T c = a|b;
        if (!a || !b) return c;
        unsigned shift;
        while(! (c & 1))
        {
            ++shift;
            c >>= 1;
        }
        while(! (a & 1))
        {
            a >>= 1;
        }
        do {
            while(! (b & 1))
            {
                b >>= 1;
            }
            if (a > b) swap(a, b);
            b -= a;
        } while (b);
        return a << shift;
    }

    template<class T>
    T lcm(T a, T b) 
    {
        return (a*b) / gcd(a, b);    
    }
    

    template<class T>
    T abs(const T& a, const T& b) 
    {
        if (a > b) return a-b;
        else       return b-a;
    }

    template<class T>
    unsigned logb(T a) 
    {
        unsigned b = 0;
        while(a)
        {
            a >>= 1;
            ++b;
        }   
        return b;
    }

    template<class T>
    T key_breaker(const T& key_1, const T& key_2, u_char c) 
    {
        T private_key, p, q, tot, y;
        switch (c)
        {
        case 1:
            p = RSA::find_factor(key_1);
            break;
        case 2:
            p = RSA::pollard_rho(key_1);
            break;
        case 3:
            p = RSA::brent(key_1);
            break;
        default:
            break;
        }
        q = key_1 / p;
        tot = RSA::lcm(p-1, q-1);
        gcd(key_2, tot, private_key, y);
        private_key = (private_key % tot + tot) % tot;
        return private_key;
    }
    
    template<class T>
    T naive_key_breaker(const T& key_1, const T& key_2) 
    {
        return RSA::key_breaker(key_1, key_2, 1);
    }
    
    template<class T>
    T pollard_key_breaker(const T& key_1, const T& key_2) 
    {
        return RSA::key_breaker(key_1, key_2, 2);
    }

    template<class T>
    T brent_key_breaker(const T& key_1, const T& key_2) 
    {
        return RSA::key_breaker(key_1, key_2, 3);
    }
    
    template<class T>
    T find_factor(const T& value) 
    {
        T i, sq = boost::multiprecision::sqrt(value);
        for(i = 2; i <= sq; ++i)
        {
            if(value % i == 0) return i;
        }
        return value;
    }
    
    template<class T>
    T pollard_rho(const T& value) 
    {
        T i = 0, k = 2, d;
        T x = 3, y = 3;
        
        while(++i)
        {
            x  = (x * x) % value;
            x += value - 1;
            x %= value;
            d = RSA::gcd(RSA::abs(x, y), value);
            if(d != 1 && d != value) return d;
            if(i == k)
            {
                y   = x;
                k <<= 1;
            }
        }
    }
    
    template<class T>
    T brent(const T& n, T x0, T c) 
    {
        T x = x0;
        T g = 1;
        T q = 1;
        T xs, y, i;

        T m = 510;
        T l = 1;
        while (g == 1)
        {
            y = x;
            for (i = 1; i < l; ++i) x = (x * x  + 1) % n;
            T k = 0;
            while (k < l && g == 1) 
            {
                xs = x;
                for (i = 0; i < m && i < l - k; ++i)
                {
                    x = (x * x + 1) % n;
                    q = (q * RSA::abs(y , x)) % n;
                }
                g  = RSA::gcd(q, n);
                k += m;
            }
            l <<= 1;
        }
        if (g == n)
        {
            do
            {
                xs = (xs * xs + 1) % n;
                g = RSA::gcd(RSA::abs(xs, y), n);
            } while (g == 1);
        }
        
        return g;
    }
}