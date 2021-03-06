#pragma once

//#include "Texture.h"
#include "iShape.h"
#include <vector>

#include "BasicObject.h"

namespace QuadCore
{

class ShapeManager
{
public:
	ShapeManager() {}
	virtual ~ShapeManager() {}

	//// 晦獄紫⑽擊 賅舒 轎溘ж朝 纔蝶お 囀萄
	void Insert_TestObjects()
	{
		for (int i = 0; i < BasicObject::FIGURE::NUM_FIGURE; i++)
		{
			m_shape_list.push_back(new BasicObject(glm::vec3( sinf((float)i)*13.0f, -3.0f, cosf((float)i)*13.0f), i ));
		}
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天	
	// 僭羹蒂 葬蝶お縑 蹺陛и棻
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Insert_Object_BasicShape(glm::vec3 pos, int figure_num = BasicObject::FIGURE::Cube)
	{
		m_shape_list.push_back(new BasicObject(pos, figure_num));
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天	
	// 僭羹蒂 葬蝶お縑 蹺陛и棻
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Insert_Object(iShape* shape)
	{
		m_shape_list.push_back(shape);
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 摹鷗и 僭羹蒂 葬蝶お縑憮 餉薯и棻
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Delete_Objet(int index)
	{
		m_shape_list.erase(m_shape_list.begin()+index);
	}


	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 摹鷗и 僭羹蒂 葬蝶お縑憮 滲唳и棻
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Modify_Objet(int index, iShape* shape)
	{
		m_shape_list.erase(m_shape_list.begin() + index);

		std::vector<iShape*>::iterator it = m_shape_list.begin();
		m_shape_list.insert(it, shape);

		//// 晦襄 螃粽薛お蒂 棻艇 ん檣攪縑 翱唸
		//iShape* tShape = m_shape_list.at(index);

		//// ⑷營 ん檣攪縑 億煎遴 螃粽薛お蒂 翱唸
		//m_shape_list.at(index) = shape;

		//// 晦襄 螃粽薛お蒂 薯剪
		//delete(tShape);
		//tShape = NULL;
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//  摹鷗и 僭羹曖 輿模高擊 奩�納挬�.
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	iShape* GetObject(int index)
	{
		if (index<0 || index>m_shape_list.size() - 1)	// 螃盟籀葬
			return NULL;
		return m_shape_list.at(index);
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//  葬蝶お曖 偃熱蒂 奩�納挬�
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	int GetSize()
	{
		return (int)m_shape_list.size(); // size_t -> int ⑽滲�� 嫦儅, 貲衛瞳戲煎 摹樹
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 摹鷗и 僭羹 葬蝶お曖 輿模高擊 奩�納挬�.
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	std::vector<iShape*> GetObjectList(int index)
	{
		return m_shape_list;
	}
	
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 葬蝶お曖 賅萇 紫⑽擊 斜溥遽棻
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void DrawAll(bool local_coordinate = false, bool poly_mode = false)
	{
		float delim = 0.7f;

		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera, local_coordinate, poly_mode);
		}
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 葬蝶お曖 賅萇 紫⑽擊 斜溥遽棻 (ィ葬堆 賅萄 摹鷗陛棟)
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void DrawAll_PolyMode(bool local_coordinate = false, bool poly_mode = false)
	{
		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera, local_coordinate, poly_mode);
		}
	}
	
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 蟾晦��
	// 斜葬晦蒂 嬪п憮 cameara 薑爾 в蹂
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Init(Camera* camera)
	{
		m_camera = camera;
	}

private:
	//QuadCore::Texture m_texture;
	//Shape* m_shape;
	std::vector<iShape*> m_shape_list;

	QuadCore::Camera* m_camera;

	typename glm::vec3 vec;	
};

}
