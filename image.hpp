#include <vector>
#include "item.hpp"
#include "subsystem.hpp"

#pragma once

class image : public item
{
    private:
        size_t version_, order_, v_[2];
        std::vector<subsystem> subsystems_;

    public:
        image(buffer & buf, size_t * offset);
        void printTree();

};

