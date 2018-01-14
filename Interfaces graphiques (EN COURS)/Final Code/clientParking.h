int client_sign_in(MYSQL* mysql,char *nom,char *prenom,char *mdp,char *mail);
int client_cb_register(MYSQL *mysql,char* account_number,char *crypto,char* expiration,char* mail);

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

	sprintf(request,"SELECT * FROM proprietaire WHERE  mail = '%s'",mail);
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	row = mysql_fetch_row(result);

	if(row == NULL)
	{
		sprintf(request,"INSERT INTO `proprietaire`(`nom`, `prenom`, `password`, `mail`) VALUES ('%s','%s','%s','%s')",nom,prenom,mdp,mail);
		mysql_query(mysql,request);


		sprintf(request,"SELECT * FROM proprietaire WHERE  mail = '%s'",mail);
		mysql_query(mysql,request);
		result = mysql_use_result(mysql);
		row = mysql_fetch_row(result);

		if(row != NULL)
		{
		    printf("Account successfully created\n");
            return 0;
		}
		else
		{
		    printf("ERROR : The account cannot be created\n");
            return 1;
		}
	}
	else
	{
		printf("ERROR : The account already exist\n");
        return 2;
	}
	mysql_free_result(result);
}

int client_cb_register(MYSQL *mysql,char* account_number,char *crypto,char* expiration,char* mail)
{
    char tempo[9]="%Y-%m-%d";
    printf("tempo : %s",tempo);
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char request[150];
    cb_user user_info;
    printf("number : %s\n",account_number);
	printf("crypto : %s\n",crypto);
	printf("expi month : %c%c\n",expiration[0],expiration[1]);
	printf("expi year : %c%c%c%c\n",expiration[2],expiration[3],expiration[4],expiration[5]);
	printf("mail : %s\n",mail);

	sprintf(request,"SELECT id_proprio FROM proprietaire WHERE  mail = '%s'",mail);
	mysql_query(mysql,request);
	result = mysql_use_result(mysql);
	if(result != NULL)
    {
        row = mysql_fetch_row(result);
        user_info.id_proprio = atoi(row[0]);
        sprintf(user_info.expi,"%c%c%c%c-%c%c-01",expiration[2],expiration[3],expiration[4],expiration[5],expiration[0],expiration[1]);
        sprintf(user_info.char_month_expi,"%c%c%",expiration[0],expiration[1]);
        sprintf(user_info.char_year_expi,"%c%c%c%c",expiration[2],expiration[3],expiration[4],expiration[5]);
        user_info.month_expi = atoi(user_info.char_month_expi);
        user_info.year_expi = atoi(user_info.char_year_expi);

        if(user_info.year_expi>=2018 || user_info.month_expi<=12 || user_info.month_expi>=1)
        {
            printf("expipipi : %s\n",user_info.expi);
            printf("user idididid : %d\n",user_info.id_proprio);

            sprintf(request,"INSERT INTO `cb`(`id_proprio`, `code_bancaire`, `crypto`, `date_expi`) VALUES (%d,'%s','%s',STR_TO_DATE('%s','%s'))",user_info.id_proprio,account_number,crypto,user_info.expi,tempo);
            printf("%s\n",request);
            mysql_query(mysql,request);
            /**IMPORTANT : this function doesn't add the line in database but when you use the sql line in database it works with the same instruction **/
            return 0;
        }
    }
    else
    {
        printf("ERROR : the account doesn't exist\n");
    }

    return 99;

}

