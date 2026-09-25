# Dodgeball — UE5 第三人称躲避球对战(C++ / 蓝图混合)

用 UE5(5.3)做的第三人称躲避球原型:C++ 负责角色、战斗、投射物与 UI 逻辑,蓝图负责资源与表现。

## 实现要点
- **生命值做成可挂载组件**:血量、扣血、死亡判定都收在一个 ActorComponent 里,再通过接口把「受伤 / 死亡」回调给挂载它的角色 —— 玩家和敌人挂同一个组件,数值逻辑与表现逻辑分离,新增受击单位不用改原有代码。
- **敌人视野**:在敌人身上挂射线检测(LineTraceSingleByChannel + 自定义碰撞通道,忽略自身与目标),「看得见玩家」就转向并开始投掷、「看不见」就停止;视线判定只负责判断,投掷交给定时器驱动。
- **投射物**:球体碰撞 + 投射物移动组件,碰撞回调统一处理伤害 / 粒子 / 音效,按撞击力度决定要不要播弹跳声;投掷时先延迟生成、生成完再给速度,避免生成瞬间就被移动组件带走。
- **表现层**:血条是 UMG 控件并绑定进度条,由玩家控制器统一刷新;角色死亡时弹出重开界面,同时暂停世界并把输入切到 UI 模式。

## 目录
```
Source/Dodgeball/     C++ 源码
  DodgeballCharacter.*        玩家角色(增强输入、生命组件、接口实现)
  EnemyCharacter.*            敌人(视线判定 + 定时投掷)
  DodgeballProjectile.*       投射物(碰撞回调、伤害、音效、寿命)
  HealthComponent.*           生命值组件
  HealthInterface.*           生命接口(受伤 / 死亡回调)
  LookAtActorComponent.*      视线检测组件
  HUDWidget.* ReStartWidget.* HUD 与重开界面
  DodgeballPlayerController.*  控制器(创建 UI、暂停、输入模式)
Content/
  ThirdPerson/        角色、游戏模式与关卡蓝图
  Physics/            物理相关资源
```

## 说明
入口关卡为 `/Game/ThirdPerson/Maps/ExampleMap`,默认 Pawn 由 GameMode 指定。
模板资源(StarterContent、官方人形与第三人称模板资产)未包含在本仓库,自行从 UE 官方模板补齐即可打开。
