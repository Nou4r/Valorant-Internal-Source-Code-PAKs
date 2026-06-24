#include "aimbot_v2.h"
#include "aimbot_v2_helpers.h"


namespace ShooterGameBlueprints {
    static uintptr_t GetAresGlobals() {
        static uobject* Function = nullptr;
        if (!Function) {
            Function = uobject::find_object<uobject*>(
                L"ShooterGame.ShooterBlueprintLibrary.GetAresGlobals");
        }
        if (!Function)
            return 0;

        static uobject* DefaultObj = nullptr;
        if (!DefaultObj) {
            DefaultObj = uobject::find_object<uobject*>(
                L"ShooterGame.Default__ShooterBlueprintLibrary");
        }
        if (!DefaultObj)
            return 0;

        struct {
            uintptr_t ReturnValue;
        } params = { 0 };

        DefaultObj->process_event(Function, &params);
        return params.ReturnValue;
    }

    static void GetWallPenetrationSpans(uworld* World, const fvector& Start,
        const fvector& End,
        const tarray<AActor*>& IgnoreActors,
        ECollisionChannel TraceChannel,
        float IgnoreGapTolerance,
        FWallSpanList& OutWallSpans) {
        static uobject* Function = nullptr;
        if (!Function) {
            Function = uobject::find_object<uobject*>(
                L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans");
        }

        if (!Function || !World) {
            return;
        }

        struct {
            uworld* World;
            fvector Start;
            fvector End;
            tarray<AActor*> IgnoreActors;
            ECollisionChannel TraceChannel;
            float IgnoreGapTolerance;
            FWallSpanList OutWallSpans;
        } params;

        params.World = World;
        params.Start = Start;
        params.End = End;
        params.IgnoreActors = IgnoreActors;
        params.TraceChannel = TraceChannel;
        params.IgnoreGapTolerance = IgnoreGapTolerance;

        World->process_event(Function, &params);
        OutWallSpans = params.OutWallSpans;
    }

    static uint8_t ConvertToAresSurfaceType(uint8_t SurfaceType) {
        static uobject* Function = nullptr;
        if (!Function) {
            Function = uobject::find_object<uobject*>(
                L"ShooterGame.ShooterBlueprintLibrary.ConvertToAresSurfaceType");
        }
        if (!Function)
            return 0;

        static uobject* DefaultObj = nullptr;
        if (!DefaultObj) {
            DefaultObj = uobject::find_object<uobject*>(
                L"ShooterGame.Default__ShooterBlueprintLibrary");
        }
        if (!DefaultObj)
            return 0;

        struct {
            uint8_t SurfaceType;
            uint8_t ReturnValue;
        } params;

        params.SurfaceType = SurfaceType;
        DefaultObj->process_event(Function, &params);
        return params.ReturnValue;
    }
}


const std::map<uint8_t, float> MaterialPenetrationLimits_v2 = {
    { 9,  0.0f },   // M_Flesh
    { 13, 0.0f },   // M_Impenetrable, M_Metal_Impenetrable, M_ThorneWall
    { 3,  200.0f }, // M_Gravel
    { 4,  200.0f }, // M_Water
    { 7,  200.0f }, // M_Grass
    { 22, 200.0f }, // M_Sand
    { 28, 200.0f }, // M_Cobblestone
    { 31, 200.0f }, // M_EtherGlass
    { 2,  150.0f }, // M_Dirt
    { 6,  150.0f }, // M_Wood
    { 1,  125.0f }, // M_Concrete
    { 5,  100.0f }  // M_Metal
};
std::map<std::wstring, WeaponPenetrationData_v2> WeaponDatabase_v2 = {
    { L"Vandal",   { 160.0f, 160.0f, 134.0f, 0.75f, 0.35f, true } },
    { L"Phantom",  { 156.0f, 156.0f, 130.0f, 0.75f, 0.35f, true } },
    { L"Operator", { 255.0f, 150.0f, 120.0f, 0.90f, 0.25f, true } },
    { L"Marshal",  { 202.0f, 101.0f,  85.0f, 0.85f, 0.30f, true } },
    { L"Sheriff",  { 159.0f,  55.0f,  46.0f, 0.70f, 0.40f, true } },
    { L"Guardian", { 195.0f,  65.0f,  49.0f, 0.80f, 0.30f, true } },
    { L"Outlaw",   { 140.0f, 140.0f, 119.0f, 0.78f, 0.32f, true } },
    { L"Ghost",    { 105.0f,  30.0f,  25.0f, 0.65f, 0.45f, true } },
    { L"Classic",  {  78.0f,  26.0f,  22.0f, 0.50f, 0.60f, false } },
    { L"Shorty",   {  20.0f,  12.0f,  10.0f, 0.20f, 0.80f, false } },
    { L"Frenzy",   {  78.0f,  26.0f,  21.0f, 0.55f, 0.55f, false } },
    { L"Spectre",  {  78.0f,  26.0f,  22.0f, 0.60f, 0.50f, true } },
    { L"Stinger",  {  67.0f,  27.0f,  22.0f, 0.58f, 0.52f, true } },
    { L"Bucky",    {  40.0f,  20.0f,  17.0f, 0.30f, 0.70f, false } },
    { L"Judge",    {  34.0f,  17.0f,  14.0f, 0.35f, 0.65f, false } },
    { L"Bulldog",  { 115.0f,  35.0f,  29.0f, 0.68f, 0.38f, true } },
    { L"Ares",     {  72.0f,  30.0f,  25.0f, 0.62f, 0.48f, true } },
    { L"Odin",     {  95.0f,  38.0f,  32.0f, 0.72f, 0.36f, true } }
};
namespace AutoWallHelpers_v2 {

    WeaponPenetrationData_v2 GetWeaponData_v2(ashootercharacter* Player) {
        if (!Player) return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };

        auto inv = Player->get_inventory();
        if (!inv) return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };

        auto eq = inv->get_current_equippable();
        if (!eq) return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };

        fstring weapon_name = system::get_object_name(eq);
        if (!weapon_name.c_str()) return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };

        std::wstring wname = weapon_name.wide();

        auto it = WeaponDatabase_v2.find(wname);
        if (it != WeaponDatabase_v2.end())
            return it->second;

        return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };
    }

    float GetDamageForBone_v2(const WeaponPenetrationData_v2& data, int bone_index) {
        switch (bone_index) {
        case 0: case 8: return data.HeadDamage;
        case 1: case 7: return data.BodyDamage;
        default: return data.LegDamage;
        }
    }

    uintptr_t SafeReadPointer(uintptr_t address) {
        if (!memory::IsValidPointer(address)) return 0;
        return memory::read<uintptr_t>(address);
    }

    uint8_t SafeReadByte(uintptr_t address) {
        if (!memory::IsValidPointer(address)) return 0;
        return memory::read<uint8_t>(address);
    }

    bool CanPenetrateMaterial_v2(uint8_t surfaceType, float thickness) {
        auto it = MaterialPenetrationLimits_v2.find(surfaceType);
        if (it != MaterialPenetrationLimits_v2.end())
            return thickness <= it->second;

        switch (surfaceType) {
        case 3: case 4: case 7: case 22: case 28: case 31: return thickness <= 200.f;
        case 2: case 6: return thickness <= 150.f;
        case 5: return thickness <= 100.f;
        case 1: return thickness <= 125.f;
        case 9: case 13: case 26: return false;
        default: return thickness <= 175.f;
        }
    }

    uint8_t GetSurfaceTypeFromActor_v2(AActor* HitActor, const FHitResult& HitResult) {
        if (!HitActor || !HitResult.Component ||
            !memory::IsValidPointer((uintptr_t)HitActor) ||
            !memory::IsValidPointer((uintptr_t)HitResult.Component))
            return 255;

        uintptr_t ComponentAddr = (uintptr_t)HitResult.Component;
        uintptr_t StaticMeshAddr = SafeReadPointer(ComponentAddr + 0x6E8);
        if (!StaticMeshAddr) return 255;

        uintptr_t MaterialsDataPtr = SafeReadPointer(StaticMeshAddr + 0x160);
        int32_t MaterialsCount = SafeRead<int32_t>(StaticMeshAddr + 0x168);
        if (!MaterialsDataPtr || MaterialsCount <= 0) return 255;

        uintptr_t MaterialAddr = SafeReadPointer(MaterialsDataPtr);
        if (!MaterialAddr) return 255;

        uintptr_t PhysMatAddr = SafeReadPointer(MaterialAddr + 0xD0);
        return SafeReadByte(PhysMatAddr + 0x68);
    }
}

bool TraceHelperV2::CanShootThroughBone(aplayercontroller* Controller,
    ashootercharacter* ShooterChar,
    ashootercharacter* TargetEnemy,
    int AimBone,
    float& outRemainingDamage)
{
    outRemainingDamage = 0.0f;
    if (!Controller || !ShooterChar || !TargetEnemy) return false;

    auto weaponData = AutoWallHelpers_v2::GetWeaponData_v2(ShooterChar);
    if (!weaponData.CanPenetrateWalls) return false;

    uskeletalmeshcomponent* EnemyMesh = TargetEnemy->get_mesh();
    if (!EnemyMesh || !memory::IsValidPointer((uintptr_t)EnemyMesh)) return false;

    auto camMgr = Controller->get_camera_manager();
    if (!camMgr || !memory::IsValidPointer((uintptr_t)camMgr)) return false;
    fvector CameraLoc = camMgr->get_camera_location();

    fvector TargetBonePos = GetBoneMatrix_v2(EnemyMesh, AimBone);

    float RemainingDamage = AutoWallHelpers_v2::GetDamageForBone_v2(weaponData, AimBone);
    float PenPower = weaponData.PenetrationPower;
    float ReductionRate = weaponData.DamageReductionPerWall;
    tarray<AActor*> IgnoreActors;
    IgnoreActors.Add((AActor*)ShooterChar);

    FWallSpanList WallSpans;
    memset(&WallSpans, 0, sizeof(FWallSpanList));

    ShooterGameBlueprints::GetWallPenetrationSpans(
        GetWorldSafe_v2(), CameraLoc, TargetBonePos, IgnoreActors,
        ECollisionChannel::ECC_Visibility, 0.0f, WallSpans
    );

    if (WallSpans.bLastPointInWall) {
        if (WallSpans.EntranceToLastPoint.HitActor &&
            memory::IsValidPointer((uintptr_t)WallSpans.EntranceToLastPoint.HitActor) &&
            WallSpans.EntranceToLastPoint.HitActor != (AActor*)TargetEnemy)
            return false;

        fvector d = WallSpans.EntranceToLastPoint.Location - TargetBonePos;
        float dist_sq = d.x * d.x + d.y * d.y + d.z * d.z;
        if (dist_sq >= 10000.0f) return false;
    }

    FWallSpanInfo* SpansData = nullptr;
    int32_t SpansCount = 0;
    SpansData = WallSpans.Spans.data;
    SpansCount = WallSpans.Spans.count;
    if (!SpansData || SpansCount <= 0) {
        outRemainingDamage = RemainingDamage;
        return true;
    }
    const float maxTotalThickness = PenPower * 350.f;
    const float penPower200 = PenPower * 200.f;
    const float penPower180 = PenPower * 180.f;
    const float reductionMult = 0.01f;

    float totalThickness = 0.0f;
    int wallsPenetrated = 0;

    for (int i = 0; i < SpansCount; i++) {
        const FWallSpanInfo& Span = SpansData[i];
        fvector diff = Span.Exit.Location - Span.Entrance.Location;
        float thickness = diff.size();
        if (thickness < 0.01f || thickness > 5000.0f) continue;

        totalThickness += thickness;
        if (totalThickness > maxTotalThickness) return false;
        if (++wallsPenetrated > 3) return false;

        AActor* WallActor = nullptr;
        if (Span.Entrance.HitActor && memory::IsValidPointer((uintptr_t)Span.Entrance.HitActor))
            WallActor = Span.Entrance.HitActor;
        else if (Span.Exit.HitActor && memory::IsValidPointer((uintptr_t)Span.Exit.HitActor))
            WallActor = Span.Exit.HitActor;

        if (WallActor) {
            fstring ActorName = system::get_object_name(WallActor);
            std::wstring actorStr = ActorName.wide();
            if (actorStr.find(L"barrier") != std::wstring::npos ||
                actorStr.find(L"Barrier") != std::wstring::npos ||
                actorStr.find(L"wall_c") != std::wstring::npos ||
                actorStr.find(L"thorne") != std::wstring::npos ||
                actorStr.find(L"ability") != std::wstring::npos ||
                actorStr.find(L"Ability") != std::wstring::npos ||
                actorStr.find(L"sage") != std::wstring::npos ||
                actorStr.find(L"shield") != std::wstring::npos)
                return false;

            const FHitResult* hit = (WallActor == Span.Entrance.HitActor) ? &Span.Entrance : &Span.Exit;
            uint8 surfaceType = AutoWallHelpers_v2::GetSurfaceTypeFromActor_v2(WallActor, *hit);
            if (!AutoWallHelpers_v2::CanPenetrateMaterial_v2(surfaceType, thickness))
                return false;

            RemainingDamage *= (1.0f - ReductionRate * thickness * reductionMult);
            if (RemainingDamage <= 1.0f || thickness > penPower200) return false;
        }
        else {
            if (thickness > penPower180) return false;
            RemainingDamage *= (1.0f - ReductionRate);
            if (RemainingDamage <= 1.0f) return false;
        }
    }

    if (RemainingDamage <= 1.0f) return false;
    outRemainingDamage = RemainingDamage;
    return true;
}

bool TraceHelperV2::CanShootThrough(aplayercontroller* Controller,
    ashootercharacter* ShooterChar,
    ashootercharacter* TargetEnemy,
    int AimBone)
{
    float dummy;
    return CanShootThroughBone(Controller, ShooterChar, TargetEnemy, AimBone, dummy);
}

// ==========================================
// Trial
// ==========================================
void AimbotV2::RunTest() {
    // auto controller = ...;
    // auto character  = ...;
    // for (auto actor : actors) {
    //     float dmg = 0;
    //     if (TraceHelperV2::CanShootThroughBone(controller, character, actor, 8, dmg)) {
    //
    //     }
    // }
}