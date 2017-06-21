#include "Vungle.h"

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Misc/ConfigCacheIni.h"
#include "Async/TaskGraphInterfaces.h"
#include "StringConv.h"

DEFINE_LOG_CATEGORY_STATIC(AdCollection, Log, All);

//#define CHECK_JNI_METHOD(Id) checkf(Id != nullptr, TEXT("Failed to find " #Id));

void FVungleModule::PlayRewardedVideo()
{
	UE_LOG(AdCollection, Log, TEXT("Ready PLayAd In cpp") );
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID PlayAdMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Vungle_PlayAd", "()Z", bIsOptional);
		//CHECK_JNI_METHOD(PlayAdMethod);
		if (PlayAdMethod == nullptr)
		{
			UE_LOG(AdCollection, Error, TEXT("AndroidThunkJava_Vungle_PlayAd not found"));
			return;
		}

		// Convert scope array into java fields
		FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, PlayAdMethod);
	}
}


bool FVungleModule::IsRewardedVideoReady()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID JniMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Vungle_Ready", "()Z", bIsOptional);
		if (JniMethod == nullptr)
		{
			UE_LOG(AdCollection, Error, TEXT("AndroidThunkJava_Vungle_Ready not found"));
			return false;
		}

		// Convert scope array into java fields
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, JniMethod);
	}

	return false;
}

__attribute__((visibility("default"))) extern "C" void Java_com_ads_util_Vungle_nativePlayRewardedComplete(JNIEnv* jenv, jobject thiz, jboolean isClick)
{
	FVungleModule* pModule = FModuleManager::Get().LoadModulePtr<FVungleModule>(TEXT("Vungle") );
	if (pModule == nullptr) return;

	
	FRewardedStatus status;
	status.State = ERewardState::COMPLETED;
	if(isClick) status.State = ERewardState::CLICKED;
	status.AdType = EAdType::Vungle;

	pModule->TriggerPlayRewardCompleteDelegates(status);
}