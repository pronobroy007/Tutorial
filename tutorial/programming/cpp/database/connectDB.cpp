#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <memory>

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
bool exec(sqlite3 *db, char *sql);


int main()
{
    sqlite3 *db;

    //Connect to database.............................
    int rc = sqlite3_open("test.db", &db);
    if(rc)
        std::cout << "Can't open database ...!" << std::endl;
    else
        std::cout << "Database open successfully" << std::endl;

    //SQL query...................
    const char *sql[5];
    sql[0] = R"(CREATE TABLE if not exists Employee(
				id INTEGER PRIMARY KEY AUTOINCREMENT, 
				Firstname varchar(30), 
				Lastname varchar(30), 
				Age smallint))";
    sql[1] = "INSERT INTO Employee(Firstname, Lastname, Age) VALUES ('Woody', 'Alan', 45)";
    sql[2] = "INSERT INTO Employee(Firstname, Lastname, Age) VALUES ('Micheal', 'Bay', 38)";
    sql[3] = "SELECT * FROM Employee";
    sql[4] = "DROP TABLE Employee";

    for (int i = 0; i < 5; i++)
    {
        if (!exec(db, (char*)sql[i]))
            return -1;
    }

    //Close connection ...............
    sqlite3_close(db);
    return 0;
}


bool exec(sqlite3 *db, char *sql)
{
    std::vector<std::string> data; 
    char *emsg;

    int rc = sqlite3_exec(db, sql, callback, (void*)&data, &emsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", emsg);
        sqlite3_free(emsg);
        return false;
    }

    std::cout << "Stored data : " << std::endl;
    for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++)
        std::cout << *it << std::endl;

    return true;
}


static int callback(void *data, int argc, char **argv, char **azColName) {
    std::vector<std::string> *str = (std::vector<std::string> *)data;

    for(int i = 0; i < argc; i++) {
        str->push_back(argv[i] ? argv[i] : "NULL");
    }
    return 0;
}
