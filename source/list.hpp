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
  friend class List <T>;
  // not implemented yet
private:
  ListNode <T>* m_node = nullptr;
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


  friend class ListIterator<T>;
  friend class ListConstIterator<T>;
// not implemented yet
private:
  std::size_t m_size = 0;
  ListNode<T>* m_first = nullptr;
  ListNode<T>* m_last = nullptr;
};

#endif //#define BUW_LIST_HPP