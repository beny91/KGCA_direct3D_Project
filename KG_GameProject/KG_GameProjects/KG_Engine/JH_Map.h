#pragma once

#include"KG_ShapeMap.h"
#include"KG_ShapeLine.h"
#include"KG_TextureMgr.h"
#include"NormalMap.h"


using namespace std;
using namespace Microsoft::WRL;

struct CB_SPT
{
	D3DXVECTOR4 MapSubData;//x:splattTexture Num
	CB_SPT()
	{
		MapSubData = D3DXVECTOR4(0, 0, 0, 0);
	}
};
struct SplattTextureDesc
{
	int TexNum;
	float Alpha;
};
struct MapDesc
{
	int iColumNum;
	int iRowNum;
	const TCHAR* TextureFileName;
	const TCHAR* ShaderFileName;
	const TCHAR* pNormMapFileName;
	float fSellDistance;
	float fScaleHeight;
	//�ؽ�Ʈ����
	//���̴� 
	//�� ����
	//��
	//��
	//���� �� ��

};

class JH_Map :public KG_Model
{
public:
	bool	m_bMapEdit;

	map<int, CTexture*> m_vSplattTextureList;
	vector<ComPtr<ID3D11ShaderResourceView>> m_vSplattSRVList;
	//
	CB_SPT m_CBSubData;
	ComPtr<ID3D11Buffer>					m_CBSub;
public:
	//NormalMap
	vector<D3DXVECTOR3>  m_TangentList;
	NormalMap			 m_NormalMap;
	D3DXMATRIX			 m_matNormal;

	ComPtr<ID3D11Buffer> m_pTangentVB;
	ComPtr<CTexture>			 m_pTexture;
	int					 m_iTexNum;
	const TCHAR*		 m_pNormMapFileName;
	ComPtr<ID3D11ShaderResourceView> m_pNormSrv;
	
	
public:
	D3DXVECTOR3 m_vEyePos;
	MapDesc m_MapDesc;
	int m_iColumNum;
	int m_iRowNum;
	int m_iVertices;
	int m_iCellCol;
	int m_iCellRow;
	int m_iCellCount;
	const TCHAR* m_TextureFileName;
	const TCHAR* m_ShaderFileName;
	float m_fCellDistance;
	float m_fScaleHeight;

	ComPtr<ID3D11ShaderResourceView>	m_pCopySrv;
public:
	vector<float> m_vHeightList;
public:
	float GetHeight(float fX, float fZ);
	float GetHeightMap(int iRow, int iCol);
	HRESULT Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext);
	HRESULT CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext, const TCHAR* TextureFileName);
	void SetMapDesc(const TCHAR* TextureFileName,
		const TCHAR* ShaderFileName,
		int ColumNum,
		int RowNum,
		float fSellDistance,
		float fScaleHeight);
	void    SetMatrix(D3DXMATRIX* matWorld,
		D3DXMATRIX* matView,
		D3DXMATRIX* matProj)override;
	void UpdateConstantBuffer(ID3D11Buffer* pConstantBuffer, void* Data);
	float Lerp(float fStart, float fEnd, float fTangent);
		//�븻�� ���� ���� ���
	
	//�� ���� �Լ�
	INT AddSplattTexture(const TCHAR* pFileName,int Num,float Alpha=0.0f);

public:

public:
	HRESULT CreateInputLayout()override;
	HRESULT	LoadTexture(const TCHAR* pszTexFileName)override;
	bool	UpdateTangentBuffer();
	bool Frame()override;
	bool Release()override;
public:
	
	HRESULT		CreateVertexData();
	HRESULT		CreateIndexData();
public:
	JH_Map();
	virtual ~JH_Map();
};
