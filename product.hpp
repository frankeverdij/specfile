#include <string>
#include <vector>
#include "buffer.hpp"

#pragma once

class item
{
    protected:
        std::string name_;
        std::string id_;
        size_t off_begin_, off_end_;
    
    public:
        item(buffer & buf, const size_t offset);
        std::string getName();
        std::string getId();
        size_t getEndOffset();
};

class subref
{
    private:
        std::string name_sub_[3];
        unsigned int v_[2];

    public:
        subref(buffer & buf, size_t * offset);
        void printRef();
};

class subsystem : public item
{
    private:
        std::string expanded_name_;
        std::vector<subref> replaces_;
        std::vector<subref> prereq_;
        std::vector<subref> incompat_;

    public:
        subsystem(buffer & buf, size_t * offset);
        void printTree();

};

class image : public item
{
    private:
        size_t version_, order_, v_[2];
        std::vector<subsystem> subsystems_;

    public:
        image(buffer & buf, size_t * offset);
        void printTree();

};

class product : public item
{
    private:
        time_t creation_time_;
        std::vector<image> images_;

    public:
        product(buffer & buf, const size_t offset);
        std::string getCreationTime();
        void printTree();
        
};

