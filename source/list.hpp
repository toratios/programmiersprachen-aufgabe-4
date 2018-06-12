#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>

// List.hpp

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
class ListIterator
{
public:
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;


  ListIterator():
    node_(nullptr) {}

  ListIterator(ListNode<T>* n):
    node_(n) {}

  reference operator*() const {
    return node_ -> m_value;
  }

  /*
  pointer operator->() const {
    return *node_;
  }
  */

  Self& operator++() {
    node_ = node_ -> m_next;
    return *this;
  }


  Self operator++(int) {
    Self temp = *this;
    ++(*this);
    return temp;
  }

  
  bool operator==(const Self& x) const {
    return node_ == x.get_node();
  }


  bool operator!=(const Self& x) const {
    return node_ != x.get_node();
  }

  Self next() const {
    if (node_)
      return ListIterator (node_ -> m_next);
    else
      return ListIterator (nullptr);
  }

  ListNode<T>* get_node() const {
    return node_;
  }

private:
  ListNode<T>* node_ = nullptr;
};


template <typename T>
class ListConstIterator
{ 
public:
  ListNode <T>* get_node() const {
    return node_;
  }

private:
  ListNode <T>* node_ = nullptr;
};


template <typename T>
class List
{
public:
  using value_type      = T;
  using pointer         = T*;
  using const_pointer   = T* const;
  using reference       = T&;
  using const_reference = T const&;
  using iterator        = ListIterator<T>;
  using const_iterator  = ListConstIterator<T>;

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

  List<T>(List<T> && list):
    m_size(list.m_size),
    m_first(list.m_first),
    m_last(list.m_last){
      list.m_size = 0;
      list.m_first = nullptr;
      list.m_last = nullptr;
    }

  List<T>(std::initializer_list<T> const& list):
    m_size{0},
    m_first{nullptr},
    m_last{nullptr}{
    for(auto& node : list)
      push_back(node);
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
    ListNode<T>* node = new ListNode<T>(data, pos.get_node() -> m_prev, pos.get_node());
    pos.get_node() -> m_prev -> m_next = node;
    pos.get_node() -> m_prev = node;
    ++m_size;
    return iterator(node);
  }

  void reverse(){
    for (auto i = m_first; i != nullptr; i = i-> m_prev){
			std::swap(i -> m_prev, i -> m_next);
		}
		std::swap(m_first, m_last);
  }

  List<T>& operator=(List<T> list){
    swap(list);
    return *this;
  }

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


template<typename T>
List<T> operator+(List<T> xs, List<T> const& ys) {
  for(auto& node : ys)
      xs.push_back(node);
  return xs;
}

#endif //#define BUW_LIST_HPP