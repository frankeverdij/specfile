#include <string>
#include <vector>

#pragma once

class item
{
    protected:
        string name_;
        string id_;
        size_t offset_;
    
    public:
        void setName(string &);
        string getName();
        void setDescription(string &);
        string getDescription();
        void setOffset(size_t &);
        size_t getOffset();
}

class subsystem : public item
{
    private:
        string expanded_name_;
        std::vector<subref> replaces_;
        std::vector<subref> prereq_;
        std::vector<subref> incompat_;

    public:
        subsystem();

}

class image : public item
{
    private:
        unsigned int version_;
        size_t order_;
        std::vector<subsystem> subsystems;

    public:
        image();

}

class product : public item
{
    private:
        time_t creation_time_;
        std::vector<image> images;

    public:
        product();
        void setTime(time_t &);
        time_t getTime();
        
};

