#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Category{
	char CategoryId[10];
	char CategoryName[10];
};
struct Product{
	char productId[10];
	char cateGory[10];
	char productName[10];
	int quantity;
	int price;
};
struct Product products[100];
struct Category category[100];
int numberProduct = 0;
int numberCategory = 0;


bool checkAdminAccount(const char *email, const char *password) {
    FILE *file = fopen("admin_accounts.txt", "r");
    if (file == NULL) {
        printf("\tLoi: Khong the mo file admin_accounts.txt!\n");
        return false;
    }

    char storedEmail[100], storedPassword[100];
    while (fgets(storedEmail, sizeof(storedEmail), file) != NULL) {
        char *comma = strchr(storedEmail, ',');
        if (comma == NULL) continue;

        *comma = '\0';
        strcpy(storedPassword, comma + 1);

        storedPassword[strcspn(storedPassword, "\n")] = '\0'; 
        storedEmail[strcspn(storedEmail, "\n")] = '\0';

        if (strcmp(email, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return true; 
        }
    }

    fclose(file);
    return false; 
}
bool loginAccount() {
    char email[100], password[100];
    printf("\n\nDANG NHAP ADMIN\n");
    printf("=====================\n");
    printf("Email: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';
    printf("Password: ");
    int indexPass = 0;
    while (1){
        c = getch(); 
        if (c == '\r') { 
            break;
        } else if (c == '\b') { 
            if (indexPass > 0){
                indexPass--;
                printf("\b \b"); 
            }
        } else if (indexPass < sizeof(password) - 1) { 
            password[indexPass++] = c; 
            printf("*"); 
        }
    }
    password[indexPass] = '\0'; 

    if (checkAdminAccount(email, password)) {
        printf("\nDang nhap thanh cong!\n");
        return true;
    } else {
        printf("\nSai email hoac mat khau!\n");
        return false;
    }
}


void createAdminFileIfNotExists() {
     FILE *file = fopen("admin_accounts.txt", "r");
    if (file == NULL) { 
        file = fopen("admin_accounts.txt", "w");
        if (file != NULL) {
           
            fprintf(file, "admin@gmail.com,password123\n");
            printf("\tTao tep admin_accounts.txt thanh cong voi tai khoan mac dinh!\n");
        } else {
            printf("\tLoi: Khong the tao tep admin_accounts.txt\n");
        }
    } else {
        //printf("\tTep admin_accounts.txt da ton tai.\n");
    }
    fclose(file);
}


int validateLogin(const char *email, const char *password) {
    FILE *file = fopen("admin_accounts.txt", "r");
    if (file == NULL) {
        printf("Loi: Tep admin_accounts.txt khong ton tai.\n");
        return 0;
    }

    char line[256];
    char storedEmail[128], storedPassword[128];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%127[^,],%127s", storedEmail, storedPassword) == 2) {
            storedPassword[strcspn(storedPassword, "\n")] = '\0';
            if (strcmp(email, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }
    fclose(file);
    return 0;
}
void printCategory() {
    printf("Danh sach danh muc:\n");
    printf("+-----+-------------------+-------------------+\n");
    printf("| STT | Ma danh muc       | Ten danh muc      |\n"); 
    printf("+-----+-------------------+-------------------+\n");
    int stt=1;
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) > 0){
            printf("| %-3d | %-17s | %-17s |\n", stt++, category[i].CategoryId, category[i].CategoryName);
        }
    }
    printf("+-----+-------------------+-------------------+\n");
}

void saveCategoryToFile() {
    FILE *file = fopen("category.txt", "w");
    if (file == NULL) {
        printf("\tLoi: Khong the mo file!\n");
        return;
    }

    int hasData = 0;
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) > 0) {
            hasData = 1;
            break;
        }
    }

    if (!hasData) {
        printf("\tKhong co danh muc nao de luu!\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) > 0) {
            if (fprintf(file, "%s,%s\n", category[i].CategoryId, category[i].CategoryName) < 0) {
                printf("\tLoi: Khong the ghi vao file!\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("Danh muc da duoc luu vao file.\n");
}
void addCategory(){
	  for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) == 0) {
            
        }
    }
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) == 0) {
            printf("Them danh muc moi:\n");
            int valid = 0;
            fflush(stdin);
            while (!valid) {
                printf("ID danh muc (toi da 9 ky tu): ");
                fgets(category[i].CategoryId, sizeof(category[i].CategoryId), stdin);
                fflush(stdin);
                category[i].CategoryId[strcspn(category[i].CategoryId, "\n")] = '\0';
                if (strlen(category[i].CategoryId) == 0) {
                    printf("Loi: ID danh muc khong duoc de trong!\n");
                    continue; 
                } else if (strlen(category[i].CategoryId) > 9){
                    printf("Loi: ID danh muc qua dai, vui long nhap toi da 9 ky tu!\n");
                    continue; 
                } else{
                    int isDuplicate = 0;
                    for (int j = 0; j < i; j++){
                        if (strcmp(category[i].CategoryId, category[j].CategoryId) == 0) {
                            printf("Loi: ID danh muc da ton tai!\n");
                            isDuplicate = 1;
                            break;
                        }
                    }
                    if (!isDuplicate) {
                        valid = 1; 
                    }
                }
            }

            valid = 0;
            while (!valid) {
                printf("Ten danh muc (toi da 9 ky tu): ");
                fgets(category[i].CategoryName, sizeof(category[i].CategoryName), stdin);

                
                category[i].CategoryName[strcspn(category[i].CategoryName, "\n")] = '\0';

                
                if (strlen(category[i].CategoryName) == 0) {
                    printf("Loi: Ten danh muc khong duoc de trong!\n");
                } else if (strlen(category[i].CategoryName) > 9) {
                    printf("Loi: Ten danh muc qua dai, vui long nhap toi da 9 ky tu!\n");
                } else {
                    valid = 1; 
                }
            }

            printf("Them danh muc thanh cong!\n");
            saveCategoryToFile();
            return;
        }
    }
    printf("Danh sach danh muc da day, khong the them moi!\n");
}



void loadCategoryFromFile(){
    FILE *file = fopen("category.txt", "r");
    if (!file) {
        printf("Khong mo duoc file category.txt!\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^\n]\n", category[numberCategory].CategoryId, category[numberCategory].CategoryName) != EOF) {
        numberCategory++;
    }

    fclose(file);
}

void editCategory() {
    char x[30];
    int found = 0;
    printf("Nhap ID danh muc can sua: ");
    while (getchar() != '\n');
    fgets(x, sizeof(x), stdin);
    x[strcspn(x, "\n")] = '\0';

    for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;

            printf("Thong tin danh muc hien tai:\n");
            printf("ID: %s\n", category[i].CategoryId);
            printf("Ten: %s\n", category[i].CategoryName);

            printf("Nhap thong tin sua doi:\n");

            printf("Ten danh muc moi: ");
            fgets(category[i].CategoryName, sizeof(category[i].CategoryName), stdin);
            category[i].CategoryName[strcspn(category[i].CategoryName, "\n")] = '\0';

            printf("Sua thong tin danh muc thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay ID danh muc!\n");
    } else {
        saveCategoryToFile();
    }
}

void deleteCategory(){
	char x[30];
	int found = 0;
	char a[30];
	printf("Hay nhap ID muon xoa: ");
	while(getchar() != '\n');
	fgets(x, sizeof(x),stdin);
	x[strcspn(x, "\n")] = '\0';
	for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;
            break;
        }
    }
    if(!found) {
    	printf("Khong tim thay ID\n");
    	return;
	}
	printf("Ban co chac chan muon xoa (yes/no): ");
	fgets(a, sizeof(a),stdin);
	a[strcspn(a, "\n")] = '\0';
	
	if(strcmp(a, "yes") == 0){
		for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;
            for(int j = i; j < 10; j++){
            	category[j] = category[j + 1];
			}
		strcpy(category[9].CategoryId, "");
        strcpy(category[9].CategoryName, "");
        printf("Da xoa danh muc thanh cong!\n");
        break;
        }
    }
    saveCategoryToFile();
    printCategory();
  }
  else{
  	printf("Huy thao tac xoa\n");
  }
}

void searchCategory(){
	char a[30];
	int found = 0;
	printf("Moi ban nhap ten danh muc muon tim: ");
	getchar();
	fgets(a, sizeof(a), stdin);
	a[strcspn(a, "\n")] = '\0';
	for(int i = 0; i < 10; i++){
		if(strcmp(a, category[i].CategoryName) == 0){
			found = 1;
			printf("Da tim thay !\n");
			printf("+-----+-------------------+-------------------+\n");
    		printf("| STT | Ma danh muc       | Ten danh muc      |\n"); 
    		printf("+-----+-------------------+-------------------+\n");
    			for (int j = i; j < 9 ; j++) {
        			if (strlen(category[i].CategoryId) > 0) {
            			printf("| %-3d | %-17s | %-17s |\n", 
                   		i + 1, 
                   		category[i].CategoryId, 
                   		category[i].CategoryName);
            printf("+-----+-------------------+-------------------+\n");
			break;
          }
      }
	}
  }
      if(!found) {
      	printf("Khong tim thay!\n");
	}
}

void arrangeCategory() {
    char a[100];
    printf("Hay chon cach sap xep (tang / giam): ");
    while(getchar() != '\n');
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0';
    if (strcmp(a, "tang") == 0 || strcmp(a, "giam") == 0) {
        for (int i = 0; i < 9; i++){
            for (int j = i + 1; j < 10; j++) {
                if ((strcmp(a, "tang") == 0 && strcmp(category[i].CategoryName, category[j].CategoryName) > 0) ||
                    (strcmp(a, "giam") == 0 && strcmp(category[i].CategoryName, category[j].CategoryName) < 0)) {
                    struct Category temp = category[i];
                    category[i] = category[j];
                    category[j] = temp;
                }
            }
        }
    }
	else{
        printf("Lua chon khong hop le. Vui long thu lai.\n");
        return;
    }
    
    saveCategoryToFile();
    printCategory();
}


void menuCategory() {
    int choice;
    do {
        printf("    QUAN LY DANH MUC\n");
        printf("===========================\n");
        printf("[1]. Hien thi danh sach danh muc\n");
        printf("[2]. Them danh muc moi\n");
        printf("[3]. Chinh sua danh muc\n");
        printf("[4]. Xoa danh muc\n");
        printf("[5]. Tim kiem danh muc\n");
        printf("[6]. Sap xep danh muc\n");
        printf("[0]. Quay lai menu chinh\n");
        printf("===========================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 0:
                printf("Quay lai menu chinh.\n");
                break;
            case 1:
                printCategory();
                break;
            case 2:
                addCategory();
                break;
            case 3:
            	editCategory();
            	break;
            case 4:
            	deleteCategory();
            	break;
            case 5:
            	searchCategory();
            	break;
            case 6:
            	arrangeCategory();
            	break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void loadProductFromFile() {
     FILE *file = fopen("product.txt", "r");
    if (!file) {
        printf("Khong mo duoc file product.txt!\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", 
                  products[numberProduct].productId, 
                  products[numberProduct].productName, 
                  products[numberProduct].cateGory, 
                  &products[numberProduct].quantity, 
                  &products[numberProduct].price) != EOF) {
        numberProduct++;
    }

    fclose(file);
}

void saveProductToFile() {
    FILE *file = fopen("product.txt", "w");
    if (file == NULL) {
        printf("Loi: khong the mo file!\n");
        return;
    }
    for (int i = 0; i < numberProduct; i++) {
        fprintf(file, "%s,%s,%s,%d,%d\n", products[i].productId, products[i].productName, products[i].cateGory, products[i].quantity, products[i].price);
    }
    fclose(file);
    printf("San pham da duoc luu vao file.\n");
}

void addProduct() {
    if (numberProduct >= 100) {
        printf("Danh sach san pham da day!\n");
        return;
    }

    struct Product newProduct;

    printf("Nhap Ma SP: ");
    getchar();
    fgets(newProduct.productId, sizeof(newProduct.productId), stdin);
    newProduct.productId[strcspn(newProduct.productId, "\n")] = '\0';

    for (int i = 0; i < numberProduct; i++) {
        if (strcmp(products[i].productId, newProduct.productId) == 0) {
            printf("Loi: Ma san pham da ton tai!\n");
            return;
        }
    }

    printf("Nhap Ten SP: ");
    fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
    newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';

    printf("Nhap Ma Danh Muc: ");
    getchar();
    fgets(newProduct.cateGory, sizeof(newProduct.cateGory), stdin);
    newProduct.cateGory[strcspn(newProduct.cateGory, "\n")] = '\0';

    int validCategory = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(category[i].CategoryId, newProduct.cateGory) == 0) {
            validCategory = 1;
            break;
        }
    }
    if (!validCategory) {
        printf("Loi: Ma danh muc khong ton tai!\n");
        return;
    }

    printf("Nhap So Luong: ");
    scanf("%d", &newProduct.quantity);
    getchar();
    if (newProduct.quantity <= 0) {
        printf("Loi: So luong khong hop le!\n");
       	getchar();
        return;
    }

    printf("\tNhap Gia: ");
    scanf("%d", &newProduct.price);
    getchar();
    if (newProduct.price <= 0) {
        printf("Loi: Gia khong hop le!\n");
        return;
    }

    products[numberProduct] = newProduct;
    numberProduct++;

    printf("Them san pham thanh cong!\n");
    saveProductToFile();
    return;
}


void printProduct() {
     if (numberProduct == 0) {
        printf("\tDanh sach san pham rong!\n");
        return;
    }
    printf("+-----+----------+--------------------+------------+----------+----------+\n");
    printf("| STT | Ma SP    | Ten San Pham       | Danh Muc   | So Luong | Gia      |\n");
    printf("+-----+----------+--------------------+------------+----------+----------+\n");
    for (int i = 0; i < numberProduct; i++) {
        printf("| %-3d | %-8s | %-18s | %-10s | %-8d | %-8d |\n", 
               i + 1, 
               products[i].productId, 
               products[i].productName, 
               products[i].cateGory,
               products[i].quantity, 
               products[i].price);
    }
    printf("+-----+----------+--------------------+------------+----------+----------+\n");
}
 
void menuProduct() {
    int choice;
    do {
        printf("    PRODUCT MANAGEMENT MENU\n");
        printf("===========================\n");
        printf("[1]. Hien thi danh sach san pham\n");
        printf("[2]. Them san pham\n");
        printf("[3]. Sua thong tin san pham\n");
        printf("[4]. Xoa san pham\n");
        printf("[5]. Tim kiem san pham theo ten\n");
        printf("[0]. Quay lai menu chinh\n");
        printf("===========================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("\tQuay lai menu chinh.\n");
                break;
            case 1:
                printProduct();
                break;
            case 2:
                addProduct();
                break;
            default:
                printf("\tLua chon khong hop le!\n");
        }
    } while (choice != 0);
}


void menuAdmin(){
	int choice;
	do{
		printf("	ADMIN MENU\n");
		printf("===========================\n");
		printf("[1]. Quan ly danh muc\n");
		printf("[2]. Quan ly san pham\n");
		printf("[0]. Exit \n");
		printf("===========================\n");
		printf("Enter the choice: ");
		scanf("%d", &choice);
		
		switch (choice){
			case 0:
				printf("Quay lai menu chinh\n");
				break;
			case 1:
				menuCategory();			
				break;
			case 2:
				menuProduct();
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				printf("Lua chon khong hop le!\n");
		}
	}while (choice != 0);
}
int main() {
	for (int i = 0; i < 10; i++) {
        category[i].CategoryId[0] = '\0';
        category[i].CategoryName[0] = '\0';
    }
    createAdminFileIfNotExists();
    loadCategoryFromFile();
    loadProductFromFile();

    int choice;
    do {
        printf("****** Store Management System Using C ******\n");
        printf("\n");
        printf("  CHOOSE YOUR ROLE\n");
        printf("=======================\n");
        printf("[1]. Admin\n");
        printf("[2]. Customer\n");
        printf("[0]. Exit the program\n");
        printf("=======================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { 
            printf("Dau vao khong hop le vui long nhap so.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 0:
                printf("Ban da thoat khoi chuong trinh. \n");
                break;
            case 1:
                if (loginAccount()) {
                    menuAdmin();
                } else {
                    printf("Dang nhap khong thanh cong vui long thu lai.\n");
                }
                break;
            case 2:
                
                break;
        }
    } while (choice != 0);

    saveCategoryToFile();
    saveProductToFile();

    return 0;
}
