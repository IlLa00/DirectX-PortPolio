#pragma once
// Vertex(����) Buffer - ���̴��� ������ �����͸� �ѱ� �� ����Ϸ��� �뵵�� ������� Ŭ����
class VertexBuffer
{
private:
	ID3D11Buffer* buffer = nullptr;
	UINT stride;
	UINT offset;

public:
	VertexBuffer(void* data, UINT s, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
};
