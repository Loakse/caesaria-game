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

#include "cityservice_animals.hpp"
#include "city.hpp"
#include "gfx/tile.hpp"
#include "game/gamedate.hpp"
#include "gfx/tilemap.hpp"
#include "walker/animals.hpp"
#include "walker/constants.hpp"

using namespace constants;

namespace city
{

class Animals::Impl
{
public:
  static const unsigned int maxSheeps = 10;
  DateTime lastTimeUpdate;
  int updateInteval;
};

SrvcPtr Animals::create(PlayerCityPtr city)
{
  Animals* ret = new Animals( city );

  return ret;
}

std::string Animals::getDefaultName() { return "animals"; }

void Animals::update(const unsigned int time)
{
  if( time % _d->updateInteval != 1 )
    return;

  if( _d->lastTimeUpdate.month() != GameDate::current().month() )
  {
    _d->lastTimeUpdate = GameDate::current();
    Tilemap& tmap = _city.tilemap();
    TilesArray border = tmap.getRectangle( TilePos( 0, 0 ), Size( tmap.size() ) );
    TilesArray::iterator it=border.begin();
    while( it != border.end() )
    {
      if( !(*it)->isWalkable(true) )       {        it = border.erase( it );      }
      else  { ++it; }
    }

    WalkerList sheeps = _city.getWalkers( walker::sheep );
    if( sheeps.size() < Impl::maxSheeps )
    {
      WalkerPtr sheep = Sheep::create( &_city );
      if( sheep.isValid() )
      {
        TilesArray::iterator it = border.begin();
        std::advance( it, std::rand() % border.size() );
        ptr_cast<Sheep>(sheep)->send2City( (*it)->pos() );
      }
    }
  }
}

Animals::Animals( PlayerCityPtr city )
  : Srvc( *city.object(), Animals::getDefaultName() ), _d( new Impl )
{
  _d->lastTimeUpdate = GameDate::current();
  _d->updateInteval = GameDate::ticksInMonth() / 4;
}

}//end namespace city
