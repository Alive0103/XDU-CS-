#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_ENTRIES 100

// ͨѶ¼��Ŀ
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Entry;

// ͨѶ¼
typedef struct {
    Entry entries[MAX_ENTRIES];
    int num_entries;
} AddressBook;

// ���ͨѶ¼��Ŀ
void add_entry(AddressBook* address_book) {
    if (address_book->num_entries >= MAX_ENTRIES) {
        printf("ͨѶ¼�������޷������Ŀ��\n");
        return;
    }
    Entry* entry = &address_book->entries[address_book->num_entries];
    printf("������������");
    scanf("%s", entry->name);
    printf("������绰���룺");
    scanf("%s", entry->phone);
    printf("����������ʼ���");
    scanf("%s", entry->email);
    address_book->num_entries++;
    printf("��ӳɹ���\n");
}

// ɾ��ͨѶ¼��Ŀ
void delete_entry(AddressBook* address_book) {
    char name[MAX_NAME_LENGTH];
    printf("������Ҫɾ����������");
    scanf("%s", &name);
    int found_index = -1;
    int i; 
    for ( i = 0; i < address_book->num_entries; i++) {
        if (strcmp(address_book->entries[i].name, name) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) {
        printf("δ�ҵ�ƥ����Ŀ��\n");
        return;
    }
    for (i = found_index; i < address_book->num_entries - 1; i++) {
        address_book->entries[i] = address_book->entries[i + 1];
    }
    address_book->num_entries--;
    printf("ɾ���ɹ���\n");
}

// ��ʾ����ͨѶ¼��Ŀ
void show_all_entries(AddressBook* address_book) {
    printf("����\t\t�绰����\t\t�����ʼ�\n");
    int i;
    for ( i = 0; i < address_book->num_entries; i++) {
        Entry* entry = &address_book->entries[i];
        printf("%s\t\t%s\t\t%s\n", entry->name, entry->phone, entry->email);
    }
}

// ����ͨѶ¼��Ŀ
void find_entry(AddressBook* address_book) {
    char name[MAX_NAME_LENGTH];
    printf("������Ҫ���ҵ�������");
    scanf("%s", &name);
    int found_index = -1;
    int i;
    for (i = 0; i < address_book->num_entries; i++) {
        if (strcmp(address_book->entries[i].name, name) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) {
        printf("δ�ҵ�ƥ����Ŀ��\n");
        return;
    }
    Entry* entry = &address_book->entries[found_index];
    printf("������%s\n�绰���룺%s\n�����ʼ���%s\n", entry->name, entry->phone, entry->email);
}

// ����ͨѶ¼���ļ�

void save_address_book(AddressBook* address_book, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("�޷����ļ���\n");
		return;
	}
	int i;
	for (i = 0; i < address_book->num_entries; i++) {
		Entry* entry = &address_book->entries[i];
		fprintf(file, "%s %s %s\n", entry->name, entry->phone, entry->email);
	}
	fclose(file);
	printf("����ɹ���\n");
}

// ���ļ�����ͨѶ¼
void load_address_book(AddressBook* address_book, const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷����ļ���\n");
		return;
	}
	address_book->num_entries = 0;
	char line[100];
	while (fgets(line, sizeof(line), file) != NULL) {
		char name[MAX_NAME_LENGTH];
		char phone[MAX_PHONE_LENGTH];
		char email[MAX_EMAIL_LENGTH];
		sscanf(line, "%s %s %s", name, phone, email);
		Entry* entry = &address_book->entries[address_book->num_entries];
		strncpy(entry->name, name, MAX_NAME_LENGTH);
		strncpy(entry->phone, phone, MAX_PHONE_LENGTH);
		strncpy(entry->email, email, MAX_EMAIL_LENGTH);
		address_book->num_entries++;
	}
	fclose(file);
	printf("���سɹ���\n");
}

// ������
int main() {
	AddressBook address_book = {0};
	char filename[] = "address_book.txt";
	int choice;
	while (1) {
		printf("��ѡ��Ҫִ�еĲ�����\n");
		printf("1. �����Ŀ\n");
		printf("2. ɾ����Ŀ\n");
		printf("3. ��ʾ������Ŀ\n");
		printf("4. ������Ŀ\n");
		printf("5. ����ͨѶ¼\n");
		printf("6. ����ͨѶ¼\n");
		printf("7. �˳�\n");
		printf("������ѡ���ţ�");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				add_entry(&address_book);
				break;
			case 2:
				delete_entry(&address_book);
				break;
			case 3:
				show_all_entries(&address_book);
				break;
			case 4:
				find_entry(&address_book);
				break;
			case 5:
				save_address_book(&address_book, filename);
				break;
			case 6:
				load_address_book(&address_book, filename);
				break;
			case 7:
				return 0;
			default:
			printf("��Чѡ�\n");
		}
	}
}

