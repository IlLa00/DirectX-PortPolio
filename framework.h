#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>

// 각종 매크로 상수를 선언하는 구간

#define WIN_START_X 100
#define WIN_START_Y 100
// 윈도우 창이 처음에 열릴 때 어느 위치에서 열릴지를 결정할 매크로

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
// 윈도우 창의 크기를 결정할 매크로

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
// 화면 중앙의 좌표를 매크로로서 손쉽게 이용할 수 있도록 선언

// 각종 매크로 단축문을 선언하는 구간
#define DEVICE Device::Get()->GetDevice()
#define DVC Device::Get()->GetDeviceContext()

#define DELTA Timer::Get()->GetDeltaTime()
#define KEY_CON Control::Get()


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map> 
#include <string>
#include <random>
#define _USE_MATH_DEFINES // 삼각비를 다루기 위해, 거기에 사용될 pi를 사용하겠다 선언
#include <math.h>


// DirectX11 관련 라이브러리
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
// 위의 내용들을 통해 DirectX에서 사용하는 기능들을 가져옴

#pragma comment(lib, "dxguid.lib")
#include "DirectXTex/DirectXTex.h"

#include"ImGui/imgui.h"
#include"ImGui/imgui_impl_win32.h"
#include"ImGui/imgui_impl_dx11.h"

#include <dwrite.h>
#pragma comment(lib,"dwrite.lib")

#include "FMOD/inc/fmod.h"

#include <dwrite.h>

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// XMFLOATN : DX에서 사용되는, 실수를 N개만큼 묶어놓은 구조체

typedef XMMATRIX Matrix;

// Framework Header - 프로그램을 구성하는 데 있어 뼈대가 될, 우리가 제작한 프레임워크

// Utility Header - 프로그램 여기저기서 사용할 기초적인 기능(=유틸리티)들을 관리하는 헤더들
#include"Framework/Utility/Singleton.h"
#include"Framework/Utility/Timer.h"
#include"Framework/Utility/Control.h"

// Buffer Header - DirectX 곳곳에서 셰이더에 정보를 넘길 때 사용하게 될 버퍼를 정의한 헤더들
#include"Framework/Buffer/IndexBuffer.h"
#include"Framework/Buffer/VertexBuffer.h"
#include"Framework/Buffer/ConstBuffer.h"
#include"Framework/Buffer/GlobalBuffer.h"

// Math Header - DirectX를 넘어 3D 공간과 관련된 수학적 연산을 담당하는 파트
#include"Framework/Math/Vector2.h"
#include"framework/Math/Transform.h"

// 미분류 - 현 시점에서는 따로 정리해두지 않는 헤더들
#include"Framework/System/Device.h"
#include"Framework/Shader/VertexShader.h"
#include"Framework/Shader/PixelShader.h"

//Object Header - 프로그램에서 이용될 오브젝트들과 관련된 헤더들
#include"Object/Vertex.h"

// Collider Header - 충돌처리를 다루는 프레임워크
#include"Framework/Collision/Collider.h"
#include"Framework/Collision/RectCollider.h"
#include"Framework/Collision/CircleCollider.h"

// Render Shader - 렌더링할 데이터를 관리(화면에 출력하는데 사용할 이미지 데이터 등을 관리)하는 클래스
// 중간에 정점을 사용하는 부분이 있어서 반드시 정점이 정의된 뒤에 호출되어야 함
#include"Framework/Render/Texture.h"
#include"Framework/Render/Frame.h"
#include"Framework/Render/Clip.h"

// Transform Header - 오브젝트들의 실제 관리를 담당하는 클래스들
#include"Object/TransformList.h" // 앞으로 Transform으로서 관리할 파일들을
// 헤더에서 쉽게 관리하기 위해,
// 미리 컴파일된 헤더에서는 그냥 놔두고
// 해당 폴더에서 직접 관련 헤더들을 다루는 헤더를 새로 만들어 거기서 관리

#include "Battle/BattleTransform.h"

#include"Pokemon/Pokemon.h"

#include "Sound/Sound.h"

#include "Battle/BattleManager.h"

// Program Header - 프로그램에서 실제로 가동하는 부분을 담당하는 헤더들
#include"Scenes/Scene.h"
#include"Scenes/SceneList.h"

#include"Program/Program.h"


// 전역 변수 선언부
extern HWND hWnd;
extern Vector2 mouse_pos;
extern Vector2 mouse_click_pos;
extern bool gender;
extern bool is_vsPokemon;
extern bool is_vsChampion;
extern bool clear_vsPokemon;
extern bool clear_vsChampion;
extern bool lose_vsPokemon;
extern bool lose_vsChampion;

#endif 
