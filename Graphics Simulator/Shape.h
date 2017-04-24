/*
	도형정보를 정의하는 기본 자료형
*/
#pragma once


#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"
#include "Coordinates.h"

#include <string>


namespace QuadCore
{

class Shape
{
public:
	Shape() : shape_path("../media/shape/")
	{}
	virtual ~Shape() {}
	
public:
	virtual void transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3(1,1,1)) = 0;
	virtual void Draw(QuadCore::Camera* camera) = 0;

	virtual QuadCore::Transform* GetTransform()
	{
		return m_transform;
	}

	virtual void position(glm::vec3 position)
	{
		m_transform->SetPos(position);
	}

	virtual void rotate(glm::vec3 rotation)
	{
		m_transform->SetRot(rotation);
	}

	virtual void scale(glm::vec3 scale)
	{
		m_transform->SetScale(scale);
	}

protected:

	QuadCore::Transform*	m_transform;
	QuadCore::Mesh*			m_mesh;

	QuadCore::Shader*		m_shader;
	QuadCore::Texture*		m_texture;

	Coordinates* m_coordinate;

	//int m_shader;
	//int m_texture;

	//Collider collider;
	//Physics* physics;

	//QuadCore::Shader*		m_shader;
	//QuadCore::Texture*		m_texture;	

	std::string shape_path;
};

}



/*
Cone
ConeHalf
ConeHexagon
ConePentagon
Cross
Cube
CubeCorner
CubeCornerThin
CubeEdgeIn
CubeEdgeOut
CubeHollow
CubeHollowThin
CubeTube
Cylinder
CylinderHalf
CylinderTube
CylinderTubeThin
Heart
Icosphere
IcosphereSmall
PrismHexagon
PrismOctagon
PrismTriangle
Pyramid
PyramidCorner
PyramidTri
Sphere
SphereHalf
Star
Torus
TorusHalf
Wedge
*/