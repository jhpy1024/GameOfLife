solution "GameOfLife"
	configurations { "Debug", "Release" }
	location "build/"

	project "GameOfLife"
		kind "ConsoleApp"
		language "C++"
		files { "src/*.cpp" }
		includedirs { "include" }
		links { "sfml-graphics", "sfml-window", "sfml-system", "jpeg", "GLEW" }
		location "build/"
		buildoptions "-std=c++11 -Wno-narrowing"

		configuration "Debug"
			flags { "ExtraWarnings" }

		configuration "Release"
			flags { "Optimize" }
