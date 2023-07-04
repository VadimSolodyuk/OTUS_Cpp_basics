#pragma once

#include "vectorContainer.h"
#include "listContainer.h"

template <typename C>
void outData(C& container, std::ostream& os) {
    if (container.getSize() == 0) os << container.getName() << " is empty\n\n";
    else {
        os << container.getName() << " contains: " << "\t";
        for (auto iter = container.begin(); iter != container.end(); ++iter) {
            if (iter == container.begin()) os << iter.get();
            else os << ", " << iter.get();
        }
        os << ";\n";        
    }
}
    
template <typename V, typename L>
void outSize(V& vector, L& list, std::ostream& os) {
    if (vector.getSize() == 0) os << vector.getName() << " is empty\n";
    else {
        os << vector.getName() << " size- " << vector.getSize();
        os << ", capaciti- " << vector.getCapaciti() << ";\n";        
    }
    if (list.getSize() == 0) os << list.getName() << " is empty\n";
    else {
        os << list.getName() << "   size- " << list.getSize() << ";\n";        
    }
}

template <typename C, typename T>
void insertDataToMiddle(C& container, T data) {
    size_t middle{0};
    if (container.getSize() == 0) container.push_back(data);
    else if (!(container.getSize() % 2 == 0)) middle = (container.getSize() + 1)/2;
        else middle = container.getSize() / 2;
    container.insert(middle+1, data);
}