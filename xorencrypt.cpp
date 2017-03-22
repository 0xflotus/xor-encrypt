/*
 * Version 1.2 from 28th Feb 2017
 */

#include <string.h>
#include <iostream>

using namespace std;

char key;

void code(char* input, char* output) {
    int ch;
    FILE *fp1, *fp2, *fp3;
    if ((fp1 = fopen(input, "r")) == 0) {
        cout << "Inputfile kann nicht geoeffnet werden!" << endl;
        exit(-1);
    }
    if ((fp2 = fopen(output, "w")) == 0) {
        cout << "Outputfile kann nicht geoeffnet werden!" << endl;
        exit(-1);
    }
    if ((fp3 = fopen("key.f", "w")) == 0) {
        cout << "keyfile kann nicht geoeffnet werden!" << endl;
        exit(-1);
    }
    do {
        ch = getc(fp1);
        if (ch == EOF) break;
        ch ^= key;
        if (ch == EOF) ch++;
        putc(ch, fp2);
    } while (true);
    putc(key, fp3);
    putc((int)'\n', fp3);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return;
}

void decode(char* input, char* output) {
    int ch;
    FILE *fp1, *fp2;
    if ((fp1 = fopen(input, "r")) == 0) {
        cout << "Inputfile kann nicht geoeffnet werden!" << endl;
        exit(-1);
    }
    if ((fp2 = fopen(output, "w")) == 0) {
        cout << "Outputfile kann nicht geoeffnet werden!" << endl;
        exit(-1);
    }
    do {
        ch = getc(fp1);
        if (ch == EOF) break;
        ch ^= key;
        if (ch == EOF) ch--;
        putc(ch, fp2);
    } while (true);
    fclose(fp1);
    fclose(fp2);
    return;
}

int main(int argc, char** argv) {
    if (argc != 5) {
        cout << "Eingabeformat: xorencrypt input " \
                "output decode|encode key" << endl;
        exit(-1);
    }
    if (strlen(argv[4])>1)
    {
        cout << "Fehler: key darf nur ein Zeichen lang sein!" << endl;
        exit(-1);
    }
    cout << "Eingabefile: " << argv[1] << endl;
    cout << "Ausgabefile: " << argv[2] << endl;
    key = *argv[4];
    if (strcmp(argv[3], "encode") == 0)
        code(argv[1], argv[2]);
    else
        decode(argv[1], argv[2]);
    return 0;
}