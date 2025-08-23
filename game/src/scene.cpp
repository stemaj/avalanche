#include <game/sceneRender.hpp>
#include <game/scene.hpp>

using namespace stemaj;

Scene::Scene() : _render(std::make_unique<SceneRender>())
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
  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* Scene::GetRender()
{
  return _render.get();
}

void Scene::LoadLevelData()
{
}

void Scene::SaveLevelData()
{
}
