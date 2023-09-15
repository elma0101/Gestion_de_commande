#ifndef PROJET2_H_INCLUDED
#define PROJET2_H_INCLUDED
#define TRUE 1
#define FALSE 0

//definition des structures

typedef struct date
{
    int jour, mois,annee;
} date;



typedef struct produit
{
    char nom[20],referencee[20],categorie[20],marque[20];
    int qtq_stock;

} produit;

typedef struct lignecommande
{

    produit prod;
    int qtq_achete,num_cmd;

} lignecommande;
typedef struct element
{
    lignecommande ligne_cmd;
    int num_cmd;

} element;
typedef struct listelignecommande
{
    element elm;
    struct listelignecommande *precedent,*suivant;

} listelignecommande;

typedef struct liste_produit
{
    produit prd;
    struct liste_produit *precedent,*suivant;

} liste_produit;


typedef struct commande
{
    listelignecommande *lst_ligne_cmd;
    float montant_HT,montant_TVA,montant_TTC;
    int num_cmd;
    date date_cmd;
    char nom_client[40];

} commande;

typedef struct liste_commande
{
    commande  cmd;
    struct liste_commande *precedent,*suivant;

} liste_commande;
// fonction additionnels

int comparer_date(date,date );
liste_produit* lire_fichier_produit();
listelignecommande* lire_fichier_ligne_cmd();
liste_commande* lire_fichier_cmd(listelignecommande *lst_lgn_cmd);
void sauvegarder_produits(liste_produit* );
void sauvegarder_ligne_commande(listelignecommande* );
void sauvegarder_commande(liste_commande* );

// fonction de saisie

produit saisir_produit();
lignecommande saisir_lignecmd();
commande saisr_cmd(listelignecommande *list_ligne_cmd);

// fonction de recherche

int chercher_prd_nom(liste_produit* );
int chercher_prd_reference();
int chercher_prd_categorie();
int chercher_prd_marque();

// fonction d'ajout

liste_produit* ajouter_produit(liste_produit*,produit );
listelignecommande* ajouter_lignecommande(listelignecommande*,element);
liste_commande* ajouter_commande(liste_commande*,commande);

// fonction de suppression

liste_produit* supprimer_produit(liste_produit* );
listelignecommande* supprimer_lignecommande(listelignecommande* ,char*);
liste_commande* supprimer_commande(liste_commande* ,listelignecommande*  );

// fonction d'affichage

void afficher_produit(liste_produit*  );
int afficher_produit_rupture(liste_produit* );
void afficher_commande(liste_commande* );

#endif // PROJET2_H_INCLUDED
