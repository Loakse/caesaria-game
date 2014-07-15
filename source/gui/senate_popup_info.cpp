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

#include "senate_popup_info.hpp"
#include "gfx/renderer.hpp"
#include "objects/senate.hpp"
#include "gfx/decorator.hpp"
#include "core/gettext.hpp"
#include "environment.hpp"
#include "gfx/tile.hpp"
#include "gfx/engine.hpp"
#include "core/stringhelper.hpp"
#include "core/color.hpp"
#include "core/time.hpp"
#include "gfx/tilemap_camera.hpp"

using namespace gfx;

namespace gui
{

class SenatePopupInfo::Impl
{
public:
  Point startPos;
  Point ratingStartPos;
  Point offset;
  Font font;
  gfx::Renderer* cityRenderer;
  PictureRef background;  
  int lastUpdateTime;

  void updateRatings( SenatePtr senate )
  {
    lastUpdateTime = DateTime::elapsedTime();

    background->fill( 0xffffffff, Rect( ratingStartPos.x(), ratingStartPos.y(), background->width()-2, background->height()-2 ) );
    font.draw( *background, StringHelper::format( 0xff, "%d %%", senate->getStatus( Senate::workless ) ), ratingStartPos, false );
    font.draw( *background, StringHelper::format( 0xff, "%d", senate->getStatus( Senate::culture ) ), ratingStartPos + offset, false );
    font.draw( *background, StringHelper::format( 0xff, "%d", senate->getStatus( Senate::prosperity ) ), ratingStartPos + offset * 2, false );
    font.draw( *background, StringHelper::format( 0xff, "%d", senate->getStatus( Senate::peace ) ), ratingStartPos + offset * 3, false );
    font.draw( *background, StringHelper::format( 0xff, "%d", senate->getStatus( Senate::favour ) ), ratingStartPos + offset * 4, false );
  }
};

SenatePopupInfo::SenatePopupInfo( Widget* parent, gfx::Renderer& mapRenderer ) :
  Widget( parent, -1, Rect( -1, -1, 0, 0 )), _d( new Impl )
{
  _d->cityRenderer = &mapRenderer;
  _d->startPos = Point( 6, 6 );
  _d->ratingStartPos = Point( 186, 6 );
  _d->offset = Point( 0, 14 );
  _d->lastUpdateTime = 0;
  _d->background.reset( Picture::create( Size( 240, 80 ) ) );

  _d->background->fill( 0xff000000, Rect( Point( 0, 0 ), _d->background->size() ) );
  _d->background->fill( 0xffffffff, Rect( Point( 1, 1 ), _d->background->size() - Size( 2, 2 ) ) );
  
  _d->font = Font::create( FONT_1 );

  _d->font.draw( *_d->background, _("##senatepp_unemployment##"), _d->startPos, false );
  _d->font.draw( *_d->background, _("##senatepp_clt_rating##"), _d->startPos + _d->offset, false );
  _d->font.draw( *_d->background, _("##senatepp_prsp_rating##"), _d->startPos + _d->offset * 2, false );
  _d->font.draw( *_d->background, _("##senatepp_peace_rating##"), _d->startPos + _d->offset * 3, false );
  _d->font.draw( *_d->background, _("##senatepp_favour_rating##"), _d->startPos + _d->offset * 4, false );
}

void SenatePopupInfo::draw(gfx::Engine& painter )
{
  Point cursorPos = environment()->getCursorPos();

  Tile* tile = _d->cityRenderer->camera()->at( cursorPos, false );

  if( tile && tile->overlay().isValid() )
  {
    SenatePtr senate = ptr_cast<Senate>( tile->overlay() );

    if( senate.isValid() )
    {
      if( DateTime::elapsedTime() - _d->lastUpdateTime > 2000 )
      {
        _d->updateRatings( senate );
      }

      painter.draw( *_d->background, cursorPos );     
    }
  }
}

}//end namespace gui
