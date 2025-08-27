#ifndef __TUTRENDER_HPP
#define __TUTRENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class TutorialRender : public LevelRender
{
public:
  explicit TutorialRender() {}
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __TUTRENDER_HPP
