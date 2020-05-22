#pragma once
#include "CBY_MeshSkin.h"
namespace CBY
{
	enum SET_DATA_TYPES
	{
		NULL_DATA = 0,
		BOOL_DATA,
		INT_DATA,
		FLOAT_DATA,
		STRING_DATA,
		VECTOR_DATA,
		VERTEX_DATA,
		INDEX_DATA,
		FACE_DATA,
		MATRIX_DATA,
		SCENE_DATA
	};

	enum AniType
	{
		ANI_POS = 0,
		ANI_ROT,
		ANI_SCL
	};

	enum CHAR_STATE
	{
		CHAR_IDLE = 0,
		CHAR_MOVE,
		CHAR_JUMP,
		CHAR_RUN,
		CHAR_FIRE
	};
}