#### Project
    mysql-c-ancestry
#### Description
    Console c program using mysql C api to Jarman family ancestors
#### Author
    Geoffrey Jarman
#### Started
    14-Jul-2021
#### References:
    https://qnaplus.com/how-to-access-mysql-database-from-c-program/
#### Prerequisites:
    None
#### Installation:
    Create a local repository and clone down
    Run ./mysql-c-ancestry from the local directory
#### Compliation:
    make, or
    gcc -g -o mysql-c-ancestry $(mysql_config --cflags) mysql-c-ancestry.c $(mysql_config --libs) cs50.c rf50.c
#### Enhancements: (0)
    send or show reminders of upcoming birthdays and events via email
    synchronize the tree with the parent links in the database
    add an option to suppress the background image on the main page
    add an option to suppress the background image on the ancestry page
#### Log:
    14-Jul-2021 started
    15-Jul-2021 fix the age formula to account for months and days
    15-Jul-2021 add cohort table and listing option
    15-Jul-2021 create loop around printing person list options
    15-Jul-2021 enable options
    16-Jul-2021 add upcoming birthdays to the list functions
    16-Jul-2021 add intelligent headings on listings
    16-Jul-2021 start personal profile
    16-Jul-2021 add dynamic limit to entering person id on personal profile
    16-Jul-2021 add search to personal profile menu
    16-Jul-2021 add information to personal profile
    19-Jul-2021 suppress printing (null)
    19-Jul-2021 exclude Unknown
    19-Jul-2021 add events to personal profiles
    21-Jul-2021 add middle and maiden names to all people listings
    22-Jul-2021 show divorces
    22-Jul-2021 show references on personal profiles
    22-Jul-2021 add known addresses
    22-Jul-2021 add search on text with wildcards
    23-Jul-2021 fix divorces showing up in error on personal profile
    24-Jul-2021 add the children of Martha Whonsbon 94
    26-Jul-2021 add nickname to all name listings and profiles
    27-Jul-2021 add Jr/Sr Suffix in table and queryies
    28-Jul-2021 fix née on marriages in personal profile
    28-Jul-2021 fix the 'Divorce' section
    28-Jul-2021 add query for half-siblings for Uncle Charlie and Maggie
    28-Jul-2021 fix the date ordering on the birthday listing to take day into account along with month
    28-Jul-2021 remove the temporarily disabled password
    28-Aug-2021 create web application for ancestry at www.risingfast.com
    29-Aug-2021 make clean and rebuild
    30-Aug-2021 test new projects home updating GitHub
    09-Sep-2021 add background picture
    09-Sep-2021 add backgound button to reveal background images
    15-Sep-2021 add vertical scrollbar and fix bug in profile query
    15-Sep-2021 fix bug in profile listing for parents birthplace
    16-Sep-2021 misc maintenance fixes
    19-Nov-2021 update GIT with changes
    31-Dec-2021 backup current version
    03-May-2021 backup current version
    14-May-2021 backup current version
    20-May-2021 backup current version
    27-May-2021 backup current version
    03-Jun-2021 backup current version
    03-Jun-2021 backup new version of tree and tables workbook
    11-Jun-2021 backup current version
    18-Jun-2021 backup current version
