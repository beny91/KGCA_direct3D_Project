#include "KG_Collision.h"

namespace KG_COLLOSION
{
	bool ChkOBBToOBB(const KG_Box box1, const KG_Box box2)
	{
		//분리축 투영 총 15개의 분리축 사용
		//각 OBB의 X,Y,Z 와 XYZ와 XYZ의 외적 축 까지 다 합치면 6+9=15;
		D3DXVECTOR3 vDist = (box1.vCenter - box2.vCenter);

		float fD[3][3];
		float absfD[3][3];
		float AxisDist;
		float fRDist[4];

		//Ax
		fD[0][0] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[0]);
		fD[0][1] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[1]);
		fD[0][2] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[2]);
		AxisDist = D3DXVec3Dot(&box1.vAxis[0], &vDist);
		absfD[0][0] = fabs(fD[0][0]);
		absfD[0][1] = fabs(fD[0][1]);
		absfD[0][2] = fabs(fD[0][2]);
		fRDist[0] = fabs(AxisDist);
		fRDist[1] = (box2.fExtent[0] * absfD[0][0]) + (box2.fExtent[1] * absfD[0][1]) + (box2.fExtent[2] * absfD[0][2]);
		fRDist[2] = box1.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Ay
		fD[1][0] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[0]);
		fD[1][1] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[1]);
		fD[1][2] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[2]);
		AxisDist = D3DXVec3Dot(&box1.vAxis[1], &vDist);
		absfD[0][0] = fabs(fD[1][0]);
		absfD[0][1] = fabs(fD[1][1]);
		absfD[0][2] = fabs(fD[1][2]);
		fRDist[0] = fabs(AxisDist);
		fRDist[1] = (box2.fExtent[0] * absfD[0][0]) + (box2.fExtent[1] * absfD[0][1]) + (box2.fExtent[2] * absfD[0][2]);
		fRDist[2] = box1.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Az
		fD[2][0] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[0]);
		fD[2][1] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[1]);
		fD[2][2] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[2]);
		AxisDist = D3DXVec3Dot(&box1.vAxis[2], &vDist);
		absfD[0][0] = fabs(fD[2][0]);
		absfD[0][1] = fabs(fD[2][1]);
		absfD[0][2] = fabs(fD[2][2]);
		fRDist[0] = fabs(AxisDist);
		fRDist[1] = (box2.fExtent[0] * absfD[0][0]) + (box2.fExtent[1] * absfD[0][1]) + (box2.fExtent[2] * absfD[0][2]);
		fRDist[2] = box1.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
	}
}

KG_Collision::KG_Collision()
{
}


KG_Collision::~KG_Collision()
{
}
