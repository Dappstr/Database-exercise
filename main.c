#include "stdio.h"
#include "errno.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
} Address;

typedef struct Database
{
    Address rows[MAX_ROWS];
} Database;

typedef struct Connection
{
    FILE* file;
    Database* db;
} Connection;

void die(const char* message)
{
    if(errno) {
        perror(message);
    } else {
        printf("Error message: %s\n", message);
    }
    exit(1);
}

void addressPrint(Address* address)
{
    printf("%d %s %s\n", address->id, address->name, address->email);
}

void databaseLoad(Connection* connection)
{
    int rc = fread(connection->db, sizeof(Database), 1, connection->file);
    if(!rc) {
        die("Failed to read database!\n");
    }
}

int main()
{

}