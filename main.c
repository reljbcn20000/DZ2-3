#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ScanString(void){
    int n=1;
    char *arr,c;
    arr = calloc(n+1, sizeof(char));

    int i = 0;
    while((c=getchar()) != ' '){
        if( ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')){ //[a-zA-Z0-9]
            char *temp_arr;
            temp_arr = calloc(n+1, sizeof(char));
            
            for(int j = 0; j < n; j++){
                temp_arr[j] = arr[j];
            }
            
            arr[n-1]=c;
            n++;
            i++;
        }
        else if(c == '\n'){
            return arr;
            
        }
    }
    arr[n-1]='\0';
    return arr;
}

int main(){
    printf("Kol-vo vershin: ");
    int kolvo;
    scanf("%d",&kolvo);
    if (kolvo <= 0)
        exit(9);
    
    char *name_elements[kolvo];
    int conn_elements[kolvo][kolvo];
    for(int i=0; i<kolvo; i++){
        for(int j=0; j<kolvo; j++){
            conn_elements[i][j] = 0;
        }
    }
    
    printf("Enter names of elements separated by spaces:\n");
    getchar();
        
    for(int i=0; i<kolvo; i++){
        name_elements[i] = ScanString();
        
        for (int j=0; j<i; j++){
            if( strcmp(name_elements[i], name_elements[j]) == 0){
                exit(9);
            }
        }
    }
            
    printf("Enter for each one connection separated by spaces\n"); // tut ne zabit' v konce problel!!!
    for(int i=0; i<kolvo; i++){
        printf("%d: ",i);
        _Bool flag=1;
        while(flag){
            char *compare;
            compare = ScanString();
            
            for(int j=0; j<kolvo; j++){
                if( strcmp(compare, name_elements[j]) == 0){
                    conn_elements[i][j]++;
                }
            }

            if(strcmp(compare, "") == 0){
                flag = 0;
            }
        }
    }
    
    printf("\n");
    _Bool relat_graph = 1;
    for(int i=0; i<kolvo; i++){
        _Bool temp_relat_graph = 0;
        for(int j=0; j<kolvo; j++){
            if(conn_elements[i][j] == 1)
                temp_relat_graph = 1;
            
            if(conn_elements[j][i] == 1)
                temp_relat_graph = 1;
        }
        if(temp_relat_graph == 0)
            relat_graph=0;
    }
    if(relat_graph == 0){
        printf("unrelated graph\n");
    } else {
        printf("related graph\n");

    }

    for(int i=0; i<kolvo; i++) {
        printf("%s\t", name_elements[i]);
        for (int j=0; j<kolvo; j++) {
            printf("%d ", conn_elements[i][j]);
        }
        printf("\n");
    }
    
    
    
    
    char *string;
    string = calloc(2048, sizeof(char));
    char arrow[3] = "->";
    strcat(string, "echo digraph G{ '");
    for(int i=0; i<kolvo; i++){
        strcat(string, name_elements[i]);
        strcat(string, "; ");
    }
    for(int i=0; i<kolvo; i++){
        for(int j=0; j<kolvo; j++){
            for(int k=0; k<conn_elements[i][j]; k++){
                strcat(string, name_elements[i]);
                strcat(string, arrow);
                strcat(string, name_elements[j]);
                strcat(string, "; ");
            }
        }
    }
    strcat(string, "}' | dot -Tpng > ./graph.png");

    
    system(string);
    system("open ./graph.png");
    
    return 0;
}
