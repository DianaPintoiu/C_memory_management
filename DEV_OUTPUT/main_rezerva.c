#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>
int add_last(void **arr, int *len, data_structure *data)
{
	int element_length = 0;
	if (*len == 0)
		// we allocate for the first time so malloc
		*arr = malloc((data->header->len + 5) * sizeof(char));
	else
	{
		int parcurgeri = 0; // this is how many times we go through the elements of the array
		int terminator = 0; // it terminates when we find the terminator obvi
		char tip;
		while (parcurgeri < *len)
		{
			// memorez in tip de tip char tipul bacnotelro
			memmove(&tip, *arr + element_length, sizeof(char));
			// e plus 5 pentru tipul memorat plus 4 pentru length-ul data-ului
			element_length = element_length + 5;
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				// se aduna caracterele din nume la length
				element_length++;
			}
			if (tip == '1') // sunt 2 bacnote de un octet fiecare deci +2
				element_length = element_length + 2;
			else if (tip == '2')
				element_length = element_length + 6; // o bacnota de 2 octeti si una de 4
			else if (tip == '3')
				element_length = element_length + 8; // 2 bacnote de 4 octeti
			/// again sw numara caracterele numelui
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				element_length++;
			}
			parcurgeri++; // creste pana se ajunge la ultimul el
		}
		// realocare pentru noul element
		*arr = realloc(*arr, element_length + data->header->len + 5);
	}
	// pune tot la finalul vectorului
	memmove(*arr + element_length, &data->header->type, sizeof(char));
	element_length = element_length + 1;
	memmove(*arr + element_length, &data->header->len, sizeof(int));
	element_length = element_length + 4;
	memmove(*arr + element_length, data->data, data->header->len);
	element_length = element_length + data->header->len;
	// creste length-ul cu un element ca am adunat un element
	*len = *len + 1;
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index < 0) // nu exista pe acea pozitie un el
		return -1;
	else if (index > *len) // nu exista deci pune la final
		add_last(arr, len, data);
	else
	{
		int element_length = 0;
		if (*len == 0)
		{
			add_last(arr, len, data);
		}
		else
		{
			char tip;
			int length_to_insert_at = 0;
			int parcurgeri = 0;
			int terminator = 0;
			/// aceeasi parcurgere dar pana la index
			while (parcurgeri < index)
			{

				memmove(&tip, *arr + element_length, sizeof(char));
				element_length = element_length + 5;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				if (tip == '1')
					element_length = element_length + 2;
				else if (tip == '2')
					element_length = element_length + 6;
				else if (tip == '3')
					element_length = element_length + 8;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				parcurgeri++;
			}
			// de aici se va insera noul element
			length_to_insert_at = element_length;
			// se va folosi aceeasi parcurgere pana la finalul vectorului
			// dar de unde am ramas, nu se mai initializeaza nimic cu 0
			while (parcurgeri < *len)
			{
				memmove(&tip, *arr + element_length, sizeof(char));
				element_length = element_length + 5;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				if (tip == '1')
					element_length = element_length + 2;
				else if (tip == '2')
					element_length = element_length + 6;
				else if (tip == '3')
					element_length = element_length + 8;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				parcurgeri++;
			}
			// realoca pt noul element
			*arr = realloc(*arr, element_length + data->header->len + 5);
			// se va insera prima data elementele de fix dupa unde trebuie inserat noul element
			// pentru a nu fi supreascris
			memmove(*arr + length_to_insert_at + data->header->len + 5,
					*arr + length_to_insert_at, element_length - length_to_insert_at);
			// apoi se insereaza elementul
			// prima data tipul
			memmove(*arr + length_to_insert_at, &data->header->type, sizeof(char));
			length_to_insert_at = length_to_insert_at + 1;
			// apoi len-ul vectorului data
			memmove(*arr + length_to_insert_at, &data->header->len, sizeof(int));
			length_to_insert_at = length_to_insert_at + 4;
			// apoi elementul efectiv
			memmove(*arr + length_to_insert_at, data->data, data->header->len * sizeof(char));
			length_to_insert_at = length_to_insert_at + data->header->len;
			// creste nr de elemente
			*len = *len + 1;
		}
	}
	return 0;
}

void find(void *data_block, int len, int index)
{
	int i;
	char tip;
	int element_length = 0;
	int terminator;
	int8_t bac1, bac2;			  // pentru tipul 1
	int16_t bac12;				  // pentrul tipul 2 (prima bac)
	int32_t bac22, bac13, bac23;  // pentru tipul 2 (prima bac) si pt tipul 3 celelalte 2
	if (index < 0 || index > len) // nu exista deci nu se pot gasi
		return;
	else
	{
		for (i = 0; i < len; i++) // se parcurg toate elementele
								  //  pana se gaseste cea cu indexul
		{
			if (i == index) // se gaseste
			{
				// se memoreaza tipul
				memmove(&tip, data_block + element_length, sizeof(char));
				// deoarce asa trebuie printat
				printf("Tipul %c\n", tip);

				/// Aceeasi parcurgere ca la add_at sau add_last
				element_length = element_length + 5;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)data_block) + element_length) == '\0')
						terminator = -1;
					else
						// printeaza caracter cu caracter numele
						//  pana gaseste terminatorul de sir
						printf("%c", *(((char *)data_block) + element_length));
					element_length++;
				}
				printf(" pentru ");
				// se vor memora bacnotele pt mai tarziu
				//  deoarece asa sunt memorate in vector
				if (tip == '1')
				{
					// bac1 e de tip int8_t
					memmove(&bac1, data_block + element_length, 1);
					// deci se creste cu 1
					element_length++;
					// bac2 e de tip int8_t
					memmove(&bac2, data_block + element_length, 1);
					// deci se creste cu 1
					element_length++;
				}
				else if (tip == '2')
				{
					// bac12 e de tip int16_t
					memmove(&bac12, data_block + element_length, 2);
					// deci se creste cu 2
					element_length = element_length + 2;
					// bac22 e de tip int32_t
					memmove(&bac22, data_block + element_length, 4);
					// deci se creste cu 4
					element_length = element_length + 4;
				}
				else if (tip == '3')
				{
					// bac22 e de tip int32_t
					memmove(&bac13, data_block + element_length, 4);
					// deci se creste cu 4
					element_length = element_length + 4;
					// bac22 e de tip int32_t
					memmove(&bac23, data_block + element_length, 4);
					// deci se creste cu 4
					element_length = element_length + 4;
				}
				// se parcurge al doilea nume si se afiseaza la fel ca si primul
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)data_block) + element_length) == '\0')
						terminator = -1;
					else
						printf("%c", *(((char *)data_block) + element_length));
					element_length++;
				}
				printf("\n");
				// se printeaza in functie de tip
				if (tip == '1')
				{
					printf("%" PRId8 "\n", bac1);
					printf("%" PRId8 "\n", bac2);
				}
				else if (tip == '2')
				{
					printf("%" PRId16 "\n", bac12);
					printf("%" PRId32 "\n", bac22);
				}
				else if (tip == '3')
				{
					printf("%" PRId32 "\n", bac13);
					printf("%" PRId32 "\n", bac23);
				}
				printf("\n");
			}
			else 
			/// aici este aceeasi parcurgere ca mai sus dar fara printf - uri
			// deoarece este nevoie de parcurgere pt a ajunge la elementului care trebuie afisat
			{
				memmove(&tip, data_block + element_length, sizeof(char));
				// printf("Tipul %c\n", tip);
				element_length = element_length + 5;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)data_block) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				if (tip == '1')
				{
					memmove(&bac1, data_block + element_length, 1);

					element_length++;

					memmove(&bac2, data_block + element_length, 1);
					element_length++;
				}
				else if (tip == '2')
				{
					memmove(&bac12, data_block + element_length, 2);

					element_length = element_length + 2;

					memmove(&bac22, data_block + element_length, 4);

					element_length = element_length + 4;
				}
				else if (tip == '3')
				{
					memmove(&bac13, data_block + element_length, 4);

					element_length = element_length + 4;

					memmove(&bac23, data_block + element_length, 4);

					element_length = element_length + 4;
				}
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)data_block) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
			}
		}
	}
}
///functia delete seamana cu functia de add_last si add_at
int delete_at(void **arr, int *len, int index)
{
	int element_length = 0;
	int length_end_to_be_deleted = 0;
	if (index < 0 || index + 1 > *len) //daca nu are unde sa st
		return -1;
	else
	{
		char tip;
		int length_to_be_deleted_at = 0;
		int parcurgeri = 0;
		int terminator = 0;
		while (parcurgeri < index)
		{

			memmove(&tip, *arr + element_length, sizeof(char));
			element_length = element_length + 5;
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				element_length++;
			}
			if (tip == '1')
				element_length = element_length + 2;
			else if (tip == '2')
				element_length = element_length + 6;
			else if (tip == '3')
				element_length = element_length + 8;
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				element_length++;
			}
			parcurgeri++;
		}
		length_to_be_deleted_at = element_length;
		if (index + 1 == *len)
		{
			*arr = realloc(*arr, element_length);
		}
		else
		{
			// if the element to be deleted isnt the last one
			// i get the length  of the el to be deleted from the start (length_to_be_deleted)
			//  and then the final of that length is element length
			memmove(&tip, *arr + element_length, sizeof(char));
			element_length = element_length + 5;
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				element_length++;
			}
			if (tip == '1')
				element_length = element_length + 2;
			else if (tip == '2')
				element_length = element_length + 6;
			else if (tip == '3')
				element_length = element_length + 8;
			terminator = 0;
			while (terminator == 0)
			{
				if (*(((char *)*arr) + element_length) == '\0')
					terminator = -1;
				element_length++;
			}
			parcurgeri++;
			// this is the length from where we start to overwrite the array
			length_end_to_be_deleted = element_length;
			while (parcurgeri < *len)
			{

				memmove(&tip, *arr + element_length, sizeof(char));
				element_length = element_length + 5;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				if (tip == '1')
					element_length = element_length + 2;
				else if (tip == '2')
					element_length = element_length + 6;
				else if (tip == '3')
					element_length = element_length + 8;
				terminator = 0;
				while (terminator == 0)
				{
					if (*(((char *)*arr) + element_length) == '\0')
						terminator = -1;
					element_length++;
				}
				parcurgeri++;
			}
			memmove(*arr + length_to_be_deleted_at, *arr + length_end_to_be_deleted, element_length - length_end_to_be_deleted);
			*arr = realloc(*arr, element_length - (length_end_to_be_deleted - length_to_be_deleted_at));
		}
		*len = *len - 1;
	}
}

void print(void *arr, int len)
{
	int i;
	char tip;
	int element_length = 0;
	int terminator;
	int8_t bac1, bac2;
	int16_t bac12;
	int32_t bac22, bac13, bac23;
	for (i = 0; i < len; i++)
	{
		memmove(&tip, arr + element_length, sizeof(char));
		printf("Tipul %c\n", tip);
		element_length = element_length + 5;
		terminator = 0;
		while (terminator == 0)
		{
			if (*(((char *)arr) + element_length) == '\0')
				terminator = -1;
			else
				printf("%c", *(((char *)arr) + element_length));
			element_length++;
		}
		printf(" pentru ");
		if (tip == '1')
		{
			memmove(&bac1, arr + element_length, 1);

			element_length++;

			memmove(&bac2, arr + element_length, 1);
			element_length++;
		}
		else if (tip == '2')
		{
			memmove(&bac12, arr + element_length, 2);

			element_length = element_length + 2;

			memmove(&bac22, arr + element_length, 4);

			element_length = element_length + 4;
		}
		else if (tip == '3')
		{
			memmove(&bac13, arr + element_length, 4);

			element_length = element_length + 4;

			memmove(&bac23, arr + element_length, 4);

			element_length = element_length + 4;
		}
		terminator = 0;
		while (terminator == 0)
		{
			if (*(((char *)arr) + element_length) == '\0')
				terminator = -1;
			else
				printf("%c", *(((char *)arr) + element_length));
			element_length++;
		}
		printf("\n");
		if (tip == '1')
		{
			printf("%" PRId8 "\n", bac1);
			printf("%" PRId8 "\n", bac2);
		}
		else if (tip == '2')
		{
			printf("%" PRId16 "\n", bac12);
			printf("%" PRId32 "\n", bac22);
		}
		else if (tip == '3')
		{
			printf("%" PRId32 "\n", bac13);
			printf("%" PRId32 "\n", bac23);
		}
		printf("\n");
	}
}

int main()
{
	// the vector of bytes u have to work with
	// good luck :)
	void *arr = NULL;
	int len_arr = 0, len = 0;
	char *citesc = malloc(256 * sizeof(char));
	int cat_timp = 1;
	data_structure *structura = malloc(sizeof(data_structure));

	while (cat_timp == 1)
	{
		fgets(citesc, 256, stdin);
		citesc[strlen(citesc) - 1] = '\0';
		char *p = strtok(citesc, " \0\n");

		if (strcmp(p, "insert") == 0)
		{
			// insert
			len = 0;
			structura->header = malloc(sizeof(head));
			p = strtok(NULL, " \0\n");

			structura->header->type = p[0];
			p = strtok(NULL, " \0\n");

			len = len + (strlen(p) + 1) * sizeof(char);
			structura->data = malloc(len * sizeof(char));
			memcpy(structura->data, p, len);
			p = strtok(NULL, " \0\n");
			if (structura->header->type == '1')
			{
				len = len + 1;
				structura->data = realloc(structura->data, len * sizeof(char));
				int8_t bac1 = (int8_t)atoi(p);
				memmove(structura->data + len - 1, &bac1, sizeof(int8_t));
				p = strtok(NULL, " \0\n");

				len = len + 1;
				structura->data = realloc(structura->data, len * sizeof(char));
				int8_t bac2 = (int8_t)atoi(p);
				memmove(structura->data + len - 1, &bac2, sizeof(int8_t));
				p = strtok(NULL, " \0\n");
			}
			else if (structura->header->type == '2')
			{
				len = len + 2;
				structura->data = realloc(structura->data, len * sizeof(char));
				int16_t bac1 = (int16_t)atoi(p);
				memmove(structura->data + len - 2, &bac1, sizeof(int16_t));
				p = strtok(NULL, " \0\n");

				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac2 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac2, sizeof(int32_t));
				p = strtok(NULL, " \0\n");
			}
			else if (structura->header->type == '3')
			{
				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac1 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac1, sizeof(int32_t));
				p = strtok(NULL, " \0\n");

				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac2 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac2, sizeof(int32_t));
				p = strtok(NULL, " \0\n");
			}
			len = len + strlen(p) + 1;
			structura->data = realloc(structura->data, len * sizeof(char));
			memmove(structura->data + len - strlen(p) - 1, p, strlen(p) + 1);
			structura->header->len = len;

			add_last(&arr, &len_arr, structura);
			free(structura->header);
			free(structura->data);
		}
		else if (strcmp(p, "insert_at") == 0)
		{
			// insert_at
			int index;
			p = strtok(NULL, " \0\n");
			index = atoi(p);
			len = 0;
			structura->header = malloc(sizeof(head));
			p = strtok(NULL, " \0\n");

			structura->header->type = p[0];
			p = strtok(NULL, " \0\n");

			len = len + (strlen(p) + 1) * sizeof(char);
			structura->data = malloc(len * sizeof(char));
			memcpy(structura->data, p, len);
			p = strtok(NULL, " \0\n");

			if (structura->header->type == '1')
			{
				len = len + 1;
				structura->data = realloc(structura->data, len * sizeof(char));
				int8_t bac1 = (int8_t)atoi(p);
				memmove(structura->data + len - 1, &bac1, sizeof(int8_t));
				p = strtok(NULL, " \0\n");

				len = len + 1;
				structura->data = realloc(structura->data, len * sizeof(char));
				int8_t bac2 = (int8_t)atoi(p);
				memmove(structura->data + len - 1, &bac2, sizeof(int8_t));
				p = strtok(NULL, " \0\n");
			}
			else if (structura->header->type == '2')
			{
				len = len + 2;
				structura->data = realloc(structura->data, len * sizeof(char));
				int16_t bac1 = (int16_t)atoi(p);
				memmove(structura->data + len - 2, &bac1, sizeof(int16_t));
				p = strtok(NULL, " \0\n");

				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac2 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac2, sizeof(int32_t));
				p = strtok(NULL, " \0\n");
			}
			else if (structura->header->type == '3')
			{
				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac1 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac1, sizeof(int32_t));
				p = strtok(NULL, " \0\n");

				len = len + 4;
				structura->data = realloc(structura->data, len * sizeof(char));
				int32_t bac2 = (int32_t)atoi(p);
				memmove(structura->data + len - 4, &bac2, sizeof(int32_t));
				p = strtok(NULL, " \0\n");
			}
			len = len + strlen(p) + 1;
			structura->data = realloc(structura->data, len * sizeof(char));
			memmove(structura->data + len - strlen(p) - 1, p, strlen(p) + 1);
			structura->header->len = len;

			add_at(&arr, &len_arr, structura, index);
			free(structura->header);
			free(structura->data);
		}
		else if (strcmp(p, "delete_at") == 0)
		{
			// delete_at
			int index;
			p = strtok(NULL, " \0\n");
			index = atoi(p);
			delete_at(&arr, &len_arr, index);
		}
		else if (strcmp(p, "find") == 0)
		{
			// find
			int index;
			p = strtok(NULL, " \0\n");
			index = atoi(p);
			find(arr, len_arr, index);
		}
		else if (strcmp(p, "print") == 0)
		{
			// print
			print(arr, len_arr);
		}
		else if (strcmp(p, "exit") == 0)
		{
			// exit
			free(structura);
			free(arr);
			free(citesc);
			break;
		}
	}

	return 0;
}