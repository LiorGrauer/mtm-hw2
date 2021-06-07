namespace mtm {
    typedef int T;  

    struct Node {
        T data;
        Node* NextNode;
    };

    template <class T>
    class SortedList {
        T data;
        SortedList* nextNode;

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
        delete[] data;
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList<T>& s) :
        data(new T[s.size]), size(s.size), nextIndex(s.nextIndex) {
        for (int i = 0; i < nextIndex; ++i) {
            data[i] = s.data[i];
        }
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& s) {
	if (this == &s) {
		return *this;
	}
	delete[] data;
	data = new T[s.size];
	size = s.size;
	nextIndex = s.nextIndex;
	for (int i = 0; i < nextIndex; ++i) {
		data[i] = s.data[i];
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
        while(!ptr++){
            size++;
        }
        return size;
    }

}