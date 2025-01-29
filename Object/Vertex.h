#pragma once
struct Vertex
// 앞으로 우리가 도형을 만들 때 쓸 정점의 정보는 이 구조체를 통해 관리함
{
	Float3 position;
	Float4 colour;

	Vertex()
		// C++에선 구조체는 사실상 public만 존재하는 클래스라 봐도 무방
		// 이렇게 생성자를 만드는 것도 문제 X
		// 아무 입력 없이 디폴트 선언했을 때의 초기화값
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// RGB값 외에 4번째 값인 알파값은 사용할 기회가 왔을 때 실행
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		// 2D에선 z축의 위치를 사용하지 않음
		colour = Float4(r, g, b, 1);
	}
};

struct VertexUV
{
	Float3 position;
	Float2 uv;

	VertexUV()
	{
		position = Float3(0, 0, 0);
		uv = Float2(0, 0);
	}
	VertexUV(float x, float y, float u, float v)
	{
		position = Float3(x, y, 0);
		uv = Float2(u, v);
	}
};

struct VertexPos // 좌표를 제외한 어떤 데이터도 없는 정점
{
	Float3 position;

	VertexPos()
	{
		position = Float3(0, 0, 0);
	}
	VertexPos(float x, float y)
	{
		position = Float3(x, y, 0);
	}
};

// 원래라면 여기서 끝이지만
// DX는 화면 좌표를 디폴트로는 -1.0~1.0까지로 이용하는 상대좌표계이므로
// 이를 변환해줄 함수가 필요함

static float ratio_pos_x(int pos_x)
// 입력한 절대좌표를 DX에서 사용할 수 있는 상대좌표로 변환하는 함수
// 지금은 이걸 쓰지만 나중엔 다른 기능으로 대체 예정
{
	float ratio = ((float)pos_x - WIN_CENTER_X) / (float)WIN_CENTER_X;

	return ratio;
}

static float ratio_pos_y(int pos_y)
{
	float ratio = -((float)pos_y - WIN_CENTER_Y) / (float)WIN_CENTER_Y;

	return ratio;
}
