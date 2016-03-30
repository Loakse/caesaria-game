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
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#include "cityservice.hpp"
#include "core/logger.hpp"
#include "core/variant_map.hpp"
#include "city/city.hpp"
#include "core/variant.hpp"

namespace city
{

class Srvc::Impl
{
public:
  PlayerCityPtr city;
  std::string name;
};

void Srvc::timeStep(const unsigned int time) {}

std::string Srvc::name() const { return _d->name; }

void Srvc::setName(const std::string& name) { _d->name = name; }
void Srvc::attach(){ _d->city->addService( this ); }
bool Srvc::isDeleted() const { return false; }
void Srvc::destroy() {}
VariantMap Srvc::save() const { return VariantMap(); }

void Srvc::load(const VariantMap& stream) {}

Srvc::~Srvc()
{
  Logger::info("CityServices: remove {0}", name());
}

Srvc::Srvc(PlayerCityPtr city, const std::string& name)
  : _d( new Impl )
{
  _d->name = name;
  _d->city = city;
  setDebugName( name );
  Logger::info("CityServices: create {0}", name);
}

PlayerCityPtr Srvc ::_city() const { return _d->city; }

}
