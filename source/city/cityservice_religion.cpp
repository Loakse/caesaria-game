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

#include "cityservice_religion.hpp"
#include "city/helper.hpp"
#include "core/safetycast.hpp"
#include "core/position.hpp"
#include "game/gamedate.hpp"
#include "objects/religion.hpp"
#include "religion/pantheon.hpp"
#include "events/event.hpp"
#include "core/foreach.hpp"
#include "core/stringhelper.hpp"
#include "core/gettext.hpp"
#include "objects/constants.hpp"
#include "core/logger.hpp"
#include "core/safetycast.hpp"

using namespace constants;
using namespace religion;

namespace city
{

class Religion::Impl
{
public:
  PlayerCityPtr city;
  DateTime lastDate;
  struct TempleInfo
  {
    int smallTempleNum;
    int bigTempleNum;

    TempleInfo() : smallTempleNum( 0 ), bigTempleNum( 0 ) {}
  };

  typedef std::map< RomeDivinityPtr, TempleInfo > TemplesMap;
  TemplesMap templesCoverity;
  TempleInfo maxTemples;

  void updateRelation( RomeDivinityPtr divn );
};

SrvcPtr Religion::create(PlayerCityPtr city)
{
  SrvcPtr ret( new Religion( city ) );
  ret->drop();

  return ret;
}

std::string Religion::getDefaultName() { return "religion"; }

Religion::Religion(PlayerCityPtr city )
  : Srvc( *city.object(), Religion::getDefaultName() ), _d( new Impl )
{
  _d->city = city;
  _d->lastDate = GameDate::current();
}

void Religion::update( const unsigned int time )
{  
  if( _d->lastDate.month() == GameDate::current().month() )
    return;

  Logger::warning( "Religion: start update relations" );
  _d->lastDate = GameDate::current();

  Pantheon::Divinities divinities = Pantheon::instance().all();

  //clear temples info
  _d->templesCoverity.clear();

  //update temples info
  Helper helper( _d->city );
  TempleList temples = helper.find<Temple>( building::religionGroup );
  foreach( it, temples)
  {
    Impl::TempleInfo& info = _d->templesCoverity[ (*it)->getDivinity() ];
    TemplePtr temple = ptr_cast<Temple>( *it );
    if( temple.isValid() && temple->getDivinity().isValid() )
    {
       if( is_kind_of<BigTemple>( temple ) ) { info.bigTempleNum++; }
       else { info.smallTempleNum++; }
    }
  }

  _d->maxTemples = Impl::TempleInfo();
  foreach( it, divinities )
  {
    Impl::TempleInfo& info = _d->templesCoverity[ *it ];
    _d->maxTemples.bigTempleNum = std::max<int>( info.bigTempleNum, _d->maxTemples.bigTempleNum );
    _d->maxTemples.smallTempleNum = std::max<int>( info.smallTempleNum, _d->maxTemples.smallTempleNum );
  }

  foreach( it, divinities )
  {
    _d->updateRelation( *it );
  }
}

void Religion::Impl::updateRelation(RomeDivinityPtr divn)
{
  Helper helper( city );
  int peopleReached = 0;
  TempleList temples = helper.find<Temple>( building::religionGroup );

  foreach( temple, temples )
  {
    if( (*temple)->getDivinity() == divn )
    {
      peopleReached += (*temple)->parishionerNumber();
    }
  }

  float faithIncome = (float)peopleReached / (float)(city->getPopulation()+1);
  Impl::TempleInfo& myTemples = templesCoverity[ divn ];

  float faithAddiction = 0;
  float smallTempleKoeff = ( myTemples.smallTempleNum < maxTemples.smallTempleNum ? 0.8 : 1 );
  float bigTempleKoeff = ( myTemples.bigTempleNum < maxTemples.bigTempleNum ? 0.5 : 1 );

  faithAddiction *= ( smallTempleKoeff * bigTempleKoeff );
  faithIncome *= faithAddiction;

  Logger::warning( "Religion: faith income for %s is %f[r=%f]", divn->name().c_str(), faithIncome, divn->relation() );
  divn->updateRelation( faithIncome, city );
}

}//end namespace city
