

namespace mtm{

    typedef int T;  

    template <class T>

    class Node {
        T data;
        Node* next_node;

        public:
        T getData;
        Node* getNext;
        void SetData;
        void getData;
    };

    template <class T>
    class SortedList {
        Node* head_node;

        public:
        explicit SortedList();
        ~SortedList();
        SortedList(const SortedList& s);
        SortedList& operator=(const SortedList&);
        void insert(const T& t);
        void remove();
        int length() const;
    };

    template <class T>
    SortedList<T>::SortedList() : {
        Node* head = NULL;
    }
    
    template <class T>
    SortedList<T>::~SortedList() {
        //delete data
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :{
        SortedList new_sorted_list;
        SortedList* ptr = s;
        while(!ptr){
            new_sorted_list.insert(ptr->data);
            ptr=ptr->nextNode;
        }
        return newSortedList;
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
	if (this == &s) {
		return *this;
	}
	// delete old data
    SortedList* ptr = s;
    while(!ptr){
        this.insert(ptr->data);
        ptr=ptr->nextNode;
    }
	return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& t) {
        if (nextIndex >= size) {
            error("SortedList full");
        }
        data[nextIndex++] = t;
    }

    template <class T>
    void SortedList<T>::remove() {
        if (nextIndex <= 0) {
            error("SortedList empty");
        }
        nextIndex--;
    }

    template <class T>
    int SortedList<T>::length() const {
        int size=0;
        SortedList* ptr = this;
        while(!ptr){
            size++;
            ptr=ptr->nextNode;
        }
        return size;
    }

}