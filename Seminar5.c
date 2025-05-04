//2. Vectori 
//Considerati codul de la task - ul precedent.
//Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.
// Realizati o functie care va creea un nou vector în care va copia dintr - un vector primit ca parametru obiectele care indeplinesc o anumita conditie.Stabiliti voi conditia in functie deun atribut sau doua atribute.
//Realizati o functie care muta intr - un nou vector obiectele care indeplinesc o alta conditie fata de cerinta precedenta.
//Realizati o functie care concateneaza doi vectori.
//Realizati o functie care afiseaza un vector cu obiecte.
//Apelati toate aceste functii in main().
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

// Calculează media
float calculeazaMedia(struct Disciplina d) {
    float suma = 0;
    for (int i = 0; i < d.nrNote; i++) {
        suma += d.note[i];
    }
    return (d.nrNote > 0) ? (suma / d.nrNote) : 0;
}

// Afișare obiect
void afisare(struct Disciplina d) {
    printf("Cod: %d | Denumire: %s | Note: ", d.cod, d.denumire);
    for (int i = 0; i < d.nrNote; i++) {
        printf("%.1f ", d.note[i]);
    }
    printf("| Media: %.2f\n", calculeazaMedia(d));
}

// Afișare vector
void afisareVector(struct Disciplina* v, int dim) {
    for (int i = 0; i < dim; i++) {
        afisare(v[i]);
    }
}

// Dezalocare obiect
void dezalocare(struct Disciplina* d) {
    free(d->denumire);
    free(d->note);
}

// Copiere după media ≥ 9
struct Disciplina* copiazaDisciplineMedieMare(struct Disciplina* vector, int dim, int* dimNoua) {
    *dimNoua = 0;
    for (int i = 0; i < dim; i++) {
        if (calculeazaMedia(vector[i]) >= 9.0f)
            (*dimNoua)++;
    }
    struct Disciplina* rezultat = (struct Disciplina*)malloc((*dimNoua) * sizeof(struct Disciplina));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (calculeazaMedia(vector[i]) >= 9.0f) {
            rezultat[k] = initializare(vector[i].cod, vector[i].denumire, vector[i].nrNote, vector[i].note);
            k++;
        }
    }
    return rezultat;
}

// Mutare după nrNote ≥ 4
struct Disciplina* mutaDisciplineCuNoteMulte(struct Disciplina* vector, int dim, int* dimNoua) {
    *dimNoua = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].nrNote >= 4)
            (*dimNoua)++;
    }
    struct Disciplina* rezultat = (struct Disciplina*)malloc((*dimNoua) * sizeof(struct Disciplina));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].nrNote >= 4) {
            rezultat[k] = initializare(vector[i].cod, vector[i].denumire, vector[i].nrNote, vector[i].note);
            k++;
        }
    }
    return rezultat;
}

// Concatenare vectori
struct Disciplina* concateneazaVectori(struct Disciplina* v1, int dim1, struct Disciplina* v2, int dim2, int* dimFinal) {
    *dimFinal = dim1 + dim2;
    struct Disciplina* rezultat = (struct Disciplina*)malloc((*dimFinal) * sizeof(struct Disciplina));
    for (int i = 0; i < dim1; i++)
        rezultat[i] = initializare(v1[i].cod, v1[i].denumire, v1[i].nrNote, v1[i].note);
    for (int i = 0; i < dim2; i++)
        rezultat[dim1 + i] = initializare(v2[i].cod, v2[i].denumire, v2[i].nrNote, v2[i].note);
    return rezultat;
}

int main() {
    int nrDiscipline = 5;
    struct Disciplina* vector = (struct Disciplina*)malloc(nrDiscipline * sizeof(struct Disciplina));

    float n1[] = { 10, 10, 9 };
    float n2[] = { 8, 7, 9 };
    float n3[] = { 9.5, 10, 10, 10 };
    float n4[] = { 6, 6, 6 };
    float n5[] = { 9, 9 };

    vector[0] = initializare(1, "Matematica", 3, n1);
    vector[1] = initializare(2, "Fizica", 3, n2);
    vector[2] = initializare(3, "Informatica", 4, n3);
    vector[3] = initializare(4, "Chimie", 3, n4);
    vector[4] = initializare(5, "Biologie", 2, n5);

    printf("Toate disciplinele:\n");
    afisareVector(vector, nrDiscipline);

    int dimMedieMare = 0;
    struct Disciplina* mediiMari = copiazaDisciplineMedieMare(vector, nrDiscipline, &dimMedieMare);
    printf("\nDiscipline cu media >= 9:\n");
    afisareVector(mediiMari, dimMedieMare);

    int dimNoteMulte = 0;
    struct Disciplina* noteMulte = mutaDisciplineCuNoteMulte(vector, nrDiscipline, &dimNoteMulte);
    printf("\nDiscipline cu nrNote >= 4:\n");
    afisareVector(noteMulte, dimNoteMulte);

    int dimFinal = 0;
    struct Disciplina* vectorFinal = concateneazaVectori(mediiMari, dimMedieMare, noteMulte, dimNoteMulte, &dimFinal);
    printf("\nVector concatenat:\n");
    afisareVector(vectorFinal, dimFinal);

    // Dezalocări
    for (int i = 0; i < nrDiscipline; i++) dezalocare(&vector[i]);
    free(vector);

    for (int i = 0; i < dimMedieMare; i++) dezalocare(&mediiMari[i]);
    free(mediiMari);

    for (int i = 0; i < dimNoteMulte; i++) dezalocare(&noteMulte[i]);
    free(noteMulte);

    for (int i = 0; i < dimFinal; i++) dezalocare(&vectorFinal[i]);
    free(vectorFinal);

    return 0;
}
