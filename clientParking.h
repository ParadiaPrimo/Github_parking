void client_add_car(MYSQL *mysql);
void client_take_reservation(MYSQL *mysql);
void client_cancel_reservation(MYSQL *mysql);
void client_modify_reservation(MYSQL *mysql);
void client_start_reservation(MYSQL *mysql);
void client_end_reservation(MYSQL *mysql);
void client_register_cb(MYSQL *mysql);
void client_subscribe(MYSQL *mysql);
void client_sing_in(MYSQL *mysql);



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

        /**ajouter le véhicule**/
        sprintf(request,"INSERT INTO voiture (`plaque_immatriculation`,`etat`) VALUES ('%s','0')",registration);
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
			printf("ERROR : The booking doesn't exist \n please contact an administrator\n");
	}
	else
	{
		printf("ERROR : The specified car doesn't exist\n")
	}
	
}

void client_register_cb(MYSQL *mysql)
{
	char request[150];
	int id_proprio;
	char cb_num[12];
	char expi[10];
	int exp_month;
	int exp_year;
	char crypto[3];
	
	/**recup les info**/
	
	/****/
	sprintf(expi,"%s-%s-01",exp_year,_exp_month);
	
	/**Vérif duplication du code**/
	sprintf(request,"SELECT * FROM cb WHERE code_bancaire = '%s'",cb_num);
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);
		
	if(row == NULL)
	{
		sprintf(request,"INSERT INTO cb ('code_bancaire','crypto','date_expi') VALUES('%s','%s','%s') ",cb_num,crypto,expi);
		mysql_query(mysql,request);
		
			
		sprintf(request,"SELECT * FROM cb WHERE code_bancaire = '%s'",cb_num);
		mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);

		if(row != NULL)
			printf("Card successfully registered\n");
		else
			printf("ERROR : The card cannot be registered\n");
	}
	else
	{
		printf("ERROR : The card is already registered\n")
	}
}

void client_subscribe(MYSQL *mysql)
{
	int option;	
	char request[150];
	int id_proprio;
	
	sprintf(request,"SELECT abonnement FROM proprietaire WHERE id_proprio = '%d'",id_proprio);
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);

	if(option > row[0] )
	{
		sprintf(request,"UPDATE proprietaire SET abonnement = '%d' WHERE id_proprio = '%d'",option,id_proprio);
	mysql_query(mysql,request);
	}
	else
	{
		printf("ERROR : you have greater subscribe activated")
	}	
}

void client_sing_in(MYSQL *mysql)
{
	char nom[50];
	char prenom[50];
	char mdp[50];
	char mail[50]
	
	sprintf(request,"SELECT * FROM proprietaire WHERE  mail = '%s'",mail);
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);

	if(row == NULL)
	{
		sprintf(request,"INSERT INTO proprietaire ('nom','prenom','password','mail' ) VALUES ('%s','%s','%s','%s' )",nom,prenom,mdp,mail);
		mysql_query(mysql,request);
		
		
		sprintf(request,"SELECT * FROM proprietaire WHERE  mail = '%s'",mail);
		mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);
		
		if(row != NULL)
			printf("Account successfully created\n");
		else
			printf("ERROR : The account cannot be created\n");
		
	}
	else
	{
		printf("ERROR : The account already exist\n")
	}
	
	
}