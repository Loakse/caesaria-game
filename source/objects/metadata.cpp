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
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com
// Copyright 2012-2015 dalerank, dalerankn8@gmail.com

#include "metadata.hpp"

#include <map>
#include "core/gettext.hpp"
#include "core/saveadapter.hpp"
#include "core/utils.hpp"
#include "core/enumerator.hpp"
#include "core/foreach.hpp"
#include "core/variant_map.hpp"
#include "core/logger.hpp"
#include "constants.hpp"
#include "gfx/picture_info_bank.hpp"

using namespace constants;
using namespace gfx;

const char* MetaDataOptions::cost = "cost";
const char* MetaDataOptions::requestDestroy = "requestDestroy";
const char* MetaDataOptions::employers = "employers";
const char* MetaDataOptions::c3logic = "c3logic";

MetaData MetaData::invalid = MetaData( object::unknown, "unknown" );

class BuildingTypeHelper : public EnumsHelper<object::Type>
{
public:
  BuildingTypeHelper() : EnumsHelper<object::Type>( object::unknown )
  {
#define __REG_TOTYPE(a) append(object::a, CAESARIA_STR_EXT(a) );
    __REG_TOTYPE( amphitheater )
    __REG_TOTYPE( theater )
    __REG_TOTYPE( hippodrome )
    __REG_TOTYPE( colloseum )
    __REG_TOTYPE( actorColony )
    __REG_TOTYPE( gladiatorSchool )
    __REG_TOTYPE( lionsNursery )
    __REG_TOTYPE( chariotSchool )
    __REG_TOTYPE( house )
    __REG_TOTYPE( road )
    __REG_TOTYPE( plaza )
    __REG_TOTYPE( garden )
    __REG_TOTYPE( senate )
    __REG_TOTYPE( forum )
    __REG_TOTYPE( governorHouse )
    __REG_TOTYPE( governorVilla )
    __REG_TOTYPE( governorPalace )
    __REG_TOTYPE( fort_legionaries )
    __REG_TOTYPE( fort_javelin )
    __REG_TOTYPE( fort_horse )
    __REG_TOTYPE( prefecture )
    __REG_TOTYPE( barracks )
    __REG_TOTYPE( military_academy )
    __REG_TOTYPE( clinic )
    __REG_TOTYPE( hospital )
    __REG_TOTYPE( baths )
    __REG_TOTYPE( barber )
    __REG_TOTYPE( school )
    __REG_TOTYPE( academy );
    __REG_TOTYPE( library )
    __REG_TOTYPE( missionaryPost )
    __REG_TOTYPE( small_ceres_temple )
    __REG_TOTYPE( small_neptune_temple )
    __REG_TOTYPE( small_mars_temple )
    __REG_TOTYPE( small_mercury_temple )
    __REG_TOTYPE( small_venus_temple )
    __REG_TOTYPE( big_ceres_temple )
    __REG_TOTYPE( big_neptune_temple )
    __REG_TOTYPE( big_mars_temple )
    __REG_TOTYPE( big_mercury_temple )
    __REG_TOTYPE( big_venus_temple )
    __REG_TOTYPE( oracle )
    __REG_TOTYPE( market )
    __REG_TOTYPE( granery )
    __REG_TOTYPE( warehouse )
    __REG_TOTYPE( wheat_farm)
    __REG_TOTYPE( fig_farm )
    __REG_TOTYPE( vegetable_farm )
    __REG_TOTYPE( olive_farm)
    __REG_TOTYPE( vinard )
    __REG_TOTYPE( meat_farm )
    __REG_TOTYPE( quarry )
    __REG_TOTYPE( iron_mine )
    __REG_TOTYPE( lumber_mill )
    __REG_TOTYPE( clay_pit )
    __REG_TOTYPE( wine_workshop )
    __REG_TOTYPE( oil_workshop )
    __REG_TOTYPE( weapons_workshop )
    __REG_TOTYPE( furniture_workshop )
    __REG_TOTYPE( pottery_workshop )
    __REG_TOTYPE( engineering_post )
    __REG_TOTYPE( statue_small )
    __REG_TOTYPE( statue_middle )
    __REG_TOTYPE( statue_big )
    __REG_TOTYPE( low_bridge )
    __REG_TOTYPE( high_bridge )
    __REG_TOTYPE( dock )
    __REG_TOTYPE( shipyard )
    __REG_TOTYPE( wharf )
    __REG_TOTYPE( triumphal_arch )
    __REG_TOTYPE( well )
    __REG_TOTYPE( fountain )
    __REG_TOTYPE( aqueduct )
    __REG_TOTYPE( reservoir )
    __REG_TOTYPE( native_hut )
    __REG_TOTYPE( native_center )
    __REG_TOTYPE( native_field )
    __REG_TOTYPE( burning_ruins )
    __REG_TOTYPE( burned_ruins )
    __REG_TOTYPE( plague_ruins )
    __REG_TOTYPE( collapsed_ruins )
    __REG_TOTYPE( gatehouse )
    __REG_TOTYPE( tower )
    __REG_TOTYPE( wall )
    __REG_TOTYPE( fortification )
    __REG_TOTYPE( elevation )
    __REG_TOTYPE( rift )
    __REG_TOTYPE( river )
    __REG_TOTYPE( tree )
    __REG_TOTYPE( waymark )
    __REG_TOTYPE( terrain )
    __REG_TOTYPE( water )
    __REG_TOTYPE( meadow )
    __REG_TOTYPE( roadBlock )

    append( object::unknown,        "" );
#undef __REG_TOTYPE
 }
};

class BuildingClassHelper : public EnumsHelper<object::Group>
{
public:
  BuildingClassHelper() : EnumsHelper<object::Group>( object::group::unknown )
  {
    append( object::group::industry, "industry" );
    append( object::group::obtain, "rawmaterial" );
    append( object::group::food, "food" );
    append( object::group::disaster, "disaster" );
    append( object::group::religion, "religion" );
    append( object::group::military, "military" );
    append( object::group::native, "native" );
    append( object::group::water, "water" );
    append( object::group::administration, "administration" );
    append( object::group::bridge, "bridge" );
    append( object::group::engineering, "engineer" );
    append( object::group::trade, "trade" );
    append( object::group::tower, "tower" );
    append( object::group::gate, "gate" );
    append( object::group::security, "security" );
    append( object::group::education, "education" );
    append( object::group::health, "health" );
    append( object::group::sight, "sight" );
    append( object::group::garden, "garden" );
    append( object::group::road, "road" );
    append( object::group::entertainment, "entertainment" );
    append( object::group::house, "house" );
    append( object::group::wall, "wall" );
    append( object::group::unknown, "" );
  }
};

class MetaData::Impl
{
public:
  Desirability desirability;
  object::Type tileovType;
  object::Group group;
  std::string name;  // debug name  (english, ex:"iron")
  std::string sound;
  StringArray desc;
  VariantMap options;
  std::string prettyName;

  std::map< int, StringArray > pictures;
};

MetaData::MetaData(const object::Type buildingType, const std::string& name )
  : _d( new Impl )
{
  _d->prettyName = "##" + name + "##";
  _d->tileovType = buildingType;
  _d->group = object::group::unknown;
  _d->name = name;  
}

MetaData::MetaData(const MetaData &a) : _d( new Impl )
{
  *this = a;
}

MetaData::~MetaData(){}
std::string MetaData::name() const{  return _d->name;}
std::string MetaData::sound() const{  return _d->sound;}
std::string MetaData::prettyName() const {  return _d->prettyName;}

std::string MetaData::description() const
{
  if( _d->desc.empty() )
    return "##" + _d->name + "_info##";

  return _d->desc[ rand() % _d->desc.size() ];
}

object::Type MetaData::type() const {  return _d->tileovType;}
Desirability MetaData::desirability() const{  return _d->desirability;}

Picture MetaData::picture(int size) const
{
  StringArray& array = _d->pictures[ size ];
  return Picture::load( array.random() );
}

Variant MetaData::getOption(const std::string &name, Variant defaultVal ) const
{
  VariantMap::iterator it = _d->options.find( name );
  return it != _d->options.end() ? it->second : defaultVal;
}

MetaData& MetaData::operator=(const MetaData &a)
{
  _d->tileovType = a._d->tileovType;
  _d->name = a._d->name;
  _d->prettyName = a._d->prettyName;
  _d->sound = a._d->sound;
  _d->pictures = a._d->pictures;
  _d->group = a._d->group;
  _d->desirability = a._d->desirability;
  _d->desc = a._d->desc;
  _d->options = a._d->options;

  return *this;
}

object::Group MetaData::group() const {  return _d->group; }

class MetaDataHolder::Impl
{
public:
  BuildingTypeHelper typeHelper;
  BuildingClassHelper classHelper;

  typedef std::map<object::Type, MetaData> ObjectsMap;
  typedef std::map<good::Product, object::Type> FactoryInMap;

  ObjectsMap objectsInfo;// key=building_type, value=data
  FactoryInMap mapBuildingByInGood;
};

MetaDataHolder& MetaDataHolder::instance()
{
  static MetaDataHolder inst;
  return inst;
}

object::Type MetaDataHolder::getConsumerType(const good::Product inGoodType) const
{
  object::Type res = object::unknown;

  Impl::FactoryInMap::iterator mapIt;
  mapIt = _d->mapBuildingByInGood.find(inGoodType);
  if (mapIt != _d->mapBuildingByInGood.end())
  {
    res = mapIt->second;
  }
  return res;
}

const MetaData& MetaDataHolder::getData(const object::Type buildingType)
{
  Impl::ObjectsMap::iterator mapIt;
  mapIt = instance()._d->objectsInfo.find(buildingType);
  if (mapIt == instance()._d->objectsInfo.end())
  {
    Logger::warning("MetaDataHolder::Unknown objects %d", buildingType );
    return MetaData::invalid;
  }
  return mapIt->second;
}

bool MetaDataHolder::hasData(const object::Type buildingType) const
{
  bool res = true;
  Impl::ObjectsMap::iterator mapIt;
  mapIt = _d->objectsInfo.find(buildingType);
  if (mapIt == _d->objectsInfo.end())
  {
    res = false;
  }
  return res;
}

MetaDataHolder::OverlayTypes MetaDataHolder::availableTypes() const
{
  OverlayTypes ret;
  foreach( it, _d->objectsInfo )  { ret.push_back( it->first );  }
  return ret;
}

void MetaDataHolder::addData(const MetaData &data)
{
  object::Type buildingType = data.type();

  if (hasData(buildingType))
  {
    Logger::warning( "MetaDataHolder: Info is already set for " + data.name() );
    return;
  }

  _d->objectsInfo.insert(std::make_pair(buildingType, data));
}


MetaDataHolder::MetaDataHolder() : _d( new Impl )
{
}

void MetaDataHolder::initialize( vfs::Path filename )
{
  // populate _mapBuildingByInGood
  _d->mapBuildingByInGood[good::iron  ] = object::weapons_workshop;
  _d->mapBuildingByInGood[good::timber] = object::furniture_workshop;
  _d->mapBuildingByInGood[good::clay  ] = object::pottery_workshop;
  _d->mapBuildingByInGood[good::olive ] = object::oil_workshop;
  _d->mapBuildingByInGood[good::grape ] = object::wine_workshop;

  VariantMap constructions = config::load( filename );

  foreach( mapItem, constructions )
  {
    VariantMap options = mapItem->second.toMap();

    const object::Type btype = findType( mapItem->first );
    if( btype == object::unknown )
    {
      Logger::warning( "!!!Warning: can't associate type with %s", mapItem->first.c_str() );
      continue;
    }

    Impl::ObjectsMap::const_iterator bdataIt = _d->objectsInfo.find( btype );
    if( bdataIt != _d->objectsInfo.end() )
    {
      Logger::warning( "!!!Warning: type %s also initialized", mapItem->first.c_str() );
      continue;
    }

    MetaData bData( btype, mapItem->first );

    bData._d->options = options;
    VariantMap desMap = options[ "desirability" ].toMap();
    bData._d->desirability.VARIANT_LOAD_ANY(base, desMap );
    bData._d->desirability.VARIANT_LOAD_ANY(range, desMap);
    bData._d->desirability.VARIANT_LOAD_ANY(step, desMap );

    bData._d->desc = options.get( "desc" ).toStringArray();
    bData._d->prettyName = options.get( "prettyName", Variant( bData._d->prettyName ) ).toString();

    bData._d->group = findGroup( options[ "class" ].toString() );

    VariantList basePic = options[ "image" ].toList();
    if( !basePic.empty() )
    {
      std::string groupName = basePic.get( 0 ).toString();
      int imageIndex = basePic.get( 1 ).toInt();
      Variant vOffset = options[ "image.offset" ];
      if( vOffset.isValid() )
      {
        PictureInfoBank::instance().setOffset( groupName, imageIndex, vOffset.toPoint() );
      }

      Picture pic = Picture::load( groupName, imageIndex );
      bData._d->pictures[ 0 ] << pic.name();
    }

    VariantMap extPics = options[ "image.ext" ].toMap();
    foreach( it, extPics )
    {
      VariantMap info = it->second.toMap();
      VARIANT_INIT_ANY( int, size, info )
      VARIANT_INIT_ANY( int, start, info );
      VARIANT_INIT_ANY( int, count, info );
      VARIANT_INIT_STR( rc, info );
      for( int i=0; i < count; i++ )
      {
        Picture pic = Picture::load( rc, start + i );
        if( pic.isValid() )
        {
          bData._d->pictures[ size ] << pic.name();
        }
      }
    }

    VariantList soundVl = options[ "sound" ].toList();
    if( !soundVl.empty() )
    {
      bData._d->sound = utils::format( 0xff, "%s_%05d",
                                              soundVl.get( 0 ).toString().c_str(), soundVl.get( 1 ).toInt() );
    }

    addData( bData );
  }
}

MetaDataHolder::~MetaDataHolder() {}

object::Type MetaDataHolder::findType( const std::string& name )
{
  object::Type type = instance()._d->typeHelper.findType( name );

  if( type == instance()._d->typeHelper.getInvalid() )
  {
    Logger::warning( "MetaDataHolder: can't find type for typeName " + ( name.empty() ? "null" : name) );
    return object::unknown;
  }

  return type;
}

std::string MetaDataHolder::findTypename(object::Type type)
{
  return instance()._d->typeHelper.findName( type );
}

object::Group MetaDataHolder::findGroup( const std::string& name )
{
  object::Group type = instance()._d->classHelper.findType( name );

  if( type == instance()._d->classHelper.getInvalid() )
  {
    Logger::warning( "MetaDataHolder: can't find object class for className %s", name.c_str() );
    return object::group::unknown;
  }

  return type;
}

std::string MetaDataHolder::findGroupname(object::Group group)
{
  return instance()._d->classHelper.findName( group );
}

std::string MetaDataHolder::findPrettyName(object::Type type)
{
  return instance().getData( type ).prettyName();
}

std::string MetaDataHolder::findDescription(object::Type type)
{
  return instance().getData( type ).description();
}

Picture MetaDataHolder::randomPicture(object::Type type, Size size)
{
  const MetaData& md = getData( type );
  return md.picture( size.width() );
}
