#ifndef PCH_H
#define PCH_H

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>
#include <windowsx.h>

#define WIN_START_X 100
#define WIN_START_Y 100
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
#define DEVICE Device::Get()->GetDevice()
#define DVC Device::Get()->GetDeviceContext()
#define DELTA Timer::Get()->GetDeltaTime()
#define KEY_CON Control::Get()

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map> 
#include <string>
#include <random>
#define _USE_MATH_DEFINES // 삼각비를 다루기 위해
#include <math.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib") // DirectX에서 사용하는 기능들을 가져옴
#pragma comment(lib, "dxguid.lib")
#include "DirectXTex/DirectXTex.h"

#include"ImGui/imgui.h"
#include"ImGui/imgui_impl_win32.h"
#include"ImGui/imgui_impl_dx11.h"

#include <dwrite.h>
#pragma comment(lib,"dwrite.lib")

#include "FMOD/inc/fmod.h"

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

#include"Framework/Utility/Singleton.h"
#include"Framework/Utility/Timer.h"
#include"Framework/Utility/Control.h"

#include"Framework/Buffer/IndexBuffer.h"
#include"Framework/Buffer/VertexBuffer.h"
#include"Framework/Buffer/ConstBuffer.h"
#include"Framework/Buffer/GlobalBuffer.h"

#include"Framework/Math/Vector2.h"
#include"framework/Math/Transform.h"

#include"Framework/System/Device.h"
#include"Framework/Shader/VertexShader.h"
#include"Framework/Shader/PixelShader.h"

#include"Object/Vertex.h"

#include"Framework/Collision/Collider.h"
#include"Framework/Collision/RectCollider.h"
#include"Framework/Collision/CircleCollider.h"

#include"Framework/Render/Texture.h"
#include"Framework/Render/Frame.h"
#include"Framework/Render/Clip.h"

#include"Object/TransformList.h"

#include "Battle/BattleTransform.h"

#include"Pokemon/Pokemon.h"

#include "Sound/Sound.h"

#include "Battle/BattleManager.h"

#include"Scenes/Scene.h"
#include"Scenes/SceneList.h"

#include"Program/Program.h"

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
