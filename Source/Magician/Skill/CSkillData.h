#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CSkillData.generated.h"

UENUM(BlueprintType)
enum class ESkillStatus : uint8
{
	Locked, UnLocked, Acquired
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None, Active, Passive
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None, Active, Passive
};

USTRUCT(BlueprintType)
struct FTemplateStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillMana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillCoolDown;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkillCoolDownSignature);

UCLASS()
class MAGICIAN_API UCSkillData : public UDataAsset
{
	GENERATED_BODY()
public:
	void BeginPlay(class ACharacter* Owner);
	void DoAction();
	
	void Casting();
	void CastComplete();
	void SpawnEffector();

	
	bool IsCoolDown() { return bCoolDown; }
	void SetCoolDown(bool CoolDown) { bCoolDown = CoolDown; }

	void Upgrade();
	void Downgrade();

	bool CanLearnedSkill();

	void RefreshSkill();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillStatus SkillStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillType SkillType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EDamageType DamageType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString SkillName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString SkillDetails;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* SkillIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* SkillMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CurrentLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UCSkillData*> RequiredSkills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillCoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillEffector")
		TSubclassOf<class ACSkillActor> SkillActorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillEffector")
		float SkillDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkillEffector")
		float SkillMana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CastingTime = 1.0f;

	// 테스트용
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCoolDown = false;

public:
	FSkillCoolDownSignature OnSkillCoolDown;

private:
	class ACharacter* OwnerCharacter;
};
