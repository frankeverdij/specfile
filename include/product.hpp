#include <vector>
#include "item.hpp"
#include "image.hpp"
#include <tinyxml2.h>

#pragma once

class product : public item
{
    private:
        time_t creation_time_;
        std::vector<image> images_;

    public:
        product(buffer & buf, tinyxml2::XMLDocument & xmlDoc, const size_t offset);
        std::string getCreationTime();
        void printTree();
        
};

