#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<getopt.h>

#define MAXLINE 1024
#define PACKAGE ngram

struct node {
	char *ngram;
	int count;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;
int c_flag = 0;
int l_flag = 0;
int u_flag = 0;
int i_flag_flag = 0;

void ngram(char *word, int n);
struct node *addTree(struct node *, char *);
struct node *talloc(void);
void printTree(struct node *, FILE *fp);

int main(int argc, char *argv[]) {
	char *word = NULL;
	char *ptr = NULL;
	char line[MAXLINE];
	char delim = ".,:;'/\"+-_(){}[]<>*&^%$#@!?|=~/|\\=1234567890 \t\n";
	FILE *fp;
	
	int opt;
	int slice = 2;
		
	if(argc == 1) {
		printf("Incorrect!!");
		return 1;
	}
	//Add a welcome function i.e., help function. 
	// I have no idea what ngram function does. 
	while((opt = getopt(argc,argv,"wn: ucil: \n")) != -1) {
		switch(opt) {
			case 'w':
				welcome_message();
				return 0;
			case 'n':
				if(strchr(optarg,'-') == NULL) {
					slice = atoi(optarg);
					if(slice < 1 || slice > 10) {
						fprintf(stderr, "%s: Error: Value too low or too high. Select n in range of 1 to 10 \n",PACKAGE);
						return 1;
					}
					else {
						/* We can use this in case a range is given instead of a number */
					}
				}
				break;
			case 'u':
				u_flag = 1;
				break;
			case 'c':
				c_flag = 1;
			case 'i':
				i_flag = 1;
				break;
			case 'l':
				l_flag = 1;
				break;
			case ':':
				fprintf(stderr,"%s: Error: Option needs to be an argument ",PACKAGE);
				welcome_message();
				break;
			case '?':
				fprintf(stderr,"%s: Error: Option needs to be an argument ",PACKAGE);
				welcome_message();
				break;
		}
	}
	
	while ((fgets(line, MAXLINE, stdin)) != NULL) {
		if(strlen(line)>1) {
			if(l_flag == 1)
				for(ptr = line; *ptr;ptr++)
					if(isupper(*ptr)) *ptr = tolower(*ptr)
			word = strtok(line,delim);
			while(word != NULL) {
				if(i_flag == 1 && strlen(word) < slice) {
					word = strtok(NULL,delim);
					continue;
				}
				if(r_flag == 0) 
					ngram(word,slice);
				
				word = strtok(NULL,delim);
			}
		}
	}
	if(fp == NULL) 
		printTree(root,stdout);
	else
		printTree(root,fp), pclose(fp);
	return 0;
}
/* Config or options.
	-w  prints welcome message and other options
	-n 	length of ngram 
	-u  unique, discard all but one of successive identical ngrams
	-c 	count, prefix ngrams by the number of occurrences
	-i 	ignore words with length less than ngram length
	-l 	change into lower case before processing
	

*/
void welcome_message(void) {
	printf("Welcome to tokenizer and ngram program: \n");
	printf("Select one of the options from below: \n");
	printf("Options: \n");
	printf("  -h                print this help\n");
	printf("  -n [INT] 			build ngrams of length n \n");
	printf("  -u                uniq, discard all but one of successive identical ngrams\n");
	printf("  -c                count, prefix ngrams by the number of occurrences\n");
	printf("  -i                ignore words shorter as ngram length\n");
	printf("  -l                lower case input before processing. May decrease performance\n");
}

void ngram(char *word, int n) {
	char *p = NULL;
	char *q = NULL;
	char *padding = NULL;
	char *buffer = NULL;
	int i=0;
	int b = n-1;
	
	if((buffer = (char*) malloc(n+1)) == NULL) {
		fprintf(stderr,"%s:Error Failed malloc\n", PACKAGE);
	}
	
	if((padding = (char*) malloc(strlen(word)+n+2)) == NULL) {
		fprintf(stderr,"%s:Error: Failed malloc \n",PACKAGE);
	}
	sprintf(padding,"_%s",word);
	for(i=0;i<n-1;i++) {
		strcat(padding,"_");
	}
	p = padding;
	q = buffer;
	i = 0;
	while(*p) {
		if(n==1) {
			*q++ = '\0';
			root = addTree(root,buffer);
			i=0;
			p = p-b;
			q = buffer;
		}
		else {
			*q++ = *p++;
			i++;
		}
		free(padding);
		free(buffer);
	}
}

void node *addTree(struct node *p, char *word) {
	int cond;
	if(p==NULL) {
		p = talloc();
		p->ngrm = strdup(word);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w,p->ngrm)) == 0){
		p->count++
	} else if(cond < 0)
		p->left = addTree(p->left,word);
	else 
		p->right = addTree(p->right,word);
	return p;
}

struct node *talloc(void) {
	return (struct node *)malloc(sizeof(struct node));
}

void printTree(struct node *p, FILE *fp) {
	if(p != NULL) {
		printTree(p->left,fp);
		if (c_flag == 1)
			fprintf(fp,"%4d %s\n", p->count, p->ngrm);
		else
			fprintf(fp,"%s\n",p->ngrm);
		printTree(p->right,fp);
	}
}
