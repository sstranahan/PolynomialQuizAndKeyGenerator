#include <stdio.h>
#include "math.h"
#include <time.h>
#include <stdlib.h>

struct polynomial {
    int a;
    int b;
    int c;
    int repeatedRoot;
    int realRoot1;
    int realRoot2;
    int realPart;
    int imaginaryPart;
};

// Generates a random integer between min and max (inclusive) - nonzero
int randomNonzeroInt(int min, int max) {
    int returnVal = 0;

    srand(time(0));

    // Make sure random int != 0
    while (returnVal == 0) {
        returnVal =  min + rand() % (max + 1 - min);
        if (returnVal != 0) return returnVal;
    }
}

// Generates a random integer between min and max (inclusive)
int randomInt(int min, int max) {
    srand(time(0));

    return min + rand() % (max + 1 - min);

}

// Returns a polynomial with repeated roots
struct polynomial repeatedRoots() {
    int root;
    root = randomNonzeroInt(-5,5);

    struct polynomial repeatedPoly = {1, 2*root, pow(root, 2), root, 0, 0, 0, 0};
    return repeatedPoly;
}

struct polynomial realRoots() {
    int root1 = 0;
    int root2 = 0;

    while (root1 == root2) {
        root1 = randomNonzeroInt(-5, 5);
        root2 = randomInt(-5, 5);
    }

    struct polynomial realPoly = {1, root1 + root2, root1 * root2, 0, root1, root2, 0, 0};
    return realPoly;
}

struct polynomial complexRoots(){
    int real, imaginary;
    real = randomInt(-5,5);
    imaginary = randomNonzeroInt(1,5);

    struct polynomial complexPoly = {1, -2 * real, pow(real, 2) + pow(imaginary,2), 0, 0, 0, real, imaginary};
    return complexPoly;
}

void printRepeatedPoly(FILE *filePtr, struct polynomial repeatedPoly){
    fprintf(filePtr, "1. Solve for the roots: $x^2");

    if (repeatedPoly.b > 0) {
        fprintf(filePtr, " + %dx", repeatedPoly.b);
    } else if (repeatedPoly.b < 0 ) {
        fprintf(filePtr, "%dx", repeatedPoly.b);
    } else {
        printf("Error - constant coefficient is zero ... terminating ...");
        exit(EXIT_FAILURE);
    }

    if (repeatedPoly.c > 0) {
        fprintf(filePtr, " + %d$\\\\\n", repeatedPoly.c);
    } else if (repeatedPoly.c < 0 ) {
        fprintf(filePtr, "%d$\\\\\n", repeatedPoly.c);
    } else {
        printf("Error - constant coefficient is zero ... terminating ...");
        exit(EXIT_FAILURE);
    }
}

void printRealPoly(FILE *filePtr, struct polynomial realPoly){
    fprintf(filePtr, "2. Solve for the roots: $x^2");

    if (realPoly.b > 0) {
        fprintf(filePtr, " + %dx", realPoly.b);
    } else if (realPoly.b < 0 ) {
        fprintf(filePtr, "%dx", realPoly.b);
    }

    if (realPoly.c > 0) {
        fprintf(filePtr, " + %d$\\\\\n", realPoly.c);
    } else if (realPoly.c < 0 ) {
        fprintf(filePtr, "%d$\\\\\n", realPoly.c);
    } else {
        fprintf(filePtr, "%d$\\\\\n", realPoly.c);
    }
}

void printComplexPoly(FILE *filePtr, struct polynomial complexPoly){
    fprintf(filePtr, "3. Solve for the roots: $x^2");

    if (complexPoly.b > 0) {
        fprintf(filePtr, " + %dx", complexPoly.b);
    } else if (complexPoly.b < 0 ) {
        fprintf(filePtr, "%dx", complexPoly.b);
    }

    if (complexPoly.c > 0) {
        fprintf(filePtr, " + %d$\\\\\n", complexPoly.c);
    } else if (complexPoly.c < 0 ) {
        fprintf(filePtr, "%d$\\\\\n", complexPoly.c);
    }
}

void printQuizFile(FILE *quizFile, struct polynomial repeatedPoly, struct polynomial realPoly, struct polynomial complexPoly) {

    fprintf(quizFile, "\\documentclass{article}\n"
                      "\\usepackage{setspace}\n"
                      "\\usepackage[utf8]{inputenc}\n"
                      "\\usepackage[document]{ragged2e}\n"
                      "\\usepackage[margin=1in]{geometry}\n"
                      "\\usepackage{datetime}\n\n"
                      "\\doublespacing\n"
                      "\\begin{document} \\raggedright\n\n"
                      "{\\Large \\textbf{ECE 370: Advanced Computer Methods in ECE}}\\\\\n\n"
                      "\\textbf{Quiz 1: The Quadratic Equation}\\\\\n"
                      "\\today\n\n"
                      "\\noindent{\\makebox[\\textwidth][l]{Name: \\rule{4in}{0.4pt}}} \\\\\\\\\n\n");

    printRepeatedPoly(quizFile, repeatedPoly);
    fprintf(quizFile, "\\vfill\n");
    printRealPoly(quizFile, realPoly);
    fprintf(quizFile, "\\vfill\n");
    printComplexPoly(quizFile, complexPoly);
    fprintf(quizFile, "\\vfill\n");

    fprintf(quizFile,"\n\\end{document}");

}

void printKeyFile(FILE *keyFile, struct polynomial repeatedPoly, struct polynomial realPoly, struct polynomial complexPoly) {

    int discriminant;

    fprintf(keyFile, "\\documentclass{article}\n"
                      "\\usepackage{setspace}\n"
                      "\\usepackage[utf8]{inputenc}\n"
                      "\\usepackage[document]{ragged2e}\n"
                      "\\usepackage[margin=1in]{geometry}\n"
                      "\\usepackage{datetime}\n\n"
                      "\\doublespacing\n"
                      "\\begin{document} \\raggedright\n\n"
                      "{\\Large \\textbf{ECE 370: Advanced Computer Methods in ECE}}\\\\\n\n"
                      "\\textbf{Quiz 1: The Quadratic Equation}\\\\\n"
                      "\\today\n\n"
                      "\\noindent{\\makebox[\\textwidth][l]{Name: \\rule{4in}{0.4pt}}} \\\\\\\\\n\n");

    printRepeatedPoly(keyFile, repeatedPoly);

    fprintf(keyFile, "\\quad \\textbf{Discriminant:}\\\\\n"
                     "\\quad $d=%d^2 - 4*%d*(%d) = %d", repeatedPoly.b, repeatedPoly.a, repeatedPoly.c, (int)pow(repeatedPoly.b, 2));

    if (-4*repeatedPoly.a * repeatedPoly.c > 0) {
        fprintf(keyFile, " + %d", -4 * repeatedPoly.a * repeatedPoly.c);
    } else {
        fprintf(keyFile, "%d", -4 * repeatedPoly.a * repeatedPoly.c);
    }

    discriminant = (int)pow(repeatedPoly.b, 2) + -4 * repeatedPoly.a * repeatedPoly.c;

    fprintf(keyFile, " = %d$\\\\\n", discriminant);

    fprintf(keyFile, "\\quad \\textbf{Roots:}\\\\\n"
                     "\\quad$(%d/%d) + (\\sqrt{%d}/%d) = %f + %f = %d$\\\\\n",
                     -1 * repeatedPoly.b, 2 * repeatedPoly.a, discriminant,2 * repeatedPoly.a,
                     (float)(-1 * repeatedPoly.b) / (float)(2* repeatedPoly.a),
                     (float)sqrt(discriminant) / (float)(2* repeatedPoly.a),
                     (int)((float)(-1 * repeatedPoly.b) / (float)(2* repeatedPoly.a) + (float)sqrt(discriminant) / (float)(2* repeatedPoly.a)));

    fprintf(keyFile, "\\vfill\n");

    printRealPoly(keyFile, realPoly);

    fprintf(keyFile, "\\quad \\textbf{Discriminant:}\\\\\n"
                     "\\quad $d=%d^2 - 4*%d*(%d) = %d", realPoly.b, realPoly.a, realPoly.c, (int)round(pow(realPoly.b, 2)));

    if (-4*realPoly.a * realPoly.c > 0) {
        fprintf(keyFile, " + %d", -4 * realPoly.a * realPoly.c);
    } else {
        fprintf(keyFile, "%d", -4 * realPoly.a * realPoly.c);
    }

    discriminant = (int)round(pow(realPoly.b, 2)) + -4 * realPoly.a * realPoly.c;

    fprintf(keyFile, " = %d$\\\\\n", discriminant);

    fprintf(keyFile, "\\quad \\textbf{Roots:}\\\\\n"
                     "\\quad$(%d/%d) + (\\sqrt{%d}/%d) = %f + %f = %d$\\\\\n",
            -1 * realPoly.b, 2 * realPoly.a, discriminant,2 * realPoly.a,
            (float)(-1 * realPoly.b) / (float)(2* realPoly.a),
            (float)sqrt(discriminant) / (float)(2* realPoly.a),
            (int)((float)(-1 * realPoly.b) / (float)(2* realPoly.a) + (float)sqrt(discriminant) / (float)(2* realPoly.a)));

    fprintf(keyFile, "\\quad$(%d/%d) - (\\sqrt{%d}/%d) = %f - %f = %d$\\\\\n",
            -1 * realPoly.b, 2 * realPoly.a, discriminant,2 * realPoly.a,
            (float)(-1 * realPoly.b) / (float)(2* realPoly.a),
            (float)sqrt(discriminant) / (float)(2* realPoly.a),
            (int)((float)(-1 * realPoly.b) / (float)(2* realPoly.a) - (float)sqrt(discriminant) / (float)(2* realPoly.a)));

    fprintf(keyFile, "\\vfill\n");
    printComplexPoly(keyFile, complexPoly);

    fprintf(keyFile, "\\quad \\textbf{Discriminant:}\\\\\n"
                     "\\quad $d=%d^2 - 4*%d*(%d) = %d", complexPoly.b, complexPoly.a, complexPoly.c, (int)pow(complexPoly.b, 2));

    if (-4*complexPoly.a * complexPoly.c > 0) {
        fprintf(keyFile, " + %d", -4 * complexPoly.a * complexPoly.c);
    } else {
        fprintf(keyFile, "%d", -4 * complexPoly.a * complexPoly.c);
    }

    discriminant = (int)pow(complexPoly.b, 2) + -4 * complexPoly.a * complexPoly.c;

    fprintf(keyFile, " = %d$\\\\\n", discriminant);

    fprintf(keyFile, "\\quad \\textbf{Roots:}\\\\\n"
                     "\\quad$(%d/%d) + (\\sqrt{%d}/%d) = %f + %di$\\\\\n",
            -1 * complexPoly.b, 2 * complexPoly.a, discriminant,2 * complexPoly.a,
            (float)(-1 * complexPoly.b) / (float)(2* complexPoly.a),
            complexPoly.imaginaryPart);

    fprintf(keyFile, "\\quad$(%d/%d) - (\\sqrt{%d}/%d) = %f - %di$\\\\\n",
            -1 * complexPoly.b, 2 * complexPoly.a, discriminant,2 * complexPoly.a,
            (float)(-1 * complexPoly.b) / (float)(2* complexPoly.a),
            complexPoly.imaginaryPart);

    fprintf(keyFile, "\\vfill\n");
    fprintf(keyFile,"\n\\end{document}");
}

int main(void) {
    FILE *quizFile;
    FILE *keyFile;
    struct polynomial repeatedPoly, realPoly, complexPoly;

    // Open file for student quiz - throw error and terminate if file fails to open
    quizFile = fopen("Quiz.tex", "w");
    if (quizFile == NULL) {
        printf("Error opening file \"Quiz.tex\" in write mode ... Terminating ...");
        exit(EXIT_FAILURE);
    }

    // Open file for quiz key - throw error and terminate if file fails to open
    keyFile = fopen("Key.tex", "w");
    if (keyFile == NULL){
        printf("Error opening file \"Key.tex\" in write mode ... Terminating ...");
        exit(EXIT_FAILURE);
    }

    repeatedPoly = repeatedRoots();
    realPoly = realRoots();
    complexPoly = complexRoots();

    printQuizFile(quizFile, repeatedPoly, realPoly, complexPoly);
    printKeyFile(keyFile, repeatedPoly, realPoly, complexPoly);

    fclose(quizFile);
    fclose(keyFile);

    return 0;
}
