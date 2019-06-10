#include <vector>
#include "item.hpp"

#pragma once

class subref
{
    private:
        std::string name_sub_[3];
        unsigned int v_[2];

    public:
        subref(buffer & buf, size_t * offset);
        void printTree();
};

class subsystem : public item
{
    private:
        std::string expanded_name_;
        std::vector<subref> replaces_;
        std::vector<subref> prereq_;
        std::vector<subref> incompat_;
        std::vector<subref> unknown_;

    public:
        subsystem(buffer & buf, size_t * offset);
        void printTree();
        
};

