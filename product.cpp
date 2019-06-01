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

product::product(buffer & buf, const size_t offset) : item(buf, offset)
{
    off_end_ += sizeof(unsigned short);
    
    creation_time_ = buf.getNum<unsigned int>(&off_end_);

    off_end_ += sizeof(unsigned short);
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
    version_ = buf.getNum<unsigned short>(&off_end_);
    order_ = buf.getNum<unsigned short>(&off_end_);
    for (size_t i = 0; i < 2 ; i++) {
        v_[i] = buf.getNum<unsigned int>(&off_end_);
    }
    size_t n_subs = buf.getNum<unsigned int>(&off_end_);
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
    std::cout << getName() << std::endl;
    std::cout << subsystems_.size() << " subsystems" << std::endl;
    for (size_t i = 0; i < subsystems_.size(); i++) {
        std::cout << subsystems_[i].getName() << std::endl;
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

    n = buf.getNum<unsigned short>(&off_end_);
    for (size_t i = 0; i < n; i++) {
        subref sr(buf, &off_end_);
        incompat_.push_back(sr);
    }

    off_end_ += sizeof(unsigned short);
    n = buf.getNum<unsigned short>(&off_end_);
    for (size_t i = 0; i < n; i++) {
        std::string s = buf.getString(&off_end_);
    }

    *offset = off_end_;
}

