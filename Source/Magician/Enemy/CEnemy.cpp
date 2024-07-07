#include "Enemy/CEnemy.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CDamageComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Enemy/CAIController.h"

#include "Global.h"

ACEnemy::ACEnemy()
{
	//PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &StatusComp, "Status");
	CHelpers::CreateActorComponent(this, &StateComp, "State");
	CHelpers::CreateActorComponent(this, &DamageComp, "Damage");

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// HP Widget Setting
	//CHelpers::GetClass(&HPWidgetClass, "/Game/Widgets/Widget/Enemy/WB_DummyHp");
	//HPWidget->SetRelativeLocation(FVector(0, 0, 90));
	//HPWidget->SetDrawSize(FVector2D(100, 10));
	//HPWidget->SetWidgetClass(HPWidgetClass);
	//HPWidget->SetHiddenInGame(true);

	// AI Controller Setting
	CHelpers::GetClass(&AIControllerClass, "/Game/Enemies/BP_AIController");
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < GetMesh()->GetNumMaterials(); i++)
	{
		UMaterialInstanceDynamic* tempMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(i), nullptr);
		MeshMaterials.AddUnique(tempMaterial);
		GetMesh()->SetMaterial(i, tempMaterial);
	}

	//CLog::Print(MeshMaterials.Num());
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);



	return DamageValue;
}

void ACEnemy::ChangeBodyColor_Implementation(FLinearColor InColor , float InPow)
{
	for (auto material : MeshMaterials)
	{
		material->SetVectorParameterValue("Rim_Colour_Tint", InColor);
		material->SetScalarParameterValue("Rim Glow Power", InPow);
	}
}