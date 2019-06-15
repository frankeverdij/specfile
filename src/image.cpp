#include "image.hpp"
#include "printtree.hpp"

image::image(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset) : item(buf, xmlDoc, "image", *offset)
{
    version_ = buf.getNum<unsigned short>(&off_end_);
    order_ = buf.getNum<unsigned short>(&off_end_);

    pElem_->SetAttribute("version", (int)version_);
    pElem_->SetAttribute("order", (int)order_);
    pRoot->InsertEndChild(pElem_);

    for (size_t i = 0; i < 2 ; i++) {
        v_[i] = buf.getNum<unsigned int>(&off_end_);
    }

    size_t n_subs = buf.getNum<unsigned int>(&off_end_);
    if (n_subs == 0) n_subs = buf.getNum<unsigned int>(&off_end_);

    for (size_t i = 0; i < n_subs; i++) {
        size_t n = buf.getNum<unsigned short>(&off_end_);
        if (n == 0) {
            off_end_ += sizeof(unsigned short);
        }
        subsystem sb(buf, xmlDoc, pElem_, &off_end_);
        subsystems_.push_back(sb);
    }

    *offset = off_end_;
}

void image::printTree()
{
    std::cout << " " << getName() << std::endl;
    printTreeList(subsystems_," subsystems",1);
}
