# DirectX PortFolio     
**DirectX2D**를 이용해 제작한 포켓몬DP 모작으로 1인 제작된 포트폴리오입니다.    
에디터 : VS 2019, ImGui, Fmod / 제작기간 : 2달 (2024.04 ~ 2024.06)  
Notion : https://thoughtful-shop-228.notion.site/DirectX2D-a534dbb0046f473f9b741c26eb928010?pvs=4      
## 들어가기 앞서,      
포켓몬DP를 DirectX2D를 통해 그래픽 렌더링을 구현하고 FMOD를 활용해 동적인 오디오 관리를 적용하였고 또한, 원활한 디버깅을 위해 ImGui를 활용하였습니다.     
원작 게임의 느낌을 최대한 살리면서 렌더링 파이프라인에 대해 학습하며 텍스처같은 리소스를 효율적으로 활용함으로써 핵심 게임 개발 역량을 시연하는 데 중점을 두었습니다.        
## 구현 영상     
https://github.com/user-attachments/assets/facaa310-cbd7-4edb-afc3-6f54613efaaf
## 기술 설명     
> DirectX기반 렌더링, FMOD, ImGui순으로 기술에 대해 설명한 뒤, 게임에 대해 후술하겠습니다.
# 목차   
[1. DirectX 렌더링.](#DirectX-렌더링)     
[2. FMOD.](#FMOD)      
[3. ImGui.](#ImGui)     
[4. InGame.](#InGame)     

###  DirectX 렌더링.     
- 모든 2D 렌더링을 위해 커스텀 정점버퍼와 인덱스버퍼를 직접 생성하고 관리해 쿼드같은 기본적인 2D 지오메트리를 효율적으로 GPU에 전달해 렌더링 오버헤드를 최소화 하였습니다.            
- 커스텀 RectCollider 클래스는 직사각형 형태의 충돌 영역을 처리하며 타일맵 오브젝트나 NPC등에 충돌에 사용되며 AABB충돌 감지 방식을 활용했습니다.        
- 커스텀 정점셰이더와 픽셀셰이더를 활용해 정점셰이더는 WVP변환을 수행하여 모든 픽셀이 화면에 매핑되게 구현했으며 픽셀셰이더는 컬러를 샘플링합니다.   
- Frame 클래스를 통해 단일 스프라이트의 UV좌표를 관리하고 이를 조합해 Clip 클래스에서 애니메이션을 관리하여 플레이어의 움직임과 전투 애니메이션 등을 유연하게 적용했습니다.    
- 정점셰이더와 픽셀셰이더의 hlsl 파일을 활용해~

### FMOD.     
- 외부 라이브러리인 FMOD를 링크시키기 위해 fmod.inc를 프로젝트의 추가 디렉토리에, fmod.lib를 라이브러리 디렉토리에 연결을 시킴으로써 성공적으로 연동시켰습니다. 
- FMOD_SYSTEM* Sound::g_System 이라는 객체로, 사운드 재생 및 일시 정지를 가능하게 합니다.    
- 커스텀 Sound 클래스를 생성해, vector<Sound*> Sound_list라는 vector 자료구조로 사용할 브금들을 push하고 Scene이 바뀔 때 마다, Scene에 맞는 브금들을 재생합니다.  
### ImGui.     
- ImGui 윈도우를 통해 FPS, RunTime을 모니터링하며 특정 Scene에서는 플레이어의 좌표와 마우스 클릭좌표, 전투 상태 등 핵심 게임 데이터를 실시간으로 모니터링할 수 있도록 구현했습니다.     
![KakaoTalk_20250605_195005060](https://github.com/user-attachments/assets/7b7bb69e-c6fd-4664-a248-09eb4e936c9b)     
- ImGui를 활용함으로써, 개발 중 예상치 못한 버그를 빠르게 진단하는데 유용했습니다.
### InGame.    
> 영상에 나오는 Scene 순서대로 설명하겠으며, 전투Scene에 대해 중점적으로 기술하겠습니다.
# StartScene    
- 시작화면입니다, 스페이스바를 누르면 다음 Scene으로 건너갑니다.
# CharacterSelectScene    
- 플레이어의 성별을 선택하는 화면입니다, 남자 캐릭터나 여자 캐릭터를 마우스로 선택하면 다음 Scene으로 건너가며, 성별에 맞는 플레이어로 게임을 진행하게 됩니다.
# TownScene     
- 두개의 배경화면(마을,야생)으로 이루어져 있으며 마을에선 강가와 나무, 집 오브젝트에 RectCollider를 적용해 충돌처리를 하였고 위쪽에 야생으로 넘어가는 RectCollider가 있습니다.
- 야생에선 나무 오브젝트에 RectCollider가 적용되어 있으며 NPC와 마주칠 시, RectCollider가 감지되어 다음 Scene으로 넘어갑니다.
# vsPokeMonScene, vsChampionScene    
- BattleManager 클래스를 만들어 원작 게임과 동일한 턴제 관리를 합니다.     
