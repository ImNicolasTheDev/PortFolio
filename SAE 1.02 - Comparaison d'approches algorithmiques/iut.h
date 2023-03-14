#include <stdio.h>
// Structure pour stocker les informations sur un choix d'un candidat
typedef struct{
    float Francais;
    float Maths;
    float Anglais;
}note;

typedef struct liste2 {
  char ville[50];
  char departement[50];
  int decision;
  int validation;
  struct liste2 *suivant;
} Choix, *ListeC;

typedef struct liste1{
  int numero;
  char nom[50];
  char prenom[50];
  note note;
  float moy;
  int nb_choix;
  ListeC lchoix;
  struct liste1 *suivant;
} Candidat;


typedef struct liste{
    char departement[30];
    int nbP;
    char resp[30];
    char AouD;
    struct liste *suivant;
}MaillonDept, *ListeD;

typedef struct{
    char ville[30];
    int nbDep;
    ListeD ldept;
}VilleIUT;


typedef enum {faux,vrai}Booleen;

//Menu utilisateur :
    void MenuUtilisateur(VilleIUT *tiut[],int n);
	int rechercheIUT(VilleIUT *tiut[],int n);
	int rechercheDept(VilleIUT *tiut[], int n);
	int recherchePlaces(VilleIUT *tiut[], int n);
    int rechercheMixed(VilleIUT *tiut[], int n);

//Menu administrateur : 
    void MenuAdministrateur(VilleIUT *tiut[],int n);  
    ListeD suppression(ListeD ld,char *departement);
    ListeD suppressionTete(ListeD ld);
    ListeD Enfiler(ListeD ld, char *departement, int nbP,char *resp);
    ListeD ModifinbP(ListeD ld, char departement[30], int MnbP, int n);
    ListeD ModifiRespon(ListeD ld, char departement[30], char respon[30], int n);
    ListeD ModifiAouD(ListeD ld, char departement[30], char AouD, int n);

//Menu Candidat 
    void MenuCandidat(Candidat *tcandidat[],VilleIUT *tiut[],int nc);
    void afficheCandidat(Candidat *tcandidat[], int i);
    int rechercheCandidatParDeaprtement(ListeC ld,char *departement, int nc);
    int rechercheCandidatParVille(ListeC ld, char *departement ,char *Ville, int nc);
    int verificationid(Candidat *tcandidat[], int numero, int nc);
    ListeC modifCandidat(ListeC ld, char *departement, char *newdepart, char *Ville, char *newVille, int n);
    ListeC ajoutCandidat(ListeC ld, char *departement, char *ville);
    ListeC suppressionCandidat(ListeC ld,char *departement, char *ville);
    ListeC suppressionTeteCandidat(ListeC ld);

//Menu Responsable
    void MenuRespon(Candidat *tcandidat[], VilleIUT *tiut[], int n,int nc);

//Liste:
    VilleIUT Initialisation(void);
    Booleen testVide(VilleIUT V);
    void afficher (VilleIUT V);
    VilleIUT defiler(VilleIUT V);

    //chargement Ville+departement
    int chargement(VilleIUT *tiut[],int tmax);
    MaillonDept lireDep(FILE *fe);
    VilleIUT lireVille(FILE *fe);
    ListeD Insertion(ListeD ld, char *departement, int nbP,char *resp, char AouD);
    ListeD InsertionTete(ListeD ld, char *departement, int nbP,char *resp, char AouD);
    void affichage (VilleIUT *tiut[],int n);
    void affichageListe(ListeD ld);

    //Candidat+choix
    int chargementcandidat(Candidat *tcandidat[],int tmax);
    Candidat lireCandidat(FILE *fe1);
    Choix lireChoix(FILE *fe1);
    ListeC InsertionTeteCandidat(ListeC ld, char *ville, char *departement, int decision, int validation);        ListeC InsertionCandidat(ListeC ld, char *ville, char *departement, int decision, int validation);
    void affichageCandidatchoix(Candidat *tcandidat[],int n);
    void affichageListeCandidatchoix(ListeC ld);
        
    // fonction de sauvegarde
    int fsauvegarde(VilleIUT *tiut[], Candidat *tcandidat[], int n, int nc, int choix, int tmax);
