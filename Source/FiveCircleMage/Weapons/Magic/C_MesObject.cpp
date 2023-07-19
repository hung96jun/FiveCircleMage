// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Magic/C_MesObject.h"

// Sets default values
AC_MesObject::AC_MesObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MesObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MesObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}