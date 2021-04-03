#include "../include/encoder.h"

namespace RSA
{
    boost::multiprecision::uint1024_t encoder::text_to_int(const std::string& message) 
    {
        boost::multiprecision::uint1024_t value;
        unsigned exp = 0;
        for (char c : message)
        {
                value += c * ((boost::multiprecision::uint1024_t) 1) << (exp*8);
                ++exp;
        }
        return value;
    }

    std::string encoder::int_to_text(boost::multiprecision::uint1024_t value) 
    {
        std::string message;
        while(value)
        {
            message += (char) (value & 255);
            value >>= 8;
        }
        return message;
    }

    std::string encoder::hash(boost::multiprecision::uint1024_t value) 
    {
        std::string message;
        while(value)
        {
            message +=  ('0' + (char)(value & 31));
            value >>= 5;
        }
        //std::reverse(message.begin(), message.end());
        return message;
    }

    boost::multiprecision::uint1024_t encoder::unhash(const std::string& message) 
    {
        boost::multiprecision::uint1024_t value;
        unsigned exp = 0;
        for (char c : message)
        {
                value += (c - '0')* ((boost::multiprecision::uint1024_t) 1) << (exp*5);
                ++exp;
        }
        return value;
    }


    void encoder::encode(
                std::string& path_in,
                std::string& path_out,
                boost::multiprecision::uint1024_t& public_key_1,
                boost::multiprecision::uint1024_t& public_key_2) 
    {
        std::ifstream is (path_in);
        if (!is.is_open())
        {
            throw std::runtime_error("Arquivo de entrada inexistente\n");
        }
        std::ofstream os (path_out);
        if (!os.is_open())
        {
            throw std::runtime_error("Arquivo de saída inexistente\n");
        }
        
        boost::multiprecision::uint1024_t k1 = public_key_1, k2 = public_key_2;
        unsigned block_size = RSA::logb(k1)/8 -1;
        unsigned last;
        boost::multiprecision::uint1024_t message;
        
        char* buffer = new char [block_size];
        //O(F)
        while((last = is.readsome (buffer,block_size)) == block_size)
        {
            message = encoder::text_to_int(buffer);
            // O(b) ou O(log(n))
            message = mod_exp(message, k2, k1);
            os << hash(message) << std::endl; 
        }
        if(last)
        {
            char* buffer_rest = new char [last];
            std::strncpy(buffer_rest, buffer, last);
            message = encoder::text_to_int(buffer_rest);
            message = mod_exp(message, k2, k1);
            os << hash(message) << std::endl;
            delete[] buffer_rest;
        }
        delete[] buffer;
    }
    
    void encoder::encode(
                std::string& path_in,
                std::string& path_out,
                std::string& public_key_1,
                std::string& public_key_2)
    {
        boost::multiprecision::uint1024_t k1 = encoder::unhash(public_key_1);
        boost::multiprecision::uint1024_t k2 = encoder::unhash(public_key_2);
        encoder::encode(path_in, path_out, k1, k2);
    }
    
    void encoder::decode(
                std::string& path_in,
                std::string& path_out,
                boost::multiprecision::uint1024_t& public_key,
                boost::multiprecision::uint1024_t& private_key)
    {
        std::ifstream is (path_in);
        if (!is.is_open())
        {
            throw std::runtime_error("Arquivo de entrada inexistente\n");
        }
        std::ofstream os (path_out);
        if (!os.is_open())
        {
            throw std::runtime_error("Arquivo de saída inexistente\n");
        }

        boost::multiprecision::uint1024_t k1 = public_key;
        boost::multiprecision::uint1024_t k2 = private_key;
        std::string v;
        boost::multiprecision::uint1024_t message;

        while(is >> v)
        {
            message = unhash(v);
            message = mod_exp(message, k2, k1);
            os << encoder::int_to_text(message);
        }
    }
    
    void encoder::decode(
                std::string& path_in,
                std::string& path_out,
                std::string& public_key,
                std::string& private_key) 
    {
        boost::multiprecision::uint1024_t k1 = encoder::unhash(public_key);
        boost::multiprecision::uint1024_t k2 = encoder::unhash(private_key);
        decode(path_in, path_out, k1, k2);
    }

}