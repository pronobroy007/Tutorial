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
    sqlite3_stmt *stmt; 

    //Connect to database.............................
    int rc = sqlite3_open("test.db", &db);
    if(rc)
        std::cout << "Can't open database ...!" << std::endl;
    else
        std::cout << "Database open successfully" << std::endl;

    //SQL query...................
    const char *sql[10];
    sql[0] = R"(CREATE TABLE if not exists Employee(
				User1 varchar(30), 
				User2 varchar(30), 
				Age smallint,
				PRIMARY KEY (User1, User2)
				))";
    sql[1] = "INSERT INTO Employee(User1, User2, Age) VALUES ('1', '2', 45)";
    sql[2] = "INSERT INTO Employee(User1, User2, Age) VALUES ('1', '3', 495)";
    sql[3] = "SELECT * FROM Employee";
    sql[4] = "DROP TABLE Employee";

    for (int i = 0; i < 3; i++)
    {
        if (!exec(db, (char*)sql[i]))
		{
			std::cout << sql[i] << std::endl;
            return -1;
		}
    }

	//Prepare stmt.......................
    //sql[1] = "INSERT INTO Employee(User1, User2, Age) VALUES ('1', '2', 45)";
    char *str = (char*)"INSERT INTO Employee(User1, User2, Age) VALUES (?, ?, ?)";
    if(sqlite3_prepare_v2(db, str, -1, &stmt, nullptr) != SQLITE_OK)
        std::cout << "Could not prepare stmt!" << std::endl;

	//Bind text vlaue ......................
    char *val[] = {(char*)"1", (char*)"4"};
    for (int i = 0; i < 2; i++)
    {
        if(sqlite3_bind_text(stmt, i+1, val[i], sizeof(val[i]), 0) != SQLITE_OK)
            std::cout << "Could not bind User" << i << "!" << std::endl;
    }

	//Bind integer value.....................
    int age = 34;
    if(sqlite3_bind_int(stmt, 3, age) != SQLITE_OK)
        std::cout << "Could not bind age !" << std::endl;

	//Execute stmt...........................
    if(sqlite3_step(stmt) != SQLITE_DONE)
        std::cout << "Could not exec stmt !" << std::endl;


	//Execute select stmt using prepare stmt....................
    if(sqlite3_prepare_v2(db, (char*)sql[3], -1, &stmt, nullptr) != SQLITE_OK)
        std::cout << "Could not prepare select stmt!" << std::endl;

	//Retrive result of select command...................
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::cout << sqlite3_column_text(stmt, 0) << " ";
        std::cout << sqlite3_column_text(stmt, 1) << " ";
        std::cout << sqlite3_column_text(stmt, 2) << std::endl;

    }

	//Execute drop table command ..............
    if (!exec(db, (char*)sql[4]))
    {
        std::cout << sql[4] << std::endl;
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

    for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++)
        std::cout << *it << std::endl;

    return true;
}


static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    std::vector<std::string> *str = (std::vector<std::string> *)data;

    for(i = 0; i < argc; i++) {
        str->push_back(argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

