#include "../include/prime_generator.h"

namespace RSA
{
    template<class T>
    prime_generator<T>::prime_generator(unsigned seed) 
    {
        rng.seed(seed);
    }


    template<class T>
    bool RSA::prime_generator<T>::is_prime() 
    {
        //Miller-Rabin
        const unsigned pn = 17;
        const unsigned p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 43, 47, 53, 57, 59};
        
        for(unsigned i = 0; i < pn; i++)
        {
            if(prime % p[i] == 0) return prime == p[i];
        }
        if(prime < p[pn-1]) return false;

        T s = 0, t = prime -1;
        while(~t & 1)
        {
            t >>= 1;
            ++s;
        }

        //Passar por todas a base O(k)
        for(unsigned i = 0; i < pn; ++i)
        {
            //O(b) ou O(log(n))
            T pt = RSA::mod_exp((T) p[i], t, prime);
            if(pt == 1) continue;
            bool ok = false;
            //O(b) ou O(log(n))
            for(unsigned j = 0; j < s && !ok; j++){
                if(pt == prime-1){
                    ok = true;
                }else{
                    pt = pt * pt;
                    pt %= prime;
                }
            }
            if(!ok) return false;
        }

        return true;
    }
    
    template<class T>
    bool prime_generator<T>::is_prime_fast() 
    {
        return ((RSA::mod_exp((T)2, this->prime, this->prime) -2) & 1) == 1;
    }

    template<class T>
    T RSA::prime_generator<T>::get_prime(unsigned size, bool fast) 
    {
        T max = ((T) 1) << size;
        boost::random::uniform_int_distribution<T> dist(1,max);
        if(fast)
        {
            do
            {
                this->prime = dist(rng);
            }while (!is_prime_fast());
        }else
        {
            do
            {
                this->prime = dist(rng);
            }while (!is_prime());
        }

        return this->prime;
    }
}