//1. Structura si functii 
//Se consideră prima literă din numele vostru, și prima literă din prenumele vostru.
//Sa se construiască un articol care să conțină cele două litere.
//Dobrescu Catalina
//struct Magazin {
	//int cod;
	//char* denumire;
	//int nrProduse;
	//float* preturi;
//}
//Articolul trebuie să aibă logica.Articolul trebuie sa fie un substantiv.Articolul trebuie sa aibă
//cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
//Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de
//voi.Funcția returnează obiectul citit.
//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o
	//medie sau o suma, un maxim, un minim...sau orice altceva)
	//Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
//	noua valoare este primita ca parametru.
	//Realizați o funcție care afișează un obiect de tipul creat.Afișarea se face la console, și sunt
//	afișate toate informațiile.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Disciplina {
	int cod;
	char* denumire;
	int nrNote;
	float* note;
};

// Inițializare disciplină
struct Disciplina initializare(int cod, const char* denumire, int nrNote, float* note) {
	struct Disciplina d;
	d.cod = cod;
	d.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(d.denumire, strlen(denumire) + 1, denumire);
	d.nrNote = nrNote;

	d.note = (float*)malloc(sizeof(float) * nrNote);
	for (int i = 0; i < nrNote; i++) {
		d.note[i] = note[i];
	}
	return d;
}

// Afișare disciplină
void afisare(struct Disciplina d) {
	printf("Cod: %d\n", d.cod);
	printf("Denumire: %s\n", d.denumire);
	printf("Note: ");
	for (int i = 0; i < d.nrNote; i++) {
		printf("%.2f ", d.note[i]);
	}
	printf("\n");
}

// Citire disciplină de la tastatură
struct Disciplina citire() {
	struct Disciplina d;
	char buffer[100];

	printf("Cod: ");
	scanf("%d", &d.cod);

	printf("Denumire: ");
	scanf(" %[^\n]", buffer);
	d.denumire = (char*)malloc(strlen(buffer) + 1);
	strcpy_s(d.denumire, strlen(buffer) + 1, buffer);

	printf("Numar note: ");
	scanf("%d", &d.nrNote);
	d.note = (float*)malloc(sizeof(float) * d.nrNote);
	for (int i = 0; i < d.nrNote; i++) {
		printf("Nota %d: ", i + 1);
		scanf("%f", &d.note[i]);
	}
	return d;
}

// Media notelor
float calculeazaMedia(struct Disciplina d) {
	float suma = 0;
	for (int i = 0; i < d.nrNote; i++) {
		suma += d.note[i];
	}
	return (d.nrNote > 0) ? (suma / d.nrNote) : 0;
}

// Modificare denumire
void modificaDenumire(struct Disciplina* d, const char* nouaDenumire) {
	free(d->denumire);
	d->denumire = (char*)malloc(strlen(nouaDenumire) + 1);
	strcpy_s(d->denumire, strlen(nouaDenumire) + 1, nouaDenumire);
}

// Dezalocare memorie
void dezalocare(struct Disciplina* d) {
	free(d->denumire);
	free(d->note);
}

int main() {
	// Inițializare disciplină
	float noteExemplu[] = { 9.5, 8.0, 10.0 };
	struct Disciplina d1 = initializare(1, "Programare", 3, noteExemplu);
	afisare(d1);
	printf("Media: %.2f\n", calculeazaMedia(d1));

	// Modificare denumire
	modificaDenumire(&d1, "Structuri de date");
	printf("\nDupa modificare denumire:\n");
	afisare(d1);

	// Citire disciplină de la tastatură
	printf("\nCitire disciplina de la tastatura:\n");
	struct Disciplina d2 = citire();
	afisare(d2);
	printf("Media: %.2f\n", calculeazaMedia(d2));

	// Eliberare memorie
	dezalocare(&d1);
	dezalocare(&d2);

	return 0;
}
