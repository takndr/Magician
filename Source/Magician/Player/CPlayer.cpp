#include "CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Component/COptionComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"
#include "Component/CSkillComponent.h"
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
	CHelpers::GetAsset(&playerMesh, "SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'");
	GetMesh()->SetSkeletalMesh(playerMesh);

	// Weapon Setting
	//Staff->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
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

	if (!!SkillListWidgetClass)
	{
		SkillListWidget = CreateWidget<UUserWidget, APlayerController>(GetController<APlayerController>(), SkillListWidgetClass);
	}

	if (!!SkillHUDWidgetClass)
	{
		SkillHUDWidget = CreateWidget<UCMainWidget, APlayerController>(GetController<APlayerController>(), SkillHUDWidgetClass);
		SkillHUDWidget->AddToViewport();
		SkillHUDWidget->SetVisibility(ESlateVisibility::Visible);
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


	StateComp->SetAttack();
}

void ACPlayer::OffAttack()
{
	// 마우스 뗏을 때
	CheckNull(CurrentSkill);

	CurrentSkill->DoAction();

	StateComp->SetIdle();
}

void ACPlayer::Dodge()
{
	CheckFalse(StateComp->IsIdle());
}

void ACPlayer::OnSkillList()
{
	CheckNull(SkillHUDWidget);
	SkillHUDWidget->ControlSkillListWidget();
}

void ACPlayer::OnSkill1()
{
	if (Skill1Signature.IsBound())
	{
		Skill1Signature.Execute();
	}
}

void ACPlayer::OnSkill2()
{
	if (Skill2Signature.IsBound())
	{
		Skill2Signature.Execute();
	}
}

void ACPlayer::OnSkill3()
{
	if (Skill3Signature.IsBound())
	{
		Skill3Signature.Execute();
	}
}

void ACPlayer::OnSkill4()
{
	if (Skill4Signature.IsBound())
	{
		Skill4Signature.Execute();
	}
}

void ACPlayer::OnSkill5()
{
	if (Skill5Signature.IsBound())
	{
		Skill5Signature.Execute();
	}
}

void ACPlayer::SetCurrentSkill(class UCSkillData* SkillData)
{
	CurrentSkill = SkillData;
}