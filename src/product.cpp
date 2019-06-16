#include "product.hpp"
#include "printtree.hpp"
#include "chartools.hpp"
#include <ctime>

product::product(buffer & buf, tinyxml2::XMLDocument & xmlDoc, const size_t offset) : item(buf, xmlDoc, "product", offset)
{
    buf.getNum<unsigned short>(&off_end_);

    creation_time_ = buf.getNum<unsigned int>(&off_end_);

    std::string s_creation_time = getCreationTime(); 
    pElem_->SetAttribute("time", s_creation_time.c_str());
    xmlDoc.InsertFirstChild(pElem_);

    std::string dummy_string = buf.getString(&off_end_);

    size_t n_images = buf.getNum<unsigned short>(&off_end_);

    if (n_images == 0) {
        size_t n = buf.getNum<unsigned short>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            std::string s = buf.getString(&off_end_);
        }
        n_images = buf.getNum<unsigned short>(&off_end_);
    }
    
    for (size_t i = 0; i < n_images; i++) {
        size_t n = buf.getNum<unsigned short>(&off_end_);
        if (n == 0) {
            off_end_ += sizeof(unsigned short);
        }
        image im(buf, xmlDoc, pElem_, &off_end_);
        images_.push_back(im);
    }
}

std::string product::getCreationTime()
{
    std::string ret = ctime(&creation_time_);
    return removeNonPrintableChar(ret);
}

void product::printTree()
{
    std::cout << getName() << std::endl;
    printTreeList(images_," images",0);
}

