#include "KG_BackViewCamera.h"

bool KG_BackViewCamera::Frame()
{
	m_fRadius += m_nMouseWhellDelta * m_fRadius * 0.1f / 120.0f;
	m_fRadius = min(m_fMaxRadius, m_fRadius);
	m_fRadius = max(m_fMinRadius, m_fRadius);
	m_nMouseWhellDelta = 0;

	if (I_Input.GetKeyCheck('W'))
	{
		Front(-1.0f);
	}
	if (I_Input.GetKeyCheck('S'))
	{
		Front(1.0f);
	}
	if (I_Input.GetKeyCheck('A'))
	{
		Side(1.0f);
	}
	if (I_Input.GetKeyCheck('D'))
	{
		Side(-1.0f);
	}

	D3DXVECTOR3 vPos = m_At + m_BackPos * m_fRadius;
	D3DXMatrixLookAtLH(&m_View, &vPos, &m_At, &m_DefaultUp);

	UpdateVector();
	return true;
}

void KG_BackViewCamera::Side(float fValue)
{
	m_At.x += fValue * g_SecondTime * m_fSpeed;
}
void KG_BackViewCamera::Front(float fValue)
{
	m_At.z += fValue * g_SecondTime* m_fSpeed;
}

KG_BackViewCamera::KG_BackViewCamera()
{
}


KG_BackViewCamera::~KG_BackViewCamera()
{
}
