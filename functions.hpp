#pragma once
#include "offsets.hpp"
#include "memory.hpp"
#include "math.hpp"
#include "structs.hpp"
#include "xor.hpp"
#include <Windows.h>
#include "ret_spoof.h"
#include "spoof.h"

class fmemory {
public:
	static uint64_t malloc(int32_t size, uint32_t aligment);
};

class uclass
{
public:
	uclass* super_class();
};




struct FPostProcessSettings final
{
public:
	uint8_t                                         bOverride_TemperatureType : 1;                     // 0x0000(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_WhiteTemp : 1;                           // 0x0000(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_WhiteTint : 1;                           // 0x0000(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturation : 1;                     // 0x0000(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrast : 1;                       // 0x0000(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGamma : 1;                          // 0x0000(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGain : 1;                           // 0x0000(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffset : 1;                         // 0x0000(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationShadows : 1;              // 0x0001(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastShadows : 1;                // 0x0001(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaShadows : 1;                   // 0x0001(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainShadows : 1;                    // 0x0001(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetShadows : 1;                  // 0x0001(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationMidtones : 1;             // 0x0001(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastMidtones : 1;               // 0x0001(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaMidtones : 1;                  // 0x0001(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainMidtones : 1;                   // 0x0002(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetMidtones : 1;                 // 0x0002(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationHighlights : 1;           // 0x0002(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastHighlights : 1;             // 0x0002(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaHighlights : 1;                // 0x0002(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainHighlights : 1;                 // 0x0002(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetHighlights : 1;               // 0x0002(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionShadowsMax : 1;           // 0x0002(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionHighlightsMin : 1;        // 0x0003(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionHighlightsMax : 1;        // 0x0003(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BlueCorrection : 1;                      // 0x0003(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ExpandGamut : 1;                         // 0x0003(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ToneCurveAmount : 1;                     // 0x0003(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmSlope : 1;                           // 0x0003(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmToe : 1;                             // 0x0003(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmShoulder : 1;                        // 0x0003(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmBlackClip : 1;                       // 0x0004(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmWhiteClip : 1;                       // 0x0004(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_SceneColorTint : 1;                      // 0x0004(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_SceneFringeIntensity : 1;                // 0x0004(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ChromaticAberrationStartOffset : 1;      // 0x0004(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientCubemapTint : 1;                  // 0x0004(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientCubemapIntensity : 1;             // 0x0004(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomMethod : 1;                         // 0x0004(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomIntensity : 1;                      // 0x0005(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomThreshold : 1;                      // 0x0005(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom1Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom1Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom2Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom2Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom3Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom3Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom4Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom4Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom5Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom5Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom6Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom6Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomSizeScale : 1;                      // 0x0006(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionTexture : 1;             // 0x0006(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionScatterDispersion : 1;   // 0x0007(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionSize : 1;                // 0x0007(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionCenterUV : 1;            // 0x0007(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilter : 1;           // 0x0007(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMin : 1;        // 0x0007(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMax : 1;        // 0x0007(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMult : 1;       // 0x0007(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionBufferScale : 1;         // 0x0007(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMaskIntensity : 1;              // 0x0008(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMaskTint : 1;                   // 0x0008(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMask : 1;                       // 0x0008(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_CameraShutterSpeed : 1;                  // 0x0008(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_CameraISO : 1;                           // 0x0008(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMethod : 1;                  // 0x0008(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureLowPercent : 1;              // 0x0008(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureHighPercent : 1;             // 0x0008(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMinBrightness : 1;           // 0x0009(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMaxBrightness : 1;           // 0x0009(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureCalibrationConstant : 1;     // 0x0009(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureSpeedUp : 1;                 // 0x0009(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureSpeedDown : 1;               // 0x0009(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureBias : 1;                    // 0x0009(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureBiasCurve : 1;               // 0x0009(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMeterMask : 1;               // 0x0009(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureApplyPhysicalCameraExposure : 1; // 0x000A(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_HistogramLogMin : 1;                     // 0x000A(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_HistogramLogMax : 1;                     // 0x000A(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureContrastScale : 1;          // 0x000A(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureHighlightContrastScale : 1; // 0x000A(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureShadowContrastScale : 1;    // 0x000A(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureDetailStrength : 1;         // 0x000A(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureBlurredLuminanceBlend : 1;  // 0x000A(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureBlurredLuminanceKernelSizePercent : 1; // 0x000B(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureMiddleGreyBias : 1;         // 0x000B(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareIntensity : 1;                  // 0x000B(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareTint : 1;                       // 0x000B(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareTints : 1;                      // 0x000B(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareBokehSize : 1;                  // 0x000B(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareBokehShape : 1;                 // 0x000B(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareThreshold : 1;                  // 0x000B(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_VignetteIntensity : 1;                   // 0x000C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Sharpen : 1;                             // 0x000C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresVignetteIntensity : 1;               // 0x000C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresVignetteSize : 1;                    // 0x000C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresVignetteCurve : 1;                   // 0x000C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_GrainIntensity : 1;                      // 0x000C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_GrainJitter : 1;                         // 0x000C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensity : 1;                  // 0x000C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityShadows : 1;           // 0x000D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityMidtones : 1;          // 0x000D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityHighlights : 1;        // 0x000D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainShadowsMax : 1;                 // 0x000D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainHighlightsMin : 1;              // 0x000D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainHighlightsMax : 1;              // 0x000D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainTexelSize : 1;                  // 0x000D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainTexture : 1;                    // 0x000D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionIntensity : 1;           // 0x000E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionStaticFraction : 1;      // 0x000E(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionRadius : 1;              // 0x000E(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionFadeDistance : 1;        // 0x000E(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionFadeRadius : 1;          // 0x000E(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionDistance : 1;            // 0x000E(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionRadiusInWS : 1;          // 0x000E(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionPower : 1;               // 0x000E(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionBias : 1;                // 0x000F(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionQuality : 1;             // 0x000F(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipBlend : 1;            // 0x000F(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipScale : 1;            // 0x000F(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipThreshold : 1;        // 0x000F(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionTemporalBlendWeight : 1; // 0x000F(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_F_6 : 2;                                    // 0x000F(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         bOverride_RayTracingAO : 1;                        // 0x0010(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAOSamplesPerPixel : 1;         // 0x0010(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAOIntensity : 1;               // 0x0010(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAORadius : 1;                  // 0x0010(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_10_4 : 4;                                   // 0x0010(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_11[0x3];                                       // 0x0011(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LPVIntensity : 1;                        // 0x0014(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionIntensity : 1;    // 0x0014(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionRadius : 1;       // 0x0014(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDiffuseOcclusionExponent : 1;         // 0x0014(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSpecularOcclusionExponent : 1;        // 0x0014(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDiffuseOcclusionIntensity : 1;        // 0x0014(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSpecularOcclusionIntensity : 1;       // 0x0014(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSize : 1;                             // 0x0014(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSecondaryOcclusionIntensity : 1;      // 0x0015(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSecondaryBounceIntensity : 1;         // 0x0015(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVGeometryVolumeBias : 1;               // 0x0015(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVVplInjectionBias : 1;                 // 0x0015(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVEmissiveInjectionIntensity : 1;       // 0x0015(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVFadeRange : 1;                        // 0x0015(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionFadeRange : 1;    // 0x0015(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_IndirectLightingColor : 1;               // 0x0015(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_IndirectLightingIntensity : 1;           // 0x0016(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGradingIntensity : 1;               // 0x0016(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGradingLUT : 1;                     // 0x0016(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFocalDistance : 1;           // 0x0016(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFstop : 1;                   // 0x0016(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldMinFstop : 1;                // 0x0016(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldBladeCount : 1;              // 0x0016(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSensorWidth : 1;             // 0x0016(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSqueezeFactor : 1;           // 0x0017(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldDepthBlurRadius : 1;         // 0x0017(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldDepthBlurAmount : 1;         // 0x0017(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFocalRegion : 1;             // 0x0017(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldNearTransitionRegion : 1;    // 0x0017(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFarTransitionRegion : 1;     // 0x0017(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldScale : 1;                   // 0x0017(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldNearBlurSize : 1;            // 0x0017(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFarBlurSize : 1;             // 0x0018(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MobileHQGaussian : 1;                    // 0x0018(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldOcclusion : 1;               // 0x0018(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSkyFocusDistance : 1;        // 0x0018(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldVignetteSize : 1;            // 0x0018(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurAmount : 1;                    // 0x0018(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurMax : 1;                       // 0x0018(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurTargetFPS : 1;                 // 0x0018(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurPerObjectSize : 1;             // 0x0019(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenPercentage : 1;                    // 0x0019(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ReflectionMethod : 1;                    // 0x0019(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenReflectionQuality : 1;              // 0x0019(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionIntensity : 1;      // 0x0019(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionQuality : 1;        // 0x0019(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionMaxRoughness : 1;   // 0x0019(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionRoughnessScale : 1; // 0x0019(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_1A[0x2];                                       // 0x001A(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_ReflectionsType : 1;                     // 0x001C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsMaxRoughness : 1;   // 0x001C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsMaxBounces : 1;     // 0x001C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsSamplesPerPixel : 1; // 0x001C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsShadows : 1;        // 0x001C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsTranslucency : 1;   // 0x001C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_TranslucencyType : 1;                    // 0x001C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyMaxRoughness : 1;  // 0x001C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyRefractionRays : 1; // 0x001D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencySamplesPerPixel : 1; // 0x001D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyShadows : 1;       // 0x001D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyRefraction : 1;    // 0x001D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DynamicGlobalIlluminationMethod : 1;     // 0x001D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneLightingQuality : 1;           // 0x001D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneDetail : 1;                    // 0x001D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneViewDistance : 1;              // 0x001D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneLightingUpdateSpeed : 1;       // 0x001E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFinalGatherQuality : 1;             // 0x001E(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFinalGatherLightingUpdateSpeed : 1; // 0x001E(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenMaxTraceDistance : 1;               // 0x001E(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenDiffuseColorBoost : 1;              // 0x001E(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSkylightLeaking : 1;                // 0x001E(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFullSkylightLeakingDistance : 1;    // 0x001E(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_1E_7 : 1;                                   // 0x001E(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_1F[0x1];                                       // 0x001F(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenRayLightingMode : 1;                // 0x0020(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFrontLayerTranslucencyReflections : 1; // 0x0020(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_20_2 : 6;                                   // 0x0020(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_21[0x3];                                       // 0x0021(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenMaxReflectionBounces : 1;           // 0x0024(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_24_1 : 7;                                   // 0x0024(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_25[0x3];                                       // 0x0025(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenSurfaceCacheResolution : 1;         // 0x0028(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_28_1 : 7;                                   // 0x0028(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_29[0x3];                                       // 0x0029(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_RayTracingGI : 1;                        // 0x002C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingGIMaxBounces : 1;              // 0x002C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingGISamplesPerPixel : 1;         // 0x002C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingMaxBounces : 1;               // 0x002C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingSamplesPerPixel : 1;          // 0x002C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingMaxPathExposure : 1;          // 0x002C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableReferenceDOF : 1;       // 0x002C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableReferenceAtmosphere : 1; // 0x002C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableDenoiser : 1;           // 0x002D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeEmissive : 1;          // 0x002D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectEmissive : 1;  // 0x002D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeDiffuse : 1;           // 0x002D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectDiffuse : 1;   // 0x002D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeSpecular : 1;          // 0x002D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectSpecular : 1;  // 0x002D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeVolume : 1;            // 0x002D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectVolume : 1;    // 0x002E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_2E_1 : 7;                                   // 0x002E(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_2F[0x1];                                       // 0x002F(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bMobileHQGaussian : 1;                             // 0x0030(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_30_1 : 7;                                   // 0x0030(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_31[0x3];                                       // 0x0031(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_AresAdaptiveSharpenCurveSlope : 1;       // 0x0034(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenDarkCompressionLow : 1; // 0x0034(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenDarkCompressionHigh : 1; // 0x0034(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenDarkOvershoot : 1;    // 0x0034(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenEnable : 1;           // 0x0034(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenLightCompressionLow : 1; // 0x0034(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenLightCompressionHigh : 1; // 0x0034(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenLightOvershoot : 1;   // 0x0034(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenPowerMeanPValue : 1;  // 0x0035(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenScaleCompressionSlope : 1; // 0x0035(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenScaleLim : 1;         // 0x0035(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresAdaptiveSharpenStrength : 1;         // 0x0035(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresCharacterOutlinesBlurDistance : 1;   // 0x0035(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresCharacterOutlinesColor : 1;          // 0x0035(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresCharacterOutlinesOverlayColor : 1;   // 0x0035(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresCharacterOutlinesPixelOffset : 1;    // 0x0035(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityBlendIfDark : 1;              // 0x0036(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityBlendIfLight : 1;             // 0x0036(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityBlendMode : 1;                // 0x0036(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityDarkIntensity : 1;            // 0x0036(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityEnable : 1;                   // 0x0036(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityLightIntensity : 1;           // 0x0036(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityOffset : 1;                   // 0x0036(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityRadius : 1;                   // 0x0036(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityStrength : 1;                 // 0x0037(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityViewBlendIfMask : 1;          // 0x0037(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AresClarityViewMask : 1;                 // 0x0037(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_37_3 : 5;                                   // 0x0037(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         bOverride_IndirectLightingScaleCurve : 1;          // 0x0038(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_38_1 : 7;                                   // 0x0038(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_39[0x3];                                       // 0x0039(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_AmbientOcclusionTintColor : 1;           // 0x003C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAresAdaptiveSharpenEnable : 1;                    // 0x003C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAresClarityEnable : 1;                            // 0x003C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAresClarityViewBlendIfMask : 1;                   // 0x003C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAresClarityViewMask : 1;                          // 0x003C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_3D[0x3];                                       // 0x003D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         Pad_43[0x1];                                       // 0x0043(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         WhiteTemp;                                         // 0x0044(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         WhiteTint;                                         // 0x0048(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_4C[0x4];                                       // 0x004C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         ColorCorrectionHighlightsMin;                      // 0x02D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorCorrectionHighlightsMax;                      // 0x02D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorCorrectionShadowsMax;                         // 0x02D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BlueCorrection;                                    // 0x02DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ExpandGamut;                                       // 0x02E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ToneCurveAmount;                                   // 0x02E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmSlope;                                         // 0x02E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmToe;                                           // 0x02EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmShoulder;                                      // 0x02F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmBlackClip;                                     // 0x02F4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmWhiteClip;                                     // 0x02F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         SceneFringeIntensity;                              // 0x030C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ChromaticAberrationStartOffset;                    // 0x0310(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomIntensity;                                    // 0x0314(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomThreshold;                                    // 0x0318(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomSizeScale;                                    // 0x031C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom1Size;                                        // 0x0320(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom2Size;                                        // 0x0324(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom3Size;                                        // 0x0328(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom4Size;                                        // 0x032C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom5Size;                                        // 0x0330(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom6Size;                                        // 0x0334(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionScatterDispersion;                 // 0x0398(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionSize;                              // 0x039C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture2D* BloomConvolutionTexture;                           // 0x03A0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMin;                      // 0x03B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMax;                      // 0x03BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMult;                     // 0x03C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionBufferScale;                       // 0x03C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture* BloomDirtMask;                                     // 0x03C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomDirtMaskIntensity;                            // 0x03D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_3E5[0x3];                                      // 0x03E5(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         IndirectLightingIntensity;                         // 0x03F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneLightingQuality;                         // 0x03FC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneDetail;                                  // 0x0400(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneViewDistance;                            // 0x0404(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneLightingUpdateSpeed;                     // 0x0408(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFinalGatherQuality;                           // 0x040C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFinalGatherLightingUpdateSpeed;               // 0x0410(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenMaxTraceDistance;                             // 0x0414(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenDiffuseColorBoost;                            // 0x0418(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSkylightLeaking;                              // 0x041C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFullSkylightLeakingDistance;                  // 0x0420(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSurfaceCacheResolution;                       // 0x0424(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_429[0x3];                                      // 0x0429(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         RayTracingGIMaxBounces;                            // 0x042C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingGISamplesPerPixel;                       // 0x0430(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_436[0x2];                                      // 0x0436(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LumenReflectionQuality;                            // 0x0438(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         LumenFrontLayerTranslucencyReflections : 1;        // 0x043D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_43E[0x2];                                      // 0x043E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         LumenMaxReflectionBounces;                         // 0x0440(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionIntensity;                    // 0x0444(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionQuality;                      // 0x0448(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionMaxRoughness;                 // 0x044C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         RayTracingReflectionsMaxRoughness;                 // 0x0450(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingReflectionsMaxBounces;                   // 0x0454(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingReflectionsSamplesPerPixel;              // 0x0458(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         RayTracingReflectionsTranslucency : 1;             // 0x045D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_45E[0x2];                                      // 0x045E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         AmbientCubemapIntensity;                           // 0x0470(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_474[0x4];                                      // 0x0474(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTextureCube* AmbientCubemap;                                    // 0x0478(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CameraShutterSpeed;                                // 0x0480(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CameraISO;                                         // 0x0484(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFstop;                                 // 0x0488(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldMinFstop;                              // 0x048C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         DepthOfFieldBladeCount;                            // 0x0490(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureBias;                                  // 0x0494(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureBiasBackup;                            // 0x0498(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bOverride_AutoExposureBiasBackup : 1;              // 0x049C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_49C_1 : 7;                                  // 0x049C(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_49D[0x3];                                      // 0x049D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         AutoExposureApplyPhysicalCameraExposure : 1;       // 0x04A0(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_4A1[0x7];                                      // 0x04A1(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UCurveFloat* AutoExposureBiasCurve;                             // 0x04A8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture* AutoExposureMeterMask;                             // 0x04B0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureLowPercent;                            // 0x04B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureHighPercent;                           // 0x04BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureMinBrightness;                         // 0x04C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureMaxBrightness;                         // 0x04C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureSpeedUp;                               // 0x04C8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureSpeedDown;                             // 0x04CC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         HistogramLogMin;                                   // 0x04D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         HistogramLogMax;                                   // 0x04D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureCalibrationConstant;                   // 0x04D8(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureContrastScale;                        // 0x04DC(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureHighlightContrastScale;               // 0x04E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureShadowContrastScale;                  // 0x04E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureDetailStrength;                       // 0x04E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureBlurredLuminanceBlend;                // 0x04EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureBlurredLuminanceKernelSizePercent;    // 0x04F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureMiddleGreyBias;                       // 0x04F4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareIntensity;                                // 0x04F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareBokehSize;                                // 0x050C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareThreshold;                                // 0x0510(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_514[0x4];                                      // 0x0514(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTexture* LensFlareBokehShape;                               // 0x0518(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VignetteIntensity;                                 // 0x05A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Sharpen;                                           // 0x05A4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresVignetteIntensity;                             // 0x05A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresVignetteSize;                                  // 0x05AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresVignetteCurve;                                 // 0x05B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bOverride_FilmWhitePoint : 1;                      // 0x05B4(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmSaturation : 1;                      // 0x05B4(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmChannelMixerRed : 1;                 // 0x05B4(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmChannelMixerGreen : 1;               // 0x05B4(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmChannelMixerBlue : 1;                // 0x05B4(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmContrast : 1;                        // 0x05B4(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmDynamicRange : 1;                    // 0x05B4(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmHealAmount : 1;                      // 0x05B4(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmToeAmount : 1;                       // 0x05B5(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmShadowTint : 1;                      // 0x05B5(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmShadowTintBlend : 1;                 // 0x05B5(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmShadowTintAmount : 1;                // 0x05B5(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_5B6[0x2];                                      // 0x05B6(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         FilmShadowTintBlend;                               // 0x05D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmShadowTintAmount;                              // 0x05DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmSaturation;                                    // 0x05E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmContrast;                                      // 0x0614(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmToeAmount;                                     // 0x0618(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmHealAmount;                                    // 0x061C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmDynamicRange;                                  // 0x0620(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         GrainJitter;                                       // 0x0624(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         GrainIntensity;                                    // 0x0628(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensity;                                // 0x062C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityShadows;                         // 0x0630(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityMidtones;                        // 0x0634(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityHighlights;                      // 0x0638(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainShadowsMax;                               // 0x063C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainHighlightsMin;                            // 0x0640(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainHighlightsMax;                            // 0x0644(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainTexelSize;                                // 0x0648(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_64C[0x4];                                      // 0x064C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTexture2D* FilmGrainTexture;                                  // 0x0650(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionIntensity;                         // 0x0658(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionStaticFraction;                    // 0x065C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionRadius;                            // 0x0660(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         AmbientOcclusionRadiusInWS : 1;                    // 0x0664(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_665[0x3];                                      // 0x0665(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         AmbientOcclusionFadeDistance;                      // 0x0668(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionFadeRadius;                        // 0x066C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionDistance;                          // 0x0670(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionPower;                             // 0x0674(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionBias;                              // 0x0678(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionQuality;                           // 0x067C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipBlend;                          // 0x0680(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipScale;                          // 0x0684(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipThreshold;                      // 0x0688(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionTemporalBlendWeight;               // 0x068C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         RayTracingAO : 1;                                  // 0x0690(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_691[0x3];                                      // 0x0691(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         RayTracingAOSamplesPerPixel;                       // 0x0694(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         RayTracingAOIntensity;                             // 0x0698(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         RayTracingAORadius;                                // 0x069C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorGradingIntensity;                             // 0x06A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_6A4[0x4];                                      // 0x06A4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTexture* ColorGradingLUT;                                   // 0x06A8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSensorWidth;                           // 0x06B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSqueezeFactor;                         // 0x06B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFocalDistance;                         // 0x06B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldDepthBlurAmount;                       // 0x06BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldDepthBlurRadius;                       // 0x06C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFocalRegion;                           // 0x06C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldNearTransitionRegion;                  // 0x06C8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFarTransitionRegion;                   // 0x06CC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldScale;                                 // 0x06D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldNearBlurSize;                          // 0x06D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFarBlurSize;                           // 0x06D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldOcclusion;                             // 0x06DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSkyFocusDistance;                      // 0x06E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldVignetteSize;                          // 0x06E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurAmount;                                  // 0x06E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurMax;                                     // 0x06EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         MotionBlurTargetFPS;                               // 0x06F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurPerObjectSize;                           // 0x06F4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVIntensity;                                      // 0x06F8(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVVplInjectionBias;                               // 0x06FC(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSize;                                           // 0x0700(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSecondaryOcclusionIntensity;                    // 0x0704(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSecondaryBounceIntensity;                       // 0x0708(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVGeometryVolumeBias;                             // 0x070C(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVEmissiveInjectionIntensity;                     // 0x0710(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionIntensity;                  // 0x0714(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionRadius;                     // 0x0718(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDiffuseOcclusionExponent;                       // 0x071C(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSpecularOcclusionExponent;                      // 0x0720(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDiffuseOcclusionIntensity;                      // 0x0724(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSpecularOcclusionIntensity;                     // 0x0728(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_72D[0x3];                                      // 0x072D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         RayTracingTranslucencyMaxRoughness;                // 0x0730(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingTranslucencyRefractionRays;              // 0x0734(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingTranslucencySamplesPerPixel;             // 0x0738(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

	uint8_t                                         RayTracingTranslucencyRefraction : 1;              // 0x073D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_73E[0x2];                                      // 0x073E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         PathTracingMaxBounces;                             // 0x0740(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         PathTracingSamplesPerPixel;                        // 0x0744(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         PathTracingMaxPathExposure;                        // 0x0748(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         PathTracingEnableReferenceDOF : 1;                 // 0x074C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingEnableReferenceAtmosphere : 1;          // 0x074C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingEnableDenoiser : 1;                     // 0x074C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeEmissive : 1;                    // 0x074C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectEmissive : 1;            // 0x074C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeDiffuse : 1;                     // 0x074C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectDiffuse : 1;             // 0x074C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeSpecular : 1;                    // 0x074C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectSpecular : 1;            // 0x074D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeVolume : 1;                      // 0x074D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectVolume : 1;              // 0x074D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_74E[0x2];                                      // 0x074E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LPVFadeRange;                                      // 0x0750(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionFadeRange;                  // 0x0754(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenPercentage;                                  // 0x0758(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_75C[0x4];                                      // 0x075C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         AresAdaptiveSharpenCurveSlope;                     // 0x0780(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenDarkCompressionHigh;            // 0x0784(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenDarkCompressionLow;             // 0x0788(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenDarkOvershoot;                  // 0x078C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenLightCompressionHigh;           // 0x0790(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenLightCompressionLow;            // 0x0794(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenLightOvershoot;                 // 0x0798(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenPowerMeanPValue;                // 0x079C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenScaleCompressionSlope;          // 0x07A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenScaleLim;                       // 0x07A4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresAdaptiveSharpenStrength;                       // 0x07A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresCharacterOutlinesBlurDistance;                 // 0x07AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         AresCharacterOutlinesPixelOffset;                  // 0x07D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         AresClarityBlendIfDark;                            // 0x07D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         AresClarityBlendIfLight;                           // 0x07D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_7DD[0x3];                                      // 0x07DD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         AresClarityDarkIntensity;                          // 0x07E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresClarityLightIntensity;                         // 0x07E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresClarityOffset;                                 // 0x07E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         AresClarityRadius;                                 // 0x07EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AresClarityStrength;                               // 0x07F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_7F4[0x4];                                      // 0x07F4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UCurveFloat* IndirectLightingScaleCurve;                        // 0x07F8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, Interp, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                               ColorGain;
	fvector                               ColorSaturation;                                   // 0x0050(0x0020)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                          SceneColorTint;                                    // 0x02FC(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                               ColorGamma;                                        // 0x0090(0x0020)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                              ColorContrast;                                     // 0x0070(0x0020)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};




struct FMinimalViewInfo {
	fvector Location;
	fvector Rotation;
	float FOV;
	float DesiredFOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float PerspectiveNearClipPlane;
	float AspectRatio;
	char bConstrainAspectRatio : 1;
	char pad_30_2 : 6;
	char pad_31[0x3];
	char pad_35[0x3];
	float PostProcessBlendWeight;
	char pad_3C[0x4];
	FPostProcessSettings PostProcessSettings;
	fvector2d OffCenterProjectionOffset;
	char pad_658[0x48];
};







class uobject {
public:
	uclass* object_class();

	template <typename t>
	static t static_find_object(uobject* klass, uobject* outer, const wchar_t* name) {
		
		return reinterpret_cast<t(*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(klass, outer, name, false, 0x46C4660, (void*)(memory::module_base + offsets::static_find_object));
	}

	template <typename t>
	static t find_object(const wchar_t* name, uobject* outer = nullptr) {
		
		return uobject::static_find_object<t>(nullptr, outer, name);
	}


	template<typename type = uobject> static inline type* find_object1(const wchar_t* name, uobject* outer = nullptr, bool exact = false) {
		
		return uobject::static_find_object<type*>(nullptr, outer, name);
	}

	//static uobject* StaticFindObject(uclass* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass)
	//{
	//	static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;

	//	auto StaticFindObjectFN = reinterpret_cast<uobject * (__fastcall*)(uclass*, uobject*, const wchar_t*, bool)>(StaticFindObjectAddress);

	//	return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	//}

	static uobject* StaticLoadObject(uobject* Class, uobject* InOuter, const wchar_t* Name);

	static uobject* StaticLoadObject(const wchar_t* ObjectPath);

	void process_event(uobject* function, void* args);

	static uobject* static_load_object(uobject* Class, uobject* InOuter, const wchar_t* Name);

	//void process_event2(void* class_, uobject* function, void* params);

	bool is_child_of(uclass* parent);

	template <typename type = uobject>
	type* cast() {
		return reinterpret_cast<type*>(this);
	}
};

template<class type> class enum_as_byte {
public:
	enum_as_byte() {}
	enum_as_byte(type value) : value(static_cast<std::uint8_t>(value)) {}

	explicit enum_as_byte(std::int32_t value) : value(static_cast<std::uint8_t>(value)) {}
	explicit enum_as_byte(std::uint8_t value) : value(value) {}

	operator type() const { return type(value); }
	type get() const { return type(value); }

private:
	std::uint8_t value;
};

static enum search_case : std::uint8_t {
	case_sensitive, ignore_case
};


struct utexture : public uobject {
	char pad_68[0x8]; // 0x68(0x08)
	int32_t LODBias; // 0x80(0x04)
	//enum class TextureGroup LODGroup; // 0x88(0x01)
	char pad_89[0x3]; // 0x89(0x03)
	char SRGB : 1; // 0x91(0x01)
	char bNoTiling : 1; // 0x91(0x01)
	char VirtualTextureStreaming : 1; // 0x91(0x01)
	char CompressionYCoCg : 1; // 0x91(0x01)
	char bNotOfflineProcessed : 1; // 0x91(0x01)
	char pad_91_5 : 3; // 0x91(0x01)
	char pad_92[0x2]; // 0x92(0x02)
	int32_t ForcedStreamingRefCount; // 0x94(0x04)
	char bAsyncResourceReleaseHasBeenStarted : 1; // 0x98(0x01)
	char pad_98_1 : 7; // 0x98(0x01)
	char pad_99[0x7]; // 0x99(0x07)
	tarray<struct UAssetUserData*> AssetUserData; // 0xa0(0x10)
	char pad_B0[0xe0]; // 0xb0(0xe0)
};

class utexture2d : public utexture
{
public:
	int32_t LevelIndex;
	int32_t FirstResourceMemMip;
	uint8_t bTemporarilyDisableStreaming : 1;
	uint8_t Pad_193[0x1];
	uint8_t Pad_19C[0x14];
};

class system : public uobject
{
public:
	static utexture2d* import_file_as_texture2d(uobject* world_context_object, fstring filename);
	static fstring get_object_name(uobject* object);
	static bool contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case = false, bool search_from_end = false);
	static bool starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case = ignore_case);
	uobject* get_outer_object(uobject* object);

	/*static inline __int64 decrypt_parent(uobject* parent) {
		static __int64(__fastcall * decrypt_function)(__int64);
		if (!decrypt_function) {
			decrypt_function = reinterpret_cast<decltype(decrypt_function)>(offsets::skin_decrypt + memory::module_base);
		}

		if (!decrypt_function) return 0x0;

		return decrypt_function((__int64)parent);
	}*/
};

class string_utils : public uobject
{
public:
	static auto STATIC_Conv_NameToString(fname InName) -> fstring;
	static fname string_to_name(fstring string);
	static bool contains(fstring SearchIn, fstring Substring, bool bUseCase = false, bool bSearchFromEnd = false);
	static fstring int_to_string(const int value);
};

class string : public uobject
{
public:
	static fname string_to_name(fstring string);
};

class equippable_skin_data_asset : public uobject
{
public:
	int32_t get_type() {
		fstring name = system::get_object_name(this);

		if (string_utils::contains(name, L"Default__BasePistol", true, false)) {
			return 1;
		}
		else if (string_utils::contains(name, L"Default__SawedOffShotgun", true, false) || string_utils::contains(name, L"Default__Slim", true, false)) {
			return 2;
		}
		else if (string_utils::contains(name, L"Default__AutoPistol", true, false) || string_utils::contains(name, L"Default__AutomaticPistol", true, false)) {
			return 3;
		}
		else if (string_utils::contains(name, L"Default__Luger", true, false)) {
			return 4;
		}
		else if (string_utils::contains(name, L"Default__Revolver", true, false)) {
			return 5;
		}
		else if (string_utils::contains(name, L"Default__Vector", true, false)) {
			return 6;
		}
		else if (string_utils::contains(name, L"Default__MP5", true, false) || string_utils::contains(name, L"Default__SubMachineGun_MP5", true, false)) {
			return 7;
		}
		else if (string_utils::contains(name, L"Default__PumpShotgun", true, false)) {
			return 8;
		}
		else if (string_utils::contains(name, L"Default__AutomaticShotgun", true, false) || string_utils::contains(name, L"Default__AutoShotgun", true, false)) {
			return 9;
		}
		else if (string_utils::contains(name, L"Default__Burst", true, false) || string_utils::contains(name, L"Default__AssaultRifle_Burst", true, false)) {
			return 10;
		}
		else if (string_utils::contains(name, L"Default__DMR", true, false)) {
			return 11;
		}
		else if (string_utils::contains(name, L"Default__AssaultRifle_ACR", true, false) || string_utils::contains(name, L"Default__Carbine", true, false)) {
			return 12;
		}
		else if (string_utils::contains(name, L"Default__AK", true, false) || string_utils::contains(name, L"Default__AssaultRifle_AK", true, false)) {
			return 13;
		}
		else if (string_utils::contains(name, L"Default__LeverSniperRifle", true, false) || string_utils::contains(name, L"Default__LeverSniper", true, false)) {
			return 14;
		}
		else if (string_utils::contains(name, L"Default__BoltSniper", true, false)) {
			return 15;
		}
		else if (string_utils::contains(name, L"Default__LMG", true, false) || string_utils::contains(name, L"Default__LightMachineGun", true, false)) {
			return 16;
		}
		else if (string_utils::contains(name, L"Default__HMG", true, false) || string_utils::contains(name, L"Default__HeavyMachineGun", true, false)) {
			return 17;
		}
		else if (string_utils::contains(name, L"Default__Melee", true, false)) {
			return 18;
		}
		else if (string_utils::contains(name, L"Default__DS_Gun", true, false)) {
			return 19;
		}
		return 0;
	}

	tarray<int> get_skin_levels();
};





struct firing_state : public uobject {
public:
	float cooldown() {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"ShooterGame.FiringStateComponent.GetCooldownTimeRemaining");
		if (!function || this == nullptr) {
			return false;
		}
		struct
		{
			float ret;
		} params;
		this->process_event(function, &params);
		return params.ret;
	}
};



class equippable_skin_chroma_inventory_model : public uobject
{
public:
	uobject* get_skin_chroma_data_asset();
};

class equippable_skin_inventory_model : public uobject
{
public:
	equippable_skin_data_asset* get_skin_data_asset();
	equippable_skin_chroma_inventory_model* get_skin_inventory_chroma_asset();
};

class equippable_charm_level_data_asset : public uobject
{
public:
	int get_charm_level();
};

class equippable_charm_instance_inventory_model : public uobject
{
public:
	uobject* get_charm_data_asset();
	equippable_charm_level_data_asset* get_charm_level_data_asset();
};

class equippable_inventory_model : public uobject
{
public:
	equippable_skin_inventory_model* get_equipped_skin_model();
	equippable_charm_instance_inventory_model* get_equipped_charm_instance();
};

class umaterialinterface : public uobject
{
public:
	class usubsurfaceprofile* SubsurfaceProfile;
	tarray<struct fmaterialtextureinfo>            TextureStreamingData;
	tarray<class uassetuserdata*>                  AssetUserData;
};

struct fskeletalmaterial final
{
public:
	umaterialinterface* MaterialInterface;
	fname  MaterialSlotName;
};


struct UActorComponent : uobject {
	char pad_30[0x18]; // 0x30(0x18)
	tarray<struct FName> ComponentTags; // 0x78(0x10)
	struct tarray<struct UAssetUserData*> AssetUserData; // 0x88(0x10)
	char pad_98[0x4]; // 0x98(0x04)
	int32_t UCSSerializationIndex; // 0x9c(0x04)
	char pad_A0_0 : 3; // 0xa0(0x01)
	char bNetAddressable : 1; // 0xa0(0x01)
	char bReplicates : 1; // 0xa0(0x01)
	char pad_A0_5 : 3; // 0xa0(0x01)
	char pad_A1[0x7]; // 0xa1(0x07)
	uint64_t TickTimingsAccumulatedTotal; // 0xa8(0x08)
	uint64_t TickTimingsAccumulatedBP; // 0xb0(0x08)
	uint64_t TickTimingsStart; // 0xb8(0x08)
	char pad_C0[0x1]; // 0xc0(0x01)
	char pad_C1_0 : 3; // 0xc1(0x01)
	char bAutoActivate : 1; // 0xc1(0x01)
	char bIsActive : 1; // 0xc1(0x01)
	char bEditableWhenInherited : 1; // 0xc1(0x01)
	char pad_C1_6 : 1; // 0xc1(0x01)
	char bCanEverAffectNavigation : 1; // 0xc1(0x01)
	char pad_C2_0 : 1; // 0xc2(0x01)
	char bIsEditorOnly : 1; // 0xc2(0x01)
	char pad_C2_2 : 6; // 0xc2(0x01)
	char pad_C3[0x1]; // 0xc3(0x01)
	char pad_C7[0x1]; // 0xc7(0x01)
	tarray<struct FSimpleMemberReference> UCSModifiedProperties; // 0xc8(0x10)
	char pad_D8[0x10]; // 0xd8(0x10)
};

enum class EAttachLocation : uint8_t
{
	KeepRelativeOffset = 0,
	KeepWorldPosition = 1,
	SnapToTarget = 2,
	SnapToTargetIncludingScale = 3,
	EAttachLocation_MAX = 4,
};

enum class EAttachmentRule : uint8_t
{
	KeepRelative = 0,
	KeepWorld = 1,
	SnapToTarget = 2,
	EAttachmentRule_MAX = 3,
};

enum class EDetachmentRule : uint8_t
{
	KeepRelative = 0,
	KeepWorld = 1,
	EDetachmentRule_MAX = 2,
};

class alignas(0x10) USceneComponent : public UActorComponent
{
public:
	uint8_t                                         Pad_A0[0x8];                                       // 0x00A0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	//TWeakObjectPtr<class APhysicsVolume>          PhysicsVolume;                                     // 0x00A8(0x0008)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	USceneComponent* AttachParent;                                      // 0x00B0(0x0008)(ExportObject, Net, ZeroConstructor, InstancedReference, RepNotify, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	fname                                   AttachSocketName;                                  // 0x00B8(0x0008)(Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_C0[0x8];                                       // 0x00C0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	tarray<USceneComponent*>                AttachChildren;                                    // 0x00C8(0x0010)(ExportObject, Net, ZeroConstructor, Transient, RepNotify, ContainsInstancedReference, UObjectWrapper, NativeAccessSpecifierPrivate)
	tarray<USceneComponent*>                ClientAttachedChildren;                            // 0x00D8(0x0010)(ExportObject, ZeroConstructor, Transient, ContainsInstancedReference, UObjectWrapper, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_E8[0x40];                                      // 0x00E8(0x0040)(Fixing Size After Last Property [ Dumper-7 ])
	fvector                                RelativeLocation;                                  // 0x0128(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	frotator                               RelativeRotation;                                  // 0x0140(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, NativeAccessSpecifierPrivate)
	fvector                                RelativeScale3D;                                   // 0x0158(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	fvector                                ComponentVelocity;                                 // 0x0170(0x0018)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bComponentToWorldUpdated : 1;                      // 0x0188(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         BitPad_188_1 : 1;                                  // 0x0188(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
	uint8_t                                         bAbsoluteLocation : 1;                             // 0x0188(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bAbsoluteRotation : 1;                             // 0x0188(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bAbsoluteScale : 1;                                // 0x0188(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bVisible : 1;                                      // 0x0188(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, Net, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldBeAttached : 1;                             // 0x0188(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapLocationWhenAttached : 1;               // 0x0188(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapRotationWhenAttached : 1;               // 0x0189(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapScaleWhenAttached : 1;                  // 0x0189(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldUpdatePhysicsVolume : 1;                    // 0x0189(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bHiddenInGame : 1;                                 // 0x0189(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bUseAttachParentBound : 1;                         // 0x018B(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputeFastLocalBounds : 1;                       // 0x018B(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputeBoundsOnceForGame : 1;                     // 0x018B(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputedBoundsOnceForGame : 1;                    // 0x018B(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bIsNotRenderAttachmentRoot : 1;                    // 0x018B(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_18C[0x1];                                      // 0x018C(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         Pad_190[0xA0];                                    
	void GetChildrenComponents(bool bIncludeAllDescendants, tarray<USceneComponent*>* Children); // just lest do a another code for this part
};

class UMaterialInterface : public uobject
{
public:

	char pad_30[0x10]; // 0x30(0x10)
	uobject* SubsurfaceProfile; // 0x40(0x08)
	tarray<uobject*> SpecularProfiles; // 0x48(0x10)
	char bIncludedInBaseGame : 1; // 0x58(0x01)
	char pad_58_1 : 7; // 0x58(0x01)
	char pad_59[0x17]; // 0x59(0x17)
	uobject* LightmassSettings; // 0x70(0x24)
	char pad_94[0x4]; // 0x94(0x04)
	struct tarray<struct FMaterialTextureInfo> TextureStreamingData; // 0x98(0x10)
	struct tarray<struct UAssetUserData*> AssetUserData; // 0xa8(0x10)
	char pad_B8[0x18]; // 0xb8(0x18)

	e_blend_mode GetBlendMode();


};
struct UMaterialInstance : uobject
{
public:
	e_blend_mode GetBlendMode();

};

class uskeletalmeshcomponent : public uobject
{
public:
	fvector get_bone_location(int32_t index);
	int32_t get_num_bones();

	UMaterialInterface* GetMaterial(int32_t ElementIndex);
	//void SetRelativeScale3D(fvector newscale);
	fname get_bone_name(int32_t bone_index);
	fvector get_socket_location(fname socket_name);
	void set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport);
	void set_materials(const tarray<fskeletalmaterial>& in_materials);
	int32_t get_num_materials();
	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent);
	bool set_actor_rotation(frotator new_rotation, bool teleport_physics);
	void SetMaterial(int32_t ElementIndex, uobject* Material);
	void SetOutlineMode(EAresOutlineMode Mode);



	bool AttachTo(uskeletalmeshcomponent* InParent, fname InSocketName, EAttachLocation AttachType, bool bWeldSimulatedBodies);

	//void SetRelativeRotation(frotator& NewRotation);

	void SetRelativeRotation(void* Target, const FRotator& Rotation, bool bSweep, bool bTeleport);

	//void SetRelativeLocation(fvector NewLocation);

	bool AttachToComponent(USceneComponent* Parent, fname SocketName, EAttachmentRule LocationRule, EAttachmentRule RotationRule, EAttachmentRule ScaleRule, bool bWeldSimulatedBodies);

	void SetRelativeScale3D(fvector NewScale3D);

	
	
};

class USkinnedMeshComponent : public uobject
{
public:

};


enum class EAresItemSlot : uint8_t
{
    Primary = 0,
    Secondary = 1,
    Melee = 2,
    GrenadeAbility = 3,
    Ability1 = 4,
    Ability2 = 5,
    Passive = 6,
    Level = 7,
    Invisible = 8,
    Ultimate = 9,
    Unarmed = 10,
    Armor = 11,
    Backpack = 12,
    Totem = 13,
    PrimaryStorage = 14,
    SecondaryStorage = 15,
    Count = 16,
    Any = 253,
    Invalid = 254,
    EAresItemSlot_MAX = 255,
};

class currentequippable : public uobject
{
public:
	struct type {
		const wchar_t* search = nullptr;
		const char* config = nullptr;
		std::int32_t index = 0;

		const bool is_valid() const noexcept {
			return this->search != nullptr || this->config != nullptr;
		}
	};

	firing_state* get_firing_state() {
		return memory::read<firing_state*>(uintptr_t(this) + offsets::FiringStateComp);
	}
	

	static inline currentequippable::type types[] = {
			{ L"basepistol", "classic" },
			{ L"sawedoffshotgun", "shorty" },
			{ L"automaticpistol", "frenzy" },
			{ L"lugerpistol", "ghost" },
			{ L"revolverpistol", "sheriff" },

			{ L"vector", "stinger" },
			{ L"submachinegun_mp5", "spectre" },

			{ L"pumpshotgun", "bucky" },
			{ L"automaticshotgun", "judge" },

			{ L"assaultrifle_burst", "bulldog" },
			{ L"dmr", "guardian" },
			{ L"assaultrifle_acr", "phantom" },
			{ L"assaultrifle_ak", "vandal" },

			{ L"leversniperrifle", "marshal" },
			{ L"boltsniper", "operator" },

			{ L"lightmachinegun", "ares" },
			{ L"heavymachinegun", "odin" },

			{ L"ability_melee_base", "knife" },

			{ L"gun_sprinter_x_heavylightninggun_production", "neon_x" },
			{ L"ability_wushu_x_dagger_production", "jett_dagger" }
	};

	currentequippable::type get_type() {
		const fstring& name = system::get_object_name(this);

		for (std::int32_t index = 0; index < sizeof(currentequippable::types) / sizeof(currentequippable::type); index++) {
			currentequippable::type type = currentequippable::types[index];

			if (type.index == 0)
				type.index = index;

			if (system::starts_with(name.c_str(), type.search))
				return { type.search, type.config, type.index };
		}

		return {};
	}

	EAresItemSlot get_item_slot();

	equippable_skin_data_asset* get_skin_data_asset();

	EAresItemSlot GetItemSlot();

	uskeletalmeshcomponent* Mesh();

	uskeletalmeshcomponent* GetMesh1P();
	uskeletalmeshcomponent* GetEquippableMesh();
	uskeletalmeshcomponent* GetMesh3P();

	void EjectShellCasing() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Gun_C.EjectShellCasing");
		if (!function) return;
		struct {} Parameters;
		this->process_event(function, &Parameters);
	}
};
class uinventory : public uobject
{
public:
	currentequippable* get_current_equippable();
};



struct UMaterialInstanceDynamic : UMaterialInstance {
public:
	e_blend_mode get_blend_mode();
	void set_vector_parameter_value2(fname parameter_name, flinearcolor value);
	void set_vector_parameter_value1(fname parameter_name, flinearcolor value);
	void set_scalar_parameter_value2(fname parameter_name, float value);
	void set_scalar_parameter_value(fname parameter_name, double value);
	//void set_scalar_parameter_value1(fname parameter_name, float value);
	void set_scalar_parameter_value1(fname parameter_name, double value);
	void set_texture_parameter_value(fname parameter_name, uobject* texture);
	void set_vector_parameter_value(fname parameter_name, flinearcolor value);
};


//struct UPrimitiveComponent : uobject {
//public:
//
//
//	void set_material(int32_t element_index, uobject* material);
//
//	void CreateAndSetMaterialInstanceDynamicFromMaterial(int32_t element_index, uobject* material);
//
//	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
//		if (!this || !parent) return nullptr;
//
//		static uobject* fn = nullptr;
//		if (!fn)
//			fn = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");
//
//		struct {
//			int32_t element_index;
//			uobject* parent;
//			uobject* return_value;
//		} params = { element_index, parent };
//
//		process_event(fn, &params);
//		return params.return_value;
//	}
//
//	UMaterialInstanceDynamic* get_material(int32_t element_index);
//
//	int32_t get_num_materials();
//
//};


class arsenal_view_model : public uobject
{
public:
	tarray<equippable_inventory_model*> get_gun_models();
};

class arsenal_view_controller : public uobject
{
public:
	arsenal_view_model* get_view_model();
};

class inventorymanager : public uobject
{
public:
	currentequippable* get_current_weapon();
};

class ares_client_game_instace : public uobject
{
public:
	arsenal_view_controller* get_aresnal_view_controller();
	inventorymanager* get_inventory_manager();
};

class ares_instance : public uobject
{
public:
	static ares_client_game_instace* get_ares_client_game_instance(uobject* world_context);
};


class aplayercameramanager : public uobject
{
public:
	fvector get_camera_location();
	fvector get_camera_rotation();
	float get_fov();
};

class aplayerstate : public uobject
{
public:
};

struct AActor : public uobject {
	char bLocallyHidden : 1; // 0x60(0x01)
	char pad_60_1 : 7; // 0x60(0x01)
	char pad_61[0x7]; // 0x61(0x07)
	char pad_78[0xa4]; // 0x78(0xa4)
	char bNetTemporary : 1; // 0x11c(0x01)
	char bNetStartup : 1; // 0x11c(0x01)
	char bOnlyRelevantToOwner : 1; // 0x11c(0x01)
	char bAlwaysRelevant : 1; // 0x11c(0x01)
	char bReplicateMovement : 1; // 0x11c(0x01)
	char bHidden : 1; // 0x11c(0x01)
	char bTearOff : 1; // 0x11c(0x01)
	char bForceNetAddressable : 1; // 0x11c(0x01)
	char bExchangedRoles : 1; // 0x11d(0x01)
	char bNetLoadOnClient : 1; // 0x11d(0x01)
	char bNetUseOwnerRelevancy : 1; // 0x11d(0x01)
	char bRelevantForNetworkReplays : 1; // 0x11d(0x01)
	char bRelevantForLevelBounds : 1; // 0x11d(0x01)
	char bReplayRewindable : 1; // 0x11d(0x01)
	char bAllowTickBeforeBeginPlay : 1; // 0x11d(0x01)
	char bAutoDestroyWhenFinished : 1; // 0x11d(0x01)
	char bCanBeDamaged : 1; // 0x11e(0x01)
	char bBlockInput : 1; // 0x11e(0x01)
	char bCollideWhenPlacing : 1; // 0x11e(0x01)
	char bFindCameraComponentWhenViewTarget : 1; // 0x11e(0x01)
	char bGenerateOverlapEventsDuringLevelStreaming : 1; // 0x11e(0x01)
	char bIgnoresOriginShifting : 1; // 0x11e(0x01)
	char bEnableAutoLODGeneration : 1; // 0x11e(0x01)
	char bIsEditorOnlyActor : 1; // 0x11e(0x01)
	char bChildActorsManuallySpawn : 1; // 0x11f(0x01)
	char bActorSeamlessTraveled : 1; // 0x11f(0x01)
	char bReplicates : 1; // 0x11f(0x01)
	char bCanBeInCluster : 1; // 0x11f(0x01)
	char bAllowReceiveTickEventOnDedicatedServer : 1; // 0x11f(0x01)
	char pad_11F_5 : 3; // 0x11f(0x01)
	char pad_120_0 : 5; // 0x120(0x01)
	char bActorEnableCollision : 1; // 0x120(0x01)
	char bActorIsBeingDestroyed : 1; // 0x120(0x01)
	char pad_120_7 : 1; // 0x120(0x01)
	char pad_121[0x1]; // 0x121(0x01)
	int32_t InputPriority; // 0x1d8(0x04)
	char pad_1DC[0x4]; // 0x1dc(0x04)
	struct UInputComponent* InputComponent; // 0x1e0(0x08)
	float NetCullDistanceSquared; // 0x1e8(0x04)
	int32_t NetTag; // 0x1ec(0x04)
	float NetUpdateFrequency; // 0x1f0(0x04)
	float MinNetUpdateFrequency; // 0x1f4(0x04)
	float NetPriority; // 0x1f8(0x04)
	char pad_1FC[0x24]; // 0x1fc(0x24)
	struct APawn* Instigator; // 0x220(0x08)
	char pad_296[0x2]; // 0x296(0x02)
	char pad_2AA[0x6]; // 0x2aa(0x06)
	char pad_2D0[0xb8]; // 0x2d0(0xb8)
	char pad_3A8[0x10]; // 0x3a8(0x10)

	float CustomTimeDilation;

	AActor* GetOwner() {  // <- mark const
		static uobject* Function = uobject::find_object<uobject*>(L"Engine.Actor.GetOwner");
		if (!Function) return nullptr;  // <- must return a value

		struct Params {
			AActor* ReturnValue;
		} args;

		this->process_event( Function, &args);
		return args.ReturnValue;
	}

	fvector K2_GetActorLocation() {
		auto function_name = crypt(L"Engine.Actor.K2_GetActorLocation").decrypt();
		static uobject* Function = nullptr;

		if (!Function)
			Function = uobject::find_object<uobject*>(function_name);

		if (!Function)
			return { 0, 0, 0 };

		struct {
			fvector Out;
		} Parameters;

		this->process_event(Function, &Parameters);
		return Parameters.Out;
	}

	void GetAllChildActors(tarray<AActor*>& OutChildren, bool bIncludeDescendants) {
		static uobject* Function = uobject::find_object<uobject*>(L"Engine.Actor.GetAllChildActors");
		if (!Function) return;

		struct Params {
			tarray<AActor*> OutChildren;
			bool bIncludeDescendants;
		} args;

		args.bIncludeDescendants = bIncludeDescendants;
		this->process_event( Function, &args);

		OutChildren = args.OutChildren;
	}

};





struct UPrimitiveComponent : uobject {
public:
	void set_material(int32_t element_index, uobject* material);

	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
		if (!this || !parent) return nullptr;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");

		struct params_t {
			int32_t element_index;
			uobject* parent;
			uobject* return_value;
		} params = { element_index, parent };

		process_event(fn, &params);
		return params.return_value;
	}

	UMaterialInstanceDynamic* get_material(int32_t element_index);
	int32_t get_num_materials();

};

class acknowledgedpawn : public uobject
{
public:

	bool canjump();

	fvector get_controlrotation();

	uskeletalmeshcomponent* GetMesh11P();

	uskeletalmeshcomponent* GetOverlayMesh11P();

	/*UPrimitiveComponent* GetOverlayMesh1P2();
	UPrimitiveComponent* GetMesh1P2();*/
};


class UDamageResponse : public uobject
{
public:
	uint8_t                                         Pad_30[0x8];                                       // 0x0030(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	acknowledgedpawn* DamagedActor; // 0x38(0x08)
public:

	acknowledgedpawn* get_damage_causer();
	currentequippable* get_equippable_used();
};


class gameobject : public uobject
{
public:
};




// ---------- storage ----------
struct SkinItem {
	std::wstring name;   // full asset name
};

#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cstdio>

inline static std::unordered_map<std::string, std::vector<SkinItem>> g_byFamily;
inline static std::unordered_map<std::string, int> g_selectedIndexForFamily;





class ashootercharacter : public uobject
{
public:
	uskeletalmeshcomponent* get_mesh();
	uskeletalmeshcomponent* GetOverlayMesh1P();
	uskeletalmeshcomponent* mesh3p();
	uskeletalmeshcomponent* getmesh1p();

	void Set3pMeshVisible(bool val);
	void SetCrouchTimeOverride(float Override);

	USceneComponent* K2_GetRootComponent();

	void GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation);

	fvector GetActorForwardVector();

	fvector GetActorRightVector();

	fvector GetActorUpVector();

	uinventory* get_inventory();
	fvector k2_get_actor_location();
	void custom_set_actor_location(fvector NewLocation, bool bSweep, bool bTeleport);
	uobject* get_character_icon();
	bool is_alive();
	bool was_invisible();
	float health();
	float shield();
	bool is_dead_and_settled(); 

	uskeletalmeshcomponent* GetCosmeticMesh3P();
	bool IsZoomed();
	void K2_SetActorRelativeRotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport);
	void reset_character_materials_internal(uskeletalmeshcomponent* mesh_to_reset);
	bool CanJump();
	//bool CanJumpInternal();
	void Jump();
	void OnJump();
	void StopJumping();

	void get_firing_location_and_direction(fvector* loc, fvector* rot, bool apply_recoil);

	fvector get_velocity();
};

class aplayercontroller : public uobject
{
public:
	
	bool dormant_server(ashootercharacter* actor);
	bool is_input_key_down(aplayercontroller* controller, const fkey key);
	ashootercharacter* get_shooter_character();
	bool line_of_sight(ashootercharacter* other);
	fvector2d project_world_to_screen(fvector world);
	fvector get_control_rotation();
	void simulate_input_key(fkey key, bool bpressed);
	bool project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative);
	void set_control_rotation(fvector angle);
	aplayercameramanager* get_camera_manager();
	void set_fov(float fov); // Corrected declaration
	acknowledgedpawn* get_acknowledged_pawn();
	void disconnect_server();
	void GetInputMouseDelta(float& DeltaX, float& DeltaY);
	float GetMouseSensitivity();
	void SimulateInputKey(fkey Key, bool bPressed);
};

class ugameviewportclient : public uobject {
public:
	struct uworld* get_world();
	struct ugameinstance* get_gameinstance();
};

class ulocalplayer : public uobject {
public:
	ugameviewportclient* viewport_client();
};

class uengine : public uobject
{
public:
	uobject* font();
};

class ugameinstance : public uobject {
public:
	uengine* get_uengine();
	tarray<ulocalplayer*> local_players();
};

class uworld : public uobject
{
public:
	ugameinstance* game_instance();
};

namespace skin_changer {
	void unlock_all_skins(uobject* world);

	void unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset);
	
}

class ucanvas : public uobject {
public:
	fvector2d get_screen_size();

	void k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color);
	void k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point);
	void k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor);

};

class text : public uobject
{
public:
	static fstring text_to_string(ftext string);
	static ftext string_to_text(const fstring& InString);
};

class blueprints : public uobject
{
public:
	static aplayercontroller* get_player_controller(uobject* context);
	static aplayercontroller* get_local_controller(uobject* context);
	static tarray<ashootercharacter*> find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive);
	static tarray<ashootercharacter*> find_all_game_objects(uworld* world_context);
};

class math : public uobject
{
public:
	static int32_t random_int(int32_t min, int32_t max);
	static fvector SmoothAim(fvector target, fvector delta_rotation, float smooth);
	/*static float distance_2d(fvector2d v1, fvector2d v2);*/

	static double distance_2d(fvector2d v1, fvector2d v2);
	static fvector find_look_at_rotation(fvector start, fvector end);


};

class game_statics : public uobject
{
public:

	static void get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output);
};

class content_library
{
public:
	static void apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level);
	static void clear_weapon_components(currentequippable* equippable);
};

class ares_outline : public uobject
{
public:
	static void setoutlinemode(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor);
	static void setoutlinemode1(uworld* WorldContextObject, flinearcolor EnemyColor);
};

class umaterial_instance : public uobject
{
public:
	void set_vector_parameter_value(fname ParameterName, flinearcolor Value);
};


namespace basecomponent {
	bool is_ally(ashootercharacter* enemy, ashootercharacter* self);
}

class variables_construct
{
public:
	uobject* blueprints;
	uobject* gameplay_statics;
	uobject* kismet_system;
	uobject* kismet_string;
	uobject* kismet_text;
	uobject* math_system;
	uobject* bobber;
	uobject* rendering_library;
	uobject* content_library;
	uobject* ares_outline_rendering;
	uobject* ares_equippable;
	uobject* ares_instance;
	uobject* base_component;


	fkey f1;
	fkey spacebar;
	fkey leftmousebutton;
	fkey n_key;

	void init_variables() {

		base_component = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__BaseTeamComponent"));
		blueprints = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ShooterBlueprintLibrary"));		
		gameplay_statics = uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics"));
		kismet_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetSystemLibrary"));
		kismet_string = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetStringLibrary"));
		rendering_library = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetRenderingLibrary"));
		kismet_text = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetTextLibrary"));
		math_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetMathLibrary"));
		bobber = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetAresOutlineMode"));
		content_library = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ContentLibrary"));
		ares_outline_rendering = uobject::find_object<uobject*>(crypt(L"Renderer.Default__AresOutlineRendering"));
		ares_equippable = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresEquippable"));
		ares_instance = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresClientGameInstance"));
	}
};

inline variables_construct variables;

class drawings {
public:

	static void draw_rect(fvector2d initial_pos, double w, double h, flinearcolor color, ucanvas* canvas)
	{
		canvas->k2_drawline(initial_pos, { initial_pos.x + w, initial_pos.y }, 1.2, color);
		canvas->k2_drawline(initial_pos, { initial_pos.x, initial_pos.y + h }, 1.2, color);
		canvas->k2_drawline({ initial_pos.x + w, initial_pos.y }, { initial_pos.x + w, initial_pos.y + h }, 1.2, color);
		canvas->k2_drawline({ initial_pos.x, initial_pos.y + h }, { initial_pos.x + w, initial_pos.y + h }, 1.2, color);
	}

	static void draw_corner(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, fvector2d base_out, fvector2d head_long_out, flinearcolor color, ucanvas* canvas) {

		if (!my_controller || !mesh || !canvas) {
			return;
		}

		if (!head_long_out.is_valid() || !base_out.is_valid()) {
			return;
		}

		double box_height = abs(head_long_out.y - base_out.y);
		if (box_height == 0) {
			return;
		}

		double box_width = box_height * 0.55;

		double X = head_long_out.x - (box_width / 2), Y = head_long_out.y;
		double lineW = (box_width / 3);
		double lineH = (box_height / 3);

		if (lineW <= 0 || lineH <= 0) {
			return;
		}
		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X, Y + lineH), 1.0, color);
		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X + lineW, Y), 1.0, color);
		canvas->k2_drawline(fvector2d(X + box_width - lineW, Y), fvector2d(X + box_width, Y), 1.0, color);
		canvas->k2_drawline(fvector2d(X + box_width, Y), fvector2d(X + box_width, Y + lineH), 1.0, color);
		canvas->k2_drawline(fvector2d(X, Y + box_height - lineH), fvector2d(X, Y + box_height), 1.0, color);
		canvas->k2_drawline(fvector2d(X, Y + box_height), fvector2d(X + lineW, Y + box_height), 1.0, color);
		canvas->k2_drawline(fvector2d(X + box_width - lineW, Y + box_height), fvector2d(X + box_width, Y + box_height), 1.0, color);
		canvas->k2_drawline(fvector2d(X + box_width, Y + box_height - lineH), fvector2d(X + box_width, Y + box_height), 1.0, color);
	}

	static void draw_3d(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, fvector vHeadBone, fvector vBaseBone, flinearcolor color, ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;

		if (!vHeadBone.is_valid() || !vBaseBone.is_valid()) return;

		fvector2d bottom1, bottom2, bottom3, bottom4;
		fvector2d top1, top2, top3, top4;

		bool valid_projection =
			my_controller->project_world_location_to_screen(fvector(vBaseBone.x + 53.0, vBaseBone.y - 55.0, vBaseBone.z), bottom1, 0) && bottom1.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vBaseBone.x - 53.0, vBaseBone.y - 55.0, vBaseBone.z), bottom2, 0) && bottom2.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vBaseBone.x - 53.0, vBaseBone.y + 55.0, vBaseBone.z), bottom3, 0) && bottom3.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vBaseBone.x + 53.0, vBaseBone.y + 55.0, vBaseBone.z), bottom4, 0) && bottom4.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vHeadBone.x + 53.0, vHeadBone.y - 55.0, vHeadBone.z + 26.0), top1, 0) && top1.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vHeadBone.x - 53.0, vHeadBone.y - 55.0, vHeadBone.z + 26.0), top2, 0) && top2.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vHeadBone.x - 53.0, vHeadBone.y + 55.0, vHeadBone.z + 26.0), top3, 0) && top3.is_valid() &&
			my_controller->project_world_location_to_screen(fvector(vHeadBone.x + 53.0, vHeadBone.y + 55.0, vHeadBone.z + 26.0), top4, 0) && top4.is_valid();

		if (valid_projection) {
			canvas->k2_drawline({ bottom1.x, bottom1.y }, { top1.x, top1.y }, 1.35, color);
			canvas->k2_drawline({ bottom2.x, bottom2.y }, { top2.x, top2.y }, 1.35, color);
			canvas->k2_drawline({ bottom3.x, bottom3.y }, { top3.x, top3.y }, 1.35, color);
			canvas->k2_drawline({ bottom4.x, bottom4.y }, { top4.x, top4.y }, 1.35, color);

			canvas->k2_drawline({ bottom1.x, bottom1.y }, { bottom2.x, bottom2.y }, 1.35, color);
			canvas->k2_drawline({ bottom2.x, bottom2.y }, { bottom3.x, bottom3.y }, 1.35, color);
			canvas->k2_drawline({ bottom3.x, bottom3.y }, { bottom4.x, bottom4.y }, 1.35, color);
			canvas->k2_drawline({ bottom4.x, bottom4.y }, { bottom1.x, bottom1.y }, 1.35, color);

			canvas->k2_drawline({ top1.x, top1.y }, { top2.x, top2.y }, 1.35, color);
			canvas->k2_drawline({ top2.x, top2.y }, { top3.x, top3.y }, 1.35, color);
			canvas->k2_drawline({ top3.x, top3.y }, { top4.x, top4.y }, 1.35, color);
			canvas->k2_drawline({ top4.x, top4.y }, { top1.x, top1.y }, 1.35, color);
		}
	}

	

	static void draw_skeleton(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, int bone_count, flinearcolor color, ucanvas* canvas) {
		struct BoneIDs {
			int hip, neck, upperArmLeft, leftHand, leftHand1, upperArmRight, rightHand, rightHand1;
			int leftThigh, leftCalf, leftFoot, rightThigh, rightCalf, rightFoot;
		};

		BoneIDs boneIDs;

		switch (bone_count) {
		case 101:
			boneIDs = { 3, 21, 23, 24, 25, 49, 50, 51, 75, 76, 78, 82, 83, 85 };
			break;
		case 103:
			boneIDs = { 3, 9, 33, 30, 32, 58, 55, 57, 63, 65, 69, 77, 79, 83 };
			break;
		case 104:
			boneIDs = { 3, 21, 23, 24, 25, 49, 50, 51, 77, 78, 80, 84, 85, 87 };
			break;
		default:
			return;
		}

		auto ProjectAndCheck = [&](int boneIndex, fvector2d& out) -> bool {
			fvector worldLocation = mesh->get_bone_location(boneIndex);
			if (!worldLocation.is_valid()) {
				return false;
			}
			return my_controller->project_world_location_to_screen(worldLocation, out, false) && out.is_valid();
			};

		fvector2d vHipOut, vNeckOut, vUpperArmLeftOut, vLeftHandOut, vLeftHandOut1, vUpperArmRightOut, vRightHandOut, vRightHandOut1;
		fvector2d vLeftThighOut, vLeftCalfOut, vLeftFootOut, vRightThighOut, vRightCalfOut, vRightFootOut;

		bool bValidProjection =
			ProjectAndCheck(boneIDs.hip, vHipOut) && ProjectAndCheck(boneIDs.neck, vNeckOut) &&
			ProjectAndCheck(boneIDs.upperArmLeft, vUpperArmLeftOut) && ProjectAndCheck(boneIDs.leftHand, vLeftHandOut) &&
			ProjectAndCheck(boneIDs.leftHand1, vLeftHandOut1) &&
			ProjectAndCheck(boneIDs.upperArmRight, vUpperArmRightOut) && ProjectAndCheck(boneIDs.rightHand, vRightHandOut) &&
			ProjectAndCheck(boneIDs.rightHand1, vRightHandOut1) &&
			ProjectAndCheck(boneIDs.leftThigh, vLeftThighOut) && ProjectAndCheck(boneIDs.leftCalf, vLeftCalfOut) &&
			ProjectAndCheck(boneIDs.leftFoot, vLeftFootOut) &&
			ProjectAndCheck(boneIDs.rightThigh, vRightThighOut) && ProjectAndCheck(boneIDs.rightCalf, vRightCalfOut) &&
			ProjectAndCheck(boneIDs.rightFoot, vRightFootOut);

		if (bValidProjection) {
			canvas->k2_drawline(vHipOut, vNeckOut, 1.0, color);
			canvas->k2_drawline(vUpperArmLeftOut, vNeckOut, 1.0, color);
			canvas->k2_drawline(vUpperArmRightOut, vNeckOut, 1.0, color);
			canvas->k2_drawline(vLeftHandOut, vUpperArmLeftOut, 1.0, color);
			canvas->k2_drawline(vRightHandOut, vUpperArmRightOut, 1.0, color);
			canvas->k2_drawline(vLeftHandOut, vLeftHandOut1, 1.0, color);
			canvas->k2_drawline(vRightHandOut, vRightHandOut1, 1.0, color);
			canvas->k2_drawline(vLeftThighOut, vHipOut, 1.0, color);
			canvas->k2_drawline(vRightThighOut, vHipOut, 1.0, color);
			canvas->k2_drawline(vLeftCalfOut, vLeftThighOut, 1.0, color);
			canvas->k2_drawline(vRightCalfOut, vRightThighOut, 1.0, color);
			canvas->k2_drawline(vLeftFootOut, vLeftCalfOut, 1.0, color);
			canvas->k2_drawline(vRightFootOut, vRightCalfOut, 1.0, color);
		}
	}

	static void draw_health_and_shield(double health, double shield, fvector2d base_out, double boxWidth, double boxHeight, double distance, flinearcolor color, ucanvas* canvas)
	{
		// Mesafeden bağımsız — tüm offset'ler boxWidth'e orantılı
		double barW     = boxWidth;
		double X        = base_out.x - barW / 2.0;
		double Y        = base_out.y + 4.0;          // ayak altında küçük boşluk
		double barH     = 3.5;
		double gap      = 2.0;

		static flinearcolor bg   { 0.12f, 0.12f, 0.12f, 0.85f };
		static flinearcolor shCol{ 0.05f, 0.45f, 0.80f, 1.0f  };

		// --- HP barı ---
		// Arka plan
		canvas->k2_drawline(fvector2d(X, Y + barH * 0.5),
							fvector2d(X + barW, Y + barH * 0.5), barH + 1.0, bg);
		// Dolu kısım
		double hpW = barW * fmath::Max(0.0, fmath::Min(health / 100.0, 1.0));
		if (hpW > 0)
			canvas->k2_drawline(fvector2d(X, Y + barH * 0.5),
								fvector2d(X + hpW, Y + barH * 0.5), barH, color);

		// --- Shield barı (varsa) ---
		if (shield > 0) {
			double sY = Y + barH + gap;
			canvas->k2_drawline(fvector2d(X, sY + barH * 0.5),
								fvector2d(X + barW, sY + barH * 0.5), barH + 1.0, bg);
			double shW = barW * fmath::Max(0.0, fmath::Min(shield / 100.0, 1.0));
			if (shW > 0)
				canvas->k2_drawline(fvector2d(X, sY + barH * 0.5),
									fvector2d(X + shW, sY + barH * 0.5), barH, shCol);
		}
	}

	static void draw_snapline(int snappos, ashootercharacter* shooter_character, fvector2d head_out, flinearcolor color, ucanvas* canvas) {

		double radius;

		if (globals::aimbot::draw_f0v) {
			radius = 10.0 + globals::aimbot::a1m_f0v;
		}
		else
		{
			radius = 53.0;
		}

		double screen_center_x = canvas->get_screen_size().x / 2.0;
		double screen_center_y = canvas->get_screen_size().y / 2.0;

		double a = head_out.y - screen_center_y;
		double b = head_out.x - screen_center_x;

		if (b == 0)
			b = 0.0001;

		double angle = atan(a / b);
		double x3, y3;

		if (b > 0) {
			x3 = radius * cos(angle) + screen_center_x;
			y3 = radius * sin(angle) + screen_center_y;
		}
		else {
			x3 = radius * (-cos(angle)) + screen_center_x;
			y3 = radius * (-sin(angle)) + screen_center_y;
		}

		if (sqrt(a * a + b * b) >= radius) {
			canvas->k2_drawline(fvector2d(head_out.x, head_out.y), fvector2d(x3, y3), 1.0, color);
		}
	}


	static void partyhat(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;

		int bone_count = mesh->get_num_bones();
		fvector head_pos;
		bool valid = false;

		if (bone_count == 101) {
			head_pos = mesh->get_bone_location(8);  // Head bone
			valid = true;
		}
		else if (bone_count == 103) {
			head_pos = mesh->get_bone_location(8);  // Head bone
			valid = true;
		}
		else if (bone_count == 104) {
			head_pos = mesh->get_bone_location(8);  // Head bone
			valid = true;
		}

		if (!valid || !head_pos.is_valid()) return;

		float base_radius = 35.0f;      // Plus large/long pour s'étendre plus
		float cone_height = 15.0f;      // Plus bas/plat, pas trop haut
		static float spin_time = 0.0f;
		spin_time += 0.02f;             // Spin animation

		// Position hat on head - plus plat et étendu
		fvector cone_top = head_pos + fvector(0, 0, cone_height + 3);     // Pas trop haut
		fvector base_center = head_pos + fvector(0, 0, 3);                // Juste au-dessus de la tête

		fvector2d screen_top;
		if (!my_controller->project_world_location_to_screen(cone_top, screen_top, 0) || !screen_top.is_valid()) return;

		static flinearcolor colors[8] = {
			flinearcolor(1.0f, 0.0f, 0.0f, 1.0f),  // Red
			flinearcolor(1.0f, 0.5f, 0.0f, 1.0f),  // Orange
			flinearcolor(1.0f, 1.0f, 0.0f, 1.0f),  // Yellow
			flinearcolor(0.5f, 1.0f, 0.0f, 1.0f),  // Light Green
			flinearcolor(0.0f, 1.0f, 0.0f, 1.0f),  // Green
			flinearcolor(0.0f, 1.0f, 1.0f, 1.0f),  // Cyan
			flinearcolor(0.0f, 0.0f, 1.0f, 1.0f),  // Blue
			flinearcolor(0.5f, 0.0f, 1.0f, 1.0f)   // Purple
		};

		static const float segment_angle = 2.0f * 3.14159f / 8.0f;

		for (int i = 0; i < 8; i++) {
			float angle1 = segment_angle * i + spin_time;
			float angle2 = angle1 + segment_angle;

			fvector base1 = base_center + fvector(base_radius * cos(angle1), base_radius * sin(angle1), 0);
			fvector base2 = base_center + fvector(base_radius * cos(angle2), base_radius * sin(angle2), 0);

			fvector2d screen1, screen2;
			bool valid1 = my_controller->project_world_location_to_screen(base1, screen1, 0) && screen1.is_valid();
			bool valid2 = my_controller->project_world_location_to_screen(base2, screen2, 0) && screen2.is_valid();

			if (valid1 && valid2) {
				// Main cone lines
				canvas->k2_drawline(screen_top, screen1, 5.0f, colors[i]);
				canvas->k2_drawline(screen_top, screen2, 5.0f, colors[i]);

				// Plus de lignes de remplissage pour un chapeau plus dense et étendu
				for (int j = 1; j < 6; j++) {
					float fill_angle = angle1 + (segment_angle * j / 6.0f);
					fvector fill_base = base_center + fvector(base_radius * cos(fill_angle), base_radius * sin(fill_angle), 0);
					fvector2d screen_fill;
					if (my_controller->project_world_location_to_screen(fill_base, screen_fill, 0) && screen_fill.is_valid()) {
						canvas->k2_drawline(screen_top, screen_fill, 3.0f, colors[i]);
					}
				}

				// Base edge line - plus épais pour montrer l'extension
				canvas->k2_drawline(screen1, screen2, 4.0f, colors[i]);
			}
		}
	}




	
	static void agent_icon(ashootercharacter* actor, fvector2d base_out, double icon_size, ucanvas* canvas) {

		uobject* icon = actor->get_character_icon();
		if (!icon || !canvas || icon_size <= 0.0)
			return;

		// Boyut cagiran taraftan geliyor (box_height oranli)
		double size = fmath::Max(8.0, fmath::Min(icon_size, 40.0));

		canvas->k2_drawtexture(icon, base_out,
			fvector2d(size, size),
			fvector2d(0.0, 0.0),
			fvector2d(1.0, 1.0),
			flinearcolor(1, 1, 1, 1), e_blend_mode::opaque, 0.0, fvector2d(0.5, 0.5));
	}

	static void gun_icon(ashootercharacter* actor, fvector2d head_out, double distance, ucanvas* canvas) {

		uobject* equippable_icon = memory::read<uobject*>(uintptr_t(actor->get_inventory()->get_current_equippable()) + offsets::inventory_icon);

		if (!equippable_icon || !canvas || distance <= 0.0)
			return;

		fvector2d base_size = fvector2d(12.5, 8.5);
		double scale_factor = 100.0 / distance;
		fvector2d size = base_size * scale_factor;

		if (size.x <= 0.0 || size.y <= 0.0)
			return;

		canvas->k2_drawtexture(equippable_icon, head_out, size,
			fvector2d(0.0, 0.0),
			fvector2d{ 1.0, 1.0 },
			flinearcolor(1, 1, 1, 1), e_blend_mode::masked, 0.0, fvector2d(0.5, 0.5));
	}

	static void head_box(fvector2d position, double width, double height, flinearcolor color, ucanvas* canvas)
	{
		double X = position.x - (width / 2.0);
		double Y = position.y;
		double lineW = (width / 3.0);
		double lineH = (height / 3.0);

		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X, Y + lineH), 1.5, color);
		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X + lineW, Y), 1.5, color);
		canvas->k2_drawline(fvector2d(X + width - lineW, Y), fvector2d(X + width, Y), 1.5, color);
		canvas->k2_drawline(fvector2d(X + width, Y), fvector2d(X + width, Y + lineH), 1.5, color);
		canvas->k2_drawline(fvector2d(X, Y + height - lineH), fvector2d(X, Y + height), 1.5, color);
		canvas->k2_drawline(fvector2d(X, Y + height), fvector2d(X + lineW, Y + height), 1.5, color);
		canvas->k2_drawline(fvector2d(X + width - lineW, Y + height), fvector2d(X + width, Y + height), 1.5, color);
		canvas->k2_drawline(fvector2d(X + width, Y + height - lineH), fvector2d(X + width, Y + height), 1.5, color);
	}

	static void draw_f0v(fvector2d pos, double radius, int numSegments, flinearcolor color, ucanvas* canvas)
	{

		if (globals::aimbot::draw_f0v) {
			const double PI = 3.14159265358979323846;

			double Step = PI * 2.0 / numSegments;
			fvector2d V[128];

			for (int i = 0; i < numSegments; i++) {
				double Angle = i * Step;
				double X = radius * cos(Angle) + pos.x;
				double Y = radius * sin(Angle) + pos.y;

				V[i].x = X;
				V[i].y = Y;
			}

			for (int i = 0; i < numSegments - 1; i++) {
				canvas->k2_drawline(fvector2d{ V[i].x, V[i].y }, fvector2d{ V[i + 1].x, V[i + 1].y }, 1.0, color);
			}

			canvas->k2_drawline(fvector2d{ V[numSegments - 1].x, V[numSegments - 1].y }, fvector2d{ V[0].x, V[0].y }, 1.0, color);
		}

	}




};



struct AGameObject : public uobject {
	char pad_0[0x4a0];
	fvector GetObjectLocation();
	float GetObjectHealth();


	void SetActorHiddenInGame(bool bNewHidden)
	{
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorHiddenInGame").decrypt());
		if (!Function) return;
		struct { bool bNewHidden; } Parameters;
		Parameters.bNewHidden = bNewHidden;
		reinterpret_cast<uobject*>(this)->process_event(Function, &Parameters);
	}

	void SetActorEnableCollision(bool bNewActorEnableCollision)
	{
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorEnableCollision").decrypt());
		if (!Function) return;
		struct { bool bNewActorEnableCollision; } Parameters;
		Parameters.bNewActorEnableCollision = bNewActorEnableCollision;
		reinterpret_cast<uobject*>(this)->process_event(Function, &Parameters);
	}
};


namespace Class {
	uobject* ShooterGameObject();

	static inline uobject* Actors()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Actor");

		return function;
	}

}


static inline fstring GetValVersion() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetFullBuildVersionString"));

	fstring return_value;
	variables.blueprints->process_event(function, &return_value);
	return return_value;
}


enum class EChatRoomType : uint8_t
{
	Party       = 0,
	Pregame     = 1,
	All         = 2,
	Team        = 3,
	InGameSystem = 4,
	System      = 5,
	Whisper     = 6,
	Count       = 7,
	EChatRoomType_MAX = 8,
};

struct UTextChatRoomV2 : public uobject {
	char pad_30[0x8]; // 0x30(0x08)
	char pad_58[0x10]; // 0x58(0x10)
	fstring RoomID; // 0x68(0x10)
	bool bIsRestricted; // 0x78(0x01)
	char pad_79[0x7]; // 0x79(0x07)
	struct UTextChatService* ChatService; // 0x80(0x08)
	struct URSOManager* RSOManager; // 0x88(0x08)
	char pad_90[0x8]; // 0x90(0x08)
	char pad_160[0x40]; // 0x160(0x40)
};

struct UThreadedChatManager : public uobject {
	struct UTextChatService* ChatService; // 0xe0(0x08)
	struct tarray<struct FUnifiedChatMessage> Messages; // 0xe8(0x10)
	UTextChatRoomV2* PartyRoom; // 0x148(0x08)
	UTextChatRoomV2* PregameRoom; // 0x150(0x08)
	UTextChatRoomV2* AllRoom; // 0x158(0x08)
	UTextChatRoomV2* TeamRoom; // 0x160(0x08)
	struct UPartyManager* PartyManager; // 0x168(0x08)
	struct UCoreGameManager* CoreGameManager; // 0x170(0x08)
	struct UPregameManager* PregameManager; // 0x178(0x08)
	struct UWhisperChatManager* WhisperChatManager; // 0x180(0x08)
	struct UMutedPatternsManager* MutedPatternsManager; // 0x188(0x08)
	struct UTextChatManagerV2* TextChatManager; // 0x190(0x08)
	struct UEmojiMapping* EmojiMapping; // 0x198(0x08)
	struct URSOManager* RSOManager; // 0x1a0(0x08)
	char pad_1A8[0x8];
public:
	static UThreadedChatManager* GetThreadedChatManager(uobject* world_context);
	void SendChatMessageV2(EChatRoomType room_type, ftext message);

	static uobject* GetDefaultObj() {
		static uobject* default_obj = nullptr;
		if (!default_obj)
			default_obj = uobject::find_object<uobject*>(L"ShooterGame.Default__ThreadedChatManager");
		if (!default_obj) return nullptr;
		return default_obj;
	}
	// 0x1a8(0x08)
};

class UBlindManagerComponent final : public UActorComponent
{
public:
	uint8_t                                         Pad_D8[0x8];                                       // 0x00D8(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	//FMulticastInlineDelegateProperty_             OnBlindedChanged;                                  // 0x00E0(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	//FMulticastInlineDelegateProperty_             OnFailedBlindApplicationTagRequirements;           // 0x00F0(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	//struct FBlindManagerState                     AuthBlindManagerState;                             // 0x0100(0x0018)(Net, RepNotify, NativeAccessSpecifierPrivate)
	//struct FBlindManagerState                     LocalBlindManagerState;                            // 0x0118(0x0018)(NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_130[0x30];                                     // 0x0130(0x0030)(Fixing Size After Last Property [ Dumper-7 ])
	tarray<struct FBlindSpawnParams>              ScheduledBlinds;                                   // 0x0160(0x0010)(ZeroConstructor, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_170[0x58];                                     // 0x0170(0x0058)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	bool IsBlinded();
	void SetBlinded(bool bNewBlinded);
	void ClientCleanseBlinds();
};

#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;









enum class EPhysicalSurface : uint8 {
	SurfaceType_Default = 0,
	SurfaceType1 = 1,
	SurfaceType2 = 2,
	SurfaceType3 = 3,
	SurfaceType4 = 4,
	SurfaceType5 = 5,
	SurfaceType6 = 6,
	SurfaceType7 = 7,
	SurfaceType8 = 8,
	SurfaceType9 = 9,
	SurfaceType10 = 10,
	SurfaceType11 = 11,
	SurfaceType12 = 12,
	SurfaceType13 = 13,
	SurfaceType14 = 14,
	SurfaceType15 = 15,
	SurfaceType16 = 16,
	SurfaceType17 = 17,
	SurfaceType18 = 18,
	SurfaceType19 = 19,
	SurfaceType20 = 20,
	SurfaceType21 = 21,
	SurfaceType22 = 22,
	SurfaceType23 = 23,
	SurfaceType24 = 24,
	SurfaceType25 = 25,
	SurfaceType26 = 26,
	SurfaceType27 = 27,
	SurfaceType28 = 28,
	SurfaceType29 = 29,
	SurfaceType30 = 30,
	SurfaceType31 = 31,
	SurfaceType32 = 32,
	SurfaceType33 = 33,
	SurfaceType34 = 34,
	SurfaceType35 = 35,
	SurfaceType36 = 36,
	SurfaceType37 = 37,
	SurfaceType38 = 38,
	SurfaceType39 = 39,
	SurfaceType40 = 40,
	SurfaceType41 = 41,
	SurfaceType42 = 42,
	SurfaceType43 = 43,
	SurfaceType44 = 44,
	SurfaceType45 = 45,
	SurfaceType46 = 46,
	SurfaceType47 = 47,
	SurfaceType48 = 48,
	SurfaceType49 = 49,
	SurfaceType50 = 50,
	SurfaceType51 = 51,
	SurfaceType52 = 52,
	SurfaceType53 = 53,
	SurfaceType54 = 54,
	SurfaceType55 = 55,
	SurfaceType56 = 56,
	SurfaceType57 = 57,
	SurfaceType58 = 58,
	SurfaceType59 = 59,
	SurfaceType60 = 60,
	SurfaceType61 = 61,
	SurfaceType62 = 62,
	SurfaceType_Max = 63,
	EPhysicalSurface_MAX = 64
};
struct UPhysicalMaterial : uobject {
	float Friction; // 0x30(0x04)
	float StaticFriction; // 0x34(0x04)
	//enum class EFrictionCombineMode FrictionCombineMode; // 0x38(0x01)
	bool bOverrideFrictionCombineMode; // 0x39(0x01)
	char pad_3A[0x2]; // 0x3a(0x02)
	float Restitution; // 0x3c(0x04)
	//enum class EFrictionCombineMode RestitutionCombineMode; // 0x40(0x01)
	bool bOverrideRestitutionCombineMode; // 0x41(0x01)
	char pad_42[0x2]; // 0x42(0x02)
	float Density; // 0x44(0x04)
	float SleepLinearVelocityThreshold; // 0x48(0x04)
	float SleepAngularVelocityThreshold; // 0x4c(0x04)
	int32_t SleepCounterThreshold; // 0x50(0x04)
	float RaiseMassToPower; // 0x54(0x04)
	float DestructibleDamageThresholdScale; // 0x58(0x04)
	char pad_5C[0x4]; // 0x5c(0x04)
	struct UPhysicalMaterialPropertyBase* PhysicalMaterialProperty; // 0x60(0x08)
	enum class EPhysicalSurface SurfaceType; // 0x68(0x01)
	char pad_69[0x3]; // 0x69(0x03)
	//struct FPhysicalMaterialStrength Strength; // 0x6c(0x0c)
	//enum class EPhysicalSurface AudioSurfaceType; // 0x78(0x01)
	char pad_79[0x1f]; // 0x79(0x1f)
};
// Enum ShooterGame.EAresSurfaceType
enum class EAresSurfaceType : uint8 {
	Default = 0,
	Concrete = 1,
	Dirt = 2,
	Gravel = 3,
	Water = 4,
	Metal = 5,
	Wood = 6,
	Grass = 7,
	Glass = 8,
	Flesh = 9,
	Snow = 10,
	MetalThin = 11,
	BrokenGlass = 12,
	Impenetrable = 13,
	Linoleum = 14,
	BubbleCage = 15,
	MetalNonResonant = 16,
	CarpetOnWood = 17,
	MetalPipe = 18,
	ConcretePuddle = 19,
	GarbageBag = 20,
	Thorns = 21,
	Sand = 22,
	Mud = 23,
	Tree = 24,
	Ice = 25,
	ShootinRangeTarget = 26,
	Cloth = 27,
	CobbleStone = 28,
	CeramicTile = 29,
	CarpetOnConcrete = 30,
	EtherGlass = 31,
	CosmicFabric = 32,
	GoldenRipple = 33,
	PlasticHollow = 34,
	Shield = 35,
	Count = 36,
	EAresSurfaceType_MAX = 37
};


struct FHitResult {
	int32_t FaceIndex;
	float Time;
	float Distance;
	char pad_0C[0x4];
	fvector Location;
	fvector ImpactPoint;
	fvector Normal;
	fvector ImpactNormal;
	fvector TraceStart;
	fvector TraceEnd;
	float PenetrationDepth;
	int32_t MyItem;
	int32_t Item;
	uint8_t ElementIndex;
	uint8_t bBlockingHit : 1;
	uint8_t bStartPenetrating : 1;
	uint8_t pad_AD_bits : 6;
	char pad_AE[0x2];
	UPhysicalMaterial* PhysMaterial;
	AActor* HitActor;
	char pad_ActorHandle[0x10];
	UPrimitiveComponent* Component;
	fname BoneName;
	fname MyBoneName;
	char pad_END[0x8];
};

struct FWallSpanInfo {
	FHitResult Entrance;
	FHitResult Exit;
};

struct FWallSpanList {
	tarray<FWallSpanInfo> Spans;
	bool bLastPointInWall;
	char pad_11[0x7];
	FHitResult EntranceToLastPoint;
};


enum class ECollisionChannel : uint8 {
	ECC_WorldStatic = 0,
	ECC_WorldDynamic = 1,
	ECC_Pawn = 2,
	ECC_Visibility = 3,
	ECC_Camera = 4,
	ECC_PhysicsBody = 5,
	ECC_Vehicle = 6,
	ECC_Destructible = 7,
	ECC_EngineTraceChannel1 = 8,
	ECC_EngineTraceChannel2 = 9,
	ECC_EngineTraceChannel3 = 10,
	ECC_EngineTraceChannel4 = 11,
	ECC_EngineTraceChannel5 = 12,
	ECC_EngineTraceChannel6 = 13,
	ECC_GameTraceChannel1 = 14,
	ECC_GameTraceChannel2 = 15,
	ECC_GameTraceChannel3 = 16,
	ECC_GameTraceChannel4 = 17,
	ECC_GameTraceChannel5 = 18,
	ECC_GameTraceChannel6 = 19,
	ECC_GameTraceChannel7 = 20,
	ECC_GameTraceChannel8 = 21,
	ECC_GameTraceChannel9 = 22,
	ECC_GameTraceChannel10 = 23,
	ECC_GameTraceChannel11 = 24,
	ECC_GameTraceChannel12 = 25,
	ECC_GameTraceChannel13 = 26,
	ECC_GameTraceChannel14 = 27,
	ECC_GameTraceChannel15 = 28,
	ECC_GameTraceChannel16 = 29,
	ECC_GameTraceChannel17 = 30,
	ECC_GameTraceChannel18 = 31,
	ECC_OverlapAll_Deprecated = 32,
	ECC_MAX = 33
};

enum class ETraceTypeQuery : uint8
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery_MAX = 28
};
// Unreal Engine's EDrawDebugTrace (simplified)
enum EDrawDebugTrace : uint8
{
	None = 0,
	ForOneFrame = 1,
	ForDuration = 2,
	Persistent = 3,
	EDrawDebugTrace_MAX = 4
};

// Structures
struct alignas(0x04) FColor final
{
public:
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A;

	FColor() : B(0), G(0), R(0), A(0) {}
	FColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : B(b), G(g), R(r), A(a) {}
};

struct FProcMeshTangent final
{
public:
	fvector TangentX;
	bool bFlipTangentY;
	uint8_t Pad_19[0x7];
};



struct UMeshComponent : UPrimitiveComponent {
	struct tarray<struct UMaterialInterface*> OverrideMaterials; // 0x688(0x10)
	struct UMaterialInterface* OverlayMaterial; // 0x698(0x08)
	float OverlayMaterialMaxDrawDistance; // 0x6a0(0x04)
	char bOverrideDisableOcclusionQuery : 1; // 0x6a4(0x01)
	//struct FLinearColor OverlayColor; // 0x6a8(0x10)
	char pad_6BC_1 : 7; // 0x6bc(0x01)
	char pad_6BD[0xb]; // 0x6bd(0x0b)
	char bEnableMaterialParameterCaching : 1; // 0x6c8(0x01)
	char pad_6C8_1 : 7; // 0x6c8(0x01)
	char pad_6C9[0x7]; // 0x6c9(0x07)

	void SetVectorParameterValueOnMaterials(struct FName ParameterName, struct FVector ParameterValue); // Function Engine.MeshComponent.SetVectorParameterValueOnMaterials // (Final|RequiredAPI|Native|Public|HasDefaults|BlueprintCallable) // @ game+0x3ec6300
	void SetScalarParameterValueOnMaterials(struct FName ParameterName, float ParameterValue); // Function Engine.MeshComponent.SetScalarParameterValueOnMaterials // (Final|RequiredAPI|Native|Public|BlueprintCallable) // @ game+0x3ec64d0
	void SetOverlayMaterialMaxDrawDistance(float InMaxDrawDistance); // Function Engine.MeshComponent.SetOverlayMaterialMaxDrawDistance // (Final|RequiredAPI|Native|Public|BlueprintCallable) // @ game+0x3ec6910
	void SetOverlayMaterial(struct UMaterialInterface* NewOverlayMaterial); // Function Engine.MeshComponent.SetOverlayMaterial // (Final|RequiredAPI|Native|Public|BlueprintCallable) // @ game+0x3ec6a70
	void PrestreamTextures(float Seconds, bool bPrioritizeCharacterTextures, int32_t CinematicTextureGroups); // Function Engine.MeshComponent.PrestreamTextures // (RequiredAPI|Native|Public|BlueprintCallable) // @ game+0x3ec6680
	bool IsMaterialSlotNameValid(struct FName MaterialSlotName); // Function Engine.MeshComponent.IsMaterialSlotNameValid // (RequiredAPI|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6be0
	float GetOverlayMaterialMaxDrawDistance(); // Function Engine.MeshComponent.GetOverlayMaterialMaxDrawDistance // (Final|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6a10
	struct UMaterialInterface* GetOverlayMaterial(); // Function Engine.MeshComponent.GetOverlayMaterial // (Final|RequiredAPI|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6b90
	struct tarray<struct FName> GetMaterialSlotNames(); // Function Engine.MeshComponent.GetMaterialSlotNames // (RequiredAPI|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6d00
	struct tarray<struct UMaterialInterface*> GetMaterials(); // Function Engine.MeshComponent.GetMaterials // (RequiredAPI|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6ed0
	int32_t GetMaterialIndex(struct FName MaterialSlotName); // Function Engine.MeshComponent.GetMaterialIndex // (RequiredAPI|Native|Public|BlueprintCallable|BlueprintPure|Const) // @ game+0x3ec6db0
	void EmptyOverrideMaterials(); // Function Engine.MeshComponent.EmptyOverrideMaterials // (Final|RequiredAPI|Native|Public|BlueprintCallable) // @ game+0x3ec68b0
};

struct UProceduralMeshComponent : UMeshComponent
{
	char pad_6D0[0x8]; // 0x6d0(0x08)
	bool bUseComplexAsSimpleCollision; // 0x6d8(0x01)
	bool bUseAsyncCooking; // 0x6d9(0x01)
	char pad_6DA[0x6]; // 0x6da(0x06)
	uobject* ProcMeshBodySetup; // 0x6e0(0x08)
	char pad_6E8[0x88]; // Reste du padding jusqu'à la fin

	void SetRelativeScale3D1(fvector NewScale3D);

	void SetRelativeRotation1(void* Target, const frotator& Rotation, bool bSweep, bool bTeleport);

	void SetRelativeRotation2(frotator Target, bool bSweep = false, bool bTeleport = true);



};

struct UParticleSystemComponent : uobject {
};

struct UParticleSystem : uobject {
};



enum class EPSCPoolMethod : uint8_t {
	None = 0,
	AutoRelease = 1,
	ManualRelease = 2,
	ManualRelease_OnComplete = 3,
	FreeInPool = 4,
	EPSCPoolMethod_MAX = 5
};



enum class EAresParticleVariantColor : uint8_t {
	AresVariantBaseColor = 0,
	AresVariant1Color = 1,
	AresVariant2Color = 2,
	AresVariant3Color = 3,
	AresVariantRadiantColor = 4,
	EAresParticleVariantColor_MAX = 5
};

struct FSpawnEmitterAttachedParams {
	UParticleSystem* EmitterTemplate;
	USceneComponent* AttachToComponent;
	fname                     AttachPointName;
	fvector                   Location;
	FRotator                  Rotation;
	fvector                   Scale;
	int32_t                   LocationType;
	bool                      bAutoDestroy;
	int32_t                   PoolingMethod;
	bool                      bAutoActivate;
	bool                      bIsFirstPerson;
	float                     WarmupTime;
	int32_t                   ParticleVariantColor;
	UParticleSystemComponent* ReturnValue;
};

class UExponentialHeightFogComponent final : public USceneComponent
{
public:
	float                                         FogDensity;                                        // 0x0330(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FogHeightFalloff;                                  // 0x0334(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* SecondFogData;                                     // 0x0338(0x000C)(Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, NativeAccessSpecifierPublic)
	flinearcolor                           FogInscatteringColor;                              // 0x0344(0x0010)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           FogInscatteringLuminance;                          // 0x0354(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           SkyAtmosphereAmbientContributionColorScale;        // 0x0364(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_374[0x4];                                      // 0x0374(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	uobject* InscatteringColorCubemap;                          // 0x0378(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InscatteringColorCubemapAngle;                     // 0x0380(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct flinearcolor                           InscatteringTextureTint;                           // 0x0384(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FullyDirectionalInscatteringColorDistance;         // 0x0394(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         NonDirectionalInscatteringColorDistance;           // 0x0398(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DirectionalInscatteringExponent;                   // 0x039C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DirectionalInscatteringStartDistance;              // 0x03A0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           DirectionalInscatteringColor;                      // 0x03A4(0x0010)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           DirectionalInscatteringLuminance;                  // 0x03B4(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FogMaxOpacity;                                     // 0x03C4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         StartDistance;                                     // 0x03C8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FogCutoffDistance;                                 // 0x03CC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bEnableVolumetricFog;                              // 0x03D0(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_3D1[0x3];                                      // 0x03D1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         VolumetricFogScatteringDistribution;               // 0x03D4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	FColor                                 VolumetricFogAlbedo;                               // 0x03D8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           VolumetricFogEmissive;                             // 0x03DC(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VolumetricFogExtinctionScale;                      // 0x03EC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VolumetricFogDistance;                             // 0x03F0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VolumetricFogStartDistance;                        // 0x03F4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VolumetricFogNearFadeInDistance;                   // 0x03F8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VolumetricFogStaticLightingScatteringIntensity;    // 0x03FC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bOverrideLightColorsWithFogInscatteringColors;     // 0x0400(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_401[0xF];


	void SetFogDensity(float Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogDensity").decrypt());

		struct
		{
			float value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}

	void SetFogHeightFalloff(float Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogHeightFalloff").decrypt());

		struct
		{
			float value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}

	void SetFogInscatteringColor(flinearcolor Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogInscatteringColor").decrypt());

		struct
		{
			flinearcolor value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}
	void SetFogMaxOpacity(float Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogMaxOpacity").decrypt());

		struct
		{
			float value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}

	void SetStartDistance(float Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetStartDistance").decrypt());

		struct
		{
			float value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}

	void SetFogCutoffDistance(float Value) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogCutoffDistance").decrypt());

		struct
		{
			float value;
		} params;

		params.value = Value;

		this->process_event(function, &params);
	}

	void SetVolumetricFog(bool bNewValue) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetVolumetricFog").decrypt());

		struct
		{
			bool value;
		} params;

		params.value = bNewValue;

		this->process_event(function, &params);
	}
	void SetVolumetricFogDistance(float NewValue) {
		static uobject* function = 0;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetVolumetricFogDistance").decrypt());

		struct
		{
			float value;
		} params;

		params.value = NewValue;

		this->process_event(function, &params);
	}
};

namespace GameplayStatics {
	uobject* GameplayStatics();

	template<typename type>
	static inline tarray<type*> GetAllActorsOfClass(uworld* world_context, uobject* actor_class) {
		uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass"));
		struct {
			uworld* world_context;
			uobject* actor_class;
			tarray<type*> return_value;
		} params = { world_context, actor_class };
		GameplayStatics()->process_event(function, &params);
		return params.return_value;
	}

	static inline void GetAllActorsOfClass2(uworld* WorldContextObject, uobject* ActorClass, tarray<AGameObject*>* OutActors)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"GameplayStatics.GetAllActorsOfClass");
		struct {
			uworld* WorldContextObject;
			uobject* ActorClass;
			tarray<AGameObject*> OutActors;
		} params;
		params.WorldContextObject = WorldContextObject;
		params.ActorClass = ActorClass;
		GameplayStatics()->process_event(function, &params);
		if (OutActors)
			*OutActors = params.OutActors;
	}

	static inline double GetTimeSeconds(uobject* WorldContextObject)
	{
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetTimeSeconds").decrypt());
		if (!Function) return 0.0;
		struct {
			uobject* WorldContextObject;
			double ReturnValue;
		} params = { WorldContextObject, 0.0 };
		GameplayStatics()->process_event(Function, &params);
		return params.ReturnValue;
	}

	static inline UParticleSystemComponent* SpawnEmitterAttached(
		UParticleSystem* EmitterTemplate,
		USceneComponent* AttachToComponent,
		fname AttachPointName,
		fvector Location,
		FRotator Rotation,
		fvector Scale,
		EAttachLocation LocationType,
		bool bAutoDestroy,
		EPSCPoolMethod PoolingMethod,
		bool bAutoActivate,
		bool bIsFirstPerson,
		float WarmupTime,
		EAresParticleVariantColor ParticleVariantColor)
	{
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(L"Engine.GameplayStatics.SpawnEmitterAttached"); 
		if (!Function) return nullptr;

		struct {
			UParticleSystem* EmitterTemplate;
			USceneComponent* AttachToComponent;
			fname AttachPointName;
			fvector Location;      
			FRotator Rotation;
			fvector Scale;         
			EAttachLocation LocationType;
			bool bAutoDestroy;
			EPSCPoolMethod PoolingMethod;
			bool bAutoActivate;
			bool bIsFirstPerson;
			float WarmupTime;
			EAresParticleVariantColor ParticleVariantColor;
			UParticleSystemComponent* Out;
		} Args;

		Args.EmitterTemplate = EmitterTemplate;
		Args.AttachToComponent = AttachToComponent;
		Args.AttachPointName = AttachPointName;
		Args.Location = Location;
		Args.Rotation = Rotation;
		Args.Scale = Scale;
		Args.LocationType = LocationType;
		Args.bAutoDestroy = bAutoDestroy;
		Args.PoolingMethod = PoolingMethod;
		Args.bAutoActivate = bAutoActivate;
		Args.bIsFirstPerson = bIsFirstPerson;
		Args.WarmupTime = WarmupTime;
		Args.ParticleVariantColor = ParticleVariantColor;
		Args.Out = nullptr;

		GameplayStatics()->process_event(Function, &Args);
		return Args.Out;
	}

	static uint8_t GetSurfaceType(FHitResult Hit) {
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(L"Engine.GameplayStatics.GetSurfaceType");
		if (!Function) return 0;

		struct {
			FHitResult Hit;
			uint8_t ReturnValue;
		} params;

		params.Hit = Hit;
		GameplayStatics()->process_event(Function, &params);
		return params.ReturnValue;
	}
}






struct UAresWallPenetrationGlobals : uobject {
	bool bShowWallPenHitConfirms; // 0x30(0x01)
	char pad_31[0x7];             // 0x31(0x07)
	char pad_38[0x750];           // 0x38(0x750) — TSoftClassPtr<uobject> WallPenetrationType[0x27]
	uobject* WallPenetrationTypeCDOCached[0x27]; // 0x788(0x138)
	char pad_GlobalPenCurve[0x88]; // 0x8c0(0x88) — FRuntimeFloatCurve GlobalPenetrationCurve
};

struct UAresWallPenetration : uobject {
	float EnergyReductionMultiplier; // 0x30(0x04)
	bool  bParticipatesInAirDropoff; // 0x34(0x01)
	bool  bShowsRicochet;            // 0x35(0x01)
	char  pad_36[0x2];               // 0x36(0x02)
	// FString on skip aussi si pas défini
};
