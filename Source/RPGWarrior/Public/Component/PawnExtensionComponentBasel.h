// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBasel.generated.h"

/**
 * 扩展Actor组件的基类
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGWARRIOR_API UPawnExtensionComponentBasel : public UActorComponent
{
	GENERATED_BODY()

public:
	UPawnExtensionComponentBasel();

protected:
	virtual void BeginPlay() override;

	template <class T>
	T* GetOwningPawn() const
	{
		// 编译时静态断言T必须是APawn的子类,即From(T)必须可以转换为To(APawn)
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "T must inherit from APawn");
		return Cast<T>(GetOwner());
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "T must inherit from AController");

		const auto InCon = GetOwningPawn();
		auto       Res   = InCon ? InCon->GetController<T>() : nullptr;

		return Res;
	}

	APawn* GetOwningPawn() const { return GetOwningPawn<APawn>(); }
};
