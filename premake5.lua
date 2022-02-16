workspace "lmc"
	configurations { "debug", "release" }

project "lmc"
	kind "ConsoleApp"
	toolset "clang"
	language "C++"
	cppdialect "C++17"
	warnings "Extra"

	links { "fmt" }

	files { "src/**.hpp", "src/**.cpp" }

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "Speed"
		defines { "DEBUG" }
