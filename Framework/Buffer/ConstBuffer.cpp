#include "framework.h"

ConstBuffer::ConstBuffer(void* data, UINT data_size)
	: data(data), data_size(data_size)
{	
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = data_size;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->VSSetConstantBuffers(slot, 1, &buffer);
}
void ConstBuffer::SetPS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->PSSetConstantBuffers(slot, 1, &buffer);
}

