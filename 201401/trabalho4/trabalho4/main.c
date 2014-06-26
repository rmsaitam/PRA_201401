/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

/**
 * \mainpage Trabalho 4 - Tabelas de Espalhamento
 *
 *
 * \section objetivo_sec Objetivo
 *
 *  Construir um sistema gerador de tabelas auxiliares de
indexação de dados para o banco de dados produzido no
trabalho 1 através de uma tabela de espalhamento.
 */

#include "main.h"

/**Menu principal do programa.
 */
void menu() {
    //to use random values
    srand(time(NULL));

    HashTable *table;
    table = malloc(sizeof (HashTable));
    table->numElements = 0;
    table->sizeOfTable = 0;
    table->hashTable = malloc(sizeof (Table*));
    *(table)->hashTable = malloc(sizeof (Table));

    int **hashTable; // vetor que guarda a tabela hash
    hashTable = malloc(sizeof (int*)); //aloca apenas 1 posicao 
    *hashTable = malloc(sizeof (int)); //ira usar realloc para guardar o arquivo inteiro

    int menu, submenu, status = 1, position, subsubmenu;
    int inicio, limit, atual;
    int ask;
    int size, blockSize = 4096, ok = 1;
    clock_t time_start, time_end;

    do {
        printf("\n[0] Create HashTable");
        printf("\n[10] Generate multiple random entries in file using block");
        printf("\n[11] Read entry in position using block");
        printf("\n[12] Create and insert one random entry");
        printf("\n[13] Read entry in position");
        printf("\n[9] exit");
        printf("\n");
        scanf("%d", &menu);

        switch (menu) {
            case 9:
                status = 0;
                break;

            case 0:

                // Criar a tabela a partir das chaves
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

                cmpKey1 = submenu;
                cmpKey2 = subsubmenu;

                time_end = time(NULL);
                executionTime(time_start, time_end);

                ok = 0;
                do {
                    printf("\n[1] Create hash table");
                    printf("\n[2] Remove item");
                    printf("\n[3] Re-index");
                    printf("\n[4] List items");
                    printf("\n[0] Exit");
                    printf("\n");
                    scanf("%d", &menu);

                    switch (menu) {
                        case 1:
                            time_start = time(NULL);

                            // select field to sort and generate
                            initHash(table, cmpKey1, cmpKey2);

                            time_end = time(NULL);
                            executionTime(time_start, time_end);
                            break;
                            /**/
                        case 2:
                            // remove entry
                            printf("What entry will be removed?\n");
                            scanf("%d", &position);
                            time_start = time(NULL);

                            // remove select item
                            removeHash(table, position);

                            time_end = time(NULL);
                            executionTime(time_start, time_end);
                            break;

                        case 3:
                            // re-index
                            printf("Re-indexing\n");
                            scanf("%d", &position);
                            time_start = time(NULL);

                            // re-index

                            time_end = time(NULL);
                            executionTime(time_start, time_end);
                            break;

                        case 4:
                            inicio = 0;
                            limit = 5;
                            atual = 0;

                            // list index table
                            show_hashlist(table);

                            printf("What now?\n");
                            printf("[0] Next Block\n");
                            printf("[1] Stop reading ...\n");
                            scanf("%d", &ask);

                            if (ask == 0) {
                                limit = 5;
                                inicio += limit;
                                atual = 0;
                            }
                            break;

                        case 0:
                            ok = -1;
                            break;
                    }

                } while (ok == 0);

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

                time_start = time(NULL);
                generateRandomEntriesBlock(size, blockSize);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                status = 1;
                break;

            case 11:
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

            default:
                status = 1;
                printf("\nPlease, select a valid option!!!");
                break;
        }

    } while (status == 1);
}

/**Gera uma entrada de dados da partida de futebol.
 */
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

/**Função para caculo do tempo de execução.
 */
void executionTime(clock_t time_start, clock_t time_end) {
    double duration;
    // calc time elapsed
    duration = (double) (time_end - time_start); /// CLOCKS_PER_SEC;

    // print elapsed time
    printf("\n=> This function was running for %.2lf seconds\n", duration);
}

/**Função para ler os dados de uma partida inserida.
 * @param position Valor da poisção dos dados da partida desejada.
 */
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

/**Função para gerar randomicamente um arquivo, em blocos de dados de partidas de futebol.
 * @param size Tamanho total de arquivos. 
 * @param blockSize Tamanho de cada bloco gerado.
 */
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
    int length = maxSizeBlock;
    ppData = (ppDATA) malloc(sizeof (pDATA) * length);
    for (i = 0; i < length; i++) {
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

    for (i = 0; i < length; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}

void readEntriesBlock(ppDATA ppData, int blockSize, int position) {
    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    int i = 0;
    openFile(ppFile, "r+b");

    fDataReadBlock((*ppFile), ppData, blockSize * (sizeof (DATA)), position);
}

/**Função para leitura dos dados gerados, em blocos. 
 * @param blockSize Tamanho do bloco que sera lido do arquivo gerado. 
 */
void readRandomEntriesBlock(int blockSize) {
    ppPARTIDA ppPartida;
    ppDATA ppData;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    int i = 0;
    int ask;
    int position;

    int length = blockSize;
    ppData = (ppDATA) malloc(sizeof (pDATA) * length);
    for (i = 0; i < length; i++) {
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

    for (i = 0; i < length; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}

void readAllEntriesBlock(ppDATA ppData) {
    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));

    openFile(ppFile, "r+b");

    fDataReadAll(ppFile, ppData);

    closeFile(ppFile);
}

/**Função para leitura dos dados gerados, em blocos. 
 * @param blockSize Tamanho do bloco que sera lido do arquivo gerado. 
 */
void readRandomEntriesBlockSorted(int blockSize) {
    ppPARTIDA ppPartida;

    FILE** ppFile;
    FILE** ppFileIndexTable;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppFileIndexTable = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;

    int count = 0;
    int id = -1;
    int ask = 0;
    int position, posId;
    //int k_vias = 8;
    int length = blockSize;
    ppData = (ppDATA) malloc(sizeof (pDATA) * length);
    for (i = 0; i < length; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
        /* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));


    ppINDEX_TABLE ppIndexTable;
    ppIndexTable = malloc(sizeof (pINDEX_TABLE) * blockSize);

    //the block size
    for (i = 0; i < blockSize; i++) {
        ppIndexTable[i] = malloc(sizeof (INDEX_TABLE));
    }


    openFileIndexTable(ppFileIndexTable, "r+b");
    /* openFile(ppFile,"r+b"); */
    printf("Reading the first block ...\n");
    position = 0;


    while (!feof(*ppFileIndexTable) && ask == 0) {

        fIndexTableReadBlock((*ppFileIndexTable), ppIndexTable, blockSize, position);
        position++;
        /* for(i=0;i<blockSize/sizeof(INDEX_TABLE);i++) */
        /* { */

        for (i = 1; i < blockSize; i++) {
            if (ppIndexTable[i] != NULL) {

                posId = ppIndexTable[i]->byteIndex;
                posId = posId / sizeof (DATA);
                readEntryPosition(position);
            }
        }

        printf("What now?\n");
        printf("[0] Next Block\n");
        printf("[1] Stop reading ...\n");
        scanf("%d", &ask);

        position++;
    }
    closeFile(ppFileIndexTable);

    for (i = 0; i < length; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free((*ppPartida));
    free(ppPartida);
}

/************ hash functions **************************************/

int getIntegerFromChar(char* string, int size) {
    int i = 0, result = 0;
    for (i = 0; i < size; i++) {
        result += (int) string[i];
    }
    return result;
}

void createIndex(HashTable* table, ppDATA ppData, int size) {
    unsigned int i = 0;

    // insert at table
    insert_hashes(table, ppData, size);

    // print index to file
    create_hashfile(table);
}

void removeHash(HashTable* table, int position) {
    int id = busca_hash(position, table);

    // set as deleted at file
    setRemoved(id * sizeof(DATA));
    
    // set as removed at hash table
    remove_hash(position, table);
}

void initHash(HashTable* table, int cmpKey1, int cmpKey2) {
    ppDATA ppData;
    unsigned int i = 0;
    int sizeOfAllBytes;

    unsigned int count, position = 0, size = fsize(FULLFILEPATH);
    sizeOfAllBytes = size / sizeof (DATA);
    count = sizeOfAllBytes / SIZE_BLOCK;

    ppData = malloc(sizeof (pDATA) * sizeOfAllBytes);
    for (i = 0; i < sizeOfAllBytes; i++) {
        ppData[i] = malloc(sizeof (DATA));
    }

    do {
        readEntriesBlock(ppData, SIZE_BLOCK, position);
        position += (SIZE_BLOCK);
        count--;

    } while (count > 0);


    // sort by field


    // create index()
    createIndex(table, ppData, sizeOfAllBytes);
}

/****************************************************************/

void teste_leitura() {
    ppDATA ppData;
    unsigned int i = 0;
    int sizeOfAllBytes;

    unsigned int count, position = 0, size = fsize(FULLFILEPATH);
    sizeOfAllBytes = size / sizeof (DATA);
    count = sizeOfAllBytes / SIZE_BLOCK;

    ppData = malloc(sizeof (pDATA) * sizeOfAllBytes);
    for (i = 0; i < sizeOfAllBytes; i++) {
        ppData[i] = malloc(sizeof (DATA));
    }

    do {
        readEntriesBlock(ppData, SIZE_BLOCK, position);
        position += (SIZE_BLOCK);
        count--;

    } while (count > 0);

    i = -1;
    do {
        i++;
        printEntries(ppData[i]);
    } while (ppData[i + 1]);
}

void teste_hash() {
    ppDATA ppData;

    //generateRandomEntriesBlock(4096, 4096);
}

/****************************************************************/

void main(void) {

    printf("\nWelcome!");
    // printf("\nWhat you want to do?");
    menu();

    //teste_leitura();

    //teste_hash();

}