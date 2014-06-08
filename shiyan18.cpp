/*
   自己用C 语言实现的通用链表
   能实现插入删除等操作
   */
#include<stdio.h>
#include<stdlib.h>
struct list_head
{
	struct list_head *next;
	struct list_head *prev;
};
void init_list_head(struct list_head *list)
{
	list->next=list;
	list->prev=list;
}
void list_add_insert(struct list_head *new_list,struct list_head *prev,struct list_head *next)
{//this is a proc to insert a node between prev and next
	new_list->next=prev->next;
	new_list->prev=next->prev;
	prev->next=new_list;
	next->prev=new_list;
}
void list_add_head(struct list_head *head,struct list_head *new_list)
{//This is a proc to insert a node between list head and list->next
	list_add_insert(new_list,head,head->next);
}
void list_add_tail(struct list_head *head,struct list_head *new_list)
{//This is a proc to insert a node in the tail of this list that is to say
	//insert a node between head and head->prev just because this a circular linked list
	list_add_insert(new_list,head->prev,head);
}
void list_del_between(struct list_head *prev ,struct list_head *next)
{//This is a proc to delete the nodes between prev ans next,just two statement,so easy
	prev->next=next;
	next->prev=prev;
}
void list_del_now(struct list_head *entry)
{//This a proc to delete entry just delele all node between entry->prev and entry->next
	//it's OK equal to delete entry ,yes just easy
	list_del_between(entry->prev,entry->next);
}
void list_remove_chain(struct list_head *ch,struct list_head *ct)
{//this is a proc to remove the node between ch and ct but ct and ch included
	list_del_between(ch->prev,ct->next);
}
void list_add_chain_head(struct list_head *ch,struct list_head *ct,struct list_head *head)
{//This is a proc to insert the node between ch and ct int head to head<->head->next
	head->next->prev=ct;
	ct->next=head->next;
	ch->prev=head;
	head->next=ch;
}
void list_add_chain_tail(struct list_head *ch,struct list_head *ct,struct list_head *head)
{//This just a proc to insert the node between ch and ct int head->prev<->head just the tail OK !
	head->prev->next=ch;
	ch->prev=head->prev;
	ct->next=head;
	head->prev=ct;
}
int list_empty(struct list_head *list)
{//Just judge if the list empty or not attention this is a circular linked list
	return list->prev==list->next;
	//you can write this list->next==list that's OK 
}
//The aim of this define to get the offset of member in struct in type 
#define offset(type,member) ((unsigned int)&((type *)0->member))
//to get the adress of struct type
#define container_of(ptr,type,member) ({typeof(((type*)0)->member)*__mptr=ptr;(type*)((char*)__mptr-offset(type,number));}
		// same as up
#define list_for_ebtry(ptr,type,member) container(ptr,type,member);

		int main()
		{

		struct list_head *head=(struct list_head *)(malloc(sizeof(struct list_head)));
		init_list_head(head);
		printf("hello world\n");
		return 0;
}
