#include <vector>
#include "item.hpp"

#pragma once

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
        std::vector<subref> unknown_;

    public:
        subsystem(buffer & buf, size_t * offset);
        void printTree();
        template<typename T, typename A>
            void printSubRefList( std::vector<T,A> & vec, const std::string& subsys)
        {
            if (vec.size()) {
                std::cout << "  " << vec.size() << subsys << std::endl;
                for (size_t i = 0; i < vec.size(); i++) {
                    vec[i].printRef();
                }
            }
        }

};

