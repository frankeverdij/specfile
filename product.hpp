#include <vector>
#include "item.hpp"
#include "image.hpp"

#pragma once

class product : public item
{
    private:
        time_t creation_time_;
        std::vector<image> images_;

    public:
        product(buffer & buf, const size_t offset);
        std::string getCreationTime();
        void printTree();
        
};

