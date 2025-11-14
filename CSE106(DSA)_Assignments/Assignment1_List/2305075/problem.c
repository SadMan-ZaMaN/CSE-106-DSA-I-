#include <stdio.h>
#include "arrayList.h"
//#include "linkedList.h"

int main()
{
    FILE* file = fopen("in_prob.txt", "r");
    if(file == NULL){
        return 1;
    }

    arrayList dal, fl;
    //linkedList dal, fl;
    
    // initialize the lists
    init(&dal);
    init(&fl);

    int func, param;
    while(fscanf(file, "%d", &func) == 1 && func != 0)
    {
        if(func == 1 && fscanf(file, "%d", &param) == 1){
            printf("Recruit %d\n", param);

            if(is_present(param,&fl)){
                printf("In the Foe List, cannot recruit\n");
            }
            else{   
                printf("DA List:\n");
                append(param,&dal);
                //print(&dal);
            }
            // implement logic here
        }
        else if(func == 2 && fscanf(file, "%d", &param) == 1){
            printf("Fire %d\n", param);
            if(is_present(param,&dal)){
                printf("DA List:\n");
                delete_item(param,&dal);
                //print(&dal);
            }
            else{
                printf("Not Found in DA List\n");
                printf("DA List:\n");
                print(&dal);
            }

            if(is_present(param,&fl)){
                printf("Already Present in Foe list\n");
                printf("Foe List:\n");
                print(&fl);
            }
            else{
                
                printf("Foe List:\n");
                append(param,&fl);
                //print(&fl);
            }
            // implement logic here
        }
        else if(func == 3 && fscanf(file, "%d", &param) == 1){
            printf("Check %d\n", param);

            if(is_present(param,&dal)){
                printf("Friend\n");
            }
            else if(is_present(param,&fl)){
                printf("Foe\n");
            }
            else{
                printf("Unknown\n");        // kono list ei nei
            }
            //implement logic here
        }
        else{
            break;
        }
        printf("\n");
    }
   
    // free memory
    free_list(&fl);
    free_list(&dal);
    
    return 0;
}





