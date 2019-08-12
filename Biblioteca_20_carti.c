#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Biblioteca{
    char titlu[50];
    char nume[40];
    char prenume[40];
    char domeniu[40];
    int pret, nrpag;
};

void citire_carti( struct Biblioteca *c, int n, FILE*f);
void adaugare_carti();
void afisare_biblioteca( struct Biblioteca *c, int n);
void sortare_alfabetica_nume(struct Biblioteca *c, int n);
void sortare_domeniu_teh_pret(struct Biblioteca *c, int n);
void afisare_titlu(struct Biblioteca *c, int n);
void afisare_dom_teh(struct Biblioteca *c, int n);
void afisare_nr_carti_suma(struct Biblioteca *c, int n);
void afisare_titluri_autori_litera_introdusa( struct Biblioteca *c, int n);


int main(){


int n;

FILE *f=fopen("Biblioteca_proiect.txt", "r");
    if(!f){
        printf("Eroare la deschiderea fisierului\n");
        return -1;
    }
    fscanf(f, "%d", &n);
    printf("Numarul de carti este: %d\n\n", n);
    struct Biblioteca *carti;
    carti = (struct Biblioteca *)malloc(n*sizeof(struct Biblioteca));
    if(!carti){
        printf("alocare esuata");
        return -1;
    }
    citire_carti(carti, n, f);
    char optiune;
    do{

		printf("\nIntroduceti: \n\na - pentru a citi datele din fisier intr-un vector de structuri de date cu campuri corespunzatoare informatiilor \nde retinut despre fiecare carte\n");
        printf("b - pentru a introduce o carte noua\nc - pentru a lista datele despre carti, in ordine alfabetica, dupa numelui autorului\n");
        printf("d - pentru a lista cartile din domeniul tehnic in ordinea crescatoare a pretului\ne - pentru a afisa titlul fiecarei carti si numarul total al cartilor cu un pret mai mic decat \no suma indicata de utilizator\n");
        printf("f - pentru a se afisa titlurile cartilor scrise de autori ai caror nume incepe cu o litera introdusa de utilizator\nx - pentru terminarea programului\n");
        do{
			scanf("%c", &optiune);
		}while(optiune == '\n');

		switch (optiune){
			case 'a': citire_carti(carti, n, f); break;
			case 'b': adaugare_carti(); break;
			case 'c': sortare_alfabetica_nume(carti, n);
            printf("\nCartile sortate alfabetic dupa numele autorului:\n\n");
            afisare_biblioteca(carti, n); break;
			case 'd': sortare_domeniu_teh_pret(carti, n);
            printf("\nCartile sortate crescator in funtie de pret, dupa domeniul tehnic:\n\n");
            afisare_dom_teh(carti, n);; break;
			case 'e': afisare_titlu(carti, n);
            afisare_nr_carti_suma(carti, n); break;
			case 'f': afisare_titluri_autori_litera_introdusa(carti, n); break;
		}
	}while(optiune!='x');

    fclose(f);

}



void citire_carti( struct Biblioteca *c, int n, FILE*f){

    int i;
    for(i=0; i<n; i++){
        fscanf(f, "%s", c[i].titlu);
        fscanf(f, "%s", c[i].nume);
        fscanf(f, "%s", c[i].prenume);
        fscanf(f, "%s", c[i].domeniu);
        fscanf(f, "%d", &c[i].pret);
        fscanf(f, "%d", &c[i].nrpag);

    }
}


void adaugare_carti(){
    FILE *f_out;
    struct Biblioteca c_nou;
    f_out = fopen("Biblioteca_20_cartii.txt", "r+");
    if (f_out){
        int n; fscanf(f_out, "%d", &n);
        n++;
        fseek(f_out, 0, SEEK_SET);
        fprintf(f_out, "%d\n", n);
        fseek(f_out, 0, SEEK_END);
        printf("Introducere date carte noua: \n");
        printf("Titlu: "); scanf("%s", &c_nou.titlu); fprintf(f_out, "%s\n", c_nou.titlu);
        printf("Nume: "); scanf("%s", &c_nou.nume); fprintf(f_out, "%s\n", c_nou.nume);
        printf("Prenume: "); scanf("%s", &c_nou.prenume); fprintf(f_out, "%s\n", c_nou.prenume);
        printf("Domeniu: "); scanf("%s", &c_nou.domeniu); fprintf(f_out, "%s\n", c_nou.domeniu);
        printf("Pret: "); scanf("%d", &c_nou.pret); fprintf(f_out, "%d\n", c_nou.pret);
        printf("Nr. Pagini: "); scanf("%d", &c_nou.nrpag); fprintf(f_out, "%d\n", c_nou.nrpag);
        fclose(f_out);
    }
}

void afisare_biblioteca( struct Biblioteca *c, int n){
    int i;
    for(i=0; i<n; i++){
        printf("Datele cartii cu numarul %d sunt: ", i+1);
        printf("\ntitlu:  %s", c[i].titlu);
        printf("\nnume:  %s", c[i].nume);
        printf("\nprenume:  %s", c[i].prenume);
        printf("\ndomeniu:  %s", c[i].domeniu);
        printf("\npret:  %d", c[i].pret);
        printf("\nnr.pagini:  %d\n\n", c[i].nrpag);

    }
}

void sortare_alfabetica_nume(struct Biblioteca *c, int n){

    int i, gasit;
    struct Biblioteca aux;

    do{
        gasit = 0;
        for(i=0; i<n-1; i++)
            if(strcmp(c[i].nume, c[i+1].nume)>0){
                gasit = 1;
                aux = c[i];
                c[i]=c[i+1];
                c[i+1]=aux;
            }
    }while(gasit);
}

void sortare_domeniu_teh_pret(struct Biblioteca *c, int n){

    int i, gasit;
    struct Biblioteca aux;

    do{
        gasit = 0;
        for(i=0; i<n-1; i++)

            if(c[i].pret > c[i+1].pret){
                gasit = 1;
                aux = c[i];
                c[i]=c[i+1];
                c[i+1]=aux;
            }
    }while(gasit);
}

void afisare_titlu( struct Biblioteca *c, int n){
    int i;
     printf("Afisarea titlurilor cartilor: ");
    for(i=0; i<n; i++){
        printf("\nTitlu %d:  %s",i+1, c[i].titlu);

    }
}

void afisare_dom_teh( struct Biblioteca *c, int n){
    int i;
    for(i=0; i<n; i++){
            if(strcmp(c[i].domeniu, "Tehnic")== 0){
            printf("Datele cartii cu numarul %d sunt: ", i+1);
            printf("\ntitlu:  %s", c[i].titlu);
            printf("\nnume:  %s", c[i].nume);
            printf("\nprenume:  %s", c[i].prenume);
            printf("\ndomeniu:  %s", c[i].domeniu);
            printf("\npret:  %d", c[i].pret);
            printf("\nnr.pagini:  %d\n\n", c[i].nrpag);}

    }
}

void afisare_nr_carti_suma( struct Biblioteca *c, int n){
    int i, nr = 0, suma;
    printf("\n\nIntroduceti suma(ex. 45): ");
    scanf("%d", &suma);

    for(i=0; i<n; i++){
            if(c[i].pret < suma){
            nr+=1;
            }

    }
    printf("\nNumarul total de cartilor cu un pret mai mic decat %d este: %d", suma, nr);
}

void afisare_titluri_autori_litera_introdusa( struct Biblioteca *c, int n){
    int i;
    char litera;
    printf("\nIntroduceti litera cu care vreti sa inceapta numele autorului: ");
    scanf(" %c", &litera);
    for(i=0; i<n; i++){
            if (c[i].nume[0] == litera ){
            printf("\nTitlu %d:  %s",i+1, c[i].titlu);
            }

    }
}
getchar(void);
