#include <stdio.h>
#include <stdlib.h>


// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType *data;
	int used;
};

// Compute the hash function
int hash(int x)
{
	int size;
	scanf("%d", &size);
	return x % size;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if (pHashArray[i].used)
        {
            printf("Index %d -> %d, %c,Order-> %d\n", i, pHashArray[i].data->id, pHashArray[i].data->name, pHashArray[i].data->order);
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	int size;
	scanf("%d", size);

	struct HashType hashTable[100];
	for (int i = 0; i < size; ++i)
    {
        hashTable[i].used = 0;
    }

	for (int i = 0; i < recordSz; ++i)
    {
        int h = hash(pRecords[i].id);
        while (hashTable[h].used){
            h = (h + 1) % size;
        }
        hashTable[h].data = &pRecords[i];
        hashTable[h].used = 1;
    }

    displayRecordsInHash(hashTable, size);
    free(pRecords);

    return 0;



}