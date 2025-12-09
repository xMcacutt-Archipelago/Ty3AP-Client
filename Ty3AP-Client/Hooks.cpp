#include "pch.h"
#include "Hooks.h"

typedef void(__stdcall* FunctionType)();

FunctionType GameLoadedOrigin = nullptr;
uintptr_t GameLoadedOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::GameLoadedHook() {
	_asm {
		pushad
		pushfd
		call GameHandler::OnGameLoaded
		popfd
		popad
		mov byte ptr[edx + ecx + 0x44], 1
		jmp dword ptr[GameLoadedOriginReturnAddr]
	}
}

FunctionType MenuLoadedOrigin = nullptr;
uintptr_t MenuLoadedOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::MenuLoadedHook() {
	_asm {
		pushad
		pushfd
		call GameHandler::OnMenuLoaded
		popfd
		popad
		mov byte ptr[edx + ecx + 0x44], 1
		jmp dword ptr[MenuLoadedOriginReturnAddr]
	}
}

FunctionType CollectCollectibleOrigin = nullptr;
uintptr_t CollectCollectibleOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::CollectCollectibleHook() {
	_asm {
		push ebx
		push edx
		push edi
		push eax
		push ecx
		push esi
		call CheckHandler::OnCollectCollectible
		pop esi
		pop ecx
		pop eax
		pop edi
		pop edx
		pop ebx
		lea edi, [edx + eax * 0x4]
		mov eax, ecx
		jmp dword ptr[CollectCollectibleOriginReturnAddr]
	}
}

FunctionType CompleteMissionOrigin = nullptr;
uintptr_t CompleteMissionOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::CompleteMissionHook() {
	_asm {
		pushfd
		pushad
		push edx
		push eax
		call CheckHandler::OnCompleteMission
		pop eax
		pop edx
		popad
		popfd
		sub esp,14
		push ebx
		push ebp
		jmp dword ptr[CompleteMissionOriginReturnAddr]
	}
}

FunctionType PurchaseItemOrigin = nullptr;
uintptr_t PurchaseItemOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::PurchaseItemHook() {
	_asm {
		push ebx
		push edi
		push esi
		push edx
		push ecx
		push eax
		call CheckHandler::OnBuyItem
		pop eax
		pop ecx
		pop edx
		pop esi
		pop edi
		pop ebx
		push 0x314
		jmp dword ptr[PurchaseItemOriginReturnAddr]
	}
}

FunctionType LoadSaveFileOrigin = nullptr;
uintptr_t LoadSaveFileOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::LoadSaveFileHook() {
	_asm {
		add esp, 0x8
		call SaveDataHandler::LoadAPSaveFile

		mov eax, SaveDataHandler::saveFileLength
		mov[edi + 0x68], eax

		sub eax, 0xc
		mov[edi + 0x70], eax

		mov esi, SaveDataHandler::saveFileBuffer       // Source (loaded file)
		mov edi, [edi + 0x6C]                          // Destination (preallocated buffer)
		mov ecx, SaveDataHandler::saveFileLength
		rep movsb
		jmp dword ptr[LoadSaveFileOriginReturnAddr]
	}
}

FunctionType RecalcSaveDataSize1Origin = nullptr;
uintptr_t RecalcSaveDataSize1OriginReturnAddr;
__declspec(naked) void __stdcall Hooks::RecalcSaveDataSize1Hook() {
	_asm {
		call SaveDataHandler::RecalcSaveDataSize
		jmp dword ptr[RecalcSaveDataSize1OriginReturnAddr]
	}
}

FunctionType RecalcSaveDataSize2Origin = nullptr;
uintptr_t RecalcSaveDataSize2OriginReturnAddr;
__declspec(naked) void __stdcall Hooks::RecalcSaveDataSize2Hook() {
	_asm {
		call SaveDataHandler::RecalcSaveDataSize
		jmp dword ptr[RecalcSaveDataSize2OriginReturnAddr]
	}
}

FunctionType SaveFileOrigin = nullptr;
uintptr_t SaveFileOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::SaveFileHook() {
	_asm {
		call SaveDataHandler::SaveFile
		//add esp, 0xC
		jmp dword ptr[SaveFileOriginReturnAddr]
	}
}

void Hooks::SetupHooks() {
	char* addr;

	GameLoadedOriginReturnAddr = Core::moduleBase + 0x234492 + 7;
	addr = (char*)(Core::moduleBase + 0x234492);
	MH_CreateHook((LPVOID)addr, &GameLoadedHook, reinterpret_cast<LPVOID*>(&GameLoadedOrigin));

	MenuLoadedOriginReturnAddr = Core::moduleBase + 0x21A8EB;
	auto addr = (char*)(Core::moduleBase + 0x21A8E6);
	MH_CreateHook((LPVOID)addr, &MenuLoadedHook, reinterpret_cast<LPVOID*>(&MenuLoadedOrigin));

	CollectCollectibleOriginReturnAddr = Core::moduleBase + 0x11179a + 5;
	auto addr = (char*)(Core::moduleBase + 0x11179a);
	MH_CreateHook((LPVOID)addr, &CollectCollectibleHook, reinterpret_cast<LPVOID*>(&CollectCollectibleOrigin));

	CompleteMissionOriginReturnAddr = Core::moduleBase + 0x1143b0 + 5;
	auto addr = (char*)(Core::moduleBase + 0x1143b0);
	MH_CreateHook((LPVOID)addr, &CompleteMissionHook, reinterpret_cast<LPVOID*>(&CompleteMissionOrigin));

	PurchaseItemOriginReturnAddr = Core::moduleBase + 0x1db792 + 5;
	auto addr = (char*)(Core::moduleBase + 0x1db792);
	MH_CreateHook((LPVOID)addr, &PurchaseItemHook, reinterpret_cast<LPVOID*>(&PurchaseItemOrigin));

	LoadSaveFileOriginReturnAddr = Core::moduleBase + 0x3470bf + 5;
	auto loadaddr = (char*)(Core::moduleBase + 0x3470bf);
	MH_CreateHook((LPVOID)loadaddr, &LoadSaveFileHook, reinterpret_cast<LPVOID*>(&LoadSaveFileOrigin));

	RecalcSaveDataSize1OriginReturnAddr = Core::moduleBase + 0x2535b6 + 7;
	auto size1addr = (char*)(Core::moduleBase + 0x2535b6);
	MH_CreateHook((LPVOID)size1addr, &RecalcSaveDataSize1Hook, reinterpret_cast<LPVOID*>(&RecalcSaveDataSize1Origin));

	RecalcSaveDataSize2OriginReturnAddr = Core::moduleBase + 0x211de3 + 7;
	auto size2addr = (char*)(Core::moduleBase + 0x211de3);
	MH_CreateHook((LPVOID)size2addr, &RecalcSaveDataSize2Hook, reinterpret_cast<LPVOID*>(&RecalcSaveDataSize2Origin));

	SaveFileOriginReturnAddr = Core::moduleBase + 0x347557 + 5;
	auto saveaddr = (char*)(Core::moduleBase + 0x347557);
	MH_CreateHook((LPVOID)saveaddr, &SaveFileHook, reinterpret_cast<LPVOID*>(&SaveFileOrigin));

	GameHandler::SetToNoOperation((void*)(Core::moduleBase + 0x3470A5), 24);
	GameHandler::SetToJmp((void*)(Core::moduleBase + 0x3470E8));
	GameHandler::SetToNoOperation((void*)(Core::moduleBase + 0x347109), 6);
	GameHandler::SetToNoOperation((void*)(Core::moduleBase + 0x347817), 17);

	GameHandler::SetToNoOperation((void*)(Core::moduleBase + 0x1117bd), 6);
}