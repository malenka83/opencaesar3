// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _OPENCAESAR3_SCENARIO_EVENT_H_INCLUDE_
#define _OPENCAESAR3_SCENARIO_EVENT_H_INCLUDE_

#include "core/referencecounted.hpp"
#include "core/smartptr.hpp"
#include "core/position.hpp"
#include "building/building.hpp"
#include "core/predefinitions.hpp"

class Game;

namespace events
{

class GameEvent : public ReferenceCounted
{
public:
  virtual void exec( Game& game ) = 0;
  virtual void dispatch();

protected:
  GameEvent() {}
};

class DisasterEvent : public GameEvent
{
public:
  typedef enum
  {
    fire, collapse, plague, count
  } Type;
  static GameEventPtr create( const TilePos&, Type type );

  virtual void exec( Game& game );

private:
  TilePos _pos;
  Type _type;
};

class BuildEvent : public GameEvent
{
public:
  static GameEventPtr create( const TilePos&, TileOverlay::Type type );
  static GameEventPtr create( const TilePos&, TileOverlayPtr overlay );

  virtual void exec( Game& game );
private:
  TilePos _pos;
  TileOverlayPtr _overlay;
};

class ClearLandEvent : public GameEvent
{
public:
  static GameEventPtr create( const TilePos& );
  virtual void exec( Game& game );
private:
  TilePos _pos;
};

class ShowInfoboxEvent : public GameEvent
{
public:
  static GameEventPtr create( const std::string& title, const std::string& text );
  virtual void exec( Game& game );
private:
  std::string _title, _text;
};

class WarningMessageEvent : public GameEvent
{
public:
  static GameEventPtr create( const std::string& text );
  virtual void exec( Game& game );
private:
  std::string _text;
};

class ShowEmpireMapWindow : public GameEvent
{
public:
  static GameEventPtr create( bool show );
  virtual void exec( Game& game );

private:
  bool _show;
};

class ShowAdvisorWindow : public GameEvent
{
public:
  static GameEventPtr create( bool show, int advisor );
  virtual void exec( Game& game );

private:
  bool _show;
  int _advisor;
};

class Pause : public GameEvent
{
public:
  typedef enum { toggle, pause, play, hidepause, hideplay } Mode;
  static GameEventPtr create( Mode mode );
  virtual void exec( Game& game );

private:
  Mode _mode;
};

class ChangeSpeed : public GameEvent
{
public:
  static GameEventPtr create( int value );
  virtual void exec( Game& game );

private:
  int _value;
};

class FundIssueEvent : public GameEvent
{
public:
  static GameEventPtr create( int type, int value );
  static GameEventPtr import( Good::Type good, int qty );
  static GameEventPtr exportg( Good::Type good, int qty );
  virtual void exec( Game& game );
private:
  int _type;
  int _value;
  Good::Type _gtype;
  int _qty;
};

} //end namespace events
#endif //_OPENCAESAR3_CITY_EVENT_H_INCLUDE_
