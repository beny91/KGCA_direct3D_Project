#pragma once
#include "CBY_DataCtrl.h"
#include "CBY_Weapon.h"

namespace CBY
{
	class CBY_Character :public CBY_Object
	{
	protected:
		std::vector<std::shared_ptr<CBY_Weapon>> m_ObjectList;
		CBY_DataCtrl m_CharData;

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		virtual bool SkinLoad(T_STR pszLoad) override;
		virtual void SetCharBox() override;

	public: //object
		virtual bool ObjLoad(T_STR pszSkinLoad);
		virtual void SetObjectSocket(int iSocket, int iObjSocket, int iFireSocket, int iobj);

	public:
		virtual bool CharacterLoad(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context ,T_STR pszLoad,
			const TCHAR* ShaderFileName= L"../../data/shader/SkinShader.txt", const TCHAR* TexFileName= nullptr, const CHAR* VSName= "VSSKIN", const CHAR* PSName= "PS");
		virtual void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)override;
		

	public:
		virtual void SetCharAction(int state, float start, float end);

	public:
		CBY_Character();
		virtual ~CBY_Character();
	};
}
