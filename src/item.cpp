#include "item.hpp"

item::item(buffer & buf,
            tinyxml2::XMLDocument & xmlDoc,
            const std::string & ElemName,
            const size_t offset) :
                off_begin_(offset), off_end_(offset)
{
    name_ = buf.getString(&off_end_);
    id_ = buf.getString(&off_end_);

    pElem_ = xmlDoc.NewElement(ElemName.c_str());
    pElem_->SetAttribute("name", name_.c_str());
    pElem_->SetAttribute("id", id_.c_str());
};

std::string item::getName()
{
    return name_;
}

std::string item::getId()
{
    return id_;
}

