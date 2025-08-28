thickness = 20.0
rest = 0.2
fric = 0.3

house_size = 60
house_rest = 0.4
house_fric = 0.2

easy_rects = {
  {1001,  { -100.0,350.0 },  { 300.0, 350.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1002,  { 300.0, 350.0 },  { 340.0, 300.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1003,  { 340.0, 300.0 },  { 450.0, 270.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1004,  { 450.0, 270.0 },  { 550.0, 255.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1005,  { 550.0, 255.0 },  { 600.0, 220.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1006,  { 600.0, 220.0 },  { 700.0, 100.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1007,  { 700.0, 100.0 },  { 780.0,  30.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1008,  { 780.0, 30.0 },   { 900.0, -30.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},

  {3001,  { 40.0,320.0 },  { 100.0, 320.0 },   house_size, 2,  1.0, house_rest, house_fric, 0.0, 0.0},
}


local mpt1 = { 370.0, 350.0 }
local mpt2 = { 410.0, 280.0 }
local mpt3 = { 510.0, 270.0 }
local mpt4 = { 570.0, 230.0 }
local mpt5 = { 590.0, 190.0 }
local mpt6 = { 700.0, 110.0 }
local mpt7 = { 740.0,   0.0 }
local mpt8 = { 1000.0, -100.0 }

medium_rects = {
  {1001,  { -100.0,350.0 },  mpt1 ,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1002,   mpt1 ,            mpt2,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1003,   mpt2 ,            mpt3,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1004,   mpt3 ,            mpt4,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1005,   mpt4 ,            mpt5,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1006,   mpt5 ,            mpt6,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1007,   mpt6 ,            mpt7,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1008,   mpt7 ,            mpt8,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},

  {3001,  { 40.0,320.0 },  { 100.0, 320.0 },   house_size, 2,  1.0, house_rest, house_fric, 0.0, 0.0},
}

local hpt1 = { 300.0, 350.0 }
local hpt2 = { 380.0, 300.0 }
local hpt3 = { 450.0, 180.0 }
local hpt4 = { 550.0, 100.0 }
local hpt5 = { 640.0, 20.0 }
local hpt6 = { 670.0, -10.0 }
local hpt7 = { 800.0, -100.0 }
local hpt8 = { 1000.0, -150.0 }


hard_rects = {
  {1001,  { -100.0,350.0 },  hpt1,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1002,  hpt1,  hpt2,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1003,  hpt2,  hpt3,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1004,  hpt3,  hpt4,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1005,  hpt4,  hpt5,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1006,  hpt5,  hpt6,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1007,  hpt6,  hpt7,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1008,  hpt7,  hpt8,   thickness, 0,  1.0, rest, fric, 0.0, 0.0},

  {3001,  { 40.0,320.0 },  { 100.0, 320.0 },   house_size, 2,  1.0, house_rest, house_fric, 0.0, 0.0},
}

box2d_scale = 0.01 --nicht aendern...

box2d_gravity = { 0.0, 9.81 } -- Erdbeschleunigung
