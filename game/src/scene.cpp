#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <vector>

using namespace stemaj;

Scene::Scene(const std::string& scenery) : _scenery(scenery), _render(std::make_unique<SceneRender>())
{
  LoadLevelData();
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
    std::uniform_real_distribution<float> dist_neg{-20.0f, -5.0f};
    std::uniform_real_distribution<float> dist_pos{5.0f, 20.0f};

    std::cout << "Spawne " << NextSpawnId << std::endl;
    std::vector<PT<float>> localPts;
    localPts.push_back({dist_neg(gen), dist_neg(gen)});
    localPts.push_back({dist_neg(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_neg(gen)});
    _world.SpawnPolygon(NextSpawnId, { 850.0, -100.0 }, localPts, 1.27f,
      2,  1.0, 0.2, 0.2, 0.0, 0.0, nullptr);
    NextSpawnId++;
  }
	
	if (input.leftMouseClicked)
	{
		std::vector<PT<float>> localPts;
		localPts.push_back({0.f,-30.f});
		localPts.push_back({-20.0f, -10.0f});
		localPts.push_back({+20.0f, 10.0f});
		_world.SpawnPolygon(NextWallSpawnId, { input.mouseX, input.mouseY }, localPts, 0.f,
			2,  1.0, 0.05, 0.8, 0.3, 0.8, nullptr);
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
  
  MountainIds = LS.PTInt(_scenery + "_mountainIds");
}

void Scene::SaveLevelData()
{
}
