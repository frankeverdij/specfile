#include "buffer.hpp"
#include <tinyxml2.h>

#pragma once

class item
{
    protected:
        std::string name_;
        std::string id_;
        tinyxml2::XMLElement *pElem_;
        size_t off_begin_, off_end_;
    
    public:
        item(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, const std::string & ElemName, const size_t offset);
        item(buffer & buf, tinyxml2::XMLDocument & xmlDoc, const std::string & ElemName, const size_t offset);
        std::string getName();
        std::string getId();
        size_t getEndOffset();
};

