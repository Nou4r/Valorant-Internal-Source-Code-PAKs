#pragma once
#include <map>
#include <vector>
#include <string>
#include "functions.hpp"
#include "offsets.hpp"
#include "memory.hpp"

struct WeaponPenetrationData_v2 {
    float HeadDamage;
    float BodyDamage;
    float LegDamage;
    float PenetrationPower;
    float DamageReductionPerWall;
    bool  CanPenetrateWalls;
};

extern const std::map<uint8_t, float> MaterialPenetrationLimits_v2;
extern std::map<std::wstring, WeaponPenetrationData_v2> WeaponDatabase_v2;

namespace AutoWallHelpers_v2 {
    WeaponPenetrationData_v2 GetWeaponData_v2(ashootercharacter* Player);
    float GetDamageForBone_v2(const WeaponPenetrationData_v2& data, int bone_index);
    template<typename T>
    T SafeRead(uintptr_t address) {
        if (!memory::IsValidPointer(address)) return T{};
        return memory::read<T>(address);
    }
    uintptr_t SafeReadPointer(uintptr_t address);
    uint8_t  SafeReadByte(uintptr_t address);
    bool CanPenetrateMaterial_v2(uint8_t surfaceType, float thickness);
    uint8_t GetSurfaceTypeFromActor_v2(AActor* HitActor, const FHitResult& HitResult);
}

class TraceHelperV2 {
public:
    static bool CanShootThroughBone(aplayercontroller* Controller,
        ashootercharacter* ShooterChar,
        ashootercharacter* TargetEnemy,
        int AimBone,
        float& outRemainingDamage);
    static bool CanShootThrough(aplayercontroller* Controller,
        ashootercharacter* ShooterChar,
        ashootercharacter* TargetEnemy,
        int AimBone = 8);

    // will add more stuff suck as bonewallmatrix...
};
// S I K K E V E R - Bone Helper
class BoneHelper {
public:
    static fname GetBoneName(uskeletalmeshcomponent* Mesh, int32_t BoneIndex) {
        if (!Mesh || !memory::IsValidPointer((uintptr_t)Mesh)) return fname();

        auto function_name = L"Engine.SkinnedMeshComponent.GetBoneName";
        static uobject* Function = nullptr;
        if (!Function)
            Function = uobject::find_object<uobject*>(function_name);
        if (!Function) return fname();

        struct {
            int32_t BoneIndex;
            fname ReturnValue;
        } params = { BoneIndex, fname() };

        Mesh->process_event(Function, &params);
        return params.ReturnValue;
    }
    static int32_t GetBoneIndex(uskeletalmeshcomponent* Mesh, fname BoneName) {
        if (!Mesh || !memory::IsValidPointer((uintptr_t)Mesh)) return -1;

        auto function_name = L"Engine.SkinnedMeshComponent.GetBoneIndex";
        static uobject* Function = nullptr;
        if (!Function)
            Function = uobject::find_object<uobject*>(function_name);
        if (!Function) return -1;

        struct {
            fname BoneName;
            int32_t ReturnValue;
        } params = { BoneName, -1 };

        Mesh->process_event(Function, &params);
        return params.ReturnValue;
    }
    static int32_t GetBonePriorityByIndex(int32_t BoneIndex, int32_t BoneCount) {
        switch (BoneCount) {
        case 101:
            if (BoneIndex == 20) return 100;
            if (BoneIndex == 21) return 90;
            if (BoneIndex >= 17 && BoneIndex <= 19) return 80;
            if (BoneIndex >= 15 && BoneIndex <= 16) return 70;
            if (BoneIndex >= 13 && BoneIndex <= 14) return 60;
            if (BoneIndex == 3) return 50;
            if (BoneIndex >= 23 && BoneIndex <= 25) return 30;
            if (BoneIndex >= 49 && BoneIndex <= 51) return 30;
            if (BoneIndex >= 75 && BoneIndex <= 78) return 25;
            if (BoneIndex >= 82 && BoneIndex <= 85) return 25;
            return 10;

        case 103:
            if (BoneIndex == 8) return 100;
            if (BoneIndex == 9) return 90;
            if (BoneIndex >= 5 && BoneIndex <= 7) return 80;
            if (BoneIndex == 3) return 50;
            if (BoneIndex >= 30 && BoneIndex <= 33) return 30;
            if (BoneIndex >= 55 && BoneIndex <= 58) return 30;
            if (BoneIndex >= 63 && BoneIndex <= 69) return 25;
            if (BoneIndex >= 77 && BoneIndex <= 83) return 25;
            return 10;

        case 104:
            if (BoneIndex == 20) return 100;
            if (BoneIndex == 21) return 90;
            if (BoneIndex >= 17 && BoneIndex <= 19) return 80;
            if (BoneIndex >= 15 && BoneIndex <= 16) return 70;
            if (BoneIndex >= 13 && BoneIndex <= 14) return 60;
            if (BoneIndex == 3) return 50;
            if (BoneIndex >= 23 && BoneIndex <= 25) return 30;
            if (BoneIndex >= 49 && BoneIndex <= 51) return 30;
            if (BoneIndex >= 77 && BoneIndex <= 80) return 25;
            if (BoneIndex >= 84 && BoneIndex <= 87) return 25;
            return 10;

        default:
            if (BoneIndex <= 10) return 80;
            if (BoneIndex <= 20) return 60;
            if (BoneIndex <= 30) return 40;
            return 20;
        }
    }
    static inline void GetCriticalBones(int32_t BoneCount, int32_t* outBones, int32_t& outCount) {
        if (BoneCount == 101 || BoneCount == 104) {
            static const int32_t bones[] = { 20, 21, 19, 18, 17, 3 };
            memcpy(outBones, bones, sizeof(bones));
            outCount = 6;
        }
        else if (BoneCount == 103) {
            static const int32_t bones[] = { 8, 9, 7, 6, 5, 3 };
            memcpy(outBones, bones, sizeof(bones));
            outCount = 6;
        }
        else {
            outCount = 0;
        }
    }
    static bool IsBoneValid(uskeletalmeshcomponent* Mesh, int32_t BoneIndex) {
        if (!Mesh || !memory::IsValidPointer((uintptr_t)Mesh)) return false;
        int32_t bone_count = memory::read<int32_t>((uintptr_t)Mesh + offsets::bone_cout);
        return BoneIndex >= 0 && BoneIndex < bone_count;
    }
    static bool IsHeadBone(uskeletalmeshcomponent* Mesh, int32_t BoneIndex) {
        if (!Mesh || !memory::IsValidPointer((uintptr_t)Mesh)) return false;
        int32_t bone_count = memory::read<int32_t>((uintptr_t)Mesh + offsets::bone_cout);
        switch (bone_count) {
        case 101: case 104: return BoneIndex == 20;
        case 103: return BoneIndex == 8;
        default: return GetBonePriorityByIndex(BoneIndex, bone_count) >= 100;
        }
    }
};

namespace AimbotV2 {
    void RunTest();
}