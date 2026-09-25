// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* BounceSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundAttenuation* BounceSoundAttenuation;
	UPROPERTY(EditDefaultsOnly, Category = "Sound") class USoundBase* DamageSound;

	UPROPERTY(EditDefaultsOnly, Category = "Particle") class UParticleSystem* HitParticles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = Damage) float Damage = 34.f;

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const//该函数用于读取私有变量,const确保该变量不会被修改而只被读取
	{
		return ProjectileMovement;
	}

	void SetBallSpeed(float Speed);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))class UProjectileMovementComponent* ProjectileMovement;

};
