#include <iostream>
#include "buffer.hpp"
#include "product.hpp"
#include <tinyxml2.h>

void parsespec(std::string filename)
{
    tinyxml2::XMLDocument xmlDoc;
    buffer buf(filename.c_str());
    product p(buf, xmlDoc, 19);
    std::cout << p.getName() << std::endl;
    std::cout << p.getId() << std::endl;
    std::cout << p.getCreationTime() << std::endl;
    p.printTree();

    std::string XMLfilename = filename + ".xml";
    tinyxml2::XMLError eResult = xmlDoc.SaveFile(XMLfilename.c_str());
    if (eResult != tinyxml2::XML_SUCCESS)
        std::cerr << "Error: " << eResult << std::endl;
}

int main (int argc, char * argv[])
{
    std::string filename;

    switch(argc)
    {
        case 2 :
            filename=argv[1];
            parsespec(filename);
            break;
        default :
            fprintf(stderr,"Usage: %s [inst spec file]\n", argv[0]);
            break;
    }
    return EXIT_SUCCESS;
}
