#include "functions.hpp"
#include "offsets.hpp"
#include "spoof.h"
#include <cstdlib>    
#include <ctime>   
#include <random>





uobject* uobject::StaticLoadObject(uobject* Class, uobject* InOuter, const wchar_t* Name)
{
	
	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	auto StaticLoadObjectFN = reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool)>(StaticLoadObjectAddress);
	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, 0x46C4660, (void*)StaticLoadObjectFN);
}

uobject* uobject::StaticLoadObject(const wchar_t* ObjectPath) {

	if (!ObjectPath)
		return nullptr;

}

bool uobject::is_child_of(uclass* parent) {
	for (auto super = this->object_class(); super; super = super->super_class()) {
		if (super == parent) {
			return true;
		}
	}
	return false;
}

uclass* uobject::object_class() {
	
	return memory::read<uclass*>(class_ptr + 0x10);
}

uclass* uclass::super_class() {
	
	return memory::read<uclass*>(class_ptr + 0x48);
}

tarray<int> equippable_skin_data_asset::get_skin_levels() {
	
	return memory::read<tarray<int>>(std::uintptr_t(this) + 0x88);
}

equippable_skin_data_asset* equippable_skin_inventory_model::get_skin_data_asset() {
	
	return memory::read<equippable_skin_data_asset*>(std::uintptr_t(this) + 0x108);
}

uobject* equippable_skin_chroma_inventory_model::get_skin_chroma_data_asset() {
	
	return memory::read<uobject*>(std::uintptr_t(this) + 0x108);
}

uobject* equippable_charm_instance_inventory_model::get_charm_data_asset() {
	
	return memory::read<uobject*>(std::uintptr_t(this) + 0x68);
}

equippable_charm_level_data_asset* equippable_charm_instance_inventory_model::get_charm_level_data_asset() {
	
	return memory::read<equippable_charm_level_data_asset*>(std::uintptr_t(this) + 0x70);
}

int equippable_charm_level_data_asset::get_charm_level() {
	
	return memory::read<int>(std::uintptr_t(this) + 0xe0);
}

void uobject::process_event(uobject* function, void* args) {
	
	return reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, args, 0x46C4660, (void*)(memory::module_base + offsets::process_event));
}

//void uobject::process_event2(void* class_, uobject* function, void* params)
//{
//	return reinterpret_cast<void (*)(uobject*, uobject*, void*)>(memory::module_base + offsets::process_event)(this, function, params);
//}

uint64_t fmemory::malloc(int32_t size, uint32_t aligment) {
	
	return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int)>(memory::module_base + offsets::fmemory_malloc)(size, aligment);
}


utexture2d* system::import_file_as_texture2d(uobject* world_context_object, fstring filename)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.KismetRenderingLibrary.ImportFileAsTexture2D");

	struct
	{
		uobject* world_context_object;
		fstring filename;
		utexture2d* return_value;
	} params;

	params.world_context_object = world_context_object;
	params.filename = filename;

	variables.rendering_library->process_event(function, &params);
	return params.return_value;
}

fstring system::get_object_name(uobject* object) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetObjectName"));

	struct
	{
		uobject* object;
		fstring output;
	} params;

	params.object = { object };

	variables.kismet_system->process_event(function, &params);
	return params.output;
}


bool system::contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case, bool search_from_end) {
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains"));

	struct {
		fstring search_in;
		fstring sub_string;
		bool use_case;
		bool search_from_end;
		bool return_value;
	} params = { search_in, sub_string, use_case , search_from_end };

	variables.kismet_string->process_event(function, &params);
	return params.return_value;
}

bool system::starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case) {
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.StartsWith"));

	struct {
		fstring source;
		fstring prefix;
		std::uint8_t search_case;
		bool return_value;
	} params = { source, prefix, search_case.get() };

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}

uobject* system::get_outer_object(uobject* object) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetOuterObject"));

	struct
	{
		uobject* object;
		uobject* output;
	} params;

	variables.kismet_system->process_event(function, &params);

	return params.output;
}

auto string_utils::STATIC_Conv_NameToString(fname InName) -> fstring
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_NameToString"));;

	struct
	{
		fname string;
		fstring output;
	} params;

	params.string = InName;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}

fname string_utils::string_to_name(fstring string) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_StringToName"));;

	struct
	{
		fstring string;
		fname output;
	} params;

	params.string = string;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}

fname string::string_to_name(fstring string) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_StringToName"));;

	struct
	{
		fstring string;
		fname output;
	} params;

	params.string = string;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}


fstring text::text_to_string(ftext string) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_TextToString"));

	struct
	{
		ftext text;
		fstring output;
	} params;

	params.text = string;

	variables.kismet_text->process_event(function, &params);

	return params.output;
}

ftext text::string_to_text(const fstring& InString)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_StringToText"));

	struct
	{
		fstring InString;
		ftext ReturnValue;
	} params;

	params.InString = InString;

	variables.kismet_text->process_event(function, &params);

	return params.ReturnValue;
}

ugameinstance* uworld::game_instance() {
	
	return memory::read<ugameinstance*>(class_ptr + offsets::game_instance);
}

tarray<ulocalplayer*> ugameinstance::local_players() {
	
	return memory::read<tarray<ulocalplayer*>>(class_ptr + offsets::local_players);
}

ugameviewportclient* ulocalplayer::viewport_client() {
	
	return memory::read<ugameviewportclient*>(class_ptr + offsets::viewport_client);
}

uworld* ugameviewportclient::get_world() {
	
	return memory::read<uworld*>(class_ptr + offsets::viewport_world);
}

ugameinstance* ugameviewportclient::get_gameinstance() {
	
	return memory::read<ugameinstance*>(class_ptr + offsets::viewport_gameinstance);
}



tarray<ashootercharacter*> blueprints::find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.FindAllShooterCharactersWithAlliance"));

	struct
	{
		uobject* context;
		ashootercharacter* viewer;
		earesalliance alliance;
		bool only_player;
		bool only_alive;
		tarray<ashootercharacter*> output;
	} params;

	params.context = context;
	params.viewer = viewer;
	params.alliance = alliance;
	params.only_player = only_player;
	params.only_alive = only_alive;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

tarray<ashootercharacter*> blueprints::find_all_game_objects(uworld* world_context) {
	
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.FindAllGameObjects"));

	if (function == nullptr || world_context == nullptr) return {};

	struct {
		uworld* world_context;
		tarray<ashootercharacter*> return_value;
	} params = { world_context };

	variables.blueprints->process_event(function, &params);
	return params.return_value;
}

aplayercontroller* blueprints::get_local_controller(uobject* context) {
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetLocalController"));

	struct {
		uobject* world_context;
		aplayercontroller* return_value;
	} params = { context };

	variables.blueprints->process_event(function, &params);

	return params.return_value;
}

aplayercontroller* blueprints::get_player_controller(uobject* context)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetFirstLocalPlayerController"));

	struct
	{
		uobject* context;
		aplayercontroller* output;
	} params;

	params.context = context;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

void game_statics::get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass"));

	struct
	{
		uobject* context;
		uobject* _class;
		tarray<gameobject*> output;
	} params;

	params.context = context;
	params._class = _class;

	variables.gameplay_statics->process_event(function, &params);

	*output = params.output;
}

void content_library::apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ApplySkin"));

	struct
	{
		currentequippable* equippable;
		uobject* skin_asset;
		uobject* chroma_asset;
		int level;
		uobject* charm_data;
		int buddie_level;
	} params;

	params.equippable = equippable;
	params.skin_asset = skin_asset;
	params.chroma_asset = chroma_asset;
	params.level = level;
	params.charm_data = charm_data;
	params.buddie_level = buddie_level;

	variables.content_library->process_event(function, &params);
}

void content_library::clear_weapon_components(currentequippable* equippable) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ClearWeaponComponents"));

	struct
	{
		currentequippable* equippable;
	} params;

	params.equippable = equippable;

	variables.content_library->process_event(function, &params);
}

ashootercharacter* aplayercontroller::get_shooter_character() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetShooterCharacter"));

	struct
	{
		ashootercharacter* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}




bool aplayercontroller::dormant_server(ashootercharacter* actor) {
	
	return memory::read<bool>(reinterpret_cast<uintptr_t>(actor) + 0x101);
}

bool aplayercontroller::is_input_key_down(aplayercontroller* controller, const fkey key)
{
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.IsInputKeyDown"));

	struct
	{
		fkey Key;
		bool ReturnValue;
	} params;

	params.Key = key;

	this->process_event(Function, &params);
	return params.ReturnValue;
}

void aplayercontroller::disconnect_server() {
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.DisconnectFromServer"));

	this->process_event(function, nullptr);
}
bool aplayercontroller::line_of_sight(ashootercharacter* enemy) {
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.LineOfSightTo"));

	struct {
		ashootercharacter* Enemy;
		fvector ViewPoint;
		bool bAlternateCheck;
		bool ReturnValue;
	} params;
	params.Enemy = enemy;
	params.ViewPoint = fvector(0, 0, 0);
	params.bAlternateCheck = false;

	this->process_event(function, &params);
	return params.ReturnValue;
}




fvector2d aplayercontroller::project_world_to_screen(fvector world) {

	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct
	{
		fvector world;
		fvector2d screen;
		bool relative_viewport;
	} params;

	params.world = world;
	params.relative_viewport = true;

	this->process_event(function, &params);
	return params.screen;
}

int32_t uskeletalmeshcomponent::get_num_bones() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.GetNumBones"));
	struct {
		int32_t return_value;
	} params;
	this->process_event(function, &params);
	return params.return_value;
}


fname uskeletalmeshcomponent::get_bone_name(int32_t bone_index) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.GetBoneName"));
	struct {
		int32_t bone_index;
		fname return_value;
	} params;
	params.bone_index = bone_index;
	this->process_event(function, &params);
	return params.return_value;
}

fvector uskeletalmeshcomponent::get_socket_location(fname socket_name) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.GetSocketLocation"));
	struct {
		fname socket_name;
		fvector return_value;
	} params;
	params.socket_name = socket_name;
	this->process_event(function, &params);
	return params.return_value;
}


bool aplayercontroller::project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative) {

	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}

fvector acknowledgedpawn::get_controlrotation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

void uskeletalmeshcomponent::set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport)
{
	

	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetWorldRotation"));

	if (function == nullptr)
		return;

	struct {
		fvector NewRotation;
		bool bsweep;
		uintptr_t FHitResult;
		bool bTeleport;
	} params = { NewRotation, bsweep, 0, bteleport };

	this->process_event(function, &params);
}

uskeletalmeshcomponent* currentequippable::GetMesh3P()
{
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh3P"));

	struct
	{
		uskeletalmeshcomponent* Out;

	}Parameters;
	this->process_event(Function, &Parameters);
	return Parameters.Out;
}

fvector aplayercontroller::get_control_rotation()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

void aplayercontroller::simulate_input_key(fkey key, bool bpressed) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"AresPlayerController.SimulateInputKey");

	struct { fkey a1; bool a2; } params{};

	params.a1 = key;
	params.a2 = bpressed;

	this->process_event(function, &params);
}

void aplayercontroller::set_control_rotation(fvector angle) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation"));

	struct
	{
		fvector angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}

uskeletalmeshcomponent* ashootercharacter::get_mesh() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetPawnMesh"));

	struct
	{
		uskeletalmeshcomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


uskeletalmeshcomponent* ashootercharacter::mesh3p() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCoreMesh3P"));

	struct
	{
		uskeletalmeshcomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


uskeletalmeshcomponent* acknowledgedpawn::GetMesh11P()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

uskeletalmeshcomponent* currentequippable::GetMesh1P()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

uskeletalmeshcomponent* currentequippable::GetEquippableMesh()
{
	
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresEquippable.GetEquippableMesh");

	struct
	{
		uskeletalmeshcomponent* Out;
	} Parameters{};

	this->process_event(function, &Parameters);
	return Parameters.Out;
}

void uskeletalmeshcomponent::SetMaterial(int32_t ElementIndex, uobject* Material) {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial"));
	if (!function) {
		return;
	}

	struct {
		int32_t ElementIndex;
		uobject* Material;
	} Parameters;

	Parameters.ElementIndex = ElementIndex;
	Parameters.Material = Material;
	this->process_event(function, &Parameters);
}

void uskeletalmeshcomponent::SetOutlineMode(EAresOutlineMode Mode)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresOutlineComponent.SetOutlineMode"));
	struct
	{
		EAresOutlineMode Mode;
	}Parameters;
	Parameters.Mode = Mode;

	function->process_event(function, &Parameters);
}

uskeletalmeshcomponent* ashootercharacter::GetOverlayMesh1P()
{

	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

uskeletalmeshcomponent* acknowledgedpawn::GetOverlayMesh11P()
{


	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}




//UPrimitiveComponent* acknowledgedpawn::GetOverlayMesh1P2()
//{
//
//
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));
//
//	struct
//	{
//		UPrimitiveComponent* Out;
//	}Parameters;
//	this->process_event(function, &Parameters);
//	return Parameters.Out;
//}
//
//UPrimitiveComponent* acknowledgedpawn::GetMesh1P2()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMesh1P"));
//
//	struct
//	{
//		UPrimitiveComponent* returnvalue;
//	} parameters;
//
//	this->process_event(function, &parameters);
//
//	return parameters.returnvalue;
//}


void ashootercharacter::GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorEyesViewPoint"));

	struct
	{
		fvector OutLocation;
		frotator OutRotation;
	} params;

	this->process_event(function, &params);

	if (OutLocation)
		*OutLocation = params.OutLocation;
	if (OutRotation)
		*OutRotation = params.OutRotation;
}

fvector ashootercharacter::GetActorForwardVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorForwardVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector ashootercharacter::GetActorRightVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorRightVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector ashootercharacter::GetActorUpVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorUpVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

uinventory* ashootercharacter::get_inventory() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetInventory"));

	struct
	{
		uinventory* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

currentequippable* uinventory::get_current_equippable()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable"));

	struct
	{
		currentequippable* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

fvector ashootercharacter::k2_get_actor_location()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation"));

	struct
	{
		fvector Out;
	} params;
	this->process_event(function, &params);

	return params.Out;
}

void ashootercharacter::custom_set_actor_location(fvector NewLocation, bool bSweep, bool bTeleport)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorLocation"));

	struct
	{
		fvector NewLocation;
		bool bSweep;
		struct FHitResult SweepHitResult;
		bool bTeleport;
		bool ReturnValue;
	} params;
	params.NewLocation = NewLocation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	params.SweepHitResult = {};
	this->process_event(function, &params);
}

uobject* ashootercharacter::get_character_icon()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCharacterIcon"));

	struct
	{
		uobject* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

uskeletalmeshcomponent* ashootercharacter::getmesh1p()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMesh1P"));

	struct
	{
		uskeletalmeshcomponent* returnvalue; 
	} parameters;

	this->process_event(function, &parameters);
	return parameters.returnvalue;
}

void ashootercharacter::Set3pMeshVisible(bool val)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.Set3PMeshVisible"));
	if (!Function)
	{
		return;
	}
	struct
	{
		bool a1;
	}Parameters;
	Parameters.a1 = val;
	this->process_event(Function, &Parameters);
	return;
}

void ashootercharacter::SetCrouchTimeOverride(float Override)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.SetCrouchTimeOverride"));
	if (!Function)
	{
		return;
	}
	struct
	{
		bool Override;
	}Parameters;
	Parameters.Override = Override;
	this->process_event(Function, &Parameters);
	return;
}

USceneComponent* ashootercharacter::K2_GetRootComponent()
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetRootComponent"));
	if (!Function)
	{
		return nullptr;
	}
	struct
	{
		USceneComponent* ReturnValue;
	} Parameters;
	Parameters.ReturnValue = nullptr;
	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}







bool ashootercharacter::is_alive() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsAlive"));

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

bool ashootercharacter::is_dead_and_settled() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsDeadAndSettled"));

	struct
	{
		bool Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

bool ashootercharacter::was_invisible() {
	return memory::read<bool>(class_ptr + offsets::was_invisible);
}

float ashootercharacter::health() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetHealth"));

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

float ashootercharacter::shield() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetShield"));

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}
//
//fvector uskeletalmeshcomponent::get_bone_location(int32_t index) {
//	fmatrix matrix;
//	reinterpret_cast<fmatrix* (__fastcall*)(uskeletalmeshcomponent*, fmatrix*, int)>(memory::module_base + offsets::bone_matrix)(this, &matrix, index);
//	return { matrix.wplane.x, matrix.wplane.y, matrix.wplane.z };
//}

fvector uskeletalmeshcomponent::get_bone_location(int32_t index) {
	FMatrix matrix;
	reinterpret_cast<FMatrix* (__fastcall*)(uskeletalmeshcomponent*, FMatrix*, int)>(memory::module_base + offsets::bone_matrix)(this, &matrix, index);

	return { matrix.WPlane.X, matrix.WPlane.Y, matrix.WPlane.Z };
}

uobject* uengine::font() {
	return memory::read<ugameinstance*>(class_ptr + offsets::font);
}

uengine* ugameinstance::get_uengine() {
	return memory::read<uengine*>(class_ptr + 0x28);
}

int32_t math::random_int(int32_t min, int32_t max) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.KismetMathLibrary.RandomIntegerInRange");

	struct
	{
		int32_t min;
		int32_t max;
		int32_t output;
	} params = { min, max };


	variables.math_system->process_event(function, &params);
	return params.output;
}

//fvector math::SmoothAim(fvector target, fvector delta_rotation, float smooth) {
//	fvector diff = target - delta_rotation;
//	normalize(diff);
//	return delta_rotation + diff / smooth;
//}

double math::distance_2d(fvector2d v1, fvector2d v2)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Distance2D"));

	struct
	{
		fvector2d v1;
		fvector2d v2;
		double output;
	} params;

	params.v1 = v1;
	params.v2 = v2;

	variables.math_system->process_event(function, &params);
	return params.output;
}

fvector math::find_look_at_rotation(fvector start, fvector end)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation"));

	struct
	{
		fvector start;
		fvector end;
		fvector output;
	} params;

	params.start = start;
	params.end = end;

	variables.math_system->process_event(function, &params);
	return params.output;
}

fvector aplayercameramanager::get_camera_location()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraLocation"));

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

fvector aplayercameramanager::get_camera_rotation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation"));

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

float aplayercameramanager::get_fov() {
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetFOVAngle"));

	if (function == nullptr)
		return {};

	struct
	{
		float return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

aplayercameramanager* aplayercontroller::get_camera_manager() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerCameraManager"));

	struct
	{
		aplayercameramanager* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


//uobject* uobject::static_load_object(uobject* Class, uobject* InOuter, const wchar_t* Name)
//{
//	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
//	auto StaticLoadObjectFN = reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool)>(StaticLoadObjectAddress);
//	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, 0x46C4660, (void*)StaticLoadObjectFN);
//}

uobject* uobject::static_load_object(uobject* Class, uobject* InOuter, const wchar_t* Name)
{
	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	auto StaticLoadObjectFN = reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool)>(StaticLoadObjectAddress);
	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, 0x46C4660, (void*)StaticLoadObjectFN);
}


void uskeletalmeshcomponent::set_materials(const tarray<fskeletalmaterial>& in_materials)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkeletalMesh.SetMaterials"));

	struct
	{
		tarray<fskeletalmaterial> in_materials;
	} params;

	params.in_materials = in_materials;

	this->process_event(function, &params);
}

void UPrimitiveComponent::set_material(int32_t element_index, uobject* material) {
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetMaterial");

	struct params_t {
		int32_t element_index;
		uobject* material;
	} params = { element_index, material };

	process_event(Function, &params);
}



int32_t UPrimitiveComponent::get_num_materials() {
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetNumMaterials");

	struct params_t {
		int32_t return_value;
	} params = {};

	process_event(Function, &params);
	return params.return_value;
}

e_blend_mode UMaterialInstanceDynamic::get_blend_mode() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInterface.GetBlendMode");

	struct params_t {
		e_blend_mode return_value;
	} params = {};

	process_event(function, &params);
	return params.return_value;
}


bool uskeletalmeshcomponent::AttachTo(uskeletalmeshcomponent* InParent, fname InSocketName, EAttachLocation AttachType, bool bWeldSimulatedBodies)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachTo");

	struct
	{
		uskeletalmeshcomponent* InParent;
		fname InSocketName;
		EAttachLocation AttachType;
		bool bWeldSimulatedBodies;
		bool ReturnValue;
	} params;

	params.InParent = InParent;
	params.InSocketName = InSocketName;
	params.AttachType = AttachType;
	params.bWeldSimulatedBodies = bWeldSimulatedBodies;

	this->process_event(function, &params);

	return params.ReturnValue;
}

//void uskeletalmeshcomponent::SetRelativeRotation(frotator& NewRotation)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeRotation");
//
//	struct
//	{
//		frotator NewRotation;
//	} params;
//
//	params.NewRotation = NewRotation;
//
//	this->process_event(function, &params);
//}



//void uskeletalmeshcomponent::SetRelativeLocation(fvector NewLocation)
//{
//	static uobject* function = nullptr;
//	if (function == nullptr)
//		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeLocation");
//	struct {
//		fvector NewLocation;
//	} params;
//	params.NewLocation = NewLocation;
//	this->process_event(function, &params);
//}

bool uskeletalmeshcomponent::AttachToComponent(USceneComponent* Parent, fname SocketName,
	EAttachmentRule LocationRule, EAttachmentRule RotationRule,
	EAttachmentRule ScaleRule, bool bWeldSimulatedBodies)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachToComponent");

	struct
	{
		USceneComponent* Parent;
		fname SocketName;
		EAttachmentRule LocationRule;
		EAttachmentRule RotationRule;
		EAttachmentRule ScaleRule;
		bool bWeldSimulatedBodies;
		bool ReturnValue;
	} params;

	params.Parent = Parent;
	params.SocketName = SocketName;
	params.LocationRule = LocationRule;
	params.RotationRule = RotationRule;
	params.ScaleRule = ScaleRule;
	params.bWeldSimulatedBodies = bWeldSimulatedBodies;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void uskeletalmeshcomponent::SetRelativeScale3D(fvector NewScale3D)
{
	static uobject* function = nullptr;

	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct {
		fvector NewScale3D;
	} params;

	params.NewScale3D = NewScale3D;

	this->process_event(function, &params);
}

void UProceduralMeshComponent::SetRelativeRotation1(void* Target, const frotator& Rotation, bool bSweep = false, bool bTeleport = true)
{
	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeRotation");
	if (!fn || !Target) return;

	struct
	{
		frotator NewRotation;  // ← CHANGÉ de FRotator à frotator
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewRotation = Rotation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(FHitResult));
	((uobject*)Target)->process_event(fn, &params);
}

void UProceduralMeshComponent::SetRelativeRotation2(frotator Target, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct
	{
		frotator NewRotation;
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewRotation = Target;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(FHitResult));

	if (fn)
		this->process_event(fn, &params);
}

void UProceduralMeshComponent::SetRelativeScale3D1(fvector NewScale3D)
{
	static uobject* function = nullptr;
	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct {
		fvector NewScale3D;
	} params;

	params.NewScale3D = NewScale3D;
	this->process_event(function, &params);
}

void USceneComponent::GetChildrenComponents(
	bool bIncludeAllDescendants,
	tarray<USceneComponent*>* OutChildren
)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(
			L"Engine.SceneComponent.GetChildrenComponents"
		);

	struct
	{
		bool bIncludeAllDescendants;
		tarray<USceneComponent*> Children;
	} params;

	params.bIncludeAllDescendants = bIncludeAllDescendants;

	this->process_event(function, &params);

	if (OutChildren)
		*OutChildren = params.Children;
}
bool UBlindManagerComponent::IsBlinded()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.IsBlinded");

	struct
	{
		bool ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

void UBlindManagerComponent::SetBlinded(bool bNewBlinded)
{
	uobject* function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.SetBlinded");

	if (!function)
		return;

	struct
	{
		bool bNewBlinded;
	} params = { bNewBlinded };

	this->process_event(function, &params);
}

void UBlindManagerComponent::ClientCleanseBlinds()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.ClientCleanseBlinds");

	struct
	{
	} params;

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_vector_parameter_value2(fname parameter_name, flinearcolor value) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");

	struct params_t {
		fname parameter_name;
		flinearcolor value;
	} params = { parameter_name, value };

	process_event(function, &params);
}


UMaterialInstanceDynamic* UPrimitiveComponent::get_material(int32_t element_index)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetMaterial");

	struct {
		int32_t element_index;
		UMaterialInstanceDynamic* return_value;
	} params = { element_index };

	this->process_event(function, &params);

	return params.return_value;
}

UMaterialInterface* uskeletalmeshcomponent::GetMaterial(int32_t ElementIndex) {

	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetMaterial").decrypt());
	if (!function) {
		return nullptr;
	}

	struct {
		int32_t ElementIndex;
		UMaterialInterface* ReturnValue;
	} Parameters;

	Parameters.ElementIndex = ElementIndex;
	Parameters.ReturnValue = nullptr;
	this->process_event(function, &Parameters);
	return Parameters.ReturnValue;
}

int32_t uskeletalmeshcomponent::get_num_materials() {
	static uobject* Function = nullptr;

	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetNumMaterials");

	struct params_t {
		int32_t return_value;
	} params = {};

	process_event(Function, &params);
	return params.return_value;
}

uobject* uskeletalmeshcomponent::create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
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

uskeletalmeshcomponent* ashootercharacter::GetCosmeticMesh3P()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ShooterCharacter.GetCosmeticMesh3P");

	struct
	{
		uskeletalmeshcomponent* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsZoomed()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ShooterCharacter.IsZoomed");

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}









void UMaterialInstanceDynamic::set_vector_parameter_value1(fname parameter_name, flinearcolor value) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");

	struct params_t {
		fname parameter_name;
		int shift;
		flinearcolor value;
	} params = { parameter_name, 0, value };

	process_event(function, &params);
}



void UMaterialInstanceDynamic::set_scalar_parameter_value2(fname parameter_name, float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		float value; // Changé de "double" à "float"
	} params = { parameter_name, value };

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_scalar_parameter_value(fname parameter_name, double value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		double value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_scalar_parameter_value1(fname parameter_name, double value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		double value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_texture_parameter_value(fname parameter_name, uobject* texture) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetTextureParameterValue");

	struct params_t {
		fname parameter_name;
		int shift;
		uobject* value;
	} params = { parameter_name, 0, texture };

	process_event(function, &params);
}


void aplayercontroller::GetInputMouseDelta(float& DeltaX, float& DeltaY) {
	static uobject* Function;
	if (!Function) Function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.GetInputMouseDelta"));
	struct
	{
		float DeltaX;
		float DeltaY;
	}Parameters;

	this->process_event(Function, &Parameters);
	DeltaX = Parameters.DeltaX;
	DeltaY = Parameters.DeltaY;
}

float aplayercontroller::GetMouseSensitivity()
{
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerController.GetMouseSensitivity"));
	struct {
		float Out;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.Out;
}

void ashootercharacter::K2_SetActorRelativeRotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport)
{
	uobject* Function = nullptr;
	if (!Function) Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation"));
	struct
	{
		fvector NewRelativeRotation;
		bool bSweep;
		bool bTeleport;
	}Parameters;
	Parameters.NewRelativeRotation = NewRelativeRotation;
	Parameters.bSweep = bSweep;
	Parameters.bTeleport = bTeleport;
	this->process_event(Function, &Parameters);
	return;
}

bool uskeletalmeshcomponent::set_actor_rotation(frotator new_rotation, bool teleport_physics) {

	static uobject* function;
	if (!function) function = uobject::find_object<uobject*>(crypt(L"Actor.K2_SetActorRotation"));
	struct {
		frotator new_rotation;
		bool teleport_physics;
		bool return_value;
	} params = { new_rotation, teleport_physics };


	this->process_event(function, &params);
	return params.return_value;
}

//void aplayercontroller::set_fov(float fov)
//{
//
//
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.SetFOV"));
//
//	struct {
//		float fov;
//	}Args;
//	Args.fov = fov;
//	function->process_event2(this, function, &Args);
//}


void aplayercontroller::set_fov(float fov)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object1(crypt(L"ShooterGame.AresPlayerController.SetFOV"));
	if (!function) return;

	struct {
		float fov;
	}Args;
	Args.fov = fov;
	this->process_event(function, &Args);
}


bool ashootercharacter::CanJump() {
    static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJump"));
    if (!Function) {
        return false;
    }
    struct {
        bool Out;
    } Parameters;

    this->process_event(Function, &Parameters);
    return Parameters.Out;
}

//bool ashootercharacter::CanJumpInternal() {
//    static uobject* Function = uobject::StaticFindObject(0, 0, L"Engine.Character.CanJumpInternal", false);
//    if (!Function) {
//        return false;
//    }
//    struct {
//        bool Out;
//    } Parameters;
//
//    this->process_event(Function, &Parameters);
//    return Parameters.Out;
//}

void ashootercharacter::Jump() {
    static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.Jump"));
    if (!Function) {
        return;
    }
    struct {

    } Parameters;

    this->process_event(Function, &Parameters);
}

EAresItemSlot currentequippable::get_item_slot() {
	uobject* function = uobject::find_object<uobject*>(L"ShooterGame.AresItem.GetItemSlot");

	if (!function || !memory::IsValidPointer((uintptr_t)function))
		return EAresItemSlot::EAresItemSlot_MAX;

	struct {
		EAresItemSlot output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

acknowledgedpawn* UDamageResponse::get_damage_causer() {
	uobject* function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetEventInstigatorPawn");

	struct {
		acknowledgedpawn* output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

currentequippable* UDamageResponse::get_equippable_used() {
	uobject* function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetEquippableUsed");

	struct {
		currentequippable* output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

void ashootercharacter::OnJump() {
    static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.OnJumped"));
    if (!Function) {
        return;
    }
    struct {

    } Parameters;

    this->process_event(Function, &Parameters);
}

void ashootercharacter::StopJumping() {
    static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.StopJumping"));
    if (!Function) {
        return;
    }
    struct {

    } Parameters;

    this->process_event(Function, &Parameters);
}

void ashootercharacter::get_firing_location_and_direction(fvector* loc, fvector* rot, bool apply_recoil)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));

	struct
	{
		fvector location;
		fvector rotation;
		bool apply_recoil;
	} params;

	params.apply_recoil = apply_recoil;

	this->process_event(function, &params);

	*loc = params.location;
	*rot = params.rotation;
}



void aplayercontroller::SimulateInputKey(fkey Key, bool bPressed) {
	
    static uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.SimulateInputKey"));
    if (!Function) {
        return;
    }
    struct {
        fkey Key;
        bool bPressed;
    } Parameters;
    Parameters.Key = Key;
    Parameters.bPressed = bPressed;
    this->process_event(Function, &Parameters);
}

acknowledgedpawn* aplayercontroller::get_acknowledged_pawn() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.K2_GetPawn"));

	struct
	{
		acknowledgedpawn* output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


currentequippable* inventorymanager::get_current_weapon() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable"));

	struct
	{
		currentequippable* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_data_asset* currentequippable::get_skin_data_asset() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetEquippableSkinDataAsset"));

	struct {
		equippable_skin_data_asset* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}


fvector2d ucanvas::get_screen_size() {
	return fvector2d(memory::read<int32_t>(class_ptr + 0x48), memory::read<int32_t>(class_ptr + 0x4c));
}

void ucanvas::k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawLine"));

	struct
	{
		fvector2d screenpos_a;
		fvector2d screenpos_b;
		float thickness;
		flinearcolor color;
	} params;

	params.screenpos_a = screenpos_a;
	params.screenpos_b = screenpos_b;
	params.thickness = thickness;
	params.color = color;

	this->process_event(function, &params);
}

void ucanvas::k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTexture"));

	struct {
		uobject* texture;
		fvector2d screen_position;
		fvector2d screen_size;
		fvector2d coordinate_position;
		fvector2d coordinate_size;
		flinearcolor render_color;
		e_blend_mode blend_mode;
		float rotation;
		fvector2d pivot_point;
	} params;
	params.texture = texture;
	params.screen_position = screen_position;
	params.screen_size = screen_size;
	params.coordinate_position = coordinate_position;
	params.coordinate_size = coordinate_size;
	params.render_color = render_color;
	params.blend_mode = blend_mode;
	params.rotation = rotation;
	params.pivot_point = pivot_point;

	this->process_event(function, &params);
}




void ucanvas::k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawText"));

	struct
	{
		uobject* font;
		fstring text;
		fvector2d screenposition;
		fvector2d scale;
		flinearcolor color;
		float kerning;
		flinearcolor shadowcolor;
		fvector2d shadowoffset;
		bool centrex;
		bool centrey;
		bool outline;
		flinearcolor outlinecolor;
	} params;

	params.font = font;
	params.text = text;
	params.screenposition = screenposition;
	params.scale = scale;
	params.color = color;
	params.kerning = kerning;
	params.shadowcolor = shadowcolor;
	params.shadowoffset = shadowoffset;
	params.centrex = centrex;
	params.centrey = centrey;
	params.outline = outline;
	params.outlinecolor = outlinecolor;

	this->process_event(function, &params);
}

ares_client_game_instace* ares_instance::get_ares_client_game_instance(uobject* world_context) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetAresClientGameInstance"));

	struct {
		uobject* uworld;
		ares_client_game_instace* return_value;
	} params = { world_context };

	variables.ares_instance->process_event(function, &params);

	return params.return_value;
}

inventorymanager* ares_client_game_instace::get_inventory_manager() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetInventoryManager"));

	struct {
		inventorymanager* out;
	} result;


	this->process_event(function, &result);
	return result.out;
}

arsenal_view_controller* ares_client_game_instace::get_aresnal_view_controller() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetArsenalViewController"));

	struct {
		arsenal_view_controller* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_inventory_model* equippable_inventory_model::get_equipped_skin_model() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedSkin"));

	struct {
		equippable_skin_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;

}

equippable_charm_instance_inventory_model* equippable_inventory_model::get_equipped_charm_instance() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedCharmInstance"));

	struct {
		equippable_charm_instance_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

tarray<equippable_inventory_model*> arsenal_view_model::get_gun_models() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewModel.GetGunModels"));

	struct {
		tarray<equippable_inventory_model*> out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

arsenal_view_model* arsenal_view_controller::get_view_model() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.GetViewModel"));

	struct {
		arsenal_view_model* out;
	} params;
	this->process_event(function, &params);
	return params.out;
}

equippable_skin_chroma_inventory_model* equippable_skin_inventory_model::get_skin_inventory_chroma_asset() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableSkinInventoryModel.GetEquippedChroma"));

	struct {
		equippable_skin_chroma_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void ares_outline::setoutlinemode(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));
	if (!Function)
	{
		return;
	}
	struct {
		uworld* WorldContextObject;
		flinearcolor AllyColor;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.AllyColor = AllyColor;
	Parameters.EnemyColor = EnemyColor;
	variables.ares_outline_rendering->process_event(Function, &Parameters);
}

void ares_outline::setoutlinemode1(uworld* WorldContextObject, flinearcolor EnemyColor)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));
	if (!Function)
	{
		return;
	}
	struct {
		uworld* WorldContextObject;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.EnemyColor = EnemyColor;
	variables.ares_outline_rendering->process_event(Function, &Parameters);
}

void umaterial_instance::set_vector_parameter_value(fname ParameterName, flinearcolor Value) {
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInstanceDynamic.SetVectorParameterValue"));

	struct
	{
		fname ParameterName;
		flinearcolor Value;
	} params;

	params.ParameterName = ParameterName;
	params.Value = Value;

	this->process_event(Function, &params);
}



void ashootercharacter::reset_character_materials_internal(uskeletalmeshcomponent* mesh_to_reset)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ShooterCharacter.ResetCharacterMaterials");

	if (!function) return;

	struct {
		uskeletalmeshcomponent* mesh_to_reset;
	} params;

	params.mesh_to_reset = mesh_to_reset;

	this->process_event(function, &params);
}


void UMaterialInstanceDynamic::set_vector_parameter_value(fname parameter_name, flinearcolor value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");

	struct {
		fname parameter_name;
		flinearcolor value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}
//namespace skin_changer_utils {
//	equippable_inventory_model* get_arsenal_gun_models(uobject* uworld, int type_index) {
//		if (aplayercontroller* player_controller = blueprints::get_local_controller(uworld))
//			if (ares_client_game_instace* ares = ares_instance::get_ares_client_game_instance(uworld))
//				if (arsenal_view_controller* arsenal_view_controller = ares->get_aresnal_view_controller())
//					if (arsenal_view_model* arsenal_view_model = arsenal_view_controller->get_view_model())
//					{
//						auto models = arsenal_view_model->get_gun_models();
//						for (int i = 0; i < models.size(); i++)
//						{
//							auto model = models[i];
//
//							if (equippable_skin_data_asset* skin_data = model->get_equipped_skin_model()->get_skin_data_asset())
//								if (equippable_skin_data_asset::type type = skin_data->get_type(); type.is_valid())
//									if (type.index == type_index)
//										return model;
//						}
//					}
//		return nullptr;
//	}
//}

template<class k, class e>
class tmap
{
public:
	k Key;
	e Element;
	char __pad0x[0x8];
};

bool basecomponent::is_ally(ashootercharacter* enemy, ashootercharacter* self) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.BaseTeamComponent.IsAlly"));
	if (!function) return false;

	if (!variables.base_component || !memory::IsValidPointer((uintptr_t)variables.base_component))
		return false;

	struct {
		ashootercharacter* enemy;
		ashootercharacter* self;
		bool return_value;
	} params;

	
	params.enemy = enemy;
	params.self = self;
	params.return_value = false;

	variables.base_component->process_event(function, &params);
	return params.return_value;
}






void skin_changer::unlock_all_skins(uobject* world) {
	// Throttle: 5 saniyede bir çalıştır
	static DWORD last_unlock_tick = 0;
	DWORD now = GetTickCount();
	if (now - last_unlock_tick < 5000) return;
	last_unlock_tick = now;

	if (inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager()) {
		tarray<uobject*> equippable_models = memory::read<tarray<uobject*>>(std::uintptr_t(manager) + 0xe8);

		if (globals::misc::sk1n_chang3r) {
			for (int32_t i = 0; i < equippable_models.size(); i++) {
				if (auto model = equippable_models[i]) {
					tarray<uobject*> skins = memory::read<tarray<uobject*>>(std::uintptr_t(model) + 0x150);

					if (skins.size() > 0) {
						for (int32_t a = 0; a < skins.size(); a++) {
							if (auto skin = skins[a]) {

								tarray<uobject*> possible_levels = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x138);
								for (int a = 0; a < possible_levels.size(); a++)
									if (uobject* xyz = possible_levels[a])
										memory::write<bool>(std::uintptr_t(xyz) + 0xfe, true),
										memory::write<bool>(std::uintptr_t(xyz) + 0xf2, true);


								tarray<uobject*> possible_chromas = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x128);
								for (int a = 0; a < possible_chromas.size(); a++)
									if (uobject* xyz = possible_chromas[a])
										memory::write<bool>(std::uintptr_t(xyz) + 0xfe, true),
										memory::write<bool>(std::uintptr_t(xyz) + 0xf2, true);


								memory::write<bool>(std::uintptr_t(skin) + 0xfe, true);
								memory::write<bool>(std::uintptr_t(skin) + 0xf2, true);

							}
						}
					}
				}
			}
		}
	}
}






void skin_changer::unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset) {
	

	auto ares_client_game_instance = ares_instance::get_ares_client_game_instance(world);
	auto a1 = memory::read<uintptr_t>((uintptr_t)ares_client_game_instance + offsets::skin_pointer);

	if (a1) {
		a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
		if (a1) {
			auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
			memory::write<int>(a1 + offsets::skin_pointer_3, 2);

		
			SPOOF_CALL(content_library::clear_weapon_components)(current_equippable);

	
			if (globals::buddy::enabled) {
				
				inventorymanager* manager = (ares_instance::get_ares_client_game_instance)(world)->get_inventory_manager();
				auto charm_instances = memory::read<tarray<tmap<uobject*, uobject*>>>(std::uintptr_t(manager) + 0x430);

				
				uobject* selected_buddy = charm_instances[globals::buddy::index].Key;

			
				SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, selected_buddy, 1);
			}
			else {
	
				if (skin_charm_data_asset != nullptr) {
					SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, skin_charm_data_asset, skin_charm_level_data_asset);
				}
				else {
			
					SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
				}
			}
			memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
		}
	}
}



bool string_utils::contains(fstring SearchIn, fstring Substring, bool bUseCase, bool bSearchFromEnd) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains"));

	struct {
		fstring SearchIn;
		fstring Substring;
		bool bUseCase;
		bool bSearchFromEnd;
		bool ReturnValue;
	}params;
	params.SearchIn = SearchIn;
	params.Substring = Substring;
	params.bUseCase = bUseCase;
	params.bSearchFromEnd = bSearchFromEnd;

	variables.kismet_string->process_event(function, &params);

	return params.ReturnValue;
}

fstring string_utils::int_to_string(const int value) {
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_IntToString"));

	if (function == nullptr)
		return {};

	struct
	{
		int value;
		fstring return_value;
	} params;

	params.value = value;

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}

EAresItemSlot currentequippable::GetItemSlot()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresItem.GetItemSlot");

	struct
	{
		EAresItemSlot ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}



fvector AGameObject::GetObjectLocation()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation"));

	struct {
		fvector Out;
	} Args;

	this->process_event(function, &Args);
	return Args.Out;
}

float AGameObject::GetObjectHealth()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject.GetHealth"));

	struct {
		float Out;
	} Args;

	this->process_event(function, &Args);
	return Args.Out;
}


uobject* Class::ShooterGameObject()
{
	return  uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject"));
}

uobject* GameplayStatics::GameplayStatics()
{
	return  uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics"));
}

UThreadedChatManager* UThreadedChatManager::GetThreadedChatManager(uobject* world_context) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.GetThreadedChatManager");

	if (!function)
		return nullptr;

	struct {
		uobject* world_context;
		UThreadedChatManager* return_value;
	} params{};

	params.world_context = world_context;

	uobject* obj = GetDefaultObj();
	if (!obj)
		return nullptr;

	obj->process_event(function, &params);

	return params.return_value;
}

void UThreadedChatManager::SendChatMessageV2(EChatRoomType room_type, ftext message) {
	if (!message.data)
		return;

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.SendChatMessageV2");

	if (!function)
		return;

	struct {
		uint8_t room_type;
		char pad[7];
		ftext message;
	} params{};

	params.room_type = (uint8_t)room_type;
	params.message = message;

	this->process_event(function, &params);
}

fvector ashootercharacter::get_velocity()
{
	auto root_comp = this->K2_GetRootComponent();
	if (!root_comp) return fvector(0.f, 0.f, 0.f);
	
	return memory::read<fvector>((uintptr_t)root_comp + 0x0170); // USceneComponent::ComponentVelocity
}
