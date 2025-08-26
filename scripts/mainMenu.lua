dofile('scripts/colors.lua')

background_color = 0

button_normal_color = 3
button_hover_color = 1
button_click_color = 2

font = "Alkia"

--        Text,											 Pos,       Size, Color
texts = {
  {"AVALANCHE ",									        {0.3, 0.1},  5, 3},
  {"made for OLC Code Jam 2025: Shapes ",	{0.3, 0.3},  3, 3},

  {"made with: ",	  {0.02, 0.02},  4, 3},
  {"BOX2D ",	      {0.02, 0.26},  4, 3},
  {"Soloud ",	      {0.02, 0.46},  4, 3},
  {"Olc PixelGameEngine ",	      {0.02, 0.6},  4, 3},
  {"Font: https://font.download/font/alkia ",	      {0.02, 0.7},  4, 3},  

  {"Sounds: https://pixabay.com/de/music",	      {0.02, 0.8},  4, 3},  
  {"intro-outro-breaking-news-177297",	      {0.02, 0.83},  4, 3},  
  {"groovy-energy-sports-80-bpm-short-12275",	      {0.02, 0.86},  4, 3},  
  {"hard-rock-logo-108960",	      {0.02, 0.89},  4, 3},  

  {"Color Palette: https://lospec.com/palette-list/bicycle",	      {0.02, 0.93},  4, 3},  
}

--   File,         Pos,      Scale
graphics = {
  {"title",     { -0.05, -0.05 }, 1.0},
  {"box2d",     { 0.02, 0.02 }, 0.3},
  {"soloud",    { 0.02, 0.3 }, 0.15},
  {"pge2_logo", { 0.015, 0.5 }, 0.2},
}

--  Option: Text,					 Pos,    Size, Color, Buttondelta
buttons = {
    [0] = {"Start Easy Game",      { 0.3, 0.4 }, 0, 0, 10 },
    [1] = {"Start Medium Game",    { 0.3, 0.52 }, 0, 0, 10 },
    [2] = {"Start Hard Game",      { 0.3, 0.63 }, 0, 0, 10 },
  }
  