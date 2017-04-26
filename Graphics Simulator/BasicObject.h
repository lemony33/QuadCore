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


		std::string filename = shape_path + m_shape_name + ".obj";
		m_mesh = new Mesh(filename);
		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../media/new_shader/basicShader_light");
		m_texture = new Texture("../media/res/bricks.jpg");
	}

	BasicObject(std::string mesh_name, std::string shader_name, std::string texture_name, Transform* transform = new Transform())
	{
		m_transform = transform;
		m_coordinate = new Coordinates(1.0f);

		using std::string;

		string file_name_mesh = shape_path + mesh_name + ".obj";
		m_mesh = new Mesh(file_name_mesh);

		string file_name_shader = "../media/new_shader/" + shader_name;
		m_shader = new Shader(file_name_shader);

		string file_name_texture = "../media/res/" + texture_name + ".jpg";
		m_texture = new Texture(file_name_texture);
	}

public:
	void Init()
	{
		
	}
	void SetMesh()
	{
		std::string filename = shape_path + m_shape_name + ".obj";
		m_mesh = new Mesh(filename);
	}
	void SetShader()
	{
		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../media/new_shader/basicShader_light");
	}
	void SetTexture()
	{
		m_texture = new Texture("../media/res/bricks.jpg");
	}


public:	

	virtual void Draw(QuadCore::Camera* camera)
	{
		m_shader->Bind();
		m_texture->Bind(0);

		m_shader->Update(*m_transform, *camera);
		m_mesh->Draw();

		m_coordinate->Init_Link(m_transform, camera);
		m_coordinate->Draw(3.0f);
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
