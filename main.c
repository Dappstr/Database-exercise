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

Connection* db_Open(const char* filename, char mode)
{
    Connection* connection = malloc(sizeof(Connection));

    if(!connection){
        die("Memory error!\n");
    }
    switch(mode)
    {
        case 'c':
            connection->file = fopen(filename, "w");
            break;

        default:
            connection->file = fopen(filename, "r+");
            if(connection->file) {
                databaseLoad(connection);
            }
            break;
    }
    if(!connection->file) {
        die("Failed to open file!\n");
    }

    return connection;
}

void Database_close(Connection* connection)
{
    if(connection) {
        if(connection->file) {
            fclose(connection->file);
        }
        if(connection->db) {
            free(connection->db);
        }
        free(connection);
    }
}

int main()
{

}
