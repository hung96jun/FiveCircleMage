#pragma once

// lib for DrawDebug
#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Utilities/CHelpers.h"
#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

#define F_RANDOM(min, max) UKismetMathLibrary::RandomFloatInRange(min, max)