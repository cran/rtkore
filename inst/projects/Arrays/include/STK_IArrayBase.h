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
 * created on: 13 oct. 2012
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

/** @file STK_IArrayBase.h
 *  @brief In this file we define the interface base class IIArrayBase
 **/

#ifndef STK_IARRAYBASE_H
#define STK_IARRAYBASE_H

#include "STK_ArrayBase.h"


namespace STK
{

/** @ingroup Arrays
 *  @brief base class for template arrays.
 *
 * This class is the base that is inherited by all containers storing
 * values (matrix, vector, point). Expressions are not arrays. Any derived
 * class can be a lhs in an expression.
 *
 * The common API for these objects is contained in this class.
 *
 *  @tparam Derived is the derived type, e.g., a matrix, vector, point type or
 *  an expression.
 **/
template< class Derived>
class IArrayBase: public ArrayBase<Derived>
{
  public:
    typedef ArrayBase<Derived> Base;
    typedef typename hidden::Traits<Derived>::Type Type;
    typedef typename hidden::Traits<Derived>::ConstReturnType ConstReturnType;

    typedef typename hidden::Traits<Derived>::Row Row;
    typedef typename hidden::Traits<Derived>::Col Col;
    typedef typename hidden::Traits<Derived>::SubRow SubRow;
    typedef typename hidden::Traits<Derived>::SubCol SubCol;
    typedef typename hidden::Traits<Derived>::SubVector SubVector;
    typedef typename hidden::Traits<Derived>::SubArray SubArray;

    enum
    {
      structure_ = hidden::Traits<Derived>::structure_,
      orient_    = hidden::Traits<Derived>::orient_,
      sizeRows_  = hidden::Traits<Derived>::sizeRows_,
      sizeCols_  = hidden::Traits<Derived>::sizeCols_,
      storage_   = hidden::Traits<Derived>::storage_
    };

  protected:
    /** Default constructor. Default values are cols=(1:0) and rows=(1:0). */
    IArrayBase(): Base() {}
    /** destructor */
    ~IArrayBase() {}

  public:
    /** @return the jth column of this */
    inline Col col(int j) const { return this->asDerived().colImpl(j);}
    /** @return the jth column of this in the range I*/
    inline SubCol col(Range const& I, int j) const
    {
      STK_STATIC_ASSERT_TWO_DIMENSIONS_ONLY(Derived)
#ifdef STK_BOUNDS_CHECK
      if (this->beginRows() > I.begin()) { STKOUT_OF_RANGE_2ARG(IArrayBase::col, I, j, beginRows() > I.begin());}
      if (this->endRows() < I.end())     { STKOUT_OF_RANGE_2ARG(IArrayBase::col, I, j, endRows() < I.end());}
      if (this->beginCols() > j)         { STKOUT_OF_RANGE_2ARG(IArrayBase::col, I, j, beginCols() > j);}
      if (this->endCols() <= j)          { STKOUT_OF_RANGE_2ARG(IArrayBase::col, I, j, endCols() <= j);}
#endif
      return this->asDerived().colImpl(I, j);
    }
    /** @return the sub array with the column in the range J */
    inline SubArray col(Range const& J) const
    {
      STK_STATIC_ASSERT_TWO_DIMENSIONS_ONLY(Derived)
#ifdef STK_BOUNDS_CHECK
      if (this->beginCols() > J.begin())
      { STKOUT_OF_RANGE_1ARG(IArrayBase::col, J, beginCols() > J.begin());}
      if (this->endCols() < J.end())
      { STKOUT_OF_RANGE_1ARG(IArrayBase::col, J, endCols() < J.end());}
#endif
      return this->asDerived().colImpl(J);
    }
    /** @return the ith row of this */
    inline Row row(int i) const
    {
#ifdef STK_BOUNDS_CHECK
      if (this->beginRows() > i) { STKOUT_OF_RANGE_1ARG(IArrayBase::row, i, beginRows() > i);}
      if (this->endRows() <= i)  { STKOUT_OF_RANGE_1ARG(IArrayBase::row, i, endRows() <= i);}
#endif
      return this->asDerived().rowImpl(i);
    }
    /** @return the ith row of this in the range J */
    inline SubRow row(int i, Range const& J) const
    {
      STK_STATIC_ASSERT_TWO_DIMENSIONS_ONLY(Derived)
      return this->asDerived().rowImpl(i,J);
    }

    /** @return the sub array with the rows in the range J */
    inline SubArray row(Range const& I) const
    {
      STK_STATIC_ASSERT_TWO_DIMENSIONS_ONLY(Derived)
      return this->asDerived().rowImpl(I);
    }
    /** @return the sub-array (I,J)*/
    inline SubArray sub(Range const& I, Range const& J) const
    {
      STK_STATIC_ASSERT_TWO_DIMENSIONS_ONLY(Derived)
      return this->asDerived().subImpl(I, J);
    }
    /** @return the sub-vector in the range I*/
    inline SubVector sub(Range const& I) const
    {
      STK_STATIC_ASSERT_ONE_DIMENSION_ONLY(Derived)
      return this->asDerived().subImpl(I);
    }

    // overloaded operators
    /** @return a reference on the ith element
     *  @param i index of the ith element
     **/
    inline Type& operator[](int i) { return this->elt(i);}
    /** @return the ith element
     *  @param i index of the ith element
     **/
    inline Type const& operator[](int i) const { return this->elt(i);}
    /** @return the ith element
     *  @param I range to get
     **/
    inline SubVector operator[](Range const& I) const { return this->sub(I);}
    /** @return a reference on the element (i,j) of the 2D container.
     *  @param i, j indexes of the row and of the column
     **/
    inline Type& operator()(int i, int j) { return this->elt(i,j);}
    /** @return a constant reference on the element (i,j) of the 2D container.
     *  @param i,j row and column indexes
     **/
    inline Type const& operator()(int i, int j) const { return this->elt(i,j);}
    /** @return a constant reference on the number */
    inline Type const& operator()() const { return this->elt();}
    /** @return the number */
    inline Type& operator()() { return this->elt();}
    /** @param I range of the index of the rows
     *  @param j index of the column
     *  @return a Vertical container containing the column @c j of this
     *  in the range @c I
     **/
    inline SubCol operator()(Range const& I, int j) const { return this->col(I, j);}
    /** @param i index of the row
     *  @param J range of the columns
     *  @return an Horizontal container containing the row @c i of this
     *  in the range @c J
     **/
    inline SubRow operator()(int i, Range const& J) const { return this->row(i, J);}
    /** @param I,J range of the rows and of the columns
     *  @return a 2D container containing this in the range @c I, @c J
     **/
    inline SubArray operator()(Range const& I, Range const& J) const { return this->sub(I, J);}
};

} // namespace STK

#undef MAKE_RESHAPE_OPERATOR

#endif /* STK_ARRAYBASE_H_ */