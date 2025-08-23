#ifndef __SCENESTATE_HPP
#define __SCENESTATE_HPP

#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class SceneRender;

class Scene : public LevelState
{
public:

  enum class Scenery
  {
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
  };

  explicit Scene(const Scenery scenery);
  virtual ~Scene();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  Scenery _scenery = Scenery::EASY;

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<SceneRender> _render;
};

} // namespace stemaj

#endif // __SCENESTATE_HPP

