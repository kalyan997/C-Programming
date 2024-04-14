//Name :  Kalyan Baddam
//G_Number : G01334382



//preprocessing or loading standard libraries
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//Declaring a 2d array as global variable my_strings to store the strings
char my_strings[10][50];

//Declaration of functions before main function to avoid implicit declaration error
char check_illegal_char(char *str);
int check_if_empty(char *str);
int is_duplicate(char *str, int n);
void swap(char *str1, char *str2);
void sort_asc(char arr[][50]);
void sort_desc(char arr[][50]);


//Main function
int main()
{
    printf("Enter 10 character strings:\n");
    for(int i = 0; i < 10; i++){
        char temp[50];
        //printf("Please press Enter two times(Double Enter) after entering the string if string length is less than 50 :  \n");
        printf("Enter string %d: ",i+1);
        fgets(temp,50,stdin);
        
        //Using getchar after fgets to clear the input buffer
        //while ((getchar()) != '\n');
        
        if(check_if_empty(temp) != 0){
            i = i-1;
            //Error prompt if string is empty
            printf("Error: String is empty, please re-enter\n");
            continue;
        }
        
        //checking the string length of the entered string
        if(strlen(temp) > 26){
            i = i - 1;
            printf("Error: Entered string length is greater than 25; please re-enter\n");
            continue;
        }
        
        //check for illegal characters
        if( check_illegal_char(temp) != '0'){
            i = i-1;
            printf("Error: %c Is an illegal character - please re-enter\n", check_illegal_char(temp));
            continue;
        }
        
        //checking for duplicates
        if(is_duplicate(temp, i) == 1){
            i = i-1;
            printf("Error: duplicate string - please re-enter\n");
            continue;
        }
        
        //copying the string to 2d array if it satisfies all constraints
        strcpy(my_strings[i], temp);
        
    }
    
    
    
    //char sort_order;
    char sort_order[5];
    printf("Enter 'A' to print strings in (A)scending or Enter 'D' to print strings in (D)escending order: ");
    //prompt for sorting order of strings
    //scanf(" %c", &sort_order);
    fgets(sort_order,5,stdin);
    
    //Handling improper input for sorting
    //while(sort_order != 'A' && sort_order != 'D'){
        //printf("Error: Enter 'A' for ascending or 'D' for descending order- please re-enter: ");
        //scanf(" %c", &sort_order);
    //}
    
    while(sort_order[0] != 'A' && sort_order[0] != 'D'){
        printf("Error: Enter 'A' to print strings in (A)scending or Enter 'D' to print strings in (D)escending order:- please re-enter: ");
        fgets(sort_order,5,stdin);
    }
    
    //For ascending Order
    if(sort_order[0] == 'A'){
        printf("\nAscending Order: \n");
        sort_asc(my_strings);
        for(int i = 0; i < 10; i++){
        printf("%s\n",my_strings[i]);
        }
        printf("string with lowest ascii value is:    %s\n",my_strings[0]);
        printf("string with highest ascii value is:   %s\n",my_strings[9]);
    }
    
    //For descending order
    else{
        printf("\nDescending Order: \n");
        sort_desc(my_strings);
        for(int i = 0; i < 10; i++){
        printf("%s\n",my_strings[i]);
        }
        printf("string with lowest ascii value is:   %s\n",my_strings[9]);
        printf("string with highest ascii value is:  %s\n",my_strings[0]);
    }
    
    return 0;
}



//function to check if the string contains illegal characters
char check_illegal_char(char *str){
    //array of illegal characters given in qstn
    char illegal_char[8] = {'!', '@', '#', '$', '%', '^', '(', ')'};
    for(int i=0;i<8;i++ ){
         //using strchr to find the occurence of illegal characters
         if(strchr(str,illegal_char[i]) != NULL) 
             return illegal_char[i];
     }
    return '0';
}


//function to check if the string is empty or not i.e it is valid or not
int check_if_empty(char *str){
    int count = 0;
    for(int i=0; i<strlen(str); i++){
        if(str[i] == ' ' || str[i] == '\n'){
            count++;
        }
    }
    if(count == strlen(str)){
        return 1;
    }
    return 0;
}


//function to check if the entered string is already in the array of strings or not
int is_duplicate(char *str, int n){
    for(int i=0; i<n; i++){
        //using strcmp to compare current string with  strings in array
        if(strcmp(my_strings[i], str) == 0){
            return 1;
        }
    }
    return 0;
}


//function to swap two strings which is used in sorting of strings using Bubble sort
void swap(char *str1, char *str2)
{
  //dymnamic memory allocation
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  //freeing the allocated space after use
  free(temp);
}   


//function to sort strings in ascending order using Bubble Sort
//Bubble Sort to sort strings in ascending order
void sort_asc(char arr[][50])
{
   int i, j;
   int n =10;
   int flag;
   for (i = 0; i < n-1; i++){
       flag = 0;
       for (j = 0; j < n-i-1; j++){
           if(strcmp(my_strings[j], my_strings[j+1]) > 0){
               //arranging two adjacent strings in order by swapping
               swap(my_strings[j], my_strings[j+1]);
               flag = 1;
           }
       }
       //if the array is sorted flag becomes 0 so the loop will break
       if(flag == 0){
           break;
       }
   }     
}


//function to sort strings in descending order using Bubble Sort
//Bubble Sort to sort strings in descending order
void sort_desc(char arr[][50])
{
   int i, j;
   int n =10;
   int flag;
   for (i = 0; i < n-1; i++){
       flag = 0;
       for (j = 0; j < n-i-1; j++){
           if(strcmp(my_strings[j], my_strings[j+1]) < 0){
               //arranging two adjacent strings in order by swapping
               swap(my_strings[j], my_strings[j+1]);
               flag = 1;
           }
       }
       
       //if the array is sorted flag becomes 0 so the loop will break
       if(flag == 0){
           break;
       }
   }     
}