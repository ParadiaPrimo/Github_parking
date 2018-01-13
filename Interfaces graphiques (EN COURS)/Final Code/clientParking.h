
void client_sing_in(MYSQL* mysql,char *nom,char *prenom,char *mdp,char *mail);


void client_sing_in(MYSQL* mysql,char *nom,char *prenom,char *mdp,char *mail)
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
			printf("Account successfully created\n");
		else
			printf("ERROR : The account cannot be created\n");

	}
	else
	{
		printf("ERROR : The account already exist\n");
	}
	mysql_free_result(result);
}
