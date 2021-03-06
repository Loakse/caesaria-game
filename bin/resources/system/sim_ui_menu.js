function OnChangeSessionUndoState(enable) {
  sim.ui.menu.enableUndo(enable);
}

function OnChangeSessionAlarmState(enable) {
  sim.ui.menu.enableAlarm(enable);
}

function OnRendererLayerChange(layerName) {
  sim.ui.menu.changeRendererLayer(layerName);
}

function OnChangeBuildingOptions() {
  sim.ui.menu.changeBuildingOptions();
}

sim.ui.menu.simConfig = {
  housing : { pos: {x:13,y:277}, image: { rc:"paneling", index:123 }, object:"house",
               miniature: { rc:"panelwindows", index:1 }, shortmenuIndex:0,
               pushButton: true, submenu: false, sound:"housing" },

  clearLand : { pos: {x:63,y:277}, image : { rc:"paneling", index:131 }, object:"removeTool",
                miniature: { rc:"panelwindows", index:12 }, shortmenuIndex:1,
                pushButton : true, submenu: false, sound: "clear_land" },

  road : { pos : {x:113,y:277}, image : { rc:"paneling", index:135 }, object: "road",
           miniature : { rc:"panelwindows", index:11 }, shortmenuIndex:2,
           pushButton : true, submenu: false, sound: "road" },

  water: { pos:{x:13,y:313}, image : { rc:"paneling", index:127 }, object:"water",
           miniature : { rc:"panelwindows", index:4 }, shortmenuIndex:3,
           pushButton : true, submenu: false, sound: "water", branch : "water"  },

  health: { pos:{x:63,y:313}, image : { rc:"paneling", index:163 }, object:"health",
            miniature : { rc:"panelwindows", index:6 },pushButton : true, shortmenuIndex:4,
            submenu: false, sound: "health", branch:"health"},

  religion: { pos:{x:113,y:313}, image : { rc:"paneling", index:151 }, object:"religion",
              miniature : { rc:"panelwindows", index:2 }, shortmenuIndex:5,
              pushButton : true, submenu: false, sound: "temples", branch:"religion"},

  education: { pos:{x:13,y:349}, image : { rc:"paneling", index:147 }, object:"education",
               miniature : { rc:"panelwindows", index:7 }, shortmenuIndex:6,
               pushButton : true, submenu: false, sound: "education", branch:"education"},

  entertainment : { pos: {x:63,y:349}, image : { rc:"paneling", index:143 }, object:"entertainment",
                    miniature : { rc:"panelwindows", index:5 }, shortmenuIndex:7,
                    pushButton : true, submenu: false, sound: "entertainment" , branch:"entertainment"},

  govt : { pos:{x:113,y:349}, image : { rc:"paneling", index:139 }, object:"administration",
           miniature : { rc:"panelwindows", index:3 }, shortmenuIndex:8,
           pushButton : true, submenu: false, sound: "administration", branch:"administration" },

  engineering: { pos:{x:13,y:385}, image : { rc:"paneling", index:167 }, object:"engineering",
           miniature : { rc:"panelwindows", index:8 }, shortmenuIndex:9,
           pushButton : true, submenu: false, sound: "engineering", branch:"engineering" },

  security : { pos:{x:63,y:385}, image : { rc:"paneling", index:159 }, object:"security",
           miniature : { rc:"panelwindows", index:9 }, shortmenuIndex:10,
           pushButton : true, submenu: false, sound: "security", branch:"security" },

  commerce : { pos:{x:113,y:385}, image: { rc:"paneling", index:155 }, object:"commerce",
           miniature : { rc:"panelwindows", index:10 }, shortmenuIndex:11,
           pushButton : true, submenu: false, sound: "commerce", branch:"commerce" },

  messages : { pos:{x:63, y:421}, image: { rc:"paneling", index:115 }, object:"message",
           miniature : { rc:"panelwindows", index:12 }, enabled : false, name : "#buttonMessages",
           pushButton : true, submenu: false, sound: "message", height : 22 },

  disaster: { pos:{x:113, y:421}, image: { rc:"paneling", index:119 }, object:"disaster",
           miniature : { rc:"panelwindows", index:12 }, enabled : false, name : "#buttonDisaster",
           pushButton : true, submenu: false, sound: "troubles", height : 22 },

  undo : { pos:{x:13,y:421}, image: { rc:"paneling", index:171 }, object:"cancel",
           miniature : { rc:"panelwindows", index:12 }, enabled : false,
           pushButton : true, submenu: false, sound: "cancel", height : 22},

  minimize : { pos:{x:127,y:5}, image: { rc:"paneling", index:97 }, object:"maximize",
               miniature : { rc:"panelwindows", index:12 },
               pushButton : false, submenu: false, sound: "hide_bigpanel"},

  senate : { pos:{x:7,y:155}, image: { rc:"paneling", index:79 }, object:"senate",
             miniature : { rc:"panelwindows", index:12 },
             pushButton : false, submenu: false, sound: "hide_bigpanel"},

  empire : { pos:{x:84,y:155}, image: { rc:"paneling", index:82 }, object:"empire",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "empire" },

  mission : { pos:{x:7,y:184}, image: { rc:"paneling", index:85 }, object:"senate",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "senate" },

  reorient_map_to_north : { pos:{x:46,y:184}, image: { rc:"paneling", index:88 }, object:"reorient_map_to_north",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "reorient_map_to_north" },

  rotate_map_counter_clockwise : { pos:{x:84,y:184}, image: { rc:"paneling", index:91 }, object:"rotate_map_counter_clockwise",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "rotate_map_counter_clockwise" },

  rotate_map_clockwise : { pos:{x:123,y:184}, image: { rc:"paneling", index:94 }, object:"rotate_map_clockwise",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "rotate_map_clockwise" },
}

sim.ui.menu.buildConfig = {
  terrain : { pos: {x:13,y:277}, image: { rc:"paneling", index:183 }, object:"terrain",
               miniature: { rc:"panelwindows", index:12 },
               pushButton: true, submenu: false, sound:"terrain" },

  tree : { pos: {x:63,y:277}, image : { rc:"paneling", index:186 }, object:"tree",
                miniature: { rc:"panelwindows", index:12 },
                pushButton : true, submenu: false, sound: "tree" },

  water : { pos : {x:113,y:277}, image : { rc:"paneling", index:189 }, object: "water",
           miniature : { rc:"panelwindows", index:12 },
           pushButton : true, submenu: false, sound: "water" },

  rock : { pos:{x:13,y:313}, image : { rc:"paneling", index:198 }, object:"rock",
            miniature : { rc:"panelwindows", index:12 },pushButton : true,
            submenu: false, sound: "rock" },

  meadow: { pos:{x:63,y:313}, image : { rc:"paneling", index:201 }, object:"meadow",
              miniature : { rc:"panelwindows", index:2 },
              pushButton : true, submenu: false, sound: "meadow" },

  plateau: { pos:{x:113,y:313}, image : { rc:"paneling", index:204 }, object:"plateau",
               miniature : { rc:"panelwindows", index:7 },
               pushButton : true, submenu: false, sound: "plateau" },

  rift : { pos: {x:13,y:349}, image : { rc:"paneling", index:192 }, object:"rift",
                    miniature : { rc:"panelwindows", index:5 },
                    pushButton : true, submenu: false, sound: "rift" },

  river : { pos:{x:63,y:349}, image : { rc:"paneling", index:189 }, object:"river",
           miniature : { rc:"panelwindows", index:3 },
           pushButton : true, submenu: false, sound: "river" },

  native_hut: { pos:{x:113,y:349}, image : { rc:"paneling", index:210 }, object:"native_hut",
           miniature : { rc:"panelwindows", index:8 },
           pushButton : true, submenu: false, sound: "native_hut" },

  road : { pos:{x:13,y:385}, image : { rc:"paneling", index:213 }, object:"road",
           miniature : { rc:"panelwindows", index:9 },
           pushButton : true, submenu: false, sound: "road" },

  waymark : { pos:{x:63,y:385}, image: { rc:"paneling", index:216 }, object:"waymark",
           miniature : { rc:"panelwindows", index:10 },
           pushButton : true, submenu: false, sound: "waymark" },

  attackTrigger : { pos:{x:113, y:385}, image: { rc:"paneling", index:225 }, object:"attackTrigger",
           miniature : { rc:"panelwindows", index:12 },
           pushButton : true, submenu: false, sound: "attackTrigger",
           ingame : true, ineditor : false, height : 22 },

  undo : { pos:{x:13,y:421}, image: { rc:"paneling", index:171 }, object:"cancel",
           miniature : { rc:"panelwindows", index:12 },
           pushButton : true, submenu: false, sound: "cancel",
           ingame : true, ineditor : false, height : 22 },

  minimize : { pos:{x:127,y:5}, image: { rc:"paneling", index:97 }, object:"maximize",
               miniature : { rc:"panelwindows", index:12 },
               pushButton : false, submenu: false, sound: "hide_bigpanel",
               ingame : true, ineditor : false,},

  senate : { pos:{x:7,y:155}, image: { rc:"paneling", index:79 }, object:"senate",
             miniature : { rc:"panelwindows", index:12 },
             pushButton : false, submenu: false, sound: "hide_bigpanel", enabled : false},

  empire : { pos:{x:84,y:155}, image: { rc:"paneling", index:82 }, object:"empire",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "empire", enabled : false },

  mission : { pos:{x:7,y:184}, image: { rc:"paneling", index:85 }, object:"senate",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "senate", enabled : false },

  reorient_map_to_north : { pos:{x:46,y:184}, image: { rc:"paneling", index:88 }, object:"reorient_map_to_north",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "reorient_map_to_north" },

  rotate_map_counter_clockwise : { pos:{x:84,y:184}, image: { rc:"paneling", index:91 }, object:"rotate_map_counter_clockwise",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "rotate_map_counter_clockwise" },

  rotate_map_clockwise : { pos:{x:123,y:184}, image: { rc:"paneling", index:94 }, object:"rotate_map_clockwise",
            miniature : { rc:"panelwindows", index:12 },
            pushButton : false, submenu: false, sound: "rotate_map_clockwise" },
}

sim.ui.menu.funcs = [];

sim.ui.menu.rightSide = engine.getOption("rightMenu");

sim.ui.menu.changeBuildingOptions = function() {
  for (var i in sim.ui.menu.simConfig) {
    var config = sim.ui.menu.simConfig[i];
    var button = sim.ui.menu.extmenu.buttons[i];
    engine.log("check for " + i)
    if (config.branch && button) {
      var avail = sim.ui.buildmenu.isBranchAvailable(config.branch);
      engine.log("set avail for " + config.branch)
      button.enabled = avail;
    }
  }
}

sim.ui.menu.clean = function() {
  engine.log("sim.ui.menu.clean");
  sim.ui.menu.extmenu = {}
}

sim.ui.menu.enableAlarm = function(enable) {
  if (enable) {
    g_session.playAudio("extm_alarm_00001", 100, g_config.audio.effects);
  }

  var btn = g_ui.find("#buttonDisaster");
  btn.enabled = enable;
}

sim.ui.menu.simConfig.disaster.func = function() { g_session.setOption( "nextAlarm", true ); }
sim.ui.menu.simConfig.messages.func = function() { sim.ui.dialogs.scribesmessages.show(); }
sim.ui.menu.enableUndo = function(enable) { sim.ui.menu.extmenu.buttons.undo.enabled = enable; }

sim.ui.menu.updateScribeStatus = function() {
  if(sim.ui.menu.extmenu.scribes) {
    var haveUnreadMessages = sim.ui.menu.extmenu.scribes.haveUnreadMessage();
    var messagesNumber = sim.ui.menu.extmenu.scribes.getMessagesNumber();

    g_ui.find("#buttonMessages").enabled = messagesNumber > 0;
    g_ui.find("#scribesBlinker").setActive(haveUnreadMessages);
  }
}

sim.ui.menu.simConfig.housing.func = function() {
  sim.ui.buildmenu.hide();
  sim.ui.menu.extmenu.miniature.picture = sim.ui.menu.simConfig.housing.miniature;
  g_session.setOption("buildMode", "house");
}

sim.ui.menu.buildEditorObject = function(obj) {
  sim.ui.buildmenu.hide();
  sim.ui.menu.extmenu.miniature.picture = sim.ui.menu.buildConfig.terrain.miniature;
  g_session.setOption("editorMode", obj);
}

sim.ui.menu.buildConfig.terrain.func = function() { sim.ui.menu.buildEditorObject("terrain"); }
sim.ui.menu.buildConfig.tree.func = function() { sim.ui.menu.buildEditorObject("tree"); }
sim.ui.menu.buildConfig.water.func = function() { sim.ui.menu.buildEditorObject("water"); }
sim.ui.menu.buildConfig.rock.func = function() { sim.ui.menu.buildEditorObject("rock"); }
sim.ui.menu.buildConfig.meadow.func = function() { sim.ui.menu.buildEditorObject("meadow"); }
sim.ui.menu.buildConfig.plateau.func = function() { sim.ui.menu.buildEditorObject("plateau"); }
sim.ui.menu.buildConfig.rift.func = function() { sim.ui.menu.buildEditorObject("rift"); }
sim.ui.menu.buildConfig.river.func = function() { sim.ui.menu.buildEditorObject("river"); }
sim.ui.menu.buildConfig.native_hut.func = function() { sim.ui.menu.buildEditorObject("native_hut"); }
sim.ui.menu.buildConfig.attackTrigger.func = function() { sim.ui.menu.buildEditorObject("attackTrigger"); }

sim.ui.menu.simConfig.undo.func = function() {
  g_session.setOption("undo", true);
}

sim.ui.menu.simConfig.clearLand.func = function() {
  sim.ui.buildmenu.hide();
  sim.ui.menu.extmenu.miniature.picture = sim.ui.menu.simConfig.clearLand.miniature;
  g_session.setOption( "removeTool", true );
}

sim.ui.menu.simConfig.road.func = function() {
  sim.ui.buildmenu.hide();
  sim.ui.menu.extmenu.miniature.picture = sim.ui.menu.simConfig.road.miniature;
  g_session.setOption( "buildMode", "road");
}

sim.ui.menu.showbuildmenu = function(o, x, y) {
  g_session.playAudio(o.sound, 100, g_config.audio.infobox);
  sim.ui.menu.extmenu.miniature.picture = o.miniature;
  sim.ui.buildmenu.show(o.object, x, y);
}

sim.ui.menu.simConfig.minimize.func = function() {
  var menu = sim.ui.menu.extmenu;

  sim.ui.buildmenu.hide();
  var stopPos = { x:menu.x + menu.w * (sim.ui.menu.rightSide ? 1 : -1 ), y:menu.y};
  var animator = g_ui.addPosAnimator(menu, stopPos, 1000, sim.ui.shortmenu.maximize);
  animator.setFlag("showParent", false);

  g_session.playAudio("panel_00003", 100, g_config.audio.infobox);
}

sim.ui.menu.maximize = function() {
  var menu = sim.ui.menu.extmenu;

  sim.ui.buildmenu.hide();
  menu.display = true;
  var stopPos = { x:menu.x - menu.w * (sim.ui.menu.rightSide ? 1 : -1), y:menu.y};
  var animator = g_ui.addPosAnimator(menu, stopPos, 1000);
  animator.setFlag("showParent", true);

  g_session.playAudio( "panel_00003", 100, g_config.audio.infobox );
}

sim.ui.menu.simConfig.senate.func = function() { g_session.setOption( "advisor", g_config.advisor.employers ); }
sim.ui.menu.simConfig.empire.func = function() { g_session.setOption( "showEmpireMap", true); }
sim.ui.menu.simConfig.mission.func = function() { sim.ui.dialogs.showMissionTargets(); }

sim.ui.menu.simConfig.reorient_map_to_north.func = function() {  }

sim.ui.menu.simConfig.rotate_map_counter_clockwise.func = function() {
  g_session.setOption("rotateLeft", true);
  sim.ui.menu.extmenu.minimap.update();
}

sim.ui.menu.simConfig.rotate_map_clockwise.func = function() {
  g_session.setOption("rotateRight", true);
  sim.ui.menu.extmenu.minimap.update();
}

sim.ui.menu.changeRendererLayer = function(layerName) {
  sim.ui.menu.extmenu.overlays.text = _u(layerName);
}

sim.ui.menu.initialize = function() {
  if (g_city.getOption("constructorMode")) {
    sim.ui.menu.config = sim.ui.menu.buildConfig;
  } else {
    sim.ui.menu.config = sim.ui.menu.simConfig;
  }

  var menu = new Widget(0);
  menu.name = "ExtentMenu";
  menu.buttons = [];

  var topmenu = g_ui.find("TopMenu");

  var rbody = g_render.picture("paneling", 14);

  var bgbody = g_render.picture("paneling", 17);
  var bgbottom = g_render.picture("paneling", 20);

  var resolution = g_session.resolution;

  menu.geometry = {x:resolution.w - bgbody.w - rbody.w, y:topmenu.h, w:bgbody.w, h:resolution.h};
  menu.imgBody = new Image(menu);
  menu.imgBody.picture = bgbody;
  menu.imgBody.mode = "image";

  var ty = menu.imgBody.h;
  while (ty < menu.h) {
    var img = new Image(menu);
    img.y = ty;
    img.picture = bgbottom;
    img.mode = "image";
    ty += bgbottom.h;
  }

  for (var i in sim.ui.menu.config) {
    var config = sim.ui.menu.config[i];

    engine.log(i);

    var btn = new TexturedButton(menu);
    btn.position = config.pos;
    btn.tooltip = _u("extm_" + config.object + "_tlp");

    btn.states = { rc:config.image.rc, normal:config.image.index, hover:config.image.index+1,
                   pressed:config.image.index+2, disabled:config.image.index+3 };
    btn.fitToImage();

    if (config.height)
      btn.h = config.height;

    if (config.name)
      btn.name = config.name;

    if (config.branch) {
      var avail = sim.ui.buildmenu.isBranchAvailable(config.branch);
      btn.enabled = avail;
    }

    (function(c, x, y){
      if (config.func) sim.ui.menu.funcs[i] = c.func;
      else sim.ui.menu.funcs[i] = function(){ sim.ui.menu.showbuildmenu(c, x, y); }
    })(config, menu.w, btn.screeny);

    btn.callback = sim.ui.menu.funcs[i];

    if (config.enabled != undefined)
      btn.enabled = config.enabled;

    menu.buttons[i] = btn;
  }

  var btnMessages = g_ui.find("#buttonMessages");
  if (btnMessages) {
    var blinker = new ImageBlinker(btnMessages);
    blinker.w = btnMessages.w;
    blinker.h = btnMessages.h;
    blinker.name = "#scribesBlinker";
    blinker.setImage(g_render.picture("paneling", 116));
    blinker.setActive(false);
    menu.scribes = g_city.scribes();
  }

  menu.minimap = new Minimap(menu);
  menu.minimap.geometry = { x:8, y:35, w:144, h:110 };
  menu.minimap.city = g_city;
  menu.minimap.center = g_session.camera.worldCenter;

  g_session.camera.onLocationChanged = function(p) { menu.minimap.tileCenter = p; }

  menu.minimap.onChangeZoom = function(delta) {
    engine.log(delta);
    g_session.camera.changeZoom(delta);
  }

  menu.minimap.onChangeCenter = function(tilepos) {
    engine.log("Move camera from minimap [i:" + tilepos.i + "  j:" + tilepos.j + "]");
    g_session.camera.setCenter(tilepos);
    menu.minimap.tileCenter = tilepos;
  }

  menu.miniature = new Image(menu);
  menu.miniature.geometry = { x:7, y:216, w:148, h:52 };
  menu.miniature.mode = "fit";
  menu.miniature.picture = { rc: "panelwindows", index:13 };

  menu.overlays = new Button(menu);
  menu.overlays.text = _u("ovrm_text");
  menu.overlays.style = "greyBorderLineFit";
  menu.overlays.geometry =  {x:4, y:1, w:119, h:28};
  menu.overlays.tooltip =  _u("select_city_layer");
  menu.overlays.callback = function() {
    sim.ui.overlaymenu.show("all", sim.ui.menu.extmenu.w,
                                   sim.ui.menu.extmenu.overlays.screeny);
  }

  sim.ui.menu.extmenu = menu;

  game.eventmgr.bindEvent(game.events.OnScribesStatusChanged, sim.ui.menu.updateScribeStatus);
  game.eventmgr.bindEvent(game.events.OnLevelDestroyed, sim.ui.menu.clean);
}

sim.ui.menu.reset = function() {
  if (sim.ui.menu.extmenu != null) {
    engine.log( "Found old main menu -> removed" );
    sim.ui.menu.extmenu.deleteLater();
    sim.ui.menu.extmenu = null;
    game.eventmgr.unbindEvent(game.events.OnScribesStatusChanged, sim.ui.menu.updateScribeStatus);
    game.eventmgr.unbindEvent(game.events.OnLevelDestroyed, sim.ui.menu.clean);

    sim.ui.menu.initialize();
  }
}

sim.ui.menu.setRightSide = function(right) {
  sim.ui.menu.rightSide = right;
  sim.ui.menu.reset();
}

sim.ui.menu.reset();
