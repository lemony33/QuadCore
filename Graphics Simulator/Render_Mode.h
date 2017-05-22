#pragma once


enum OBJECT_MODE 
{
	Bunny, Lucy, Lucycat, Lucycat_voronol,
	bear, nanosuit,
	glove, chair, WineGlasses,
	Torus, Cube, Sphere, Icosphere, CubeHollow,

	Custom1, Custom2, Custom3,

	OBJECT_MODE_SIZE
};

enum SHADER_MODE
{ 
	Phong, Multi, Rim,

	SHADER_MODE_SIZE
};

enum TEXTURE_MODE
{
	Bricks, Skyblue, Formula,
	dark_spot, diamond, grain_grass, iron, lines_dark, metal, moon,
	slime, surface_dark, surface_gold_shine, pastel, wall_brick, wood,

	TEXTURE_MODE_SIZE
};

enum EFFECT_MODE
{
	EFFECT_OFF, EFFECT_PAUSE,
	EXPLODE, NORMAL_VIEW,

	EFFECT_MODE_SIZE
};


enum SHADING_MODE
{
	FLAT, SMOOTH, PN_TRIANGLE,
	
	
	TEST_CODE,

	SHADING_MODE_SIZE
};