# CLAUDE.md — DirectX PortFolio (PokémonDP 모작)

## 프로젝트 개요

DirectX 11 기반 2D 포켓몬DP 모작 포트폴리오 (1인 개발, 2024.04 ~ 2024.06).  
IDE: Visual Studio 2019 / 외부 라이브러리: FMOD(오디오), ImGui(디버그 UI).

---

## 디렉토리 구조

```
DirectX-PortPolio/
├── Battle/          # 전투 시스템 (BattleManager, ActionProcessor, StatusBox 등)
├── Core/            # 공유 상태 (GameState, SceneID, Interfaces)
├── Data/            # 포켓몬 스탯/스프라이트 정적 데이터 (PokemonData)
├── Framework/       # 엔진 레이어 (렌더링, 입력, 수학 유틸리티)
├── Pokemon/         # Pokemon 엔티티 클래스
├── Scenes/          # 씬 목록 (StartScene, TownScene, vsPokemonScene, vsChampionScene 등)
├── Shader/          # HLSL 버텍스/픽셀 셰이더
├── Texture/         # 스프라이트 시트 리소스
└── Sound/           # BGM 파일
```

---

## 핵심 아키텍처

### 전투 흐름

```
BattleManager::Update()
  ├─ is_appearance == true  → Appearance()   (입장 연출 FSM)
  └─ is_appearance == false
       ├─ HP <= 0           → HandlePlayerFainted() / HandleEnemyFainted()
       ├─ !IsIdle()         → RunCurrentAction()
       ├─ IsPlayerTurn()    → ProcessPlayerInput()
       └─ EnemyTurn         → ProcessEnemyTurn()
```

### 전략 패턴 — IBattleContext

`BattleManager(bool mode)` 생성자의 `mode` 인자는 외부 인터페이스로만 유지.  
내부에서는 `unique_ptr<IBattleContext> m_context` 를 통해 모드별 로직을 위임한다.

| 구현체 | 파일 | 역할 |
|--------|------|------|
| `VsPokemonContext` | `Battle/IBattleContext.h` | 야생 포켓몬 전투 |
| `VsChampionContext` | `Battle/IBattleContext.h` | 챔피언 전투 |

`IBattleContext` 가상 메서드:
- `BuildEnemyTeam()` — 적 팀 생성
- `GetEnemySkillSlot(fieldIndex)` — 현재 적 슬롯의 스킬 인덱스 반환
- `OnPlayerLose / OnEnemyFainted` — 전투 결과 GameState 반영
- `GetEnemyNameSlotOffset()` — StatusBox 폰트 슬롯 오프셋 (챔피언=1)
- `IsVsPokemon()` — 입장 연출 분기용

> **주의:** `BattleManager.h` 는 `struct IBattleContext;` 전방 선언 없이  
> `unique_ptr<IBattleContext>` 멤버를 선언한다.  
> 이 경우 `IBattleContext.h` 의 완전한 타입은 `BattleManager.cpp` 에서 include 한다.

### 턴 관리 — TurnManager

`Battle/TurnManager.h` 의 `TurnManager` 구조체가 턴과 액션 페이즈를 관리한다.

```cpp
enum class BattleTurn  { Player, Enemy };
enum class ActionPhase { Idle, Attack, Recovery, Change };
```

### 공유 전역 상태 — GameState

`Core/GameState.h` 의 `GameState g_state` (전역)가 씬 간 공유 데이터를 보관한다.

```cpp
struct GameState {
    bool gender;
    bool is_vsPokemon, is_vsChampion;
    bool clear_vsPokemon, clear_vsChampion;
    bool lose_vsPokemon, lose_vsChampion;
    Vector2 mouse_pos, mouse_click_pos;
};
```

클릭 좌표 초기화는 `g_state.mouse_click_pos = Vector2(0, 0)` 대신  
`g_state.ResetMouseClick()` 을 사용한다.

---

## 코드 규칙

### 스마트 포인터

모든 소유권 있는 멤버는 `unique_ptr` 을 사용한다.  
`BattleAnimation` 등 복합 컴포넌트는 `= default` 소멸자면 충분하다.

### Pokemon 접근

`Pokemon` 의 `is_active` 는 private. 반드시 `SetActive(bool)` / `IsActive()` 를 사용한다.  
위치 초기화는 `ResetPosition(Vector2)` 메서드를 사용한다.

### 버튼 입력

`SelectButton::GetClickedAction(Vector2 clickPos)` 가 `ButtonAction` enum 을 반환한다.  
`BattleManager` 에서 좌표 범위를 직접 비교하지 않는다.

### ActionProcessor

`RunAttack(slot, atk, def, defStatus)` 하나로 플레이어/적 공격을 모두 처리한다.  
`defStatus->SetHPBar()` 는 `Damage` 단계에서만 호출된다.

---

## 개발 브랜치

현재 작업 브랜치: `claude/analyze-battlemanager-oop-StYtX`  
모든 변경은 이 브랜치에 커밋하고 `git push -u origin <branch>` 로 푸시한다.
