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
   toolset "clang"
   buildoptions {"-Wall"}

   targetdir ("./bin/" .. "%{cfg.system}/" .. outputdir)
   objdir ("./bin-int/" .. "%{cfg.system}/" .. outputdir)

   links {
     "SDL2",
   }

   includedirs {
      "./src/**",
      "./vendor/"
   }

   files {
      "./src/**.hpp",
      "./src/**.cpp"
   }

   filter "system:linux"
      defines {
         "GK_LINUX_BUILD"
      }

   filter "system:macosx"
      defines {
         "GK_OSX_BUILD"
      }

   filter "configurations:Debug"
      symbols "On"
      defines {
          "DEBUG"
      }
