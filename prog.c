#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data_famille
{
    int codef;
    char nomf[100];
    char designationf[100];
};
typedef struct data_famille DATA_FAMILLE;

struct famille
{
    DATA_FAMILLE dfamille;
    struct famille *nextf;
};
typedef struct famille FAMILLE;


struct data_produit
{
    int codep;
    char nomp[100];
    int code_famille;
    char designationp[100];
    float coutp;
    int quantp;
};
typedef struct data_produit DATA_PRODUIT;
struct produit
{
    DATA_PRODUIT dproduit;
    struct produit *nextp;
};
typedef struct produit PRODUIT;


void view_entete()
{
	FILE *ft;
	char st[200];
	printf("|--------------------------------|\n");
	printf("|BIENVENUE Chez Notre Entreprise |\n");
	printf("|--------------------------------|\n");
	ft=fopen("en_téte","r");
	for(;fgets(st,100,ft);)
	{
		*(st+strlen(st)-1)='\0';
		puts(st);
	}
}

void extract(char* s,char** mot)
{
 
	int i;
	char s1[500];
	char c;
	*mot=(char*)malloc(500*sizeof(char));
	**mot='\0';
	strcpy(s1,s);
    for (i=0;(*(s1+i)!=' ')&&(*(s1+i));i++)
	{	c=*(s1+i);
		*(*mot+strlen(*mot))=c;
	}
	*(*mot+strlen(*mot))='\0';

}

void insert_famille(FAMILLE **firstf,char sf[])
{
	int j;
    char *motf;
    int c=0;
    FAMILLE *pf;
    pf=(FAMILLE *)malloc(sizeof(FAMILLE));
    extract(sf,&motf);
    c=atoi(motf);
    (pf->dfamille.codef)=c;
	j=strlen(motf)+1;
    extract(sf+j,&motf);
	strcat((pf->dfamille.nomf),motf);
	j=j+strlen(motf)+1;
    extract(sf+j,&motf);
    strcat((pf->dfamille.designationf),motf);
    pf->nextf=*firstf;
    *firstf=pf; 
}

void insert_produit(PRODUIT **firstp,char sp[])
{
	float co;
	int j;
    char *motp;
    int c;
    PRODUIT *pp;
    pp=( PRODUIT *)malloc(sizeof(PRODUIT));
    extract(sp,&motp);
    c=atoi(motp);
    (pp->dproduit.codep)=c;
	j=strlen(motp)+1;
    extract(sp+j,&motp);
	strcat((pp->dproduit.nomp),motp);
	j=j+strlen(motp)+1;
    extract(sp+j,&motp);
	c=atoi(motp);
	pp->dproduit.code_famille=c;
	j=j+strlen(motp)+1;
    extract(sp+j,&motp);
	strcat((pp->dproduit.designationp),motp);
	j=j+strlen(motp)+1;
    extract(sp+j,&motp);
	co=atof(motp);
	pp->dproduit.coutp=co;
	j=j+strlen(motp)+1;
    extract(sp+j,&motp);
	c=atoi(motp);
	pp->dproduit.quantp=c;
    pp->nextp=*firstp;
    *firstp=pp; 
}

int affiche_menu()
{
	int choix;
	printf("\n");
	printf("Choisisez : \n 1 : Etat Global Stock. \n 2 : Etat Produit Par Famille. \n 3 : Recap Famille. \n 4 : Suppression D'une Famille. \n 5 : Sauvegarder Un Produit. \n 0 : Quitter. \n");
	printf("tapez : ");
	scanf("%d",&choix);
	if ((choix<=5)&&(choix>=0))
	{
		return(choix);
	}
	else
	{
		printf("choix incorrecte, retapez \n tapez :");
		affiche_menu();
	}
}


float affiche_etat_global_stock(PRODUIT *firstp)
{
	float total_prix=0;
	PRODUIT *pp;
	printf("+----------------+----------------------+-----------------+------------------------------+----------+----------|\n");
	printf("|  Code Produit  |     Nom Produit      |   Code Famille  |     Designation Produit      |   cout   | Quantité |\n");
	printf("+----------------+----------------------+-----------------+------------------------------+----------+----------|\n");
	for(pp=firstp;pp;pp=pp->nextp)
	{ 
		printf("|%-16d|%-22s|%-17d",pp->dproduit.codep,pp->dproduit.nomp,pp->dproduit.code_famille);
		printf("|%-30s|%9f|%10d|\n",pp->dproduit.designationp,pp->dproduit.coutp,pp->dproduit.quantp);
		printf("+----------------+----------------------+-----------------+------------------------------+----------+----------|\n");
		total_prix += (pp->dproduit.coutp)*(pp->dproduit.quantp) ;
    }
return(total_prix);
}

void affiche_famille(FAMILLE *firstf)

{
	FAMILLE *pf;
	printf("\n");
	printf("+----------------+----------------------+-------------------------+\n");
	printf("|  Code famille  |     Nom famille      |   Designation Produit   |\n");
	printf("+----------------+----------------------+-------------------------+\n");
	for(pf=firstf;pf;pf=pf->nextf)
	{ 
		printf("|%-16d|%-22s|%-25s|\n",pf->dfamille.codef,pf->dfamille.nomf,pf->dfamille.designationf);
		printf("+----------------+----------------------+-------------------------+\n");
    }
}

int calcul_produit_par_famille(PRODUIT *firstp,int codefam)
{	
	int nb_produit=0;
	PRODUIT *pp;
	for(pp=firstp;pp;pp=pp->nextp)
	{
		if (codefam==pp->dproduit.code_famille)
			nb_produit=nb_produit+1;
	}
	return(nb_produit);
}

	
int verifier_existence_famille(FAMILLE *firstf,int codefam)
{
	FAMILLE *pf;
	for(pf=firstf;(pf)&&(pf->dfamille.codef!=codefam);pf=pf->nextf)
		;

	if(pf==NULL)
		return(0);
	else
		return(1);
}


int retapez_choix(FAMILLE *firstf)
{
	int choix;
	printf("\n1 : Afficher Toutes Les Famille. \n2 : retapez un code. \n0 : Quitter. \n");
	printf("Tapez votre choix : ");
	scanf("%d",&choix);
	if ((choix<=2)&&(choix>=0))
	{
		switch(choix)
		{
			case 0 :
				exit(0);
			break;
			case 1 :
			{
				affiche_famille(firstf);
				printf("Retapez un code famille : ");
				scanf("%d",&choix);
				return(choix);
			}
			break;
			case 2 :
			{
				printf("Retaper un code famille : ");
				scanf("%d",&choix);
				return(choix);
			}
				break;
		}
	}
	else
	{
		printf("Choix Incorrecte, Reessayez");
		choix=retapez_choix(firstf);
	}
}

void affiche_etat_par_famille(PRODUIT *firstp,FAMILLE *firstf,int* choix)
{
	int c;	
	if ((verifier_existence_famille(firstf,*choix))==0)
	{
		printf("\nle code famille nexiste pas, reverifiez\n");
		*choix=retapez_choix(firstf);
		affiche_etat_par_famille(firstp,firstf,choix);
	}
	else
	{
		c=calcul_produit_par_famille(firstp,*choix);
		printf("+----------+----------+\n");
		printf("|  codef   |   valeur |\n");
		printf("+----------+----------+\n");
		printf("|%-10d|%-10d|\n",*choix,c);
	}
	
}

void modification_fichier_produit(PRODUIT *firstp)
{
	PRODUIT *p;
	FILE *fp;
	fp=fopen("produit","w");
	for(p=firstp;p;p=p->nextp)
	{
		fprintf(fp,"%d %s %d %s %f %d \n",p->dproduit.codep,p->dproduit.nomp,p->dproduit.code_famille,p->dproduit.designationp,p->dproduit.coutp,p->dproduit.quantp);
	}
	fclose(fp);
}

void supp_produits(PRODUIT **firstp,FAMILLE *firstf,int* choix)
{	PRODUIT *pp;
	PRODUIT *pred;
	FILE *fp;
	if (!(verifier_existence_famille(firstf,*choix)))
	{
		printf("\nle code famille nexiste pas, reverifiez\n");
		*choix=retapez_choix(firstf);
		supp_produits(firstp,firstf,choix);
	}
	else
	{
		if (((*firstp)->dproduit.code_famille)==*choix)
		{
			pp=(*firstp)->nextp;
			free(*firstp);
			*firstp=pp;
		}
		else
		{
			for(pp=(*firstp)->nextp,pred=*firstp;pp;pred=pp,pp=pp->nextp)
			{
				if (pp->dproduit.code_famille==*choix)
				{
					pred->nextp=pp->nextp;
					free(pp);
				}
			}
		}
		modification_fichier_produit(*firstp);
		
		
	}
}

void ajouter_produit(PRODUIT **firstp,int cp,char np[],int cf,char dp[],float cop,int qp)
{
	PRODUIT *p;
	p=(PRODUIT *)malloc(sizeof(PRODUIT));
	p->dproduit.codep=cp;
	strcat(p->dproduit.nomp,np);
	p->dproduit.code_famille=cf;
	strcat(p->dproduit.designationp,dp);
	p->dproduit.coutp=cop;
	p->dproduit.quantp=qp;
	p->nextp=*firstp;
	*firstp=p;
	modification_fichier_produit(*firstp);
}

void modification_fichier_famille(FAMILLE *firstf)
{
	FAMILLE *p;
	FILE *fp;
	fp=fopen("famille_fich","w");
	for(p=firstf;p;p=p->nextf)
	{
		fprintf(fp,"%d %s %s \n",p->dfamille.codef,p->dfamille.nomf,p->dfamille.designationf);
	}
	fclose(fp);
}

void ajout_famille(FAMILLE **firstf,int cf)
{	
	char nf[100],df[100];
	FAMILLE *pf;

	printf("\nDonnez le nom de la famille : ");
	scanf("%s",nf);
	printf("\nDonnez la designation de la famille : ");
	scanf("%s",df);
	pf=(FAMILLE *)malloc(sizeof(FAMILLE));
	pf->dfamille.codef=cf;
	strcat(pf->dfamille.nomf,nf);
	strcat(pf->dfamille.designationf,df);
	pf->nextf=*firstf;
	*firstf=pf;
	modification_fichier_famille(*firstf);
}

void ajout_produit(PRODUIT **firstp,FAMILLE **firstf)
{
	int cp,cf,qp;
	char np[100],dp[100];
	char c[5];
	float cop;

	printf("\nDonnez le code famille du produit à ajouter : ");
	scanf("%d",&cf);
	if((verifier_existence_famille(*firstf,cf))==0)
	{
		printf("\nCette famille ne existe pas, voulez vous l'ajoutez ? oui/non : ");
		scanf("%s",c);
		if(strcmp(c,"oui")==0)
		{
		
			ajout_famille(firstf,cf);
			printf("\nDonnez le code du produit a ajouter : ");
			scanf("%d",&cp);
			printf("\nDonnez le nom du produit a ajouter : ");
			scanf("%s",np);
			printf("\nDonner la designation du produit : ");
			scanf("%s",dp);
			printf("\nDonner le cout du produit : ");
			scanf("%f",&cop);
			printf("\nDonner la quantite du produit : ");
			scanf("%d",&qp);
			ajouter_produit(firstp,cp,np,cf,dp,cop,qp);
		}
		else
		{
			printf("\nchoix incorrecte");
			retapez_choix(*firstf);
		}
	}
	else
	{
		printf("\nDonnez le code du produit a ajouter : ");
		scanf("%d",&cp);
		printf("\nDonnez le nom du produit a ajouter : ");
		scanf("%s",np);
		printf("\nDonner la designation du produit : ");
		scanf("%s",dp);
		printf("\nDonner le cout du produit : ");
		scanf("%f",&cop);
		printf("\nDonner la quantite du produit : ");
		scanf("%d",&qp);
		ajouter_produit(firstp,cp,np,cf,dp,cop,qp);
	}
}

void reponse_menu(int choix,FAMILLE **firstf,PRODUIT **firstp)
{
	float total_prix;
	int cfam;

		switch(choix)
	{
		case 0:
			exit(0);
		break;
		
		case 1:
			total_prix=affiche_etat_global_stock(*firstp);
			printf("Total Des Produits = %f\n",total_prix);
			choix=affiche_menu();
			reponse_menu(choix,firstf,firstp);
		break;

		case 2:
			printf("Donner un code de famille : ");
			scanf("%d",&cfam);
			affiche_etat_par_famille(*firstp,*firstf,&cfam);
			choix=affiche_menu();
			reponse_menu(choix,firstf,firstp);
		break;

		case 3:
			affiche_famille(*firstf);
			choix=affiche_menu();
			reponse_menu(choix,firstf,firstp);
		break;	
		
		case 4:
			printf("\nDonner Le Code De La Famille Pour Supprimer Ses Produits : ");
			scanf("%d",&cfam);
			supp_produits(firstp,*firstf,&cfam);
			choix=affiche_menu();
			reponse_menu(choix,firstf,firstp);
		break;
	
		case 5:
			ajout_produit(firstp,firstf);
			choix=affiche_menu();
			reponse_menu(choix,firstf,firstp);
		break;   
	}
}
void main()
{	
	
	int choix;
	int c;
    char sp[500];
    FILE *fp1;
    PRODUIT *firstp;
	char sf[500];
    FILE *fp;
    FAMILLE *firstf;
	view_entete();
    fp1=fopen("produit","r");
    for(firstp=NULL;fgets(sp,500,fp1);)
    {
		*(sp+strlen(sp)-1)='\0';
        insert_produit(&firstp,sp);
    }
    fp=fopen("famille_fich","r");
    for(firstf=NULL;fgets(sf,1000,fp);)
    {
		*(sf+strlen(sf)-1)='\0';
        insert_famille(&firstf,sf);
    }
	fclose(fp1);
	fclose(fp);

	choix=affiche_menu();
	reponse_menu(choix,&firstf,&firstp);
	
		


}
