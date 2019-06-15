#include <vector>

template <typename T, typename A>  void printTreeList(
    std::vector<T,A> & vec, const std::string& treename, const size_t& n)
{
    if (vec.size()) {
        std::cout << std::string( n, ' ' ) << vec.size() << treename << std::endl;
        for (size_t i = 0; i < vec.size(); i++) {
            vec[i].printTree();
        }
    }
}
