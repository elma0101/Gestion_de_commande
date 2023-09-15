#include"projet2.h"
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

//lors de la saisie d un produit indisponible pour le supprimer ca cause la perte de la tete de la liste


int menu()
{
    int choix;

    system("cls");
    gotoxy(40,2);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB Gestion de commande \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(25,6);
    printf("---------------------------------------------------------------- ");
    gotoxy(25,7);
    printf("\xDB  1- consulter les produits                                    \xDB");
    gotoxy(25,8);
    printf("\xDB  2- consulter les produits en rupture de stock                \xDB");
    gotoxy(25,9);
    printf("\xDB  3- consulter une commande par son numero                     \xDB");
    gotoxy(25,10);
    printf("---------------------------------------------------------------- ");
    gotoxy(25,11);
    printf("\xDB  4- Chercher un produit                                       \xDB");
    gotoxy(25,12);
    printf("\xDB  5- Chercher les produits d'une categorie bien determine      \xDB");
    gotoxy(25,13);
    printf("\xDB  6- Chercher les produits d'une marque bien determine         \xDB");
    gotoxy(25,14);
    printf("---------------------------------------------------------------- ");
    gotoxy(25,15);
    printf("\xDB  7- Ajouter un produit                                        \xDB");
    gotoxy(25,16);
    printf("\xDB  8- Ajouter une commande                                      \xDB");
    gotoxy(25,17);
   printf("---------------------------------------------------------------- ");
    gotoxy(25,18);
    printf("\xDB  9- Supprimer un produit                                      \xDB");
    gotoxy(25,19);
    printf("\xDB  10- Supprimer une commande                                   \xDB");
    gotoxy(25,20);
    printf("\xDB  0- Quitter                                                   \xDB");
    gotoxy(25,21);
    printf("---------------------------------------------------------------- ");
    gotoxy(50,24);
    printf("Votre choix : ");
    scanf("%d",&choix);

    return choix;

}
int main()
{

     liste_produit *lst_prod=NULL;
     listelignecommande *lst_ligne_cmd=NULL;
     liste_commande* lst_cmd=NULL;

     produit prd;
     commande cmd;
     int ch,ch2;

     lst_prod=lire_fichier_produit();
     lst_ligne_cmd=lire_fichier_ligne_cmd();
     lst_cmd=lire_fichier_cmd(lst_ligne_cmd);



    do{

      ch=menu();

      switch(ch){

           case 1 :
               afficher_produit(lst_prod);
               if(lst_prod==NULL)
               {
                 gotoxy(45,15);
                 printf("\xDB PRODUIT INDISPONIBLE \n\n");
                 gotoxy(36,17);
                 system("pause");
               }else
                 system("pause");

               break;
           case 2 :

               if(!afficher_produit_rupture(lst_prod))
               {
                  gotoxy(45,15);
                  printf("\xDB PRODUIT EN RUPTURE INDISPONIBLE \n\n");
                  gotoxy(36,17);
                  system("pause");
               }else
                 system("pause");

               break;
          case 3 :
               afficher_commande(lst_cmd);
               break;
          case 4 :
              system("cls");
              gotoxy(40,2);
              printf("***Recherche de produit *** \n\n");
              printf("\t\t\xDB CHERCHER PRODUIT PAR : \n\n");
              printf("\t\t  1.NOM \n");
              printf("\t\t  2.REFERENCE \n\n\t\t\t votre choix :");
              scanf("%d",&ch2);
              getchar();
              switch(ch2){
                case 1 :
                     if(!chercher_prd_nom(lst_prod))
                     {
                        gotoxy(45,15);
                        printf("PRODUIT INDISPONIBLE");
                     }

                    break;
                case 2 :
                    if(!chercher_prd_reference(lst_prod))
                     {
                       gotoxy(45,15);
                       printf("PRODUIT INDISPONIBLE");
                     }
                    break;

              }
              gotoxy(36,17);
              system("pause");
              break;
          case 5 :
              getchar();
              if(!chercher_prd_categorie(lst_prod))
                printf("\nProduit indisponible \n\n");
              system("pause");
              break;
          case 6 :
              getchar();
              if(!chercher_prd_marque(lst_prod))
                printf("\nProduit indisponible \n\n");
              system("pause");
              break;
          case 7 :
              getchar();
              prd=saisir_produit();
              lst_prod=ajouter_produit(lst_prod,prd);
              break;
          case 8 :
              getchar();
              cmd=saisr_cmd(lst_ligne_cmd);
              lst_cmd=ajouter_commande(lst_cmd,cmd);
              break;
          case 9 :
              getchar();
              lst_prod=supprimer_produit(lst_prod);
              break;
          case 10 :
              getchar();
              lst_cmd=supprimer_commande(lst_cmd,lst_ligne_cmd);
              break;


      }



    }while(ch!=0);

    sauvegarder_produits(lst_prod);
    //sauvegarder_ligne_commande(lst_ligne_cmd);
    sauvegarder_commande(lst_cmd);

    return 0;
}
