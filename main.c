#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <winsock2.h>
#include "adminParking.h"

int main(int argc, char **argv) {

    MYSQL *mysql;
    char menu ='\0';

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    if(mysql_real_connect(mysql, "127.0.0.1", "root","", "Parking", 0, NULL, 0))
    {
        printf("Connexion OK! \n");
        do
        {
            menu = admin_menu(mysql);
        }while(menu!='q');
//        admin_add_car(mysql);


        mysql_close(mysql);
    }
    else {
        printf("Erreur connexion!");
    }
    return 0;
}

