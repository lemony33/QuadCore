#ifndef TWBAR_H
#define TWBAR_H

#include <AntTweakBar.h>
#include <GLEW-2.0.0_x64/GL/glew.h>

#define _snprintf snprintf
/*
struct Light
{
	bool    Active;					// light On or Off
	float   Pos[4];					// light position (in homogeneous coordinates, ie. Pos[4]=1)
	float   Color[4];				// light color (no alpha, ie. Color[4]=1)
	float   Radius;					// radius of the light influence area 
	float   Dist0, Angle0, Height0, Speed0; // light initial cylindrical coordinates and speed
	char    Name[4];				// light short name (will be named "1", "2", "3",...)
	enum    AnimMode { ANIM_FIXED, ANIM_BOUNCE, ANIM_ROTATE, ANIM_COMBINED };
	AnimMode Animation;				// light animation mode
	float specular[4];
};

struct MultiLight
{
	char    Name[4];				// light short name (will be named "1", "2", "3",...)
	float posX;
	float posY;
	float posZ;
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

class Scene
{
public:
	bool    Wireframe;				// draw scene in wireframe or filled
	int     Subdiv;					// number of subdivisions used to tessellate the scene
	int     NumLights;				// number of dynamic lights
	float   BgColor0[3], BgColor1[3]; // top and bottom background colors

	float	cubeColor[4];
	float	g_MatAmbient[4];
	float	g_MatDiffuse[4];
	float	g_MatSpecular[4];
	float	g_MatShininess[4];

	float	g_LigPosition[4];
	float	g_LigAmbient[4];
	float	g_LigDiffuse[4];
	float	g_LigSpecular[4];


	float   Ambient;				// scene ambient factor 
	float   Reflection;				// ground plane reflection factor (0=no reflection, 1=full reflection)
	double  RotYAngle;				// rotation angle of the scene around its Y axis (in degree)
	//enum    RotMode { ROT_OFF, ROT_CW, ROT_CCW };
	//RotMode Rotation;				// scene rotation mode (off, clockwise, counter-clockwise)

	Scene();                        // constructor
	~Scene();                       // destructor
	void    Init(bool changeLightPos);      // (re)initialize the scene

	double speed = 0.3; // Model rotation speed
	double time = 0, dt;// Current time and enlapsed time
	double turn = 0;    // Model turn counter

	//본 프로젝트에 맞춘 추가적인 변수들
	int BackgroundNum_prev = 0;
	int BackgroundNum = 0;
	int SceneNumber = 0;
	int Spheres = 5;
	MultiLight * multilights;

private:
	void    CreateBar();                    // create a tweak bar for lights

											// Some drawing subroutines
	void    DrawSubdivPlaneY(float xMin, float xMax, float y, float zMin, float zMax, int xSubdiv, int zSubdiv) const;
	void    DrawSubdivCylinderY(float xCenter, float yBottom, float zCenter, float height, float radiusBottom, float radiusTop, int sideSubdiv, int ySubdiv) const;
	void    DrawSubdivHaloZ(float x, float y, float z, float radius, int subdiv) const;
	void    DrawHalos(bool reflected) const;

	GLuint  objList, groundList, haloList;  // OpenGL display list IDs
	int     maxLights;                      // maximum number of dynamic lights allowed by the graphic card
	Light * lights;                         // array of lights
	TwBar * lightsBar;                      // pointer to the tweak bar for lights created by CreateBar()
	
};
*/
#endif