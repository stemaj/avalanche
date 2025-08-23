#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <vector>

using namespace stemaj;

Scene::Scene(const std::string& scenery) : _render(std::make_unique<SceneRender>()), _scenery(scenery)
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
  time += fElapsedTime;
  if (time*2.0f > (float)NextSpawnId)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist_neg{-20.0f, -5.0f};
    std::uniform_real_distribution<float> dist_pos{5.0f, 20.0f};

    std::cout << "Spawne " << NextSpawnId << std::endl;
    std::vector<PT<float>> localPts;
    localPts.push_back({dist_neg(gen), dist_neg(gen)});
    localPts.push_back({dist_neg(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_pos(gen)});
    localPts.push_back({dist_pos(gen), dist_neg(gen)});
    _world.SpawnPolygon(NextSpawnId, { 850.0, -100.0 }, localPts, 1.27f,
      2,  1.0, 0.2, 0.4, 0.3, 0.0, nullptr);
    NextSpawnId++;
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
