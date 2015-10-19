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

#include "layerfire.hpp"
#include "objects/overlay.hpp"
#include "objects/constants.hpp"
#include "objects/house.hpp"
#include "objects/house_spec.hpp"
#include "game/resourcegroup.hpp"
#include "city/statistic.hpp"
#include "constants.hpp"
#include "gfx/tilemap_camera.hpp"
#include "core/event.hpp"
#include "core/gettext.hpp"

using namespace gfx;

namespace citylayer
{

static const char* fireLevelName[] = {
                                       "##no_fire_risk##",
                                       "##very_low_fire_risk##", "##some_low_fire_risk##", "##low_fire_risk##",
                                       "##middle_file_risk##", "##some_fire_risk##", "##high_fire_risk##",
                                       "##very_high_fire_risk##",
                                       "##extreme_fire_risk##", "##moment_fire_risk##"
                                     };


int Fire::type() const { return citylayer::fire; }

void Fire::drawTile( const RenderInfo& rinfo, Tile& tile )
{

  if( tile.overlay().isNull() )
  {
    drawPass( rinfo, tile, Renderer::ground );
    drawPass( rinfo, tile, Renderer::groundAnimation );
  }
  else
  {
    bool needDrawAnimations = false;
    OverlayPtr overlay = tile.overlay();
    int fireLevel = 0;
    if( _isVisibleObject( overlay->type() ) )
    {
      // Base set of visible objects
      needDrawAnimations = true;
    }
    else if( overlay->type() == object::house )
    {
      auto house = overlay.as<House>();
      fireLevel = (int)house->state( pr::fire );
      needDrawAnimations = (house->level() <= HouseLevel::hovel) && house->habitants().empty();
      drawArea( rinfo, overlay->area(), ResourceGroup::foodOverlay, config::id.overlay.inHouseBase  );
    }
    else //other buildings
    {
      auto constr = overlay.as<Construction>();
      if( constr != 0 )
      {
        fireLevel = (int)constr->state( pr::fire );
      }

      drawArea( rinfo, overlay->area(), ResourceGroup::foodOverlay, config::id.overlay.base  );
    }

    if( needDrawAnimations )
    {
      Layer::drawTile( rinfo, tile );
      registerTileForRendering( tile );
    }
    else if( fireLevel >= 0)
    {
      Point screenPos = tile.mappos() + rinfo.offset;
      drawColumn( rinfo, screenPos, fireLevel );
    }
  }

  tile.setRendered();
}

void Fire::handleEvent(NEvent& event)
{
  if( event.EventType == sEventMouse )
  {
    switch( event.mouse.type  )
    {
    case mouseMoved:
    {
      Tile* tile = _camera()->at( event.mouse.pos(), false );  // tile under the cursor (or NULL)
      std::string text = "";
      if( tile != 0 )
      {
        auto construction = tile->overlay<Construction>();
        if( construction != 0 )
        {
          int fireLevel = math::clamp<int>( construction->state( pr::fire ), 0, 100 );
          text = fireLevelName[ math::clamp<int>( fireLevel / 10, 0, 9 ) ];
        }
      }

      _setTooltipText( _(text) );
    }
    break;

    default: break;
    }
  }

  Layer::handleEvent( event );
}

LayerPtr Fire::create( Camera& camera, PlayerCityPtr city)
{
  LayerPtr ret( new Fire( camera, city ) );
  ret->drop();

  return ret;
}

Fire::Fire( Camera& camera, PlayerCityPtr city)
  : Info( camera, city, 18 )
{
  _addWalkerType( walker::prefect );
  _initialize();
}

}//end namespace citylayer
