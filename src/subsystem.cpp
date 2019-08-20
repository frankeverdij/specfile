#include "subsystem.hpp"
#include "printtree.hpp"

subref::subref(subrefcat_t category, buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset) : category_(category)
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
    std::cout << std::string( 3, ' ' ) << subrefcatstr[category_] << " " << name_;
    std::cout << " " << v_[0] << " " << v_[1] << std::endl;
}

subsystem::subsystem(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, unsigned short headerbits, size_t * offset) : item(buf, xmlDoc, pRoot, "subsystem", *offset), bits_(headerbits)
{
    tinyxml2::XMLElement * pAttr;

    expanded_name_ = buf.getString(&off_end_);

    if (bits_ & SUBSYS_REQUIRED) {
        pAttr = xmlDoc.NewElement("required");
        pElem_->InsertEndChild(pAttr);
    }
    if (bits_ & SUBSYS_DEFAULT) {
        pAttr = xmlDoc.NewElement("default");
        pElem_->InsertEndChild(pAttr);
    }
    if (bits_ & SUBSYS_PATCH) {
        pAttr = xmlDoc.NewElement("patch");
        pElem_->InsertEndChild(pAttr);
    }
    if (!(bits_ & SUBSYS_NO_MINIROOT)) {
        pAttr = xmlDoc.NewElement("miniroot");
        pElem_->InsertEndChild(pAttr);
    }

    pAttr = xmlDoc.NewElement("exp");
    pAttr->SetText(expanded_name_.c_str());
    pElem_->InsertEndChild(pAttr);

    off_end_ += sizeof(unsigned int);

    makeSubRefEntry(SUBREFCAT_REPLACES, buf, xmlDoc, &off_end_);

    off_end_ += sizeof(unsigned short);

    size_t n = makeSubRefEntry(SUBREFCAT_PREREQ, buf, xmlDoc, &off_end_);

    if (n > 0) {
        off_end_ += sizeof(unsigned short);
    }

    if (buf.getInstType() > 7) {
        makeSubRefEntry(SUBREFCAT_INCOMPAT, buf, xmlDoc, &off_end_);
        n = buf.getNum<unsigned int>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            std::string s = buf.getString(&off_end_);
        }
    }

    if (buf.getInstType() > 8) {
        makeSubRefEntry(SUBREFCAT_UPDATES, buf, xmlDoc, &off_end_);
    }
    *offset = off_end_;
}

size_t subsystem::makeSubRefEntry(subrefcat_t category, buffer & buf, tinyxml2::XMLDocument & xmlDoc, size_t * offset)
{
    size_t n = buf.getNum<unsigned short>(offset);
    tinyxml2::XMLElement *pNew;

    // handle patch subsystems differently: if it is a patch subsystem and the
    // number of replaces is not zero, the first one will be categorized as "follows"
    if (bits_ & SUBSYS_PATCH) {
        if ((n > 0) && (category == SUBREFCAT_REPLACES)) {
            pNew = xmlDoc.NewElement(subrefcatstr[SUBREFCAT_FOLLOWS].c_str());
            pElem_->InsertEndChild(pNew);
            subref sr(SUBREFCAT_FOLLOWS, buf, xmlDoc, pNew, offset);
            subrefcat_.push_back(sr);
            n--;
        }
    }
    if (n > 0) {
        pNew = xmlDoc.NewElement(subrefcatstr[category].c_str());
        pElem_->InsertEndChild(pNew);

        for (size_t i = 0; i < n; i++) {
            subref sr(category, buf, xmlDoc, pNew, offset);
            subrefcat_.push_back(sr);
        }
    }
    return n;
}

void subsystem::printTree()
{
    std::cout << "  " << getName() << std::endl;

    for (size_t i = 0; i < subrefcat_.size(); i++) {
        subrefcat_[i].printTree();
    }
}

