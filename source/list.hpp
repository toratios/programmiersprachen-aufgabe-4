#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>

// List.hpp
template <typename T>
struct List;

template <typename T>
struct ListNode
{
  ListNode() : m_value(), m_prev(nullptr), m_next(nullptr) {}
  ListNode(T const& v, ListNode* prev, ListNode* next)
    : m_value(v), m_prev(prev), m_next(next)
  {}
  T m_value;
  ListNode* m_prev ;
  ListNode* m_next ;
};

template <typename T>
struct ListIterator
{
  typedef ListIterator<T> Self;

  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  friend class List <T>;

  ListIterator():
    m_node(nullptr) {}

  ListIterator(ListNode<T>* n):
    m_node(n) {}

  reference operator*() const {
    return m_node -> m_value;
  }

  pointer operator->() const {
    return *m_node;
  }

  Self& operator++() {
    m_node = m_node -> m_next;
    return *this;
  }

  Self operator++(int) {
    Self temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const Self& x) const {
    return m_node == x.m_node;
  }

  bool operator!=(const Self& x) const {
    return m_node != x.m_node;
  }

  Self next() const {
    if (m_node)
      return ListIterator (m_node -> m_next);
    else
      return ListIterator (nullptr);
  }

private:
  // The Node the iterator is pointing to
  ListNode<T>* m_node = nullptr;
};

template <typename T>
struct ListConstIterator
{
  friend class List <T>;
public:
  // not implemented yet
private:
  ListNode <T>* m_node = nullptr;
};

template <typename T>
class List
{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef ListIterator<T> iterator;
  typedef ListConstIterator<T> const_iterator;

  List():
    m_size{0},  
    m_first{nullptr},
    m_last{nullptr}{}

  List(List const& list):
    m_size{0},
    m_first{nullptr},
    m_last{nullptr}{
      for (auto l = list.begin(); l != list.end(); ++l){
				push_back(*l);
      }
    }

  ~List(){
    clear();
  }

  bool empty() const{
    return size() == 0;
  }

  std::size_t size() const{
    return m_size;
  }

  T const& front() const{
    return m_first -> m_value;
  }

  T const& back() const{
    return m_last -> m_value;
  }

  void push_front(T const& x){
    if(empty()){
      ListNode<T>* n = new ListNode<T>(x, nullptr, nullptr);
      m_first = n;
      m_last = n;
    }else{
      ListNode<T>* n = new ListNode<T>(x, nullptr, m_first);
      m_first -> m_prev = n;
      m_first = n;
    }
    ++m_size; 
  }

  void push_back(T const& x){
    if(empty()){
      ListNode<T>* n = new ListNode<T>(x, nullptr, nullptr);
      m_first = n;
      m_last = n;
    }else{
      ListNode<T>* n = new ListNode<T>(x, m_last, nullptr);
      m_last -> m_next = n;
      m_last = n;
    }
    ++m_size;
  }

  void pop_front(){
    if(m_size == 0){
      std::cout << "empty list!";
    }
    if(m_size == 1){
      delete m_first;
      m_first = nullptr;
      m_last = nullptr;
      --m_size;
    }
    if(m_size > 1){
      auto temp = m_first -> m_next;
      delete m_first;
      temp -> m_prev = nullptr;
      m_first = temp;
      --m_size;
    }
  }

  void pop_back(){
    if(m_size == 0){
      std::cout << "empty list!";
    }
    if(m_size == 1){
      delete m_first;
      m_first = nullptr;
      m_last = nullptr;
      --m_size;
    }
    if(m_size > 1){
      auto temp = m_last -> m_prev;
      delete m_last;
      temp -> m_next = nullptr;
      m_last = temp;
      --m_size;
    }
  }

  void clear(){
    while(!empty()){
      pop_front();
    }
  }
  
  iterator begin() const{
    return ListIterator<T>(m_first);
  }

  iterator end() const{
    return ListIterator<T>();
  }

  iterator insert(iterator pos, T const& data){
    ListNode<T>* node = new ListNode<T>(data, pos.m_node -> m_prev, pos.m_node);
    pos.m_node -> m_prev -> m_next = node;
    pos.m_node -> m_prev = node;
    ++m_size;
    return iterator(node);
  }

  void reverse(){
    for (auto i = m_first; i != nullptr; i = i-> m_prev){
			std::swap(i -> m_prev, i -> m_next);
		}
		std::swap(m_first, m_last);
  }


  friend class ListIterator<T>;
  friend class ListConstIterator<T>;
// not implemented yet
private:
  std::size_t m_size = 0;
  ListNode<T>* m_first = nullptr;
  ListNode<T>* m_last = nullptr;
};

template<typename T>
bool operator==(List<T> const& xs, List<T> const& ys) {
  ListIterator<T> x = xs.begin();
  ListIterator<T> y = ys.begin();
  if(xs.size() == ys.size()){
    unsigned int z = 0;
    while(z < xs.size()){
      if(*x == *y){
        ++x;
        ++y;
        ++z;
      }else{
        return false;
      }
    }
    return true;
  }else{
    return false;
  }
}

template<typename T>
List<T> reverse(List<T> list){
  list.reverse();
  return list;
}

template<typename T>
bool operator!=(List<T> const& xs, List<T> const& ys) {
  return !(xs == ys);
}

#endif //#define BUW_LIST_HPP