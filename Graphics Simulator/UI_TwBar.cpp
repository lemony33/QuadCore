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
	if (maxLights>3)
		maxLights = 3;

	// Create the lights array
	if (multilights == NULL && maxLights>0)
	{
		multilights = new MultiLight[maxLights];
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
			multilights[i].posX = 0;
			multilights[i].posY = 0;
			multilights[i].posZ = 0;
			multilights[i].ambient[0] = (float)rand() / RAND_MAX;
			multilights[i].ambient[1] = (float)rand() / RAND_MAX;
			multilights[i].ambient[2] = (multilights[i].ambient[0]>multilights[i].ambient[1]) ? 1.0f - multilights[i].ambient[1] : 1.0f - multilights[i].ambient[0];
			multilights[i].ambient[3] = 1;
			multilights[i].diffuse[0] = (float)rand() / RAND_MAX;
			multilights[i].diffuse[1] = (float)rand() / RAND_MAX;
			multilights[i].diffuse[2] = (multilights[i].diffuse[0]>multilights[i].diffuse[1]) ? 1.0f - multilights[i].diffuse[1] : 1.0f - multilights[i].diffuse[0];
			multilights[i].diffuse[3] = 1;
			multilights[i].specular[0] = (float)rand() / RAND_MAX;
			multilights[i].specular[1] = (float)rand() / RAND_MAX;
			multilights[i].specular[2] = (multilights[i].specular[0]>multilights[i].specular[1]) ? 1.0f - multilights[i].specular[1] : 1.0f - multilights[i].specular[0];
			multilights[i].specular[3] = 1;
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
	TwDefine(" Lights label='LIGHTS' size ='245 450' position='30 450' alpha=0 help='Use this bar to edit the lights in the scene.' ");

	// 추가 될 각 multilight의 속성 
	TwStructMember lightMembers[] = // Light structure
	{
		{ "Pos - X",     TW_TYPE_FLOAT, offsetof(MultiLight, posX),     " min=-500.00 max=500.00 step=0.1 help='Light PositionX.' " },
		{ "Pos - Y",     TW_TYPE_FLOAT, offsetof(MultiLight, posY),     " min=-500.00 max=500.00 step=0.1 help='Light PositionY.' " },
		{ "Pos - Z",     TW_TYPE_FLOAT, offsetof(MultiLight, posZ),     " min=-500.00 max=500.00 step=0.1 help='Light PositionZ.' " },
		
		{ "Ambient",     TW_TYPE_COLOR3F, offsetof(MultiLight, ambient),     " help='Light Ambient.' " },
		{ "Diffuse",     TW_TYPE_COLOR3F, offsetof(MultiLight, diffuse),     " help='Light Diffuse.' " },
		{ "Specular",     TW_TYPE_COLOR3F, offsetof(MultiLight, specular),     " help='Light Specular.' " }			// Light::Speed is made read-only
	};
	TwType lightType = TwDefineStruct("MultiLight", lightMembers, 6, sizeof(MultiLight), NULL, NULL);  // struct defined by the lightMembers array

	// light 갯수만큼 메뉴 생성
	for (int i = 0; i<3; ++i)  // Add 'maxLights' variables of type lightType; 
	{   // unused lights variables (over NumLights) will hidden by Scene::Update( )
		_snprintf(multilights[i].Name, sizeof(multilights[i].Name), "%d", i + 1);							// Create a name for each light ("1", "2", "3",...)
		TwAddVarRW(lightsBar, multilights[i].Name, lightType, &multilights[i], " opened=true group='Edit lights' ");  // Add a lightType variable and group it into the 'Edit lights' group

																								// Set 'label' and 'help' parameters of the light
		char paramValue[64];
		_snprintf(paramValue, sizeof(paramValue), "Light #%d", i + 1);
		TwSetParam(lightsBar, multilights[i].Name, "label", TW_PARAM_CSTRING, 1, paramValue); // Set label
		_snprintf(paramValue, sizeof(paramValue), "Parameters of the light #%d", i + 1);
		TwSetParam(lightsBar, multilights[i].Name, "help", TW_PARAM_CSTRING, 1, paramValue);  // Set help
	}

	TwAddSeparator(lightsBar, "", NULL);

}

///////////////////////////////////////필요없고 헤더파일 수정하기 귀찮아서 냅둠 ///////////////////////////////
// Light Bar Update 
void Scene::Update(double time)
{
	float horizSpeed, vertSpeed;
}

// Activate OpenGL lights; hide unused lights in the Lights tweak bar; 
// and draw the scene. The scene is reflected by the ground plane, so it is
// drawn two times: first reflected, and second normal (unreflected).

// Light Bar & Scene 생성
void Scene::Draw() const
{
	
}



//================ Object 그리기 ==================//

// Subroutine used to draw halos around light positions
void Scene::DrawHalos(bool reflected) const
{
}

// Subroutine used to build the ground plane display list (mesh subdivision is adjustable)
void Scene::DrawSubdivPlaneY(float xMin, float xMax, float y, float zMin, float zMax, int xSubdiv, int zSubdiv) const
{
}

// Subroutine used to build objects display list (mesh subdivision is adjustable)
void Scene::DrawSubdivCylinderY(float xCenter, float yBottom, float zCenter, float height, float radiusBottom, float radiusTop, int sideSubdiv, int ySubdiv) const
{
}

// Subroutine used to build halo display list
void Scene::DrawSubdivHaloZ(float x, float y, float z, float radius, int subdiv) const
{
}

// Callback function called when the 'Subdiv' variable value of the main tweak bar has changed.
void TW_CALL SetSubdivCB(const void *value, void *clientData)
{                             // re-init scene with the new Subdiv parameter
}

// Callback function called by the main tweak bar to get the 'Subdiv' value
void TW_CALL GetSubdivCB(void *value, void *clientData)
{
}

