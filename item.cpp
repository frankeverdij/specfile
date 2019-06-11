#include "item.hpp"

item::item(buffer & buf,
            tinyxml2::XMLElement * pRoot,
            const std::string & ElemName,
            const size_t offset) :
                off_begin_(offset), off_end_(offset)
{
    name_ = buf.getString(&off_end_);
    id_ = buf.getString(&off_end_);
    pElem_ = pRoot->NewElement(ElemName);
    pRoot->InsertEndChild(pElem_);
};

std::string item::getName()
{
    return name_;
}

std::string item::getId()
{
    return id_;
}

