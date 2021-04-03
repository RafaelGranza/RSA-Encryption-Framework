#ifndef __PRIME_UTILS_H__
#define __PRIME_UTILS_H__

#include <tuple>
#include <iostream>
#include <algorithm>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace RSA{
    
    template <class T>
    T mod_exp(const T& base, const T& exp,const T& mod);

    template <class T>
    T gcd(T a, T b,T& x, T& y);

    template <class T>
    T gcd(T a, T b);

    template <class T>
    T gcd_fast(T a, T b);

    template <class T>
    T lcm(T a, T b);

    template <class T>
    T abs(const T& a, const T& b);

    template <class T>
    unsigned logb(T a);

    template <class T>
    T key_breaker(const T& key_1, const T& key_2, u_char c = 1); 

    template <class T>
    T naive_key_breaker(const T& key_1, const T& key_2); // O(2^(b/2)) ou O(n^(1/2))

    template <class T>
    T pollard_key_breaker(const T& key_1, const T& key_2); // O(2^(b/4)) ou O(n^(1/4))

    template <class T>
    T brent_key_breaker(const T& key_1, const T& key_2); // O(2^(b/4)) ou O(n^(1/4))

    template <class T>
    T find_factor(const T& value);

    template <class T>
    T pollard_rho(const T& value);

    template <class T>
    T brent(const T& n, T x0 = 32, T c = 1);


}

#endif // __PRIME_UTILS_H__