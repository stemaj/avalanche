#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/loadsave.hpp>

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
  ;
}

void Scene::SaveLevelData()
{
}
