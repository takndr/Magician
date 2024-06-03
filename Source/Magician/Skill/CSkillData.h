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
		FString SkillName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString SkillDetails;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* SkillIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* SkillMontage;

	// ��ȯ�� ��ų ����Ʈ
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	
	//
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

	
	bool IsCoolDown() { return bCoolDown; }
	void SetCoolDown(bool CoolDown) { bCoolDown = CoolDown; }

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
		float SkillRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* SkillMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint8 CurrentLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint8 MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UCSkillData*> RequiredSkills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillCoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ACSkillEffector> EffectActor;

	// �׽�Ʈ��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCoolDown = false;

public:
	FSkillCoolDownSignature OnSkillCoolDown;

private:
	class ACharacter* OwnerCharacter;
};
