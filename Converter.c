#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void cleanup();
void read_file_to_buffer(FILE *f);
void find_line(char Line[]);
void segment_array(char Line[]);
int find_base(char b[]);
void toBin(char num[], int b1, int b2);
void toB2(int number, int b2);
void print_Result(char n[], int b2);

char *buffer = NULL;

int main(int argc, char *argv[]) {

	int i;
	char Line[100];

	atexit(cleanup);

	for(i = 0; i < argc - 1; i++) {
		FILE *f = NULL;

		f = fopen(argv[i + 1], "rb");
		if(f == NULL) {
			fprintf(stderr, "Could not open %s\n", argv[i + 1]);
			continue;
		}
		i = 0;

		read_file_to_buffer(f);
        while(*buffer != '\0'){
            find_line(Line);
            if (Line[0] != '#' && Line[0] != '-'){
                segment_array(Line);
            }
        }
		fclose(f);
		free(buffer);
		buffer = NULL;
	}

	exit(EXIT_SUCCESS);
}


void cleanup() {
	return;
}


void read_file_to_buffer(FILE *f) {
	long file_size = 0;

	if(buffer != NULL) {
		fprintf(stderr, "Buffer in use\n");
		exit(EXIT_FAILURE);
	}

	rewind(f);
	if(fseek(f, 0, SEEK_END) != 0) {
		perror("Couldn't seek to end of file");
		exit(EXIT_FAILURE);
	}

	file_size = ftell(f);
	if(file_size < 0) {
		perror("Couldn't tell size");
		exit(EXIT_FAILURE);
	}
	rewind(f);

	buffer = (char *)malloc(sizeof(char) * (file_size + 1));
	if(buffer == NULL) {
		fprintf(stderr, "Could not allocate buffer\n");
		exit(EXIT_FAILURE);
	}

	if(fread(buffer, sizeof(char), (size_t)file_size, f) != file_size) {
		fprintf(stderr, "Couldn't read file\n");
		exit(EXIT_FAILURE);
	}
	buffer[file_size] = '\0';
	return;
}

void find_line(char Line[])
{
    int i;
    for(i = 0; i < 100; i++)
    {
        if(*buffer != '\n'){
            Line[i] = *buffer;
            buffer++;
        }
        else
            break;
    }
    while(i < 100){
        Line[i] = '-';
        i++;
    }
    *buffer++;
    return;
}

void segment_array(char Line[])
{
    int tracer = 0, i, b1, b2;
    char base1[3], base2[3], middle[50];
    for(i = 0; Line[tracer] != ' '; tracer++, i++)
    {
        base1[i] = Line[tracer];
    }
    base1[i] = '\0';
    b1 = find_base(base1);
    tracer++;

    for(i = 0; Line[tracer] != ' '; tracer++, i++)
    {
        middle[i] = Line[tracer];
    }
    while(i < 50){
        middle[i] = '-';
        i++;
    }
    tracer++;

    for(i = 0; Line[tracer] != ' ' && Line[tracer] != '-'; tracer++, i++)
    {
        base2[i] = Line[tracer];
    }
    base2[i] = '\0';
    b2 = find_base(base2);

    if(b1 == b2){
        printf("%d ", b2);
        for(i = 0; i < 50 && middle[i] != '-'; i++)
            printf("%c", middle[i]);
        printf("\n");
    }
    else{
        toBin(middle, b1, b2);
    }
    return;
}

int find_base(char b[])
{
    int base;
    sscanf(b, "%d", &base);
    return base;
}

void toBin(char num[], int b1, int b2)
{
    int number = 0, i, j, h, nums[100];
    if(b1 == 10)
        sscanf(num, "%d", &number);

    else{
        for(j = 0; num[j] != '-'; j++){
            nums[j] = num[j] - '0';
            while(nums[j] )
        }
        nums[j] = -1;

         for(i = 0; nums[i] != -1 ; i++, j--)
        {
            if(nums[j] != -1)
                number += (nums[j] * pow(b1, i));
        }

    }
    printf("%d %d %d\n", b1, number, b2);
    //toB2(number, b2);
    return;
}

void toB2(int number, int b2)
{
    int count, full[50], i = 0, h = 0;
    char actual[50];

    while(number != 0){
        full[count] = number % b2;
        number /= b2;
        count++;
    }

    while(i < count)
    {
        if(full[i] == h){
            actual[i] = number_lineup[h];
            i++;
        }
        else
            h++;
    }
    while(i < 50){
        actual[i] = '-';
        i++;
    }

    print_Result(actual, b2);
}

void print_Result(char n[], int b2)
{
    int i;
    printf("%d ", b2);
    for(i = 0; i < 50 && n[i] != '-'; i++)
        printf("%c", n[i]);
    printf("\n");

    return;
}
