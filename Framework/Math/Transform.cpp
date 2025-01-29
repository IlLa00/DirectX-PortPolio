#include "framework.h"

Transform::Transform(Vector2 p, Vector2 s, float a, Matrix* parent)
	: pos(p), scale(s), rot(Float3(0.0f, 0.0f, a)), parent(parent)
{
	world = XMMatrixIdentity(); 

	right = Vector2(1, 0);
	up = Vector2(0, -1);

	WB = new MatrixBuffer();

}

Transform::~Transform()
{
	delete WB;
}

void Transform::WorldUpdate()
{
	S = XMMatrixScaling(scale.x, scale.y, 1.0f);

	R = XMMatrixRotationZ(rot.z);

	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(NULL, P);

	world = IP * S * R * T * P;



	if (this->parent != NULL)
		world *= *this->parent;


	XMStoreFloat4x4(&mat_world, world);
	

	right = Vector2(mat_world._11, mat_world._12);
	up = Vector2(mat_world._21, mat_world._22);


	XMVECTOR outS, outR, outT;


	XMMatrixDecompose(&outS, &outR, &outT, world);

	XMStoreFloat2(&global_scale, outS);
	

	WB->Set(world);

}
