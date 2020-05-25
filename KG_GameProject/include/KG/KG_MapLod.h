#pragma once
#include"KG_Node.h"
namespace JH
{
	typedef std::vector<KG_Node*> KGNODE_VECTOR;
	class KG_MapLod
	{
	public:
		std::vector<KGNODE_VECTOR> m_LevelList;
	public:
		KG_MapLod();
		virtual ~KG_MapLod();
	};
}

