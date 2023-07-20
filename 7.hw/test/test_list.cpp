#include "listContainer.h"

#include <list> 
#include <gtest/gtest.h>

#include <iostream>

TEST(list, CreatingWithArgument) {
    // Arrange
    listContainer<int> myList(0);
    int expectedElement = 0;
    size_t expectedSize = 1;
    // Assert
    EXPECT_EQ(myList[0], expectedElement);
    EXPECT_EQ(myList.getSize(), expectedSize);
}
struct listEmpty : public testing::Test {
    listContainer<int> myList;
    std::list<int> list;
    int element = 555;

    template <typename T>
    void comparisonOfElements(listContainer<T>& myList, std::list<T>& list) {
        auto iterList = list.begin();
        for (size_t i{0}; i < list.size(); ++i) {
            T elementList = *iterList;
            EXPECT_EQ(myList[i], elementList);
            ++iterList;
        }
    }
};
TEST_F(listEmpty, CreatingWithoutArgument) {
    // Assert
    EXPECT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listEmpty, pushBack) {
    //Act
    myList.push_back(element);
    list.push_back(element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listEmpty, insertFront) {
    //Act
    myList.insert(myList.begin(), element);
    list.insert(list.begin(), element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}

template <typename T>
auto middleList(const std::list<T>& list) {
    auto iterList = list.begin();
    if (list.size() == 0) return iterList;
    else if (!(list.size() % 2 == 0)) {
        for (size_t i{0}; i < ((list.size() + 1)/2); ++i) {
        ++iterList;
        }
    }
    else {
        for (size_t i{0}; i < (list.size() /2); ++i) {
            ++iterList;
        }  
    } 
    return iterList;
};
template <typename T>
auto middleMyList(const listContainer<T>& list) {
    auto iterList = list.begin();
    if (list.getSize() == 0) return iterList;
    else if (!(list.getSize() % 2 == 0)) {
        for (size_t i{0}; i < ((list.getSize() + 1)/2); ++i) {
        ++iterList;
        }
    }
    else {
        for (size_t i{0}; i < (list.getSize() /2); ++i) {
            ++iterList;
        }  
    } 
    return iterList;
};

TEST_F(listEmpty, insertMiddle) {
    //Act
    myList.insert(middleMyList(myList), element);
    list.insert(middleList(list), element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listEmpty, copyingСontainer) {
    // Arrange
    listContainer<int> myListNew;
    //Act
    myListNew = myList;
    //Assert
    ASSERT_EQ(myListNew.getSize(), myList.getSize());
    for (size_t i{0}; i < myList.getSize(); ++i) {
        EXPECT_EQ(myListNew[i], myList[i]);
    }   
}

struct listNotEmpty : public testing::Test {
    std::list<int> list;
    listContainer<int> myList;
    int element = 555;

    template <typename T>
    void comparisonOfElements(listContainer<T>& myList, std::list<T>& list) {
        auto itrerList = list.begin();
        for (size_t i{0}; i < list.size(); ++i) {
            T elementList = *itrerList;
            EXPECT_EQ(myList[i], elementList);
            ++itrerList;
        }    
    }
    
    void SetUp() override { 
        int elements[] = {0,1,2,3,4,5,6,7,8,9};
        for (auto &i : elements) {
            myList.push_back(i);
            list.push_back(i);
        }
    }
};
TEST_F(listNotEmpty, pushBack) {
    //Act
    myList.push_back(element);
    list.push_back(element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, insertFront) {
    //Act
    myList.insert(myList.begin(), element);
    list.insert(list.begin(), element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, insertMiddle) {
    //Act
    myList.insert(middleMyList(myList), element);
    list.insert(middleList(list), element);
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, eraseBack) {
    //Act
    myList.erase(myList.end()-1);
    list.pop_back();
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, eraseFront) {
    //Act
    myList.erase(myList.begin());
    list.pop_front();
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, eraseMiddle) {
    //Act
    myList.erase(middleMyList(myList)); //(middle(myList.getSize()))
    list.erase(middleList(list));
    // Assert
    ASSERT_EQ(myList.getSize(), list.size());
    comparisonOfElements(myList, list);
}
TEST_F(listNotEmpty, copyingСontainer) {
    // Arrange
    listContainer<int> myListNew;
    //Act
    myListNew = myList;
    //Assert
    ASSERT_EQ(myListNew.getSize(), myList.getSize());
    for (size_t i{0}; i < myList.getSize(); ++i) {
        EXPECT_EQ(myListNew[i], myList[i]);
    }   
}

// std::cout << myList.getSize() << " s|s "  << list.size() << "\n";
// std::cout << myList[i] << " | " << elementList << "\n";

// std::cout << myListNew[i] << " -|- "  << myList[i] << "\n";
// std::cout << myListNew.getSize() << " s|s "  << myList.getSize() << "\n";


// for (size_t i{0}; i < list.size(); ++i) {
//     std::cout << myList[i] << ", ";
// }
// std::cout << "\n";
// for (size_t i{0}; i < list.size(); ++i) {
//     std::cout << list[i] << ", ";
// }
// std::cout << "\n";

// std::cout << myList.getSize() << " " << myList.getCapaciti()<< "; "
//  << list.size() << " " << list.capacity() << "\n";

// for (size_t i{0}; i < list.size(); ++i) {
//     std::cout << myList[i] << ", ";
// }
// std::cout << "\n";
// for (size_t i{0}; i < list.size(); ++i) {
//     std::cout << list[i] << ", ";
// }
// std::cout << "\n";