#include "Animations/Notify/C_Notify_SpiderOnFire.h"

#include "Utilities/Defines.h"


UC_Notify_SpiderOnFire::UC_Notify_SpiderOnFire()
{
}

void UC_Notify_SpiderOnFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	CheckNull(MeshComp);


}
