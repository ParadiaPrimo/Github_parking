void client_add_car(MYSQL *mysql);


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

