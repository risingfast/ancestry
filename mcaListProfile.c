//  mcaListProfile.c -- list a person's profile in the mysql ancestry database as a cgi
//  Author: Geoffrey Jarman
//  Started: 16-Aug-2021
//  References:
//  Log:
//      16-Aug-2021 started
//      16-Aug-2021 added parameter decode in URL string as GET request for PersonID
//      16-Aug-2021 changed output format to attribute list for a person
//      17-Aug-2021 added profile sections
//      18-Aug-2021 unpadded the Person ID
//      18-Aug-2021 calculate and show age for living people
//      18-Aug-2021 add a check for invalid Person ID
//      20-Aug-2021 fix the age calculation on the profile if DOB or DOD is missing
//      20-Aug-2021 fix message if invalid person id is entered
//      23-Aug-2021 change age calculation to calculate ages of living people
//      24-Aug-2021 age calulation modified to show DoB or DoD unknown
//      25-Aug-2021 fix the age calculation on parents, siblings and children
//      26-Aug-2021 add a recursive function to print ancestors
//      26-Aug-2021 add location to ancestor tree list
//      27-Aug-2021 expand indentations on the tree listing
//      15-Sep-2021 fix bug selecting father's birthplace in parent query
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
    char caSQL0[SQL_LEN] = {'\0'};
    char *data = NULL;
    long lPersonID = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

//    setenv("QUERY_STRING", "PersonID=75", 1);

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

    printf("Content-type: text/html\n\n");

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

// print a person's profile

    sprintf(caSQL0, "SELECT AP.`Person ID` "
                    ", COALESCE(AP.`First Name`, '')"
                    ", COALESCE(AP.`Nick Name`, '')"
                    ", COALESCE(AP.`Middle Names`, '')"
                    ", COALESCE(AP.`Last Name`, '')"
                    ", COALESCE(AP.`Suffix`, '')"
                    ", COALESCE(AP.`Birth Last Name`, '')"
                    ", COALESCE(AP.`Gender`, '') "
                    ", COALESCE(AP.`Born On`, '') "
                    ", COALESCE(AP.`Birth Place`, '') "
                    ", IF(AP.`Born On` IS NOT NULL, IF(AP.`Deceased On` IS NOT NULL,FLOOR(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365), IF(AP.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                    ", COALESCE(IF(AP.`Deceased` = 1, 'Deceased', 'Living'), '') AS 'Status'"
                    ", COALESCE(AP.`Deceased On`, '') "
                    ", COALESCE(AP.`Deceased Place`, '') "
                    ", COALESCE(AP.`Cause of Death`, '') "
                    ", COALESCE(AP.`Grave Site`, '') "
                    ", COALESCE(AP.`Education`, '') "
                    ", COALESCE(AP.`Comments`, '') "
                    "  FROM risingfast.`Ancestry People` AP"
                    "  WHERE AP.`Actual`= TRUE"
                    "  AND AP.`Person ID` = %ld ", lPersonID);

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
    
   
// check at least one row returned otherwise return

    iRowCount = mysql_num_rows(res);

    if(iRowCount == 0)
    {
        printf("No records match this Person ID (choose 'People' > 'Go' to list valid Person ID's)");
        return 0;
    }

// print each row of results

    row = mysql_fetch_row(res);

    printf("Profile:");
    printf("\n");
    printf("  Person ID:      %s ", row[0]);
    printf("\n");
    printf("  First Name:     %s ", row[1]);
    printf("\n");
    printf("  Nick Name:      %s ", row[2]);
    printf("\n");
    printf("  Middle Names:   %s ", row[3]);
    printf("\n");
    printf("  Last Name:      %s ", row[4]);
    printf("\n");
    printf("  Suffix:         %s ", row[5]);
    printf("\n");
    printf("  Née:            %s ", row[6]);
    printf("\n");
    printf("  Gender:         %s ", row[7]);
    printf("\n");
    printf("  Born On:        %s ", row[8]);
    printf("\n");
    printf("  Birth Place:    %s ", row[9]);
    printf("\n");
    printf("  Age:            %s ", row[10]);
    printf("\n");
    printf("  Status:         %s ", row[11]);
    printf("\n");
    printf("  Deceased On:    %s ", row[12]);
    printf("\n");
    printf("  Deceased Place: %s ", row[13]);
    printf("\n");
    printf("  Cause of Death: %s ", row[14]);
    printf("\n");
    printf("  Grave Site:     %s ", row[15]);
    printf("\n");
    printf("  Education:      %s ", row[16]);
    printf("\n");
    printf("  Comment:        %s ", row[17]);
    printf("\n");

    mysql_free_result(res);

// print a person's parents

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

// print each row of results

    printf("\n");
    printf("Parents:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
    }

    mysql_free_result(res);

// print a person's siblings

    sprintf(caSQL0, "SELECT LPAD(AC.`Person ID`, 4, ' ') AS 'Sibling ID' "
                       " , IF(AC.`Gender` = 'Male', 'Brother:', 'Sister: ') "
                       " , REPLACE(REPLACE(CONCAT(AC.`First Name`, COALESCE(CONCAT(' ''', AC.`Nick Name`, ''' '), ' '), "
                       "   COALESCE(AC.`Middle Names`, ''),' ', AC.`Last Name`, ' ',COALESCE(AC.`Suffix`, '')), '  ', ' '), '''''', '') AS `Person` "
                       " , COALESCE(CONCAT('b. ', AC.`Born On`), '') as 'Born On' "
                       " , IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                       " , IF(AM.`Born On` IS NOT NULL, IF(AC.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365), IF(AC.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT JOIN risingfast.`Ancestry People` AC on AP.`Mother ID` = AC.`Mother ID` AND AP.`Father ID` = AC.`Father ID` "
                   "LEFT JOIN risingfast.`Ancestry People` AM on AP.`Mother ID` = AM.`Person ID` "
                   "LEFT JOIN risingfast.`Ancestry People` AF on AP.`Father ID` = AF.`Person ID` "
                   "WHERE  AP.`Person ID` in (%ld) "
                   "AND AC.`Actual` = TRUE "
                   "AND AM.`Actual` = TRUE "
                   "AND AF.`Actual` = TRUE "
                   "AND AP.`Person ID` != AC.`Person ID`", lPersonID);

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

    printf("\n\n");
    printf("Siblings:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
    }

    mysql_free_result(res);

// print a person's marriages

    sprintf(caSQL0, "select AP1.`Person ID` "
                    ", REPLACE(REPLACE(CONCAT(AP1.`First Name`, COALESCE(CONCAT(' ''', AP1.`Nick Name`, ''' '), ' '), "
                    "  COALESCE(AP1.`Middle Names`, ''),' ', AP1.`Last Name`, ' ',COALESCE(AP1.`Suffix`, '')), '  ', ' '), '''''', '') AS `Husband` "
                    " , AP2.`Person ID` "
                    " , REPLACE(REPLACE(CONCAT(AP2.`First Name`, COALESCE(CONCAT(' ''', AP2.`Nick Name`, ''' '), ' '),  "
                    " COALESCE(AP2.`Middle Names`, ''),' ', AP2.`Last Name`, ' ',COALESCE(AP2.`Suffix`, ''), "
                    " COALESCE(CONCAT('(née ', AP2.`Birth Last Name`, ')'), '')), '  ', ' '), '''''', '') AS `Wife` "
                    " , COALESCE(AM.`Marriage Date`, '') "
                    " , COALESCE(AM.`Marriage Place`, '') "
                    " , AC.`Country Abbreviation` "
                    " FROM risingfast.`Ancestry Marriages` AM "
                    " left join risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                    " left join risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                    " LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Marriage Country ID` = AC.`Country ID` "
                    " WHERE (AM.`Husband ID` = %ld OR AM.`Wife ID` = %ld) "
                    " AND AM.`Marriage Type` in ('Marriage', 'Cohabitation', 'Liason')", lPersonID, lPersonID);

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

    printf("\n\n");
    printf("Marriages:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
        printf(" %s", row[6]);
    }


// print a person's divorces

    sprintf(caSQL0, "select AP1.`Person ID` "
                   ", REPLACE(REPLACE(CONCAT(AP1.`First Name`, COALESCE(CONCAT(' ''', AP1.`Nick Name`, ''' '), ' '), "
                   "  COALESCE(AP1.`Middle Names`, ''),' ', AP1.`Last Name`, ' ',COALESCE(AP1.`Suffix`, '')), '  ', ' '), '''''', '') AS `Husband` "
                   " , AP2.`Person ID` "
                   " , REPLACE(REPLACE(CONCAT(AP2.`First Name`, COALESCE(CONCAT(' ''', AP2.`Nick Name`, ''' '), ' '),  "
                   " COALESCE(AP2.`Middle Names`, ''),' ', AP2.`Last Name`, ' ',COALESCE(AP2.`Suffix`, ''), "
                   " COALESCE(CONCAT('(née ', AP2.`Birth Last Name`, ')'), '')), '  ', ' '), '''''', '') AS `Wife` "
                   " , COALESCE(AM.`Divorce Date`, '') "
                   " , COALESCE(AM.`Divorce Place`, '') "
                   " , AC.`Country Abbreviation` "
                   " FROM risingfast.`Ancestry Marriages` AM "
                   " left join risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                   " left join risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                   " LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Divorce Country ID` = AC.`Country ID` "
                   " WHERE (AM.`Husband ID` = %ld OR AM.`Wife ID` = %ld) "
                   " AND AM.`Marriage Type` in ('Marriage') "
                   " AND AM.`Divorced` = TRUE ", lPersonID, lPersonID);

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

    printf("\n\n");
    printf("Divorces:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
        printf(" %s", row[6]);
    }

// print a person's children

    sprintf(caSQL0, "SELECT LPAD(AC.`Person ID`, 3, ' ') AS AP"
                      ", IF(AC.`Gender` = 'Male', 'Son:', 'Dau:') "
                      ", REPLACE(REPLACE(CONCAT(AC.`First Name`, COALESCE(CONCAT(' ''', AC.`Nick Name`, ''' '), ' '), "
                      "  COALESCE(AC.`Middle Names`, ''),' ', AC.`Last Name`, ' ',COALESCE(AC.`Suffix`, '')), '  ', ' '), '''''', '') AS `Person` "
                      ", COALESCE(CONCAT('b. ', AC.`Born On`), '') as 'Born On' "
                      ",  IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      " , IF(AC.`Born On` IS NOT NULL, IF(AC.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365), IF(AC.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   " FROM risingfast.`Ancestry People` AP "
                   " LEFT JOIN risingfast.`Ancestry People` AC ON AP.`Person ID` = AC.`Father ID` "
                   " WHERE AP.`Person ID` = %ld "
                   " AND AC.`Actual` = TRUE "
                   " UNION ALL "
                   "SELECT LPAD(AC.`Person ID`, 3, ' ') AS AP"
                      ", IF(AC.`Gender` = 'Male', 'Son:', 'Dau:') "
                      ", REPLACE(REPLACE(CONCAT(AC.`First Name`, COALESCE(CONCAT(' ''', AC.`Nick Name`, ''' '), ' '), "
                      "  COALESCE(AC.`Middle Names`, ''),' ', AC.`Last Name`, ' ',COALESCE(AC.`Suffix`, '')), '  ', ' '), '''''', '') AS `Person` "
                      ", COALESCE(CONCAT('b. ', AC.`Born On`), '') as 'Born On' "
                      ",  IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      " , IF(AC.`Born On` IS NOT NULL, IF(AC.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365), IF(AC.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   " FROM risingfast.`Ancestry People` AP "
                   " LEFT JOIN risingfast.`Ancestry People` AC ON AP.`Person ID` = AC.`Mother ID` "
                   " WHERE AP.`Person ID` = %ld"
                   " AND AC.`Actual` = TRUE ", lPersonID, lPersonID);

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

    printf("\n\n");
    printf("Children:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
        printf(" %s", row[4]);
        printf(" %s", row[5]);
    }

// print a person's residences

    sprintf(caSQL0, " SELECT REPLACE(CONCAT(AA.`Address Line 1`, COALESCE(CONCAT(' ', AA.`Address Line 2`), ' ') "
                   ", COALESCE(CONCAT(' ', AA.`Address Line 3`), ' ')), '  ', '') AS Street "
                   ", AA.`Address City` "
                   ", AA.`Address State` "
                   ", AC.`Country Abbreviation` "
                   "  FROM risingfast.`Ancestry Addresses` AA "
                   "  LEFT JOIN risingfast.`Ancestry Residents` AR on AR.`Address ID` = AA.`Address ID` "
                   "  LEFT JOIN risingfast.`Ancestry Countries` AC on AA.`Address Country ID` = AC.`Country ID` "
                   "  WHERE AR.`Person ID` = %ld", lPersonID);

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

    printf("\n\n");
    printf("Residences:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);
        printf(" %s", row[3]);
    }

// print a person's references

    sprintf(caSQL0, "SELECT LPAD(AR.`Reference ID`, 4, ' ') "
                      "  , AR.`Reference Name` "
                      "  , AR.`Reference Link` "
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

    printf("\n\n");
    printf("References:");

    while(row = mysql_fetch_row(res))
    {
        printf("\n  ");
        printf("%s", row[0]);
        printf(" %s", row[1]);
        printf(" %s", row[2]);

    }
    printf("\n\n");

// show a person's ancestor tree

    printf("Ancestors:");
    fPrintParents(lPersonID, 0);
    printf("\n");

    mysql_free_result(res);
    return 0;
}

int fPrintParents(long lPersonID, int iLvl)
{

    char caSQL0[SQL_LEN] = {'\0'};
    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL0, "SELECT LPAD(AM.`Person ID`, 3, ' ') AS 'Parent ID' "
                      " , 'Mother:' as 'Relation' "
                      " , REPLACE(REPLACE(CONCAT(AM.`First Name`, COALESCE(CONCAT(' ''', AM.`Nick Name`, ''' '), ' '), COALESCE(AM.`Middle Names`, ''),' ', "
                      "   AM.`Last Name`, ' ',COALESCE(AM.`Suffix`, ''), COALESCE(CONCAT('(née ', AM.`Birth Last Name`, ')'))), '  ', ' '), '''''', '') AS `Person` "
                      " , COALESCE(CONCAT('b. ', AM.`Born On`), '') as 'Born On' "
                      " , COALESCE(AM.`Birth Place`, '') as 'Birth Place' "
                      " , IF(AM.`Deceased` = 1, 'Deceased', 'Living') as 'Status' "
                      " , IF(AM.`Born On` IS NOT NULL, IF(AM.`Deceased On` IS NOT NULL, FLOOR(DATEDIFF(AM.`Deceased On`, AM.`Born On`)/365), IF(AM.`Deceased` = 0, FLOOR(DATEDIFF(CURRENT_DATE(), AM.`Born On`)/365), 'DoD Unknown')), 'DoB Unknown') AS 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT join risingfast.`Ancestry People` AM ON AP.`Mother ID` = AM.`Person ID` "
                   "WHERE  AP.`Person ID` = %ld "
                   "AND AM.`Actual` = TRUE "
                   "UNION DISTINCT "
                   "SELECT LPAD(AF.`Person ID`, 3, ' ') AS 'Parent ID' "
                      " , 'Father:' AS 'Relation' "
                      " , REPLACE(REPLACE(CONCAT(AF.`First Name`, COALESCE(CONCAT(' ''', AF.`Nick Name`, ''' '), ' '), "
                      "  COALESCE(AF.`Middle Names`, ''),' ', AF.`Last Name`, ' ',COALESCE(AF.`Suffix`, '')), '  ', ' '), '''''', '') AS `Person` "
                      " , COALESCE(CONCAT('b. ', AF.`Born On`), '') as 'Born On' "
                      " , COALESCE(AF.`Birth Place`, '') as 'Birth Place' "
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
        printf(" %s", row[6]);
        fPrintParents((long) atoi(row[0]), iLvl+2);
    }

    mysql_free_result(res);

    return 0;
}
