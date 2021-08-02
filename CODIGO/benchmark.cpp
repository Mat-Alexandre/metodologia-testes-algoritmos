#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <fstream>

/**
 * Disponibilizado por: https://pt.wikipedia.org/wiki/Selection_sort#Exemplos_de_c%C3%B3digos
 */
void selectionSort(std::vector<int> vetor)
{
    for (int i = 0; i < (int)vetor.size(); i++)
    {
        int min = i;
        for (int next = i+1; next < (int)vetor.size(); next++)
        {
            if (vetor[next] < vetor[min])
                min = next;
        }
        // swap
        int aux = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = aux;
    }
}

/**
 * Disponibilizado por: https://pt.wikipedia.org/wiki/Insertion_sort#C++
 */
void insertionSort(std::vector<int> vetor)
{
    for (int i = 1; i < (int)vetor.size(); i++)
    {
		int aux = vetor[i];
		int j = i - 1;
		
		while ((j >= 0) && (vetor[j] > aux))
        {
			vetor[j + 1] = vetor[j];
			j--;
		}
		
		vetor[j + 1] = aux;
	}
}

/**
 * Disponibilizado por: https://en.wikipedia.org/wiki/Bubble_sort#Pseudocode_implementation
 */
void bubbleSort(std::vector<int> vector)
{ 
    for (int i = 0; i < (int)vector.size(); i++)
    {
        for (int j = 0; j < (int)vector.size()-1; j++)
        {
            if(vector[j] > vector[j+1])
            {
                // swap
                int aux = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = aux;
            }
        }
    }
}

/**
 * Disponibilizado por: https://pt.wikipedia.org/wiki/Cocktail_sort#C%C3%B3digo_em_C
 */
void cocktailSort(std::vector<int> vector)
{
    int bottom, top, swapped;
    bottom = 0;
    top = (int)vector.size() - 1;
    swapped = 0; 
    
    while(swapped == 0 && bottom < top)
    {
        swapped = 1; 
        for(int i = bottom; i < top; i++)
        {
            if(vector[i] > vector[i + 1])
            {
                int aux = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = aux;
                swapped = 0;
            }
        }
        
        top = top - 1; 
        
        for(int i = top; i > bottom; i--)
        {  
            if(vector[i] < vector[i - 1]) 
            {
                int aux = vector[i];
                vector[i] = vector[i-1];
                vector[i-1] = aux;
                swapped = 0;
            }
        }
        
        bottom = bottom + 1;  
    }
}

/**
 * @param int vecSize   tamanho do vetor a ser inicializado
 *
 * @return std::vector<int> vetor de inteiros de tamnaho especificado
 */
std::vector<int> initializeRandomVec(int vecSize)
{
    std::vector<int> vector(vecSize);
    
    for( int i = 0; i < (int)vector.size(); i++) {
        vector[i] = rand() % vecSize + 1;
    }
    
    return vector;
}

/**
 * @param int vecSize   tamanho do vetor a ser inicializado
 *
 * @return std::vector<int> vetor de inteiros de tamnaho especificado
 */
std::vector<int> initializeOrderedVec(int vecSize)
{
    std::vector<int> vector(vecSize);
    
    for( int i = 0; i < (int)vector.size(); i++) {
        vector[i] = i + 1;
    }
    
    return vector;
}

/**
 * @param int vecSize   tamanho do vetor a ser inicializado
 *
 * @return std::vector<int> vetor de inteiros de tamnaho especificado
 */
std::vector<int> initializeReverseVec(int vecSize)
{
    std::vector<int> vector(vecSize);
    
    for( int i = 0; i < (int)vector.size(); i++) {
        vector[i] = vector.size() - i;
    }
    
    return vector;
}

/**
 * @param int numTest                       quantidade de testes que serão realizadas
 * @param void (*func)(std::vector<int>)    função de ordenação a ser executada
 * @param std::vector<int> vector           vetor que será ordenado
 * @param const std::string  fileName       nome do arquivo de saída
 *
 * @return 
 */
void runTest(
    int numTest, 
    void (*func)(std::vector<int>), 
    std::vector<int> vector, 
    const std::string fileName
    )
{
    clock_t start, end;
    double time_taken = 0;

    std::ofstream myfile;
    myfile.open(fileName, std::ios::app);
    
    for(int i = 0; i < numTest; i++)
    {
        start = clock();
        func(vector);
        end = clock();
        
        time_taken += double(end - start) * 1000 / double(CLOCKS_PER_SEC);        
        
    }
    time_taken /= numTest;
    
    myfile << std::fixed << time_taken << std::setprecision(9) << " ms\n";
    
    myfile.close();
}

/**
 * @param int numTest                       quantidade de testes que serão realizadas
 * @param int vecsize                       tamanho do vetor
 * @param void (*func)(std::vector<int>)    função de ordenação a ser executada
 * @param const std::string  fileName       nome do arquivo de saída
 *
 * @return 
 */
void benchmark(
    int numTest, 
    int vecSize,  
    void (*func)(std::vector<int>), 
    const std::string fileName
    )
{
    std::vector<int> vector;
    std::ofstream myfile;
    
    myfile.open(fileName, std::ios::app);
    myfile << vecSize << ":\n";
    myfile << "Sorted: ";
    myfile.close();
    vector = initializeOrderedVec(vecSize);
    runTest(numTest, func, vector, fileName);

    myfile.open(fileName, std::ios::app);
    myfile << "Reverse: ";
    myfile.close();
    vector = initializeReverseVec(vecSize);
    runTest(numTest, func, vector, fileName);

    myfile.open(fileName, std::ios::app);
    myfile << "Random: ";
    myfile.close();
    vector = initializeRandomVec(vecSize);
    runTest(numTest, func, vector, fileName);

    myfile.open(fileName, std::ios::app);
    myfile << "\n";
    myfile.close();

    std::cout << "Benchmark " << vecSize << " units DONE!" << std::endl;
}

int main()
{
    int sampleSizes[] = { 100, 1000, 10000, 100000 };
    int iterations[]  = { 100, 10, 1, 1 };
    std::ofstream myfile;

    for(int i = 0; i < 4; i++)
    {
        myfile.open("results", std::ios::app);
        myfile << "SELECTIONSORT ";
        myfile.close();
        benchmark(iterations[i], sampleSizes[i], selectionSort, "results");
        
        myfile.open("results", std::ios::app);
        myfile << "INSERTION ";
        myfile.close();
        benchmark(iterations[i], sampleSizes[i], insertionSort, "results");
        
        myfile.open("results", std::ios::app);
        myfile << "BUBBLESORT ";
        myfile.close();
        benchmark(iterations[i], sampleSizes[i], bubbleSort,    "results");
        
        myfile.open("results", std::ios::app);
        myfile << "COCKTAILSORT ";
        myfile.close();
        benchmark(iterations[i], sampleSizes[i], cocktailSort,  "results");
    }

    return 0;
}