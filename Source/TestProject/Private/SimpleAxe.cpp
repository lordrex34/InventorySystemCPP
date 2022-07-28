// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAxe.h"

ASimpleAxe::ASimpleAxe() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LocalStaticMesh(TEXT("/Game/Items/Equipment/Weapons/Meshes/SM_Weapon_Simple_Axe.SM_Weapon_Simple_Axe"));
	StaticMesh->SetStaticMesh(LocalStaticMesh.Object);

	Name = LOCTABLE(COMMON_WORDS2, "ID_SimpleAxe");
	Action = LOCTABLE(COMMON_WORDS2, "Use");

	ID = FName("ID_SimpleAxe");
}