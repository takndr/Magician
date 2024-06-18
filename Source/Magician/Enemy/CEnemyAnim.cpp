#include "Enemy/CEnemyAnim.h"

#include "Enemy/CEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"

void UCEnemyAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	ACEnemy* enemy = Cast<ACEnemy>(OwnerCharacter);

	bFalling = enemy->GetCharacterMovement()->IsFalling();
	Speed = enemy->GetVelocity().Size2D();
}