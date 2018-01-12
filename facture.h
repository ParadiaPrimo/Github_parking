void facture_check(MYSQL *mysql);


typedef struct Info
{
    int id_user;
    int id_car;
    int id_booking;
    char plate[15];
    char name[50];
    char surname[50];
    int subscribe;
    char bank[16];
} Info;

typedef struct Date
{
    char initial_date[20];
    char final_date[20];
    char real_initial_date[20];
    char real_final_date[20];

} Date;

typedef struct Bonus_price
{
    int cleaning_out;
    int cleaning_in;
    int cleaning_both;
    double fuel;
    int penality;
    float hour;
    double total;

} Bonus_price;

void facture_check(MYSQL *mysql)
{
    Info user;
    Date booking;
    Bonus_price price;
    price.penality = 0;
    long date_one = 0;
    long date_two = 0;
    long date_real_one = 0;
    long date_real_two = 0;
    long hour_one = 0;
    long hour_two = 0;


    char tempo[8];
    char tempo2[4];
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    char request[150];
    strcpy(user.plate,"BATMOBILE!");

    /**R�cup�ration de toute les info de l'utilisateur**/
    sprintf(request,"SELECT id_voiture,id_proprio FROM voiture WHERE plaque_immatriculation='%s' AND etat = 1",user.plate);
    mysql_query(mysql,request);
    result = mysql_use_result(mysql);
    row = mysql_fetch_row(result);
    if(row!=NULL)
    {
        user.id_car=atoi(row[0]);
        user.id_user = atoi(row[1]);
    }
    mysql_free_result(result);

    sprintf(request,"SELECT nom,prenom,abonnement FROM proprietaire WHERE id_proprio=%d",user.id_user);
    mysql_query(mysql,request);
    result = mysql_use_result(mysql);
    row = mysql_fetch_row(result);
    if(row!=NULL)
    strcpy(user.name,row[0]);
    strcpy(user.surname,row[1]);
    user.subscribe = atoi(row[2]);
    mysql_free_result(result);

    sprintf(request,"SELECT code_bancaire FROM cb WHERE id_proprio='%d'",user.id_user);
    mysql_query(mysql,request);
    result = mysql_use_result(mysql);
    row = mysql_fetch_row(result);
    strcpy(user.bank,row[0]);
    mysql_free_result(result);



    sprintf(request,"SELECT * FROM reservation WHERE id_voiture = '%d' AND fini = 1 AND paye = 0",user.id_car);
    mysql_query(mysql,request);
    result = mysql_use_result(mysql);
    row = mysql_fetch_row(result);

    user.id_booking = atoi(row[0]);
    strcpy(booking.initial_date,row[2]);
    strcpy(booking.final_date,row[3]);
    strcpy(booking.real_initial_date,row[4]);
    strcpy(booking.real_final_date,row[5]);
    price.cleaning_in = atoi(row[6]);
    price.cleaning_out = atoi(row[7]);
    price.cleaning_both = atoi(row[8]);
    price.fuel = atof(row[9]);



    /**booking time**/
    sprintf(tempo,"%c%c%c%c%c%c%c%c",booking.initial_date[0],booking.initial_date[1],booking.initial_date[2],booking.initial_date[3],
                                    booking.initial_date[5],booking.initial_date[6],booking.initial_date[8],booking.initial_date[9]);
    date_one = atol(tempo);

    sprintf(tempo,"%c%c%c%c%c%c%c%c",booking.final_date[0],booking.final_date[1],booking.final_date[2],booking.final_date[3],
                                    booking.final_date[5],booking.final_date[6],booking.final_date[8],booking.final_date[9]);
    date_two = atol(tempo);

    sprintf(tempo,"%c%c%c%c%c%c%c%c",booking.real_initial_date[0],booking.real_initial_date[1],booking.real_initial_date[2],booking.real_initial_date[3],
                                    booking.real_initial_date[5],booking.real_initial_date[6],booking.real_initial_date[8],booking.real_initial_date[9]);
    date_real_one = atol(tempo);

    sprintf(tempo,"%c%c%c%c%c%c%c%c",booking.real_final_date[0],booking.real_final_date[1],booking.real_final_date[2],booking.real_final_date[3],
                                    booking.real_final_date[5],booking.real_final_date[6],booking.real_final_date[8],booking.real_final_date[9]);
    date_real_two = atol(tempo);

    if((date_real_one<date_one)||(date_real_two>date_two))
    {
        if(user.subscribe == 0)
        {
            price.penality = 20;
        }
        else if(user.subscribe == 1)
        {
            price.penality = 15;
        }
        else if(user.subscribe == 2)
        {
            price.penality = 5;
        }
    }
    sprintf(tempo2,"%c%c%c%c",booking.real_initial_date[11],booking.real_initial_date[12],booking.real_initial_date[14],booking.real_initial_date[15]);
    hour_one= atol(tempo2);
    sprintf(tempo2,"%c%c%c%c",booking.real_final_date[11],booking.real_final_date[12],booking.real_final_date[14],booking.real_final_date[15]);
    hour_two= atol(tempo2);

    price.hour = 0;
    if(hour_two<=hour_one)
    {
        if(user.subscribe == 0)
        {
            price.hour = (((float)hour_two-(float)hour_one)/100+24*(date_real_two-date_real_one))*3;
        }
        else
        {
            price.hour = (((float)hour_two-(float)hour_one)/100+(float)(date_real_two-date_real_one)*24);
        }
    }
    else
    {
        price.hour = (hour_two-hour_one);
    }


    if(price.cleaning_in != 0)
    {
         if(user.subscribe == 0)
        {
            price.cleaning_in = 25;
        }
        else if(user.subscribe == 1)
        {
            price.cleaning_in = 15;
        }
        else if(user.subscribe == 2)
        {
            price.cleaning_in = 15;
        }
    }

    if(price.cleaning_out != 0)
    {
         if(user.subscribe == 0)
        {
            price.cleaning_out = 20;
        }
        else if(user.subscribe == 1)
        {
            price.cleaning_out = 10;
        }
        else if(user.subscribe == 2)
        {
            price.cleaning_out = 10;
        }
    }

    if(price.cleaning_both != 0)
    {
         if(user.subscribe == 0)
        {
            price.cleaning_both = 35;
        }
        else if(user.subscribe == 1)
        {
            price.cleaning_both = 20;
        }
        else if(user.subscribe == 2)
        {
            price.cleaning_both = 20;
        }
    }

     if(user.subscribe == 0)
    {
        price.fuel *= 1.2;
    }
    else if(user.subscribe == 1)
    {
        price.fuel *= 0.9;
    }
    else if(user.subscribe == 2)
    {
        price.fuel *= 0.7;
    }

    /**
    clean in OK
    clean out OK
    clean both OK
    fuel OK
    hour OK
    penality OK
    **/

    mysql_free_result(result);




}
