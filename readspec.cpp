#include <iostream>
#include "buffer.hpp"
#include "product.hpp"

void parsespec(const char * filename)
{
    buffer buf(filename);
    product p(buf,21);
    std::cout << p.getName() << std::endl;
    std::cout << p.getId() << std::endl;
    std::cout << p.getCreationTime() << std::endl;
    p.printTree();
}

int main (int argc, char * argv[])
{
    char * filename;
    switch(argc)
    {
        case 2 :
            parsespec(argv[1]);
            break;
        default :
            fprintf(stderr,"Usage: %s [inst spec file]\n", argv[0]);
            break;
    }
    return EXIT_SUCCESS;
}
