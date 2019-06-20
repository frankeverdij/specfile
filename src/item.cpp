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
    xmlDoc.InsertFirstChild(pElem_);
    tinyxml2::XMLElement *pAttr = xmlDoc.NewElement("id");
    pAttr->SetText(id_.c_str());
    pElem_->InsertEndChild(pAttr);
}

item::item(buffer & buf,
            tinyxml2::XMLDocument & xmlDoc,
            tinyxml2::XMLElement *pRoot,
            const std::string & ElemName,
            const size_t offset) :
                off_begin_(offset), off_end_(offset)
{
    name_ = buf.getString(&off_end_);
    id_ = buf.getString(&off_end_);

    pElem_ = xmlDoc.NewElement(ElemName.c_str());
    pElem_->SetAttribute("name", name_.c_str());
    pRoot->InsertEndChild(pElem_);
    tinyxml2::XMLElement *pAttr = xmlDoc.NewElement("id");
    pAttr->SetText(id_.c_str());
    pElem_->InsertEndChild(pAttr);
}

std::string item::getName()
{
    return name_;
}

std::string item::getId()
{
    return id_;
}

