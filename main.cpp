#include "./include/rsa.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    RSA::key_generator key_gen(512);
    auto k1 = key_gen.get_public_key_1();
    auto k2 = key_gen.get_public_key_2();
    auto k3 = key_gen.get_private_key();

    std::cout << "Chave pública 1:\t" << k1 << std::endl;
    std::cout << "Chave pública 2:\t" << k2 << std::endl;   
    std::cout << "Chave privada:\t\t" << k3 << std::endl;
    
    RSA::encoder manager;
    std::string file("messages/text.txt");
    std::string file1("messages/encoded.txt");
    std::string file2("messages/decoded.txt");
    
    manager.encode(file, file1, k1, k2);
    manager.decode(file1, file2, k1, k3);
    
    return 0;
}
