#include <string>
#include <vector>
#include "image.hpp"

#pragma once

class product
{
    private:
        time_t creation_time_;
        string name_;
        string description_;
        size_t offset_;
        std::vector<image> images;

    public:
        product();
        time_t getTime();
        
};
