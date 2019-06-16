#include <string>
#include <algorithm>

#pragma once

static bool notPrintableChar (char c) 
{  
    return !(c>=32 && c <128);   
} 

static std::string removeNonPrintableChar(std::string str)
{
    std::string ret(str);
    ret.erase(std::remove_if(ret.begin(),ret.end(), notPrintableChar), ret.end());
    return ret;
}
