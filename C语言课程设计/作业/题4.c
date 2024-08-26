#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATABASES 10
#define MAX_TABLES 10
#define MAX_FIELDS 10
#define MAX_RECORDS 1000
#define MAX_NAME_LENGTH 32
#define MAX_CONDITION_LENGTH 64
#define MAX_QUERY_LENGTH 256
#define MAX_LINE_LENGTH 1024

/* ���ݿ� */
typedef struct {
    char name[MAX_NAME_LENGTH];         /* ���ݿ��� */
    int table_count;                    /* ���ݱ����� */
    char tables[MAX_TABLES][MAX_NAME_LENGTH]; /* ���ݱ��� */
} database_t;

/* ���ݱ��ֶ� */
typedef struct {
    char name[MAX_NAME_LENGTH]; /* �ֶ��� */
    char type[MAX_NAME_LENGTH]; /* �ֶ����� */
} field_t;

/* ���ݱ��¼ */
typedef struct {
    char data[MAX_FIELDS][MAX_NAME_LENGTH]; /* ��¼���� */
} record_t;

/* ���ݱ� */
typedef struct {
    char name[MAX_NAME_LENGTH]; /* ���ݱ��� */
    int field_count;            /* �ֶ����� */
    field_t fields[MAX_FIELDS]; /* �ֶ���Ϣ */
    int record_count;           /* ��¼���� */
    record_t records[MAX_RECORDS]; /* ��¼���� */
} table_t;

/* ȫ�ֱ��� */
database_t databases[MAX_DATABASES]; /* ���ݿ� */
table_t *current_table;               /* ��ǰ���ݱ� */
char current_database[MAX_NAME_LENGTH]; /* ��ǰ���ݿ� */

/* �������� */
int load_database(char *database_name);
void save_database(char *database_name);
void create_database(char *database_name);
void drop_database(char *database_name);
void use_database(char *database_name);
void create_table(char *table_name, char **fields, int field_count);
void drop_table(char *table_name);
void info_table(char *table_name);
void insert_record(char **data, int data_count);
void delete_records(char *condition);
void select_records(char **fields, int field_count, char *condition, char *order_field, int order_desc);

/* ��ȡ�� */
char *read_line(FILE *fp) {
    static char line[MAX_LINE_LENGTH];
    char *result = fgets(line, sizeof(line), fp);
    if (result == NULL) {
        return NULL;
    }
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    return result;
}

/* ����ַ��� */
char **split_string(char *str, char *delim, int *count) {
    char *token;
    char **result = NULL;
    int i = 0;
    token = strtok(str, delim);
    while (token != NULL) {
        result = (char **)realloc(result, sizeof(char *) * (i + 1));
        result[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    *count = i;
    return result;
}

/* �������ݿ� */
//int load_database(char *database_name) {
//    char filename[MAX_NAME_LENGTH + 5];
//    sprintf(filename, "%s.db", database_name);
//    FILE *fp;
//fp = fopen(filename, "rb");
//if (fp == NULL) {
//printf("Database %s does not exist.\n", database_name);
//return 0;
//}
//fread(&current_db, sizeof(DB), 1, fp);
//fclose(fp);
//return 1;
//}

/* �������ݿ� */
//int save_database(char *database_name) {
//char filename[MAX_NAME_LENGTH + 5];
//sprintf(filename, "%s.db", database_name);
//FILE *fp;
//fp = fopen(filename, "wb");
//if (fp == NULL) {
//printf("Failed to save database.\n");
//return 0;
//}
//fwrite(&current_db, sizeof(DB), 1, fp);
//fclose(fp);
//return 1;
//}

/* �������ݿ� */
//void create_database(char *database_name) {
//if (strlen(database_name) > MAX_NAME_LENGTH) {
//printf("Database name too long.\n");
//return;
//}
//if (load_database(database_name)) {
//printf("Database %s already exists.\n", database_name);
//return;
//}
//current_db.num_tables = 0;
//strcpy(current_db.name, database_name);
//save_database(database_name);
//printf("Database %s created.\n", database_name);
//}

/* ɾ�����ݿ� */
void drop_database(char *database_name) {
if (!load_database(database_name)) {
printf("Database %s does not exist.\n", database_name);
return;
}
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s.db", database_name);
remove(filename);
printf("Database %s dropped.\n", database_name);
}

/* ѡ�����ݿ� */
void use_database(char *database_name) {
if (!load_database(database_name)) {
printf("Database %s does not exist.\n", database_name);
return;
}
printf("Using database %s.\n", database_name);
}
/* �������ݱ� */
void create_table(char *table_name, char **columns) {
if (current_db.num_tables >= MAX_TABLES) {
printf("Cannot create table. Maximum number of tables reached.\n");
return;
}
/* �����Ƿ��Ѿ����� */
for (int i = 0; i < current_db.num_tables; i++) {
    if (strcmp(current_db.tables[i].name, table_name) == 0) {
        printf("Table %s already exists.\n", table_name);
        return;
    }
}

/* �����±� */
Table new_table;
strcpy(new_table.name, table_name);
new_table.num_cols = 0;
new_table.num_rows = 0;

/* �����ֶ����ͺ����� */
int i = 0;
while (columns[i] != NULL) {
    char *col_type = strtok(columns[i], " ");
    char *col_name = strtok(NULL, " ");

    /* ����Ƿ����ظ����ֶ��� */
    for (int j = 0; j < new_table.num_cols; j++) {
        if (strcmp(new_table.columns[j].name, col_name) == 0) {
            printf("Duplicate column name %s.\n", col_name);
            return;
        }
    }

    /* ������� */
    Column new_col;
    strcpy(new_col.name, col_name);
    if (strcmp(col_type, "int") == 0) {
        new_col.type = INT;
    } else if (strcmp(col_type, "float") == 0) {
        new_col.type = FLOAT;
    } else if (strcmp(col_type, "string") == 0) {
        new_col.type = STRING;
    } else {
        printf("Unknown column type %s.\n", col_type);
        return;
    }
    new_table.columns[new_table.num_cols++] = new_col;
    i++;
}

/* ����±���ǰ���ݿ��� */
current_db.tables[current_db.num_tables++] = new_table;
printf("Table %s created.\n", table_name);
}

/* ɾ�����ݱ� */
void drop_table(char table_name) {
/ ���ұ��λ�� */
int table_index = -1;
for (int i = 0; i < current_db.num_tables; i++) {
if (strcmp(current_db.tables[i].name, table_name) == 0) {
table_index = i;
break;
}
}
/* ����������򱨴� */
if (table_index == -1) {
    printf("Table %s does not exist.\n", table_name);
    return;
}

/* �����ݿ���ɾ���� */
for (int i = table_index; i < current_db.num_tables - 1; i++) {
    current_db.tables[i] = current_db.tables[i+1];
}
current_db.num_tables--;

printf("Table %s deleted.\n", table_name);
}

/* ��ʾ����Ϣ */
void show_table_info(char table_name) {
/ ���ұ��λ�� */
int table_index = -1;
for (int i = 0; i < current_db.num_tables; i++) {
if (strcmp(current_db.tables[i].name, table_name) == 0) {
table_index = i;
break;
}
}
/* ����������򱨴� */
if (table_index == -1) {
    printf("Table %s does not exist.\n", table_name);
    return;
}

/* ��ӡ����Ϣ */
void print_table(Table *table) {
    printf("Table name: %s\n", table->name);
    printf("Number of columns: %d\n", table->num_columns);
    printf("Column names: ");
    for (int i = 0; i < table->num_columns; i++) {
        printf("%s ", table->columns[i].name);
    }
    printf("\n");
    printf("Number of rows: %d\n", table->num_rows);
    printf("Row data:\n");
    for (int i = 0; i < table->num_rows; i++) {
        Row row = table->rows[i];
        printf("%d ", row.id);
        for (int j = 0; j < table->num_columns; j++) {
            switch (table->columns[j].type) {
                case INT:
                    printf("%d ", row.ints[j]);
                    break;
                case DOUBLE:
                    printf("%.2lf ", row.doubles[j]);
                    break;
                case TEXT:
                    printf("%s ", row.texts[j]);
                    break;
            }
        }
        printf("\n");
    }
}

/* ɾ�����ݱ� */
void drop_table(char *table_name) {
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s/%s.tb", current_db_path, table_name);
if (remove(filename) != 0) {
printf("Table %s does not exist.\n", table_name);
return;
}
printf("Table %s dropped.\n", table_name);
}

/* ��ʾ����Ϣ */
void info_table(char *table_name) {
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s/%s.tb", current_db_path, table_name);
FILE *fp = fopen(filename, "rb");
if (fp == NULL) {
printf("Table %s does not exist.\n", table_name);
return;
}
TableHeader header;
fread(&header, sizeof(header), 1, fp);
printf("Table %s:\n", table_name);
printf("Columns: %d\n", header.num_cols);
printf("Records: %d\n", header.num_records);
fclose(fp);
}

/* �����¼ */
void insert_record(char *table_name, char *values_str) {
TableHeader header;
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s/%s.tb", current_db_path, table_name);
FILE *fp = fopen(filename, "rb+");
if (fp == NULL) {
printf("Table %s does not exist.\n", table_name);
return;
}
fread(&header, sizeof(header), 1, fp);
Record new_record;
memset(&new_record, 0, sizeof(new_record));
char *ptr = values_str;
for (int i = 0; i < header.num_cols; i++) {
char *value = get_value_from_str(&ptr);
if (value == NULL) {
printf("Invalid values.\n");
fclose(fp);
return;
}
set_column_value(&new_record, i, value);
}
fwrite(&new_record, sizeof(new_record), 1, fp);
header.num_records++;
fseek(fp, 0, SEEK_SET);
fwrite(&header, sizeof(header), 1, fp);
fclose(fp);
printf("Record inserted into table %s.\n", table_name);
}

/* ɾ����¼ */
void delete_record(char *table_name, char *condition) {
TableHeader header;
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s/%s.tb", current_db_path, table_name);
FILE *fp = fopen(filename, "rb+");
if (fp == NULL) {
printf("Table %s does not exist.\n", table_name);
return;
}
fread(&header, sizeof(header), 1, fp);
Record record;
char temp_filename[MAX_NAME_LENGTH + 5];
sprintf(temp_filename, "%s/temp.tb", current_db_path);
FILE *temp_fp = fopen(temp_filename, "wb");
if (temp_fp == NULL) {
fclose(fp);
printf("Error creating temp file.\n");
return;
}
fwrite(&header, sizeof(header), 1, temp_fp);
int num_deleted = 0;
for (int i = 0; i < header.num_records; i++) {
fread(&record, sizeof(record), 1, fp);
if (condition == NULL || evaluate_condition(&record, condition)) {
num_deleted++;
} else {
fwrite(&record, sizeof(record), 1, temp_fp);
}
}
/* �ر��ļ������ɾ����ʱ�ļ� */
fclose(fp);
fclose(temp_fp);
remove(filename);
rename(temp_filename, filename);

return 1;
}

/* ɾ�����ݿ� */
void drop_database(char *database_name) {
char filename[MAX_NAME_LENGTH + 5];
sprintf(filename, "%s.db", database_name);
remove(filename);
printf("Database %s has been dropped.\n", database_name);
}

