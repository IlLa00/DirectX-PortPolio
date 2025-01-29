#include "framework.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	: stride(s), offset(0)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
	buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DVC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DVC->IASetPrimitiveTopology(type);
}
