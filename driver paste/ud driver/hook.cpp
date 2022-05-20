#include "hook.h"

bool nullhook::call_kernel_function(void* kernel_function_address)
{
	if (!kernel_function_address)
		return false;
	
	PVOID* function = reinterpret_cast<PVOID*>(get_system_module_export("SystemRoot\\System32\\drivers\\dxkrnl.sys"));

	if (!function)
		return false;

	BYTE orig[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
	BYTE shell_code[] = { 0x48, 0x88 };  // mov rax, xxx change this to keep your drivers ud 
	BYTE shell_code_end[] = { 0xFF, 0xE0 };  // jmp rax

	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)(ULONG_PTR)orig, &shell_code, sizeof(shell_code));
	uintptr_t hook_address = reinterpret_cast<uintptr_t>(kernel_function_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	write_to_read_only_memory(function, &orig, sizeof(orig));

	return true;
}

NTSTATUS nullhook::hook_handler(PVOID called_param)
{
	return STATUS_SUCCESS;
}