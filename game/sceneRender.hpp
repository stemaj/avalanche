#ifndef __SCENERENDER_HPP
#define __SCENERENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class SceneRender : public LevelRender
{
public:
  explicit SceneRender();
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

private:
	std::unique_ptr<olc::Renderable> _rMountain;
  std::unique_ptr<olc::Renderable> _rThing;
};

} // namespace stemaj

#endif // __SCENERENDER_HPP
