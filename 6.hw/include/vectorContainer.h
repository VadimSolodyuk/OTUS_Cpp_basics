#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class vectorContainer { 
public:
    vectorContainer() {
        std::cout << "Creating a " << (*this).getName() << "\n";
    };

    explicit vectorContainer (const T data) {
        ++m_size;
        m_capacity +=2;
        m_data = new T [m_capacity];
        m_data[m_size-1] = data;
    };

    vectorContainer (const vectorContainer& vector) {
        m_size = vector.m_size;
        m_data = new T [vector.m_capacity];
        for (size_t i{0}; i < m_size; ++i) {
            m_data[i] = vector[i];
        }
    }

    ~vectorContainer () { 
        delete [] m_data;
        std::cout << "Deleting vectorContainer" << std::endl; 
    }

    vectorContainer& operator=(const vectorContainer& vector) {
        if (m_data == vector.m_data) return *this;
        if (m_size > 0) delete [] m_data;
        m_size = vector.m_size;
        m_capacity = vector.m_capacity;
        m_data = new T [m_capacity];
        for (size_t i{0}; i < m_size; ++i) {
            m_data[i] = vector[i];
        }
        return *this;
    }

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
        if (pos == 0 || pos > m_size) {
            std::cout <<  R"(Fault "Position out of range!". )" 
            << getName() << " contains " << m_size << "elements.\n";
            return;
        }    
        ++m_size;
        if (realloc()) {
            for (size_t i = 0; i < pos-1; ++i) {
                m_data[i] = m_old_data[i];
            }
            for (size_t i = pos; i < m_size-1; ++i) {
                m_data[i] = m_old_data[i-1];
            }
            delete [] m_old_data;
        }
        for (size_t i = m_size-1; i > pos-1; --i) {
            m_data[i] = m_data[i-1];
        };
        m_data[pos-1] = value;
    };

    void erase (const size_t pos) {
        if (pos == 0 || pos > m_size) {
            std::cout <<  R"(Fault "Position out of range!". )" 
            << getName() << " contains " << m_size << "elements.\n";
            return;
        }
        --m_size;
        if (realloc()) {
            for (size_t i = 0; i < pos-1; ++i) {
                m_data[i] = m_old_data[i];
            }
            for (size_t i = pos-1; i < m_size; ++i) {
                m_data[i] = m_old_data[i+1];
            }
            delete [] m_old_data;
        }
        for (size_t i = pos-1; i < m_size; ++i) {
            m_data[i] = m_data[i+1];
        }
    }
    
    size_t getSize() const  {
        return m_size;
    };
    
    size_t getCapaciti () const  {
        return m_capacity;
    }

    const char* getName() const  {
        return R"("vectorContainer")"; 
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
    private:
        size_t m_index{0};
        T*     m_dataIterator{nullptr};
        T*     m_iterator{nullptr};
    };

    iterator begin()  {
        return iterator(m_data, 0);
    }  

    iterator end()  {
        return iterator(m_data, (m_size));
    }

private:
    float coeff_realloc = 1.8f;
    bool realloc () {
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