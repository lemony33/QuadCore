#include "UI_TwBar.h"

const float FLOAT_2PI = 6.283185307f; // 2*PI

// Constructor
Scene::Scene()
	: g_MatAmbient{ 0.5f, 0.0f, 0.0f, 1.0f }
{
	// Set scene members.
	// The scene will be created by Scene::Init( )
	Wireframe = false;
	Subdiv = 20;
	NumLights = 0;
	BgColor0[0] = 0.0f;
	BgColor0[1] = 0.0f;
	BgColor0[2] = 0.3f;
	BgColor1[0] = 0.3f;
	BgColor1[1] = 0.0f;
	BgColor1[2] = 0.0f;

	Ambient = 0.2f;
	Reflection = 0.5f;
	RotYAngle = 0;
	Rotation = ROT_CCW;
	objList = 0;
	groundList = 0;
	haloList = 0;
	maxLights = 0;
	lights = NULL;
	lightsBar = NULL;
}

// Destructor
Scene::~Scene()
{
	// delete all lights
	if (lights)
		delete[] lights;
}

// Light Bar 초기화
void Scene::Init(bool changeLights)
{
	// Get the max number of lights allowed by the graphic card
	glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
	if (maxLights>16)
		maxLights = 16;

	// Create the lights array
	if (lights == NULL && maxLights>0)
	{
		lights = new Light[maxLights];
		NumLights = 3;               // default number of lights
		if (NumLights>maxLights)
			NumLights = maxLights;
		changeLights = true;         // force lights initialization

		// Create a tweak bar for lights
		CreateBar();
	}

	// (Re)initialize lights if needed (uses random values)
	if (changeLights)
		for (int i = 0; i<maxLights; ++i)
		{
			lights[i].Dist0 = 0.5f*(float)rand() / RAND_MAX + 0.55f;
			lights[i].Angle0 = FLOAT_2PI*((float)rand() / RAND_MAX);
			lights[i].Height0 = FLOAT_2PI*(float)rand() / RAND_MAX;
			lights[i].Speed0 = 4.0f*(float)rand() / RAND_MAX - 2.0f;
			lights[i].Animation = (Light::AnimMode)(Light::ANIM_BOUNCE + (rand() % 3));
			lights[i].Radius = (float)rand() / RAND_MAX + 0.05f;
			lights[i].Color[0] = (float)rand() / RAND_MAX;
			lights[i].Color[1] = (float)rand() / RAND_MAX;
			lights[i].Color[2] = (lights[i].Color[0]>lights[i].Color[1]) ? 1.0f - lights[i].Color[1] : 1.0f - lights[i].Color[0];
			lights[i].Color[3] = 1;
			lights[i].Active = true;
		}

	// Initialize some OpenGL states
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Create objects display list using the current Subdiv parameter to control the tesselation
	if (objList>0)
		glDeleteLists(objList, 1);      // delete previously created display list
	objList = glGenLists(1);
	glNewList(objList, GL_COMPILE);
	///DrawSubdivCylinderY(-0.9f, 0, -0.9f, 1.4f, 0.15f, 0.12f, Subdiv / 2 + 8, Subdiv);
	///DrawSubdivCylinderY(+0.9f, 0, -0.9f, 1.4f, 0.15f, 0.12f, Subdiv / 2 + 8, Subdiv);
	///DrawSubdivCylinderY(+0.9f, 0, +0.9f, 1.4f, 0.15f, 0.12f, Subdiv / 2 + 8, Subdiv);
	///DrawSubdivCylinderY(-0.9f, 0, +0.9f, 1.4f, 0.15f, 0.12f, Subdiv / 2 + 8, Subdiv);
	///DrawSubdivCylinderY(0, 0, 0, 0.4f, 0.5f, 0.3f, Subdiv + 16, Subdiv / 8 + 1);
	///DrawSubdivCylinderY(0, 0.4f, 0, 0.05f, 0.3f, 0.0f, Subdiv + 16, Subdiv / 16 + 1);
	glEndList();

	// Create ground display list
	if (groundList>0)
		glDeleteLists(groundList, 1);   // delete previously created display list
	groundList = glGenLists(1);
	glNewList(groundList, GL_COMPILE);
	///DrawSubdivPlaneY(-1.2f, 1.2f, 0, -1.2f, 1.2f, (3 * Subdiv) / 2, (3 * Subdiv) / 2);
	glEndList();

	// Create display list to draw light halos
	if (haloList>0)
		glDeleteLists(haloList, 1);     // delete previously created display list
	haloList = glGenLists(1);
	glNewList(haloList, GL_COMPILE);
	///DrawSubdivHaloZ(0, 0, 0, 1, 32);
	glEndList();
}

// Callback function associated to the 'Change lights' button of the lights tweak bar.
void TW_CALL ReinitCB(void *clientData)
{
	Scene *scene = static_cast<Scene *>(clientData); // scene pointer is stored in clientData
	scene->Init(true);                               // re-initialize the scene
}

// Light Bar 생성
void Scene::CreateBar()
{
	// Light parameter
	float g_LightDirection[] = { -0.57735f, -0.57735f, -0.57735f };

	// Bar 이름
	lightsBar = TwNewBar("Lights");
	TwDefine(" Lights label='LIGHTS' position='20 400' alpha=0 help='Use this bar to edit the lights in the scene.' ");

	// light 갯수 추가 하기 
	TwAddVarRW(lightsBar, "NumLights", TW_TYPE_INT32, &NumLights,
		" label='Number of lights' keyIncr=l keyDecr=L help='Changes the number of lights in the scene.' ");

	// light 갯수 최대, 최소값 
	int zero = 0;
	TwSetParam(lightsBar, "NumLights", "min", TW_PARAM_INT32, 1, &zero);
	TwSetParam(lightsBar, "NumLights", "max", TW_PARAM_INT32, 1, &maxLights);

	TwAddSeparator(lightsBar, "", NULL); // 아래쪽에 line생성

	// 추가 된 light 색깔 랜덤으로 바꾸기 
	TwAddButton(lightsBar, "Reinit", ReinitCB, this,
		" label='Change lights' key=c help='Random changes of lights parameters.' ");

	TwAddSeparator(lightsBar, "", NULL);

	// light 애니메이션 모드 -> 선택가능 
	TwEnumVal modeEV[] = // Scene::AnimMode enum values
	{
		{ Light::ANIM_FIXED,    "Fixed" },
		{ Light::ANIM_BOUNCE,   "Bounce" },
		{ Light::ANIM_ROTATE,   "Rotate" },
		{ Light::ANIM_COMBINED, "Combined" }
	};
	TwType modeType = TwDefineEnum("Mode", modeEV, 4);

	// 추가 된 각 light의 속성 
	TwStructMember lightMembers[] = // Light structure
	{
		{ "Active",    TW_TYPE_BOOLCPP, offsetof(Light, Active),    " help='Enable/disable the light.' " },					// Light::Active is a C++ boolean value
		{ "Color",     TW_TYPE_COLOR4F, offsetof(Light, Color),     " noalpha help='Light color.' " },						// Light::Color is represented by 4 floats, but alpha channel should be ignored
		{ "Radius",    TW_TYPE_FLOAT,   offsetof(Light, Radius),    " min=0 max=4 step=0.02 help='Light radius.' " },
		{ "Animation", modeType,        offsetof(Light, Animation), " help='Change the animation mode.' " },				// use the enum 'modeType' created before to tweak the Light::Animation variable
		{ "Speed",     TW_TYPE_FLOAT,   offsetof(Light, Speed0),    " readonly=true help='Light moving speed.' " }			// Light::Speed is made read-only
	};
	TwType lightType = TwDefineStruct("Light", lightMembers, 5, sizeof(Light), NULL, NULL);  // struct defined by the lightMembers array

	// light 증가
	for (int i = 0; i<maxLights; ++i)  // Add 'maxLights' variables of type lightType; 
	{   // unused lights variables (over NumLights) will hidden by Scene::Update( )
		_snprintf(lights[i].Name, sizeof(lights[i].Name), "%d", i + 1);							// Create a name for each light ("1", "2", "3",...)
		TwAddVarRW(lightsBar, lights[i].Name, lightType, &lights[i], " group='Edit lights' ");  // Add a lightType variable and group it into the 'Edit lights' group

																								// Set 'label' and 'help' parameters of the light
		char paramValue[64];
		_snprintf(paramValue, sizeof(paramValue), "Light #%d", i + 1);
		TwSetParam(lightsBar, lights[i].Name, "label", TW_PARAM_CSTRING, 1, paramValue); // Set label
		_snprintf(paramValue, sizeof(paramValue), "Parameters of the light #%d", i + 1);
		TwSetParam(lightsBar, lights[i].Name, "help", TW_PARAM_CSTRING, 1, paramValue);  // Set help
	}

	TwAddSeparator(lightsBar, "", NULL);

	// light 화살표
	TwAddVarRW(lightsBar, "LightDir", TW_TYPE_DIR3F, &g_LightDirection,
		" label='Light direction' opened=true help='Change the light direction.' ");

	
	// and is inserted into a group named 'Material'.
	TwAddVarRW(lightsBar, "Ambient", TW_TYPE_COLOR3F, &g_MatAmbient, " group='Material' ");
	TwAddVarRW(lightsBar, "Diffuse", TW_TYPE_COLOR3F, &g_MatDiffuse, " group='Material' ");
	TwAddVarRW(lightsBar, "Specular", TW_TYPE_COLOR3F, &g_MatSpecular, " group='Material' ");
	TwAddVarRW(lightsBar, "Shininess", TW_TYPE_COLOR3F, &g_MatShininess, " group='Material' ");

	TwAddSeparator(lightsBar, "", NULL);

	TwAddVarRW(lightsBar, "LigPosition", TW_TYPE_COLOR3F, &g_LigPosition, " group='Light' ");
	TwAddVarRW(lightsBar, "LigAmbient", TW_TYPE_COLOR3F, &g_LigAmbient, " group='Light' ");
	TwAddVarRW(lightsBar, "LigDiffuse", TW_TYPE_COLOR3F, &g_LigDiffuse, " group='Light' ");
	TwAddVarRW(lightsBar, "LigSpecular", TW_TYPE_COLOR3F, &g_LigSpecular, " group='Light' ");
}

// Light Bar Update 
void Scene::Update(double time)
{
	float horizSpeed, vertSpeed;
	for (int i = 0; i<NumLights; ++i)
	{
		// Change light position according to its current animation mode

		if (lights[i].Animation == Light::ANIM_ROTATE || lights[i].Animation == Light::ANIM_COMBINED)
			horizSpeed = lights[i].Speed0;
		else
			horizSpeed = 0;

		if (lights[i].Animation == Light::ANIM_BOUNCE || lights[i].Animation == Light::ANIM_COMBINED)
			vertSpeed = 1;
		else
			vertSpeed = 0;

		lights[i].Pos[0] = lights[i].Dist0 * (float)cos(horizSpeed*time + lights[i].Angle0);
		lights[i].Pos[1] = (float)fabs(cos(vertSpeed*time + lights[i].Height0));
		lights[i].Pos[2] = lights[i].Dist0 * (float)sin(horizSpeed*time + lights[i].Angle0);
		lights[i].Pos[3] = 1;
	}
}

// Activate OpenGL lights; hide unused lights in the Lights tweak bar; 
// and draw the scene. The scene is reflected by the ground plane, so it is
// drawn two times: first reflected, and second normal (unreflected).

// Light Bar & Scene 생성
void Scene::Draw() const
{
	// Rotate the scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(RotYAngle, 0, 1, 0);

	// Hide/active lights
	int i, lightVisible;
	for (i = 0; i<maxLights; ++i)
	{
		if (i<NumLights)
		{
			// Lights under NumLights are shown in the Lights tweak bar
			lightVisible = 1;

			// Tell OpenGL to enable or disable the light
			if (lights[i].Active)
				glEnable(GL_LIGHT0 + i);
			else
				glDisable(GL_LIGHT0 + i);

			// Update OpenGL light parameters (for the reflected scene)
			float reflectPos[4] = { lights[i].Pos[0], -lights[i].Pos[1], lights[i].Pos[2], lights[i].Pos[3] };
			glLightfv(GL_LIGHT0 + i, GL_POSITION, reflectPos);
			glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lights[i].Color);
			glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1);
			glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0);
			glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 1.0f / (lights[i].Radius*lights[i].Radius));
		}
		else
		{
			// Lights over NumLights are hidden in the Lights tweak bar
			lightVisible = 0;

			// Disable the OpenGL light
			glDisable(GL_LIGHT0 + i);

		}

		// Show or hide the light variable in the Lights tweak bar
		TwSetParam(lightsBar, lights[i].Name, "visible", TW_PARAM_INT32, 1, &lightVisible);
	}

	// Set global ambient and clear screen and depth buffer
	float ambient[4] = { Ambient*(BgColor0[0] + BgColor1[0]) / 2, Ambient*(BgColor0[1] + BgColor1[1]) / 2,
						Ambient*(BgColor0[2] + BgColor1[2]) / 2, 1 };
	glClearColor(ambient[0], ambient[1], ambient[2], 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	// Draw the reflected scene
	glPolygonMode(GL_FRONT_AND_BACK, (Wireframe ? GL_LINE : GL_FILL));
	glCullFace(GL_FRONT);
	glPushMatrix();
	glScalef(1, -1, 1);
	glColor3f(1, 1, 1);
	///glCallList(objList);
	///DrawHalos(true);
	glPopMatrix();
	glCullFace(GL_BACK);

	// clear depth buffer again
	//glClear(GL_DEPTH_BUFFER_BIT);

	// Draw the ground plane (using the Reflection parameter as transparency)
	glColor4f(1, 1, 1, 1.0f - Reflection);
	///glCallList(groundList);

	// Draw the gradient background (requires to switch to screen-space normalized coordinates)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	///glBegin(GL_QUADS);
	///glColor3f(BgColor0[0], BgColor0[1], BgColor0[2]);
	///glVertex3f(-1, -1, 0.9f);
	///glVertex3f(1, -1, 0.9f);
	///glColor3f(BgColor1[0], BgColor1[1], BgColor1[2]);
	///glVertex3f(1, 1, 0.9f);
	///glVertex3f(-1, 1, 0.9f);
	///glEnd();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	// Update light positions for unreflected scene
	for (i = 0; i<NumLights; ++i)
		glLightfv(GL_LIGHT0 + i, GL_POSITION, lights[i].Pos);

	// Draw the unreflected scene
	glPolygonMode(GL_FRONT_AND_BACK, (Wireframe ? GL_LINE : GL_FILL));
	glColor3f(1, 1, 1);
	///glCallList(objList);
	///DrawHalos(false);
}



//================ Object 그리기 ==================//

// Subroutine used to draw halos around light positions
void Scene::DrawHalos(bool reflected) const
{
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);
	float prevAmbient[4];
	glGetFloatv(GL_LIGHT_MODEL_AMBIENT, prevAmbient);
	glPushMatrix();
	glLoadIdentity();
	if (reflected)
		glScalef(1, -1, 1);
	float black[4] = { 0, 0, 0, 1 };
	float cr = (float)cos(FLOAT_2PI*RotYAngle / 360.0f);
	float sr = (float)sin(FLOAT_2PI*RotYAngle / 360.0f);
	for (int i = 0; i<NumLights; ++i)
	{
		if (lights[i].Active)
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lights[i].Color);
		else
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
		glPushMatrix();
		glTranslatef(cr*lights[i].Pos[0] + sr*lights[i].Pos[2], lights[i].Pos[1], -sr*lights[i].Pos[0] + cr*lights[i].Pos[2]);
		//glScalef(0.5f*lights[i].Radius, 0.5f*lights[i].Radius, 1);
		glScalef(0.05f, 0.05f, 1);
		///glCallList(haloList);
		glPopMatrix();
	}
	glPopMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, prevAmbient);
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Subroutine used to build the ground plane display list (mesh subdivision is adjustable)
void Scene::DrawSubdivPlaneY(float xMin, float xMax, float y, float zMin, float zMax, int xSubdiv, int zSubdiv) const
{
	const float FLOAT_EPS = 1.0e-5f;
	float dx = (xMax - xMin) / xSubdiv;
	float dz = (zMax - zMin) / zSubdiv;
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	for (float z = zMin; z<zMax - FLOAT_EPS; z += dz)
		for (float x = xMin; x<xMax - FLOAT_EPS; x += dx)
		{
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + dz);
			glVertex3f(x + dx, y, z + dz);
			glVertex3f(x + dx, y, z);
		}
	glEnd();
}

// Subroutine used to build objects display list (mesh subdivision is adjustable)
void Scene::DrawSubdivCylinderY(float xCenter, float yBottom, float zCenter, float height, float radiusBottom, float radiusTop, int sideSubdiv, int ySubdiv) const
{
	float h0, h1, y0, y1, r0, r1, a0, a1, cosa0, sina0, cosa1, sina1;
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int j = 0; j<ySubdiv; ++j)
		for (int i = 0; i<sideSubdiv; ++i)
		{
			h0 = (float)j / ySubdiv;
			h1 = (float)(j + 1) / ySubdiv;
			y0 = yBottom + h0*height;
			y1 = yBottom + h1*height;
			r0 = radiusBottom + h0*(radiusTop - radiusBottom);
			r1 = radiusBottom + h1*(radiusTop - radiusBottom);
			a0 = FLOAT_2PI*(float)i / sideSubdiv;
			a1 = FLOAT_2PI*(float)(i + 1) / sideSubdiv;
			cosa0 = (float)cos(a0);
			sina0 = (float)sin(a0);
			cosa1 = (float)cos(a1);
			sina1 = (float)sin(a1);
			glNormal3f(cosa0, 0, sina0);
			glVertex3f(xCenter + r0*cosa0, y0, zCenter + r0*sina0);
			glNormal3f(cosa0, 0, sina0);
			glVertex3f(xCenter + r1*cosa0, y1, zCenter + r1*sina0);
			glNormal3f(cosa1, 0, sina1);
			glVertex3f(xCenter + r1*cosa1, y1, zCenter + r1*sina1);
			glNormal3f(cosa1, 0, sina1);
			glVertex3f(xCenter + r0*cosa1, y0, zCenter + r0*sina1);
		}
	glEnd();
}

// Subroutine used to build halo display list
void Scene::DrawSubdivHaloZ(float x, float y, float z, float radius, int subdiv) const
{
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 0);
	glColor4f(1, 1, 1, 1);
	glVertex3f(x, y, z);
	for (int i = 0; i <= subdiv; ++i)
	{
		glColor4f(1, 1, 1, 0);
		glVertex3f(x + radius*(float)cos(FLOAT_2PI*(float)i / subdiv), x + radius*(float)sin(FLOAT_2PI*(float)i / subdiv), z);
	}
	glEnd();
}

// Callback function called when the 'Subdiv' variable value of the main tweak bar has changed.
void TW_CALL SetSubdivCB(const void *value, void *clientData)
{
	Scene *scene = static_cast<Scene *>(clientData);    // scene pointer is stored in clientData
	scene->Subdiv = *static_cast<const int *>(value);   // copy value to scene->Subdiv
	scene->Init(false);                                 // re-init scene with the new Subdiv parameter
}

// Callback function called by the main tweak bar to get the 'Subdiv' value
void TW_CALL GetSubdivCB(void *value, void *clientData)
{
	Scene *scene = static_cast<Scene *>(clientData);    // scene pointer is stored in clientData
	*static_cast<int *>(value) = scene->Subdiv;         // copy scene->Subdiv to value
}

