#include "item.hpp"

item::item(buffer & buf,
            tinyxml2::XMLDocument & xmlDoc,
            tinyxml2::XMLElement * pRoot,
            const std::string & ElemName,
            const size_t offset) :
                off_begin_(offset), off_end_(offset)
{
    initVars(buf);
    pElem_ = xmlDoc.NewElement(ElemName.c_str());
    pElem_->SetAttribute("name", name_.c_str());
    pElem_->SetAttribute("id", id_.c_str());
    pRoot->InsertEndChild(pElem_);
};

item::item(buffer & buf,
            tinyxml2::XMLDocument & xmlDoc,
            const std::string & ElemName,
            const size_t offset) :
                off_begin_(offset), off_end_(offset)
{
    initVars(buf);
    pElem_ = xmlDoc.NewElement(ElemName.c_str());
    pElem_->SetAttribute("name", name_.c_str());
    pElem_->SetAttribute("id", id_.c_str());
    xmlDoc.InsertFirstChild(pElem_);
};

void item::initVars(buffer & buf)
{
    name_ = buf.getString(&off_end_);
    id_ = buf.getString(&off_end_);
}

std::string item::getName()
{
    return name_;
}

std::string item::getId()
{
    return id_;
}

