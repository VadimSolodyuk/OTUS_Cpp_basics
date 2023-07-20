#include "vectorContainer.h"

#include <vector> 
#include <gtest/gtest.h>

#include <iostream>

TEST(vector, CreatingWithArgument) {
    // Arrange
    vectorContainer<int> myVector(0);
    int expectedElement = 0;
    size_t expectedSize = 1;
    // Assert
    EXPECT_EQ(myVector[0], expectedElement);
    EXPECT_EQ(myVector.getSize(), expectedSize);
};
size_t middle(size_t size) {
    if (size == 0) return 0;
    else if (!(size % 2 == 0)) return ((size + 1)/2);
        else return (size / 2);
}
struct vectorEmpty : public testing::Test {
    std::vector<int> vector;
    vectorContainer<int> myVector;
    int element = 555;

    template <typename T>
    void comparisonOfElements(vectorContainer<T>& myVector, std::vector<T>& vector) {
        for (size_t i{0}; i < vector.size(); ++i) {
            EXPECT_EQ(myVector[i], vector[i]);
        }
    }
};
TEST_F(vectorEmpty, CreatingWithoutArgument) {
    //Assert
    EXPECT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
};
TEST_F(vectorEmpty, pushBack) {
    //Act
    myVector.push_back(element);
    vector.push_back(element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorEmpty, insertFront) {
    //Act
    myVector.insert(myVector.begin(), element);
    vector.insert(vector.begin(), element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorEmpty, insertMiddle) {
    //Act
    myVector.insert(myVector.begin() + middle(myVector.getSize()), element);
    vector.insert(vector.begin() + middle(vector.size()), element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorEmpty, copyingСontainer) {
    // Arrange
    vectorContainer<int> myVectorNew;
    //Act
    myVectorNew = myVector;
    //Assert
    ASSERT_EQ(myVectorNew.getSize(), myVector.getSize());
    for (size_t i{0}; i < myVector.getSize(); ++i) {
        EXPECT_EQ(myVectorNew[i], myVector[i]);
    }   
}

struct vectorNotEmpty : public testing::Test {
    int element = 1;
    std::vector<int> vector;
    vectorContainer<int> myVector;

    template <typename T>
    void comparisonOfElements(vectorContainer<T>& myVector, std::vector<T>& vector) {
        for (size_t i{0}; i < vector.size(); ++i) {
            EXPECT_EQ(myVector[i], vector[i]);
        }    
    }

    void SetUp() override { 
        int elements[] = {0,1,2,3,4,5,6,7,8,9};
        for (auto &i : elements) {
            myVector.push_back(i);
            vector.push_back(i);
        }
        ASSERT_EQ(myVector.getSize(), vector.size());
        comparisonOfElements(myVector, vector);
    }
};
TEST_F(vectorNotEmpty, pushBack) {
    //Act
    myVector.push_back(element);
    vector.push_back(element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, insertFront) {
    //Act
    myVector.insert(myVector.begin(), element);
    vector.insert(vector.begin(), element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, insertMiddle) {
    // Arrange
    element = 555;
    //Act
    myVector.insert(myVector.begin() + middle(myVector.getSize()), element);
    vector.insert(vector.begin() + middle(vector.size()), element);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, eraseBack) {
    //Act
    myVector.erase(myVector.end()-1);
    vector.erase(vector.end()-1);
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, eraseFront) {
    //Act
    myVector.erase(myVector.begin());
    vector.erase(vector.begin());
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, eraseMiddle) {
    //Act
    myVector.erase(myVector.begin() + middle(myVector.getSize()));
    vector.erase(vector.begin() + middle(vector.size()));
    //Assert
    ASSERT_EQ(myVector.getSize(), vector.size());
    comparisonOfElements(myVector, vector);
}
TEST_F(vectorNotEmpty, copyingСontainer) {
    // Arrange
    vectorContainer<int> myVectorNew;
    //Act
    myVectorNew = myVector;
    //Assert
    ASSERT_EQ(myVectorNew.getSize(), myVector.getSize());
    for (size_t i{0}; i < myVector.getSize(); ++i) {
        EXPECT_EQ(myVectorNew[i], myVector[i]);
    }   
}
// TEST_F(vectorNotEmpty, deletingСontainer) {
//     // Arrange
//     size_t expectedSize = 0;

//     //Act
//     myVector.~vectorContainer();
//     //Assert
//     EXPECT_EQ(myVector.getSize(), expectedSize);
//     for (size_t i{0}; i < myVector.getSize(); ++i) {
// std::cout << myVector.getSize() << " s|" << "\n";
// std::cout << myVector[i] << " |" << "\n";
//         // EXPECT_EQ(myVectorNew[i], myVector[i]);
//     }   
// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// std::cout << myVector.getSize() << " s|s "  << vector.size() << "\n";
// std::cout << myVector[i] << " | " << vector[i] << "\n";

// std::cout << myVector[i] << " -|- "  << myVectorNew[i] << "\n";
// std::cout << myVector.getSize() << " s|s "  << myVectorNew.getSize() << "\n";