workspace "mtlx"
	architecture "x64"
	startproject "Sandbox"

	configurations { 
		"Debug", "Release" 
	}

	flags { 
		"MultiProcessorCompile" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "mtlx"
	location "mtlx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs { 
		"%{prj.name}/src"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MTLX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MTLX_RELEASE"
		runtime "Release"
		optimize "speed"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs {
		"mtlx/src"
	}

	links {
		"mtlx"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MTLX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MTLX_RELEASE"
		runtime "Release"
		optimize "on"