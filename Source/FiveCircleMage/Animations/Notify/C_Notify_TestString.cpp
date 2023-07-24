#include "Animations/Notify/C_Notify_TestString.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

void UC_Notify_TestString::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	NotifyCheck();

	CLog::Print(Str, Time, Color);
}
