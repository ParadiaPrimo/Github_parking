void client_add_car(MYSQL *mysql);
void client_take_reservation(MYSQL *mysql);
void client_cancel_reservation(MYSQL *mysql);
void client_modify_reservation(MYSQL *mysql);
void client_start_reservation(MYSQL *mysql);
void client_end_reservation(MYSQL *mysql);




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
        sprintf(request,"INSERT INTO voiture (`id`, `plaque_immatriculation`, `abonnement`, `etat`) VALUES (NULL, '%s', '%d', '0')",registration,subscribe);
        mysql_query(mysql,request);
    }
}

void client_take_reservation(MYSQL *mysql)
{
    /**0min => 00:00 / 1439min => 23:59**/
    /**'2017-12-28 00:00:00' => format DATETIME **/
    char day_start_char[19];
    char day_end_char[19];


    char request[150];

    if()/**Voiture pas garée et existe**/
        {
		mysql_query(mysql,"SELECT * FROM voiture WHERE etat=0");
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        char voiture[15];
        long line=1;

        result = mysql_use_result(mysql);
         while((row=mysql_fetch_row(result)))
        {
            strcpy(voiture,row[2]);
            if(strcmp(voiture,registration)==0)/*La voiture est la bonne*/
            {
                if()/**start<end ET si aucune ligne avec actif = 0 et fini = 0**/ 
                {

                    /**Toutes conditions OK donc ajout dans la database**/
                    sprintf(day_start_char,"%d-%d-%d %d:%d:00",year_start,month_start,day_start,hour_start,min_start);
                    sprintf(day_end_char,"%d-%d-%d %d:%d:00",year_end,month_end,day_end,hour_end,min_end);

                    sprintf(request,"INSERT INTO reservation (`id_voiture`, `date_prevue_start`, `date__prevue_end`) VALUES ('%s', '%s', '%s')",plaque_immatriculation,day_start_char,day_end_char);


                }
                else
                {
                    printf("ERROR : The specified date is wrong\n");
                }

            }
            line++;
        }

    }
    else
    {
        printf("ERROR : The specified car doesn't exist or is already parked\n");
    }

}

void client_cancel_reservation(MYSQL *mysql)
{
	char plaque_immatriculation[15];
	int id_voiture = 0;
    char request[150];
	sprintf(request,"SELECT id_voiture FROM voiture WHERE plaque_immatriculation='%s' ",plaque_immatriculation);
    mysql_query(mysql,request);

	MYSQL_RES *result = NULL;
    MYSQL_ROW row;
	
    result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);
	id_voiture = row[0];
	if(row != NULL)
	{
		sprintf(request,"UPDATE reservation SET actif=-1 WHERE id_voiture='%d' AND fini=0 AND actif=0 ",id_voiture);
		    mysql_query(mysql,request);
			
		sprintf(request,"SELECT * FROM reservation WHERE id_voiture='%d' AND fini=0 AND actif=0 ",id_voiture);
		    mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);
		if(row == NULL)
			printf("Booking successfully cancelled");
		else
			printf("ERROR : The booking doesn't exist \n please contact an administrator");
	}
	else
	{
		printf("ERROR : The specified car doesn't exist")
	}
}

void client_modify_reservation(MYSQL *mysql)
{
	char plaque_immatriculation[15];
	int id_voiture = 0;
    char request[150];
	
	char newday_start_char[19];
    char newday_end_char[19];
	
	sprintf(request,"SELECT id_voiture FROM voiture WHERE plaque_immatriculation='%s' ",plaque_immatriculation);
    mysql_query(mysql,request);

	MYSQL_RES *result = NULL;
    MYSQL_ROW row;
	
    result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);
	id_voiture = row[0];
	if(id_voiture != 0)
	{
		sprintf(newday_start_char,"%d-%d-%d %d:%d:00",year_start,month_start,day_start,hour_start,min_start);
		sprintf(newday_end_char,"%d-%d-%d %d:%d:00",year_end,month_end,day_end,hour_end,min_end);
		sprintf(request,"UPDATE reservation SET date_prevue_start='%s',date__prevue_end='%s' WHERE id_voiture='%d' AND fini=0 AND actif=0 ",newday_start_char,newday_end_char,id_voiture);
		    mysql_query(mysql,request);
			
		sprintf(request,"SELECT * FROM reservation WHERE id_voiture='%d' AND fini=0 AND actif=0 ",id_voiture);
		    mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);
		if(row == NULL)
			printf("New booking date : \n start [%s] \n end [%s]",row[2],row[3]);
		else
			printf("ERROR : The booking doesn't exist \n please contact an administrator");
	}
	else
	{
		printf("ERROR : The specified car doesn't exist")
	}
}

void client_start_reservation(MYSQL *mysql)
{
	char plaque_immatriculation[15];
	int id_voiture = 0;
    char request[150];
	char day_true_start_char[19];
	
	sprintf(request,"SELECT CURRENT_TIMESTAMP();");
	day_true_start_char = mysql_query(mysql,request);
	
	sprintf(request,"SELECT id_voiture FROM voiture WHERE plaque_immatriculation='%s' ",plaque_immatriculation);
    mysql_query(mysql,request);

	MYSQL_RES *result = NULL;
    MYSQL_ROW row;
	
    result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);
	id_voiture = row[0];
	if(id_voiture != 0)
	{
		sprintf(request,"UPDATE reservation SET date_true_start='%s',actif=1 WHERE id_voiture='%d' AND fini=0 AND actif=0 ",day_true_start_char);
		mysql_query(mysql,request);
			
		sprintf(request,"SELECT * FROM reservation WHERE id_voiture='%d' AND fini=0 AND actif=1 AND paye = 0 ",id_voiture);
		    mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);
		if(row == NULL)
			printf("Booking date : end [%s]",row[3]);
		else
			printf("ERROR : The booking doesn't exist \n please contact an administrator");
	}
	else
	{
		printf("ERROR : The specified car doesn't exist")
	}
	
}

void client_end_reservation(MYSQL *mysql)
{
	char plaque_immatriculation[15];
	int id_voiture = 0;
    char request[150];
	char day_true_end_char[19];
	
	sprintf(request,"SELECT CURRENT_TIMESTAMP();");
	day_true_end_char = mysql_query(mysql,request);
	
	sprintf(request,"SELECT id_voiture FROM voiture WHERE plaque_immatriculation='%s' ",plaque_immatriculation);
    mysql_query(mysql,request);

	MYSQL_RES *result = NULL;
    MYSQL_ROW row;
	
    result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);
	id_voiture = row[0];
	if(id_voiture != 0)
	{
		sprintf(request,"UPDATE reservation SET date_true_end='%s',fini=1 WHERE id_voiture='%d' AND fini=0 AND actif=1 ",day_true_start_char);
		mysql_query(mysql,request);
			
		sprintf(request,"SELECT * FROM reservation WHERE id_voiture='%d' AND fini=1 AND actif=1 AND paye=0 ",id_voiture);
		    mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);
		if(row == NULL)
			printf("Bill is printing...");
			admin_facture(mysql,id_voiture);
		else
			printf("ERROR : The booking doesn't exist \n please contact an administrator");
	}
	else
	{
		printf("ERROR : The specified car doesn't exist")
	}
	
}