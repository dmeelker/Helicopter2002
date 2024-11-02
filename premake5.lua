workspace "Helicopter2002"
   configurations { "Debug", "Release" }
   platforms { "Win64"}

project "Helicopter2002"
   
   language "C"
   cdialect  "C17"
   targetdir "bin/%{cfg.buildcfg}"

   characterset ("Unicode")
   buildoptions { "/utf-8" }

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
      kind "ConsoleApp"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      staticruntime "on"
      kind "WindowedApp"
      entrypoint "mainCRTStartup"