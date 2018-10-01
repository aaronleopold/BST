#include <iostream>
#include <string>
#include "BST.h"

int main()
{
    BST<int> tree;

    tree.add(10);
    tree.add(11);
    tree.add(4);

   int nums[] = {54, 0, 1, 12, 15, 17, 3, 75, 42, 22, 61, 39, 28, 105, 97, 7};
    tree.add(nums, 16);
	tree.remove(4);
    tree.remove(12);
    tree.clear();

    tree.print(true);
    //tree.clear();
    //std::cout << std::endl;
    //tree.print(false);
    //std::cout << std::endl;
    //std::cout << tree.size() << std::endl;


    return 0;
}