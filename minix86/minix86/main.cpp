#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <mini/x86/inst.h>
#include <mini/memory.h>
using namespace mini;

float float_func(float asd) {
	float ebin = asd * 2.0f;
	return ebin - asd;
}

int main(int argc, char** argv) {

	/*x86::inst_byte b[8];
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
	*/
	exec_ptr pt = exec_alloc(32);
	unsigned int val = 0, *vp = &val;
	
	float a = 2.0f, b = 2.0f, d;
	float *ap = &a, *bbp = &b, *dp = &d;

	float_func(a);

	pt[ 0] = Bin(11110011); // single prefix
	pt[ 1] = Bin(00001111); // opcode prefix
	pt[ 2] = Bin(00010000); // movss
	pt[ 3] = x86::make_mrm(x86::MOD_POINTER, x86::REG_XMM0, x86::REG_EAX); // xmm0, [eax]
	pt[ 4] = Bin(11110011); // single prefix
	pt[ 5] = Bin(00001111); // opcode prefix
	pt[ 6] = Bin(01011001); // mulss
	pt[ 7] = x86::make_mrm(x86::MOD_POINTER, x86::REG_XMM0, x86::REG_EBX);; // xmm0, [ebx]
	pt[ 8] = Bin(11110011); // single prefix
	pt[ 9] = Bin(00001111); // opcode prefix
	pt[10] = Bin(00010001); // movss (inv)
	pt[11] = x86::make_mrm(x86::MOD_POINTER, x86::REG_XMM0, x86::REG_ECX); // xmm0, [ecx]
	pt[12] = 0xC3; // ret
	
	char buf[2048], *bptr = buf;

	for (auto ptr = pt, end = ptr + 12; ptr != end; ptr++) {
		bptr += sprintf(bptr, "%02x ", *ptr);
	}

__asm {
	pushad
	mov eax, ap
	mov ebx, bbp
	mov ecx, dp
	call pt
	popad
}
	
	printf("%f\n", d);

	/*for (auto c : b) {
		printf("%02x ", c);
	}*/

	exec_free(pt);

	getchar();

}
