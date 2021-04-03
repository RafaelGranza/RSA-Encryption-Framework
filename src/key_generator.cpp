#include "../include/key_generator.h"
#include "../include/prime_generator.h"


namespace RSA
{

    RSA::key_generator::key_generator() 
    {
        RSA::key_generator(512);
    }
    
    key_generator::key_generator(unsigned size, bool fast) 
    {
        if(size > 512){
            throw std::runtime_error("Chave não suportada\n");
        }
        RSA::prime_generator< boost::multiprecision::uint1024_t > gen(std::time(NULL));
        boost::multiprecision::uint1024_t p, q, totn, y, g;
        do
        {
            p = gen.get_prime(size/2, fast);
            q = gen.get_prime(size/2, fast);
            totn = (p - 1) * (q - 1);
            this->public_key_1 = p * q;
            do
            {
                this->public_key_2 = gen.get_prime(size, fast);
            }while(this->public_key_2 >= totn);

            gcd(public_key_2, totn, this->private_key, y);
            this->private_key = (this->private_key % totn + totn) % totn;
        }while((this->public_key_2 * this->private_key % totn) != 1);
    }
    
    boost::multiprecision::uint1024_t key_generator::get_public_key_1() 
    {
        return this->public_key_1;
    }
    
    boost::multiprecision::uint1024_t key_generator::get_public_key_2() 
    {
        return this->public_key_2;
    }
    
    boost::multiprecision::uint1024_t key_generator::get_private_key() 
    {
        return this->private_key;
    }
    
}