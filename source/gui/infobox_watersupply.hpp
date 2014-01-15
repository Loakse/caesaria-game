// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _CAESARIA_INFOBOXWATERSUPPLY_H_INCLUDE_
#define _CAESARIA_INFOBOXWATERSUPPLY_H_INCLUDE_

#include "info_box.hpp"

namespace gui
{

// info box about a fontain
class InfoBoxFontain : public InfoBoxSimple
{
public:
   InfoBoxFontain( Widget* parent, const Tile& tile );
   virtual ~InfoBoxFontain();

   virtual void showDescription();
};

}//end namespace gui
#endif //_CAESARIA_INFOBOXWATERSUPPLY_H_INCLUDE_