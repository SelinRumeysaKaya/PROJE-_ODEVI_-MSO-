#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX_CHAR_COUNT = 1024;
const char matrix_bigram_strings[10][3] = {"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
const char matrix_trigram_strings[10][4]= {"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
const float frequency_eng[20]= { 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
const float frequency_germ[20]= { 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };
//matrix_trigram_strings[5]=?

const float calculated_frequencies_bi[10];
const float calculated_frequencies_tri[10];
// bu i�lev, girilen kullan�c� girdisinin t�m bigramlar�n� yazd�r�r
void calculate_frequencies_bi(char str[])
{
    // bellekte bigramlar matrisi i�in 1024 sat�rl�k yer ay�r�yoruz
    char **input_str_bigrams = malloc(1024 * sizeof(char *)); // her sat�r yine bir karakter dizisi oldu�u i�in char * tipinde oluyor her sat�r
    for(int i = 0; i < 1024; i++)
    {
        // matrisin i�indeki her bir sat�r i�in 3 s�tunluk yer ay�r�yoruz
        input_str_bigrams[i] = malloc(3 * sizeof(char));
    }
// girilen input i�inde ka� tane bigram oldu�unu bu de�i�kene kaydediyoruz
    int input_bigram_count = 0;
// girilen input i�erisindeki bigramlar� buluyoruz
// 0. ve 1., 1. ve 2., 2. ve 3. �eklinde
    for (int i=0; i<strlen(str)- 2; i++)
    {
       char *bigram = (char*) malloc( 3 * sizeof(char) );
        bigram[0] = str[i];
        bigram[1] = str[i+1];
// buldu�umuz bir tane bigram� bigramlar matrisine kaydediyoruz
        input_str_bigrams[i] = bigram;
// toplam bigram say�s�n� 1 artt�r�yoruz
        input_bigram_count = input_bigram_count + 1;
    }
// 10 tane bigram verildi�i i�in 10'luk bir int dizisi a�t�k (say�lar�n� tutmak i�in)
    int * calculated_bigram_counts = malloc(10 * sizeof(int));

    // 10 tane bigram verildi�i i�in 10'luk bir float dizisi a�t�k (frekanslar�n� tutmak i�in)
    float * calculated_bigram_frequencies = malloc( 10 * sizeof(float));
// bize verilen 10 tane bigram'� d�n�yoruz
    for (int i=0; i<=10; i++)
    {
// bize verilen her bir bigram'�n input'un icinde ka� defa ge�ti�ini bu de�i�kene kaydediyoruz
        int count_of_bigram = 0;
// daha �nce buldu�umuz her bir bigram� d�n�yoruz
        for (int j=0; j<input_bigram_count; j++)
        {
// bize verilen bir tane bigram ile, input'un i�indeki bir tane bigram ayn� m� diye kar��la�t�r�yoruz
            int is_equal = strcmp(input_str_bigrams[j], matrix_bigram_strings[i]);
// e�er ikisi e�itse, mesela th = th, count'u 1 artt�r�yoruz
            if (is_equal == 0)
            {
                count_of_bigram = count_of_bigram + 1;
            }
        }
// toplamda bize verilen bir bigram�n say�s�n� kaydediyoruz.
        calculated_bigram_counts[i] = count_of_bigram;
    }

// bize verilen b�t�n bigramlar�n say�lar�n� hesaplad�ktan sonra form�le g�re frekanslar�n� hesapl�yoruz
// frekans = ka� defa ge�iyor / toplam ka� tane bigram var
    for (int i=0; i<=sizeof(calculated_bigram_counts); i++)
    {
        float bigram_frequency =  (calculated_bigram_counts[i] / (float)input_bigram_count);
        printf("\n'%s' bigrami input icinde %d defa gecmektedir ve frekansi: %f 'dir.\n", matrix_bigram_strings[i], calculated_bigram_counts[i],bigram_frequency );
    }

}

void filter_str(char str[])
{

// bize verilen girdiyi d�n�yoruz
    for (int i = 0; i < strlen(str); i++)
    {

// e�er karakter bo�luk karakteri de�ilse
        if (str[i] != '\x20')
        {

// e�er karakter A-Z aral���nda de�ilse
            if (str[i] < 65 || str[i] > 90)
            {
                str[i] = '\x20'; // bo�luk karakteri ile de�i�tir
            }
        }
    }
    int fark = 97 - 65;//ascii de 97 Z ye 65 ise A ya denk gelir
    int i = 0;
// bize verilen string'in sonuna gelene kadar d�n�yoruz
    while (str[i] != '\0')
    {
        if (str[i] <= 90 && str[i] >=65)
        {
            str[i] += fark;
        }
        else if (str[i] >= 97 && str[i] <= 122)
        {
            str[i] -= fark;
        }
        i++;
    }
}
//trigramlar i�in kullanaca��m�z frekans hesaplama burda yap�lacka
void calculate_frequencies_tri(char str[])
{
// bellekte trigramlar matrisi i�in 1024 sat�rl�k yer ay�r�yoruz
    char **input_str_trigram = malloc(1024 * sizeof(char *)); // her sat�r yine bir karakter dizisi oldu�u i�in char * tipinde oluyor her sat�r
    for(int i = 0; i < 1024; i++)
    {
        // matrisin i�indeki her bir sat�r i�in 4 s�tunluk yer ay�r�yoruz
        input_str_trigram[i] = malloc(4 * sizeof(char));
    }
// girilen input i�inde ka� tane trigram oldu�unu bu de�i�kene kaydediyoruz
    int input_trigram_count = 0;
// girilen input i�erisindeki trigramlar� buluyoruz

    for (int i=0; i<strlen(str)- 3; i++)
    {
        char *trigram = (char*) malloc( 4 * sizeof(char) );
        trigram[0] = str[i];
        trigram[1] = str[i+1];
        trigram[2] = str[i+2];
        // buldu�umuz bir tane trigram� trigramlar matrisine kaydediyoruz
        input_str_trigram[i] = trigram;
// toplam trigram say�s�n� 1 artt�r�yoruz
        input_trigram_count = input_trigram_count + 1;
    }
// 10 tane bigram verildi�i i�in 10'luk bir int dizisi a�t�k (say�lar�n� tutmak i�in)
    int * calculated_trigram_counts = malloc(10 * sizeof(int));
    for (int i =0; i<10;i++){
        calculated_trigram_counts[i]=0;
    }
    // 10 tane trigram verildi�i i�in 10'luk bir float dizisi a�t�k (frekanslar�n� tutmak i�in)
    float * calculated_trigram_frequencies = malloc( 10 * sizeof(float));
    for (int i=0;i<10;i++){
        calculated_trigram_frequencies[i]=0;
    }
// bize verilen 10 tane trigram'� d�n�yoruz
    for (int i=0; i<=10; i++)
    {
// bize verilen her bir trigram'�n input'un icinde ka� defa ge�ti�ini bu de�i�kene kaydediyoruz
        int count_of_trigram = 0;
// daha �nce buldu�umuz her bir trigram� d�n�yoruz
        for (int j=0; j<input_trigram_count; j++)
        {
// bize verilen bir tane trigram ile, input'un i�indeki bir tane trigram ayn� m� diye kar��la�t�r�yoruz
            int is_equal = strcmp(input_str_trigram[j],matrix_trigram_strings[i]);
// e�er ikisi e�itse, mesela th = th, count'u 2 artt�r�yoruz
            if (is_equal == 0)
            {
                count_of_trigram = count_of_trigram + 1;
            }

// toplamda bize verilen bir trigram�n say�s�n� kaydediyoruz.
            calculated_trigram_counts[i] = count_of_trigram ;
        }

// bize verilen b�t�n trigramlar�n say�lar�n� hesaplad�ktan sonra form�le g�re frekanslar�n� hesapl�yoruz
// frekans = ka� defa ge�iyor / toplam ka� tane trigram var
        for (int i=0; i<=sizeof(calculated_trigram_counts); i++)
        {
            float trigram_frequency =  (calculated_trigram_counts[i] / (float)input_trigram_count);
            printf("\n'%s' trigrami input icinde %d defa gecmektedir ve frekansi: %f 'dir.\n", matrix_trigram_strings[i], calculated_trigram_counts[i],trigram_frequency );
        }



    }
}
// bu fonksiyon mesafeleri hesaplar
void calculate_distances(const float distances [2][20])
{

}
//bu fonksiyon dili alg�lamay� saglar
void detect_lang()
{

}

int main()
{

    char input[MAX_CHAR_COUNT];
    printf("Metni giriniz: ");
    gets(input);

    filter_str(input);
    printf("temizlenmis input:\n%s", input); // temizlenmis input

    printf("\nbigram frekanslar�:\n");
    calculate_frequencies_bi(input);

    printf("\ntrigram frekanslar�:\n");
    calculate_frequencies_tri(input);

    return 0;
}
