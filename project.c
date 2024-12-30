#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Category {
    int CategoryId;
    char CategoryName[50];
};
struct Category ctr[100];
int categoryCount = 0;

void showCategory();
void addCategory();
void editCategory();

int main(){
    int choose;
    do {
        printf("====== Store Management System Using C =====\n");
        printf("[1] Hien thi danh sach \n");
        printf("[2] Them danh muc \n");
        printf("[3] Sua danh muc \n");
        printf("=========================== \n");
        printf("Nhap lua chon cua ban: \n");
        scanf("%d", &choose);
        switch (choose){
            case 1:
                showCategory();
                break;
            case 2:
                addCategory();
                break;
            case 3:
            	editCategory();
            	break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }

    } while (choose != 0); 

    return 0;
}

void showCategory(){
    if (categoryCount == 0){
        printf("Khong co muc nao trong danh sach! \n");
        return;
    }
    printf("\nDanh sach danh muc:\n");
    printf("\n%-10s | %-50s\n", "ID", "Ten");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < categoryCount; i++) {
        printf("%-10d | %-50s\n", ctr[i].CategoryId, ctr[i].CategoryName); 
    }
}

void addCategory(){
    if (categoryCount >= 100){
        printf("Danh sach da day, khong the them danh muc moi!\n");
        return;
    }
    printf("Nhap ID danh muc: ");
    scanf("%d", &ctr[categoryCount].CategoryId); 
    printf("Nhap ten danh muc: ");
    getchar();  
    fgets(ctr[categoryCount].CategoryName, sizeof(ctr[categoryCount].CategoryName), stdin);
    ctr[categoryCount].CategoryName[strcspn(ctr[categoryCount].CategoryName, "\n")] = 0; 
    categoryCount++;
    printf("Danh muc da duoc them thanh cong!\n");
}

void editCategory(){
	int id, found = 0;
    printf("Nhap ID danh muc muon sua: ");
    scanf("%d", &id);
     for (int i = 0; i < categoryCount; i++){
       if (ctr[i].CategoryId == id) {
           found = 1;
            printf("Danh muc hien tai:\n");
            printf("ID: %d | Ten: %s\n", ctr[i].CategoryId, ctr[i].CategoryName);
            printf("Nhap ten danh muc moi: ");
            getchar();  
            fgets(ctr[i].CategoryName, sizeof(ctr[i].CategoryName), stdin);
            ctr[i].CategoryName[strcspn(ctr[i].CategoryName, "\n")] = 0; 
            printf("Danh muc da duoc sua thanh cong!\n");
            break;
        }
    }
    if (!found){
        printf("ID danh muc khong ton tai!\n");
    }
}

	

