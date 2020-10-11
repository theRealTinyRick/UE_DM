// Fill out your copyright notice in the Description page of Project Settings.


#include <Core/UtilityStatics.h>

bool UUtilityStatics::IsEditor()
{
#if WITH_EDITOR
	return true;
#endif

	return false;
}
