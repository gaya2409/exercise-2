#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 6
#include <string.h>

typedef struct Worker {
	unsigned long ID;
	char* name;
	unsigned long salary;

	union year {
		unsigned long international;
		char hebrew[SIZE];
	} *y;
}myworker;

typedef struct WorkerList
{
	myworker * data;
	struct WorkerList* next;
} WorkerList;

myworker* CreateWorker(int yeartype);
myworker* createWorker(unsigned long id, char* name, unsigned long salary, union year* myyear, int yeartype);
void PrintWorker(myworker* worker, int yeartype);
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

	myworker* w1 = createWorker(12, "arie1_2", 10, "tash", 0, yeartype);
	PrintWorker(w1, yeartype);
	myworker* w2 = createWorker(21, "ben2_1", 5, "tash", 0,yeartype);//change head
	PrintWorker(w2, yeartype);
	myworker* w3 = createWorker(35, "coral3_5", 100000, "tash", 0,yeartype);//add tail
	PrintWorker(w3, yeartype);
	myworker* w4 = createWorker(44, "dan4_4", 9999, "tash", 0,yeartype);//change mid list
	PrintWorker(w4, yeartype);
	myworker* w5 = createWorker(53, "edna5_3", 158, "tash", 0,yeartype);//change mid list
	PrintWorker(w5, yeartype);

	printf("Enter a worker\n");
	myworker* userworker = CreateWorker(yeartype);
	PrintWorker(userworker, yeartype);

	WorkerList * list = (WorkerList*)malloc(sizeof(WorkerList));
	list->data = w1;
	list->next = NULL;

	list = addWorker(list, w2);
	list = addWorker(list, w3);
	list = addWorker(list, w4);
	list = addWorker(list, w5);

	//test list with index1
	printf("%s -> %d,  $$$=%d\n", w1->name, index1(list, w1->ID), w1->salary);
	printf("%s -> %d,  $$$=%d\n", w2->name, index1(list, w2->ID), w2->salary);
	printf("%s -> %d,  $$$=%d\n", w3->name, index1(list, w3->ID), w3->salary);
	printf("%s -> %d,  $$$=%d\n", w4->name, index1(list, w4->ID), w4->salary);
	printf("%s -> %d,  $$$=%d\n", w5->name, index1(list, w5->ID), w5->salary);

	//test index2
	printf("i2 %s -> %d\n", w4->name, index2(list, w4->ID));
	printf("i2 %s -> %d\n", w5->name, index2(list, w5->ID));
	printf("i2 %s -> %d\n", "5555", index2(list, 5555));//should fail

	//test deleting least-earning worker
	list = deleteWorstWorker(list);
	printf("\ndeleted %s -> %d\n", w2->name, index1(list, w2->ID));

	//test updating workers
	update_worker(list, 30);
	printf("%s     $$$ = %d\n", w1->name, w1->salary);
	printf("%s     $$$ = %d\n", w2->name, w2->salary);
	printf("%s     $$$ = %d\n", w3->name, w3->salary);
	printf("%s     $$$ = %d\n", w4->name, w4->salary);
	printf("%s     $$$ = %d\n", w5->name, w5->salary);

	//test reversing order of the list
	list = reverse(list);
	printf("%s -> %d\n", w1->name, index1(list, w1->ID));
	printf("%s -> %d\n", w2->name, index1(list, w2->ID));//should fail
	printf("%s -> %d\n", w3->name, index1(list, w3->ID));
	printf("%s -> %d\n", w4->name, index1(list, w4->ID));
	printf("%s -> %d\n", w5->name, index1(list, w5->ID));


	list = deleteWorstWorker(list);
	printf("\n deleted %s -> %d\n", w1->name, index1(list, w1->ID));
	//TODO test add after reverse (should keep order by salary)
	list = addWorker(list, w2);

	myworker* w6 = createWorker(64, "gaya5_4", 207, "tash", 0,yeartype);//change mid list
	PrintWorker(w6, yeartype);

	list = addWorker(list, w6);


	//test freeing the list
	printf("\nbefore release\n");
	WorkerList * tmp = list;
	while (tmp != NULL) {
		printf("%s\n", tmp->data->name);
		tmp = tmp->next;
	}
	freeWorkers(list);
	printf("\nafter release\n");

	free(w1);
	free(w2);
	free(w3);
	free(w4);
	free(w5);
}

/*
yeartype - 0 for heb, 1 for international
*/
myworker* CreateWorker(int yeartype) {
	unsigned long id; char name[20]; unsigned long salary; char yr[SIZE]; unsigned long yir = 0;

	printf("enter id: ");
	scanf("%d", &id);
	printf("enter name: ");
	scanf("%s", name);
	printf("enter salary :");
	scanf("%d", &salary);

	printf("enter year (%s): ", yeartype ? "intl" : "heb");
	if (yeartype == 0) {
		scanf("%s", yr);
	}
	else {
		scanf("%d", yir);
	}
	return createWorker(id, name, salary, yr, yir, yeartype);

}

myworker* createWorker(unsigned long id, char* name, unsigned long salary, char* yr, unsigned long yir, int yeartype) {

	myworker* worker;
	worker = (myworker*)malloc(sizeof(myworker));
	if (!worker) { exit(0); }
	worker->ID = id;
	worker->name = (char*)malloc(sizeof(char)*20);
	if (!worker->name) { exit(0); }
	strcpy(worker->name, name);
	worker->salary = salary;
	if (yeartype) worker->y = yir;
	else {
		worker->y = (char*)malloc(sizeof(char) * 6);
		if (!worker->y) {exit(0);}
		strcpy(worker->y, yr);
	}
	return worker;
}

void PrintWorker(myworker* worker, int yeartype) {

	printf("the details about the worker:\n id:%u \n name:%s\n salary: %u \n",
		worker->ID, worker->name, worker->salary);
	if (yeartype) printf("year: %d", worker->y->international);
	else printf(" year: %s\n", worker->y->hebrew);
}

//add worker ordered by salary A-Z
WorkerList * addWorker(WorkerList *head, myworker * w) {
	WorkerList *new_list_member = (WorkerList*)malloc(sizeof(WorkerList));
	if (!new_list_member) {
		exit(0);
	}

	new_list_member->data = w;
	new_list_member->next = NULL;

	if (head->data->salary > w->salary) {
		new_list_member->next = head;
		return new_list_member;
	}

	WorkerList* current = head;
	WorkerList* prev = NULL;
	while (current->next != NULL)
	{
		if (current->data->salary > w->salary) {
			new_list_member->next = current;
			prev->next = new_list_member;
			return head;
		}
		prev = current;
		current = current->next;
	}

	if (current->data->salary > w->salary) {
		prev->next = new_list_member;
		new_list_member->next = current;
		return head;
	}

	current->next = new_list_member;
	return head;
}


int index1(WorkerList *head, long unsigned id) {

	int count = 1;
	WorkerList* current = head;
	while (current) {
		if (current->data->ID == id) {

			return count;
		}
		count++;
		current = current->next;
	}
	return -1;
}

int index2(WorkerList *head, long unsigned id) {

	if (head->data->ID == id) return 1; //found an item
	if (!head->next) return -1; //when no item was found and reached end of list
	int res = index2(head->next, id);
	return res == -1 ? -1 : res + 1;
}

WorkerList* deleteWorstWorker(WorkerList *head) {
	if (head->next == NULL) {
		free(head);
		return NULL;
	}
	else {
		WorkerList* current = head;
		while (current->next != NULL) {
			//do when remove first:
			if (current->data->salary < current->next->data->salary) {
				WorkerList* tmp = head;
				head = head->next;
				free(tmp);
				break;
			}

			//do when remove last
			if (current->next->next == NULL) {
				free(current->next);
				current->next = NULL;
				break;
			}
			current = current->next;
		}
	}
	return head;
}

// assuming percent is given in the form of 100=100%
void update_worker(WorkerList *head, float percent) {
	while (head) {
		head->data->salary *= (100.0 + percent) / 100.0;
		head = head->next;
	}
}


WorkerList *reverse(WorkerList *head) {
	if (head == NULL || head->next == NULL) return head;
	WorkerList *prev = reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return prev;
}

void freeWorkers(WorkerList *head) {
	WorkerList * tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
