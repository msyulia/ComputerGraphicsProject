workspace "GK_Projects"
   architecture "x64"

   configurations { 
      "Debug",
   }

outputdir = "%{cfg.buildcfg}"

project "p2"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   targetdir ("./bin/" .. outputdir)
   objdir ("./bin-int/" .. outputdir)

   links {
      "SDL2",
   }

   includedirs {
      "./src/**",
      "%{prj.name}/vendor/"
   }

   files { 
      "./src/**.hpp",
      "./src/**.cpp" 
   }

   filter "system:linux"
      defines {
         "GK_LINUX_BUILD"
      }

   filter "configurations:Debug"
      symbols "On"
      defines {
          "DEBUG" 
      }