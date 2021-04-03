#ifndef __PRIME_GENERATOR_H__
#define __PRIME_GENERATOR_H__

#include <boost/random.hpp>
#include "utils.h"


namespace RSA{

    template<class T>
    class prime_generator
    {
    private:
        T prime;
        boost::random::mt19937 rng;
    public:
        prime_generator(){};
        prime_generator(unsigned seed);
        T get_prime(unsigned size, bool fast = false);
        bool is_prime(); //Miller-Rabin O(k*b)
        bool is_prime_fast();
    };


}

#endif // __PRIME_GENERATOR_H__