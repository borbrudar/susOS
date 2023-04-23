int main(){
	// create a pointer to video memory
	char *video_memory = (char*) 0xb8000;
	*video_memory = 'X'; //set it to X
}
