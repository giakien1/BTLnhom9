#include<stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
typedef struct Date{
	int day;
	int month;
	int year;
} date;
typedef struct Room{
	int id;
	char name[50];
	char address[50];
	char type[20]; //Single Room, Twin Room, Double Room, Triple Room, Quad Room
	int price;
	char contact[20]; //email / hotline
	char state[20];
	date start; //ngay bat dau cho thue
	date end; //ngay ket thuc thoi gian thue
}room;
void drawLine(int n){
	printf ("\n");
	for (int i=0;i<n;i++) printf ("_");
	printf ("\n");
}
int IDMAX (room a[], int n) {
    int idMax = 0;
    if (n > 0) {
        idMax = a[0].id;
        for(int i = 0;i < n; i++) {
            if (a[i].id > idMax) {
                idMax = a[i].id;
            }
        }
    }
    return idMax;
}
void showRoom(room a[], int n) {
    drawLine(100);
    printf("\nSTT\tID\tTen Khach san\tDia chi\t\tLoai phong\tGia phong/dem\tLien he Dat phong\tTrang thai phong\tNgay cho thue\tNgay het han");
    for(int i = 0; i < n; i++) {
        // in phong thu i ra man hinh
        printf("\n %d", i + 1);
        printf("\t%d", a[i].id);
        printf("\t%s", a[i].name);
        printf("\t%s", a[i].address);
        printf("\t\t%s", a[i].type);
        printf("\t%d", a[i].price);
    	printf("\t\t%s", a[i].contact);
    	printf("\t\t%s", a[i].state);
        printf("\t%d/%d/%d", a[i].start.day, a[i].start.month, a[i].start.year);
		printf("\t\t%d/%d/%d", a[i].end.day, a[i].end.month, a[i].end.year);
    }
    drawLine(100);
}
void roomType(){
	printf ("\n( 1-Single Room \t2-Twin Room \t3-Double Room \t4-Triple Room \t5-Quad Room )\n");
}
void roomInforInput(room &newRoom,int id){
	newRoom.id=id;
	printf ("Nhap ten Khach san : ");  fflush(stdin); gets (newRoom.name);
	printf ("Nhap dia chi phong : "); gets(newRoom.address);roomType();
	printf ("Nhap loai phong : ");fflush(stdin); gets(newRoom.type); 
	printf ("Nhap gia cho phong / dem (nghin VND): "); scanf ("%d",&newRoom.price);
	printf ("Nhap email/sdt : "); fflush(stdin);gets(newRoom.contact);
	strcpy(newRoom.state,"Chua dat");
	newRoom.start.day = 0; newRoom.start.month = 0; newRoom.start.year = 0;
	newRoom.end.day=0; newRoom.end.month=0; newRoom.end.year=0;
}
void inputRoom(room a[], int id, int n) {
    drawLine(60);
    printf("\n Nhap phong: \n");
    roomInforInput(a[n], id);
    drawLine(60);
}
int deleteRoom(room a[], int id, int n){
	int found = 0;
    for(int i = 0; i < n; i++) {
        if (a[i].id == id) {
            found = 1;
            drawLine(60);
            for (int j = i; j < n; j++) {
                a[j] = a[j+1];
            }
            printf ("\n Da xoa phong co ID = %d",id);
            drawLine(60);
            break;
        }
    }
    if (found == 0) {
        printf("\n Phong co ID = %d khong ton tai.", id);
        return 0;
    } else {
        return 1;
    }
}
void updateRoom(room &newRoom) {
	strcpy(newRoom.state,"Da dat");
	printf ("Nhap ngay bat dau thue (dd/mm/yy) : "); scanf("%d%d%d",&newRoom.start.day,&newRoom.start.month,&newRoom.start.year);
	printf ("Nhap ngay ket thuc (dd/mm/yy) : "); scanf("%d%d%d",&newRoom.end.day,&newRoom.end.month,&newRoom.end.year);
}
void booking(room a[], int id, int n) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if (a[i].id == id) {
            found = 1;
            drawLine(60);
            printf ("\n Ban muon dat phong co ID = %d",id);
            updateRoom(a[i]);
            printf ("\nBan da dat phong thanh cong!");
            drawLine(60);
            break;
        }
    }
    if (found == 0) {
        printf("\n Phong co ID = %d khong ton tai.", id);
    }
}
void nameFind(room a[], char ten[], int n) {
    room arrayFound[MAX];
    char tenPhong[30];
    int found = 0;
    for(int i = 0; i < n; i++) {
        strcpy(tenPhong, a[i].name);
        if(strstr(strupr(tenPhong), strupr(ten))) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showRoom(arrayFound, found);
}
void desFind(room a[], char ten[], int n) {
    room arrayFound[MAX];
    char tenPhong[30];
    int found = 0;
    for(int i = 0; i < n; i++) {
        strcpy(tenPhong, a[i].address);
        if(strstr(strupr(tenPhong), strupr(ten))) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showRoom(arrayFound, found);
}
void bookingHistory(room a[], int n) {
    room arrayFound[MAX];
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(strstr(a[i].state, "Da dat")) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showRoom(arrayFound, found);
}
void writeNum(char fileNum[]){
	FILE * f;
	f=fopen(fileNum,"w");
	int num;
	fprintf (f,"%d",num);
}
int takeFile(room a[], char fileNum[]) {
    FILE * f;
    int i = 0;
    int num;
    f = fopen (fileNum, "r");   
    fscanf(f, "%d", &num);
    i=num;
	i+=1;
    printf (" So luong phong co san la: %d\n\n",i);
  
    fclose (f);
    return i;
}
void readFile(room a[], char fileName[], int n){
	FILE * fp;
    int i = 0;
    fp = fopen (fileName, "rb");
    fread(&n, sizeof(n), 1, fp);
	for(int i=0; i<n; i++){
		fread(&a[i], sizeof(room), 1, fp);
		}
    fclose (fp);
}
void appendFile(room a[], int n, char fileName[]) {
    FILE * fp;
    fp = fopen (fileName,"wb");
    fwrite(&n, sizeof(n), 1, fp);
	for(int i=0; i<n; i++){
		fwrite(&a[i], sizeof(room), 1, fp);
	}
    fclose (fp);
}
void pressAnyKey() {
    printf ("\n\nBam phim bat ky de tiep tuc...");
    getch();
    system("cls");
}
void menu(){
	char fileNum[]="TheAmountOfRoom.txt";
	char fileName[] = "HotelRoomListTest.bin";
    room arrayRoom[MAX];
    int roomTotal = 0;
    int idCount = 0;
    roomTotal = takeFile(arrayRoom, fileName);
    readFile(arrayRoom,fileName,roomTotal);
    idCount = IDMAX (arrayRoom, roomTotal);
	int choice; int purpuse;
	mainMenu: 
	printf ("           UNG DUNG DAT PHONG KHACH SAN \n");
    printf ("**********************MAIN MENU************************\n");
    printf ("**  1. Cho thue phong                                **\n");
	printf ("**  2. Tim phong 	                             **\n");
    printf ("**  3.Xem lich su dat phong                          **\n");
    printf ("*******************************************************\n");
	printf ("\nChon so tren ban phim: ");
	do{
	scanf ("%d",&purpuse);
	if (purpuse>3 || purpuse < 1) printf ("Khong co chuc nang nay! Hay chon lai: ");
	} while (purpuse<1||purpuse>3);
	if (purpuse==1){
	do { 
        printf ("               DANG PHONG LEN UNG DUNG \n");
        printf ("*************************MENU**************************\n");
        printf ("**  1. Dang phong cua ban                            **\n");
        printf ("**  2. Xoa phong cua ban                             **\n");
        printf ("**  3. Tro lai MAIN MENU                             **\n");
        printf ("**  0. Thoat ung dung                                **\n");
        printf ("*******************************************************\n");
        printf ("Nhap tuy chon: ");
        scanf ("%d",&choice);
        system("cls");
        switch(choice){
            case 1:
                printf ("\n1.Dang phong cua ban.");
                idCount++;
                inputRoom(arrayRoom, idCount, roomTotal);
                printf("\nThem phong thanh cong!");
                appendFile(arrayRoom, roomTotal, fileName);
                roomTotal++;
                pressAnyKey();
                break;
            case 2:
                if(roomTotal > 0) {
                    int id;
                    printf ("\n2. Xoa phong cua ban.");
                    printf ("\n Nhap ID phong cua ban: "); scanf ("%d",&id);
                    if (deleteRoom(arrayRoom, id, roomTotal) == 1) {
                        printf("\nPhong cua ban da bi xoa da bi xoa.");
                        roomTotal--;
                    }
                }else{
                    printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
                break;
            case 3:
                printf ("\nQuay tro lai MAIN MENU!\n");
                goto mainMenu;
            case 0:
                printf ("\nBan da chon Thoat ung dung !");
                getch();
            default:
                printf ("\nKhong co chuc nang nay!");
                printf ("\nHay chon chuc nang trong hop menu.");
                pressAnyKey();
                break;
        }
        }
        while (choice !=0);
    }
    else if (purpuse==2){
	do { 
        printf ("                 TIM PHONG KHACH SAN \n");
        printf ("*************************MENU**************************\n");
        printf ("**  1. Danh sach cac phong dang co tren ung dung     **\n");
        printf ("**  2. Tim phong theo ten Khach San                  **\n");
        printf ("**  3. Tim phong theo dia chi muon den               **\n");
        printf ("**  4. Dat phong                                     **\n");
        printf ("**  5. Tro lai MAIN MENU                             **\n");
        printf ("**  0. Thoat ung dung                                **\n");
        printf ("*******************************************************\n");
        printf ("Nhap tuy chon: ");
        scanf ("%d",&choice);
        switch(choice){
            case 1:
                if(roomTotal > 0){
                    printf ("\n1.Danh sach cac phong dang co tren ung dung.");
                    showRoom(arrayRoom, roomTotal);
                }else{
                    printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
                break;
            case 2:
                if(roomTotal > 0) {
                    printf ("\n2. Tim phong theo ten Khach San.");
                    char strTen[30];
                    printf ("\nNhap ten Khach San ban muon tim: ");fflush(stdin); gets(strTen);
                    nameFind(arrayRoom, strTen, roomTotal);
                }else{
                    printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
                break;
            case 3:
                if(roomTotal > 0) {
                    printf ("\n3. Tim phong theo dia chi muon den.");
                    char strTen[30];
                    printf ("\nNhap dia chi ban muon den: "); fflush(stdin); gets(strTen);
                    desFind(arrayRoom, strTen, roomTotal);
                }else{
                    printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
                break;
            case 4:
                if(roomTotal > 0) {
                    int id;
                    printf ("\n4. Dat phong.");
                    printf ("\n Nhap ID phong ban muon dat: "); scanf ("%d",&id);
                    booking(arrayRoom, id, roomTotal);
                }else{
                    printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
                break;
            case 5:
                printf ("\nQuay tro lai MAIN MENU!\n");
                goto mainMenu;
            case 0:
                printf ("\nBan da chon Thoat ung dung!");
                getch();
            default:
                printf ("\nKhong co chuc nang nay!");
                printf ("\nHay chon chuc nang trong hop menu.");
                pressAnyKey();
                break;
        }
        }
        while (choice != 0);
    }
    else {
    	do { 
        printf ("              XEM CAC PHONG DA DUOC DAT \n");
        printf ("*************************MENU**************************\n");
        printf ("**  1. Xem cac phong da duoc dat                     **\n");
        printf ("**  2. Tro lai MAIN MENU                             **\n");
        printf ("**  0. Thoat ung dung                                **\n");
        printf ("*******************************************************\n");
        printf ("Nhap tuy chon: ");
        scanf ("%d",&choice);
        switch(choice){
            case 1:
            if(roomTotal > 0){
                printf ("\n3.Xem lich su dat phong :\n");
                bookingHistory(arrayRoom, roomTotal);
            }else{
                printf ("\nDanh sach phong trong!");
                }
                pressAnyKey();
            case 2:
                printf ("\nQuay tro lai MAIN MENU!\n");
                goto mainMenu;
            case 0:
                printf ("\nBan da chon Thoat ung dung !");
                getch();
            default:
                printf ("\nKhong co chuc nang nay!");
                printf ("\nHay chon chuc nang trong hop menu.");
                pressAnyKey();
                break;
        }
        }
        	while (choice != 0);
	}
	writeNum(fileNum);
}
int main(){
    menu();
}
