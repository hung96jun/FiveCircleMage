#include "Animations/Notify/C_Notify_BossOnFire.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Monster/Boss/C_Boss.h"

#include "Weapons/Weapon/ThrowingWeapons/C_BossRock.h"
#include "C_GameInstance.h"
#include "Managers/C_WeaponManager.h"

void UC_Notify_BossOnFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AC_Boss* owner = Cast<AC_Boss>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	UC_GameInstance* instance = Cast<UC_GameInstance>(owner->GetWorld()->GetGameInstance());
	if (instance == nullptr) return;
	if (instance->GetWeaponManager() == nullptr) return;
	if (instance->GetWeaponManager()->FindWeapon(WeaponName) == false) return;

	AC_BossRock* object = Cast<AC_BossRock>(instance->GetWeaponManager()->ActiveWeapon(WeaponName));

	object->OnFire(owner->GetActorForwardVector(), owner);
}