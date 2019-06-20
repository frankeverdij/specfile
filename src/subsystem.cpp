#include "subsystem.hpp"
#include "printtree.hpp"

subref::subref(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset)
{
    for (size_t i = 0; i < 3; i++) {
        name_sub_[i] = buf.getString(offset);
    }
    for (size_t i = 0; i < 2; i++)
        v_[i] = buf.getNum<unsigned int>(offset);

    name_ = name_sub_[0] + "." + name_sub_[1] + "." + name_sub_[2];

    pElem_ = xmlDoc.NewElement("subref");
    pElem_->SetAttribute("name", name_.c_str());
    pElem_->SetAttribute("minvers", v_[0]);
    pElem_->SetAttribute("maxvers", v_[1]);
    pRoot->InsertEndChild(pElem_);
}

void subref::printTree()
{
    std::cout << "   " << name_;
    std::cout << " " << v_[0] << " " << v_[1] << std::endl;
}

subsystem::subsystem(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, unsigned short headerbits, size_t * offset) : item(buf, xmlDoc, pRoot, "subsystem", *offset), bits_(headerbits)
{
    expanded_name_ = buf.getString(&off_end_);
    bool is_default = (bits_ & SUBSYS_DEFAULT);
    pElem_->SetAttribute("default",  is_default);

    tinyxml2::XMLElement *pAttr = xmlDoc.NewElement("exp");
    pAttr->SetText(expanded_name_.c_str());
    pElem_->InsertEndChild(pAttr);

    off_end_ += sizeof(unsigned int);

    makeSubRefEntry(replaces_, "replace", buf, xmlDoc, pElem_, &off_end_);

    off_end_ += sizeof(unsigned short);

    size_t n = makeSubRefEntry(prereq_, "prereq", buf, xmlDoc, pElem_, &off_end_);

    if (n > 0) {
        off_end_ += sizeof(unsigned short);
    }

    if (buf.getInstType() > 7) {
        makeSubRefEntry(incompat_, "incompat", buf, xmlDoc, pElem_, &off_end_);
        n = buf.getNum<unsigned int>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            std::string s = buf.getString(&off_end_);
        }
    }

    if (buf.getInstType() > 8) {
        makeSubRefEntry(unknown_, "unknown", buf, xmlDoc, pElem_, &off_end_);
    }
    *offset = off_end_;
}

size_t subsystem::makeSubRefEntry(std::vector<subref> & vec, std::string category, buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset)
{
    size_t n = buf.getNum<unsigned short>(offset);
    if (n > 0) {
        tinyxml2::XMLElement *pElem = xmlDoc.NewElement(category.c_str());
        pRoot->InsertEndChild(pElem);

        for (size_t i = 0; i < n; i++) {
            subref sr(buf, xmlDoc, pElem, offset);
            vec.push_back(sr);
        }
    }
    return n;
}

void subsystem::printTree()
{
    std::cout << "  " << getName() << std::endl;

    printTreeList(replaces_," replaces", 2);
    printTreeList(prereq_," prereqs", 2);
    printTreeList(incompat_," incompats", 2);
    printTreeList(unknown_," unknowns", 2);
}

