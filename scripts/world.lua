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

hard_rects = {
  {1001,  { -100.0,350.0 },  { 410.0, 350.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1002,  {  410.0,350.0 },  { 430.0, 320.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1003,  {  430.0,320.0 },  { 530.0, 320.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1004,  {  530.0,320.0 },  { 600.0, 300.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1005,  { 600.0, 300.0 },  { 550.0, 160.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1006,  { 550.0, 160.0 },  { 430.0, 110.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1007,  { 430.0, 110.0 },  { 540.0,  60.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1008,  { 540.0, 60.0 },  { 780.0,  -10.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},
  {1009,  { 780.0, -10.0 },   { 900.0, -150.0 },   thickness, 0,  1.0, rest, fric, 0.0, 0.0},

  {3001,  { 450.0,320.0 },  { 510.0, 320.0 },   house_size, 2,  1.0, house_rest, house_fric, 0.0, 0.0},
}

box2d_scale = 0.01 --nicht aendern...

box2d_gravity = { 0.0, 9.81 } -- Erdbeschleunigung
