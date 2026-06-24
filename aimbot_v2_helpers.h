#pragma once
#include "functions.hpp"
#include "offsets.hpp"
#include "memory.hpp"


inline fvector GetBoneMatrix_v2(uskeletalmeshcomponent* mesh, int bone_index) {
    if (!mesh) return fvector();
    return mesh->get_bone_location(bone_index);
}

inline uworld* GetWorldSafe_v2() {
    uintptr_t base = memory::module_base;
    if (!base) return nullptr;
    
    uintptr_t state_ptr = base + offsets::State;
    if (!memory::IsValidPointer(state_ptr)) return nullptr;
    
    uintptr_t* uworld_state_ptr = *(uintptr_t**)state_ptr;
    if (!uworld_state_ptr || !memory::IsValidPointer((uintptr_t)uworld_state_ptr)) return nullptr;
    
    return *(uworld**)uworld_state_ptr;
}