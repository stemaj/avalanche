#include "olcTemplate/game/guiElements.hpp"
#include <algorithm>
#include <cstdint>
#include <exception>
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

//#define LEVEL_DESIGN

SceneRender::SceneRender() : _rMountain(std::make_unique<olc::Renderable>()),
  _rStones(std::make_unique<olc::Renderable>()),
	_rWall(std::make_unique<olc::Renderable>()),
  _rHouse(std::make_unique<olc::Renderable>()) {}

void SceneRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto pix = [](std::array<uint8_t,4> col){
    return olc::Pixel(col[0],col[1],col[2],col[3]);
  };

  auto S = static_cast<Scene*>(state);

  if (!_rendsCreated)
  {
    OlcHelper::CreateOneColorDecal(_rMountain.get(), pix(S->Colors[0]));
    OlcHelper::CreateOneColorDecal(_rStones.get(), pix(S->Colors[1]));
    OlcHelper::CreateOneColorDecal(_rWall.get(), pix(S->Colors[1]));
    auto houseCol = pix(S->Colors[0]);
    houseCol.a = S->Scenery == "hard" ? 255 : 150;
    OlcHelper::CreateOneColorDecal(_rHouse.get(), houseCol);

    _rendsCreated = true;
  }

#ifdef LEVEL_DESIGN
  pge->Clear(olc::GREY);
#else
  // background
  pge->DrawDecal({0.0f,0.0f}, AS.Decal(S->Scenery), {0.8,0.8});
#endif

  auto font = FT.Font("Alkia", FontSize::SMALLER);
  float f = std::max(S->Winning_time-S->Time, 0.0f);
  auto dec = font->RenderStringToDecal(
      utf8::utf8to32(std::to_string(f)), pix(S->Colors[3]));
  pge->DrawDecal({(float)CO.W-100.0f,
    (float)CO.H-dec->sprite->height - 10.0f}, dec);

  auto decalById = [&](int id){
    if (id > 1000 && id < 2000)
      return _rMountain.get()->Decal();
    else if (id > 2000 && id < 3000)
      return _rWall.get()->Decal();
    else if (id > 3000)
      return _rHouse.get()->Decal();
    else
      return _rStones.get()->Decal();
	};

  std::vector<PT<float>> vPts;
  std::array<olc::vf2d, 4> arr = {};

#ifdef LEVEL_DESIGN
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
#endif

  auto heliSprite = S->Scenery == "hard" ? AS.Sprite("helicopter_night")->Size() : AS.Sprite("helicopter")->Size();
  for (const auto& heli : S->Helis)
  {
    auto d = S->Scenery == "hard" ? AS.Decal("helicopter_night") : AS.Decal("helicopter"); 
    pge->DrawDecal({
      heli.Pos.x - heli.Scale.x*heliSprite.x/2.0f,
      heli.Pos.y - heli.Scale.y*heliSprite.y/2.0f},
      d, {heli.Scale.x, heli.Scale.y});

    if (heli.payLoad && !heli.fliesAway)
    {
      arr[0].x = heli.Pos.x + S->LocalPtsNextBlockSpawn[0].x; arr[0].y = heli.Pos.y + 50.0f + S->LocalPtsNextBlockSpawn[0].y;
      arr[1].x = heli.Pos.x + S->LocalPtsNextBlockSpawn[1].x; arr[1].y = heli.Pos.y + 50.0f + S->LocalPtsNextBlockSpawn[1].y;
      arr[2].x = heli.Pos.x + S->LocalPtsNextBlockSpawn[2].x; arr[2].y = heli.Pos.y + 50.0f + S->LocalPtsNextBlockSpawn[2].y;
      arr[3].x = heli.Pos.x + S->LocalPtsNextBlockSpawn[3].x; arr[3].y = heli.Pos.y + 50.0f + S->LocalPtsNextBlockSpawn[3].y;
      pge->DrawWarpedDecal(decalById(2500), arr);
    }
    else if (!heli.payLoad && heli.fliesAway && !heli.fliesAwayStone.empty())
    {
      arr[0].x = heli.Pos.x + heli.Scale.x/0.25f * heli.fliesAwayStone[0].x; arr[0].y = heli.Pos.y + heli.Scale.y/0.25f * (50.0f + heli.fliesAwayStone[0].y);
      arr[1].x = heli.Pos.x + heli.Scale.x/0.25f * heli.fliesAwayStone[1].x; arr[1].y = heli.Pos.y + heli.Scale.y/0.25f * (50.0f + heli.fliesAwayStone[1].y);
      arr[2].x = heli.Pos.x + heli.Scale.x/0.25f * heli.fliesAwayStone[2].x; arr[2].y = heli.Pos.y + heli.Scale.y/0.25f * (50.0f + heli.fliesAwayStone[2].y);
      arr[3].x = heli.Pos.x + heli.Scale.x/0.25f * heli.fliesAwayStone[3].x; arr[3].y = heli.Pos.y + heli.Scale.y/0.25f * (50.0f + heli.fliesAwayStone[3].y);
      pge->DrawWarpedDecal(decalById(2500), arr);
    }
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

  auto drawBlock = [pge, S, decalById, &arr](int i){
    auto vPts = S->GetPolygon(i);
    arr[0].x = vPts[0].x; arr[0].y = vPts[0].y;
    arr[1].x = vPts[1].x; arr[1].y = vPts[1].y;
    arr[2].x = vPts[2].x; arr[2].y = vPts[2].y;
    arr[3].x = vPts[3].x; arr[3].y = vPts[3].y;
    pge->DrawWarpedDecal(decalById(i), arr);
  };

  for (int i = 1; i < S->NextSpawnId; i++)
  {
    drawBlock(i);
  }
	for (int i = 2001; i < S->NextWallSpawnId; i++)
	{
		drawBlock(i);
	}

  // success / failure Texts
  if (S->StatusTextTime < S->Time)
  {
    font = FT.Font("Alkia", FontSize::BIG);
    dec = font->RenderStringToDecal(
      utf8::utf8to32(S->StatusText1), pix(S->Scenery == "hard" ? S->Colors[3] : S->Colors[0]));
    pge->DrawDecal({(float)CO.W/2.0f-dec->sprite->width/2.0f,
      (float)CO.H/2.0f-dec->sprite->height- 25.0f}, dec);

    font = FT.Font("Alkia", FontSize::NORMAL);
    dec = font->RenderStringToDecal(
      utf8::utf8to32(S->StatusText2), pix(S->Scenery == "hard" ? S->Colors[3] : S->Colors[0]));
    pge->DrawDecal({(float)CO.W/2.0f-dec->sprite->width/2.0f,
      (float)CO.H/2.0f+ 25.0f}, dec);
  }

  // back button
  font = FT.Font("Alkia", FontSize::SMALLEST);
  try
  {
    dec = font->RenderStringToDecal(
        utf8::utf8to32(std::string("BACK")), pix(S->Colors[0]));
  }
  catch (std::exception& ex)
  {
    std::cout << ex.what();
  }
  pge->FillRectDecal({0.0f,(float)CO.H-S->BackBox.y},
    {S->BackBox.x,S->BackBox.y});
  pge->DrawDecal({0.0f, (float)CO.H-dec->sprite->height}, dec);

#if LEVEL_DESIGN
  pge->DrawStringDecal({0,0}, pge->GetMousePos().str(), olc::BLACK);
#endif
}
