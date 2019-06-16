#include "image.hpp"
#include "printtree.hpp"

image::image(buffer & buf, tinyxml2::XMLDocument & xmlDoc, tinyxml2::XMLElement * pRoot, size_t * offset) : item(buf, xmlDoc, "image", *offset)
{
    counter_ = buf.getNum<unsigned short>(&off_end_);
    order_ = buf.getNum<unsigned short>(&off_end_);

    for (size_t i = 0; i < 2 ; i++) {
        v_[i] = buf.getNum<unsigned int>(&off_end_);
    }

    pElem_->SetAttribute("counter", (int)counter_);
    pElem_->SetAttribute("order", (int)order_);
    pElem_->SetAttribute("version", (int)v_[0]);
//    pElem_->SetAttribute("version2", (int)v_[1]);
    pRoot->InsertEndChild(pElem_);

    size_t n_subs = buf.getNum<unsigned int>(&off_end_);
    if (n_subs == 0) n_subs = buf.getNum<unsigned int>(&off_end_);

    for (size_t i = 0; i < n_subs; i++) {
        unsigned short n = buf.getNum<unsigned short>(&off_end_);
        if (n == 0) {
            n = buf.getNum<unsigned short>(&off_end_);
        }
        subsystem sb(buf, xmlDoc, pElem_, n, &off_end_);
        subsystems_.push_back(sb);
    }

    *offset = off_end_;
}

void image::printTree()
{
    std::cout << " " << getName() << std::endl;
    printTreeList(subsystems_," subsystems",1);
}
