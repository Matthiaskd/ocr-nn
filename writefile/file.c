#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>


#define MAX_LEN 256
//returns TRUE(1) if the dir was just created, FALSE otherwise
int dir_exists(char* path){
	if(mkdir(path,0777)==-1){
		return 0;
	}
	return 1;
}

//writes a column matrix in a file
void write_column(double column[], size_t len, char* path){
	//opens the file in appending mode
	FILE* writer= fopen(path, "a");
	size_t i;
	for(i=0; i<len; i++){
		fprintf(writer, "%f",column[i]);
		fprintf(writer," ");
	}
	fprintf(writer,"\n");
	fclose(writer);
}
//writes a 2d matrix in a file
void write_mult(double matrix[][2], size_t len, char* path){
	size_t i;
	for(i=0; i<len; i++){
		write_column(matrix[i], 2, path);
	}
}

//restores a column matrix


//restores a 2d matrix
void read_matrix(double matrix[][10], size_t len, char* path){
	FILE* fp;
	fp= fopen(path,"r");
	char buffer[MAX_LEN];
	while(fgets(buffer, MAX_LEN, fp))
	{
		buffer[strcspn(buffer,"\n")]=0;
		printf("%s\n", buffer);
	}
	fclose(fp);
}


int main(void){
	
	dir_exists("bin");
	char* path="bin/column";
	double column[5]={1,2,3,4,5};
	write_column(column, 5, path);
	double test[5];
	printf("OKOKOKKOKOKOKOKO\n");
	read_matrix(NULL, 10, path);
	return 0;
}
