#include "pch.h"
#include "Hooks.h"

typedef void(__stdcall* FunctionType)();

FunctionType WriteLevelOrigin = nullptr;
uintptr_t WriteLevelOriginReturnAddr;
uintptr_t levelAddr; 
__declspec(naked) void __stdcall Hooks::WriteLevelHook() {
	_asm {
		pushfd
		push edi
		mov edi,esp
		add edi,0x18
		mov edi,[edi]
		cmp edi,levelAddr
		jne not_writing_level
		pushad
		pushfd
		push esi
		call GameHandler::OnWriteLevel 
		pop esi
		popfd
		popad 
	not_writing_level :
		pop edi
		popfd
		test esi,0x3
		jmp dword ptr[WriteLevelOriginReturnAddr]
	}
}

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
		pop esi
		pop edi
		pop ebx
		test eax,eax
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
uintptr_t CompleteMissionSkipOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::CompleteMissionHook() {
	_asm {
		pushfd;
		pushad;
		mov ebp,[esp+0x28]
		cmp ebp, 1;
		je we_need_to_check_this_one;
		cmp ebp, 3;
		jne normal_restore;
	we_need_to_check_this_one:
		push ecx;
		call GameHandler::CanActivateMission;
		cmp eax,1;
		je normal_restore;
		popad;
		popfd;
		jmp dword ptr[CompleteMissionSkipOriginReturnAddr];
	normal_restore:
		push ebp;
		push ecx;
		call CheckHandler::OnCompleteMission;
		pop ecx;
		pop ebp;
		popad;
		popfd;
		sub esp, 0x14;
		push ebx;
		push ebp;
		jmp dword ptr[CompleteMissionOriginReturnAddr];
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

FunctionType GetShadowPieceOrigin = nullptr;
uintptr_t GetShadowPieceOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::GetShadowPieceHook() {
	_asm {
		pushad
		pushfd
		push esi
		call CheckHandler::OnGetShadowPiece
		pop esi
		popfd
		popad
		mov [esi+0x108],7
		jmp dword ptr[GetShadowPieceOriginReturnAddr]
	}
}

FunctionType SelectBunyipOrigin = nullptr;
uintptr_t SelectBunyipOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::SelectBunyipHook() {
	_asm {
		pushad
		pushfd
		push edi
		call GameHandler::OnSelectBunyip
		pop edi
		popfd
		popad
		push [edi+0x504]
		jmp dword ptr[SelectBunyipOriginReturnAddr]
	}
}

FunctionType LoadSaveFileOrigin = nullptr;
uintptr_t LoadSaveFileOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::LoadSaveFileHook() {
	_asm {
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
		add esp, 0xC
		jmp dword ptr[SaveFileOriginReturnAddr]
	}
}

FunctionType ChunkLoadedOrigin = nullptr;
uintptr_t ChunkLoadedOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::ChunkLoadedHook() {
	_asm {
		pushfd
		pushad
		call GameHandler::OnChunkLoaded
		popad
		popfd
		pop esi
		pop edi
		add esp,0x48
		jmp dword ptr[ChunkLoadedOriginReturnAddr]
	}
}

FunctionType ChunkQueuedOrigin = nullptr;
uintptr_t ChunkQueuedOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::ChunkQueuedHook() {
	_asm {
		pushfd
		pushad
		mov edi, esp
		add edi,0x24
		mov edi,[edi]
		mov edi,[edi]
		push edi
		call GameHandler::OnChunkQueued
		pop edi   
		popad
		popfd
		mov al,01
		pop esi
		pop edi
		pop ebx
		jmp dword ptr[ChunkQueuedOriginReturnAddr]
	}
}

FunctionType ChunkQueuedWithoutQueuerOrigin = nullptr;
uintptr_t ChunkQueuedWithoutQueuerOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::ChunkQueuedWithoutQueuerHook() {
	_asm {
		add esp,0x10
		pushfd
		pushad
		push esi
		call GameHandler::OnChunkQueuedWithoutQueuer
		pop esi
		popad
		popfd
		mov al, 01
		jmp dword ptr[ChunkQueuedWithoutQueuerOriginReturnAddr]
	}
}

FunctionType FindItemOrigin = nullptr;
uintptr_t FindItemOriginReturnAddr;
__declspec(naked) void __stdcall Hooks::FindItemHook() {
	_asm {
		call dword ptr[eax+0x64]
		pushfd
		pushad
		push eax
		call CheckHandler::OnFindItem
		pop eax
		popad
		popfd
		jmp dword ptr[FindItemOriginReturnAddr]
	}
}



void Hooks::SetupHooks() {
	char* addr;

	GameLoadedOriginReturnAddr = Core::moduleBase + 0x1fa4e1 + 5;
	addr = (char*)(Core::moduleBase + 0x1fa4e1);
	MH_CreateHook((LPVOID)addr, &GameLoadedHook, reinterpret_cast<LPVOID*>(&GameLoadedOrigin));

	MenuLoadedOriginReturnAddr = Core::moduleBase + 0x21A8EB;
	addr = (char*)(Core::moduleBase + 0x21A8E6);
	MH_CreateHook((LPVOID)addr, &MenuLoadedHook, reinterpret_cast<LPVOID*>(&MenuLoadedOrigin));

	CollectCollectibleOriginReturnAddr = Core::moduleBase + 0x11179a + 5;
	addr = (char*)(Core::moduleBase + 0x11179a);
	MH_CreateHook((LPVOID)addr, &CollectCollectibleHook, reinterpret_cast<LPVOID*>(&CollectCollectibleOrigin));

	FindItemOriginReturnAddr = Core::moduleBase + 0x18bc56;
	addr = (char*)(Core::moduleBase + 0x18bc50);
	MH_CreateHook((LPVOID)addr, &FindItemHook, reinterpret_cast<LPVOID*>(&FindItemOrigin));

	CompleteMissionOriginReturnAddr = Core::moduleBase + 0x1143b0 + 5;
	CompleteMissionSkipOriginReturnAddr = Core::moduleBase + 0x114657;
	addr = (char*)(Core::moduleBase + 0x1143b0);
	MH_CreateHook((LPVOID)addr, &CompleteMissionHook, reinterpret_cast<LPVOID*>(&CompleteMissionOrigin));

	PurchaseItemOriginReturnAddr = Core::moduleBase + 0x1db792 + 5;
	addr = (char*)(Core::moduleBase + 0x1db792);
	MH_CreateHook((LPVOID)addr, &PurchaseItemHook, reinterpret_cast<LPVOID*>(&PurchaseItemOrigin));

	LoadSaveFileOriginReturnAddr = Core::moduleBase + 0x3470bf + 5;
	addr = (char*)(Core::moduleBase + 0x3470bf);
	MH_CreateHook((LPVOID)addr, &LoadSaveFileHook, reinterpret_cast<LPVOID*>(&LoadSaveFileOrigin));

	RecalcSaveDataSize1OriginReturnAddr = Core::moduleBase + 0x2535b6 + 7;
	addr = (char*)(Core::moduleBase + 0x2535b6);
	MH_CreateHook((LPVOID)addr, &RecalcSaveDataSize1Hook, reinterpret_cast<LPVOID*>(&RecalcSaveDataSize1Origin));

	RecalcSaveDataSize2OriginReturnAddr = Core::moduleBase + 0x211de3 + 7;
	addr = (char*)(Core::moduleBase + 0x211de3);
	MH_CreateHook((LPVOID)addr, &RecalcSaveDataSize2Hook, reinterpret_cast<LPVOID*>(&RecalcSaveDataSize2Origin));

	SaveFileOriginReturnAddr = Core::moduleBase + 0x346fca + 5;
	addr = (char*)(Core::moduleBase + 0x346fca);
	MH_CreateHook((LPVOID)addr, &SaveFileHook, reinterpret_cast<LPVOID*>(&SaveFileOrigin));

	ChunkLoadedOriginReturnAddr = Core::moduleBase + 0x18DBCA + 5;
	addr = (char*)(Core::moduleBase + 0x18DBCA);
	MH_CreateHook((LPVOID)addr, &ChunkLoadedHook, reinterpret_cast<LPVOID*>(&ChunkLoadedOrigin));

	ChunkQueuedOriginReturnAddr = Core::moduleBase + 0x11ab4b + 5;
	addr = (char*)(Core::moduleBase + 0x11ab4b);
	MH_CreateHook((LPVOID)addr, &ChunkQueuedHook, reinterpret_cast<LPVOID*>(&ChunkQueuedOrigin));
	// esp + 4 contains current chunk
	// esp + 24 contains connecting chunk

	ChunkQueuedWithoutQueuerOriginReturnAddr = Core::moduleBase + 0x11aae7 + 5;
	addr = (char*)(Core::moduleBase + 0x11aae7);
	MH_CreateHook((LPVOID)addr, &ChunkQueuedWithoutQueuerHook, reinterpret_cast<LPVOID*>(&ChunkQueuedWithoutQueuerOrigin));

	addr = (char*)(Core::moduleBase + 0x1608C0);
	MH_CreateHook((LPVOID)addr, &GameHandler::OnDeath, reinterpret_cast<void**>(&GameHandler::stateTransitionFunc));

	addr = (char*)(Core::moduleBase + 0x313940);
	MH_CreateHook((LPVOID)addr, &ShopHandler::OnGetString, reinterpret_cast<void**>(&ShopHandler::getStringFunc));

	GetShadowPieceOriginReturnAddr = Core::moduleBase + 0x18a827;
	addr = (char*)(Core::moduleBase + 0x18a81d);
	MH_CreateHook((LPVOID)addr, &Hooks::GetShadowPieceHook, reinterpret_cast<void**>(&GetShadowPieceOrigin));

	SelectBunyipOriginReturnAddr = Core::moduleBase + 0x391bbb;
	addr = (char*)(Core::moduleBase + 0x391bb5);
	MH_CreateHook((LPVOID)addr, &Hooks::SelectBunyipHook, reinterpret_cast<void**>(&SelectBunyipOrigin));

	WriteLevelOriginReturnAddr = Core::moduleBase + 0x3bfb4b;
	levelAddr = Core::moduleBase + 0xEB9C90;
	addr = (char*)(Core::moduleBase + 0x3bfb45);
	MH_CreateHook((LPVOID)addr, &Hooks::WriteLevelHook, reinterpret_cast<void**>(&WriteLevelOrigin));

	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x3470A5), 26);
	GameHandler::SetToJmp((uintptr_t*)(Core::moduleBase + 0x3470E8));
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x347109), 6);
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x34780C), 28);

	// Prevent collectible increment
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x1117bd), 6);

	// Prevent purchase increment
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x1db797), 3);

	// Prevent found item increment
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x18bc53), 3);
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x139FF6), 3);
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x13A006), 4);

	// Prevent ever adding to the spent count of non-opal currencies
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x1db72d), 6);
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x1db77d), 6);
	GameHandler::SetToNoOperation((uintptr_t*)(Core::moduleBase + 0x1db6cf), 6);
}