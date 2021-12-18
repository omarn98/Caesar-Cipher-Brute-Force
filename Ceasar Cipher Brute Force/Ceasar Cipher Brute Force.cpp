#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <time.h>

#define numOfThreads 12
std::string readFile();
void writeToFile(std::string text);

int main()
{
    clock_t tStart = clock();
    std::string plainText = "", cipherText = readFile();
    int flag = 0;
    
    omp_set_num_threads(numOfThreads);
    #pragma omp parallel
    {
       
        int i,j;
        
        #pragma omp for 
        for (i = 1; i <= 10; i++)
        {
          
            std::string test;
            for (j = 0; j < cipherText.length(); j++)
            {
                if (j == 0)
                {
                    test = "";
                }
                int ascii = int(cipherText[j]) - i;

                if (ascii < 32)
                {
                    ascii += 222;
                }
                test += char(ascii);
            }
            
            if (test.find("the") != std::string::npos) {
                flag = 1; 
                plainText = test;
                break;
            }
        

        }


    }


    


    writeToFile(plainText);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}


std::string readFile()
{
    std::string word, cipherText;
    std::ifstream cipherFile("cipherText.txt");
    while (cipherFile >> word)
    {
        cipherText += word;
    }

    cipherFile.close();

    return cipherText;
}

void writeToFile(std::string text)
{
    std::ofstream cipherFile("plainText.txt");
    if (cipherFile.is_open())
    {
        cipherFile << text;
    }
    else
    {
        std::cout << "unable to open file";
    }
    return;

}