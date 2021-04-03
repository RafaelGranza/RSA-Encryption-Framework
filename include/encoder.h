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
        boost::multiprecision::uint1024_t text_to_int(const std::wstring& message);
        std::wstring int_to_text(boost::multiprecision::uint1024_t value);
        boost::multiprecision::uint1024_t unhash(const std::wstring& message);
        std::wstring hash(boost::multiprecision::uint1024_t value);
        void encode(
            std::string& path_in,
            std::string& path_out,
            std::wstring& public_key_1,
            std::wstring& public_key_2
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
            std::wstring& public_key,
            std::wstring& private_key
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