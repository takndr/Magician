#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class MAGICIAN_API ACPlayer : public ACharacter
{
	GENERATED_BODY()
public:
	ACPlayer();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
// ================================================================================================
public:
	// Getter & Setter
	class UCMainWidget* GetSkillHUDWidget() { return SkillHUDWidget; }

private:
	// Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
	void OnZoom(float Axis);

	// Action Event
	void OnJump();
	void OnAttack();
	void OffAttack();
	void Dodge();
	void OnSkillList();

// ================================================================================================
protected:
	UPROPERTY(EditAnywhere)
		class UStaticMesh* MagicianWeapon;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* TestAttackMontage;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MeshSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* MeshCamera;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Staff;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* OptionComp;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComp;

	UPROPERTY(VisibleDefaultsOnly)
		class UCSkillComponent* SkillComp;
// ================================================================================================
private:
	TSubclassOf<class UCMainWidget> SkillHUDWidgetClass;
	TSubclassOf<class UUserWidget> SkillListWidgetClass;

	class UCMainWidget* SkillHUDWidget;
	class UUserWidget* SkillListWidget;

	bool bOpenSkillList = false;
	
};
