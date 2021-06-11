#include <stdexcept>

namespace mtm{

    //typedef int T;  

    template <class T>
    class Node {
        private:
        T data;
        Node<T>* next_node;

        public:
        explicit Node(const T& data);
        ~Node() = default;
        T getData() const;
        Node* getNext() const;
        void setNext(const Node* ptr);
    };

    template <class T>
    Node<T>::Node(const T& data) :
        data(data), next_node(NULL) {

    }

    template <class T>
    T Node<T>::getData() const{
        return data;
    }
    
    template <class T>
    Node<T>* Node<T>::getNext() const{
        return next_node;
    }
    
    template <class T>
    void Node<T>::setNext(const Node* ptr){
        next_node = ptr;
    }

    template <class T>
    class SortedList {
        public:
            class const_iterator;
            explicit SortedList();
            ~SortedList() = default();
            SortedList(const SortedList<T>& s);
            SortedList<T>& operator=(const SortedList<T>&);
            void insert(const T& t);
            void remove(const const_iterator& iter);
            int length() const;
            template<class Condition>
            SortedList<T> filter(Condition c) const;
            template<class Function>
            SortedList<T> apply(Function f) const;
            void begin();
            void end();

        private:
            Node<T>* head_node;
            int size;
            const_iterator iterator;
        
    };

    template <class T>
    class SortedList<T>::const_iterator {
        private:
            Node<T>* ptr;
            explicit const_iterator();

        public:
            const_iterator(const const_iterator& iter);
            ~const_iterator() = default;
            const_iterator& operator=(const const_iterator& iter);
            void operator++();
            bool operator==(const const_iterator& iter) const;
            const Node<T>& operator*(const const_iterator& iter) const;
    };

    template <class T>
    SortedList<T>::SortedList() :
        head(NULL), size(0) {
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :{
        SortedList<T> new_sorted_list;
        Node<T>* ptr = s;
        while(!ptr){
            new_sorted_list.insert(ptr->getData);
            ptr=ptr->getNext();
        }
        return new_sorted_list;
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
        if (this == &s) {
            return *this;
        }
        // delete old data
        head_node = NULL;
        Node<T>* ptr = s;
        while(!ptr){
            this->insert(ptr->getData());
            ptr=ptr->getNext();
        }
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& t) {
        Node<T>* new_node = Node(t);
        Node<T>* ptr=head_node;
        if (!ptr || t < ptr->getData())
        {
            new_node->setNext(ptr);
            head_node=new_node;
            size++;
            return;
        }
        while(ptr->getNext){
            if(t < ptr->getNext()->getData()){
            new_node->setNext(ptr);
            ptr->setNext(new_node);
            size++;
            return;
            }
            ptr->setNext(new_node);
            size++;
        }
    }

    template <class T>
    void SortedList<T>::remove(const const_iterator& iter){
        Node<T>* ptr=head_node;
        if(!ptr){
            return;
        }
        if (iter == ptr)
        {
            head_node=ptr->getNext();
            size--;
            return;
        }
        while(ptr->getNext){
            if(iter == ptr->getNext()){
                ptr->setNext(ptr->getNext()->getNext())
                size--;
                return;
            }
            ptr->setNext(new_node);
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
        for (typename Set<T>::Iterator it = begin(); it != end(); ++it) {
            if (c(it->getData())) {
                result.insert(it->getData());
            }
        }
        return result;
    }
    
    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function f) const {
        SortedList<T> result;
        for (typename Set<T>::Iterator it = begin(); it != end(); ++it) {
            result.insert(f(it->getData()));
        }
    return result;
    }

    template <class T>
    void SortedList<T>::begin(){
        iterator = head_node;
    }

    template <class T>
    void SortedList<T>::end() {
        iterator = head_node;
        while(iterator->getNext()){
            iterator=iterator->getNext();
        }
    }

    //SortedList::const_iterator

    template <class T>
    SortedList<T>::const_iterator::const_iterator() :
        ptr(NULL) {
    }

    template <class T>
    SortedList<T>::const_iterator::const_iterator(const const_iterator& iter) : 
        ptr(iter.ptr) {
    }

    template <class T>
    SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator=(const const_iterator& iter){
        if (this == &iter) {
            return *this;
        }
        ptr = iter.ptr;
        return *this;
    }

    template <class T>
    void SortedList<T>::const_iterator::operator++(){
        if (!(ptr->getNext())){
            throw std::out_of_range("out_of_range");
        }
        ptr = ptr->getNext();
    }

    template <class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iter) const{
        return ptr == iter.ptr;
    }

    template <class T>
    const Node<T>& SortedList<T>::const_iterator::operator*(const const_iterator& iter) const{
        return *ptr;
    }

}