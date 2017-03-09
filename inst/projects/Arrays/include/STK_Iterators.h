/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2016  Serge Iovleff, Université Lille 1, Inria

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the
    Free Software Foundation, Inc.,
    59 Temple Place,
    Suite 330,
    Boston, MA 02111-1307
    USA

    Contact : S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
*/

/*
 * Project:  stkpp::Arrays
 * created on: 4 déc. 2015
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

/** @file STK_Iterators.h
 *  @brief In this file we implement the const_iterator and iterator classes.
 **/


#ifndef STK_ITERATORS_H
#define STK_ITERATORS_H

namespace std
{

/** defined in std namespace in order to use algorithm of the STL */
template<class Derived>
struct iterator_traits< STK::ArrayBase<Derived>::iterator>
{
    typedef typename Derived::Type Type;
    typedef typename Derived::PtrType PtrType;

    typedef std::random_access_iterator_tag iterator_category;
    typedef Type value_type;
    typedef Type& reference;
    typedef Type* pointer;
    typedef std::ptrdiff_t difference_type;
};

} // namespace std

namespace STK
{

/** @ingroup Arrays
 * @brief A constant iterator allows to loop over the element of a dense (sparse)
 * matrix/vector or expression.
 **/
template<class Derived>
class ExprBase<Derived>::const_iterator
{

};

/** @ingroup Arrays
 *  @brief An iterator allows to loop over the element of a dense (sparse)
 *  matrix/vector.
 **/
template<class Derived>
class ArrayBase<Derived>::iterator
{

  protected:

    typedef typename Derived::Type Type;
    typedef typename Derived::Index Index;

    enum { IsRowMajor = (Derived::Flags&RowMajorBit)==RowMajorBit };
  public:
    iterator(const Derived& expr, Index outer)
      : m_expression(expr), m_inner(0), m_outer(outer), m_end(expr.innerSize())
    {}

    Type value() const
    { return m_expression.elt(m_outer, m_inner);}

    iterator operator++() { iterator i = *this; ptr_++; return i; }
    iterator operator++(int junk) { ptr_++; return *this; }

    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }

    bool operator==(const iterator& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const iterator& rhs) { return ptr_ != rhs.ptr_; }

    InnerIterator& operator++() { m_inner++; return *this; }
    Index index() const { return m_inner; }
    inline Index row() const { return IsRowMajor ? m_outer : index(); }
    inline Index col() const { return IsRowMajor ? index() : m_outer; }

    operator bool() const { return m_inner < m_end && m_inner>=0; }

  protected:
    const Derived& m_expression;
    Index m_inner;
    const Index m_outer;
    const Index m_end;
};

} // namespace STK

#endif /* STK_ITERATORS_H */
