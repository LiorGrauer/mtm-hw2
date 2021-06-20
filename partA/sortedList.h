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

        /**
         * Node: sorted list node constructor
         *
         * @param data - data. Must be type T
         *
         * @return
         *     node with given data and null pointer
         */
        explicit Node(const T& data);

        //default destructer
        ~Node() = default;

        /**
         * getData: returns data in node
         *
         * @return
         *     const T type data
         */
        const T& getData() const;

        /**
         * getNext: returns next node pointer in the node
         *
         * @return
         *     Node<T> pointer to the next node in the list
         */
        Node* getNext() const;

        /** setNext: sets next node pointer in the node */
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

    /** SortedList class declaration */
    template <class T>
    class SortedList {
        public:
            class const_iterator;
            
            /**
             * SortedList: sorted list constructor
             *
             * @return
             *     empty sorted list
             */
            explicit SortedList();

            /** ~SortedList: sorted list deconstructor. erases all the data nodes in the sorted list */
            ~SortedList();

            /**
             * SortedList: sorted list node copy constructor
             *
             * @param s - SortedList<T>&. existing sorted list from data type T
             *
             * @return
             *     new copy of the given sorted list
             */
            SortedList(const SortedList<T>& s);

            /**
             * operator=: sorted list placement operator
             *
             * @param s - SortedList<T>&. existing sorted list from data type T
             *
             * @return
             *     inserts the data from the given sorted list to an existing sorted list
             *     deletes all the old data and inserts the new from the given sorted list.
             */
            SortedList<T>& operator=(const SortedList<T>&);

            /**
             * insert: inserts given data type T to the sorted list
             *
             * @param t - T&. reference to data type T
             *
             */
            void insert(const T& t);

            /**
             * remove: remove specific data from the sorted list by given iterator
             *
             * @param t - const_iterator& . reference to iterator
             *
             */
            void remove(const const_iterator& iter);

            /**
             * length: returns sorted list length
             *
             * @return 
             *      length of the sorted list
             *
             */
            int length() const;

            /**
             * filter: creates new sorted list that contains only objects that meet filter condition
             *
             * @param c - Condition. bool function that recives data type T and returns if met condition or not
             *
             * @return
             *     new sorted list that containes only objects that met the condition.
             */
            template<class Condition>
            SortedList<T> filter(Condition c) const;

             /**
             * apply: creates new sorted list that contains all objects after apply function was activated on them
             *
             * @param f - Function. function that recives data type T and returns it after appling something on it
             *
             * @return
             *     new sorted list that containes all objects after apply function was applied on them.
             */
            template<class Function>
            SortedList<T> apply(Function f) const;

            /**
             * begin: return iterator that points to the first node in the sorted list
             *
             * @return
             *     iterator the point to the first node
             */
            const_iterator begin() const;

            /**
             * end: return iterator that points to the next node attribute of the last node in the sorted list (nullptr)
             *
             * @return
             *     iterator the point to nullptr
             */
            const_iterator end() const;

        private:
            Node<T>* head_node;
            int size;
    };

    template <class T>
    SortedList<T>::SortedList() :
        head_node(nullptr), 
        size(0){
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
        head_node(nullptr),
        size(0){
        Node<T>* ptr = s.head_node;
        while(ptr){
            this->insert(ptr->getData());
            ptr = ptr->getNext();
        }
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
        if (this == &s) {
            return *this;
        }

        SortedList<T> temp_list;
        Node<T>* ptr = s.head_node;
        while(ptr){
            temp_list.insert(ptr->getData());
            ptr = ptr->getNext();
        }

        ptr = head_node;
        while(ptr){
            head_node = ptr->getNext();
            delete ptr;
            ptr = head_node;
        }
        
        head_node = temp_list.head_node;
        temp_list.head_node = nullptr;
        size = temp_list.size;
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

    template <class T>
    void SortedList<T>::remove(const const_iterator& iter){
        SortedList<T>::const_iterator iterator(this->begin());
        if(iterator == this->end()){
            return;
        }
        if (iter == iterator)
        {
            head_node = head_node->getNext();
            delete iter.ptr;
            size--;
            return;
        }
        Node<T>* ptr = head_node; 
        while(!(iterator == this->end())){
            if(iter.ptr == iterator.ptr->getNext()){
                ptr->setNext(ptr->getNext()->getNext());
                delete iter.ptr;
                size--;
                return;
            }
            ++iterator;
            ptr = ptr->getNext();
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
        for (typename SortedList<T>::const_iterator iterator = begin(); !(iterator == end()); ++iterator) {
            if (c(*iterator)) {
                result.insert(*iterator);
            }
        }
        return result;
    }
    
    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function f) const {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator iterator = begin(); !(iterator == end()); ++iterator) {
            result.insert(f(*iterator));
        }
        return result;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(head_node);
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(nullptr);
    }

    /** const_iterator class declaration */
    template <class T>
    class SortedList<T>::const_iterator {
        private:
            const Node<T>* ptr;

            /**
             * const_iterator: const_iterator constructor
             *
             * @param node_ptr - const Node<T>*. pointer to Node
             * 
             * @return
             *     iterator that points to the given pointer
             */
            explicit const_iterator(const Node<T>* node_ptr);

            friend class SortedList<T>;

        public:
            /**
             * const_iterator: const_iterator copy constructor
             *
             * @param iter - const const_iterator&. existing iterator
             * 
             * @return
             *     a copy of the given iterator
             */
            const_iterator(const const_iterator& iter);

            // default destructor
            ~const_iterator() = default;

            /**
             * const_iterator: const_iterator placement constructor
             *
             * @param node_ptr - const const_iterator&. existing iterator
             * 
             * @return
             *     inserts the pointer of the given iterator to the existing iterator.
             */
            const_iterator& operator=(const const_iterator& iter);

            /**
             * operator++: advanced the iterator and returns it after advancment
             * 
             * @return
             *     Advanced iterator
             */
            const_iterator& operator++();

            /**
             * operator++: advanced the iterator and returns it before advancment
             * 
             * @return
             *     Pre advancedment iterator
             */
            const_iterator operator++(int);

            /**
             * operator==: check if two iterators are equel
             * 
             * @return
             *     true if both are the same, false if not
             */
            bool operator==(const const_iterator& iter) const;

            /**
             * operator*: returns the data in the node the iterator has its pointer
             * 
             * @return
             *     data type T
             */
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
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int){
        if (!ptr){
            throw std::out_of_range("out_of_range");
        }
        const_iterator result = *this; 
        ++*this; 
        return result;
    }

    template <class T>  
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iter) const{
        return ptr == iter.ptr;
    }

    template <class T>
    const T& SortedList<T>::const_iterator::operator*() const{
        return ptr->getData();
    }
}

#endif