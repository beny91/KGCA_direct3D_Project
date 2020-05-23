#pragma once
#include "CBY_Object.h"

namespace CBY
{
	class CBY_Weapon :public CBY_Object
	{
	protected:
		int m_iCharSocket;
		int m_iObjSocket;
		int m_iFireSocket;
		std::vector<int> m_SocketList;
		int m_ObjIndex;
		D3DXMATRIX m_matCalculation;
		CBY_MeshSkin* m_RootMesh;

	public:
		virtual bool Update(D3DXMATRIX* parmat);

	public:
		void SetSocket(int i);		//ĳ���Ϳ� ����� ĳ������ ����
		int GetSocket();
		void SetObjSocke(int i);	//������Ʈ�� ����
		int GetObjSocke();	//������Ʈ�� ����
		void SetFireSocket(int i);
		int GetFireSocket();

	public:
		CBY_Weapon();
		virtual ~CBY_Weapon();
	};
}


