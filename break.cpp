#include "./include/rsa.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    RSA::key_generator key_gen(100);
    auto k1 = key_gen.get_public_key_1();
    auto k2 = key_gen.get_public_key_2();
    auto k3 = key_gen.get_private_key();

    std::cout << "Chave pública 1:\t\t" << k1 << std::endl;
    std::cout << "Chave pública 2:\t\t" << k2 << std::endl;
    std::cout << "Chave privada:\t\t\t" << k3 << std::endl;
    
    std::cout << "Chave privada (BRUTADA):\t" << RSA::brent_key_breaker(k1, k2) << std::endl;

    return 0;
}
