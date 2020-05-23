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
		float AxisDist[3];
		float fRDist[4];

		//Ax
		fD[0][0] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[0]);
		fD[0][1] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[1]);
		fD[0][2] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[2]);
		AxisDist[0] = D3DXVec3Dot(&box1.vAxis[0], &vDist);
		absfD[0][0] = fabs(fD[0][0]);
		absfD[0][1] = fabs(fD[0][1]);
		absfD[0][2] = fabs(fD[0][2]);
		fRDist[0] = fabs(AxisDist[0]);
		fRDist[1] = (box2.fExtent[0] * absfD[0][0]) + (box2.fExtent[1] * absfD[0][1]) + (box2.fExtent[2] * absfD[0][2]);
		fRDist[2] = box1.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Ay
		fD[1][0] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[0]);
		fD[1][1] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[1]);
		fD[1][2] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[2]);
		AxisDist[1] = D3DXVec3Dot(&box1.vAxis[1], &vDist);
		absfD[1][0] = fabs(fD[1][0]);
		absfD[1][1] = fabs(fD[1][1]);
		absfD[1][2] = fabs(fD[1][2]);
		fRDist[0] = fabs(AxisDist[1]);
		fRDist[1] = (box2.fExtent[0] * absfD[1][0]) + (box2.fExtent[1] * absfD[1][1]) + (box2.fExtent[2] * absfD[1][2]);
		fRDist[2] = box1.fExtent[1] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Az
		fD[2][0] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[0]);
		fD[2][1] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[1]);
		fD[2][2] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[2]);
		AxisDist[2] = D3DXVec3Dot(&box1.vAxis[2], &vDist);
		absfD[2][0] = fabs(fD[2][0]);
		absfD[2][1] = fabs(fD[2][1]);
		absfD[2][2] = fabs(fD[2][2]);
		fRDist[0] = fabs(AxisDist[2]);
		fRDist[1] = (box2.fExtent[0] * absfD[2][0]) + (box2.fExtent[1] * absfD[2][1]) + (box2.fExtent[2] * absfD[2][2]);
		fRDist[2] = box1.fExtent[2] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Bx
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[0], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][0]) + (box1.fExtent[1] * absfD[1][0]) + (box1.fExtent[2] * absfD[2][0]);
		fRDist[2] = box2.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//By
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[1], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][1]) + (box1.fExtent[1] * absfD[1][1]) + (box1.fExtent[2] * absfD[2][1]);
		fRDist[2] = box2.fExtent[1] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//Bz
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[2], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][2]) + (box1.fExtent[1] * absfD[1][2]) + (box1.fExtent[2] * absfD[2][2]);
		fRDist[2] = box2.fExtent[2] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;

		//AxBx
		fRDist[0] = fabs((AxisDist[2]* fD[1][0]) - (AxisDist[1]*fD[2][0]));
		fRDist[1] = box1.fExtent[1] * absfD[2][0] + box1.fExtent[2] * absfD[1][0];
		fRDist[2] = box2.fExtent[1] * absfD[0][2] + box2.fExtent[2] * absfD[0][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		
		//AxBy
		fRDist[0] = fabs((AxisDist[2] * fD[1][1]) - (AxisDist[1] * fD[2][1]));
		fRDist[1] = box1.fExtent[1] * absfD[2][1] + box1.fExtent[2] * absfD[1][1];
		fRDist[2] = box2.fExtent[0] * absfD[0][2] + box2.fExtent[2] * absfD[0][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AxBz
		fRDist[0] = fabs((AxisDist[2] * fD[1][2]) - (AxisDist[1] * fD[2][2]));
		fRDist[1] = box1.fExtent[1] * absfD[2][2] + box1.fExtent[2] * absfD[1][2];
		fRDist[2] = box2.fExtent[1] * absfD[0][0] + box2.fExtent[0] * absfD[0][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AyBx
		fRDist[0] = fabs((AxisDist[0] * fD[2][0]) - (AxisDist[2] * fD[0][0]));
		fRDist[1] = box1.fExtent[0] * absfD[2][0] + box1.fExtent[2] * absfD[0][0];
		fRDist[2] = box2.fExtent[1] * absfD[1][2] + box2.fExtent[2] * absfD[1][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AyBy
		fRDist[0] = fabs((AxisDist[0] * fD[2][1]) - (AxisDist[2] * fD[0][1]));
		fRDist[1] = box1.fExtent[0] * absfD[2][1] + box1.fExtent[2] * absfD[0][1];
		fRDist[2] = box2.fExtent[0] * absfD[1][2] + box2.fExtent[2] * absfD[1][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AyBz
		fRDist[0] = fabs((AxisDist[0] * fD[2][2]) - (AxisDist[2] * fD[0][2]));
		fRDist[1] = box1.fExtent[0] * absfD[2][2] + box1.fExtent[2] * absfD[0][2];
		fRDist[2] = box2.fExtent[1] * absfD[1][0] + box2.fExtent[0] * absfD[1][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AzBx
		fRDist[0] = fabs((AxisDist[0] * fD[1][0]) - (AxisDist[1] * fD[0][0]));
		fRDist[1] = box1.fExtent[0] * absfD[1][0] + box1.fExtent[1] * absfD[0][0];
		fRDist[2] = box2.fExtent[1] * absfD[2][2] + box2.fExtent[2] * absfD[2][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AzBy
		fRDist[0] = fabs((AxisDist[0] * fD[1][1]) - (AxisDist[1] * fD[0][1]));
		fRDist[1] = box1.fExtent[0] * absfD[1][1] + box1.fExtent[1] * absfD[0][1];
		fRDist[2] = box2.fExtent[0] * absfD[2][2] + box2.fExtent[2] * absfD[2][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		//AzBz
		fRDist[0] = fabs((AxisDist[0] * fD[1][2]) - (AxisDist[1] * fD[0][2]));
		fRDist[1] = box1.fExtent[0] * absfD[1][2] + box1.fExtent[1] * absfD[0][2];
		fRDist[2] = box2.fExtent[1] * absfD[2][0] + box2.fExtent[0] * absfD[2][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;

		return true;
	}

	bool ChkOBBToOBBAndDirection(const KG_Box box1, const KG_Box box2, D3DXVECTOR3& vCenDir, float& fM)
	{
		//분리축 투영 총 15개의 분리축 사용
		//각 OBB의 X,Y,Z 와 XYZ와 XYZ의 외적 축 까지 다 합치면 6+9=15;
		D3DXVECTOR3 vDist = (box1.vCenter - box2.vCenter);

		vCenDir = vDist;
		D3DXVec3Normalize(&vCenDir, &vCenDir);

		float fD[3][3];
		float absfD[3][3];
		float AxisDist[3];
		float fRDist[4];

		float fBeginM;

		//Ax
		fD[0][0] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[0]);
		fD[0][1] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[1]);
		fD[0][2] = D3DXVec3Dot(&box1.vAxis[0], &box2.vAxis[2]);
		AxisDist[0] = D3DXVec3Dot(&box1.vAxis[0], &vDist);
		absfD[0][0] = fabs(fD[0][0]);
		absfD[0][1] = fabs(fD[0][1]);
		absfD[0][2] = fabs(fD[0][2]);
		fRDist[0] = fabs(AxisDist[0]);
		fRDist[1] = (box2.fExtent[0] * absfD[0][0]) + (box2.fExtent[1] * absfD[0][1]) + (box2.fExtent[2] * absfD[0][2]);
		fRDist[2] = box1.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		fM = fBeginM;

		//Ay
		fD[1][0] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[0]);
		fD[1][1] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[1]);
		fD[1][2] = D3DXVec3Dot(&box1.vAxis[1], &box2.vAxis[2]);
		AxisDist[1] = D3DXVec3Dot(&box1.vAxis[1], &vDist);
		absfD[1][0] = fabs(fD[1][0]);
		absfD[1][1] = fabs(fD[1][1]);
		absfD[1][2] = fabs(fD[1][2]);
		fRDist[0] = fabs(AxisDist[1]);
		fRDist[1] = (box2.fExtent[0] * absfD[1][0]) + (box2.fExtent[1] * absfD[1][1]) + (box2.fExtent[2] * absfD[1][2]);
		fRDist[2] = box1.fExtent[1] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//Az
		fD[2][0] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[0]);
		fD[2][1] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[1]);
		fD[2][2] = D3DXVec3Dot(&box1.vAxis[2], &box2.vAxis[2]);
		AxisDist[2] = D3DXVec3Dot(&box1.vAxis[2], &vDist);
		absfD[2][0] = fabs(fD[2][0]);
		absfD[2][1] = fabs(fD[2][1]);
		absfD[2][2] = fabs(fD[2][2]);
		fRDist[0] = fabs(AxisDist[2]);
		fRDist[1] = (box2.fExtent[0] * absfD[2][0]) + (box2.fExtent[1] * absfD[2][1]) + (box2.fExtent[2] * absfD[2][2]);
		fRDist[2] = box1.fExtent[2] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//Bx
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[0], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][0]) + (box1.fExtent[1] * absfD[1][0]) + (box1.fExtent[2] * absfD[2][0]);
		fRDist[2] = box2.fExtent[0] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//By
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[1], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][1]) + (box1.fExtent[1] * absfD[1][1]) + (box1.fExtent[2] * absfD[2][1]);
		fRDist[2] = box2.fExtent[1] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//Bz
		fRDist[0] = fabs(D3DXVec3Dot(&box2.vAxis[2], &vDist));
		fRDist[1] = (box1.fExtent[0] * absfD[0][2]) + (box1.fExtent[1] * absfD[1][2]) + (box1.fExtent[2] * absfD[2][2]);
		fRDist[2] = box2.fExtent[2] + fRDist[1];
		if (fRDist[0] > fRDist[2])return false;
		fBeginM = fRDist[2] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AxBx
		fRDist[0] = fabs((AxisDist[2] * fD[1][0]) - (AxisDist[1] * fD[2][0]));
		fRDist[1] = box1.fExtent[1] * absfD[2][0] + box1.fExtent[2] * absfD[1][0];
		fRDist[2] = box2.fExtent[1] * absfD[0][2] + box2.fExtent[2] * absfD[0][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AxBy
		fRDist[0] = fabs((AxisDist[2] * fD[1][1]) - (AxisDist[1] * fD[2][1]));
		fRDist[1] = box1.fExtent[1] * absfD[2][1] + box1.fExtent[2] * absfD[1][1];
		fRDist[2] = box2.fExtent[0] * absfD[0][2] + box2.fExtent[2] * absfD[0][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AxBz
		fRDist[0] = fabs((AxisDist[2] * fD[1][2]) - (AxisDist[1] * fD[2][2]));
		fRDist[1] = box1.fExtent[1] * absfD[2][2] + box1.fExtent[2] * absfD[1][2];
		fRDist[2] = box2.fExtent[1] * absfD[0][0] + box2.fExtent[0] * absfD[0][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AyBx
		fRDist[0] = fabs((AxisDist[0] * fD[2][0]) - (AxisDist[2] * fD[0][0]));
		fRDist[1] = box1.fExtent[0] * absfD[2][0] + box1.fExtent[2] * absfD[0][0];
		fRDist[2] = box2.fExtent[1] * absfD[1][2] + box2.fExtent[2] * absfD[1][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AyBy
		fRDist[0] = fabs((AxisDist[0] * fD[2][1]) - (AxisDist[2] * fD[0][1]));
		fRDist[1] = box1.fExtent[0] * absfD[2][1] + box1.fExtent[2] * absfD[0][1];
		fRDist[2] = box2.fExtent[0] * absfD[1][2] + box2.fExtent[2] * absfD[1][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AyBz
		fRDist[0] = fabs((AxisDist[0] * fD[2][2]) - (AxisDist[2] * fD[0][2]));
		fRDist[1] = box1.fExtent[0] * absfD[2][2] + box1.fExtent[2] * absfD[0][2];
		fRDist[2] = box2.fExtent[1] * absfD[1][0] + box2.fExtent[0] * absfD[1][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AzBx
		fRDist[0] = fabs((AxisDist[0] * fD[1][0]) - (AxisDist[1] * fD[0][0]));
		fRDist[1] = box1.fExtent[0] * absfD[1][0] + box1.fExtent[1] * absfD[0][0];
		fRDist[2] = box2.fExtent[1] * absfD[2][2] + box2.fExtent[2] * absfD[2][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AzBy
		fRDist[0] = fabs((AxisDist[0] * fD[1][1]) - (AxisDist[1] * fD[0][1]));
		fRDist[1] = box1.fExtent[0] * absfD[1][1] + box1.fExtent[1] * absfD[0][1];
		fRDist[2] = box2.fExtent[0] * absfD[2][2] + box2.fExtent[2] * absfD[2][0];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		//AzBz
		fRDist[0] = fabs((AxisDist[0] * fD[1][2]) - (AxisDist[1] * fD[0][2]));
		fRDist[1] = box1.fExtent[0] * absfD[1][2] + box1.fExtent[1] * absfD[0][2];
		fRDist[2] = box2.fExtent[1] * absfD[2][0] + box2.fExtent[0] * absfD[2][1];
		fRDist[3] = fRDist[1] + fRDist[2];
		if (fRDist[0] > fRDist[3])return false;
		fBeginM = fRDist[3] - fRDist[0];
		if (fBeginM > fM)
		{
			fM = fBeginM;
		}

		if (box1.vCenter.x >= box2.vCenter.x)
		{
			if (box1.vCenter.x > box2.vMax.x && (box1.vCenter.z >= box2.vMax.z || box1.vCenter.z < box2.vMin.z))
			{
				return true;
			}

			if (box1.vCenter.z >= box2.vMax.z)
			{
				//fM /= box2.fExtent[2];
				vCenDir = box2.vAxis[2];
			}
			else if (box1.vCenter.z < box2.vMin.z)
			{
				//fM /= box2.fExtent[2];
				vCenDir = -box2.vAxis[2];
			}
			else
			{
				//fM /= box2.fExtent[0];
				vCenDir = box2.vAxis[0];
			}
		}
		else if (box1.vCenter.x < box2.vCenter.x)
		{
			if (box1.vCenter.x < box2.vMin.x && (box1.vCenter.z >= box2.vMax.z || box1.vCenter.z < box2.vMin.z))
			{
				//vCenDir = box2.vAxis[2] + (-box2.vAxis[0]);
				return true;
			}

			if (box1.vCenter.z >= box2.vMax.z)
			{
				//fM /= box2.fExtent[2];
				vCenDir = box2.vAxis[2];
			}
			else if (box1.vCenter.z < box2.vMin.z)
			{
				//fM /= box2.fExtent[2];
				vCenDir = -box2.vAxis[2];
			}
			else
			{
				//fM /= box2.fExtent[0];
				vCenDir = -box2.vAxis[0];
			}
		}

		//else if (vCenDir.x < 0)
		//{
		//	if (vCenDir.x < -box2.fExtent[0] && (vCenDir.z >= box2.fExtent[2] || vCenDir.z < -box2.fExtent[2]))
		//	{
		//		return true;
		//	}

		//	if (vCenDir.z >= box2.fExtent[2])
		//	{
		//		//fM /= box2.fExtent[2];
		//		vCenDir = box2.vAxis[2];
		//	}
		//	else if (vCenDir.z < -box2.fExtent[2])
		//	{
		//		//fM /= box2.fExtent[2];
		//		vCenDir = -box2.vAxis[2];
		//	}
		//	else
		//	{
		//		//fM /= box2.fExtent[0];
		//		vCenDir = box2.vAxis[0];
		//	}
		//}

		return true;
	}
}

KG_Collision::KG_Collision()
{
}


KG_Collision::~KG_Collision()
{
}
