#include <game/tutorialRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void TutorialRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  pge->DrawDecal({0,0}, AS.Decal("tutorial"), {0.8f,0.8f});
}