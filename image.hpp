#include <string>
#include <vector>
#include "subsystem.hpp"

#pragma once

class image
{
    private:
        string name_;
        string description_;
        size_t offset_;
        std::vector<subsystem> subsystems;

    public:
        image();

}
