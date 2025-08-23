ROOT_DIR = path.getabsolute(".")

solution "Avalanche"
  basedir (ROOT_DIR)
  location (path.join(ROOT_DIR,"solution"))
  language "C++"
  configurations {
    "Debug",
    "Test",
    "Release",
  }
  configuration "Debug"
    targetdir (path.join(ROOT_DIR,"solution/bin/Debug"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    defines { "STEMAJ_DEBUG" }
    flags { "Symbols", "Cpp20" }
  configuration "Test"
    targetdir (path.join(ROOT_DIR,"solution/bin/Test"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    defines { "RUN_TESTS" }
    flags { "Symbols", "Cpp20" }
  configuration "Release"
    targetdir (path.join(ROOT_DIR,"solution/bin/Release"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    defines { "STEMAJ_RELEASE" }
    flags { "OptimizeSpeed", "Cpp20" }
  platforms {
    "Native",
    "x64",
    "Universal64",
  }

project "Avalanche"
  kind "ConsoleApp"
  files {
    path.join(ROOT_DIR,"**.h"),
    path.join(ROOT_DIR,"**.hpp"),
    path.join(ROOT_DIR,"**.c"),
    path.join(ROOT_DIR,"**.cc"),
    path.join(ROOT_DIR,"**.cpp"),
    path.join(ROOT_DIR,"**.lua"),
    path.join(ROOT_DIR,"**.png"),
    path.join(ROOT_DIR,"**.ttf"),
    path.join(ROOT_DIR,"**.wav"),
    path.join(ROOT_DIR,"**.mp3"),
    path.join(ROOT_DIR,"**.mp4"),
  }
  includedirs {
    ".",
    "olcTemplate/sdk/box2d/include",
    "olcTemplate/sdk/imgui-1.90.4",
    "olcTemplate/sdk/imgui-1.90.4/backends",
    "olcTemplate/sdk/sol2-3.3.0",
    "olcTemplate/sdk/lua-5.4.2/include",
    "olcTemplate/sdk/soloud/include",
    "olcTemplate/sdk/freetype-2.13.1/include",
    "olcTemplate/sdk/lz4-1.10.0",
  }

  configuration "windows"
    debugdir (ROOT_DIR)
    includedirs {
    }
    libdirs {
      "olcTemplate/sdk/box2d/windows",
      "olcTemplate/sdk/freetype-2.13.1/windows",
      "olcTemplate/sdk/lua-5.4.2/windows",
      "olcTemplate/sdk/soloud/windows",
    }
    links {
      "freetype",
      "lua54",
      "soloud_static_x64"
    }
    buildoptions {
      "/wd4244", -- Konvertierung, möglicher Datenverlust
      "/wd4267", -- Konvertierung, möglicher Datenverlust
  }

  configuration "linux"
    includedirs {
      "/usr/include",
    }
    libdirs {
      "/usr/lib",
      "olcTemplate/sdk/box2d/linux",
      "olcTemplate/sdk/lua-5.4.2/linux",
      "olcTemplate/sdk/soloud/linux",
    }
    links {
       "freetype",
       "X11",
       "GL",
       "pthread",
       "png",
       "stdc++fs",
       "lua54",
       "dl",
       "soloud_static",
       "asound",
       "box2d",
    }

  configuration { "windows", "Debug" }
    links {
      "box2dD",
    }
  configuration { "windows", "Test" }
    links {
      "box2dD",
    }
  configuration { "windows", "Release" }
    links {
      "box2d",
    }
 
  configuration "macosx"
    debugdir (ROOT_DIR)
    buildoptions_cpp {
      "-Wall",
    }
    includedirs {
      "/usr/local/Cellar/libpng/1.6.43/include"
    }
    libdirs {
      "/usr/local/Cellar/freetype/2.13.2/lib",
      "/usr/local/Cellar/libpng/1.6.43/lib",
      "olcTemplate/sdk/box2d/macos",
      "olcTemplate/sdk/lua-5.4.2/macos",
      "olcTemplate/sdk/soloud/macos",
    }
    links {
       "box2d",
       "freetype",
       "png",
       "lua",
       "soloud_static",
       "OpenGL.framework",
       "GLUT.framework",
       "Carbon.framework",
       "AudioToolbox.framework",
    }
    xcodecopyframeworks {
      "OpenGL.framework",
      "GLUT.framework",
      "Carbon.framework",
      "AudioToolbox.framework",
    }

  configuration {}