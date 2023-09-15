#include"projet2.h"
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

// fonction additionnels

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int comparer_date(date date1,date date2)
{
    if(date1.annee>date2.annee || (date1.annee==date2.annee && date1.mois>date2.mois) || (date1.annee==date2.annee && date1.mois==date2.mois && date1.jour>date2.jour))
        return 1;
    else if(date1.annee==date2.annee && date1.mois==date2.mois && date1.jour==date2.jour)
        return 0;

    return -1;
}

liste_produit* lire_fichier_produit()
{
    FILE *fprd;
    liste_produit *lst_prd=NULL,*courant=lst_prd,*nv=malloc(sizeof(liste_produit));



    fprd=fopen("produits.txt","r");

    while(fscanf(fprd,"%s%s%s%s%d",nv->prd.nom,nv->prd.referencee,nv->prd.categorie,nv->prd.marque,&nv->prd.qtq_stock)!=EOF)
    {
        courant=lst_prd;

        if(lst_prd==NULL)
        {
            nv->precedent=NULL;
            nv->suivant=NULL;
            lst_prd=nv;
        }
        else
        {
            while(courant->suivant!=NULL)
                courant=courant->suivant;
            courant->suivant=nv;
            nv->precedent=courant;
            nv->suivant=NULL;


        }

        nv=malloc(sizeof(liste_produit));

    }

    fclose(fprd);

    return lst_prd;
}

listelignecommande* lire_fichier_ligne_cmd()
{
    FILE *flc;
    listelignecommande *lst_ligne_cmd=NULL,*nv=malloc(sizeof(listelignecommande)),*courant;




    flc=fopen("lignecommande.txt","r");

    while(fscanf(flc,"%d%s%s%s%s%d%d",&nv->elm.num_cmd,nv->elm.ligne_cmd.prod.nom,nv->elm.ligne_cmd.prod.referencee,nv->elm.ligne_cmd.prod.categorie,nv->elm.ligne_cmd.prod.marque,&nv->elm.ligne_cmd.prod.qtq_stock,&nv->elm.ligne_cmd.qtq_achete)!=EOF)
    {
        courant=lst_ligne_cmd;
        if(lst_ligne_cmd==NULL)
        {
            nv->precedent=NULL;
            nv->suivant=NULL;
            lst_ligne_cmd=nv;
        }
        else
        {
            while(courant->suivant!=NULL)
                courant=courant->suivant;
            courant->suivant=nv;
            nv->precedent=courant;
            nv->suivant=NULL;


        }
        nv=malloc(sizeof(listelignecommande));

    }

    fclose(flc);

    return lst_ligne_cmd;
}

liste_commande* lire_fichier_cmd(listelignecommande *lst_lgn_cmd)
{
    FILE *fc,*fl;
    liste_commande *lst_cmd=NULL,*courant2,*nv=malloc(sizeof(liste_commande));
    listelignecommande *courant1,*courant3,*nv2=malloc(sizeof(listelignecommande));
    int i=0;


    fc=fopen("commande.txt","r");

    while(fscanf(fc,"%d%d%d%d%s%f%f%f",&nv->cmd.num_cmd,&nv->cmd.date_cmd.jour,&nv->cmd.date_cmd.mois,&nv->cmd.date_cmd.annee,nv->cmd.nom_client,&nv->cmd.montant_HT,&nv->cmd.montant_TVA,&nv->cmd.montant_TTC)!=EOF)
    {
        courant1=lst_lgn_cmd;
        courant2=lst_cmd;
        i=0;

        while(courant1!=NULL)
        {

            if(courant1->elm.num_cmd==nv->cmd.num_cmd)
            {
                nv2->elm=courant1->elm;
                courant3=nv->cmd.lst_ligne_cmd;
                if(i==0) //je pouvais pas utiliser courant3->prec
                {
                    //nv2->precedent=NULL;
                    nv2->suivant=NULL;
                    nv->cmd.lst_ligne_cmd=nv2;
                    i++;
                }
                else
                {
                    while(courant3->suivant!=NULL)
                        courant3=courant3->suivant;
                    courant3->suivant=nv2;
                    //nv2->precedent=courant3;
                    nv2->suivant=NULL;


                }
                nv2=malloc(sizeof(listelignecommande));

            }
            courant1=courant1->suivant;
        }



        nv->precedent=NULL;
        nv->suivant=lst_cmd;
        //lst_cmd->precedent=nv;
        //prob1 je sais pas pourquoi pas fonctionant
        lst_cmd=nv;

        nv=malloc(sizeof(liste_commande));

    }

    fclose(fc);

    return lst_cmd;
}

void sauvegarder_produits(liste_produit *lst_prd)
{
    FILE *fprd;
    liste_produit *courant=lst_prd;


    fprd=fopen("produits.txt","w");

    while(courant!=NULL)
    {
        fprintf(fprd,"%s %s %s %s %d \n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
        courant=courant->suivant;
    }

    fclose(fprd);

}

void sauvegarder_ligne_commande(listelignecommande *lst_ligne_cmd)
{
    FILE *flc;
    listelignecommande *courant=lst_ligne_cmd;


    flc=fopen("lignecommande.txt","w");

    while(courant!=NULL)
    {
        fprintf(flc,"%d %s %s %s %s %d %d\n",courant->elm.num_cmd,courant->elm.ligne_cmd.prod.nom,courant->elm.ligne_cmd.prod.referencee,courant->elm.ligne_cmd.prod.categorie,courant->elm.ligne_cmd.prod.marque,courant->elm.ligne_cmd.prod.qtq_stock,courant->elm.ligne_cmd.qtq_achete);
        courant=courant->suivant;
    }

    fclose(flc);

}

void sauvegarder_commande(liste_commande *lst_cmd)
{
    FILE *fc,*fl;
    liste_commande *courant=lst_cmd;



    fc=fopen("commande.txt","w");


    while(courant!=NULL)
    {
        fprintf(fc,"%d %2d %2d %2d %s %g %g %g\n",courant->cmd.num_cmd,courant->cmd.date_cmd.jour,courant->cmd.date_cmd.mois,courant->cmd.date_cmd.annee,courant->cmd.nom_client,courant->cmd.montant_HT,courant->cmd.montant_TVA,courant->cmd.montant_TTC);
        courant=courant->suivant;
    }

    fclose(fc);

}

//fonction de saisie

produit saisir_produit()
{
    produit prd;

    system("cls");
    gotoxy(40,2);
    printf("***traitement de produit*** \n\n");
    printf("\n\t\t\xDB NOM : \t");
    gets(prd.nom);
    printf("\t\t\xDB REFERENCE : \t");
    gets(prd.referencee);
    printf("\t\t\xDB CATEGORIE : \t");
    gets(prd.categorie);
    printf("\t\t\xDB MARQUE : \t");
    gets(prd.marque);
    printf("\t\t\xDB QUANTITE EN STOCK : \t");
    scanf("%d",&prd.qtq_stock);



    return prd;
}

lignecommande saisir_lignecmd()
{
    lignecommande lignecmd;

    system("cls");

    printf("\t\t\t***Traitement de ligne de commande *** \n");
    lignecmd.prod=saisir_produit();
    printf("\t\t\xDB Quantite achetee : \t");
    scanf("%d",&lignecmd.qtq_achete);
    getchar();

    return lignecmd;
}


commande saisr_cmd(listelignecommande *list_ligne_cmd)
{
    commande cmd;
    element elm_ligne_cmd;
    char choix;

    system("cls");
    gotoxy(40,2);
    printf("*** Traitement de commande *** \n\n\n");
    printf("\t\t \xDB NUMERO DE COMMANDE  : \t");
    scanf("%d",&cmd.num_cmd);
    printf("\t\t \xDB DATE DE COMMANDE (jj/mm/aa) : \t");
    scanf("%d%d%d",&cmd.date_cmd.jour,&cmd.date_cmd.mois,&cmd.date_cmd.annee);
    printf("\t\t \xDB NOM/PRENOM CLIENT (nom-prenom): \t");
    getchar();
    gets(cmd.nom_client);
    printf("\t\t \xDBMontant HT :\t");
    scanf("%f",&cmd.montant_HT);
    printf("\t\t \xDBMontant TVA :\t");
    scanf("%f",&cmd.montant_TVA);
    printf("\t\t \xDBMontant TTC :\t");
    scanf("%f",&cmd.montant_TTC);
    //liste de ligne decommande

    do
    {
        getchar();
        elm_ligne_cmd.ligne_cmd=saisir_lignecmd();
        elm_ligne_cmd.num_cmd=cmd.num_cmd;
        cmd.lst_ligne_cmd=ajouter_lignecommande(cmd.lst_ligne_cmd,elm_ligne_cmd );

        list_ligne_cmd=ajouter_lignecommande(list_ligne_cmd,elm_ligne_cmd);
        system("cls");
        printf("continuer [o/n] ");
        choix=getchar();

    }while(choix!='n');
    
    sauvegarder_ligne_commande(list_ligne_cmd);


    return cmd;
}

//fonction de recherche


int chercher_prd_nom(liste_produit *lst_prd)
{
    liste_produit *courant=lst_prd;
    char *nom=malloc(20*sizeof(char));

    system("cls");
    gotoxy(40,2);
    printf("***Recherche de produit *** \n\n\n");
    printf("\t\t \xDB NOM DE PRODUIT : ");
    gets(nom);

    while(courant!=NULL && strcmp(courant->prd.nom,nom)!=0)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;

    printf("\n\t\t-----------------------------------------------------------------------------------------------------\n");
    printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
    printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
    printf("\n\t\t");
    return TRUE;

}

int chercher_prd_reference(liste_produit *lst_prd)
{
    liste_produit *courant=lst_prd;
    char *reference=malloc(20*sizeof(char));

    system("cls");
    gotoxy(40,2);
    printf("***Recherche de produit *** \n\n\n");
    printf("\t\t \xDB REFERENCE DE PRODUIT : ");
    gets(reference);

    while(courant!=NULL && strcmp(courant->prd.referencee,reference)!=0)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;

    printf("\n\t\t-----------------------------------------------------------------------------------------------------\n");
    printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
    printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
    printf("\n\t\t");
    return TRUE;

}

int chercher_prd_categorie(liste_produit *lst_prd)
{
    liste_produit *courant=lst_prd;
    char *categorie=malloc(20*sizeof(char));
    int flag=0;

    system("cls");
    gotoxy(40,2);
    printf("***Recherche de produit *** \n\n\n");
    printf("\t\t \xDB CATEGORIE DU PRODUIT : ");
    gets(categorie);

    while(courant!=NULL )
    {
        if(strcmp(courant->prd.categorie,categorie)==0)
        {
             printf("\n\t\t-----------------------------------------------------------------------------------------------------\n");
             printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
             printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
             printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
            flag=1;
        }
        courant=courant->suivant;
    }

    if(flag==0)
        return FALSE;
    printf("\n\t\t");
    return TRUE;

}

int chercher_prd_marque(liste_produit *lst_prd)
{
    liste_produit *courant=lst_prd;
    char *marque=malloc(20*sizeof(char));

    system("cls");
    gotoxy(40,2);
    printf("***Recherche de produit *** \n\n\n");
    printf("\t\t \xDB MARQUE DU PRODUIT : ");
    gets(marque);

    while(courant!=NULL && strcmp(courant->prd.marque,marque)!=0)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;

    printf("\n\t\t-----------------------------------------------------------------------------------------------------\n");
    printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
    printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
    printf("\n\t\t");
    return TRUE;

}


// fonction d'ajout

liste_produit* ajouter_produit(liste_produit *lst_prd,produit prd)
{
    liste_produit *courant=lst_prd,*nv=malloc(sizeof(liste_produit)),*prev=NULL;

    system("cls");

    while(courant!=NULL && courant->prd.qtq_stock>prd.qtq_stock)
    {
        prev=courant;
        courant=courant->suivant;
    }


    nv->prd=prd;
    nv->suivant=courant;
    nv->precedent=prev;


    if(prev==NULL)
    {
        courant->precedent=nv;
        lst_prd=nv;
    }
    else
    {

        if(courant!=NULL)
            courant->precedent=nv;

        prev->suivant=nv;

    }

    return lst_prd;
}

listelignecommande* ajouter_lignecommande(listelignecommande* lst_ligne_cmd,element elm_ligne_cmd)
{
    listelignecommande *courant=lst_ligne_cmd,*nv=malloc(sizeof(listelignecommande)),*prev=NULL;

    system("cls");

    while(courant!=NULL && courant->elm.ligne_cmd.qtq_achete>elm_ligne_cmd.ligne_cmd.qtq_achete)
    {
        prev=courant;
        courant=courant->suivant;
    }


    nv->elm=elm_ligne_cmd;
    nv->suivant=courant;
    nv->precedent=prev;


    if(prev==NULL)
    {
        courant->precedent=nv;
        lst_ligne_cmd=nv;
    }
    else
    {

        if(courant!=NULL)
            courant->precedent=nv;
        else
            nv->suivant=NULL;

        prev->suivant=nv;

    }

    return lst_ligne_cmd;
}

liste_commande* ajouter_commande(liste_commande* lst_cmd,commande cmd)
{
    liste_commande *courant=lst_cmd,*nv=malloc(sizeof(liste_commande)),*prev=NULL;

    system("cls");

    while(courant!=NULL && (comparer_date(courant->cmd.date_cmd,cmd.date_cmd)==1))
    {
        prev=courant;
        courant=courant->suivant;
    }


    nv->cmd=cmd;
    nv->suivant=courant;
    nv->precedent=prev;


    if(prev==NULL)
    {
        courant->precedent=nv;
        lst_cmd=nv;
    }
    else
    {

        if(courant!=NULL)
            courant->precedent=nv;

        prev->suivant=nv;

    }

    return lst_cmd;
}

//fonction de suppression

liste_produit* supprimer_produit(liste_produit* lst_prd)
{

    liste_produit *courant=lst_prd,*aide,*prev=NULL;
    char *reference=malloc(20*sizeof(char));

    system("cls");
    printf("\nReference :\t");
    gets(reference);


    while(courant!=NULL && strcmp(courant->prd.referencee,reference)!=0)
    {
        prev=courant;
        courant=courant->suivant;
    }

    if(courant==NULL)
        return FALSE;



    if(prev==NULL)
    {
        aide=lst_prd;
        lst_prd=lst_prd->suivant;
        if(courant->suivant!=NULL)
            lst_prd->precedent=NULL;

    }
    else
    {
        aide=courant;
        prev->suivant=courant->suivant;
        if(courant->suivant!=NULL)
        {

            courant->suivant->precedent=prev;
        }
    }

    free(aide);

    return lst_prd;

}

listelignecommande* supprimer_lignecommande(listelignecommande* lst_ligne_cmd,char* reference)
{

    listelignecommande *courant=lst_ligne_cmd,*aide,*prev=NULL;


    system("cls");



    while(courant!=NULL && strcmp(courant->elm.ligne_cmd.prod.referencee,reference)!=0)
    {
        prev=courant;
        courant=courant->suivant;
    }

    if(courant==NULL)
        return FALSE;

    aide=courant;

    if(prev==NULL)
    {
        lst_ligne_cmd=lst_ligne_cmd->suivant;
        if(courant->suivant!=NULL)
            lst_ligne_cmd->precedent=NULL;

    }
    else
    {
        prev->suivant=courant->suivant;
        if(courant->suivant!=NULL)
            courant->suivant->precedent=prev;
    }

    free(aide);

    return lst_ligne_cmd;

}

liste_commande* supprimer_commande(liste_commande* lst_cmd,listelignecommande *lst_ligne_cmd)
{

    liste_commande *courant=lst_cmd,*aide,*prev=NULL;
    listelignecommande *courant2,*courant3=lst_ligne_cmd;
    int num;

    system("cls");
    printf("\nNumero de commande :\t");
    scanf("%d",&num);


    while(courant!=NULL && courant->cmd.num_cmd!=num)
    {
        prev=courant;
        courant=courant->suivant;
    }

    if(courant==NULL)
        return FALSE;

    courant2=courant->cmd.lst_ligne_cmd;

    while(courant2!=NULL)
    {

        lst_ligne_cmd=supprimer_lignecommande(lst_ligne_cmd,courant2->elm.ligne_cmd.prod.referencee);

        courant2=courant2->suivant;
    }

    aide=courant;

    if(prev==NULL)
    {
        lst_cmd=lst_cmd->suivant;
        if(courant->suivant!=NULL)
            lst_cmd->precedent=NULL;

    }
    else
    {
        prev->suivant=courant->suivant;
        if(courant->suivant!=NULL)
            courant->suivant->precedent=prev;
    }

    free(aide);

    return lst_cmd;

}

// fonction d affichage

void afficher_produit(liste_produit* lst_prd)
{

    liste_produit *courant=lst_prd;

    system("cls");
    gotoxy(40,2);
    printf("*** TRAITEMENTS DE PRODUITS  *** \n\n\n");

    if(courant!=NULL){
     printf("\t\t-----------------------------------------------------------------------------------------------------\n");
     printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
     printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
     while(courant!=NULL)
     {
         printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
         courant=courant->suivant;
     }
     printf("\n\t\t");
    }
}

int afficher_produit_rupture(liste_produit* lst_prd)
{

    liste_produit *courant=lst_prd;

    system("cls");
    gotoxy(40,2);
    printf("*** PRODUITS EN RUPTURE DE STOCK *** \n\n\n");

    while(courant!=NULL && courant->prd.qtq_stock>=10)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;
    printf("\t\t-----------------------------------------------------------------------------------------------------\n");
    printf("\t\t NOM \t\t REFERENCE \t\t CATEGORIE \t\t MARQUE \t\t QTQ STOCK \n");
    printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
    while(courant!=NULL)
    {
        printf("\t\t%-16s %-25s%-23s%-25s%-20d\n\n",courant->prd.nom,courant->prd.referencee,courant->prd.categorie,courant->prd.marque,courant->prd.qtq_stock);
        courant=courant->suivant;
    }
    printf("\n\t\t");
    return TRUE;
}

void afficher_commande(liste_commande* lst_cmd)
{
    liste_commande *courant=lst_cmd;
    listelignecommande *courant2;
    int num;

    system("cls");
    gotoxy(40,2);
    printf("*** AFFICHAGE DE COMMANDE *** ");
    gotoxy(25,10);
    printf("\xDB NUMERO DE COMMANDE : ");
    scanf("%d",&num);

    system("cls");
    gotoxy(40,2);
    printf("*** AFFICHAGE DE COMMANDE ***\n\n\n");

    while(courant!=NULL && courant->cmd.num_cmd!=num)
        courant=courant->suivant;

   if(courant!=NULL){

    courant2=courant->cmd.lst_ligne_cmd;
    printf("\t\t-----------------------------------------------------------------------------------------------\n");
    printf("\t\tN COMMANDE \t\t DATE \t\t NOM \t\t HT \t\t TVA \t\t TTC\n");
    printf("\t\t-----------------------------------------------------------------------------------------------\n\n");
    printf("\t\t    %-20d %d %d %-10d%-16s%-17g%-17g%g\n\n",courant->cmd.num_cmd,courant->cmd.date_cmd.jour,courant->cmd.date_cmd.mois,courant->cmd.date_cmd.annee,courant->cmd.nom_client,courant->cmd.montant_HT,courant->cmd.montant_TVA,courant->cmd.montant_TTC);
    printf("\t\t-----------------------------------------------------------------------------------------------\n\n");
    printf("\t\tNOM \t REFERENCE \t CATEGORIE \t MARQUE \t QTQ STOCK \t QTQ ACHETE\n\n");
    printf("\t\t-----------------------------------------------------------------------------------------------\n\n");
    while(courant2!=NULL)
    {
        printf("\t\t%-10s %-15s%-15s%-18s%-15d%d\n\n",courant2->elm.ligne_cmd.prod.nom,courant2->elm.ligne_cmd.prod.referencee,courant2->elm.ligne_cmd.prod.categorie,courant2->elm.ligne_cmd.prod.marque,courant2->elm.ligne_cmd.prod.qtq_stock,courant2->elm.ligne_cmd.qtq_achete);
        courant2=courant2->suivant;
    }
    printf("\n\n\t\t");
    system("pause");
   }else{

     gotoxy(45,15);
     printf("\xDB COMMANDE INDISPONIBLE \n\n");
     gotoxy(36,17);
     system("pause");
   }

}
void afficher_ligne_commande(listelignecommande *lst_ligne_cmd)
{
    listelignecommande *courant=lst_ligne_cmd;
    system("cls");

    while(courant!=NULL)
    {
        printf("\n%d\t%s\t%s\t%s\t%s\t%d\t%d \n",courant->elm.num_cmd,courant->elm.ligne_cmd.prod.nom,courant->elm.ligne_cmd.prod.referencee,courant->elm.ligne_cmd.prod.categorie,courant->elm.ligne_cmd.prod.marque,courant->elm.ligne_cmd.prod.qtq_stock,courant->elm.ligne_cmd.qtq_achete);
        courant=courant->suivant;
    }

}


