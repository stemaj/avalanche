#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <vector>
#include <random>

using namespace stemaj;

Scene::Scene(const std::string& scenery) : _scenery(scenery), _render(std::make_unique<SceneRender>())
{
  LoadLevelData();

  // Hausdach
  auto cp = _world.GetCenterPoint(3001);
  std::vector<PT<float>> roofPts = {
    { 0.0f, -_roof_height }, 
    {-_roof_height/2.f, _roof_height/2.f}, 
    {_roof_height/2.f, _roof_height/2.f} };
  _world.SpawnPolygon(3002, 
    {cp.x, cp.y - _roof_height}, roofPts,
    0.0f, 2, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, nullptr);
}

Scene::~Scene()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> Scene::Update(
  const Input& input, float fElapsedTime)
{
	std::random_device rd;
	std::mt19937 gen(rd());
  _time += fElapsedTime;
  if (_time*2.0f > (float)NextSpawnId)
  {
    std::uniform_real_distribution<float> dist_neg{
      _stones_dist_neg.x,_stones_dist_neg.y};
    std::uniform_real_distribution<float> dist_pos{
      _stones_dist_pos.x,_stones_dist_pos.y};

    std::cout << "Spawne " << NextSpawnId << std::endl;
    std::vector<PT<float>> localPts;
    localPts.push_back({dist_neg(gen), dist_neg(gen)});
    localPts.push_back({dist_neg(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_neg(gen)});
    _world.SpawnPolygon(NextSpawnId, _stone_spawn, localPts,
      _stone_angle, 2,  1.0, _stone_rest, _stone_fric,
      0.0, 0.0, nullptr);
    NextSpawnId++;
  }
	
	if (input.leftMouseClicked)
	{
		_world.SpawnPolygon(NextWallSpawnId, { input.mouseX, input.mouseY },
      _wall_local_coord, _wall_angle, 2,  1.0,
      _wall_rest, _wall_fric, 0.0, 0.0, nullptr);
		NextWallSpawnId++;
	}

  _world.Step(fElapsedTime);

  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* Scene::GetRender()
{
  return _render.get();
}

void Scene::LoadLevelData()
{
  _world.LoadFromScript("world", _scenery, &_userData);

  LS.Init("scripts/scenes.lua", false);
  
  MountainIds = { 1001, LS.Int(_scenery + "_mountainIds") };
  _stones_dist_neg = LS.PTFloat("stones_dist_neg");
  _stones_dist_pos = LS.PTFloat("stones_dist_pos");
  _stone_spawn = LS.PTFloat(_scenery + "_stone_spawn");
  _stone_fric = LS.Float(_scenery + "_stone_fric");
  _stone_angle = LS.Float(_scenery + "_stone_angle");
  _stone_rest = LS.Float(_scenery + "_stone_rest");

  _roof_height = LS.Float(_scenery + "_roof_height");

  _wall_rest = LS.Float(_scenery + "_stone_rest");
  _wall_fric = LS.Float(_scenery + "_stone_fric");
  _wall_angle = LS.Float(_scenery + "_stone_angle");
  _wall_local_coord = LS.VPTFloat(_scenery + "_wall_local_coord");
}

void Scene::SaveLevelData()
{
}
