#include <algorithm>
#include <cmath>
#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/sound.hpp>
#include <vector>
#include <random>

using namespace stemaj;

Scene::Scene(const std::string& scenery) : Scenery(scenery), _render(std::make_unique<SceneRender>())
{
  _fader = Fader(2.0f);
  LoadLevelData();

  // Hausdach
  auto cp = _world.GetCenterPoint(3001);
  std::vector<PT<float>> roofPts = {
    { 0.0f, -_roof_height }, 
    {-_roof_height/2.f, _roof_height/2.f}, 
    {_roof_height/2.f, _roof_height/2.f} };
  _userdata.push_back(3002);
  _world.SpawnPolygon(3002, 
    {cp.x, cp.y - _roof_height}, roofPts,
    0.0f, 2, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, &_userdata.back());

  _cl_house = std::make_shared<PhysicalWorld::ContactChecker>(3001);
  _world.SetListener(_cl_house.get());
  // _cl_roof = std::make_shared<PhysicalWorld::ContactChecker>(3002);
  // _world.SetListener(_cl_roof.get());
}

Scene::~Scene()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> Scene::Update(
  const Input& input, float fElapsedTime)
{
  if (!_heliSound)
  {
    SO.StartEffect("assets/mp3/helicopter.mp3", 1.0f);
    _heliSound = true;
  }

  std::random_device rd;
	std::mt19937 gen(rd());
  
  if (_spawnNewHeli)
  {
    Helicopter heli;
    heli.Pos = {0.0f,50.0f};
    Helis.push_back(heli);

    // TODO Coord for next block
    std::uniform_real_distribution<float> dist_neg{
      _wall_dist_neg.x,_wall_dist_neg.y};
    std::uniform_real_distribution<float> dist_pos{
      _wall_dist_pos.x,_wall_dist_pos.y};

    LocalPtsNextBlockSpawn.clear();
    LocalPtsNextBlockSpawn.push_back({dist_neg(gen), dist_neg(gen)});
    LocalPtsNextBlockSpawn.push_back({dist_neg(gen), dist_pos(gen)});
    LocalPtsNextBlockSpawn.push_back({dist_pos(gen), dist_pos(gen)});
    LocalPtsNextBlockSpawn.push_back({dist_pos(gen), dist_neg(gen)});

    _spawnNewHeli = false;
  }
  for (auto& h : Helis)
  {
    h.Pos.x += 150.0f * fElapsedTime;

    auto getOff = [](Helicopter& h, float fElapsedTime){
      h.Pos.x += 50.0f * fElapsedTime;
      h.Pos.y -= 100.0f * fElapsedTime;
      h.Scale.x = std::max(h.Scale.x-0.005f, 0.005f);
      h.Scale.y = std::max(h.Scale.y-0.005f, 0.005f);
    };

    if (h.payLoad == false)
    {
      getOff(h, fElapsedTime);
    }

    if (h.Pos.x > 400.0f && h.payLoad == true)
    {
      h.payLoad = false;
      h.fliesAway = true;
      getOff(h, fElapsedTime);
      if (Time < Winning_time)
      {
        h.fliesAwayStone = LocalPtsNextBlockSpawn;
        _spawnNewHeli = true;
      }      
    }
  }

  Time += fElapsedTime;
  if (Time*_avalanche_speed > (float)NextSpawnId && Time < Winning_time)
  {
    std::uniform_real_distribution<float> dist_neg{
      _stones_dist_neg.x,_stones_dist_neg.y};
    std::uniform_real_distribution<float> dist_pos{
      _stones_dist_pos.x,_stones_dist_pos.y};

    std::vector<PT<float>> localPts;
    localPts.push_back({dist_neg(gen), dist_neg(gen)});
    localPts.push_back({dist_neg(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_neg(gen)});
    _userdata.push_back(NextSpawnId);
    if (!_stoneSound)
    {
      SO.StartEffect("assets/mp3/stone.mp3", 1.0f);
      _stoneSound = true;
    }
    
    _world.SpawnPolygon(NextSpawnId, _stone_spawn, localPts,
      _stone_angle, 2,  1.0, _stone_rest, _stone_fric,
      0.0, 0.0, &_userdata.back());
    NextSpawnId++;
  }
  if (Time > Winning_time)
  {
    SO.StopEffect("assets/mp3/stone.mp3", 0.8f);
    _stoneSound = false;
    SO.StopEffect("assets/mp3/helicopter.mp3", 0.8f);
    _heliSound = false;
    if (!_birdSound)
    {
      SO.StartEffect("assets/mp3/bird.mp3", 0.6f);
      _birdSound = true;
    }
  }
	
	if (input.leftMouseClicked)
	{
    auto it = std::find_if(Helis.begin(), Helis.end(),
      [](Helicopter& h){return h.payLoad == true && h.fliesAway == false;});
    if (it != Helis.end() && it->Pos.x > 50.0f)
    {
      _userdata.push_back(NextWallSpawnId);

      std::vector<PT<float>> localPts;
      localPts.push_back(LocalPtsNextBlockSpawn[0]);
      localPts.push_back(LocalPtsNextBlockSpawn[1]);
      localPts.push_back(LocalPtsNextBlockSpawn[2]);
      localPts.push_back(LocalPtsNextBlockSpawn[3]);

      _world.SpawnPolygon(NextWallSpawnId, { it->Pos.x, it->Pos.y + 50.0f },
        localPts, _wall_angle, 2,  1.0,
        _wall_rest, _wall_fric, 0.0, 0.0, &_userdata.back());
      NextWallSpawnId++;
      it->payLoad = false;
      _spawnNewHeli = true;
    }
	}

  if (StatusText1.empty())
  {
    if (_cl_house->IsInContactWithId(1000, 0))
    {
      _world.SetBoostXY(3001, 100.0f, 150.0f);
      _world.SetBoostXY(3002, -125.0f, 75.0f);
      _levelEndTime = Time + 5.0f;
      StatusText1 = "YOU FAILED !!!";
      StatusText2 = "YOUR HOME IS LOST.";
      StatusTextTime = Time + 2.0f;
    }
    if (_cl_house->IsInContactWithId(3000, 2000))
    {
      _world.SetBoostXY(3001, -50.0f, 10.0f);
      _world.SetBoostXY(3002, -60.0f, 10.0f);
      _levelEndTime = Time + 5.0f;
      StatusText1 = "YOU FOOL !!!";
      StatusText2 = "THIS WAS A VERY BAD IDEA.";
      StatusTextTime = Time + 2.0f;
    }
    if (Time > (Winning_time+2.0f))
    {
      _levelEndTime = Time + 5.0f;
      StatusText1 = "CONGRATULATIONS !!!";
      StatusText2 = "THE AVALANCHE IS DEFEATED.";
      StatusTextTime = Time + 2.0f;
    }
  }

  _world.Step(fElapsedTime);

  if (Time > _levelEndTime)
  {
    _fader.StartFadeOut();
    _levelEndTime = FLT_MAX;
  }
  if (_fader.IsFading())
  {
    _fader.Update(fElapsedTime);
    if (_fader.IsTurning())
    {
      SO.StopAllEffects();
      return std::make_unique<MainMenuState>();
    }
  }

  bool getOutOfHere = input.escapePressed;
//#ifdef __EMSCRIPTEN__
  if (input.leftMouseClicked && input.mouseX < BackBox.x && input.mouseY > (CO.H-BackBox.y))
  {
    getOutOfHere = true;
  }
//#endif

  return RequestForMainMenu(getOutOfHere, fElapsedTime);
}

Render* Scene::GetRender()
{
  return _render.get();
}

void Scene::LoadLevelData()
{
  _world.LoadFromScript("world", Scenery, _userdata);

  LS.Init("scripts/scenes.lua", false);
  
  MountainIds = { 1001, LS.Int(Scenery + "_mountainIds") };
  _stones_dist_neg = LS.PTFloat("stones_dist_neg");
  _stones_dist_pos = LS.PTFloat("stones_dist_pos");
  _stone_spawn = LS.PTFloat(Scenery + "_stone_spawn");
  _stone_fric = LS.Float(Scenery + "_stone_fric");
  _stone_angle = LS.Float(Scenery + "_stone_angle");
  _stone_rest = LS.Float(Scenery + "_stone_rest");

  _roof_height = LS.Float(Scenery + "_roof_height");

  _wall_rest = LS.Float(Scenery + "_wall_rest");
  _wall_fric = LS.Float(Scenery + "_wall_fric");
  _wall_angle = LS.Float(Scenery + "_wall_angle");

  _wall_dist_neg = LS.PTFloat("wall_dist_neg");
  _wall_dist_pos = LS.PTFloat("wall_dist_pos");

  _avalanche_speed = LS.Float(Scenery + "_avalanche_speed");

  Winning_time = LS.Float(Scenery + "_winning_time");

  Colors = LS.Colors();
}

void Scene::SaveLevelData()
{
}
