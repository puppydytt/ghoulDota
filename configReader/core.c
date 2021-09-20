#include <regex.h>
// -1 -not exist
// 0 empty file
void isErrorThrown(const FILE * config, const char *errorType) {
    /*if (config == EOF) {
        printf("Err type = %s", errorType);
    }*/
    return;
}

int reader(FILE * config) {
    struct {
        int keyStart;
        int keyReset;
        int keyEnd;
    } keyStruct;



    return keyStruct;
}

int ReadConfig(void) {
    FILE *config;
    long size;
    char init[1];

    config = fopen("../bind.ghoul", "r");
   // isErrorThrown(config, "Open file error");
    fseek(config, 0L, SEEK_END);
    size = ftell(config);
    fseek(config, 0, SEEK_SET);

    switch (size) {
        case -1:
            fclose(config);
          //  isErrorThrown(config, "Closure file error");
            config = fopen("../bind.ghoul", "w");
            printf("Init?(Y,N)");
            scanf("%c", init);
            break;
        case 0:
            printf("No script config was found in ghoul file");
            exit(1);
            break;
        default:
            return 0;
    }

    return 0;
}