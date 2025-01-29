#pragma once
// Vertex(정점) Buffer - 셰이더에 정점의 데이터를 넘길 떄 사용하려는 용도로 만들어진 클래스
class VertexBuffer
{
private:
	ID3D11Buffer* buffer;
	UINT stride;
	UINT offset;

public:
	VertexBuffer(void* data, UINT s, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
};
