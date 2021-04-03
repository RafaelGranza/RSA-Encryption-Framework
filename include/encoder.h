#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "utils.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>

namespace RSA
{

    class encoder
    {
    private:
        
    public:
        encoder(){}
        boost::multiprecision::uint1024_t text_to_int(const std::string& message);
        std::string int_to_text(boost::multiprecision::uint1024_t value);
        boost::multiprecision::uint1024_t unhash(const std::string& message);
        std::string hash(boost::multiprecision::uint1024_t value);
        void encode(
            std::string& path_in,
            std::string& path_out,
            std::string& public_key_1,
            std::string& public_key_2
        );
        void encode(
            std::string& path_in,
            std::string& path_out,
            boost::multiprecision::uint1024_t& public_key_1,
            boost::multiprecision::uint1024_t& public_key_2
        );
        void decode(
            std::string& path_in,
            std::string& path_out,
            std::string& public_key,
            std::string& private_key
        );
        void decode(
            std::string& path_in,
            std::string& path_out,
            boost::multiprecision::uint1024_t& public_key,
            boost::multiprecision::uint1024_t& private_key
        );
        ~encoder() {}
    };

} // namespace RSA

#endif // __ENCODER_H__