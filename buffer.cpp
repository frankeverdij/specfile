#include <iostream>
#include <cstring>

#include "buffer.hpp"

#define ERRMSG(...) std::cerr << __VA_ARGS__ << std::endl , exit(EXIT_FAILURE)

buffer::buffer(const char * filename) : len_(0), version_(0.0)
{
    FILE * fp;
    size_t i;

    /* open file */
    if ((fp = fopen(filename,"r")) == NULL) {
        std::cerr << "cannot open file " << filename << " for reading" << std::endl;
        exit(EXIT_FAILURE);
    }
    /* count bytes */
    while (fgetc(fp) != EOF)
        len_++;
    /* allocate buffer */
    buf_ = new unsigned char[len_];
    /* seek back */
    fseek(fp, 0, SEEK_SET);
    /* read file in buffer */
    for (i = 0; i < len_; i++)
        buf_[i] = fgetc(fp);
    fclose(fp);
}

buffer::~buffer()
{
    delete[] buf_;
}

std::string buffer::getString(size_t * offset)
{
    unsigned short sh = getNum<unsigned short>(offset);
    size_t slen = *offset + sh;

    if (slen <= len_) {
        std::string ret((const char *)buf_ + *offset, (size_t) sh);
        *offset = slen;
        return ret;
    } else {
        std::cerr << "string out of bounds at " << *offset << " size " << sh << std::endl;
        exit(EXIT_FAILURE);
    }
}

void buffer::checkmagic()
{
    char strversion[32];
    const char magicstring[] = "pd001V";
    const unsigned char magicbytes[8] = {0x00, 0x07, 0xc4, 0x00, 0x01, 0x07, 0xc3, 0x00 };

    if (len_ < 20)
        std::cerr << "file is too short for an inst spec file" << std::endl;

    if ((std::memcmp(magicstring, buf_, strlen(magicstring)) != 0 &
        std::memcmp(magicbytes,  buf_ + 12, sizeof(magicbytes))) != 0) {
        std::cerr << "file is not an inst spec file" << std::endl;
    } else {
        strncpy(strversion, (const char *)buf_ + 6, 6);
        std::cout << "inst version" << strversion << std::endl;
        if (strversion[3] == 'P') {
            strversion[3] ='.';
            version_ = strtod(strversion, NULL);
        }
    }
}

