#pragma once
#include "CBY_DataCtrl.h"
#include "CBY_Object.h"

namespace CBY
{
	class CBY_Character :public CBY_Object
	{
	protected:
		std::vector<std::shared_ptr<CBY_Object>> m_ObjectList;
		CBY_DataCtrl m_CharData;

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	public: //object
		virtual bool ObjLoad(T_STR pszSkinLoad);
		virtual void SetObjectSocket(int iSocket, int iObjSocket, int iobj);

	public:
		virtual bool CharacterLoad(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context ,T_STR pszLoad,
			const TCHAR* ShaderFileName= L"../../data/shader/SkinShader.txt", const TCHAR* TexFileName= nullptr, const CHAR* VSName= "VSSKIN", const CHAR* PSName= "PS");

	public:
		void SetCharAction(int state, float start, float end);

	public:
		CBY_Character();
		virtual ~CBY_Character();
	};
}
