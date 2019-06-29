#include <vector>
#include "item.hpp"

#pragma once

typedef enum {
    SUBSYS_REQUIRED    = 0x1,
    SUBSYS_DEFAULT     = 0x2,
    SUBSYS_PATCH       = 0x400,
    SUBSYS_NO_MINIROOT = 0x800
} subsys_t;

class subref
{
    private:
        std::string name_sub_[3];
        std::string name_;
        unsigned int v_[2];
        tinyxml2::XMLElement *pElem_;

    public:
        subref(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset);
        void printTree();
};

class subsystem : public item
{
    private:
        std::string expanded_name_;
        unsigned short bits_;
        std::vector<subref> follows_;
        std::vector<subref> replaces_;
        std::vector<subref> prereq_;
        std::vector<subref> incompat_;
        std::vector<subref> updates_;

    public:
        subsystem(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, unsigned short n, size_t * offset);
        size_t makeSubRefEntry(std::vector<subref> & vec, std::string category, buffer & buf, tinyxml2::XMLDocument & xmlDoc, size_t * offset);
        void printTree();
        
};

