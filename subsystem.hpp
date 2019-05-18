#include <string>
#include <vector>

#pragma once

class subsystem
{
    private:
        string name_;
        string description_;
        size_t offset_;
        std::vector<subref> prereq_;
        std::vector<subref> incompat_;

    public:
        subsystem();

}
