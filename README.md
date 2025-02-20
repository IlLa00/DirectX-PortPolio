# DirectX PortFolio     
DirectX2D를 이용해 제작한 포켓몬DP 모작 1인 첫번째 포트폴리오입니다.    
에디터 : VS 2019, ImGui, Fmod / 제작기간 : 2달 (2024.04 ~ 2024.06)  
Notion : https://thoughtful-shop-228.notion.site/DirectX2D-a534dbb0046f473f9b741c26eb928010?pvs=4    
## 목차
1. [구현 영상](#구현-영상)
2. [기술 설명](#기술-설명)     
## 구현 영상     
https://github.com/user-attachments/assets/facaa310-cbd7-4edb-afc3-6f54613efaaf
## 기술 설명     
> 영상에 보이는 Scene순서대로 설명하겠습니다.
### StartScene     
스페이스바 입력을 받으면 다음 Scene으로 넘어갑니다.
### CharacterSelectScene
마우스 클릭 위치(남자 캐릭터, 여자캐릭터)에 따라 캐릭터가 선택되고 다음 Scene으로 넘어갑니다.     
### TownScene
플레이어는 입력받은 방향키에 따라 플레이어의 이동모션을 담당하는 열거형을 통해 진행되는 스프라이트가 달라집니다.     
RectCollider를 만들어 AABB충돌을 이용해 플레이어가 이동할 수 있는 구역을 제한하고 다음 스테이지로 이동할 수 있는 트리거를 만들었습니다.    
다음 스테이지에선 특정 RectColler와 충돌되면 다음 Scene으로 넘어가는 트리거가 있습니다.   
### vsPocketMonScene    
### vsChampionScene    
BattleManager이란 클래스를 만들어 턴제 전투의 흐름을 담당했습니다.   
Font라는 클래스를 만들어 화면에 보일 글자들을 렌더링했습니다.   





 
