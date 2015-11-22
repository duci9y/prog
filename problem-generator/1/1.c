#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define BUFFERSIZE UINT8_MAX

char inputStream[BUFFERSIZE], outputStream[BUFFERSIZE];
unsigned int inputOffset = 0, outputOffset = 0;
unsigned int bufferSize = 0;

char static inline read_int()
{
    char returnValue = 0, dataStatus = 0;
    while(1)
    {
        if(inputOffset >= bufferSize)
        {
            bufferSize = read(STDIN_FILENO, inputStream, BUFFERSIZE);
            inputOffset = 0;
        }
        if(inputStream[inputOffset] < 48)
        {
            inputOffset++;
            if(dataStatus)
                return returnValue;
        }
        else
        {
            dataStatus = 1;
            returnValue *= 10;
            returnValue += (inputStream[inputOffset++] - 48);
        }
    }
}

char static inline read_fast()
{
    char returnValue = 0, dataStatus = 0;
    while(1)
    {
        if(inputOffset >= bufferSize)
        {
            bufferSize = read(STDIN_FILENO, inputStream, BUFFERSIZE);
            inputOffset = 0;
        }
        if(inputStream[inputOffset] < 48)
        {
            inputOffset++;
            if(dataStatus)
                return returnValue;
        }
        else
        {
            dataStatus = 1;
            if(inputStream[inputOffset++] % 2)
                returnValue = 'O';
            else
                returnValue = 'E';
        }
    }
}

void flush()
{
    write(STDOUT_FILENO, outputStream, outputOffset);
    outputOffset = 0;
}

void static inline write_fast(char in)
{
    if(outputOffset > BUFFERSIZE - 5)
    {
        flush();
    }
    if(in == 'Y')
    {
        sprintf(outputStream + outputOffset, "YES\n");
        outputOffset += 4;
    }
    else
    {
        sprintf(outputStream + outputOffset, "NO\n");
        outputOffset += 3;
    }

}

int main()
{
    signed char testCase, arrLen, evenLen, evenCount = 0, oddCount;
    testCase = read_int();
    while(testCase--)
    {
        evenCount = 0;
        oddCount = 0;
        arrLen = read_int();
        evenLen = read_int();
        while(arrLen--)
        {
            if(read_fast() == 'E')
                evenCount++;
            else
                oddCount++;
        }
        if(evenLen == 0)
        {
            if(oddCount)
                write_fast('Y');
            else
                write_fast('N');
        }
        else if(evenCount >= evenLen)
            write_fast('Y');
        else
            write_fast('N');
    }
    flush();
    return 0;
}
