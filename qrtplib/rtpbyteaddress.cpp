/*

 This file is a part of JRTPLIB
 Copyright (c) 1999-2017 Jori Liesenborgs

 Contact: jori.liesenborgs@gmail.com

 This library was developed at the Expertise Centre for Digital Media
 (http://www.edm.uhasselt.be), a research center of the Hasselt University
 (http://www.uhasselt.be). The library is based upon work done for
 my thesis at the School for Knowledge Technology (Belgium/The Netherlands).

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 IN THE SOFTWARE.

 */

#include "rtpbyteaddress.h"

namespace qrtplib
{

bool RTPByteAddress::IsSameAddress(const RTPAddress *addr) const
{
    if (addr == 0)
        return false;
    if (addr->GetAddressType() != ByteAddress)
        return false;

    const RTPByteAddress *addr2 = (const RTPByteAddress *) addr;

    if (addr2->addresslength != addresslength)
        return false;
    if (addresslength == 0 || (memcmp(hostaddress, addr2->hostaddress, addresslength) == 0))
    {
        if (port == addr2->port)
            return true;
    }
    return false;
}

bool RTPByteAddress::IsFromSameHost(const RTPAddress *addr) const
{
    if (addr == 0)
        return false;
    if (addr->GetAddressType() != ByteAddress)
        return false;

    const RTPByteAddress *addr2 = (const RTPByteAddress *) addr;

    if (addr2->addresslength != addresslength)
        return false;
    if (addresslength == 0 || (memcmp(hostaddress, addr2->hostaddress, addresslength) == 0))
        return true;
    return false;
}

RTPAddress *RTPByteAddress::CreateCopy() const
{
    RTPByteAddress *a = new RTPByteAddress(hostaddress, addresslength, port);
    return a;
}

} // end namespace
