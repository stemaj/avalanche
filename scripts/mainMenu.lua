
colors = {
  --Jehkoba16 Palette
  {41,128,166 ,255},
  {240,205,48 ,255},
  {8,9,26 ,255},
  {242,236,230 ,255},
  {152,217,211 ,255},
}

background_color = 4

button_normal_color = 1
button_hover_color = 2
button_click_color = 3

font = "Alkia"

--        Text,											 Pos,       Size, Color
texts = {
  {"AVALANCHE ",									        {0.3, 0.1},  5, 0},
  {"made for OLC Code Jam 2025: Shapes ",	{0.3, 0.3},  3, 0},

  {"made with: ",	  {0.02, 0.02},  4, 0},
  {"BOX2D ",	      {0.02, 0.26},  4, 0},
  {"Soloud ",	      {0.02, 0.46},  4, 0},
  {"Olc PixelGameEngine ",	      {0.02, 0.6},  4, 0},
  {"Font: https://font.download/font/alkia ",	      {0.02, 0.7},  4, 0},  

  {"Sounds: https://pixabay.com/de/music",	      {0.02, 0.8},  4, 0},  
  {"intro-outro-breaking-news-177297",	      {0.02, 0.83},  4, 0},  
  {"groovy-energy-sports-80-bpm-short-12275",	      {0.02, 0.86},  4, 0},  
  {"hard-rock-logo-108960",	      {0.02, 0.89},  4, 0},  
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
    [0] = {"Start Easy Game",      { 0.3, 0.4 }, 1, 0, 10 },
    [1] = {"Start Medium Game",    { 0.3, 0.52 }, 1, 0, 10 },
    [2] = {"Start Hard Game",      { 0.3, 0.63 }, 1, 0, 10 },
  }
  