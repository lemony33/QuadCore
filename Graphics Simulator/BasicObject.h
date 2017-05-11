#pragma once

#include "iShape.h"


namespace QuadCore
{
	
	
class BasicObject : public iShape
{
public:
	BasicObject(glm::vec3 position, int figure_num)
	{
		this->SetName();
		
		m_transform = new Transform(position);
		m_coordinate = new Coordinates(1.0f);
		
		m_shape_name = objects[figure_num];
		
		//shape_path("../resources/objects/")

		std::string filename = shape_path + "BasicObjects/" + m_shape_name + ".obj";
		m_mesh = new Mesh(filename);
		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../resources/shaders/basicShader_light");
		m_texture = new Texture("../resources/textures/bricks.jpg");
	}

	BasicObject(std::string mesh_name, std::string shader_name, std::string texture_name, Transform* transform = new Transform())
	{
		m_transform = transform;
		m_coordinate = new Coordinates(1.0f);

		using std::string;
		
		//shape_path("../resources/objects/")


		string file_name_shader = "../resources/shaders/" + shader_name;
		m_shader = new Shader(file_name_shader);

		string file_name_texture = "../resources/textures/" + texture_name + ".jpg";
		m_texture = new Texture(file_name_texture);



		string file_name_mesh = shape_path + mesh_name + ".obj";
		m_mesh = new Mesh(file_name_mesh);
	}

public:
	void Init(std::string mesh_name, std::string shader_name, std::string texture_name, Transform* transform = new Transform())
	{
		// 1. 기존 데이터들을 다른 포인터에 연결
		Transform*		prev_transform = m_transform;
		Coordinates*	prev_coordinate = m_coordinate;
		Mesh*		prev_mesh = m_mesh;
		Shader*		prev_shader = m_shader;
		Texture*	prev_texture = m_texture;


		m_transform = transform;
		m_coordinate = new Coordinates(1.0f);

		using std::string;

		//shape_path("../resources/objects/")

		string file_name_mesh = shape_path + mesh_name + ".obj";
		m_mesh = new Mesh(file_name_mesh);

		string file_name_shader = "../resources/shaders/" + shader_name;
		m_shader = new Shader(file_name_shader);

		string file_name_texture = "../resources/textures/" + texture_name + ".jpg";
		m_texture = new Texture(file_name_texture);


		delete(prev_transform);
		delete(prev_coordinate);
		delete(prev_mesh);
		delete(prev_shader);
		delete(prev_texture);

		prev_transform = NULL;
		prev_coordinate = NULL;
		prev_mesh = NULL;
		prev_shader = NULL;
		prev_texture = NULL;
	}
	void SetMesh()
	{
		std::string filename = shape_path + m_shape_name + ".obj";
		m_mesh = new Mesh(filename);
	}
	void SetShader()
	{
		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../resources/shaders/basicShader_light");
	}
	void SetTexture()
	{
		m_texture = new Texture("../resources/textures/bricks.jpg");
	}


public:	

	virtual void Draw(QuadCore::Camera* camera, bool enable_coor)
	{
		m_shader->Bind();
		m_texture->Bind(0);

		m_shader->Update(*m_transform, *camera);
		m_mesh->Draw();

		if (enable_coor)
		{
			m_coordinate->Init_Link(m_transform, camera);
			m_coordinate->Draw(3.0f);
		}
	}

public:
	enum FIGURE
	{
		Cone,
		ConeHalf,
		ConeHexagon,
		ConePentagon,
		Cross,
		Cube,
		CubeCorner,
		CubeCornerThin,
		CubeEdgeIn,
		CubeEdgeOut,
		CubeHollow,
		CubeHollowThin,
		CubeTube,
		Cylinder,
		CylinderHalf,
		CylinderTube,
		CylinderTubeThin,
		Heart,
		Icosphere,
		IcosphereSmall,
		PrismHexagon,
		PrismOctagon,
		PrismTriangle,
		Pyramid,
		PyramidCorner,
		PyramidTri,
		Sphere,
		SphereHalf,
		Star,
		Torus,
		TorusHalf,
		Wedge,

		NUM_FIGURE
	};

private:
	std::string objects[NUM_FIGURE];

	void SetName()
	{
		objects[Cone]				= "Cone";
		objects[ConeHalf]			= "ConeHalf";		
		objects[ConeHexagon]		= "ConeHexagon";
		objects[ConePentagon]		= "ConePentagon";
		objects[Cross]				= "Cross";
		objects[Cube]				= "Cube";
		objects[CubeCorner]			= "CubeCorner";
		objects[CubeCornerThin]		= "CubeCornerThin";
		objects[CubeEdgeIn]			= "CubeEdgeIn";
		objects[CubeEdgeOut]		= "CubeEdgeOut";
		objects[CubeHollow]			= "CubeHollow";
		objects[CubeHollowThin]		= "CubeHollowThin";
		objects[CubeTube]			= "CubeTube";
		objects[Cylinder]			= "Cylinder";
		objects[CylinderHalf]		= "CylinderHalf";
		objects[CylinderTube]		= "CylinderTube";
		objects[CylinderTubeThin]	= "CylinderTubeThin";
		objects[Heart]				= "Heart";
		objects[Icosphere]			= "Icosphere";
		objects[IcosphereSmall]		= "IcosphereSmall";
		objects[PrismHexagon]		= "PrismHexagon";
		objects[PrismOctagon]		= "PrismOctagon";
		objects[PrismTriangle]		= "PrismTriangle";
		objects[Pyramid]			= "Pyramid";
		objects[PyramidCorner]		= "PyramidCorner";
		objects[PyramidTri]			= "PyramidTri";
		objects[Sphere]				= "Sphere";
		objects[SphereHalf]			= "SphereHalf";
		objects[Star]				= "Star";
		objects[Torus]				= "Torus";
		objects[TorusHalf]			= "TorusHalf";
		objects[Wedge]				= "Wedge";
	}

	
};

}
