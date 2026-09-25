# Dodgeball — UE5 第三人称躲避球对战原型

> 用 UE5 做的第三人称躲避球原型:**C++ 承担角色、战斗、投射物与 UI 逻辑,蓝图负责资源与表现**。
> 生命值是独立组件、敌人靠射线"看"玩家、投射物走碰撞回调 —— 结构上做的是职责拆分,不是堆功能。

## 简介

| | |
|---|---|
| **项目类型** | 第三人称对战原型(玩家 vs AI 敌人,投球互相扣血,一方死亡即结束) |
| **引擎版本** | Unreal Engine 5.3 |
| **实现方式** | C++(玩法逻辑)+ 蓝图(资源与表现)混合 |
| **C++ 规模** | 30 个头文件 / 源文件,约 1200 行 |
| **用到的引擎系统** | Enhanced Input、ActorComponent + 接口、LineTrace(自定义碰撞通道)、ProjectileMovement + 碰撞回调、UMG、世界暂停与输入模式切换 |
| **仓库规模** | C++ 源码 30 个文件 + 蓝图与资产 26 个 |
| **入口关卡** | `/Game/ThirdPerson/Maps/ThirdPersonMap`,默认 GameMode 为 `BP_DodgeballGamemode` |

## 功能流程

```
玩家 / 敌人各挂一个生命值组件 ── 敌人射线"看见"玩家 → 转向并起手投掷 → 投射物飞行
        ↓                                                          ↓
   命中碰撞回调统一处理(扣血 / 粒子 / 音效) ←───────────── 命中或落地自毁
        ↓
   血量归零 → 接口回调通知挂载者 → 敌人死亡 / 玩家死亡弹出重开界面(暂停世界 + 切 UI 输入)
```

## 实现要点(结构)

- **生命值做成可挂载组件**:血量、扣血、死亡判定都收在一个 ActorComponent 里,再通过接口把「受伤 / 死亡」回调给挂载它的角色 —— 玩家和敌人挂同一个组件,数值逻辑与表现逻辑分离,新增受击单位不用改原有代码。
- **敌人视野**:在敌人身上挂射线检测(`LineTraceSingleByChannel` + 自定义碰撞通道,忽略自身与目标),「看得见玩家」就转向并开始投掷、「看不见」就停止 —— 视线判定只负责判断,投掷交给定时器驱动,两者不耦合。
- **投射物**:球体碰撞 + 投射物移动组件,撞到谁由碰撞回调统一处理(扣血 / 粒子 / 音效),按撞击力度决定要不要播弹跳声;投掷时先延迟生成、生成完再给速度,避免生成瞬间就被移动组件带走。
- **表现层**:血条是 UMG 控件并绑定进度条,由玩家控制器统一刷新;角色死亡时弹出重开界面,同时暂停世界并把输入切到 UI 模式。
- **输入**:用 Enhanced Input 的输入映射上下文,把移动、视角、投掷拆成不同动作,投掷的按住 / 松开分别绑定 —— 为后续做蓄力留好结构。

## 目录结构

```
Source/Dodgeball/                 C++ 源码
  DodgeballCharacter.*            玩家角色(增强输入、生命组件、接口实现)
  EnemyCharacter.*                敌人(视线判定 + 定时投掷)
  DodgeballProjectile.*           投射物(碰撞回调、伤害、音效、自毁)
  HealthComponent.*               生命值组件
  HealthInterface.*               生命接口(受伤 / 死亡回调)
  LookAtActorComponent.*          视线检测组件
  HUDWidget.*  ReStartWidget.*    HUD 与重开界面
  DodgeballPlayerController.*     控制器(创建 UI、暂停世界、切输入模式)
Content/
  ThirdPerson/                    角色、GameMode 与关卡
  Physics/                        物理相关资源
Config/                           项目与输入配置
```

## 如何打开

1. 安装 **Unreal Engine 5.3** 与 **Visual Studio 2022**(需含「使用 C++ 的游戏开发」工作负载)。
2. `git clone` 本仓库,右键 `Dodgeball.uproject` → **Generate Visual Studio project files** → 打开 `.sln` 编译
   (或直接双击 `.uproject`,提示编译模块时选 Yes)。
3. 本仓库不含 UE 官方模板资源:用 UE 新建一个 **Third Person C++ 模板** 工程,把它的 `Content/Characters`、
   `Content/StarterContent`、`Content/ThirdPerson/Maps` 补进本项目 `Content/` 下,关卡即可完整显示。
4. 入口关卡 `/Game/ThirdPerson/Maps/ThirdPersonMap`,默认 Pawn 与 GameMode 由项目配置指定。

## 说明

- 仓库只包含本人产出的 C++ 源码、蓝图与资源;UE 官方模板资源未包含(见"如何打开"第 3 步),clone 后需要补一次模板资源才能完整运行。
- 玩法数值(血量、投掷间隔、球形投射物速度等)都有默认值,可在蓝图上直接覆盖,方便调手感。
