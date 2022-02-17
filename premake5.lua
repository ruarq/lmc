workspace "lmc"
	configurations { "debug", "release", "tracy" }

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

	filter { "configurations:tracy" }
		optimize "Speed"
		symbols "On"
		files { "tracy/TracyClient.cpp" }
		defines { "TRACY_ENABLE", "TRACY_NO_EXIT=1" }
		links { "pthread", "dl" }
