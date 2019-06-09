#include "product.hpp"
#include <ctime>

item::item(buffer & buf, const size_t offset) :
             off_begin_(offset), off_end_(offset)
{
    name_ = buf.getString(&off_end_);
    id_ = buf.getString(&off_end_);
};

std::string item::getName()
{
    return name_;
}

std::string item::getId()
{
    return id_;
}

subref::subref(buffer & buf, size_t * offset)
{
    for (size_t i = 0; i < 3; i++) {
        name_sub_[i] = buf.getString(offset);
    }
    for (size_t i = 0; i < 2; i++)
        v_[i] = buf.getNum<unsigned int>(offset);
}

void subref::printRef()
{
    std::cout << "   " << name_sub_[0] << "." << name_sub_[1] << "." << name_sub_[2];
    std::cout << " " << v_[0] << " " << v_[1] << std::endl;
}

product::product(buffer & buf, const size_t offset) : item(buf, offset)
{
    size_t dummy = buf.getNum<unsigned short>(&off_end_);

    creation_time_ = buf.getNum<unsigned int>(&off_end_);

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
        image im(buf, &off_end_);
        images_.push_back(im);
    }
}

std::string product::getCreationTime()
{
    return ctime(&creation_time_);
}

void product::printTree()
{
    std::cout << getName() << std::endl;
    std::cout << images_.size() << " images" << std::endl;
    for (size_t i = 0; i < images_.size(); i++) {
        images_[i].printTree();
    }
}

image::image(buffer & buf, size_t * offset) : item(buf, *offset)
{
    std::cout << "in image, offset 0x" << std::hex << *offset << std::dec << std::endl;
    version_ = buf.getNum<unsigned short>(&off_end_);
    order_ = buf.getNum<unsigned short>(&off_end_);
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
        subsystem sb(buf, &off_end_);
        subsystems_.push_back(sb);
    }

    *offset = off_end_;
}

void image::printTree()
{
    std::cout << " " << getName() << std::endl;
    std::cout << " " << subsystems_.size() << " subsystems" << std::endl;
    for (size_t i = 0; i < subsystems_.size(); i++) {
        subsystems_[i].printTree();
    }
}

subsystem::subsystem(buffer & buf, size_t * offset) : item(buf, *offset)
{
    expanded_name_ = buf.getString(&off_end_);
    off_end_ += sizeof(unsigned int);

    size_t n = buf.getNum<unsigned short>(&off_end_);
    for (size_t i = 0; i < n; i++) {
        subref sr(buf, &off_end_);
        replaces_.push_back(sr);
    }

    off_end_ += sizeof(unsigned short);
    n = buf.getNum<unsigned short>(&off_end_);
    if (n > 0) {
        for (size_t i = 0; i < n; i++) {
            subref sr(buf, &off_end_);
            prereq_.push_back(sr);
        }
        off_end_ += sizeof(unsigned short);
    }

    if (buf.getInstType() > 7) {
        n = buf.getNum<unsigned short>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            subref sr(buf, &off_end_);
            incompat_.push_back(sr);
        }

        n = buf.getNum<unsigned int>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            std::string s = buf.getString(&off_end_);
        }
    }
    *offset = off_end_;
}

void subsystem::printTree()
{
    std::cout << "  " << getName() << std::endl;

    if (replaces_.size()) {
        std::cout << "  " << replaces_.size() << " replaces" << std::endl;
        for (size_t i = 0; i < replaces_.size(); i++) {
            replaces_[i].printRef();
        }
    }
    if (prereq_.size()) {    
        std::cout << "  " << prereq_.size() << " prereqs" << std::endl;
        for (size_t i = 0; i < prereq_.size(); i++) {
            prereq_[i].printRef();
        }
    }
    if (incompat_.size()) {
        std::cout << "  " << incompat_.size() << " incompats" << std::endl;
        for (size_t i = 0; i < incompat_.size(); i++) {
            incompat_[i].printRef();
        }
    }
}

