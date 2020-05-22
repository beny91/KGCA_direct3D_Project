#pragma once
#include "KG_ShapeBox.h"

namespace CBY
{

	class CBY_CharBox : public KG_ShapeBox
	{
	private:
		int m_iBoneIndex;
		KG_Box m_Box;
		std::vector<D3DXMATRIX*> m_pParmatList;
		D3DXMATRIX* m_pBindmat;
		D3DXVECTOR3 m_vMax;
		D3DXVECTOR3 m_vMin;
		D3DXVECTOR3 m_vPos;
		D3DXVECTOR3 m_vBoxSize;
		std::vector<PNCT_VERTEX> m_VertexList;

	public:
		HRESULT UpdateBoxVB();
		HRESULT CreateIndexData();
		void CreateBox(int index, D3DXVECTOR3 vPos, float fXsize, float fYsize, float fZsize);
		void SetBox(float fXsize, float fYsize, float fZsize, int id);
		void SetParentMatrix(D3DXMATRIX* mat);
		void SetBindMatrix(D3DXMATRIX* mat);
		D3DXMATRIX GetParentMatrix(int index);
		D3DXMATRIX GetBindMatrix();
		D3DXMATRIX GetWorldMatrix(int index);
		int GetBoneIndex();
		D3DXVECTOR3 GetSize();
		D3DXVECTOR3 GetPos();

	public:
		CBY_CharBox();
		virtual ~CBY_CharBox();
	};
}
