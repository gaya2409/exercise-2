#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 6

typedef struct Worker {
	unsigned long ID;
	char* name;
	unsigned long salary;

	union year {
		char hebrew[SIZE];
		unsigned long international;
	} *y;
}myworker;

typedef struct WorkerList
{
	myworker * data;
	struct WorkerList* next;
} WorkerList;

myworker* CreateWorker(unsigned long id, char* name, unsigned long salary, union year* myyear);
void printworker(myworker* worker);
WorkerList * addWorker(WorkerList *head, myworker * w);
int index1(WorkerList *head, long unsigned id);
int index2(WorkerList *head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList *head);
void update_worker(WorkerList *head, float percent);
WorkerList *reverse(WorkerList *head);
void freeWorkers(WorkerList *head);

void main() {
	int yeartype = 0;
	//test data
	
	

	myworker* w1 = CreateWorker(4545, "tal", 10, "2020", yeartype);
	printworker(w1, yeartype);
	myworker* w2 = CreateWorker(78786, "or", 50, "2021", yeartype);
	printworker(w2, yeartype);
	myworker* w3 = CreateWorker(456456, "yona", 10000, "vazhat", yeartype);
	printworker(w3, yeartype);
	myworker* w4 = CreateWorker(53534, "tan", 9999, "alefbe", yeartype);
	printworker(w4, yeartype);
	myworker* w5 = CreateWorker(11234, "paamona", 158, "tash", yeartype);
	printworker(w5, yeartype);

	WorkerList * list;
	addWorker(list, w1);
	addWorker(list, w2);
	addWorker(list, w3);
	addWorker(list, w4);
	addWorker(list, w5);

	printf("%s -> %d\n", w1->name, index1(list, w1));
	printf("%s -> %d\n", w2->name, index1(list, w2));
	printf("%s -> %d\n", w4->name, index2(list, w4));
	printf("%s -> %d\n", w5->name, index2(list, w5));

	deleteWorstWorker(list);
	printf("%s -> %d\n", w1->name, index1(list, w1));

	update_worker(list, 30);
	printf("%s -> %d\n", w2->name, w2->salary);
	printf("%s -> %d\n", w3->name, w3->salary);
	printf("%s -> %d\n", w4->name, w4->salary);
	printf("%s -> %d\n", w5->name, w5->salary);

	reverse(list);
	printf("%s -> %d\n", w2->name, index1(list, w2));
	printf("%s -> %d\n", w3->name, index1(list, w3));
	printf("%s -> %d\n", w4->name, index1(list, w4));
	printf("%s -> %d\n", w5->name, index1(list, w5));

	freeWorkers(list);
	printf("%d\n", list);

	free(w2);
	free(w3);
	free(w4);
	free(w5);
}

/*
yeartype - 0 for heb, 1 for international
*/
myworker* CreateWorker(unsigned long id, char* name, unsigned long salary, union year* myyear, int yeartype) {

	myworker* worker;
	worker = (myworker*)malloc(sizeof(myworker));
	worker->ID = id;
	worker->name = name;
	worker->salary = salary;
	if (yeartype) worker->y = myyear->international;
	else worker->y = myyear->hebrew;
	return worker;
}

void printworker(myworker* worker, int yeartype) {

	printf("the details about the worker:\n id:%u \n name:%s\n salary: %u \n",
		worker->ID, worker->name, worker->salary);
	if (yeartype) printf("year: %d", worker->y->international);
	else printf(" year: %s\n", worker->y->hebrew);
}

WorkerList * addWorker(WorkerList *head, myworker * w) {	WorkerList *new_list_member = (WorkerList*)malloc(sizeof(WorkerList));	if (!new_list_member) {		exit(0);	}	new_list_member->data = w;	if (!head) {		head = new_list_member;		return head;	}	WorkerList* bobby = head;	while (bobby) {		if (bobby->next) {			if (bobby->data->salary > w->salary) {				new_list_member->next = bobby;				bobby = new_list_member;				break;			}			bobby = bobby->next;		}		else {			bobby->next = new_list_member;			break;		}	}	return head;}

int index1(WorkerList *head, long unsigned id) {

	int count = 1;
	while (head) {
		if (head->data->ID == id) {

			return count;
		}
		count++;
		head = head->next;
	}
	return -1;
}

int index2(WorkerList *head, long unsigned id) {

	if (head) return -1;
	if (head->data->ID == id && head->next) return 0;
	if (head->data->ID == id) return 1;
	int res = index2(head->next, id);
	return res == -1 ? -1 : res + 1;
}

WorkerList* deleteWorstWorker(WorkerList *head) {	if (!head) return NULL;	if (!head->next) {		free(head);		return NULL;	}	else {		int * tmp = head;		head = head->next;		free(tmp);	}}// assuming percent is given in the form of 100=100%void update_worker(WorkerList *head, float percent) {
	while (head) {		head->data->salary *= (100 + percent) / 100;		head = head->next;	}}WorkerList *reverse(WorkerList *head) {
	if (!head) return NULL;
	if (!head->next) return head;
	WorkerList *prev = reverse(head->next);	prev->next = head;}void freeWorkers(WorkerList *head) {	int * tmp;	while (!head) {		tmp = head;		head = head->next;		free(tmp);	}}