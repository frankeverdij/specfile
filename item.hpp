#include "buffer.hpp"

#pragma once

class item
{
    protected:
        std::string name_;
        std::string id_;
        size_t off_begin_, off_end_;
    
    public:
        item(buffer & buf, const size_t offset);
        std::string getName();
        std::string getId();
        size_t getEndOffset();
};

