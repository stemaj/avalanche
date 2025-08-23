#ifndef __SCENESTATE_HPP
#define __SCENESTATE_HPP

#include <olcTemplate/game/src/state/levelState.hpp>
#include <olcTemplate/game/physicalWorld.hpp>

namespace stemaj {

class SceneRender;

class Scene : public LevelState
{
public:

  explicit Scene(const std::string& scenery);
  virtual ~Scene();

  PT<int> MountainIds;

  std::vector<PT<float>> GetPolygon(const int id) { 
    auto ret = _world.GetPolygons()[id];
    return ret.empty() ? std::vector<PT<float>>{} : ret;
  }
  
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  std::unordered_map<int, std::vector<PT<float>>> _mountainCoords;

  PT<float> _worldUpperLeft;
  PT<float> _worldSize;
  PhysicalWorld::Userdata _userData = {};
  PhysicalWorld _world;
  std::string _scenery = "";

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<SceneRender> _render;
};

} // namespace stemaj

#endif // __SCENESTATE_HPP

