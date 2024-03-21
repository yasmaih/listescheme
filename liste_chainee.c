#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>



typedef struct cell {
	int val;
	struct cell *suiv;
}liste;
typedef struct cell * liste_t;


liste_t cons (int nb, liste_t l) {
	liste_t new;
	//creer case de type liste_t
	new = (liste_t) malloc (sizeof(liste_t));
	//alloue la mémoire avec la taille du type
	assert(new);
	//!!penser a inserer assert.h
	new->val = nb;
	new->suiv = l;
	return new;
	//ajoute une case :)
}


//2 creer la liste
liste_t creer (int nb) {
	liste_t debut;
	int i, j, k, t;
	j = 13;
	k = 21;
	debut = (liste_t) 0;
	for (i = 0; i < nb; i++) {
		debut = cons (j, debut);
		t = (j + k) % 31;
		k = j;
		j = t;
	}
	return debut;
}


//Afficher la liste 
void Afficherliste (liste_t l);
void afflirec(liste_t l);
void affilistinv(liste_t l);



void Afficherliste(liste_t l){
	liste_t current = l;
	//element. actuel = l
	while(current!=NULL){
		//y'a la fonction (nestpasvide aussi,...ou (!l) bref
		printf("%d > ",current->val);
		current = current ->suiv;
	}
	printf("[ ]");
	//fin de la liste [0]
}


void afflirec (liste_t l){
	if(l!=NULL){
		printf("%d >",l->val);
		afflirec(l->suiv);
	}else {
		printf("[ ]");
	}
}


void affReverse(liste_t l){
	if (l!=NULL){
		affReverse(l->suiv);
		printf(" < %d ",l->val );
	}else {
		printf("[ ]");
	}
}




//Insertion et modification de la liste 

//a)inserer au debut
liste_t modifiel(liste_t l,int nouvelleVal){

	liste_t nvELt = malloc(sizeof(liste));
	nvELt->val = nouvelleVal;

	if(l!= NULL){
		nvELt->suiv = l;


	}else {
		nvELt->suiv = NULL;
	}
	return nvELt;
}

//b)inserer a la fin de la liste
 liste_t insererFin (liste_t l, int nb){

//On crée notre nouveau bloc a inserer 
	liste_t caseFin = malloc(sizeof(liste));

//ce bloc prends la valeur que l'on souhaite inserer
	caseFin->val = nb;

	caseFin->suiv = NULL;
/*
	etant donne que l'on veut se placer a la fin de la liste 
	l'élèment suivant point vers NULL
	*/

	liste_t caseActul = l;

//si notre liste de base est nulle alors on retour le nouvel element
	if(!l){
		return caseFin;
	}else{
//current va avancer jusqu'a qu'il y a rien donc null, puis on reassigne courrant le dernier element
		while(caseActul->suiv != NULL){
			caseActul = caseActul->suiv;
		}
	}
	//on insere le nvele a la fin
	caseActul->suiv = caseFin;
	return l;
}

//c) inserer un element a la fin de maniere recursive 
liste_t insererFinRec(liste_t l,int valeur){
	if(l == NULL){
		//si on est a la fin de la liste 
		liste_t nvEle = malloc(sizeof(liste));
		//on alloue une nvl case pour l'element a inserer
		nvEle->val = valeur;
		//on lui attribue la valeur que l'on desireras inserer
		nvEle->suiv = NULL; //on mets bien cet element avant le null 
		return nvEle;
	}else{
		l->suiv = insererFinRec(l->suiv,valeur);
		//ca seras egal a ce que ce retourneras cette fonction jusqu'a null
	}
	return l;
	//alors la on retourne le resultat de tout nos appels recursifs
}

//2) Inserer a un certain endroit 
liste_t insertionC (liste_t l, int valeur){
	liste_t nvEle = malloc(sizeof(liste));
	if(l == NULL){
		nvEle->val = valeur;
		nvEle->suiv = NULL;
		return nvEle;
	}else {
		if(valeur < l->val)
			return modifiel(l,valeur);

		else{
			liste_t current = l;
			liste_t suivant = l->suiv;

			while(suivant != NULL && suivant->val < valeur){
			//tant que je ne suis pas au bout de la liste 
			//et que la
			//valeur suivante est inferieure a la valeur inseree
				suivant = suivant->suiv;
				current = current->suiv;
			//je fais avancer mes deux pointzurs 
			}
			nvEle->val = valeur;
		nvEle->suiv = suivant; //la ou s'arrete 
		current->suiv = nvEle; //on insere la valeur entre suivant et courrant
		return l;
	}
}
}


//Trier la liste 
liste_t insererTrieDecroissant(liste_t l, int valeur) {
	liste_t nouveau = malloc(sizeof(liste));
	nouveau->val = valeur;
	nouveau->suiv = NULL;

	if (l == NULL || valeur >= l->val) {
		nouveau->suiv = l;
		return nouveau;
	} else {
		liste_t courant = l;
		while (courant->suiv != NULL && courant->suiv->val > valeur) {
			courant = courant->suiv;
		}
		nouveau->suiv = courant->suiv;
		courant->suiv = nouveau;
		return l;
	}
}


liste_t trierListeDecroissant(liste_t l) {
	liste_t listeTriee = NULL;
	liste_t courant = l;

	while (courant != NULL) {
		listeTriee = insererTrieDecroissant(listeTriee, courant->val);
		courant = courant->suiv;
	}

	return listeTriee;
}


//Supprimer un element de la liste 

liste_t supprimer (liste_t l, int valeur){

	if(l == NULL){
		printf("Liste vide, pas de suppression possible\n");
		//si la liste est vide il n'a rien a supprime
	}else {
		//Si la valeur que je vuex supprimer est dans le premier element alors 
		//on retourne directement la valeur qui suis
		if(l->val == valeur){
			return l->suiv;
		} else {
		//alors la nouvelle liste est la valeur suivante
			liste_t current = l;
		//premiere
			liste_t next = l->suiv;
		//deuxieme position
			while(next!= NULL && next->val != valeur){
			//tant que je ne suis pas arriver a une liste vide 
			//et 
			// que je n'ai pas trouver l'element que je veux suppriùmer
			next = next->suiv;
			current = current->suiv;
			//on fait un parcours de notre liste d'element en element 
			}
		//soit la valeur n'est pas de bloc alors pas de supper
			if (next == NULL){
				printf("pas de bloc, pas de suppression");
			}
			else{
			//sinon l'element avec la valeur est directement remplace par l'element qui le suis 
				current -> suiv = next->suiv;
			}
		}

	}
	return l;
}

liste_t concatenation(liste_t l, liste_t liste2){

	if(l==NULL) return liste2;
	if(liste2==NULL) return l;

	liste_t concat = NULL;
	liste_t current = l;

	while(current!=NULL){
		concat = insererFinRec(concat,current->val);
		current= current->suiv;
	}
	return concat;
}


int main(void) {
	liste_t l;
	int nb;
	nb = 10;
	l = creer(nb);
	printf("\n");
	printf("Affichage classique \n");
	Afficherliste(l);
	printf("\n");
	printf("\n");
	printf("Affichage recursif \n");
	afflirec(l);
	printf("\n");
	printf("\n");


	printf("Affichage recursif inversé \n");
	affReverse(l);
	printf("\n");
	printf("\n");


	printf("Inserer un element au debut de la liste \n");
	liste_t new = modifiel(l,0);
	Afficherliste(new);
	printf("\n");
	printf("\n");

	printf("Inserer un element a la fin de la liste \n");
	new = insererFin(new,34);
	Afficherliste(new);
	printf("\n");
	printf("\n");

	printf("Inserer un element a la fin de la liste recusrive \n");
	new = insererFinRec(new,34);
	Afficherliste(new);
	printf("\n");
	printf("\n");

	printf("Inserer un à un certain endroit de la liste\n");
	new = insertionC(new,22);
	Afficherliste(new);
	printf("\n");

	l = creer(nb);
l = trierListeDecroissant(l); // Tri décroissant de la liste
printf("\nListe triée en ordre décroissant : \n");
Afficherliste(l); // Affichage de la liste triée décroissante$
printf("\n");


printf("\nInsertion dans une liste triée en ordre décroissant : \n");
new = insererTrieDecroissant(l,22);
Afficherliste(new);
printf("\n");
printf("\n");

printf("Supprimer un elementde la liste \n");
l = supprimer(l,3);
Afficherliste(l);
printf("\n");
printf("\n");


return 0;
}

