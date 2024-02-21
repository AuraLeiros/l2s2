
    //Biblio* maBiblio = NULL;
    char buffer[(3 * BUF_SIZE)];
    char* buffer_aux = NULL;
    int rep;
    int len;

    /* Ex. 1.4 - Charger une bibliotheque */
    int rep = input()

    /* Check des arguments */
    if (argc != 3) {
        printf("Usage: %s txt_file umber_lines", argv[0]);
        exit(EXIT_FAILURE);
    }

    maBiblio = charger_n_entrees_lc(argv[1], atoi(argv[2]));
    
    /* Ex. 1.8 - Menu et affichage */
    do{
        /* Afficher le menu à l'utilisateur */
        menu();
        fflush(stdout);

        /* Traitement de l'entrée */
        if (!fgets(buffer, (3 * BUF_SIZE), stdin)){
            fprintf(stderr, "Erreur dans le fgets");
            liberer_biblio_lc(maBiblio);
            return EXIT_FAILURE;
        }
        

        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n'){
            buffer[len - 1] = '\0';
        }

        rep = atoi(buffer);


        switch(rep){

            // Affichage d'une bibliothèque
            case 1:                            
                printf("Affichage :\n");
                afficher_biblio_lc(maBiblio);
                break;
            // Insérer un ouvrage
            case 2:
                int num;
                char titre[BUF_SIZE];
                char auteur[BUF_SIZE];
                char* token;
                char delimiter[] = " ";

                printf("Veuillez écrire le numéro, le titre et l'auteur de l'ouvrage : \n");
                buffer_aux = input_lc(maBiblio);
                if (!buffer_aux){
                    fprintf(stderr, "Erreur dans l'allocation mémoire\n");
                    liberer_biblio_lc(maBiblio);
                    return EXIT_FAILURE;
                }
        
                /* Tokenization de chaque élément dans une ligne */
                token = strtok(buffer_aux, delimiter);
                num = atoi(token);
                token = strtok(NULL, delimiter);
                strncpy(titre, token, BUF_SIZE);
                token = strtok(NULL, delimiter);
                strncpy(auteur, token, BUF_SIZE);

                inserer_en_tete(maBiblio, num, titre, auteur);
                free(buffer_aux);
                break;
            
            case 3:
                printf("Veuillez saisir le numéro d'enregistrement : \n");
                buffer_aux = input_lc(maBiblio);
                if (!buffer_aux){
                    fprintf(stderr, "Erreur dans l'allocation mémoire\n");
                    liberer_biblio(maBiblio);
                    return EXIT_FAILURE;
                }
                afficher_livre(recherche_par_num(maBiblio, atoi(buffer_aux)));
                free(buffer_aux);
                break;
            
            case 4:
                printf("Veuille saisir l'auteur : \n");
                buffer_aux = input_lc(maBiblio);
                if (!buffer_aux){
                    fprintf(stderr, "Erreur dans l'allocation mémoire\n");
                    liberer_biblio_lc(maBiblio);
                    return EXIT_FAILURE;
                }

                Biblio* biblioAuteur = recherche_par_auteur_lc(maBiblio, buffer_aux);
                if (!biblioAuteur){
                    fprintf(stderr, "Erreur dans l'allocation mémoire\n");
                    free(buffer_aux);
                    liberer_biblio_lc(maBiblio);
                    return EXIT_FAILURE;
                }
                afficher_biblio(biblioAuteur);
                free(buffer_aux);
                break;

            case 5:
                printf("Veuille saisir l'titre : \n");
                buffer_aux = input_lc(maBiblio);
                if (!buffer_aux){
                    fprintf(stderr, "Erreurs sans l'allocation mémoire\n");
                    liberer_biblio_lc(maBiblio);
                    return EXIT_FAILURE;
                }

                afficher_livre_lc(recherche_par_titre_lc(maBiblio, buffer_aux));
                free(buffer_aux);
                break;

            case 6:
                Livre* dupliques = recherche_dupliques_lc(maBiblio);
                while(dupliques != NULL){
                    afficher_livre_lc(dupliques);
                    dupliques = dupliques->suiv;
                }     
                break;   
        }
    }while(rep != 0);
    	
    

    liberer_biblio_lc(maBiblio);

    printf("Merci et au revoir !\n");
    return EXIT_SUCCESS;