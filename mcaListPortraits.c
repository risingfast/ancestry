//  mcaListPortraits.c -- list portraits of people in the mysql ancestry database as a cgi
//  Author: Geoffrey Jarman
//  Started: 31-Aug-2022
//  References:
//  Log:
//      31-Aug-2022 started and tested
//      31-Aug-2022 add sort order on SQL by date
//  Enhancements:
//

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define SQL_LEN 5000
#define HDG_LEN 1000

// global declarations

char *sgServer = "192.168.0.13";                                                               //mysqlServer IP address
char *sgUsername = "gjarman";                                                              // mysqlSerer logon username
char *sgPassword = "Mpa4egu$";                                                    // password to connect to mysqlserver
char *sgDatabase = "risingfast";                                                // default database name on mysqlserver

MYSQL *conn;

int main(int argc, char** argv) {

    int iColCount = 0;
    char caOrder[] = {'A', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    long lPersonID = 0;
    char *data = NULL;

    MYSQL_RES *res;
    MYSQL_ROW row;

// print HTTP headers

    printf("Content-type: text/html\n\n");

//    setenv("QUERY_STRING", "PersonID=23", 1);

    data = getenv("QUERY_STRING");
    if(data == NULL)
    {
         printf("Error passing PersonID from form to script.");
        printf("\n\n");
         return 0;
    }
    else if(sscanf(data,"PersonID=%ld",&lPersonID)!=1)
    {
         printf("Invalid data. Data must be a number.");
         return 0;
    }

// define SQL to query the database for portraits in JSON

    sprintf(caSQL, "SELECT JSON_OBJECT('Portrait ID', `Portrait ID`, 'Person ID', `Person ID` "
                   " , 'Portrait Date', `Portrait Date`, 'Portrait Caption', `Portrait Caption` "
                   " , 'Portrait Path', `Portrait Path`) AS 'Portraits' "
                   " FROM risingfast.`Ancestry Portraits` "
                   " WHERE risingfast.`Ancestry Portraits`.`Person ID` = %ld "
                   " ORDER BY `Portrait Date` ASC", lPersonID)
                    ;

// Initialize a connection and connect to the database

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, sgServer, sgUsername, sgPassword, sgDatabase, 0, NULL, 0))
    {
        printf("\n");
        printf("Failed to connect to MySQL Server %s in module %s()", sgServer, __func__);
        printf("\n\n");
        printf("Error: %s\n", mysql_error(conn));
        printf("\n");
        return  EXIT_FAILURE;
    }

// execute the query and check for no result
    
    if(mysql_query(conn, caSQL) != 0)
    {
        printf("\n");
        printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
        printf("\n\n");
        return EXIT_FAILURE;
    }

// store the result of the query

    res = mysql_store_result(conn);
    if(res == NULL)
    {
        printf("%s() -- no results returned", __func__);
        printf("\n");

        mysql_free_result(res);
        return EXIT_FAILURE;
    }
    
// fetch the number of fields in the result
    
    iColCount = mysql_num_fields(res);
    
    mysql_data_seek(res, 0);
    
// print each row of results

    while(row = mysql_fetch_row(res))
    {
        for(int i = 0; i < iColCount; i++)
        {
            if(i == 0)
            {
                printf("%s ", row[i]);
            }
            else if (i == iColCount - 1)
            {
                printf("%s", row[i]);
            }
            else
            {
                printf("%s|", row[i]);
            }
        }
        printf("\n");
    }

    mysql_free_result(res);

    return 0;
}
