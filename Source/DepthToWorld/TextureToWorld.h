// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextureToWorld.generated.h"

/**
 * 
 */


UCLASS()
class DEPTHTOWORLD_API UTextureToWorld : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FVector DeprojectWithDepth(const FVector2D& ScreenPos, const FIntRect& ViewRect, const FMatrix& InvViewProjMatrix, float z);
	UFUNCTION(BlueprintCallable)
	static FVector ScreenCaptureDeproject(USceneCaptureComponent2D* SceneCapture, UTextureRenderTarget* Texture, const FVector2D& UV, const FVector2D& ScreenPosition);

};
