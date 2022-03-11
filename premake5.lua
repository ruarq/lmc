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

	filter { "system:macosx" }
		buildoptions { "`pkg-config fmt --cflags`" }
		linkoptions { "`pkg-config fmt --libs-only-L`" }

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "Speed"

	filter { "configurations:tracy" }
		optimize "Speed"
		symbols "On"
		files { "tracy/TracyClient.cpp" }
		defines { "TRACY_ENABLE", "TRACY_NO_EXIT=1" }
		links { "pthread", "dl" }
