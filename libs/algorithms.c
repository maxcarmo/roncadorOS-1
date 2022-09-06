


unsigned int str_len(char *string){
	unsigned int counter = 0;
	while (*(string++)) counter++;
	return counter;
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}