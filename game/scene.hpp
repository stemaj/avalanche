#ifndef __SCENESTATE_HPP
#define __SCENESTATE_HPP

#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class SceneRender;

class Scene : public LevelState
{
public:

  explicit Scene();
  virtual ~Scene();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<SceneRender> _render;
};

} // namespace stemaj

#endif // __SCENESTATE_HPP

