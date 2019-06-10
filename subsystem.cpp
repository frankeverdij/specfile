#include "subsystem.hpp"

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

    if (buf.getInstType() > 8) {
        n = buf.getNum<unsigned short>(&off_end_);
        for (size_t i = 0; i < n; i++) {
            subref sr(buf, &off_end_);
            unknown_.push_back(sr);
        }
    }
    *offset = off_end_;
}

void subsystem::printTree()
{
    std::cout << "  " << getName() << std::endl;

    printSubRefList(replaces_," replaces");
    printSubRefList(prereq_," prereqs");
    printSubRefList(incompat_," incompats");
    printSubRefList(unknown_," unknowns");
}

