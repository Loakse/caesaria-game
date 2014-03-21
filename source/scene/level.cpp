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
// Copyright 2012-2013 Dalerank, dalerankn8@gmail.com

#include "level.hpp"

#include <algorithm>

#include "gfx/engine.hpp"
#include "city/win_targets.hpp"
#include "core/exception.hpp"
#include "gui/rightpanel.hpp"
#include "game/resourcegroup.hpp"
#include "gui/environment.hpp"
#include "gui/topmenu.hpp"
#include "gui/menu.hpp"
#include "core/event.hpp"
#include "game/infoboxmanager.hpp"
#include "objects/objects_factory.hpp"
#include "gfx/renderermode.hpp"
#include "gui/message_stack_widget.hpp"
#include "core/time.hpp"
#include "core/stringhelper.hpp"
#include "gui/empiremap_window.hpp"
#include "gui/save_dialog.hpp"
#include "gui/advisors_window.hpp"
#include "game/alarm_event_holder.hpp"
#include "gfx/city_renderer.hpp"
#include "game/game.hpp"
#include "gui/senate_popup_info.hpp"
#include "city/funds.hpp"
#include "game/gamedate.hpp"
#include "world/empire.hpp"
#include "game/settings.hpp"
#include "gui/mission_target_window.hpp"
#include "gui/label.hpp"
#include "core/gettext.hpp"
#include "gui/minimap_window.hpp"
#include "gui/window_gamespeed_options.hpp"
#include "events/setvideooptions.hpp"
#include "core/logger.hpp"
#include "walker/enemysoldier.hpp"
#include "game/patrolpointeventhandler.hpp"
#include "city/city.hpp"
#include "gfx/tilemap_camera.hpp"
#include "game/ambientsound.hpp"
#include "gui/win_mission_window.hpp"
#include "events/showempiremapwindow.hpp"
#include "events/showadvisorwindow.hpp"
#include "gui/sound_options_window.hpp"
#include "sound/engine.hpp"

using namespace gui;
using namespace constants;

namespace scene
{

class Level::Impl
{
public:
  typedef std::vector< EventHandlerPtr > EventHandlers;

  EventHandlers eventHandlers;
  gui::MenuRigthPanel* rightPanel;
  gui::TopMenu* topMenu;
  gui::Menu* menu;
  GfxEngine* engine;
  gui::ExtentMenu* extMenu;
  CityRenderer renderer;
  Game* game; // current game
  AlarmEventHolder alarmsHolder;
  DateTime lastDate;
  std::string mapToLoad;
  bool isPaused;

  int result;

  void showSaveDialog();
  void showEmpireMapWindow();
  void showAdvisorsWindow(const advisor::Type advType );
  void showAdvisorsWindow();
  void showMissionTaretsWindow();
  void showTradeAdvisorWindow();
  void resolveCreateConstruction( int type );
  void resolveSelectLayer( int type );
  void resolveRemoveTool();
  void makeScreenShot();
  void setVideoOptions();
  void showGameSpeedOptionsDialog();
  void resolveWarningMessage( std::string );
  void saveCameraPos(Point p);
  void showSoundOptionsWindow();
  void makeEnemy();
  void makeFastSave();
  vfs::Path getFastSaveName();
};

Level::Level(Game& game , GfxEngine& engine ) : _d( new Impl )
{
  _d->topMenu = NULL;
  _d->game = &game;
  _d->engine = &engine;
  _d->isPaused = false;
}

Level::~Level() {}

void Level::initialize()
{
  PlayerCityPtr city = _d->game->getCity();
  _d->renderer.initialize( city, _d->engine );
  _d->game->gui()->clear();

  const int topMenuHeight = 23;
  const Picture& rPanelPic = Picture::load( ResourceGroup::panelBackground, 14 );

  GfxEngine& engine = GfxEngine::instance();
  gui::GuiEnv& gui = *_d->game->gui();

  installEventHandler( PatrolPointEventHandler::create( *_d->game, _d->renderer ) );

  Rect rPanelRect( engine.getScreenWidth() - rPanelPic.width(), topMenuHeight,
                   engine.getScreenWidth(), engine.getScreenHeight() );

  _d->rightPanel = MenuRigthPanel::create( gui.rootWidget(), rPanelRect, rPanelPic);

  _d->topMenu = new TopMenu( gui.rootWidget(), topMenuHeight );
  _d->topMenu->setPopulation( _d->game->getCity()->getPopulation() );
  _d->topMenu->setFunds( _d->game->getCity()->getFunds().getValue() );

  _d->menu = Menu::create( gui.rootWidget(), -1, city );
  _d->menu->setPosition( Point( engine.getScreenWidth() - _d->menu->width() - _d->rightPanel->width(),
                                 _d->topMenu->height() ) );

  _d->extMenu = ExtentMenu::create( gui.rootWidget(), -1, city );
  _d->extMenu->setPosition( Point( engine.getScreenWidth() - _d->extMenu->width() - _d->rightPanel->width(),
                                     _d->topMenu->height() ) );

  Minimap* mmap = new Minimap( _d->extMenu, Rect( 8, 35, 8 + 144, 35 + 110 ),
                               city->getTilemap(),
                               city->getClimate() );

  WindowMessageStack::create( gui.rootWidget() );

  _d->rightPanel->bringToFront();
  _d->renderer.camera().setViewport( engine.getScreenSize() );

  new SenatePopupInfo( gui.rootWidget(), _d->renderer );

  _d->game->getCity()->addService( city::AmbientSound::create( _d->game->getCity(), _d->renderer.camera() ) );

  //connect elements
  CONNECT( _d->topMenu, onSave(), _d.data(), Impl::showSaveDialog );
  CONNECT( _d->topMenu, onExit(), this, Level::_resolveExitGame );
  CONNECT( _d->topMenu, onEnd(), this, Level::_resolveEndGame );
  CONNECT( _d->topMenu, onRequestAdvisor(), _d.data(), Impl::showAdvisorsWindow );
  CONNECT( _d->topMenu, onShowVideoOptions(), _d.data(), Impl::setVideoOptions );
  CONNECT( _d->topMenu, onShowSoundOptions(), _d.data(), Impl::showSoundOptionsWindow );
  CONNECT( _d->topMenu, onShowGameSpeedOptions(), _d.data(), Impl::showGameSpeedOptionsDialog );

  CONNECT( _d->menu, onCreateConstruction(), _d.data(), Impl::resolveCreateConstruction );
  CONNECT( _d->menu, onRemoveTool(), _d.data(), Impl::resolveRemoveTool );
  CONNECT( _d->menu, onMaximize(), _d->extMenu, ExtentMenu::maximize );

  CONNECT( _d->extMenu, onCreateConstruction(), _d.data(), Impl::resolveCreateConstruction );
  CONNECT( _d->extMenu, onRemoveTool(), _d.data(), Impl::resolveRemoveTool );

  CONNECT( city, onPopulationChanged(), _d->topMenu, TopMenu::setPopulation );
  CONNECT( city, onFundsChanged(), _d->topMenu, TopMenu::setFunds );
  CONNECT( city, onWarningMessage(), _d.data(), Impl::resolveWarningMessage );

  CONNECT( _d->extMenu, onSelectOverlayType(), _d.data(), Impl::resolveSelectLayer );
  CONNECT( _d->extMenu, onEmpireMapShow(), _d.data(), Impl::showEmpireMapWindow );
  CONNECT( _d->extMenu, onAdvisorsWindowShow(), _d.data(), Impl::showAdvisorsWindow );
  CONNECT( _d->extMenu, onMissionTargetsWindowShow(), _d.data(), Impl::showMissionTaretsWindow );

  CONNECT( city, onDisasterEvent(), &_d->alarmsHolder, AlarmEventHolder::add );
  CONNECT( _d->extMenu, onSwitchAlarm(), &_d->alarmsHolder, AlarmEventHolder::next );
  CONNECT( &_d->alarmsHolder, onMoveToAlarm(), &_d->renderer.camera(), TilemapCamera::setCenter );
  CONNECT( &_d->alarmsHolder, onAlarmChange(), _d->extMenu, ExtentMenu::setAlarmEnabled );

  CONNECT( &_d->renderer.camera(), onPositionChanged(), mmap, Minimap::setCenter );
  CONNECT( &_d->renderer.camera(), onPositionChanged(), _d.data(), Impl::saveCameraPos );
  CONNECT( mmap, onCenterChange(), &_d->renderer.camera(), TilemapCamera::setCenter );

  _d->showMissionTaretsWindow();
  _d->renderer.camera().setCenter( city->getCameraPos() );
}

std::string Level::nextFilename() const{  return _d->mapToLoad;}

void Level::Impl::showSaveDialog()
{
  vfs::Directory saveDir = GameSettings::get( GameSettings::savedir ).toString();
  std::string defaultExt = GameSettings::get( GameSettings::saveExt ).toString();

  if( !saveDir.exist() )
  {
    vfs::Directory::createByPath( saveDir );
  }

  SaveDialog* dialog = new SaveDialog( game->gui()->rootWidget(), saveDir, defaultExt, -1 );
  CONNECT( dialog, onFileSelected(), game, Game::save );
}

void Level::Impl::setVideoOptions()
{
  events::GameEventPtr event = events::SetVideoSettings::create();
  event->dispatch();
}

void Level::Impl::showGameSpeedOptionsDialog()
{
  GameSpeedOptionsWindow* dialog = new GameSpeedOptionsWindow( game->gui()->rootWidget(),
                                                               game->getTimeMultiplier(),
                                                               0 );

  CONNECT( dialog, onGameSpeedChange(), game, Game::setTimeMultiplier );
  CONNECT( dialog, onScrollSpeedChange(), &renderer.camera(), TilemapCamera::setScrollSpeed );
}

void Level::Impl::resolveWarningMessage(std::string text )
{
  events::GameEventPtr e = events::WarningMessageEvent::create( text );
  e->dispatch();
}

void Level::Impl::saveCameraPos(Point p)
{
  Tile* tile = renderer.camera().at( Point( engine->getScreenWidth()/2, engine->getScreenHeight()/2 ), false );

  if( tile )
  {
    game->getCity()->setCameraPos( tile->pos() );
  }
}

void Level::Impl::showSoundOptionsWindow()
{
  audio::Engine& e = audio::Engine::instance();
  SoundOptionsWindow* dialog = new SoundOptionsWindow( game->gui()->rootWidget(),
                                                       e.volume( audio::gameSound ),
                                                       e.volume( audio::ambientSound ),
                                                       e.volume( audio::themeSound ) );

  CONNECT( dialog, onSoundChange(), &e, audio::Engine::setVolume );
}

void Level::Impl::makeEnemy()
{
  EnemySoldierPtr enemy = EnemySoldier::create( game->getCity(),
                                                constants::walker::britonSoldier );
  enemy->send2City( game->getCity()->getBorderInfo().roadEntry );
}

void Level::Impl::makeFastSave() {  game->save( getFastSaveName().toString() ); }

void Level::_resolveFastLoad()
{
  _d->mapToLoad = _d->getFastSaveName().toString();
  _resolveSwitchMap();
}

vfs::Path Level::Impl::getFastSaveName()
{
  vfs::Path filename = game->getCity()->getName()
                       + GameSettings::get( GameSettings::fastsavePostfix ).toString()
                       + GameSettings::get( GameSettings::saveExt ).toString();

  vfs::Directory saveDir = GameSettings::get( GameSettings::savedir ).toString();

  return saveDir/filename;
}

void Level::_resolveSwitchMap()
{
  bool isNextBriefing = vfs::Path( _d->mapToLoad ).isExtension( ".briefing" );
  _d->result = isNextBriefing ? Level::loadBriefing : Level::loadGame;
  stop();
}

void Level::Impl::showEmpireMapWindow()
{
  events::GameEventPtr e;
  if( game->getEmpire()->isAvailable() ) { e = events::ShowEmpireMapWindow::create( true ); }
  else {  e = events::WarningMessageEvent::create( "##not_available##" ); }

  if( e.isValid() ) e->dispatch();
}

void Level::draw()
{ 
  _d->renderer.render();

  _d->game->gui()->beforeDraw();
  _d->game->gui()->draw();
}

void Level::animate( unsigned int time ) {  _d->renderer.animate( time ); }

void Level::afterFrame()
{
  if( _d->lastDate.month() != GameDate::current().month() )
  {
    _d->lastDate = GameDate::current();
    PlayerCityPtr city = _d->game->getCity();
    const CityWinTargets& wt = city->getWinTargets();

    int culture = city->getCulture();
    int prosperity = city->getProsperity();
    int favour = city->getFavour();
    int peace = city->getFavour();
    int population = city->getPopulation();
    bool success = wt.isSuccess( culture, prosperity, favour, peace, population );

    if( success )
    {
      std::string newTitle = wt.getNewTitle();

      gui::WinMissionWindow* wnd = new gui::WinMissionWindow( _d->game->gui()->rootWidget(), newTitle, false );

      _d->mapToLoad = wt.getNextMission();

      CONNECT( wnd, onAcceptAssign(), this, Level::_resolveSwitchMap );
    }
  }
}

void Level::handleEvent( NEvent& event )
{
  //After MouseDown events are send to the same target till MouseUp
  GuiEnv& gui = *_d->game->gui();

  static enum _MouseEventTarget
  {
    _MET_NONE,
    _MET_GUI,
    _MET_TILES
  } _mouseEventTarget = _MET_NONE;

  if( event.EventType == sEventKeyboard )
  {
    switch( event.keyboard.key )
    {
    case KEY_MINUS:
    case KEY_PLUS:
    case KEY_SUBTRACT:
    case KEY_ADD:
    {
      events::GameEventPtr e = events::ChangeSpeed::create( (event.keyboard.key == KEY_MINUS ||
                                                              event.keyboard.key == KEY_SUBTRACT)
                                                            ? -10 : +10 );
      e->dispatch();
    }
    break;

    case KEY_KEY_P:
    {
      if( event.keyboard.pressed )
        break;

      _d->isPaused = !_d->isPaused;

      events::GameEventPtr e = events::Pause::create( _d->isPaused
                                                        ? events::Pause::pause
                                                        : events::Pause::play );
      e->dispatch();      
    }
    break;

    case KEY_F10:	_d->makeScreenShot(); break;

		case KEY_F5: _d->makeFastSave(); break;
		case KEY_F9: _resolveFastLoad(); break;

		case KEY_F11:
			if( event.keyboard.pressed )
				_d->makeEnemy();
		break;

    default:
    break;
    }
  }

  for( Impl::EventHandlers::iterator it=_d->eventHandlers.begin(); it != _d->eventHandlers.end(); )
  {
    (*it)->handleEvent( event );
    if( (*it)->finished() ) { it = _d->eventHandlers.erase( it ); }
    else{ it++; }
  }

  bool eventResolved = false;
  if (event.EventType == sEventMouse)
  {
    if( event.mouse.type == mouseRbtnPressed || event.mouse.type == mouseLbtnPressed )
    {
      eventResolved = gui.handleEvent( event );
      if (eventResolved)
      {
        _mouseEventTarget = _MET_GUI;
      }
      else // eventresolved
      {
        _mouseEventTarget = _MET_TILES;
        _d->renderer.handleEvent( event );
      }
      return;
    }

    switch(_mouseEventTarget)
    {
    case _MET_GUI:
      gui.handleEvent( event );
    break;

    case _MET_TILES:
      _d->renderer.handleEvent( event );
    break;

    default:
       if (!gui.handleEvent( event ))
        _d->renderer.handleEvent( event );
    break;
    }

    if( event.mouse.type == mouseRbtnRelease || event.mouse.type == mouseLbtnRelease )
    {
      _mouseEventTarget = _MET_NONE;
    }
  }
  else
  {
    eventResolved = gui.handleEvent( event );
   
    if( !eventResolved )
    {
      _d->renderer.handleEvent( event );
    }
  }
}

void Level::Impl::makeScreenShot()
{
  DateTime time = DateTime::getCurrenTime();

  std::string filename = StringHelper::format( 0xff, "oc3_[%04d_%02d_%02d_%02d_%02d_%02d].png", 
                                               time.year(), time.month(), time.day(),
                                               time.hour(), time.minutes(), time.seconds() );
  Logger::warning( "creating screenshot %s", filename.c_str() );

  GfxEngine::instance().createScreenshot( filename );
}

int Level::getResult() const {  return _d->result; }
bool Level::installEventHandler(EventHandlerPtr handler) {  _d->eventHandlers.push_back( handler ); return true; }
void Level::Impl::resolveCreateConstruction( int type ){  renderer.setMode( BuildMode::create( TileOverlay::Type( type ) ) );}
void Level::Impl::resolveRemoveTool(){  renderer.setMode( DestroyMode::create() );}
void Level::Impl::resolveSelectLayer( int type ){  renderer.setMode( LayerMode::create( type ) );}
void Level::Impl::showAdvisorsWindow(){  showAdvisorsWindow( advisor::employers ); }
void Level::Impl::showTradeAdvisorWindow(){  showAdvisorsWindow( advisor::trading ); }
void Level::Impl::showMissionTaretsWindow(){  MissionTargetsWindow::create( game->gui()->rootWidget(), game->getCity() ); }
void Level::_resolveEndGame(){  _d->result = Level::mainMenu;  stop();}
void Level::_resolveExitGame(){  _d->result = Level::quitGame;  stop();}

void Level::Impl::showAdvisorsWindow( const advisor::Type advType )
{  
  events::GameEventPtr e = events::ShowAdvisorWindow::create( true, advType );
  e->dispatch();
}

void Level::setCameraPos(TilePos pos)
{
  _d->renderer.camera().setCenter( pos );
}


}//end namespace scene