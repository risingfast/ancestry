//  mcaShowTree.c -- show a person's family tree of direct acnestors as a cgi
//  Author: Geoffrey Jarman
//  Started: 26-Aug-2021
//  References:
//  Log:
//      26-Aug-2021 started
//      16-Sep-2022 add http header for CORS
//  Enhancements:

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

int fPrintParents(long lPersonID, int iLvl);                // recursive function to print both of a person's parents

MYSQL *conn;

int main(int argc, char** argv) {

    int iColCount = 0;
    int iRowCount = 0;
    char caOrder[] = {'A', 'S', 'C', '\0'};
    char *data = NULL;
    long lPersonID = 0;

//    setenv("QUERY_STRING", "PersonID=75", 1);

    data = getenv("QUERY_STRING");
    if(data == NULL)
    {
         printf("Error passing PersonID from form to script.");
         return 0;
    }
    else if(sscanf(data,"PersonID=%ld",&lPersonID)!=1)
    {
         printf("Invalid data. Data must be a number.");
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

    printf("Ancestors:");
    printf("\n");
    fPrintParents(lPersonID, 1);

    printf("\n\n");

}

int fPrintParents(long lPersonID, int iLvl)
{

    char caSQL0[SQL_LEN] = {'\0'};
    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL0, "SELECT LPAD(AM.`Person ID`, 4, ' ') AS 'Parent ID' "
                      " , 'Mother:' as 'Relation' "
                      " , REPLACE(REPLACE(CONCAT(AM.`First Name`, COALESCE(CONCAT(' ''', AM.`Nick Name`, ''' '), ' '), COALESCE(AM.`Middle Names`, ''),' ', "
                      "   AM.`Last Name`, ' ',COALESCE(AM.`Suffix`, ''), COALESCE(CONCAT('(née ', AM.`Birth Last Name`, ')'))), '  ', ' '), '''''', '') AS `Person` "
                      " , COALESCE(CONCAT('b. ', AM.`Born On`), '') as 'Born On' "
                      " , IF(AM.`Deceased` = 1, 'Deceased', 'Living') as 'Status' "
                      " , IF(AM.`Born On` IS NOT NULL, IF(AM.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AM.`Deceased On`, AM.`Born On`)/365), IF(AM.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AM.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT join risingfast.`Ancestry People` AM ON AP.`Mother ID` = AM.`Person ID` "
                   "WHERE  AP.`Person ID` = %ld "
                   "AND AM.`Actual` = TRUE "
                   "UNION DISTINCT "
                   "SELECT LPAD(AF.`Person ID`, 4, ' ') AS 'Parent ID' "
                      " , 'Father:' AS 'Relation' "
                      " , REPLACE(REPLACE(CONCAT(AF.`First Name`, COALESCE(CONCAT(' ''', AF.`Nick Name`, ''' '), ' '), "
                      "  COALESCE(AF.`Middle Names`, ''),' ', AF.`Last Name`, ' ',COALESCE(AF.`Suffix`, '')), '  ', ' '), '''''', '') AS `Person` "
                      " , COALESCE(CONCAT('b. ', AF.`Born On`), '') as 'Born On' "
                      " , IF(AF.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      " , IF(AF.`Born On` IS NOT NULL, IF(AF.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AF.`Deceased On`, AF.`Born On`)/365), IF(AF.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AF.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT JOIN risingfast.`Ancestry People` AF ON AP.`Father ID` = AF.`Person ID` "
                   "WHERE  AP.`Person ID` = %ld "
                   "AND AF.`Actual` = TRUE ", lPersonID, lPersonID);

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
    
    printf("\n");
// print each row of results
    while(row = mysql_fetch_row(res))
    { 
        for (int i = 0; i < iLvl; i++)
        { 
            printf("....");
        }
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
        fPrintParents((long) atoi(row[0]), iLvl+1);
    }

    mysql_free_result(res);

    return 0;
}
