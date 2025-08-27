#include <game/tutorialRender.hpp>
#include <game/tutorial.hpp>
#include <optional>

using namespace stemaj;

Tutorial::Tutorial() : _render(std::make_unique<TutorialRender>())
{
}

Tutorial::~Tutorial()
{
}

std::optional<std::unique_ptr<State>> Tutorial::Update(
  const Input& input, float fElapsedTime)
{
    return RequestForMainMenu(
      input.escapePressed || input.spacePressed || input.leftMouseClicked, 
      fElapsedTime);
}

Render* Tutorial::GetRender()
{
  return _render.get();
}

void Tutorial::LoadLevelData()
{
}

void Tutorial::SaveLevelData()
{
}
