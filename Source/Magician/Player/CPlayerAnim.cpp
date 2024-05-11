#include "Player/CPlayerAnim.h"

#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"

void UCPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);

	bFalling = player->GetCharacterMovement()->IsFalling();
	Speed = player->GetVelocity().Size2D();
	Direction = CalculateDirection(player->GetVelocity(), player->GetControlRotation());
	Pitch = player->GetBaseAimRotation().Pitch;
}