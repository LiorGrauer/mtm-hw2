

namespace mtm{

    typedef int T;  

    template <class T>
    class Node {
        T data;
        Node<T>* next_node;

        public:
        explicit Node(const T& data);
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
        head_node = NULL;
        Node<T>* ptr = s;
        while(!ptr){
            this->insert(ptr->getData);
            ptr=ptr->getNext;
        }
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& t) {
        Node* new_node = new Node(t);
        //Map_node current_node = map -> head_node;
        MapDataElement data_copy= map->copyDataElement(dataElement);
        MapKeyElement key_copy= map->copyKeyElement(keyElement);
        if(mapContains(map,key_copy)) {
            while (current_node) {
                if (map->compareKeyElements(nodeGetKey(current_node),key_copy) == 0)
                {
                    map->freeDataElement(nodeGetData(current_node));
                    map->freeKeyElement(key_copy);
                    nodeSetData(current_node,data_copy);
                }
                current_node= nodeGetNext(current_node);
            }
        size++;
        }
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
    SortedList<T>::const_iterator::const_iterator() :
        ptr(NULL) {
    }

    SortedList<T>::const_iterator::const_iterator(const const_iterator& iter) : 
        ptr(iter.ptr) {
    }

    SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator=(const const_iterator& iter){
        if (this == &iter) {
            return *this;
        }
        ptr = iter.ptr;
        return *this;
    }

    void SortedList<T>::const_iterator::operator++(){
        if (!(ptr->getNext())){
            throw std::out_of_range;
        }
        ptr = ptr->getNext();
    }

    bool SortedList<T>::const_iterator::operator==(const const_iterator& iter) const{
        return ptr == iter.ptr;
    }
    const Node<T>& SortedList<T>::const_iterator::operator*(const const_iterator& iter) const{
        return *ptr;
    }

}