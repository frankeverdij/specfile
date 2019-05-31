#include <string>
#include <iostream>

#pragma once

class buffer
{
    private:
        unsigned char * buf_;
        size_t len_;
        double version_;
        void checkmagic();

    public:
        buffer(const char * filename);
        ~buffer();

        template <typename T> T getNum(size_t * offset)
        {
            T s = 0;
            size_t slen = sizeof(T);

            if (*offset + slen < len_) {
                for (size_t i = 0; i < slen; i++) {
                    s <<= 8;
                    s += buf_[*offset + i];
                }
                *offset += slen;
                return s;
            } else {
                std::cerr << "number out of bounds at " << *offset << std::endl;
                exit(EXIT_FAILURE);
            }
        };

        std::string getString(size_t * offset);
        
};
