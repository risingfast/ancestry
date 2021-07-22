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
#### Enhancements: (0)
    add known addresses
    add the children of Martha Whonsbon 94
    add query for half-siblings for Uncle Charlie and Maggie
    fix the date ordering on the birthday listing to take day into account along with month
    send or show reminders of upcoming birthdays and events via email
    remove the temporarily disabled password
