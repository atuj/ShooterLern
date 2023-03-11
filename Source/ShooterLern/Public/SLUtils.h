#pragma once

class SLUtils
{
public:
	template <typename T>
	static T* GetSLPlayerComponent(APawn* PlayerPawn)
	{
		if(!PlayerPawn) return nullptr;
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);;
	}
};