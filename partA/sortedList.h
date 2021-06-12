#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdexcept>

namespace mtm{

#pragma region Node<T>

    template <class T>
    class Node {
        private:
        T data;
        Node<T>* next_node;

        public:
        explicit Node(const T& data);
        ~Node() = default;
        const T& getData() const;
        Node* getNext() const;
        void setNext(Node* ptr);
    };

    template <class T>
    Node<T>::Node(const T& data) :
        data(data), next_node(nullptr) {

    }

    template <class T>
    const T& Node<T>::getData() const{
        return data;
    }
    
    template <class T>
    Node<T>* Node<T>::getNext() const{
        return next_node;
    }
    
    template <class T>
    void Node<T>::setNext(Node* ptr){
        next_node = ptr;
    }

#pragma endregion

#pragma region SortedList<T>

    template <class T>
    class SortedList {
        public:
            class const_iterator;
            explicit SortedList();
            ~SortedList();
            SortedList(const SortedList<T>& s);
            SortedList<T>& operator=(const SortedList<T>&);
            void insert(const T& t);
            void remove(const const_iterator& iter);
            int length() const;
            template<class Condition>
            SortedList<T> filter(Condition c) const;
            template<class Function>
            SortedList<T> apply(Function f) const;
            const_iterator begin() const;
            const_iterator end() const;

        private:
            Node<T>* head_node;
            int size;
            const_iterator iterator;
    };

    template <class T>
    SortedList<T>::SortedList() :
        head_node(nullptr), 
        size(0),
        iterator(head_node) {
    }

    template <class T>
    SortedList<T>::~SortedList(){
        Node<T>* ptr = head_node;
        while(ptr){
            head_node = ptr->getNext();
            delete ptr;
            ptr = head_node;
        }
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :
        iterator (s.iterator),
        size(0),
        head_node(nullptr) {
        Node<T>* ptr = s.head_node;
        while(ptr){
            this->insert(ptr->getData());
            ptr=ptr->getNext();
        }
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
        if (this == &s) {
            return *this;
        }
        Node<T>* ptr = head_node;
        while(ptr){
            head_node = ptr->getNext();
            delete ptr;
            ptr = head_node;
        }
        iterator = s.iterator;
        head_node = nullptr;
        ptr = s.head_node;
        while(ptr){
            this->insert(ptr->getData());
            ptr=ptr->getNext();
        }
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& t) {
        Node<T>* new_node_ptr = new Node<T>(t);
        Node<T>* ptr=head_node;
        if (!ptr || t < ptr->getData())
        {
            new_node_ptr->setNext(ptr);
            head_node=new_node_ptr;
            size++;
            return;
        }
        while(ptr->getNext()){
            if(t < ptr->getNext()->getData()){
                new_node_ptr->setNext(ptr);
                ptr->setNext(new_node_ptr);
                size++;
                return;
            }
            ptr = ptr->getNext();
        }
        ptr->setNext(new_node_ptr);
        size++;
    }

    template <class T>
    void SortedList<T>::remove(const const_iterator& iter){
        Node<T>* ptr=head_node;
        if(!ptr){
            return;
        }
        if (!(*iter < ptr->getData()) &&
            !(ptr->getData() < *iter))
        {
            head_node=ptr->getNext();
            delete ptr;
            size--;
            return;
        }
        while(ptr->getNext()){
            if(!(*iter < ptr->getNext()->getData()) &&
                !(ptr->getNext()->getData() < *iter)){
                ptr->setNext(ptr->getNext()->getNext());
                delete ptr;
                size--;
                return;
            }
            ptr->setNext(ptr->getNext());
            delete ptr;
            size--;
        }
    }

    template <class T>
    int SortedList<T>::length() const {
        return size;
    }

    template<class T>
    template<class Condition>
    SortedList<T> SortedList<T>::filter(Condition c) const {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator it = begin(); !(it == end()); ++it) {
            if (c(*it)) {
                result.insert(*it);
            }
        }
        return result;
    }
    
    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function f) const {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator it = begin(); !(it == end()); ++it) {
            result.insert(f(*it));
        }
        return result;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(head_node);
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        /*if (!head_node){
            return const_iterator(head_node);
        }
        Node<T>* ptr = head_node;
        while(ptr->getNext()){
            ptr=ptr->getNext();
        }
        return const_iterator(ptr);*/
        return const_iterator(nullptr);
    }

#pragma endregion

#pragma region SortedList<T>::const_iterator

    template <class T>
    class SortedList<T>::const_iterator {
        private:
            const Node<T>* ptr;
            explicit const_iterator(const Node<T>* node_ptr);
            friend class SortedList<T>;

        public:
            const_iterator(const const_iterator& iter);
            ~const_iterator() = default;
            const_iterator& operator=(const const_iterator& iter);
            const_iterator& operator++();
            //const_iterator& operator++(int);
            bool operator==(const const_iterator& iter) const;
            const T& operator*() const;
    };

    template <class T>
    SortedList<T>::const_iterator::const_iterator(const Node<T>* node_ptr) :
        ptr(node_ptr) {
    }

    template <class T>
    SortedList<T>::const_iterator::const_iterator(const const_iterator& iter) : 
        ptr(iter.ptr) {
    }

    template <class T>
    //why typename needed??
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator=(const const_iterator& iter){
        if (this == &iter) {
            return *this;
        }
        ptr = iter.ptr;
        return *this;
    }

    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++(){
        if (!ptr){
            throw std::out_of_range("out_of_range");
        }
        ptr = ptr->getNext();
        return *this;
    }

    template <class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iter) const{
        return ptr == iter.ptr;
    }

    template <class T>
    const T& SortedList<T>::const_iterator::operator*() const{
        return ptr->getData();
    }

#pragma endregion

}

#endif