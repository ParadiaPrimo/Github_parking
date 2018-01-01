char admin_menu(MYSQL *mysql);
int admin_already_exist(MYSQL *mysql,char *registration);
int admin_already_parked(MYSQL *mysql, char *registration);
void admin_add_car(MYSQL *mysql);
void admin_delete_car(MYSQL *mysql);
void admin_facture(MYSQL *mysql,int id_voiture);



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
        case 'd':
            debug_mode(mysql);
            break;
        default :
            break;
        }
    }while(menu[0]!='q');
    return menu[0];


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
        strcpy(voiture,row[2]);
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
    int id_proprio = NULL; /** A DEFINIR **/

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
        sprintf(request,"INSERT INTO voiture (`id_proprio`, `plaque_immatriculation`, `etat`) VALUES ('%s', '%d', '0')",id_proprio,registration,subscribe);
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
        sprintf(request,"DELETE FROM voiture WHERE plaque_immatriculation = '%s'",registration);
    }
    else
    {
        printf("ERROR : la plaque n'existe pas ou le véhicule est actuellement stationné");
        return;
    }
}

void debug_mode(MYSQL *mysql)
{
    mysql_query(mysql,"SELECT * FROM reservation");
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    unsigned int i = 0;
    unsigned int num_champs = 0;


        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(mysql);

        //On récupère le nombre de champs
        num_champs = mysql_num_fields(result);

        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {
               //On ecrit toutes les valeurs
/*               printf("i = %d  ",i);
               printf("num_champ = %d",num_champs);
               printf("length = %d",lengths);
*/               printf("[%s] ", row[i]);
            }
            printf("\n");
        }

        //Libération du jeu de résultat
        mysql_free_result(result);
    return;
}

void admin_facture(MYSQL *mysql,int id_voiture)
{
	char day_true_start_char[19];
	char day_true_end_char[19];

	char request[150];
	sprintf(request,"SELECT * FROM reservation WHERE id_voiture='%d' AND fini=1 AND actif=1 AND paye=0 ",id_voiture);
	result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);	
	
	day_true_start_char=row[4];
	day_true_end_char=row[5];
	
	/**faire le calcul du prix**/
	
	/**faire la facture**/
	
	sprintf(request,"UPDATE reservation SET paye = 1 WHERE id_voiture='%d' AND fini=1 AND actif=1 AND paye = 0 ",id_voiture);
	mysql_use_result(mysql);
	

}