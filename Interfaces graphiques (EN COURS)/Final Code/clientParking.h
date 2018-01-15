int client_sign_in(MYSQL* mysql,char *nom,char *prenom,char *mdp,char *mail);
int client_cb_register(MYSQL *mysql,char* account_number,char *crypto,char* expiration,char* mail);
int client_booking_creation(MYSQL*mysql,int start_day,int start_month,int start_year,int start_hour,int start_min,int end_day,int end_month,int end_year,int end_hour,int end_min, int fuel,int cleaning,char *car_id);



typedef struct cb_user
{
    int id_proprio;
    char expi[10];
    int month_expi;
    int year_expi;
    char char_month_expi[2];
    char char_year_expi[4];
} cb_user;





int client_sign_in(MYSQL* mysql,char *nom,char *prenom,char *mdp,char *mail)
{
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char request[150];

	sprintf(request,"SELECT * FROM proprietaire");
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	while ((row = mysql_fetch_row(result)))
    {
        if(strcmp(row[4],mail) == 0)
            {
                printf("ERROR : The account already exist\n");
                return 99;
            }
    }

    sprintf(request,"INSERT INTO `proprietaire`(`nom`, `prenom`, `password`, `mail`) VALUES ('%s','%s','%s','%s')",nom,prenom,mdp,mail);
	mysql_query(mysql,request);

	sprintf(request,"SELECT * FROM proprietaire");
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
    while ((row = mysql_fetch_row(result)))
    {
        if(strcmp(row[4],mail) == 0)
            {
                printf("Account successfully created\n");
                return 0;
            }
    }

    printf("ERROR : The account cannot be created\n");
    return 1;
	mysql_free_result(result);
}

int client_cb_register(MYSQL *mysql,char* account_number,char *crypto,char* expiration,char* mail)
{
    char tempo[9]="%Y-%m-%d";
    printf("tempo : %s",tempo);
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int flag = 0;
    char request[150];
    cb_user user_info;
    printf("number : %s\n",account_number);
	printf("crypto : %s\n",crypto);
	printf("expi month : %c%c\n",expiration[0],expiration[1]);
	printf("expi year : %c%c%c%c\n",expiration[2],expiration[3],expiration[4],expiration[5]);
	printf("mail : %s\n",mail);

	sprintf(request,"SELECT * FROM proprietaire");
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
    while ((row = mysql_fetch_row(result)))
    {
        if(strcmp(row[4],mail) == 0)
            {
                user_info.id_proprio = atoi(row[0]);
                flag = 1;
                break;
            }
    }
    if(flag==0);
    {
        printf("ERROR : the account doesn't exist\n");
        return 99;
    }
        sprintf(user_info.expi,"%c%c%c%c-%c%c-01",expiration[2],expiration[3],expiration[4],expiration[5],expiration[0],expiration[1]);
        sprintf(user_info.char_month_expi,"%c%c",expiration[0],expiration[1]);
        sprintf(user_info.char_year_expi,"%c%c%c%c",expiration[2],expiration[3],expiration[4],expiration[5]);
        user_info.month_expi = atoi(user_info.char_month_expi);
        user_info.year_expi = atoi(user_info.char_year_expi);
        mysql_free_result(result);
        if(user_info.year_expi>=2018 || user_info.month_expi<=12 || user_info.month_expi>=1)
        {
            sprintf(request,"INSERT INTO cb(`id_proprio`, `code_bancaire`, `crypto`,`date_expi`) VALUES (%d,'%s','%s',NULL);",user_info.id_proprio,account_number,crypto);
            printf("%s\n",request);
            mysql_query(mysql,request);
            sprintf(request,"UPDATE cb SET date_expi ='%s' WHERE id_proprio = %d;",user_info.expi,user_info.id_proprio);
            mysql_query(mysql,request);
            return 0;
        }
    return 99;
}

int client_booking_creation(MYSQL*mysql,int start_day,int start_month,int start_year,int start_hour,int start_min,int end_day,int end_month,int end_year,int end_hour,int end_min, int fuel,int cleaning,char *car_id)
{
    int flag=0;
    char id_voiture[2];
    char date_start[20];
    char date_end[20];
    int cleaning_in=0;
    int cleaning_out=0;
    int cleaning_both=0;


    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char request[1000];

    sprintf(request,"SELECT * FROM voiture");
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
    while ((row = mysql_fetch_row(result)))
    {
        if(strcmp(row[2],car_id) == 0)
            {
                strcpy(id_voiture,row[0]);
                flag=1;
                break;
            }
    }
    mysql_free_result(result);

    if(flag==0)
    {
        printf("ERROR : The car isn't registered\n");
        return 99;
    }

    sprintf(request,"SELECT * FROM reservation");
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
    while ((row = mysql_fetch_row(result)))
    {
        if(row[1]==id_voiture)
            {
                if(row[9]==0 || row[10]==0)
                {
                    printf("ERROR : already a booking active \n");
                    return 2;
                }
            }
    }
    mysql_free_result(result);
    printf("start hour %.2d\n",start_hour);
    sprintf(date_start,"%d-%.2d-%.2d %.2d:%.2d:00",start_year,start_month,start_day,start_hour,start_min);
    sprintf(date_end,"%d-%.2d-%.2d %.2d:%.2d:00",end_year,end_month,end_day,end_hour,end_min);
    printf("%s\n",date_start);
    printf("%s\n",date_end);

    if(cleaning == 1)
    {
        cleaning_in=1;
    }
    else if(cleaning == 2)
    {
        cleaning_out=1;
    }
    else if(cleaning == 3)
    {
        cleaning_both=1;
    }
    printf("cleaning in %d\n",cleaning_in);
    printf("cleaning out %d \n",cleaning_out);
    printf("cleaning both : %d \n",cleaning_both);
    printf("id_voiture : %s \n",id_voiture);


    sprintf(request,"INSERT INTO `reservation`(`id_voiture`, `date_prevue_start`, `date_prevue_end`, `date_true start`, `date_true_end`, `lavage_int`, `lavage_ext`, `lavage_total`, `essence`) VALUES (%s,'%s','%s',NULL,NULL,%d,%d,%d,%d)",id_voiture,date_start,date_end,cleaning_in,cleaning_out,cleaning_both,fuel);
	mysql_query(mysql,request);


    mysql_free_result(result);

}


