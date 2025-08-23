#include <game/sceneRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void SceneRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  pge->Clear(olc::DARK_BLUE);
  pge->DrawString({ 10, 10 }, "SceneRender", olc::WHITE);
}