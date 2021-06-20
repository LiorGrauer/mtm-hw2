#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdexcept>

namespace mtm{

    /** Node class declaration */
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

    /**
     * Node: sorted list node constructor
     *
     * @param data - data. Must be type T
     *
     * @return
     *     node with given data and null pointer
     */
    template <class T>
    Node<T>::Node(const T& data) :
        data(data), next_node(nullptr) {
    }

    /**
     * getData: returns data in node
     *
     * @return
     *     T type data
     */
    template <class T>
    const T& Node<T>::getData() const{
        return data;
    }
    
    /**
     * getNext: returns next node pointer in the node
     *
     * @return
     *     Node<T> pointer to the next node in the list
     */
    template <class T>
    Node<T>* Node<T>::getNext() const{
        return next_node;
    }
    
    /** setNext: sets next node pointer in the node */
    template <class T>
    void Node<T>::setNext(Node* ptr){
        next_node = ptr;
    }

    /** SortedList class declaration */
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

    /**
     * SortedList: sorted list constructor
     *
     * @return
     *     empty sorted list
     */
    template <class T>
    SortedList<T>::SortedList() :
        head_node(nullptr), 
        size(0),
        iterator(head_node) {
    }

    /** ~SortedList: sorted list deconstructor. erases all the data nodes in the sorted list */
    template <class T>
    SortedList<T>::~SortedList(){
        Node<T>* ptr = head_node;
        while(ptr){
            head_node = ptr->getNext();
            delete ptr;
            ptr = head_node;
        }
    }

    /**
     * SortedList: sorted list node copy constructor
     *
     * @param s - SortedList<T>&. existing sorted list from data type T
     *
     * @return
     *     new copy of the given sorted list
     */
    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :
        head_node(nullptr),
        size(0),
        iterator (s.iterator) {
        Node<T>* ptr = s.head_node;
        while(ptr){
            this->insert(ptr->getData());
            ptr=ptr->getNext();
        }
    }

    /**
     * operator=: sorted list placement operator
     *
     * @param s - SortedList<T>&. existing sorted list from data type T
     *
     * @return
     *     inserts the data from the given sorted list to an existing sorted list
     *     deletes all the old data and inserts the new from the given sorted list.
     */
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
        size=s.size;
        return *this;
    }

    /**
     * insert: inserts given data type T to the sorted list
     *
     * @param t - T&. reference to data type T
     *
     */
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
                new_node_ptr->setNext(ptr->getNext());
                ptr->setNext(new_node_ptr);
                size++;
                return;
            }
            ptr = ptr->getNext();
        }
        ptr->setNext(new_node_ptr);
        size++;
    }

    /**
     * remove: remove specific data from the sorted list by given iterator
     *
     * @param t - const_iterator& . reference to iterator
     *
     */
    template <class T>
    void SortedList<T>::remove(const const_iterator& iter){
        SortedList<T>::const_iterator it(this->begin());
        if(it == this->end()){
            return;
        }
        if (iter==it)
        {
            head_node = head_node->getNext();
            delete iter.ptr;
            size--;
            return;
        }
        Node<T>* ptr = head_node;
        while(!(it == this->end())){
            if(iter.ptr==it.ptr->getNext()){
                ptr->setNext(ptr->getNext()->getNext());
                delete iter.ptr;
                size--;
                return;
            }
            ptr = ptr->getNext();
            it++;
        }
    }

    /**
     * length: returns sorted list length
     *
     * @return 
     *      length of the sorted list
     *
     */
    template <class T>
    int SortedList<T>::length() const {
        return size;
    }

    /**
     * filter: creates new sorted list that contains only objects that meet filter condition
     *
     * @param c - Condition. bool function that recives data type T and returns if met condition or not
     *
     * @return
     *     new sorted list that containes only objects that met the condition.
     */
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
    
    /**
     * apply: creates new sorted list that contains all objects after apply function was activated on them
     *
     * @param f - Function. function that recives data type T and returns it after appling something on it
     *
     * @return
     *     new sorted list that containes all objects after apply function was applied on them.
     */
    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function f) const {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator it = begin(); !(it == end()); ++it) {
            result.insert(f(*it));
        }
        return result;
    }

    /**
     * begin: return iterator that points to the first node in the sorted list
     *
     * @return
     *     iterator the point to the first node
     */
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(head_node);
    }

    /**
     * end: return iterator that points to the next node attribute of the last node in the sorted list (nullptr)
     *
     * @return
     *     iterator the point to nullptr
     */
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(nullptr);
    }

    /** const_iterator class declaration */
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
            const_iterator operator++(int);
            bool operator==(const const_iterator& iter) const;
            const T& operator*() const;
    };

    /**
     * const_iterator: const_iterator constructor
     *
     * @param node_ptr - const Node<T>*. pointer to Node
     * 
     * @return
     *     iterator that points to the given pointer
     */
    template <class T>
    SortedList<T>::const_iterator::const_iterator(const Node<T>* node_ptr) :
        ptr(node_ptr) {
    }

    /**
     * const_iterator: const_iterator copy constructor
     *
     * @param iter - const const_iterator&. existing iterator
     * 
     * @return
     *     a copy of the given iterator
     */
    template <class T>
    SortedList<T>::const_iterator::const_iterator(const const_iterator& iter) : 
        ptr(iter.ptr) {
    }

    /**
     * const_iterator: const_iterator placement constructor
     *
     * @param node_ptr - const const_iterator&. existing iterator
     * 
     * @return
     *     inserts the pointer of the given iterator to the existing iterator.
     */
    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator=(const const_iterator& iter){
        if (this == &iter) {
            return *this;
        }
        ptr = iter.ptr;
        return *this;
    }

    /**
     * operator++: advanced the iterator and returns it after advancment
     * 
     * @return
     *     Advanced iterator
     */
    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++(){
        if (!ptr){
            throw std::out_of_range("out_of_range");
        }
        ptr = ptr->getNext();
        return *this;
    }

    /**
     * operator++: advanced the iterator and returns it before advancment
     * 
     * @return
     *     Pre advancedment iterator
     */
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int){
        if (!ptr){
            throw std::out_of_range("out_of_range");
        }
        const_iterator result = *this; 
        ++*this; 
        return result;
    }

    /**
     * operator==: check if two iterators are equel
     * 
     * @return
     *     true if both are the same, false if not
     */
    template <class T>  
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iter) const{
        return ptr == iter.ptr;
    }

    /**
     * operator*: returns the data in the node the iterator has its pointer
     * 
     * @return
     *     data type T
     */
    template <class T>
    const T& SortedList<T>::const_iterator::operator*() const{
        return ptr->getData();
    }

}

#endif