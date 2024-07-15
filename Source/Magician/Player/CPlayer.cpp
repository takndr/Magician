#include "CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Component/COptionComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CPlayerStatusComponent.h"
#include "Component/CSkillComponent.h"
#include "Component/CDamageComponent.h"

#include "Widget/CSkillList.h"
#include "Widget/CMainWidget.h"
#include "Skill/CSkillData.h"

#include "Global.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Component
	CHelpers::CreateSceneComponent(this, &MeshSpringArm, "MeshSpringArm", GetCapsuleComponent());
	CHelpers::CreateSceneComponent(this, &MeshCamera, "MeshCamera", MeshSpringArm);
	CHelpers::CreateSceneComponent(this, &Staff, "Staff", GetMesh());

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &OptionComp, "Option");
	CHelpers::CreateActorComponent(this, &StateComp, "State");
	CHelpers::CreateActorComponent(this, &StatusComp, "Status");
	CHelpers::CreateActorComponent(this, &SkillComp, "Skill");
	CHelpers::CreateActorComponent(this, &DamageComp, "Damage");

	// MeshSpringArm Setting
	MeshSpringArm->SetRelativeLocation(FVector(0, 0, 60));
	MeshSpringArm->TargetArmLength = 300.0f;
	MeshSpringArm->bDoCollisionTest = false;
	MeshSpringArm->bUsePawnControlRotation = true;

	// MeshCamera Setting
	//MeshCamera->bUsePawnControlRotation = true;

	// Based Character Setting
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);

	class USkeletalMesh* playerMesh;
	CHelpers::GetAsset(&playerMesh, "/Game/Asset/BattleWizardPolyart/Meshes/WizardSM");
	GetMesh()->SetSkeletalMesh(playerMesh);

	// Weapon Setting
	Staff->AttachTo(GetMesh(), "WeaponSocket");

	// Anim Setting
	TSubclassOf<UAnimInstance> animClass;
	CHelpers::GetClass(&animClass, "/Game/Player/ABP_Player");
	GetMesh()->SetAnimInstanceClass(animClass);

	// Widget Setting
	CHelpers::GetClass(&SkillHUDWidgetClass, "/Game/Widget/WB_HUD_Main");
}

void ACPlayer::BeginPlay()
{
	if (!!MagicianWeapon)
	{
		Staff->SetStaticMesh(MagicianWeapon);
	}

	if (!!SkillHUDWidgetClass)
	{
		MainHUDWidget = CreateWidget<UCMainWidget, APlayerController>(GetController<APlayerController>(), SkillHUDWidgetClass);
		MainHUDWidget->AddToViewport();
		MainHUDWidget->SetVisibility(ESlateVisibility::Visible);
	}

	for (int i = 0; i < GetMesh()->GetNumMaterials(); i++)
	{
		UMaterialInstanceDynamic* tempMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(i), nullptr);
		MeshMaterials.AddUnique(tempMaterial);
		GetMesh()->SetMaterial(i, tempMaterial);
	}

	Super::BeginPlay();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Event Binding
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	// Action Event Binding
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACPlayer::OnAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACPlayer::OffAttack);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ACPlayer::Dodge);
	PlayerInputComponent->BindAction("SkillList", IE_Pressed, this, &ACPlayer::OnSkillList);

	PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &ACPlayer::OnSkill1);
	PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &ACPlayer::OnSkill2);
	PlayerInputComponent->BindAction("Skill3", IE_Pressed, this, &ACPlayer::OnSkill3);
	PlayerInputComponent->BindAction("Skill4", IE_Pressed, this, &ACPlayer::OnSkill4);
	PlayerInputComponent->BindAction("Skill5", IE_Pressed, this, &ACPlayer::OnSkill5);
}

void ACPlayer::ChangeBodyColor_Implementation(FLinearColor InColor, float InPow)
{
	for (auto material : MeshMaterials)
	{
		material->SetVectorParameterValue("Color", InColor);
	}
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, MeshSpringArm->GetRelativeRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, MeshSpringArm->GetRelativeRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	float speed = Axis * GetWorld()->GetDeltaSeconds() * OptionComp->GetHorizontalSpeed();

	FRotator temp = MeshSpringArm->GetRelativeRotation();
	FRotator modify = FRotator(temp.Pitch, temp.Yaw + speed, temp.Roll);

	MeshSpringArm->SetRelativeRotation(modify);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	float speed = Axis * GetWorld()->GetDeltaSeconds() * OptionComp->GetVerticalSpeed();

	FRotator temp = MeshSpringArm->GetRelativeRotation();
	FRotator modify = FRotator(FMath::Clamp(temp.Pitch + speed, -20.0f, 0.0f), temp.Yaw, temp.Roll);

	MeshSpringArm->SetRelativeRotation(modify);
}

void ACPlayer::OnZoom(float Axis)
{
	float rate = OptionComp->GetZoomSpeed() * Axis * GetWorld()->GetDeltaSeconds();
	MeshSpringArm->TargetArmLength += rate;

	MeshSpringArm->TargetArmLength = FMath::Clamp(MeshSpringArm->TargetArmLength, OptionComp->GetZoomMin(), OptionComp->GetZoomMax());
}

void ACPlayer::OnJump()
{
	CheckFalse(StateComp->IsIdle());
	Jump();
}

void ACPlayer::OnAttack()
{
	// 마우스 쭉 누르고 있을 때
	CheckFalse(StateComp->IsIdle());
	//CheckNull(CurrentSkill);

	if (CurrentSkill == nullptr)
	{
		CLog::Print("No Skill Selected");
		return;
	}

	if (CurrentSkill->IsCoolDown())
	{
		CLog::Print("Skill Cool Down Now. Wait");
		return;
	}

	// 캐릭터가 현재 가지고 있는 마나와 스킬의 유효 마나 비교하여 적으면 못쓰게 설정
	if (StatusComp->GetCurrentMp() < CurrentSkill->SkillMana)
	{
		CLog::Print("Not Enough Mana");
		return;
	}

	StateComp->SetAttack();
	StatusComp->DecreaseMana(CurrentSkill->SkillMana);
	CurrentSkill->Casting();
}

void ACPlayer::OffAttack()
{
	// 마우스 뗏을 때
	CheckNull(CurrentSkill);
}

void ACPlayer::Dodge()
{
	CheckFalse(StateComp->IsIdle());
}

void ACPlayer::OnSkillList()
{
	CheckNull(MainHUDWidget);
	MainHUDWidget->ControlSkillListWidget();
}

void ACPlayer::OnSkill1()
{
	CheckFalse(StateComp->IsIdle());

	if (Skill1Signature.IsBound())
	{
		Skill1Signature.Execute();
	}
}

void ACPlayer::OnSkill2()
{
	CheckFalse(StateComp->IsIdle());

	if (Skill2Signature.IsBound())
	{
		Skill2Signature.Execute();
	}
}

void ACPlayer::OnSkill3()
{
	CheckFalse(StateComp->IsIdle());

	if (Skill3Signature.IsBound())
	{
		Skill3Signature.Execute();
	}
}

void ACPlayer::OnSkill4()
{
	CheckFalse(StateComp->IsIdle());

	if (Skill4Signature.IsBound())
	{
		Skill4Signature.Execute();
	}
}

void ACPlayer::OnSkill5()
{
	CheckFalse(StateComp->IsIdle());

	if (Skill5Signature.IsBound())
	{
		Skill5Signature.Execute();
	}
}

void ACPlayer::SetCurrentSkill(class UCSkillData* SkillData)
{
	CurrentSkill = SkillData;
}