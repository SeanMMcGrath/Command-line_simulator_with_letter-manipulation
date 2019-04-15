#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//takes a char array str and returns a char array with chars reversed
char *strrev(char *str){//string reverse
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}


//takes a word as input, reverses it in another char*, then compares the two char by char skipping ahead when a non-alphanumeric char is reached
//if all chars match then the 'word' is a palindrome, and is printed as such. Otherwise no palindrome is printed
void palin(char *input){
	
	char* reverse = (char *) malloc(100);
 
   strcpy(reverse,input);
   strrev(reverse);//reverse is backwards input

   int inputLen = strlen(input);
   int reverseLen = strlen(reverse);
   
   int palindrome = 1;//true until proven false?   1 is true, 0 is false
   int inputCount = 0;
   int reverseCount = 0;
   for(;;){//continues until break;
	   
	    int cont = 0;//continues when for both input[x] and reverse[y] are alphnuemeric. Used to skip special characters and whitespace
		while(cont != 2){
			cont = 0;
			if(('a' <=  input[inputCount] && input[inputCount] <= 'z') || ('A' <=  input[inputCount] && input[inputCount] <= 'Z') || ('0' <=  input[inputCount] && input[inputCount] <= '9')){
				cont++;
			} else {
				inputCount++;
			}
			if(('a' <=  reverse[reverseCount] && reverse[reverseCount] <= 'z') || ('A' <=  reverse[reverseCount] && reverse[reverseCount] <= 'Z') || ('0' <=  reverse[reverseCount] && reverse[reverseCount] <= '9')){
				cont++;
			} else {
				reverseCount++;
			}
		} 
		
		if(tolower(reverse[reverseCount]) != tolower(input[inputCount])){
			palindrome = 0;//noncase sensitive, if there is a mismatch then palindrome = false
		}
	   
		inputCount++; reverseCount++;//increment
		if(palindrome == 0 || (inputCount == inputLen || reverseCount == reverseLen)){//found to not be a palindrome, or run out of chars to look through
			break; // we done so break loop, and begin preparing output
		}
   }
	if(palindrome == 0){
		printf("%s", reverse);
		printf(" <- no palindrome\n");
	} else {//==1, should never equal something other than 1 or 0
		printf("%s", reverse);
		printf(" <- palindrome\n");
	}
	
	//finally free memory
	free(reverse);
}


//changes the capitalization of chars from the input char* input
//code == 0; all lowercase to uppercase and visaversa 
//code == 1; all chars that are not already uppercase are changed to uppercase
//code == 2; all chars that are not already lowercase are changed to lowercase
//tolower and toupper ignore special characters so nothing is needed to be added for them
void cascnvt(char* input, char* code) {
	char* result = (char*) malloc(100);//allocate memory
	if(*code == '0'){//switch capitalization
		strcpy(result, input);
		
		for(int i=0;i<strlen(result);i++){
			if(islower(result[i])){
				result[i] = toupper(result[i]);
			} else if(isupper(result[i])){
				result[i] = tolower(result[i]);
			} 
		}
		printf("%s\n",result);
	}else if(*code == '1'){//to upper
		strcpy(result, input);
		for(int i=0;i<strlen(result);i++){
			result[i] = toupper(result[i]);
		}
		printf("%s\n",result);
	}else if(*code == '2') {//to lower
		strcpy(result, input);
		for(int i=0;i<strlen(result);i++){
			result[i] = tolower(result[i]);
		}
		printf("%s\n",result);
	}else {//something other than 0, 1, or 2 is entered as a code
		printf("[Error] Please enter the code correctly\n");
	} 
	
	free(result);
	//after printf'ing the output, release any used vars
}	



int main(){
  for(;;){
	printf("smcgrat3> $ ");
	char input[100];
	scanf("%[^\n]%*c", input);	//takes input in the syntax of either command(word) for command == 'palin' or command(word, code) for command == 'cascnvt'
	
	if(strcmp(input, "exit") == 0 && strlen(input) == 4){//so, input includes exit, and is only exit aka 4 char long
		return 0;
	} else {//not exiting this iteration
		int valid = 1;
		if(input[strlen(input)-1] != ')'){//if the last char is not a ')' then syntax is violated
			valid = 0;
		} else {//if syntax is not already violated, check for '(' syntax
			int numLeftParen = 0;//how many left parenthesis there are, should only be one!!!
			int numRightParen = 0;
			for(int i = 0; i < strlen(input); i++){
				if(input[i] == '('){
					numLeftParen++;
				}
				if(input[i] == ')'){
					numRightParen++;
				}
				if(numLeftParen > 1 || numRightParen > 1){
					break; //syntax already broken by having multiple '(' or ')', no need to search for more mistakes. Send error.
				}
			}
			if(numLeftParen != 1 || numRightParen != 1){//either no '(' or ')', or more than 1 
				valid = 0;
			}
		}
		
		
		if(valid == 1){//valid syntax
			char* info;
			info = strtok(input, "(");
			info = strtok(NULL, "(");
			if(input && info){
				if(strcmp(input, "cascnvt") == 0 && strlen(input) == 7){//////////////////check for no code input and no word input(?), as well as multiple ','
					int numOfComma = 0;
					int valid = 1; //1 is valid, 0 invalid syntax
					for(int i = 0; i < strlen(info); i++){//checks to make sure syntax is correct, having only a single ','(no ',' already covered)
						if(info[i] == ','){
							numOfComma++;
						}
						if(numOfComma > 1){
							break;
						}
					}
					if(numOfComma > 1){
						valid = 0;
					}
					if(valid == 1){
						char* temp = strtok(info,")"); 	
						if(temp){
							char* code;
							char* word = strtok(temp,",");
							code = strtok(NULL, ",");
							if(code&&word){
								//get the word and code from input
								cascnvt(word, code);
							} else {
								printf("Incorrect command \n");
							}
						} else {
							printf("Incorrect command \n");
						}
					} else {
						printf("[Error] Please enter the command correctly\n");
					}
				}else if(strcmp(input, "palin") == 0 && strlen(input) == 5){
					char* word = strtok(info,")");
					word = strtok(NULL, ")");
					//split at ')'				
					palin(info);
				
				} else {
					printf("Incorrect command \n");
				}
			} else {
				printf("Incorrect command \n");//no left parenthesis
			}
		} else {
			printf("[Error] Please enter the command correctly\n");
		}
	} 
  }
}