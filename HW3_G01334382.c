//Name: Kalyan Baddam
//G#: G01334382
// CS_531 Homework_4

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Initializing structure in the format of Ip address
struct address_t
{
    int    octet[4];
    char alias[12];
    struct address_t *left, *right;
};

//global variables
int loc_found;
int add_found;
//int count =0;


//Implicit declaration of functions
struct address_t *insert(struct address_t *node, char *add, char *alias);
struct address_t *searchBST(struct address_t *root, char *alias);
struct address_t *update_address_f(struct address_t *root, char *alias);
struct address_t* deleteNode(struct address_t *root, char *alias);
void display_list(struct address_t *root);
void disp_loc_alias(struct address_t *root, int add_1, int add_2);
void saveto_file(char *file_name, struct address_t *root);
void quit_program();


void display_menu();


int check_alias_valid(char *alias);
int check_alias_present(struct address_t *root,char *alias);
int check_address_valid(int add1,int add2, int add3, int add4);
void check_address_present(struct address_t *root,int add1,int add2, int add3, int add4);


void write_file(FILE *fptr, struct address_t *root);
char *toLower(char *str);
struct address_t* minValueNode(struct address_t* node);
int check_if_empty(char *str);


//Main function
int main()
{
    //Initializiong root to null
    struct address_t *root = NULL;
    FILE *filptr;
    char line[100];
    filptr = fopen("CS531_Inet.txt","r");
    
    //Inserting all the address alias pairs in file to BST
    while(fgets(line,100,filptr)){
        char Ipv4_add[15],Ipv4_alias[12];
        sscanf(line,"%s %s",Ipv4_add,Ipv4_alias);
        toLower(Ipv4_alias);
        root = insert(root,Ipv4_add,Ipv4_alias);
    }
    fclose(filptr);
    
    
    while(1){
        int selected_menu_option;
        display_menu();
        printf("\nEnter your option from the menu(0-8): \n");
        scanf("%d",&selected_menu_option);
        getchar();
        
        //switch case for each option in the menu
        switch(selected_menu_option){
            case 1:{
                
                int address_present,address_valid,alias_present, alias_valid,address1,address2,address3,address4;
                char temp[50];
                char Ipv4_add[15],Ipv4_alias[15];
                add_found = 0;
                printf("Enter Ipv4 address/alias pair in format: 145.76.99.3\n");
                fgets(Ipv4_add,50,stdin);
                //sscanf(temp,"%s %s",Ipv4_add,Ipv4_alias);
                sscanf(Ipv4_add,"%d.%d.%d.%d",&address1,&address2,&address3,&address4);
                printf("\nEnter alias corresponding to entered address:\n");
                //scanf("%s",Ipv4_alias);
                //getchar();
                fgets(Ipv4_alias,15,stdin);
                //printf("%s",Ipv4_alias);
                Ipv4_alias[strcspn(Ipv4_alias, "\n")] = 0;
                //printf("%s",Ipv4_alias);
                //printf("testing\n");
                address_valid = check_address_valid(address1,address2,address3,address4);
                check_address_present(root,address1,address2,address3,address4);
                alias_present = check_alias_present(root,Ipv4_alias);
                alias_valid = check_alias_valid(Ipv4_alias);
                if(address_valid != 1 || alias_valid != 1 || alias_present == 1 || add_found ==1){
                    printf("Error:The entered address alias pair is not valid:\n");
                    if(address_valid != 1){
                        printf("Error:The entered address is not valid\n");
                    }
                    else if(add_found == 1){
                        printf("Error:The entered address is already present\n");
                    }
                    else if(alias_valid != 1){
                        printf("Error:The entered aliass is not valid, length of alias should be 1-10\n");
                    }
                    else{
                        printf("Error:The entered alias is already present\n");
                    }
                }
                else{
                    toLower(Ipv4_alias);
                    root = insert(root,Ipv4_add,Ipv4_alias);
                    printf("\n");
                    //add_found = 0;
                }
                add_found = 0;
                break;
            }
            case 2:{
                char look_alias[15];
                printf("Enter an alias to get its address: \n");
                //scanf("%s",look_alias);
                //getchar();
                fgets(look_alias,15,stdin);
                //printf("%s",Ipv4_alias);
                look_alias[strcspn(look_alias, "\n")] = 0;
                //if enterd alias is not present in the list
                if(check_alias_present(root,look_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                else{
                    searchBST(root,look_alias);
                }
                break;
            }
            case 3:{
                //duplicate address
                //not valid address
                char update_alias[15];
                add_found = 0;
                printf("Enter an alias to update its address: \n");
                //scanf("%s",update_alias);
                //getchar();
                fgets(update_alias,15,stdin);
                //printf("%s",Ipv4_alias);
                update_alias[strcspn(update_alias, "\n")] = 0;
                //toLower(update_alias);
                if(check_alias_present(root,update_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                else{
                    update_address_f(root,update_alias);
                }
                add_found = 0;
                break;
            }
            case 4:{
                char delete_alias[15];
                char del_cnfrm;
                printf("Enter an alias to delete its address: \n");
                //scanf("%s",delete_alias);
                //getchar();
                fgets(delete_alias,15,stdin);
                //printf("%s",Ipv4_alias);
                delete_alias[strcspn(delete_alias, "\n")] = 0;
                //toLower(delete_alias);
                //To check if alias is present in the list
                if(check_alias_present(root,delete_alias) != 1){
                    printf("Error: The entered alias is not present in the list\n");
                }
                
                else{
                    printf("Are you sure you want to delete this address\nif yes press y, if no press n:\n" );
                    scanf("%c",&del_cnfrm);
                    getchar();
                    //prompt for confirmation to delete
                    if(del_cnfrm == 'y'){
                        root = deleteNode(root,delete_alias);
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
                if(root == NULL){
                    printf("The address/alias pair list is empty\n");
                    printf("No. of nodes are 0\n");
                }
                else{
                    display_list(root);
                    //printf("The no. of nodes in the BST are: %d\n",count);
                }

                //count = 0;
                break;
            }
            case 6:{
                //no addresses with given location
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
                loc_found = 0;
                printf("The aiases with location %d.%d are:\n",address_location_1,address_location_2);
                disp_loc_alias(root,address_location_1, address_location_2);
                if(loc_found == 0){
                    printf("Error: Sorry! No addresses with given location\n");
                }
                loc_found = 0;
                break;
            }
            case 7:{
                char file_name[25];
                printf("Enter file name to save the list:\n");
                scanf("%s",file_name);
                getchar();
                saveto_file(file_name,root);
                break;
            }
            case 8:
                quit_program();
            default:
                printf("Error:Invalid selection:\n");
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



//Function to insert nodes into BST
struct address_t *insert(struct address_t *node, char *add, char *alias)
{
      /* If the tree is empty, return a new node */
    //printf("%s\n",add);
    //printf("%s\n",alias);
    if (node == NULL){
        struct address_t *temp = (struct address_t*) malloc(sizeof(struct address_t));
        sscanf(add,"%d.%d.%d.%d",&temp->octet[0],&temp->octet[1],&temp->octet[2],&temp->octet[3]);
        strcpy(temp->alias,alias);
        temp->left = temp->right = NULL;
        return temp;
    }
    /* Otherwise, recur down the tree */
    //if (key < node->key)
    if(strcmp(alias,node->alias)<=0){
        node->left = insert(node->left, add, alias);
    }
    else if(strcmp(alias,node->alias)>0){
        node->right = insert(node->right, add, alias);
    }
    else{
        printf("Alias already exists\n");
    }
    /* return the (unchanged) node pointer */
    return node;
}


//Function to lookuip given alias node
struct address_t *searchBST(struct address_t *root, char *alias){
    if(root==NULL){
        //printf("No address\n");
        return root;
    }                   // If tree doesn't exist i.e root is NULL,return NULL.
    if(strcmp(root->alias,alias) == 0){
        printf("The address of %s is: %d.%d.%d.%d\n",alias,root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
        return root;
    }
    // If the value of key matches the node value,return the node.
    else if (strcmp(root->alias,alias) < 0 ) return searchBST(root->right,alias); // If the key is greater than node's value, then search for key in right subtree.
    else return searchBST(root->left,alias);   // If the node value is greater than the key value then search key in left subtree.
}


//Function to update address of given alias node
struct address_t *update_address_f(struct address_t *root, char *alias){
    char new_add[18];
    int address1, address2,address3,address4,address_valid;
    //add_found = 0;
    if(root==NULL){
        //printf("No address\n");
        return root;
    }                   // If tree doesn't exist i.e root is NULL,return NULL.
    if(strcmp(root->alias,alias) == 0){
        //printf("Address : %d.%d.%d.%d\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
        printf("The current address for alias %s is:",alias);
        printf(" %d.",root->octet[0]);
        printf("%d.",root->octet[1]);
        printf("%d.",root->octet[2]);
        printf("%d ",root->octet[3]);
        printf("\nEnter new address in the form 123.45.6.80 for alias %s to update:\n",alias);
        fgets(new_add,18,stdin);
        sscanf(new_add,"%d.%d.%d.%d",&address1,&address2,&address3,&address4);
        address_valid = check_address_valid(address1,address2,address3,address4);
        check_address_present(root,address1,address2,address3,address4);
        if(address_valid != 1){
            printf("Error: The address you are updating to is not valid\n");
        }
        //if entered address already exists in the list
        else if(add_found == 1){
            printf("Error: The address you are updating to is already taken\n");
        }
        else{
            sscanf(new_add,"%d.%d.%d.%d",&root->octet[0],&root->octet[1],&root->octet[2],&root->octet[3]);
        }
        //add_found = 0;
        return root;
    }            // If the value of key matches the node value,return the node.
    else if (strcmp(root->alias,alias) < 0 ) return update_address_f(root->right,alias); // If the key is greater than node's value, then search for key in right subtree.
    else return update_address_f(root->left,alias);   // If the node value is greater than the key value then search key in left subtree.
}


//Function to return Inorder predecessor to replace the node to be deleted
/* Given a non-empty binary search
   tree, return the node
   with minimum key value found in
   that tree. Note that the
   entire tree does not need to be searched. */
struct address_t* minValueNode(struct address_t* node)
{
    struct address_t* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

//Function to delete the given alias node
/* Given a binary search tree
   and a key, this function
   deletes the key and
   returns the new root */
struct address_t* deleteNode(struct address_t *root, char *alias)
{
    //count = count -1
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(alias,root->alias)<0)
        root->left = deleteNode(root->left, alias);
 
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(alias,root->alias)>0)
        root->right = deleteNode(root->right, alias);
 
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        
        // node with only one child or no child
        if (root->left == NULL) {
            struct address_t *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct address_t *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct address_t *temp = minValueNode(root->right);
 
        // Copy the inorder
        // successor's content to this node
        strcpy(root->alias,temp->alias);
        root -> octet[0] = temp -> octet[0];
        root -> octet[1] = temp -> octet[1];
        root -> octet[2] = temp -> octet[2];
        root -> octet[3] = temp -> octet[3];
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->alias);
    }
    return root;
}


//Function to display the list of address alias pairs of BST in Inorder
void display_list(struct address_t *root){
    //count = 0;
    if (root != NULL) {
        display_list(root->left);
        printf("%d.",root->octet[0]);
        printf("%d.",root->octet[1]);
        printf("%d.",root->octet[2]);
        printf("%d\t",root->octet[3]);
        printf("\t%s\n",root->alias);
        //count+=1;
        //printf("%d\n",count);
        display_list(root->right);
    }
}

//Function to display aliases of given location
void disp_loc_alias(struct address_t *root, int add_1, int add_2)
{
    //printf("Inorder:\n");
    //add_present = 0;
    if (root != NULL) {
        //printf("Nodes exist\n");
        disp_loc_alias(root->left,add_1,add_2);
        if(add_1 == root->octet[0] && add_2 == root->octet[1]){
            printf("%s\t",root->alias);
            printf("%d.%d.%d.%d\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
            //address_found = 1;
            
             //location_present = 1;
            loc_found = 1;
        }
        disp_loc_alias(root->right,add_1,add_2);
    }
    /*if(count == 0){
        printf("No addresses with given location\n");
    }*/
    //printf("Inor func done\n");
}

//Function to save the existing list to the file
void saveto_file(char *file_name, struct address_t *root){
    printf("Saving to file\n");
    FILE * fptr;
    fptr = fopen(file_name, "w");
    //struct address_t *current_node = head;

    if(fptr==NULL)
    {
        printf("Error:unable to open or create file\n");
    }

    else
    {
        write_file(fptr, root);
    }

    fclose(fptr);
}


//Function to write to file
void write_file(FILE *fptr, struct address_t *root){
    if (root != NULL) {
        write_file(fptr,root->left);
        fprintf(fptr,"%d.",root->octet[0]);
        fprintf(fptr,"%d.",root->octet[1]);
        fprintf(fptr,"%d.",root->octet[2]);
        fprintf(fptr,"%d\t",root->octet[3]);
        fprintf(fptr,"\t%s\n",root->alias);
        write_file(fptr,root->right);
    }
}

//Function to quit the program
void quit_program(){
    printf("Quitting program......\n");
    exit(0);
}

//Function to check if the alias is present in BST
int check_alias_present(struct address_t *root, char *alias){
    
    if(root==NULL){
        //printf("No address\n");
        return 0;
    }                   // If tree doesn't exist i.e root is NULL,return NULL.
    if(strcmp(root->alias,alias) == 0){
        //printf("Address : %d.%d.%d.%d\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
        return 1;
    }            // If the value of key matches the node value,return the node.
    else if (strcmp(root->alias,alias) < 0 ) return check_alias_present(root->right,alias); // If the key is greater than node's value, then search for key in right subtree.
    else return check_alias_present(root->left,alias);   // If the node value is greater than the key value then search key in left subtree.

    //return 0;
}

//Function to check if the address is valid
int check_address_valid(int add1,int add2, int add3, int add4){
    if((add1>=0)&&(add2>=0)&&(add3>=0)&&(add4>=0)&&(add1<256)&&(add2<256)&&(add3<256)&&(add4<256)){
        return 1;
    }
    return 0;
}

//Function to check if address is present in BST
void check_address_present(struct address_t *root, int add1,int add2, int add3, int add4){
    //int add_present = 0;
    //printf("%d %d %d %d\n",add1,add2,add3,add4);
    if (root != NULL) {
        //printf("Nodes exist\n");
        //printf("%d %d %d %d\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
        if((add1 == root->octet[0])&&(add2 == root->octet[1])&&(add3 == root->octet[2])&&(add4 == root->octet[3])){
            add_found = 1;
            //printf("present\n");
            //add_present = 1;
            //return 1;
        }
        check_address_present(root->left,add1,add2,add3,add4);
        check_address_present(root->right,add1,add2,add3,add4);
    }
    //return add_present;
}

//Function to check if a given address is valid
int check_alias_valid(char *alias){
    if(check_if_empty(alias) || strlen(alias) <1 || strlen(alias)>10){
        return 0;
    }
    return 1;
}


//Function to convert uppercase alphabets to lowercase
char *toLower(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}



//Function to check if the string is empty
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
