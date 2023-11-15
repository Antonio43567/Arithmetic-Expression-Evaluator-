#ifndef __LIST_H__
#define __LIST_H__

#include <iterator>
#include <ostream>

namespace ds {

/** List abstract class. */
template <typename ItemType> class List {
public:
  virtual int size() const = 0;
  virtual ItemType &get(int i) = 0;
  virtual const ItemType &get(int i) const = 0;
  virtual void insert(const ItemType &x, int i) = 0;
  virtual ItemType remove(int i) = 0;
  virtual void addFirst(const ItemType &x) = 0;
  virtual void addLast(const ItemType &x) = 0;
  virtual ItemType &getFirst() = 0;
  virtual ItemType &getLast() = 0;
  virtual const ItemType &getFirst() const = 0;
  virtual const ItemType &getLast() const = 0;
  virtual ItemType removeFirst() = 0;
  virtual ItemType removeLast() = 0;

  friend std::ostream &operator<<(std::ostream &os, const List &l) {
    os << "[";
    for (int i = 0; i < l.size(); i += 1) {
      if (i != 0) {
        os << ",";
      }
      os << l.get(i);
    }
    os << "]";
    return os;
  }
};

} // namespace ds

#endif // __LIST_H__