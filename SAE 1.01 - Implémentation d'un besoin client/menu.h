int chargement(int *t1, int *t2, char *t3, int *t4,int *t5,int tmax);
int chargementAct(int *tAct, int *tNbEntree, int tmax);


//Fonctions Adhérent

int menuClient(void);
void rechargeCarte(int *t2, int rangId);
int choixActiv(int *t2, int nbPoints, int *tAct, int *tNbEntree, int *n, int tmax);

int identificationClient(int *t1, int *t2, int *n);
int rechercheIdentificationClient(int *t1, int *n, int client);

void fage(int rangId,int *t1,int *t2,char *t3,int *t4,int *t5,int *n);


//Fonctions Admin

void MenuAdmin(int *t1,int *t2,char *t3,int *t4,int *t5, int *tNbEntree, int *n,int tmax);

void affichage(int *t1,int *t2,char *t3,int *t4,int *t5, int *n);
void affichageUnA(int *t1,int *t2,char *t3, int *t4,int *t5,int *n);

int RechercheInsertion(int *t, int n, int val,int *trouve);
int FDesactiverActiver(int *t1,char *t3,int *n);
void affichageFreq(int *tNbEntree);

int Fcreer(int *n,int *t1,int *t2,char *t3,int *t4,int *t5,int tmax);
int Fsupprimer(int *t1,int *t2,char *t3,int *t4,int *t5,int *n);

int fsauvegarde(int *t1,int *t2,char *t3,int *t4,int *t5, int *tNbPoints, int *tNbEntree, int *n,int tmax, int choix);
