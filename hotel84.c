#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX 10

char gch(){
	char ch = getchar();
	getchar();
	return tolower(ch);
}
void clear(){system("clear");}

int main();
void cmd_view();
void cmd_new();
void cmd_buy();
void cmd_modifyBill();
void cmd_help();
void cmd_print();
typedef struct customerData
{
	int roomNo, begin, end, currentBill;
	int purchase;
	char contact[12];
	char name[25];

} customerData;

char cmd[10];
char fname[] = {"customerData.dat"};
int rooms[600] = {0};

void displayAll(){
	FILE *fp;
	customerData data;

	fp = fopen(fname,"rb");
	printf("ROOM\t");
	printf("NAME\t\t");
	printf("CONTACT\n");
	
	while(1){

		fread(&data,sizeof(data),1,fp);
		if (feof(fp))
		{
			break;
		}
		printf("%d\t",data.roomNo);
		printf("%s\t\t",data.name);
		printf("\t%s\n",data.contact);
	}
	getchar();
	main();
}

void modifyBill(int roomNo, int price){
	FILE *fp,*fp1;
	customerData t,t1;
	int found = 0;

	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}
		if(t.roomNo==roomNo)
		{
			found=1;
			t.currentBill += price;
			t.purchase++;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
		{
			fwrite(&t,sizeof(t),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	if(found==0)
	{
		printf("\nSorry No Record Found\n\n");
	}
	else
	{
		fp=fopen(fname,"wb");
		fp1=fopen("temp.dat","rb");

		while(1)
		{
			fread(&t,sizeof(t),1,fp1);

			if(feof(fp1))
			{
				break;
			}
			fwrite(&t,sizeof(t),1,fp);
		}

	}
	fclose(fp);
	fclose(fp1);
}

int allot(int floor){
	srand(time(0));
	int num = rand()%100;
	if (!(rooms[(floor*100)+num]))
	{
		return ((floor*100)+num);
	}
	else{
		allot(floor);
	}
}

int buy_menu2(char bm1, char bm2){
	int tmp;
	if (bm2 == 'x'){
		cmd_buy();
	}
	else{
		if (bm1 == 'd'){
			if (bm2 == 'd'){
				tmp = 500;
			}
			else if (bm2 == 'r'){
				tmp = 560;
			}
			else if (bm2 == 'v'){
				tmp = 480;
			}
			else if (bm2 == 'w'){
				tmp = 780;
			}
		}
		else if (bm1 == 'e'){
			if (bm2 == 'a'){
				tmp = 8000;
			}
			else if (bm2 == 'b'){
				tmp = 4500;
			}
			else if (bm2 == 'r'){
				tmp = 9000;
			}
			else if (bm2 == 'i'){
				tmp = 5500;
			}
		}
		else if (bm1 == 'c'){
			if (bm2 == 'i'){
				tmp = 780;
			}
			else if (bm2 == 'j'){
				tmp = 1250;
			}
			else if (bm2 == 's'){
				tmp = 1700;
			}
			else if (bm2 == 'g'){
				tmp = 2400;
			}
		}
	}
	return tmp;
}
void buy_menu1(int roomNo, char bm1){
	int price = 0;
	if (bm1 == 'c'){
		printf("\n\t(i)Indian\t(j)Japanese\t(s)Spanish\t(g)Global Mix\t(x)Back\n");
	}
	else if (bm1 == 'd'){
		printf("\n\t(b)Beer\t(r)Rum\t(v)Vodka\t(w)Whiskey\t(x)Back\n");
	}
	else if (bm1 == 'e'){
		printf("\n\t(a)American\t(b)Brazilian\t(i)Indian\t(r)Russian\t(x)Back\n");
	}
	else if (bm1 == 'x'){
		cmd_buy();
	}
	else{
		printf("\nPlease enter a valid command !\n");
		getchar();
		cmd_buy();
	}
	char bm2 = gch();
	int tmp = buy_menu2(bm1,bm2);
	price += tmp;
	modifyBill(roomNo,price);
}

void cmd_buy(int roomNo){
	if (!(rooms[roomNo]))
	{
		printf("\nRoom EMPTY !\n");
		getchar();
		main();
	}
	else{
		printf("Purchase :\n\t(c)Cuisine\t(d)Drinks\t(e)Escort\t(x)Back\n");
		int bm1 = gch();
		buy_menu1(roomNo, bm1);
	}	
}
void roomDisplay(int roomNo){
	FILE *fp;
	customerData dat;
	int found=0;

	fp = fopen(fname,"rb");

	while(1)
	{
		fread(&dat,sizeof(dat),1,fp);
		if(feof(fp))
		{
			break;
		}
		if(dat.roomNo==roomNo)
		{
			found=1;
			printf("\n\t\tROOM : %d",dat.roomNo);
			printf("\n\t\tSTATUS : BOOKED");
			printf("\n\tby\tNAME : %s",dat.name);
		}
	}
	if(found==0){
		printf("\nThe Room is empty.\n");
	}
	fclose(fp);
}
void makeBill(int roomNo){
	clear();
	int found = 0;
	FILE *fp;
	customerData dat;

	fp = fopen(fname,"rb");
	while(1){
		fread(&dat,sizeof(dat),1,fp);

		if (feof(fp)){
			break;
		}
		if(dat.roomNo==roomNo){
			found = 1;
			printf("\n\n\n\n\n\n");
			printf("\t\t\tThe Bates Motel\n");
			printf("\t\tNear the Cervix Area, Orlando\n");
			printf("\tNAME :\t\t%s\n\tROOM :\t\t%d\n", dat.name, roomNo);
			printf("\tCONTACT :\t%s\n", dat.contact);
			printf("\tBILL :\t\t%d\n",dat.currentBill);
			printf("\t\t\tHave a Good Day\n\n\n");
			printf("\t(p)Print\t(x)Back\n");
		}
	}
	if (found == 0){
		printf("\nThe Room is empty.\n");
	}

	fclose(fp);
	char prp = gch();
	cmd_print();
}

void view_menu2(char vm1, char vm2){
	int room;
	if (vm2 == 'x'){
		cmd_view();
	}
	else{
		if (vm1 == 'a'){
			if (vm2 == 'a'){
				displayAll();
			}
			else if (vm2 == 'r'){

			}
		}
		/*else if (vm1 == 'b'){
			if (vm2 == 'd'){
			}
			else if (vm2 == 'n'){
			}
			else if (vm2 == 'r'){
			}
		}*/
		else if (vm1 == 'l'){
			if (vm2 == 'd'){
			}
			else if (vm2 == 'w'){
			}
			else if (vm2 == 'm'){
			}
			else if (vm2 == 'y'){
			}
		}
		else if (vm1 == 'r'){
			if (vm2 == 'f'){
				int floor;
				printf("\nFloor : ");
				scanf("%d",&floor);getchar();
				floor = floor*100;
				int tmp = floor;
				printf("\nBooked Rooms : \n");
				while(tmp < (floor+100)){
					if (rooms[tmp] == 1)
					{
						printf("%d\n",tmp);
					}
					++tmp;
				}
			}
			else if (vm2 == 'n'){
				int room;
				printf("\nRoom No : ");
				scanf("%d",&room);getchar();
				roomDisplay(room);
			}
		}
		getchar();
		cmd_view();
	}
}

void view_menu1(char vm1){
	char vm2;
	
	if (vm1 == 'a'){
		printf("\n\t(a)All\n\tby\t(r)Room\t(x)Back\n");
	}
	else if (vm1 == 'b'){
		printf("\nNo past customers !\n");
		//printf("\n\tby\t(d)Date\t(n)Name\t(r)Room\t(x)Back\n");
	}
	else if (vm1 == 'l'){
		printf("\n\t(t)Today\t(w)this Week\t(m)this Month\t(y)this Year\t(x)Back\n");
	}
	else if (vm1 == 'r'){
		printf("\n\t(f)by Floor\t(n)by roomNo\t(x)Back\n");
	}
	else if (vm1 == 'x'){
		main();
	}
	else{
		printf("\nPlease enter a valid command !\n");
		getchar();
		cmd_view();
	}
	vm2 = gch();
	view_menu2(vm1, vm2);
}

void cmd_view(){
	clear();
	printf("\nVIEW : \n\t(a)Present Customer Data\n\t(b)Past Customer Data\n\t(l)Ledger\n\t(r)Rooms Matrix\n\t(x)Back\n");
	char vm1 = gch();
	view_menu1(vm1);
}

void makePass(int roomNo){
	clear();
	int found = 0;
	FILE *fp;
	customerData dat;

	fp = fopen(fname,"rb");
	while(1){
		fread(&dat,sizeof(dat),1,fp);

		if (feof(fp)){
			break;
		}
		if(dat.roomNo==roomNo){
			found = 1;
			printf("\n\n\n\n\n\n");
			printf("\t\t\t\tThe Bates Motel\n");
			printf("\t\t\tNear the Cervix Area, Orlando\n");
			printf("\tNAME : %s\t\t\t\t\t\tROOM : %d\n", dat.name, roomNo);
			printf("\tCONTACT : %s\n", dat.contact);
			printf("\t\t\t\tHave a Good Day\n\n\n");
			printf("\t(p)Print\t(x)Back\n");
		}
	}
	if (found == 0){
		printf("\nThe Room is empty.\n");
	}

	fclose(fp);
	char prp = gch();
	cmd_print();
}

void print_menu1(char pm1){
	int billRoom, passRoom;
	if (pm1 == 'b'){
		printf("\nRoom : ");
		scanf("%d",&billRoom);getchar();
		makeBill(billRoom);
	}
	else if (pm1 == 'r'){
		printf("\nRoom : ");
		scanf("%d",&passRoom);getchar();
		makePass(passRoom);
	}
	else if (pm1 == 'x'){
		main();
	}
	else{
		printf("\nPlease enter a valid command !\n");
		getchar();
		cmd_print();
	}
}

void cmd_print(){
	clear();
	printf("PRINT : \n\t(b)Bill\t(r)Room Pass\t(x)Back\n");
	char pm1 = gch();
	print_menu1(pm1);
}

void cmd_help(){
	clear();
	printf("\nBasic Hotel Management program\n\tby Manu Ojha\n");
	printf("\nCOMMANDS\n\tnew - Add a new entry to the ledger\n");
	printf("\n\tprint - Print a Bill, or room pass\n");
	printf("\n\tbuy - Additional purchases/transactions\n");
	printf("\n\tview - Look at the room matrix, customerData, bills, etc.\n");
	printf("\n\thelp - stuck somewhere?\n");
	getchar();
	fflush(stdin);
	main();
}

void add(char *name, char *contact, int room, int money){
	FILE *fp;
	customerData c1;

	fp = fopen(fname,"ab");
	strcpy(c1.name, name);
	strcpy(c1.contact, contact);
	c1.roomNo = room;
	c1.currentBill = money;
	c1.purchase = 0;

	fwrite(&c1,sizeof(c1),1,fp);

	fclose(fp);
}

void getDate(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int year = tm.tm_year + 1900;
	int month = tm.tm_mon + 1;
	int date = tm.tm_mday;
}

void cmd_new(){
	clear();
	int floor, rn, days;
	char room;
	printf("NEW : \n");
	char name[25]; char contact[12];
	printf("\nCustomer Name : ");
	fgets(name, 25, stdin);
	printf("\nContact Number : ");
	fgets(contact, 12, stdin);
	printf("\nHow many days stay : ");
	scanf("%d", &days);getchar();
	days = days*5000;
	printf("\nRoom Number : (a) Auto\t(b) Manual\n");
	room = gch();
	if (room == 'b'){
		printf("\nFloor : ");
		scanf("%d",&floor);getchar();
		printf("\nRoom No : ");
		scanf("%d",&rn);getchar();
		rn = ((floor*100)+rn);
		printf("\nAlloted Room : %d", rn);
	}
	else if (room == 'a')
	{
		printf("\nFloor : ");
		scanf("%d",&floor);getchar();
		rn = allot(floor);
		printf("\nAlloted Room : %d", rn);
	}
	else{
		printf("Please enter a valid command !\n");
		getchar();
		cmd_new();
	}
	rooms[rn] = 1;
	add(name,contact,rn, days);
	gch();
	fflush(stdin);
	main();
}

void checkCommand(char *cmd){
	if (strcmp(cmd,"help\n")==0){
		cmd_help();
	}
	else if (strcmp(cmd,"new\n")==0){
		cmd_new();
	}
	else if (strcmp(cmd,"print\n")==0){
		cmd_print();
	}
	else if (strcmp(cmd,"buy\n")==0){
		int tmp;
		printf("Room No : \n");
		scanf("%d", &tmp);getchar();
		cmd_buy(tmp);
	}
	else if (strcmp(cmd,"view\n")==0){
		cmd_view();
	}
	else{
		printf("Please enter a valid command !\nPress Enter...\n");
		fflush(stdin);
		getchar();
		main();
	}
}

int main(){
	clear();
	for (int i = 0; i < 99; ++i){
		printf("_");
	}
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("\n\t\t\t\t\tWelcome to The Bates Motel\n");
	printf("\nPress\thelp anytime for info\t\t\t\t\t\t\t%d-%02d-%02d %02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fflush(stdin);

	fgets(cmd, MAX, stdin);
	checkCommand(cmd);
	return 0; 
}
