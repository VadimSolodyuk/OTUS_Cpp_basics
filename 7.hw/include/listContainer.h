#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
struct Node {
    T data{0};
    Node* prev{nullptr};
    Node* next{nullptr};
};

template <typename T>
class listContainer { 
public:
    listContainer() {
        std::cout << "Creating a " << (*this).getName() << "\n";
    }
    explicit listContainer(const T value) {
        Node<T>* new_node = new Node<T>{};
        new_node->data = value;
        m_first = new_node;
        m_last = new_node;
        ++m_sizeList;
        set_end(m_sizeList);
        std::cout << "Creating a " << (*this).getName() << std::endl;
    }
    listContainer(const listContainer& list) : listContainer() {
        if (!list.getSize()) return; 
        else 
            for (size_t i{0}; i < list.getSize(); ++i) {
                this->push_back(list[i]);
            }
    }   
    ~listContainer() {
        const auto size = m_sizeList;
        for (size_t i{1}; i <= size; i++) {
            this->erase(1);
        }
        delete _end;
        m_first = nullptr;
        m_last = nullptr;
        _end = nullptr;
        m_sizeList = 0;
        target_node = nullptr;

        std::cout << "Deleting a " << (*this).getName() << std::endl;
    }
    listContainer& operator=(const listContainer& list) {
        if (this->getSize() == list.getSize()) {
            for (size_t i{0}; i < list.getSize(); ++i) {
                if ((*this)[i] == list[i])
                    return *this;
            }
        }
        if (this->getSize() > 0) {
            this->~listContainer();
        }
        for (size_t i{0}; i < list.getSize(); ++i) {
            this->push_back(list[i]);
        }
        return *this;
    }

    struct iterator { 
        explicit iterator(Node<T>* node) : m_iterator(node) {}

        iterator& operator++() {
            if (m_iterator->next == nullptr) return *this; 
            m_iterator = m_iterator->next;
            return *this;
        }
        iterator& operator--() {
            if (m_iterator->prev == nullptr) return *this; 
            m_iterator = m_iterator->prev;
            return *this;
        }
        iterator& operator+(const size_t rhs) {
            for (size_t i{1}; i <= rhs; ++i) {
                if (m_iterator->next == nullptr) return *this; 
                m_iterator = m_iterator->next;
            }
            return *this;
        }
        iterator& operator-(const size_t rhs) {
            for (size_t i{1}; i <= rhs; ++i) {
                if (m_iterator->prev == nullptr) return *this; 
                m_iterator = m_iterator->prev;
            }
            return *this;
        }
        bool operator==(const iterator& rhs) const {
            if (m_iterator == rhs.m_iterator) return 1; 
                else return 0;
        }
        bool operator!=(const iterator& rhs) const {
            if (m_iterator != rhs.m_iterator) return 1; 
                else return 0;
        }
        T& get() const {
            return m_iterator->data;
        }
        Node<T>* getPtr() {
            return m_iterator;
        }
        
    private:
        Node<T>* m_iterator{nullptr};
    };

    T& operator[] (const size_t index) const  {
        if (index > m_sizeList-1) throw std::invalid_argument 
            (R"(Error "Index out of range!" in the function listContainer::operator[])");
        target_node = step(index);
        return target_node->data;
    }

    void push_back(const T value)  {
        Node<T>* new_node = new Node<T>{};
        new_node->data = value;
        if (m_sizeList == 0) {
            m_first = new_node;
        }
        else {
            new_node->prev = m_last;
            m_last->next = new_node;
        }
        m_last = new_node;
        ++m_sizeList;
        set_end(m_sizeList);
    }

    void insert(const size_t pos, const T value)   { //pos - позиция (по счёту)
        ++m_sizeList;
        if (pos == 0 || pos > m_sizeList) throw std::invalid_argument 
            (R"(Fault "Position out of range!" in the function listContainer::insert(pos, value).)"); 
        Node<T>* new_node = new Node<T>{};
        new_node->data = value;
        target_node = step(pos-1);
        if (target_node == m_first) {
            new_node->next = target_node;
            target_node->prev = new_node;
            m_first = new_node;
        }
        else if (target_node == m_last) {
            new_node->prev = target_node;
            target_node->next = new_node;
            m_last = new_node;
        }
        else {
            (*target_node->prev).next = new_node;
            target_node->prev = new_node;
            new_node->prev = target_node->prev;
            new_node->next = target_node;
        }
        set_end(m_sizeList);
    }
void insert(iterator iter, const T value)   { 
        // if (pos == 0 || pos > m_sizeList) throw std::invalid_argument 
        //     (R"(Fault "Position out of range!" in the function listContainer::insert(pos, value).)"); 
        if (!m_sizeList) {
            this->push_back(value);
            return;
        }
        Node<T>* new_node = new Node<T>{};
        new_node->data = value;
        target_node = iter.getPtr();
        if (target_node == m_first) {
            new_node->next = target_node;
            target_node->prev = new_node;
            m_first = new_node;
        }
        else if (target_node == m_last) {
            new_node->prev = target_node;
            target_node->next = new_node;
            m_last = new_node;
        }
        else {
            (*target_node->prev).next = new_node;
            target_node->prev = new_node;
            new_node->prev = target_node->prev;
            new_node->next = target_node;
        }
        ++m_sizeList;
        set_end(m_sizeList);
    }

    void erase(const size_t pos)  {
        if (pos == 0 || pos > m_sizeList) throw std::invalid_argument 
            (R"(Fault "Position out of range!" in the function listContainer::erase(pos).)"); 
        target_node = step(pos-1);
        if (target_node == m_first) {
            (*target_node->next).prev = {nullptr};
            m_first = target_node->next;
            delete target_node;
        }
        else if (target_node == m_last) {
            (*target_node->prev).next = {nullptr};
            m_last = target_node->prev;
            delete target_node;
            m_last->next = _end;
            _end->prev = m_last; 
        } 
        else {
            (*target_node->prev).next = target_node->next;
            (*target_node->next).prev = target_node->prev;
            delete target_node;
        }
        --m_sizeList;
    }
    void erase(iterator iter)  {
        // if (pos == 0 || pos > m_sizeList) throw std::invalid_argument 
        //     (R"(Fault "Position out of range!" in the function listContainer::erase(pos).)"); 
        if (!m_sizeList) return;
        target_node = iter.getPtr();
        if (target_node == m_first) {
            (*target_node->next).prev = {nullptr};
            m_first = target_node->next;
            delete target_node;
        }
        else if (target_node == m_last) {
            (*target_node->prev).next = {nullptr};
            m_last = target_node->prev;
            delete target_node;
            m_last->next = _end;
            _end->prev = m_last; 
        } 
        else {
            (*target_node->prev).next = target_node->next;
            (*target_node->next).prev = target_node->prev;
            delete target_node;
        }
        --m_sizeList;
    }

    size_t getSize() const  {
        return m_sizeList;
    }
    
    const char* getName() const   {
        return R"(listContainer)"; 
    }

    iterator begin() const {
        return iterator(m_first);
    }  

    iterator end() const {
        return iterator(_end);
    }  

    //Поиск нужного Node по индексу в зависимости от его удаленности от начала|конца контейнера      
    Node<T>* step(const size_t index) const {
        Node<T>* node{nullptr};
        if (index == 0) return m_first;
        if (index == (m_sizeList-1)) return m_last;
        if (index > (m_sizeList-1)) return _end;
        size_t middl_sizeList{0};
        if (!(m_sizeList % 2 == 0)) middl_sizeList = (m_sizeList + 1)/2;
            else middl_sizeList = m_sizeList / 2;
        if (index <= (middl_sizeList)) {
            node = m_first;
            for (size_t i{1}; i <= index; ++i) {
                node = node->next; 
            }
        }
        else {
            node = m_last;
            for (size_t i{1}; i <= ((m_sizeList - 1) - index); ++i) {
            node = node->prev;
            }
        }
        return node;
    }

private:
    Node<T>* m_first{nullptr};
    Node<T>* m_last{nullptr};
    Node<T>* _end{nullptr};
    size_t   m_sizeList{0};

    mutable Node<T>* target_node{nullptr};

    void set_end(size_t sizeList) {
        if (sizeList == 1) _end = new Node<T>{};
        m_last->next = _end;
        _end->prev = m_last; 
    };
};