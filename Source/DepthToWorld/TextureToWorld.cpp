// Fill out your copyright notice in the Description page of Project Settings.


#include "TextureToWorld.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"

FVector UTextureToWorld::DeprojectWithDepth(const FVector2D& ScreenPos, const FIntRect& ViewRect, const FMatrix& InvViewProjMatrix, float z) {
	const FVector2D Normalized(ScreenPos.X / ViewRect.Width(),
		ScreenPos.Y / ViewRect.Height());
	const float ScreenSpaceX = (Normalized.X - 0.5f) * 2.0f;
	const float ScreenSpaceY = ((1.0f - Normalized.Y) - 0.5f) * 2.0f;
	auto PosInScreenSpaceBack = FVector4(ScreenSpaceX * z, ScreenSpaceY * z, GNearClippingPlane, z);

	auto HGWorld = InvViewProjMatrix.TransformFVector4(PosInScreenSpaceBack);
	auto world = FVector(HGWorld);
	if (HGWorld.W != 0.0f)
	{
		world /= HGWorld.W;
	}
	return world;
}

FVector UTextureToWorld::ScreenCaptureDeproject(USceneCaptureComponent2D* SceneCapture, UTextureRenderTarget* Texture, const FVector2D& UV, const FVector2D& ScreenPosition) {
	if (Texture || SceneCapture) {

		FRenderTarget* RenderTarget = Texture->GameThread_GetRenderTargetResource();
	
		TArray<FLinearColor> LinearColors;
		RenderTarget->ReadLinearColorPixels(LinearColors);
	
		int32 x = UV.X * RenderTarget->GetSizeXY().X;
		int32 y = UV.Y * RenderTarget->GetSizeXY().Y;

		FLinearColor LinearColor = LinearColors[x + y * RenderTarget->GetSizeXY().X];
	
		FVector2D Result = FVector2D(1, 1);
		if (GEngine && GEngine->GameViewport)
		{
			GEngine->GameViewport->GetViewportSize( /*out*/Result);
		}

		FMinimalViewInfo View;
		SceneCapture->GetCameraView(0.1, View);
		FMatrix viewMatrix, projectionMatrix, viewProjectionMatrix;
		UGameplayStatics::GetViewProjectionMatrix(View, viewMatrix, projectionMatrix, viewProjectionMatrix);
		
		float Depth = LinearColor.A;
		FVector World = DeprojectWithDepth(FVector2D(x, y), FIntRect(0, 0, Result.X, Result.Y), viewProjectionMatrix.Inverse(), Depth);
		return World;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Render target or scene capture is null"));
	}
	return FVector(0);

}