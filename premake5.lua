workspace "Game"
   configurations { "Debug", "Release" }
   platforms { "Win64"}

project "Game"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   characterset ("Unicode")
   buildoptions { "/utf-8" }
   -- architecture "x86_64"

   -- includedirs { "vcpkg_installed/x64-windows/include" }
   -- libdirs { "vcpkg_installed/x64-windows/lib" }
   links { "raylib" }

   files { "src/**.h", "src/**.c" }



   filter "platforms:Win64" 
      system "Windows"
      architecture "x86_64"
      libdirs { "vcpkg_installed/x64-windows/lib" }
      includedirs { "vcpkg_installed/x64-windows/include" }
      postbuildcommands { 
         "{COPYFILE} vcpkg_installed/x64-windows/bin/*.dll %{cfg.targetdir}" 
      }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"