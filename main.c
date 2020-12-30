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
// bu iþlev, girilen kullanýcý girdisinin tüm bigramlarýný yazdýrýr
void calculate_frequencies_bi(char str[])
{
    // bellekte bigramlar matrisi için 1024 satýrlýk yer ayýrýyoruz
    char **input_str_bigrams = malloc(1024 * sizeof(char *)); // her satýr yine bir karakter dizisi olduðu için char * tipinde oluyor her satýr
    for(int i = 0; i < 1024; i++)
    {
        // matrisin içindeki her bir satýr için 3 sütunluk yer ayýrýyoruz
        input_str_bigrams[i] = malloc(3 * sizeof(char));
    }
// girilen input içinde kaç tane bigram olduðunu bu deðiþkene kaydediyoruz
    int input_bigram_count = 0;
// girilen input içerisindeki bigramlarý buluyoruz
// 0. ve 1., 1. ve 2., 2. ve 3. þeklinde
    for (int i=0; i<strlen(str)- 2; i++)
    {
       char *bigram = (char*) malloc( 3 * sizeof(char) );
        bigram[0] = str[i];
        bigram[1] = str[i+1];
// bulduðumuz bir tane bigramý bigramlar matrisine kaydediyoruz
        input_str_bigrams[i] = bigram;
// toplam bigram sayýsýný 1 arttýrýyoruz
        input_bigram_count = input_bigram_count + 1;
    }
// 10 tane bigram verildiði için 10'luk bir int dizisi açtýk (sayýlarýný tutmak için)
    int * calculated_bigram_counts = malloc(10 * sizeof(int));

    // 10 tane bigram verildiði için 10'luk bir float dizisi açtýk (frekanslarýný tutmak için)
    float * calculated_bigram_frequencies = malloc( 10 * sizeof(float));
// bize verilen 10 tane bigram'ý dönüyoruz
    for (int i=0; i<=10; i++)
    {
// bize verilen her bir bigram'ýn input'un icinde kaç defa geçtiðini bu deðiþkene kaydediyoruz
        int count_of_bigram = 0;
// daha önce bulduðumuz her bir bigramý dönüyoruz
        for (int j=0; j<input_bigram_count; j++)
        {
// bize verilen bir tane bigram ile, input'un içindeki bir tane bigram ayný mý diye karþýlaþtýrýyoruz
            int is_equal = strcmp(input_str_bigrams[j], matrix_bigram_strings[i]);
// eðer ikisi eþitse, mesela th = th, count'u 1 arttýrýyoruz
            if (is_equal == 0)
            {
                count_of_bigram = count_of_bigram + 1;
            }
        }
// toplamda bize verilen bir bigramýn sayýsýný kaydediyoruz.
        calculated_bigram_counts[i] = count_of_bigram;
    }

// bize verilen bütün bigramlarýn sayýlarýný hesapladýktan sonra formüle göre frekanslarýný hesaplýyoruz
// frekans = kaç defa geçiyor / toplam kaç tane bigram var
    for (int i=0; i<=sizeof(calculated_bigram_counts); i++)
    {
        float bigram_frequency =  (calculated_bigram_counts[i] / (float)input_bigram_count);
        printf("\n'%s' bigrami input icinde %d defa gecmektedir ve frekansi: %f 'dir.\n", matrix_bigram_strings[i], calculated_bigram_counts[i],bigram_frequency );
    }

}

void filter_str(char str[])
{

// bize verilen girdiyi dönüyoruz
    for (int i = 0; i < strlen(str); i++)
    {

// eðer karakter boþluk karakteri deðilse
        if (str[i] != '\x20')
        {

// eðer karakter A-Z aralýðýnda deðilse
            if (str[i] < 65 || str[i] > 90)
            {
                str[i] = '\x20'; // boþluk karakteri ile deðiþtir
            }
        }
    }
    int fark = 97 - 65;//ascii de 97 Z ye 65 ise A ya denk gelir
    int i = 0;
// bize verilen string'in sonuna gelene kadar dönüyoruz
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
//trigramlar için kullanacaðýmýz frekans hesaplama burda yapýlacka
void calculate_frequencies_tri(char str[])
{
// bellekte trigramlar matrisi için 1024 satýrlýk yer ayýrýyoruz
    char **input_str_trigram = malloc(1024 * sizeof(char *)); // her satýr yine bir karakter dizisi olduðu için char * tipinde oluyor her satýr
    for(int i = 0; i < 1024; i++)
    {
        // matrisin içindeki her bir satýr için 4 sütunluk yer ayýrýyoruz
        input_str_trigram[i] = malloc(4 * sizeof(char));
    }
// girilen input içinde kaç tane trigram olduðunu bu deðiþkene kaydediyoruz
    int input_trigram_count = 0;
// girilen input içerisindeki trigramlarý buluyoruz

    for (int i=0; i<strlen(str)- 3; i++)
    {
        char *trigram = (char*) malloc( 4 * sizeof(char) );
        trigram[0] = str[i];
        trigram[1] = str[i+1];
        trigram[2] = str[i+2];
        // bulduðumuz bir tane trigramý trigramlar matrisine kaydediyoruz
        input_str_trigram[i] = trigram;
// toplam trigram sayýsýný 1 arttýrýyoruz
        input_trigram_count = input_trigram_count + 1;
    }
// 10 tane bigram verildiði için 10'luk bir int dizisi açtýk (sayýlarýný tutmak için)
    int * calculated_trigram_counts = malloc(10 * sizeof(int));
    for (int i =0; i<10;i++){
        calculated_trigram_counts[i]=0;
    }
    // 10 tane trigram verildiði için 10'luk bir float dizisi açtýk (frekanslarýný tutmak için)
    float * calculated_trigram_frequencies = malloc( 10 * sizeof(float));
    for (int i=0;i<10;i++){
        calculated_trigram_frequencies[i]=0;
    }
// bize verilen 10 tane trigram'ý dönüyoruz
    for (int i=0; i<=10; i++)
    {
// bize verilen her bir trigram'ýn input'un icinde kaç defa geçtiðini bu deðiþkene kaydediyoruz
        int count_of_trigram = 0;
// daha önce bulduðumuz her bir trigramý dönüyoruz
        for (int j=0; j<input_trigram_count; j++)
        {
// bize verilen bir tane trigram ile, input'un içindeki bir tane trigram ayný mý diye karþýlaþtýrýyoruz
            int is_equal = strcmp(input_str_trigram[j],matrix_trigram_strings[i]);
// eðer ikisi eþitse, mesela th = th, count'u 2 arttýrýyoruz
            if (is_equal == 0)
            {
                count_of_trigram = count_of_trigram + 1;
            }

// toplamda bize verilen bir trigramýn sayýsýný kaydediyoruz.
            calculated_trigram_counts[i] = count_of_trigram ;
        }

// bize verilen bütün trigramlarýn sayýlarýný hesapladýktan sonra formüle göre frekanslarýný hesaplýyoruz
// frekans = kaç defa geçiyor / toplam kaç tane trigram var
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
//bu fonksiyon dili algýlamayý saglar
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

    printf("\nbigram frekanslarý:\n");
    calculate_frequencies_bi(input);

    printf("\ntrigram frekanslarý:\n");
    calculate_frequencies_tri(input);

    return 0;
}
