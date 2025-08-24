#include "olcTemplate/game/guiElements.hpp"
#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

SceneRender::SceneRender() : _rMountain(std::make_unique<olc::Renderable>()),
  _rStones(std::make_unique<olc::Renderable>()),
	_rWall(std::make_unique<olc::Renderable>()),
  _rHouse(std::make_unique<olc::Renderable>())
{
  OlcHelper::CreateOneColorDecal(_rMountain.get(), olc::CYAN);
  OlcHelper::CreateOneColorDecal(_rStones.get(), olc::DARK_GREY);
	OlcHelper::CreateOneColorDecal(_rWall.get(), olc::RED);
  OlcHelper::CreateOneColorDecal(_rHouse.get(), olc::DARK_YELLOW);
}

void SceneRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto S = static_cast<Scene*>(state);

  pge->Clear(olc::DARK_BLUE);
  auto font = FT.Font("dogica", FontSize::SMALLER);
  auto dec = font->RenderStringToDecal(
      utf8::utf8to32(std::to_string(S->Time)), olc::WHITE);
  pge->DrawDecal({(float)CO.W-dec->sprite->width - 10.0f,
    (float)CO.H-dec->sprite->height - 10.0f}, dec);

  auto decalById = [&](int id){
    if (id > 1000 && id < 2000)
      return _rStones.get()->Decal();
    else if (id > 2000 && id < 3000)
      return _rWall.get()->Decal();
    else if (id > 3000)
      return _rHouse.get()->Decal();
    else
      return _rMountain.get()->Decal();
	};

  std::vector<PT<float>> vPts;
  std::array<olc::vf2d, 4> arr = {};

  for (int i = S->MountainIds.x; i <= S->MountainIds.y; i++)
  {
    vPts = S->GetPolygon(i);
    {
      arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
      arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
      arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
      arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
    }
    pge->DrawWarpedDecal(decalById(i), arr);
  }

  auto heliSprite = AS.Sprite("helicopter")->Size();
  for (const auto& heli : S->Helis)
  {
    pge->DrawDecal({
      heli.Pos.x - heli.Scale.x*heliSprite.x/2.0f,
      heli.Pos.y - heli.Scale.y*heliSprite.y/2.0f},
      AS.Decal("helicopter"), {heli.Scale.x, heli.Scale.y});
  }

  vPts = S->GetPolygon(3001);
  {
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
  }
  pge->DrawWarpedDecal(decalById(3001), arr);
  vPts = S->GetPolygon(3002);
  {
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[2].x+0.01f; arr[3].y = vPts[2].y-0.01f;
  }
  pge->DrawWarpedDecal(decalById(3002), arr);


  for (int i = 1; i < S->NextSpawnId; i++)
  {
    vPts = S->GetPolygon(i);
    {
      arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
      arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
      arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
      arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
    }
    pge->DrawWarpedDecal(decalById(i), arr);
  }

	for (int i = 2001; i < S->NextWallSpawnId; i++)
	{
		vPts = S->GetPolygon(i);
		{
			arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
			arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
			arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
      if (vPts.size() < 4)
      {
        arr[3].x = vPts[2].x+0.01f; arr[3].y = vPts[2].y-0.01f;
      }
      else
      {
        arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;      
      }
		}
		pge->DrawWarpedDecal(decalById(i), arr);
	}
}
