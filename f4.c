#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 100

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void bubbleSort(int arr[], int n, int **secondArr)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
    }
                
}

int weight_count(int *line, int len, int i)
{
    int wi = 0, weight = 0;

    while (wi < len)
    {
        if(wi != i) weight += line[wi]; 
        wi++;    
    }
    weight += weight*line[i];
    return weight;
}

int main(void)
{
    int maxlen = VERTEX_COUNT*10;
    char line[maxlen];
    int **matrix;

    int w = 0, h = 0, cc = 0, len;
    char input[VERTEX_COUNT];

    int removal_edge[2];
    int *vertex_weight;


    FILE * matrixFile;


    matrix = (int**) malloc(VERTEX_COUNT * sizeof(int*));
    for(int i = 0; i < VERTEX_COUNT; i++){
        matrix[i] = (int*) malloc(VERTEX_COUNT * sizeof(int));
    }
    


    /*   ------------------             СЧИТЫВАЕТ ФАЙЛИК С МАТРИЦЕЙ               --------------    */
    matrixFile = fopen("matrix.txt", "r");
        if (matrixFile == NULL)
        {
            printf("Can't open file for reading.\n");
		    return 1;
        }

    /*   ------------------             ЗАПИСЫВАЕТ МАТРИЦУ В МАССИВ               --------------    */
    while(fgets(line, maxlen, matrixFile))
    {
        w = 0;

        for(int i = 0; line[i]; i++)
        {
            if(line[i] != ' ' && line[i] != '\n')
            {
                if(line[i] == '0')
                    matrix[h][w] = 0;
                else
                    matrix[h][w] = 1;
                printf("%d-%d:%d\n", h+1, w+1, matrix[h][w]);
                w++;
            }
        }
        h++;
    }

    /*   ------------------             СОЗДАЕМ МАССИВ ВЕСОВ ВЕРТУШЕК               --------------    */
    len = h;
    vertex_weight = (int *) malloc(len * sizeof(int));

    printf("What edge to delete? Enter like 'x y': ");
    scanf("%d %d", &removal_edge[0], &removal_edge[1]);
    printf("%d-%d", removal_edge[0], removal_edge[1]);

    /*   ------------------             УДАЛЯЕМ ГРАНЬ                --------------    */
    matrix[removal_edge[0] - 1][removal_edge[1] - 1] = 0;
    matrix[removal_edge[1] - 1][removal_edge[0] - 1] = 0;


    /*   ------------------             СЧИТАЕМ ВЕС КАЖДОЙ ВЕРШИНЫ               --------------    */
    for(int i = 0; i < len; i++)
    {
        vertex_weight[i] = weight_count(matrix[i], len, i);
        printf("%d", vertex_weight[i]);
    }

    /*   ------------------             СОРТИРОВКА БУБЛИКОМ               --------------    */
    printf("\n");
    bubbleSort(vertex_weight, len, matrix);
    printf("\n");

    /*   --------------------           ТУПО ВЫВОД              ----------------------   */
    for(int j = 0; j< h; j++){
        for(int k = 0; k < w; k++){
            printf("%d-%d: %d\n", j+1, k+1, matrix[j][k]);
        }
        //printf("%d ", vertex_weight[j]);
    }

    return 1;
}