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
  int NextSpawnId = 1;
	int NextWallSpawnId = 2001;

  std::vector<PT<float>> GetPolygon(const int id) { 
    auto ret = _world.GetPolygons()[id];
    return ret.empty() ? std::vector<PT<float>>{} : ret;
  }

  struct Helicopter
  {
    PT<float> Pos = {};
    bool payLoad = true;
    bool fliesAway = false;
    std::vector<PT<float>> fliesAwayStone = {};
    PT<float> Scale = {0.25f, 0.25f};
  };
  std::vector<Helicopter> Helis = {};

  float Time = -3.0f;
  float Winning_time = 0.0f;
  std::string StatusText1 = "";
  std::string StatusText2 = "";
  float StatusTextTime = FLT_MAX;

  std::vector<std::array<uint8_t, 4>> Colors = {};
  std::string Scenery = "";

  std::vector<PT<float>> LocalPtsNextBlockSpawn = {};

  PT<float> BackBox = { 29., 13. };

  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:

  bool _heliSound = false;
  bool _stoneSound = false;
  bool _birdSound = false;

  float _levelEndTime = FLT_MAX;

  float _spawnNewHeli = true;

  float _avalanche_speed = 0.0f;

  float _wall_angle = 0.0f;
  float _wall_rest = 0.0f;
  float _wall_fric = 0.0f;
  PT<float> _wall_dist_neg = {};
  PT<float> _wall_dist_pos = {};

  float _roof_height = 0.0f;
  
  float _stone_fric = 0.0f;
  float _stone_angle = 0.0f;
  float _stone_rest = 0.0f;
  PT<float> _stone_spawn = {};
  PT<float> _stones_dist_neg = {};
  PT<float> _stones_dist_pos = {};
  std::unordered_map<int, std::vector<PT<float>>> _mountainCoords;

  PT<float> _worldUpperLeft;
  PT<float> _worldSize;
  std::shared_ptr<PhysicalWorld::ContactChecker> _cl_house;
  //std::shared_ptr<PhysicalWorld::ContactChecker> _cl_roof;
  std::list<int> _userdata = {};
  PhysicalWorld _world;

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<SceneRender> _render;
};

} // namespace stemaj

#endif // __SCENESTATE_HPP

