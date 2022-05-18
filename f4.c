#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 100


void insertSort(int arr[], int n, int unsorted_vertex[])
{
    int i, j, temp, temp_i;
    for (i = 1; i < n; i++)
    {
        temp = arr[i];
        temp_i = unsorted_vertex[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] < temp)
                break;
    
            arr[j + 1] = arr[j];
            arr[j] = temp;
            unsorted_vertex[j + 1] = unsorted_vertex[j];
            unsorted_vertex[j] = temp_i;
        }
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
    int *output_vertex;

    int w = 0, h = 0, cc = 0, len;
    char input[VERTEX_COUNT];

    int removal_edge[2];
    int *vertex_weight;


    FILE * matrixFile;


    /*   ------------------             СОЗДАЕМ ДВУМЕРНЫЙ МАССИВ ДЛЯ ГРАФА               --------------    */
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

                if(matrix[h][w]) printf("%d-%d\n", h+1, w+1);       //Выводит, если есть грань

                w++;
            }
        }
        h++;
    }

    /*   ------------------             СОЗДАЕМ МАССИВ ВЕСОВ ВЕРТУШЕК               --------------    */
    len = h;
    vertex_weight = (int *) malloc(len * sizeof(int));


    /*   ------------------             СОЗДАЕМ МАССИВ С НУМЕРАЦИЕЙ ВЕРШИН               --------------    */
    output_vertex = (int*) malloc(len * sizeof(int));
    for(int i = 0; i < len; i++)
    {
        output_vertex[i] = i + 1;
    }


    /*   ------------------             УДАЛЯЕМ ГРАНЬ                --------------    */
    printf("What edge to delete? Enter like 'x y': ");
    scanf("%d %d", &removal_edge[0], &removal_edge[1]);

    if(!matrix[removal_edge[0] - 1][removal_edge[1] - 1]){
        printf("You pick couple of vertex that haven't edge or oversize.\n");
		return 1;
    }
    matrix[removal_edge[0] - 1][removal_edge[1] - 1] = 0;
    matrix[removal_edge[1] - 1][removal_edge[0] - 1] = 0;


    /*   ------------------             СЧИТАЕМ ВЕС КАЖДОЙ ВЕРШИНЫ               --------------    */
    for(int i = 0; i < len; i++)
    {
        vertex_weight[i] = weight_count(matrix[i], len, i);
    }

    /*   ------------------             СОРТИРОВКА ВСТАВКАМИ               --------------    */

    insertSort(vertex_weight, len, output_vertex);


    /*   --------------------           ТУПО ВЫВОД              ----------------------   */
    printf("Sorted Vertex by weight\n");
    for(int j = 0; j< h; j++){
        // for(int k = 0; k < w; k++){
        //     printf("%d-%d: %d\n", j+1, k+1, matrix[j][k]);
        // }
        printf("%d ", output_vertex[j]);
    }

    return 1;
}