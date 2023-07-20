#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class vectorContainer { 
public:
    vectorContainer() {
        std::cout << "Creating a " << (*this).getName() << "\n";
    };
    explicit vectorContainer(const T data) {
        ++m_size;
        m_capacity +=2;
        m_data = new T [m_capacity];
        m_data[m_size-1] = data;
        std::cout << "Creating a " << (*this).getName() << std::endl;
    };
    vectorContainer(const vectorContainer& vector) : vectorContainer() {
        if (!vector.getSize()) return;
        m_size = vector.m_size;
        m_capacity = vector.m_capacity;
        m_data = new T [m_capacity];
        for (size_t i{0}; i < m_size; ++i) {
            m_data[i] = vector[i];
        }
    }
    ~vectorContainer() { 
        delete [] m_data;
        m_size = 0;
        m_capacity = 0;
        std::cout << "Deleting a " << (*this).getName() << std::endl;
    }
    vectorContainer& operator=(const vectorContainer& vector) {
        if (this->getSize() == vector.getSize()) {
            if (m_data == vector.m_data) 
                return *this;
        }
        if (m_size > 0) this->~vectorContainer();
        m_size = vector.m_size;
        m_capacity = vector.m_capacity;
        m_data = new T [m_capacity];
        for (size_t i{0}; i < m_size; ++i) {
            m_data[i] = vector[i];
        }
        return *this;
    }

    struct iterator {
        iterator(T data[], const size_t index) : m_index(index), m_dataIterator(data) { 
            m_iterator = &m_dataIterator[m_index];            
        }   

        iterator& operator++() {
            ++m_index;
            m_iterator = &m_dataIterator[m_index];
            return *this;
        }
        iterator& operator--() {
            --m_index;
            m_iterator = &m_dataIterator[m_index];
            return *this;
        }
        iterator& operator+(const size_t rhs) {
            m_index += rhs;
            m_iterator = &m_dataIterator[m_index];
            return *this;
        }
        iterator& operator-(const size_t rhs) {
            m_index -= rhs;
            m_iterator = &m_dataIterator[m_index];
            return *this;
        }
        bool operator==(const iterator& rhs) const {
            if (m_iterator == rhs.m_iterator) return true; 
                else return false;
        }
        bool operator!=(const iterator& rhs) const {
            if (m_iterator != rhs.m_iterator) return true; 
                else return false;
        }
        T& get() const {
            return *m_iterator;
        }
        size_t getIndex() const {
            return m_index;
        }
    private:
        size_t m_index{0};
        T*     m_dataIterator{nullptr};
        T*     m_iterator{nullptr};
    };

    T& operator[](const size_t index) const {
        if (index > m_size-1) throw std::invalid_argument 
            (R"("Error "Index out of range!" in the function vectorContainer::operator[])");
        return m_data[index];   
    }
    
    void push_back(const T value)  {
        ++m_size;
        if (realloc()) {
            for (size_t i{0}; i < m_size-1; ++i) {
                m_data[i] = m_old_data[i];
            }
            delete [] m_old_data;
        }
        m_data[m_size-1] = value;
    };
 
    void insert(const size_t pos, const T value)  { //pos - позиция (по счёту)
        ++m_size;
        if (pos == 0 || pos > m_size) throw std::invalid_argument 
            (R"(Fault "Position out of range!" in the function vectorContainer::insert(pos, value).)"); 
        if (realloc()) {
            for (size_t i = m_size-1; i > pos-1; --i) {
                m_data[i] = m_old_data[i-1];
            }
            for (size_t i = 0; i < pos-1; ++i) {
                m_data[i] = m_old_data[i];
            }
            delete [] m_old_data;
        }
        else for (size_t i = m_size-1; i > pos-1; --i) {
                m_data[i] = m_data[i-1];
            };
        m_data[pos-1] = value;
    };
    void insert(iterator iter, const T value)  { 
        ++m_size;
        if (realloc()) {
            for (size_t i = m_size-1; i > iter.getIndex(); --i) {
                m_data[i] = m_old_data[i-1];
            }
            for (size_t i = 0; i < iter.getIndex(); ++i) {
                m_data[i] = m_old_data[i];
            }
            delete [] m_old_data;
        }
        else for (size_t i = m_size-1; i > iter.getIndex(); --i) {
                m_data[i] = m_data[i-1];
            };
        m_data[iter.getIndex()] = value;
    };

    void erase(const size_t pos) {
        --m_size;
        if (pos == 0 || pos > m_size) throw std::invalid_argument 
            (R"(Fault "Position out of range!" in the function vectorContainer::erase(pos).)"); 
        if (realloc()) {
            for (size_t i = 0; i < pos-1; ++i) {
                m_data[i] = m_old_data[i];
            }
            for (size_t i = pos-1; i < m_size; ++i) {
                m_data[i] = m_old_data[i+1];
            }
            delete [] m_old_data;
        }
        else for (size_t i = pos-1; i < m_size; ++i) {
                m_data[i] = m_data[i+1];
            }
    }
    void erase(iterator iter) {
        --m_size;
        // if (pos == 0 || pos > m_size) throw std::invalid_argument 
        //     (R"(Fault "Position out of range!" in the function vectorContainer::erase(pos).)"); 
        if (realloc()) {
            for (size_t i = 0; i < iter.getIndex(); ++i) {
                m_data[i] = m_old_data[i];
            }
            for (size_t i = iter.getIndex(); i < m_size; ++i) {
                m_data[i] = m_old_data[i+1];
            }
            delete [] m_old_data;
        }
        else for (size_t i = iter.getIndex(); i < m_size; ++i) {
                m_data[i] = m_data[i+1];
            }
    }
     
    size_t getSize() const  {
        return m_size;
    };
    
    size_t getCapaciti() const  {
        return m_capacity;
    }

    const char* getName() const  {
        return R"(vectorContainer)"; 
    }

    iterator begin()  {
        const size_t index{0};
        return iterator(m_data, index);
    }  

    iterator end()  {
        return iterator(m_data, (m_size));
    }

private:
    float coeff_realloc = 1.8f;
    bool realloc() {
        if ((m_size > m_capacity) || (m_capacity - m_size) > (m_size * 2)) {
            m_capacity = m_size * coeff_realloc;
            if (m_size != 1) m_old_data = m_data;
            m_data = new T [m_capacity];
            return true;
        }
        return false;
    }
    
    size_t m_size{0};
    size_t m_capacity{0};

    T*     m_data{nullptr};
    T*     m_old_data{nullptr};
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const vectorContainer<T>& vector) {
    const size_t i{0};
    os << vector[i];
    return os;
}