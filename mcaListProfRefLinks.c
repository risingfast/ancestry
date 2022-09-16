//  mcaListProfRefLinks.c -- list a person's profile reference links in the mysql ancestry database as a cgi
//  Author: Geoffrey Jarman
//  Started: 18-Aug-2021
//  References:
//  Log:
//      18-Aug-2021 started
//      18-Aug-2021 add reference links data
//      25-Aug-2021 show the reference type (record or picture) in the list of reference links
//      15-Sep-2022 add Access-Control-Allow-Origin: * CORS header
//  Enhancements:
///

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
    int iRowCount = 0;
    char caOrder[] = {'A', 'S', 'C', '\0'};
    char caSQL0[SQL_LEN] = {'\0'};
    char *data = NULL;
    long lPersonID = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    data = getenv("QUERY_STRING");
    if(data == NULL)
    {
         printf("Error passing PersonID from form to script.");
         return 0;
    }
    else if(sscanf(data,"PersonID=%ld",&lPersonID)!=1)
    {
         printf("Invalid data. Data must be a numberr.");
         return 0;
    }

// print http headers for content-type and CORS

    printf("Content-type: text/html\n");
    printf("Access-Control-Allow-Origin: *\n\n");

// Initialize a connection and connect to the database$$

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


// print a person's references

    sprintf(caSQL0, "SELECT LPAD(AR.`Reference ID`, 4, ' ') "
                      "  , AR.`Reference Name` "
                      "  , AR.`Reference Link` "
                      "  , AR.`Reference Type` "
                      " FROM risingfast.`Ancestry References` AR "
                      " WHERE AR.`Person ID` = %ld", lPersonID);

// execute the query and check for no result
    
    if(mysql_query(conn, caSQL0) != 0)
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

// print each row of results

    while(row = mysql_fetch_row(res))
    {
        printf("%s: <a href=\"%s\" target=\"_blank\">", row[3], row[2]);
        printf("%s</a>", row[1]);
        printf("<BR>");
    }
    printf("\n\n");

    mysql_free_result(res);

    return 0;
}
