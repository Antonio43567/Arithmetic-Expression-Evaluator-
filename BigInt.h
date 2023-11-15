#ifndef __BIGINT_H__
#define __BIGINT_H__

#include "VList.h"
#include <iostream>
#include <string>

namespace ds {

class BigInt {
private:
  VList<int> digits; // stores the digits of the BigInt

public:
  /**
   * Construct a new BigInt object from string.
   *
   * @param val a string of unlimited digits; default is empty string
   */
  explicit BigInt(const std::string &val = "") {

    for (unsigned j = 0; j < val.length(); j++) 
    {
      digits.addLast(val[j] - '0');
    }
  }

  /** Override `<<` to print all digits to os. */
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
    for (int i = 0; i < bi.digits.size(); i++)
      os << bi.digits.get(i);
    return os;
  }
  // overloading < operator 
  friend bool operator<(const BigInt &a, const BigInt &b)
  {
    // is a is more than b 
    if (a.digits.size() > b.digits.size()) 
    {
      return false;
    }
    // if size of a is less than b
    if (a.digits.size() < b.digits.size())
    {
      return true;
    }
    // same size
    for (int i = 0; i < a.digits.size(); i++)
    {
      if (a.digits.get(i) < b.digits.get(i)) // if digit is greater than b, return true
      {
        return true;
      }
      else if (a.digits.get(i) > b.digits.get(i)) // if digit is greater in a, return false
      {
        return false;
      }
    }
    return false;
  }

  inline BigInt operator+(const BigInt &other) const;
  inline BigInt operator-(const BigInt &other) const;
};

/** Return the *sum* of this BigInt and the `other` BigInt. */
BigInt BigInt::operator+(const BigInt &other) const {
  // Reference: https://en.wikipedia.org/wiki/Addition
  // Example: 456 + 1123 = 1579
  // TODO:

  int TheCarryOver = 0; 
  BigInt res; // res initialized to empty BigInt

  int List1 = digits.size() - 1; // taken from slides 
  int List2 = other.digits.size() - 1; // taken from slides j = last item index in other BigInt
  int num1, num2, sum;

  // Iterate through the two lists from the back with the least significant digit until all items have been consumed
  while (List1 >= 0 || List2 >= 0) 
  {
    if (List1 < 0) // if i<0, sets d1 to 0 (sets next item to 0 if all items in i are consumed)
    {
      num1 = 0;
    }
    else
    {
      num1 = digits.get(List1); // else, d1 set to current item in digits
    }

    if (List2 < 0) // if j<0, sets d2 to 0 (sets next item to 0 if all items in j are consumed)
    {
      num2 = 0;
    }
    else
    {
      num2 = other.digits.get(List2); // else, d2 set to current item in digits
    }

    sum = num1 + num2 + TheCarryOver; // sum = digit from current list + digit from other list + carry
     
    if (sum < 10) // sets carry to 0 if sum < 10, otherwise carry is set to 1 and 10 is minused from sum
    {
      TheCarryOver = 0;
    }
    else 
    {
      TheCarryOver = 1;
      sum -= 10; 
    }

    res.digits.addFirst(sum); // adds sum value to the first item in res
    List1--; 
    List2--;
  }

  if(TheCarryOver == 1) // Add 1 to the front of res.digits if carry == 1
  {
    res.digits.addFirst(1);
  }

  return res; // returns res value
}

/** Return the *absolute difference* between this and the `other` BigInt. */
BigInt BigInt::operator-(const BigInt &other) const {
  // Reference: https://en.wikipedia.org/wiki/Absolute_difference
  // Example: 456 - 1123 = 667
  // TODO:

  if (*this < other) // checking if current BigInt is less than other BigInt
  {
    return other - *this; 
  }
  int borrow = 0; // borrow initialized to 0
  BigInt res; // res initialized to empty BigInt

  int sub = digits.size() - 1; // slides
  int subj = other.digits.size() - 1; // slides

  int d1, d2, dif;

  // Iterate through the two lists from the back with the least significant digit until all items have been consumed
  while (sub >= 0 || subj >= 0)
  {
    d1 = digits.get(sub); 
    if (subj < 0) // if items in j or other BigInt consumed, then assign next item to 0
    {
      d2 = 0; 
    }
    else
    {
      d2 = other.digits.get(subj); // else d2 is set to the current j item in the other BigInt
    }
    dif = d1 - d2 - borrow; // dif = digit from current list - digit from other list - borrow

    if (dif >= 0) // If dif < 0, set borrow = 1 and dif += 10; otherwise, borrow = 0
    {
      borrow = 0;
    }
    else
    {
      borrow = 1;
      dif += 10;
    }

    res.digits.addFirst(dif); // add dif value to front of res.digits
    sub--;
    subj--; 
  }

  while(res.digits.getFirst() == 0 && res.digits.size() != 1) // removes any leading xeros
  {
    res.digits.removeFirst(); 
  }
  return res; //returns res value
}

} // namespace ds

#endif //__BIGINT_H__
