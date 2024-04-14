//Homework 2
//Name: Kalyan Baddam
//G Num: G01334382

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Initializing structure in ythe format of Ip address
struct address_t	
{
	int	octet[4];
	char alias[11];
	struct address_t *next;
};

//Initializing head as global variable
struct address_t *head = NULL;

//Implicit declaration of functions
void add_address(char *add, char *alias);
void lookup_address(char *alias);
void update_address(char *alias);
void delete_address(char *alias);
void display_list();
void display_aliases_for_location(int add_1,int add_2);
void saveto_file(char *file_name);
void quit_program();
void display_menu();

int check_alias_valid(char *alias);
int check_alias_present(char *alias);
int check_address_valid(int add1,int add2, int add3, int add4);
int check_address_present(int add1,int add2, int add3, int add4);

char *toLower(char *str);


int main()
{
    //Opening file using c file operations
    FILE *filptr;
    char line[100];
    filptr = fopen("CS531_Inet.txt","r");
    
    //read from file line by line
    while(fgets(line,100,filptr)){
        struct address_t *node = malloc(sizeof(struct address_t));
        //Parsing the line using sscanf
        sscanf(line,"%d.%d.%d.%d %s",&node->octet[0],&node->octet[1],&node->octet[2],&node->octet[3],node->alias);
        //toLower(node->alias);
        node->next = head;
        head = node;
    }
    //closing file after reading all lines into a linked list
    fclose(filptr);
    
    while(1){
        int selected_menu_option;
        char menu_option[20];
        display_menu();
        printf("\nEnter your option from the menu(0-8): \n");
        scanf("%d",&selected_menu_option);
        getchar();
        
        //switch case for each option in the menu
        switch(selected_menu_option){
            case 1:{
                char temp[50];
                char Ipv4_add[15],Ipv4_alias[11];
                printf("Enter Ipv4 address/alias pair in format: 145.76.99.3 Google\n");
                fgets(temp,50,stdin);
                sscanf(temp,"%s %s",Ipv4_add,Ipv4_alias);
                //toLower(Ipv4_alias);
                add_address(Ipv4_add,Ipv4_alias);
                printf("\n");
                break;
            }
            case 2:{
                char look_alias[11];
                printf("Enter an alias to get its address: \n");
                scanf("%s",look_alias);
                getchar();
                //if enterd alias is not present in the list
                if(check_alias_present(look_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                else{
                    lookup_address(look_alias);
                    printf("\n");
                }
                break;
            }
            case 3:{
                //duplicate address
                char update_alias[11];
                printf("Enter an alias to update its address: \n");
                scanf("%s",update_alias);
                getchar();
                //toLower(update_alias);
                if(check_alias_present(update_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                else{
                    update_address(update_alias);
                }
                break;
            }
            case 4:{
                char delete_alias[11];
                char del_cnfrm;
                printf("Enter an alias to delete its address: \n");
                scanf("%s",delete_alias);
                getchar();
                //toLower(delete_alias);
                //To check if alias is present in the list
                if(check_alias_present(delete_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                
                else{
                    printf("Are you sure you want to delete this address\nif yes press y, if no press n:\n" );
                    scanf("%c",&del_cnfrm);
                    getchar();
                    //prompt for confirmation to delete
                    if(del_cnfrm == 'y'){
                        delete_address(delete_alias);
                    }
                    else if(del_cnfrm == 'n'){
                        printf("Okay! Not deleting %s\n",delete_alias);
                    }
                    else{
                        printf("Invalid Entry\n");
                    }
                }
                break;
            }
            case 5:{
                //if the list is empty
                if(head == NULL){
                    printf("The address/alias pair list is empty\n");
                    printf("No. of nodes are 0\n");
                }
                else{
                    display_list();
                }
                break;
            }
            case 6:{
                int address_location_1, address_location_2;
                printf("Enter the address location #1(0-255):\n");
                scanf("%d",&address_location_1);
                getchar();
                printf("Enter the address location #2(0-255):\n");
                scanf("%d",&address_location_2);
                getchar();
                //Re-prompt for location if loaction is inbvalid
                while(address_location_1 < 0 || address_location_2 <0 || address_location_1 > 255 || address_location_2 > 255){
                    printf("Error: Address location out of range. Address locations cannot be greater than 255, and cannot be less than 0\n");
                    printf("Enter the address location #1(0-255):\n");
                    scanf("%d",&address_location_1);
                    getchar();
                    printf("Enter the address location #2(0-255):\n");
                    scanf("%d",&address_location_2);
                    getchar();
                }
                display_aliases_for_location(address_location_1, address_location_2);
                break;
            }
            case 7:{
                char file_name[25];
                printf("Enter file name to save the list:\n");
                scanf("%s",file_name);
                getchar();
                saveto_file(file_name);
                break;
            }
            case 8:
                quit_program();
            default:
                printf("Invalid selection:\n");
        }
    }
    return 0;
}

//Function to display the menu options for the user to choose from
void display_menu(){
    printf("\nMenu:");
    printf("\nEnter '1' to Add address\n");
    printf("Enter '2' to Lookup address\n");
    printf("Enter '3' to Update address\n");
    printf("Enter '4' to Delete address\n");
    printf("Enter '5' to Display list\n");
    printf("Enter '6' to Display aliases for locations\n");
    printf("Enter '7' to Save to file\n");
    printf("Enter '8' to Quit\n");
}

//Function to add the given address alias pair to the list, Here insertion is done at the beginning of the linked list
void add_address(char *add, char *alias) {
    
    int alias_present, alias_valid, address_present, address_valid,address1,address2,address3,address4;
    struct address_t *link = (struct address_t*) malloc(sizeof(struct address_t));
    
    sscanf(add,"%d.%d.%d.%d",&address1,&address2,&address3,&address4);
    
    address_valid = check_address_valid(address1,address2,address3,address4);
    address_present = check_address_present(address1,address2,address3,address4);
    alias_present = check_alias_present(alias);
    alias_valid = check_alias_valid(alias);
    if(address_valid != 1){
        printf("Error: The enterded address is not valid\n");
        return;
    }
    if(address_present == 1){
        printf("Error: The enterded address is already taken\n");
        return;
    }
    if(alias_present == 1){
        printf("Error: The entered alias is already present in the list\n");
        return;
    }
    if(alias_valid != 1){
        printf("Error: The entered alias is not valid, length of alias should not be greater than 10\n");
        return;
    }
    
    sscanf(add,"%d.%d.%d.%d",&link->octet[0],&link->octet[1],&link->octet[2],&link->octet[3]);
    strcpy(link->alias,alias);
    link->next = head;
    head = link;
}

//Function to search or query the address of the given alias
void lookup_address(char *alias){
    struct address_t *current_node = head;
    int lookup_found;
        while ( current_node != NULL) {
            lookup_found = strcmp(alias, current_node->alias);
            if(lookup_found == 0){
                printf("The address for alias %s is:",alias);
                printf(" %d.",current_node->octet[0]);
                printf("%d.",current_node->octet[1]);
                printf("%d.",current_node->octet[2]);
                printf("%d ",current_node->octet[3]);
                break;
            }
            current_node = current_node->next;
        }
}

//Function to update the address of given alias
void update_address(char *alias){
    struct address_t *current_node = head;
    int lookup_found;
    char new_add[15];
    int address_present,address_valid,address1,address2,address3,address4;
    
        while ( current_node != NULL) {
            lookup_found = strcmp(alias, current_node->alias);
            if(lookup_found == 0){
                printf("The current address for alias %s is:",alias);
                printf(" %d.",current_node->octet[0]);
                printf("%d.",current_node->octet[1]);
                printf("%d.",current_node->octet[2]);
                printf("%d ",current_node->octet[3]);
                printf("\nEnter new address in the form 123.45.6.80 for alias %s to update:\n",alias);
                fgets(new_add,50,stdin);
                sscanf(new_add,"%d.%d.%d.%d",&address1,&address2,&address3,&address4);
                address_valid = check_address_valid(address1,address2,address3,address4);
                address_present = check_address_present(address1,address2,address3,address4);
                
                //if entered new address is not valid display error
                if(address_valid != 1){
                    printf("Error: The address you are updating to is not valid\n");
                    return;
                }
                //if entered address already exists in the list
                if(address_present == 1){
                    printf("Error: The address you are updating to is already taken\n");
                    return;
                }
                sscanf(new_add,"%d.%d.%d.%d",&current_node->octet[0],&current_node->octet[1],&current_node->octet[2],&current_node->octet[3]);
                printf("The new address for alias %s is:",alias);
                printf(" %d.",current_node->octet[0]);
                printf("%d.",current_node->octet[1]);
                printf("%d.",current_node->octet[2]);
                printf("%d\n",current_node->octet[3]);
                break;
            }
            current_node = current_node->next;
        }
}

//Function to delete the node the with the given alias
void delete_address(char *alias){
    struct address_t *temp = head, *prev;
     
        // If head node itself holds the key to be deleted
        if (temp != NULL && strcmp(temp->alias,alias) == 0) {
            head = temp->next;
            free(temp);
            return;
        }
     
        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (temp != NULL && strcmp(temp->alias,alias) != 0) {
            prev = temp;
            temp = temp->next;
        }
     
        // Unlink the node from linked list
        prev->next = temp->next;
     
        free(temp); // Free memory
}

//Function to display the list of address alias pairs
void display_list(){
    printf("The address alias pairs in the list are:\n");
    printf("\n");
    int no_nodes = 0;
    struct address_t *current_node = head;
        //traverse through the linked listr and print them
        while ( current_node != NULL) {
            printf("%d.",current_node->octet[0]);
            printf("%d.",current_node->octet[1]);
            printf("%d.",current_node->octet[2]);
            printf("%d\t",current_node->octet[3]);
            printf("%s\n",current_node->alias);
            current_node = current_node->next;
            no_nodes += 1;
        }
    printf("\nTotal no. of nodes in the list are: %d\n",no_nodes);
}

//Function to display alises for the given location of Ipv4 address
void display_aliases_for_location(int add_1,int add_2){
    printf("Displaying aliases for given location\n");
    struct address_t *current_node = head;
    int address_found = 0;
    printf("The aliases with address location %d.%d are:\n",add_1,add_2);
        while ( current_node != NULL) {
            if(add_1 == current_node->octet[0] && add_2 == current_node->octet[1]){
                address_found = 1;
                printf("%s\t",current_node->alias);
                printf("%d.%d.%d.%d\n",current_node->octet[0],current_node->octet[1],current_node->octet[2],current_node->octet[3]);
                current_node = current_node->next;
            }
            else{
                current_node = current_node->next;
            }
        }
    if(address_found == 0){
        printf("Error:There exists no address in list with location %d.%d\n",add_1,add_2);
    }
}

//Function to save the existing list to the file
void saveto_file(char *file_name){
    printf("Saving to file\n");
    FILE * fptr;
    fptr = fopen(file_name, "w");
    struct address_t *current_node = head;

    if(fptr==NULL)
    {
        printf("Error\n");
    }

    else
    {
        while(current_node != NULL)
        {
            fprintf(fptr, "%d.%d.%d.%d %s\n", current_node->octet[0],current_node->octet[1],current_node->octet[2],current_node->octet[3],current_node->alias);
            current_node = current_node->next;
        }
    }

    fclose(fptr);
}

//Function to quit the program
void quit_program(){
    printf("Quitting program......\n");
    //To terminate the program completely
    exit(0);
}

//Function to check if the given alias already exists in the list or not
int check_alias_present(char *alias){
    struct address_t *current_node = head;
    int flag = 0;
        while ( current_node != NULL) {
            if(strcmp(alias,current_node->alias) == 0){
                flag = 1;
            }
            current_node = current_node->next;
        }
    return flag;
}

//Function to check if the given address is valid or not
int check_address_valid(int add1,int add2, int add3, int add4){
    if((add1>=0)&&(add2>=0)&&(add3>=0)&&(add4>=0)&&(add1<256)&&(add2<256)&&(add3<256)&&(add4<256)){
        return 1;
    }
    return 0;
}

//Function to check if the given address already exists in the list or not
int check_address_present(int add1,int add2, int add3, int add4){
    struct address_t *current_node = head;
        while ( current_node != NULL) {
            if((add1 == current_node->octet[0])&&(add2 == current_node->octet[1])&&(add3 == current_node->octet[2])&&(add4 == current_node->octet[3])){
                return 1;
            }
            current_node = current_node->next;
        }
    return 0;
}

//Functioin to check if the given alias is valid or not
int check_alias_valid(char *alias){
    if(strlen(alias)>10){
        return 0;
    }
    return 1;
}

//Function to convert Uppercase characters to lowercase characters
char *toLower(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
