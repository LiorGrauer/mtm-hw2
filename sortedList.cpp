

namespace mtm{

    typedef int T;  

    template <class T>
    class Node {
        T data;
        Node* next_node;

        public:
        T getData() const;
        Node* getNext() const;
        void setData(const T& t);
        void setNext(const Node* ptr);
    };

    template <class T>
    T Node<T>::getData() const{
        return this->data;
    }
    
    template <class T>
    Node<T>* Node<T>::getNext() const{
        return this->next_node;
    }

    template <class T>
    void Node<T>::setData(const T& t){
        T copy=t;
        this->data = copy&;
    }
    
    template <class T>
    void Node<T>::setNext(const Node* ptr){
        this->next_node = ptr;
    }

    template <class T>
    class SortedList {
        Node* head_node;
        int size;

        public:
        explicit SortedList();
        ~SortedList();
        SortedList(const SortedList<T>& s);
        SortedList<T>& operator=(const SortedList<T>&);
        void insert(const T& t);
        void remove();
        int length() const;
        class const_iterator;
    };

    template <class T>
    class SortedList<T>::const_iterator {
        Node<T>* ptr;
        explicit SortedList::const_iterator();

        public:
        ~SortedList::const_iterator();
        SortedList::const_iterator& operator=(const SortedList::const_iterator& iter);
        void operator++();
        bool operator==(const SortedList::const_iterator& iter) const;
        const Node<T>& operator*(const SortedList::const_iterator& iter) const;
    };

    template <class T>
    SortedList<T>::SortedList() :
        head(NULL), size(0) {
    }
    
    template <class T>
    SortedList<T>::~SortedList() {
        
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :{
        SortedList<T> new_sorted_list;
        Node<T>* ptr = s;
        while(!ptr){
            new_sorted_list.insert(ptr->getData);
            ptr=ptr->getNext;
        }
        return new_sorted_list;
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
        if (this == &s) {
            return *this;
        }
        // delete old data
        Node<T>* ptr = s;
        while(!ptr){
            this->insert(ptr->getData);
            ptr=ptr->getNext;
        }
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& t) {
        //add
        size++;
    }

    template <class T>
    void SortedList<T>::remove() {
        
        size--;
    }

    template <class T>
    int SortedList<T>::length() const {
        return size;
    }


    //SortedList::const_iterator

    template <class T>
    SortedList<T>::const_iterator<T>::const_iterator() :
        ptr(NULL) {
    }

    ~SortedList::const_iterator(){
    }

    SortedList::const_iterator& operator=(const SortedList::const_iterator& iter){
        if (this == &iter) {
            return *this;
        }
        ptr = iter.ptr;
        return *this;
    }

    void operator++(){
        if (!*ptr.next_node){
            throw std::out_of_range();
        }
        ptr = *ptr.next_node;
    }

    bool operator==(const SortedList::const_iterator& iter) const;
    const Node<T>& operator*(const SortedList::const_iterator& iter) const;

}