char admin_menu(MYSQL *mysql);
int admin_already_exist(MYSQL *mysql,char *registration);
int admin_already_parked(MYSQL *mysql, char *registration);
void admin_add_car(MYSQL *mysql);
void admin_delete_car(MYSQL *mysql);
void client_add_car(MYSQL *mysql);


char admin_menu(MYSQL *mysql)
{
    char menu[2]="";

    do
    {
        printf("What do you want to do?\n");
        printf("1 - add a car\n");
        printf("2 - delete a car\n");
        printf("q - quit the application\n");
        menu[0]=getchar();
        while (getchar() != '\n');
        menu[1]='\0';

        switch(menu[0])
        {
        case '1':
            admin_add_car(mysql);
            break;
        case '2':
            printf("Work in progress !\n");
            break;
        default :
            break;
        }
    }while(menu[0]!='q');
    return menu[0];
}

int admin_already_exist(MYSQL *mysql,char *registration)
{
    mysql_query(mysql,"SELECT * FROM voiture");
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char voiture[15];
    long line=1;

    result = mysql_use_result(mysql);
     while((row=mysql_fetch_row(result)))
    {
        strcpy(voiture,row[1]);
        if(strcmp(voiture,registration)==0)
        {
            printf("ERROR : The car %s is already registered !\n",registration);
            return 1;
        }
        line++;
    }
    return 0;
}

int admin_already_parked(MYSQL *mysql,char *registration)
{
    char request[150];
    sprintf(request,"SELECT * FROM voiture WHERE plaque_immatriculation = '%s'",registration);

    mysql_query(mysql,request);
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char state[1];

    result = mysql_use_result(mysql);
    row=mysql_fetch_row(result);

    strcpy(state,row[3]);
    if(state[0]=='1')
        {
            printf("ERROR : The car %s is already parked !\n",registration);
            return 1;
        }
    return 0;
}

void admin_add_car(MYSQL *mysql)
{
    char registration[15];
    char request[150];
    int subscribe =0;
    int exist = 0;

    printf("Enter your car registration : ");
    fgets(registration,15,stdin);
    if(strlen(registration)<14)
        registration[strlen(registration)-1]='\0';

    /**faire vérif plaque**/
    /**faire vérif non existant dans la bdd**/
    exist = admin_already_exist(mysql,registration);
    if(!exist)
    {
        /**check la valeur de l'abonnement**/

        /**check si le véhicule est stationné**/

        /**ajouter le véhicule**/
        sprintf(request,"INSERT INTO `voiture` (`id`, `plaque_immatriculation`, `abonnement`, `etat`) VALUES (NULL, '%s', '%d', '0')",registration,subscribe);
        mysql_query(mysql,request);
    }
}

void admin_delete_car(MYSQL *mysql)
{
    char registration[15];
    char request[150];
    int exist = 0;
    int parked = 0;

    printf("Enter your car registration : ");
    fgets(registration,15,stdin);
    if(strlen(registration)<14)
        registration[strlen(registration)-1]='\0';

    exist = admin_already_exist(mysql,registration);
    parked = admin_already_parked(mysql,registration);
    if(exist && !parked)
    {
        sprintf(request,"DELETE FROM 'voiture' WHERE plaque_immatriculation = '%s'",registration);
    }
    else
    {
        printf("ERROR : la plaque n'existe pas ou le véhicule est actuellement stationné");
    }
}


void client_add_car(MYSQL *mysql)
{
    char registration[15];
    char request[150];
    int subscribe =0;
    int exist = 0;

    printf("Enter your car registration : ");
    fgets(registration,15,stdin);
    if(strlen(registration)<14)
        registration[strlen(registration)-1]='\0';

    /**faire vérif plaque**/
    /**faire vérif non existant dans la bdd**/
    exist = admin_already_exist(mysql,registration);
    if(!exist)
    {
        /**demander s'il veut un abonnement**/

        /**ajouter le véhicule**/
        sprintf(request,"INSERT INTO `voiture` (`id`, `plaque_immatriculation`, `abonnement`, `etat`) VALUES (NULL, '%s', '%d', '0')",registration,subscribe);
        mysql_query(mysql,request);
    }
}
