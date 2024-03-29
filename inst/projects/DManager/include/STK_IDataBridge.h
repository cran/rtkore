/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2016 Serge Iovleff

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

    Contact : S..._DOT_I..._AT_stkpp.org (see copyright for ...)
*/

/*
 * Project:  stkpp::DManager
 * created on: 15 nov. 2013
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

/** @file STK_IDataBridge.h
 *  @brief In this file we define the interface class IDataBridge.
 **/

#ifndef STK_DATABRIDGEBASE_H
#define STK_DATABRIDGEBASE_H

#include <vector>

namespace STK
{
/** @ingroup DManager
 *  @brief Interface class wrapping a data set.
 *  Every data set wrapped by the end-user has to furnish an Id identifying it.
 **/
class IDataBridge
{
  public:
    /** default constructor. User must provide with the data set an Id */
    IDataBridge(std::string const& idData);
    /** copy constructor (Warning: will copy the data set)
     *  @param bridge the DataBridge to copy
     **/
    IDataBridge( IDataBridge const& bridge);

    /** destructor */
    virtual ~IDataBridge() {}

    /** return the Id of the mixture */
    inline std::string const& idData() const { return idData_;}

  private:
    /** Id data of the mixture */
    std::string idData_;
};

/* default constructor. */
inline IDataBridge::IDataBridge( std::string const& idData)
                               : idData_(idData) {}
/* copy constructor
 *  @param manager the IDataBridge to copy
 **/
inline IDataBridge::IDataBridge( IDataBridge const& bridge)
                               : idData_(bridge.idData_)
{}


} // namespace STK

#endif /* STK_DATABRIDGEBASE_H */
