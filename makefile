# -*- makefile -*-
# makefile for mysql-c-ancestry project
# Created: 14-Jul-2021
# Geoffrey Jarman
# $@ Target file
# $^ Dependency files
# $(CC) Compiler executable
# $(CFLAGS) Compiler options
# $@ Souce file
# $^ Dependent files (dependencies)

# Variables

CC=gcc
CFLAGS=-g -o
SQL1FLAGS=-I/usr/include/mysql
SQL2FLAGS=-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl -lresolv

all: mysql-c-ancestry mcaListPeople mcaListPeople.cgi mcaListAllPeople mcaListAllPeople.cgi mcaListBdyPeople mcaListLvgPeople mcaListLvgPeople.cgi mcaListBdyPeople.cgi mcaListMlePeople mcaListMlePeople.cgi mcaListFmlPeople mcaListFmlPeople.cgi mcaListChtPeople mcaListChtPeople.cgi mcaListProfile mcaListProfile.cgi mcaListCohorts mcaListDcdPeople mcaListBirthdays mcaListMarriages mcaListMarriages.cgi mcaListReferences mcaListResidents mcaListProfRefLinks mcaShowTree mcaListPortraits mcaListPortraitPeople mcaListPortraitPeople.cgi

mysql-c-ancestry: mysql-c-ancestry.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPeople: mcaListPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListAllPeople: mcaListAllPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListAllPeople.cgi: mcaListAllPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListBdyPeople: mcaListBdyPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListBdyPeople.cgi: mcaListBdyPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListChtPeople: mcaListChtPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListChtPeople.cgi: mcaListChtPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListLvgPeople: mcaListLvgPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListLvgPeople.cgi: mcaListLvgPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListFmlPeople: mcaListFmlPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListFmlPeople.cgi: mcaListFmlPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListMlePeople: mcaListMlePeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListMlePeople.cgi: mcaListMlePeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPeople.cgi: mcaListPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListProfile: mcaListProfile.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListProfile.cgi: mcaListProfile.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListCohorts: mcaListCohorts.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListDcdPeople: mcaListDcdPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListBirthdays: mcaListBirthdays.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListResidents: mcaListResidents.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListReferences: mcaListReferences.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListMarriages: mcaListMarriages.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListMarriages.cgi: mcaListMarriages.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListProfRefLinks: mcaListProfRefLinks.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaShowTree: mcaShowTree.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPortraits: mcaListPortraits.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPortraitPeople: mcaListPortraitPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPortraitPeople.cgi: mcaListPortraitPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

clean:
	rm -f *.o *.s *.i mysql-c-ancestry mcaListPeople mcaListPeople.cgi mcaListAllPeople mcaListAllPeople.cgi mcaListLvgPeople mcaListLvgPeople.cgi mcaListBdyPeople mcaListBdyPeople.cgi mcaListMlePeople mcaListMlePeople.cgi mcaListFmlPeople mcaListFmlPeople.cgi mcaListChtPeople mcaListChtPeople.cgi mcaListProfile mcaListProfile.cgi mcaListCohorts mcaListDcdPeople mcaListBirthdays mcaListProfRefLinks mcaShowTree mcaListPortraits mcaListPortraitPeople mcaListPortraitPeople.cgi mcaListMarriages mcaListMarriages.cgi
