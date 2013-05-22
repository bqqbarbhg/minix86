#include <cstdio>
#include <mini/x86/inst.h>
#include <mini/memory.h>
using namespace mini;
int main(int argc, char** argv) {
	
	x86::inst_byte b[8];
	exec_ptr pt = exec_alloc(32);

	x86::inst_simple inst;
	inst.op = 0;
	inst.size = x86::OPSIZE_32;
	inst.op = 0xC3;

	x86::inst_bin instmov;
	instmov.op = 0x88;
	instmov.size = x86::OPSIZE_32;
	instmov.addrmode = x86::ADDRMODE_PTR;
	instmov.dst = x86::REG32_EAX;
	instmov.disp = 0;
	instmov.src = x86::REG32_EBX;

	x86::write(pt, instmov);
	x86::write(pt + 2, inst);

	unsigned int val = 0, *vp = &val;

	__asm {
		pushad
		mov eax, vp
		mov ebx, 1234
		call pt
		popad
	}

	printf("%d\n", val);

	/*for (auto c : b) {
		printf("%02x ", c);
	}*/

	exec_free(pt);

	getchar();
	
}
