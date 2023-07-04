#include "../include/vectorContainer.h"
#include "../include/listContainer.h"
#include "../include/functions.h"

#include <cstddef>
#include <iostream>

int main() {

    // 1.Сreating containers
    std::cout << "\n\tTask 1:\n";
    vectorContainer<int> vector;
    outData(vector, std::cout);

    listContainer<int> list;
    outData(list, std::cout);

    // 2.Adding elements
    int elements[] = {0,1,2,3,4,5,6,7,8,9};

    for (auto &i : elements) {
        vector.push_back(i);
        list.push_back(i);
    }
    
    // 3.Outputting the contents of the container
    std::cout << "\n\tTask 2, 3:\n";
    outData(vector, std::cout);
    outData(list, std::cout);

    // 4.Output of container size
    std::cout << "\n\tTask 4:\n";
    outSize(vector, list, std::cout);

    // 5.Deleting elements #3, 5, 7
    size_t delPosElements[] {3,5,7};

    size_t count{0};
    for (auto &i : delPosElements) {
        vector.erase(i-count);
        list.erase(i-count);
        ++count;
    }

    // 6.Outputting the contents of the container
    std::cout << "\n\tTask 5, 6:\n";
    outData(vector, std::cout);
    outData(list, std::cout);

    // 7.Adding an element to the beginning
    int element{10};

    vector.insert(1, element);
    list.insert(1, element);

    // 8.Outputting the contents of the container
    std::cout << "\n\tTask 7, 8:\n";
    outData(vector, std::cout);
    outData(list, std::cout);

    // 9.Adding an element to the middle
    element = 20;

    insertDataToMiddle(vector, element);
    insertDataToMiddle(list, element);

    // 10.Outputting the contents of the container
    std::cout << "\n\tTask 9, 10:\n";
    outData(vector, std::cout);
    outData(list, std::cout);

    // 11.Adding an element to the end
    element = 30;

    vector.push_back(element);
    list.push_back(element);
    
    
    // 12.Outputting the contents of the container
    std::cout << "\n\tTask 11, 12:\n";
    outData(vector, std::cout);
    outData(list, std::cout);

    //
    std::cout << "\n  Freeing up memory:" << std::endl;
    
    return 0;
};
