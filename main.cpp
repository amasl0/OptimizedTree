#include <iostream>
#include <vector>
#include "optimized-tree.h"


int main()
{
//    tree FirstTree;
//    std::vector<int> x(10000); // вектор из десяти элементов
//
//    for (int i = 0; i < 10000; i++){
//        x[i] = i; // инициализация диапозоном от 0 до 10 (здесь вы можете указать свой диапозон)
//    }
//
//    srand(unsigned(time(0)));
//    random_shuffle(x.begin(), x.end()); // перемешиваеаем
//
//    for (int i = 0; i < 10000; i++){
//        FirstTree.insert(x[i]);
//    }
//
//    FirstTree.balanced();

    std::vector<int> values_first = {30, 1, 2, 8, 38, 25, 31};
std::vector<int> values_second = {30, 1, 5, 20, 38, 31, 22};
tree FirstTree;
FirstTree.insert(30);
FirstTree.insert(1);
FirstTree.insert(2);
FirstTree.insert(8);
FirstTree.insert(38);
FirstTree.insert(25);
FirstTree.insert(31);
FirstTree.balanced();
tree SecondTree;
SecondTree.insert(30);
SecondTree.insert(1);
SecondTree.insert(5);
SecondTree.insert(20);
SecondTree.insert(38);
SecondTree.insert(31);
SecondTree.insert(22);
SecondTree.balanced();
std::cout << "First values: { ";
for(auto it = values_first.begin(); it != values_first.end(); it++)
    std::cout << *it << " ";
std::cout << "};";
std::cout << " A = ";
FirstTree.print_direct();
std::cout << "Second values: { ";
for(auto it = values_second.begin(); it != values_second.end(); it++)
    std::cout << *it << " ";
std::cout << "};";
std::cout << " B = ";
SecondTree.print_simmetric();
std::cout << std::endl << "A ^ B = ";
(FirstTree^SecondTree).print_direct();

    // FirstTree.print_simmetric();
    // FirstTree.print_direct();
    std::cout << "N_op: " << FirstTree.N_op << ";" << std::endl;
    //FirstTree.print_reverse();
    return 0;
}
