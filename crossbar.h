/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __Crossbar_h__
#define __Crossbar_h__


//------------------------------------------------------------------------------
// Name: class CClass
// Desc: This class contains routing information for the capture data
//------------------------------------------------------------------------------
class CRouting {
public:
    class CRouting       *pLeftRouting;
    class CRouting       *pRightRouting;
    LONG                 VideoInputIndex;
    LONG                 VideoOutputIndex;
    LONG                 AudioInputIndex;
    LONG                 AudioOutputIndex;
    IAMCrossbar         *pXbar;
    LONG                 InputPhysicalType;
    LONG                 OutputPhysicalType;
    LONG                 Depth;

    CRouting () {};
    ~CRouting () {};
};

typedef CGenericList<CRouting> CRoutingList;




//------------------------------------------------------------------------------
// Name: class CCrossbar
// Desc: The actual helper class for Crossbars
//------------------------------------------------------------------------------
class CCrossbar
{
private:
    IPin                    *m_pStartingPin;
    CRouting                 m_RoutingRoot;
    CRoutingList            *m_RoutingList;
    int                      m_CurrentRoutingIndex;

    HRESULT BuildRoutingList (
                IPin     *pStartingInputPin,
                CRouting *pCRouting,
                int       Depth);
    HRESULT SaveRouting (CRouting *pRoutingNew);
    HRESULT DestroyRoutingList();
    BOOL    StringFromPinType (TCHAR *pc, int nSize, long lType);
    
    HRESULT GetCrossbarIPinAtIndex(
                IAMCrossbar *pXbar,
                LONG PinIndex,
                BOOL IsInputPin,
                IPin ** ppPin);
    HRESULT GetCrossbarIndexFromIPin (
                IAMCrossbar * pXbar,
                LONG * PinIndex,
                BOOL IsInputPin,
                IPin * pPin);

public:

    CCrossbar (IPin *pPin, HRESULT *phr);
    ~CCrossbar();

    HRESULT GetInputCount (LONG *pCount);
    HRESULT GetInputType  (LONG Index, LONG * PhysicalType);
    HRESULT GetInputName  (LONG Index, TCHAR * pName, LONG NameSize);
    HRESULT SetInputIndex (LONG Index);
    HRESULT GetInputIndex (LONG *Index);

};

#endif  // __Crossbar_h__
