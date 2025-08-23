#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

SceneRender::SceneRender() : _rMountain(std::make_unique<olc::Renderable>()), _rThing(std::make_unique<olc::Renderable>())
{
  OlcHelper::CreateOneColorDecal(_rMountain.get(), olc::CYAN);
  OlcHelper::CreateOneColorDecal(_rThing.get(), olc::RED);
}

void SceneRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto S = static_cast<Scene*>(state);

  pge->Clear(olc::DARK_BLUE);
  pge->DrawString({ 10, 10 }, "SceneRender", olc::WHITE);

  auto decalById = [&](int id){
		if (id < 10) return _rThing.get()->Decal();
    return _rMountain.get()->Decal();
	};

  auto vPts = S->GetPolygon(101);
  std::array<olc::vf2d, 4> arr = {};
  {
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
  }
  pge->DrawWarpedDecal(decalById(101), arr);

  vPts = S->GetPolygon(1);
  {
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
  }
  pge->DrawWarpedDecal(decalById(1), arr);

  vPts = S->GetPolygon(2);
  {
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
  }
  pge->DrawWarpedDecal(decalById(2), arr);
}