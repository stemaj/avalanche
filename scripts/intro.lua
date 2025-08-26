dofile('scripts/colors.lua')

font = "Alkia"
fade_time = 1.0
intro_time = 14.0

background_color = 0

--        Name,               Pos,       Size, Start, End, Color
texts = {
  {"A",                 { 0.3, 0.1 },  5, 0.1, 0.9, 3},
  {"AV",                { 0.3, 0.1 },  5, 0.12, 0.88, 3},
  {"AVA",               { 0.3, 0.1 },  5, 0.14, 0.86, 3},
  {"AVAL",              { 0.3, 0.1 },  5, 0.16, 0.84, 3},
  {"AVALA",              { 0.3, 0.1 },  5, 0.18, 0.82, 3},
  {"AVALAN",              { 0.3, 0.1 },  5, 0.2, 0.8, 3},
  {"AVALANC",              { 0.3, 0.1 },  5, 0.22, 0.78, 3},
  {"AVALANCH",              { 0.3, 0.1 },  5, 0.24, 0.76, 3},
  {"AVALANCHE",              { 0.3, 0.1 },  5, 0.26, 0.74, 3},
  {"(c) 2025 riegel games",  { 0.3, 0.8 }, 0, 0.28, 0.92, 3},
}

--   File,         Pos,      Scale, Start, End
graphics = {
  {"title",     { -0.05, -0.05 }, 1.0, -0.1, 9.0},
--  {"pge2_logo", { 0.03, 0.76 }, 0.5, 0.19, 0.31}
}

animations = {
  --"pretty_pretty_bg_25pc",
  --"pretty_pretty_ch_25pc",
}