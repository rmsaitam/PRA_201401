/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

#include "main.h"

void generateRandomEntriesBlock(int size, int blockSize);
void readRandomEntriesBlock(int blockSize);
void executionTime(clock_t time_start, clock_t time_end);
void readEntryPosition(int position);
void generateOneEntry();

// main menu

int main() {
    printf("\nWelcome!");
    printf("\nWhat you want to do?");

    menu();
}

void menu() {
    //to use random values
    srand(time(NULL));

    int menu, submenu, status = 0, position, quantity, subsubmenu;
    int size, blockSize = 4096, k_vias = 8, ok = 1;

    //Function to sort
    void *cmpFisrt;
    void *cmpSecond;

    // execution time control
    clock_t time_start, time_end;

    do {
        printf("\n[0] Create BTree");

        printf("\n[10] Generate multiple randon entries in file using block");
        printf("\n[11] Read entry in position using block");
        printf("\n[12] Create and insert one random entry");
        printf("\n[13] Read entry in position");
        printf("\n[20] Sort file");
        printf("\n[21] Read sorted entries");

        printf("\n");
        scanf("%d", &menu);

        switch (menu) {
            case 0:
                
                arvoreB **raiz;
                raiz = malloc(sizeof (arvoreB*));
                *raiz = malloc(sizeof (arvoreB));
                
                // Generate BTree and create index
                printf("\n What is the first key to sort:");
                printf("\n[0] Name Time A");
                printf("\n[1] Name Time B");
                printf("\n[2] Score (Default)");
                printf("\n[3] Date");
                printf("\n[4] Place");
                printf("\n");

                scanf("%d", &submenu);

                do {
                    printf("\n What is the second key to sort (don't choose the same!):");
                    printf("\n[0] Name Time A");
                    printf("\n[1] Name Time B");
                    printf("\n[2] Score");
                    printf("\n[3] Date (Date)");
                    printf("\n[4] Place");
                    printf("\n");

                    scanf("%d", &subsubmenu);

                    if (subsubmenu == submenu) {
                        printf("\nPlease, choose another option!");
                        ok = 0;
                    }
                } while (ok == 0);

                time_start = time(NULL);
                
                // create BTree
                creteBTree(raiz, cmpKey1, cmpKey2);
                
                time_end = time(NULL);
                executionTime(time_start, time_end);

                // outro menu
                printf("\n[1] Read sorted enties");
                printf("\n[2] Add entry");
                printf("\n[3] Remove entry");
                printf("\n[4] Refresh index");
                printf("\n");
                scanf("%d", &menu);

                switch (menu) {
                    case 1:
                        time_start = time(NULL);
                        // read entries from tree
                        time_end = time(NULL);
                        executionTime(time_start, time_end);
                        break;

                    case 2:
                        printf("How much entries you want to create?\n");
                        scanf("%d", &quantity);
                        time_start = time(NULL);
                        // create random entries and add
                        time_end = time(NULL);
                        executionTime(time_start, time_end);
                        break;

                    case 3:
                        // Remove entry
                        printf("What entry will be removed?\n");
                        scanf("%d", &position);
                        time_start = time(NULL);
                        
                        // removeFromBTree
                        removeFromBTree(int info, cmpKey1, cmpKey2);                        
                        
                        time_end = time(NULL);
                        executionTime(time_start, time_end);
                        break;

                    case 4:
                        // Refresh index file
                        break;
                }

                break;

            case 10:
                printf("\n Chose size:");
                printf("\n[0] MB");
                printf("\n[1] GB (default)");
                printf("\n");

                scanf("%d", &submenu);

                printf("What size?\n");
                switch (submenu) {
                    case 0:
                        scanf("%d", &size);
                        size *= 1024 * 1024;
                        break;
                    default:
                        scanf("%d", &size);
                        size *= 1024 * 1024 * 1024;
                        break;
                }

                printf("What is the block size?\n");
                scanf("%d", &blockSize);

                time_start = time(NULL);
                generateRandomEntriesBlock(size, blockSize);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                status = 1;
                break;

            case 11:
                printf("What is the block size?\n");
                scanf("%d", &blockSize);

                time_start = time(NULL);
                readRandomEntriesBlock(blockSize);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;

            case 12:
                time_start = time(NULL);
                generateOneEntry(size, blockSize);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;

            case 13:
                printf("What position?\n");
                scanf("%d", &position);

                time_start = time(NULL);
                readEntryPosition(position);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;

            case 20:
                printf("What is the block size (Default: 4096)?\n");
                scanf("%d", &blockSize);

                printf("The amount of 'k-vias' (Default: 8)?\n");
                scanf("%d", &k_vias);

                printf("\n What is the first key to sort:");
                printf("\n[0] Name Time A");
                printf("\n[1] Name Time B");
                printf("\n[2] Score (Default)");
                printf("\n[3] Date");
                printf("\n[4] Place");
                printf("\n");

                scanf("%d", &submenu);


                printf("\n What is the second key to sort (don't choose the same!):");
                printf("\n[0] Name Time A");
                printf("\n[1] Name Time B");
                printf("\n[2] Score");
                printf("\n[3] Date (Date)");
                printf("\n[4] Place");
                printf("\n");

                scanf("%d", &subsubmenu);

                time_start = time(NULL);
                intercalateSort(blockSize, k_vias, submenu, subsubmenu);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                status = 1;
                break;

            case 21:
                printf("What is the block size?\n");
                scanf("%d", &blockSize);

                time_start = time(NULL);
                readRandomEntriesBlockSorted(blockSize);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;
            default:
                status = 1;
                printf("\nPlease, select a valid option!!!");
                break;
        }

    } while (status == 1);
}

void generateOneEntry() {
    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    pDATA pData;
    pData = (pDATA) malloc(sizeof (DATA));

    ppPARTIDA ppPartida;
    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));

    randomPartida(ppPartida);
    pData->id = 1;

    memcpy(&pData->partida, (*ppPartida), sizeof (PARTIDA));

    openFile(ppFile, "wb");
    fDataWrite((*ppFile), pData);
    fflush(*ppFile);
    closeFile(ppFile);

    free((*ppPartida));
    free((ppPartida));
    free((pData));
    free(ppFile);
}

void executionTime(clock_t time_start, clock_t time_end) {
    double duration;
    // calc time elapsed
    duration = (double) (time_end - time_start); /// CLOCKS_PER_SEC;

    // print elapsed time
    printf("\n=> This function was running for %.2lf seconds\n", duration);
}

void readEntryPosition(int position) {
    pDATA pData;
    pData = (pDATA) malloc(sizeof (DATA));

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));

    DATA data;

    openFile(ppFile, "r+b");
    fDataReadPosition((*ppFile), &data, position);
    printEntries((&data));
    closeFile(ppFile);

    /* free((pData)->data); */
    free((pData));
    free(ppFile);
}

void generateRandomEntriesBlock(int size, int blockSize) {
    ppPARTIDA ppPartida;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;
    printf("Generating random entries ....\n");

    long maxSizeFile = size;
    int currSizeBlock = 0;
    int maxSizeBlock = blockSize; //4096;//1024;//2048;//4096;

    int count = 0;
    int id = -1;

    //* multiply by 2 just to ensure enougth space
    int lenght = maxSizeBlock;
    ppData = (ppDATA) malloc(sizeof (pDATA) * lenght);
    for (i = 0; i < lenght; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
        /* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));
    long currSizeFile = 0.0f;

    openFile(ppFile, "a+b");
    while (currSizeFile <= maxSizeFile) {

        currSizeBlock = 0;
        count = 0;
        i = 0;
        while ((currSizeBlock + sizeof (DATA)) <= maxSizeBlock) {
            count++; //keep count

            //Generete PARTIDA
            randomPartida(ppPartida);

            //Generate Data
            id++;
            ppData[i]->id = id;

            //copy the random PARTIDA generated before
            memcpy(&(ppData[i]->partida), (*ppPartida), sizeof (PARTIDA));

            i++;
            currSizeBlock += sizeof (DATA);
        }
        fDataWriteBlock((*ppFile), ppData, maxSizeBlock / sizeof (DATA));
        currSizeFile += currSizeBlock; //update current size of file
    }
    closeFile(ppFile);

    for (i = 0; i < lenght; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}

void readRandomEntriesBlock(int blockSize) {
    ppPARTIDA ppPartida;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;
    int ask;
    int position;

    int lenght = blockSize;
    ppData = (ppDATA) malloc(sizeof (pDATA) * lenght);
    for (i = 0; i < lenght; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
        /* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));

    printf("Reading the first block ...\n");
    position = -1;
    do {
        position++;

        openFile(ppFile, "r+b");
        fDataReadBlock((*ppFile), ppData, blockSize / (sizeof (DATA)), position);

        i = 0;
        while (i < blockSize / sizeof (DATA)) {
            printEntries(ppData[i]);
            i++;
        }
        closeFile(ppFile);

        printf("What now?\n");
        printf("[0] Next Block\n");
        printf("[1] Stop reading ...\n");
        scanf("%d", &ask);
    } while (ask == 0);

    for (i = 0; i < lenght; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}

void readRandomEntriesBlockSorted(int blockSize) {
    ppPARTIDA ppPartida;

    FILE** ppFile;
    FILE** ppFileIndexTable;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppFileIndexTable = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;
    int ask = 0;
    int position, posId;
    int k_vias = 8;
    int lenght = blockSize;
    ppData = (ppDATA) malloc(sizeof (pDATA) * lenght);

    for (i = 0; i < lenght; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));

    ppINDEX_TABLE ppIndexTable;
    ppIndexTable = malloc(sizeof (pINDEX_TABLE) * k_vias);

    //the block size
    for (i = 0; i < k_vias; i++) {
        ppIndexTable[i] = malloc(sizeof (INDEX_TABLE));
    }

    openFileIndexTable(ppFileIndexTable, "r+b");
    printf("Reading the first block ...\n");
    position = 0;

    while (!feof(*ppFileIndexTable) && ask == 0) {
        fIndexTableReadBlock((*ppFileIndexTable), ppIndexTable, k_vias, position);
        position++;
        for (i = 1; i < k_vias; i++) {
            if (ppIndexTable[i] != NULL) {
                posId = ppIndexTable[i]->byteIndex;
                posId = posId / sizeof (DATA);
            }
        }

        printf("What now?\n");
        printf("[0] Next Block\n");
        printf("[1] Stop reading ...\n");
        scanf("%d", &ask);

        position++;
    }
    closeFile(ppFileIndexTable);

    for (i = 0; i < lenght; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}
