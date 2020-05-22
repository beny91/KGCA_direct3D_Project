#include "KG_Point.h"

HRESULT KG_Point::CreateVertexData()
{
	HRESULT hr = S_OK;

	m_obj.m_VertexSize = sizeof(PNCT_VERTEX);

	m_VerTex.resize(4);
	m_VerTex[0].p = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	m_VerTex[1].p = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	m_VerTex[2].p = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	m_VerTex[3].p = D3DXVECTOR3(0.5f, -0.5f, 0.0f);				//정점 좌표 입력

	m_VerTex[0].c = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
	m_VerTex[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VerTex[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VerTex[3].c = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);									//정점 컬러값 입력

	m_VerTex[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_VerTex[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_VerTex[2].t = D3DXVECTOR2(0.0f, 1.0f);
	m_VerTex[3].t = D3DXVECTOR2(1.0f, 1.0f);												//정점 텍스쳐 좌표
	return hr;
}

KG_Point::KG_Point()
{
}


KG_Point::~KG_Point()
{
}
