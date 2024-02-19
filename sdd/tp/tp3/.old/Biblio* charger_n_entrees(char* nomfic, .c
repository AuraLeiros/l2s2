Biblio* charger_n_entrees(char* nomfic, int n){

    char ligne[(3 * BUF_SIZE)];
    char titre[BUF_SIZE];
    char auteur[BUF_SIZE];
    int numLiv;
    char delimiter[] = " ";
    int countLines = 0;
    char* token;
    int ch = 0;

    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        return NULL;
    }

    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return NULL;
    }

    /* Vérification que le nombre de lignes présent dans le fichier est >= n sortie du programme sinon retourne NULL */
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            countLines++;
        }
    }

    if (ch != '\n' && countLines != 0) {
        countLines++;
    }

    if ((n > countLines) || (countLines == 0)) {
        fprintf(stderr, "Erreur dans le calcul du nombre de lignes dans le fichier.\n");
        liberer_biblio(newBiblio);
        fclose(fptr);
        return NULL;
    }

    /* Retourner le pointeur à l'origine avant de faire le traitement */
    rewind(fptr);

    /* Traitement du fichier */
    for (int x=1;x<=n;x++){
        
        fgets(ligne, (3 * BUF_SIZE), fptr);

        /* Tokenization de chaque élément dans une ligne */
        token = strtok(ligne, delimiter);
        numLiv = atoi(token);
        token = strtok(NULL, delimiter);
        strncpy(titre, token, BUF_SIZE);
        titre[BUF_SIZE-1] = '\0';
        token = strtok(NULL, delimiter);
        strncpy(auteur, token, BUF_SIZE);
        auteur[BUF_SIZE-1] = '\0';

        inserer_en_tete(newBiblio, numLiv, titre, auteur);

    }

    /* Fermeture du fichier et return du résultat */
    fclose(fptr);
    return newBiblio;
}


Biblio* charger_n_entrees(char* nomfic, int n){

    char ligne[(3 * BUF_SIZE)];
    char titre[BUF_SIZE];
    char auteur[BUF_SIZE];
    int numLiv;
    char delimiter[] = " ";
    int countLines = 0;
    char* token;
    int ch = 0;

    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        return NULL;
    }

    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return NULL;
    }

    for (int x=1; x<=n; x++){
        if (!fgets(ligne, (3 * BUF_SIZE), fptr)){
            fprintf(stdout, "EOF, plus d'éléments á lire dans le fichier");
            break;
        }

        token = strtok(ligne, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        num = atoi(token);

        token = strtok(NULL, delimiter);
        if (token == NULL) {
            fprintf(stderr, "Titre manquant.\n");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        strncpy(titre, token, BUF_SIZE - 1);
        titre[BUF_SIZE - 1] = '\0';

        token = strtok(NULL, delimiter);
        if (token == NULL) {
            fprintf(stderr, "Auteur manquant\n");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        strncpy(auteur, token, BUF_SIZE - 1);
        auteur[BUF_SIZE - 1] = '\0';

        inserer_en_tete(newBiblio, numLiv, titre, auteur);        
    }
}