
void test(){}

int main(int arcg, char *argv[]){
	asm("mov eax, 0x1\n"
	    "mov ebx, 0x0\n"
	    "int 0x80");
}
