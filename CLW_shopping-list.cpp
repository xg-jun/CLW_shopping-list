#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct ShoppingItem {
 char name[50]; // 商品名称
 int quantity; // 商品数量
 struct ShoppingItem* next; // 指向下一个节点的指针
};
struct ShoppingItem* shoppingList = NULL; // 初始化购物清单
void addItem(char itemName[], int itemQuantity) {
	struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
	newItem->next=NULL;
	strcpy(newItem->name,itemName);
 	newItem->quantity=itemQuantity;
 	newItem->next=shoppingList;
	shoppingList=newItem;	
}
void removeItem(char itemName[]) {
		 struct ShoppingItem* current = shoppingList;
		 struct ShoppingItem* previous = NULL;
		 while (current != NULL) {
		 if (strcmp(current->name, itemName) == 0) {
		 if (previous != NULL) {
		 previous->next = current->next;
		 } 
		 else {
		 shoppingList = current->next;
		 }
		 free(current);
		 break;
		 }
		 previous=current;
		 current=current->next;	 
	 } 
 }
void displayList() {
	 struct ShoppingItem* current = shoppingList;
	 printf("购物清单:\n");
	 while (current != NULL) {
	 printf("%s - 数量：%d\n", current->name, current->quantity);
	 current=current->next;
	 } 
}
void updateQuantity(char itemName[], int newItemQuantity) {
	 struct ShoppingItem* current = shoppingList;
	 while (current != NULL) {
		 if (strcmp(current->name, itemName) == 0) {
		 current->quantity=newItemQuantity;
		 break;
		 }
	 current = current->next;
	 } 
 }
void clearList() {
	 while (shoppingList != NULL) {
	 struct ShoppingItem*temp=shoppingList;
	 shoppingList=shoppingList->next;
	 free(temp);
	 } 
 }
int totalQuantity() {
 	struct ShoppingItem* current = shoppingList;
 	int total = 0;
	 while (current != NULL) {
     total+=current->quantity; 
	 current=current->next;
	 }
 	return total;
}

void findItem(char itemName[]) {
	 struct ShoppingItem* current = shoppingList;
	 printf("查找商品 \"%s\" ：\n", itemName);
	 while (current != NULL) {
		 if (strcmp(current->name, itemName) == 0) {
		 printf("%s   数量：%d\n", current->name, current->quantity);
		 return;
		 }
		 current=current->next;
	 }
	 printf("未找到商品 \"%s\"。\n", itemName);
}
void sortList() {
	struct ShoppingItem* current = shoppingList;
	struct ShoppingItem* nextItem = NULL;
	char tempName[50];
	int tempQuantity;
	while (current != NULL) {
	nextItem = current->next;
		while (nextItem != NULL) {
			 if (strcmp(current->name, nextItem->name) > 0) {
			 // 交换商品信息
			strcpy(tempName,current->name);
			strcpy(current->name,nextItem->name);
			strcpy(nextItem->name,tempName);
			
			 tempQuantity = current->quantity;
			 current->quantity = nextItem->quantity;
			 nextItem->quantity = tempQuantity;
			}
	 		nextItem = nextItem->next;
		}	
	 	current = current->next;
	} 
 }
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
	struct ShoppingItem* current = *list1;
	// 遍历到第一个购物清单的末尾
	while(current->next!=NULL){
		current=current->next;
	}
	// 将第二个购物清单连接到第一个清单的末尾
	current->next = *list2;
	*list2 = NULL; // 清空第二个购物清单的头指针，防止误用
}
void deleteItem(char itemName[], int deleteAll) {
struct ShoppingItem* current = shoppingList;
struct ShoppingItem* prev = NULL;
	 while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			if (prev == NULL) {
			 	// 如果要删除的是第一个节点
				struct ShoppingItem* temp = shoppingList;
			 	shoppingList=shoppingList->next; 
				free(temp);
				if (!deleteAll) break;
			} 
			else {
				// 如果要删除的不是第一个节点
				prev->next=current->next;
				free(current);
				current = prev->next;
				if (!deleteAll) break;
				}
		}
		else{
		 prev = current;
		 current = current->next;
		}
	}
}

int main()
{
	char Name[100];int itemQuantity,num,newItemQuantity,my_delete;
	printf("Please enter a number：\n");
	printf("1：添加商品到购物清单\n");
	printf("2：从购物清单中移除商品\n");
	printf("3：查看购物清单\n") ;
	printf("4：修改购物清单中商品的数量\n");
	printf("5：清空购物清单\n");
	printf("6: 计算购物清单中商品的总数量\n");
	printf("7：查找购物清单中的商品\n") ;
	printf("8：排序购物清单\n");
	printf("9：合并购物清单\n");
	printf("10：删除购物清单中的商品\n");
	printf("0：退出此程序\n"); 
	scanf("%d",&num);
	while(num!='0'){
		if(num==1){
			printf("请分别输入商品信息，按0停止输入 \n"); 
			while(1){
			scanf("%s ",Name);
			if(Name[0]=='0')
				break;
			scanf("%d",&itemQuantity);	
			addItem(Name,itemQuantity);				
			}

		}
		else if(num==2){
			scanf("%s",Name);
			removeItem(Name);
		}
		else if(num==3){
			displayList();
		}
		else if(num==4){
			scanf("%s %d",Name,&newItemQuantity);
			updateQuantity(Name,newItemQuantity);
		}
		else if(num==5){
			clearList();
		}
		else if(num==6){
			printf("商品总数：d\n",totalQuantity());
		}
		else if(num==7){
			scanf("%s",Name);
			findItem(Name);
		}
		else if(num==8){
			sortList();
			displayList();
		}
		else if(num==9){
			printf("该功能尚未实现，感谢您的支持，敬请期待！"); 
		}
		else if(num==10){
			printf("请分别输入需要删除购物清单中的商品名称，输入0删除其中一个，输入1删除全部信息 \n");
			scanf("%s %d",Name,&my_delete);
			deleteItem(Name,my_delete);
			displayList();
		}
		else{
			printf("感谢使用！\n");
			break; 
		}
		scanf("%d",&num);
	}
	return 0;
}

