#include "image.hpp"
#include "printtree.hpp"

image::image(buffer & buf, size_t * offset) : item(buf, *offset)
{
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
    printTreeList(subsystems_," subsystems",1);
}
