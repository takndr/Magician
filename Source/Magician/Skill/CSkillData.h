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

	// 소환할 스킬 이펙트
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	
	//
};

UCLASS()
class MAGICIAN_API UCSkillData : public UDataAsset
{
	GENERATED_BODY()
public:
	void DoAction();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillStatus SkillStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillType SkillType;

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint8 CurrentLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint8 MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCSkillData* PreviousSkill;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SkillCoolDown;
};
