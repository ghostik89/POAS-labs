// 5laba_tests_mod.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>

int separateToSentences(const char str[81], char sentences[20][81])
{
	//char sentences_local[20][81];
	int i, j = 0, k, sentenceCounter = 0;

	//copying sentences
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == '.' || str[i] == '?' || str[i] == '!')
		{
			strncpy(sentences[sentenceCounter], (str + j), i - j + 1);

			for (j = i; j < strlen(str); j++)
			{
				if (str[j] != '.' && str[j] != '?' && str[j] != '!')
				{
					i = j;
					sentenceCounter++;
					break;
				}
			}
			//index_start = i+1;
			//sentenceCounter++;
		}
	}
	if (sentenceCounter == 0)
	{
		//printf("%d",-1);
		//_getch();
		return 0;
	}

	//deleting blank chars
	for (i = 0; i < sentenceCounter; i++)
	{
		for (j = 0; j < strlen(sentences[i]); j++)
		{
			if (!isalnum(sentences[i][0]))
				for (k = 0; k < strlen(sentences[i]); k++)
				{
					if (k != strlen(sentences[i]))
						sentences[i][k] = sentences[i][k + 1];
				}
		}
	}

	//deleting end of the sentence
	/*for(k=0; k<sentenceCounter; k++)
	{
		for(i=0; i<strlen(sentences[k]); i++)
		{
			if((sentences[k][i]=='.' || sentences[k][i]=='!' || sentences[k][i]=='?') && i!=strlen(sentences[k])-1)
			{
				for(j=i+1; j<strlen(sentences[k]); j++)
				{
					sentences[k][j] = 0;
				}
			}
		}
	}*/

	return sentenceCounter;
}

int strToWords(const char str[81], char *words[40][2])
{
	int i, j, word_counter = 0;
	bool IsWord = false;

	for (i = 0; i < strlen(str); i++)
	{
		if (isalnum(str[i]) && IsWord == false)
		{
			words[word_counter][0] = (char*)&str[i];
			IsWord = true;

			for (j = i; j < strlen(str); j++)
			{
				if (!isalnum(str[j]))
				{
					words[word_counter][1] = (char*)&str[j - 1];
					word_counter++;
					IsWord = false;
					i = j;
					break;
				}
				else if ((isalnum(str[j]) && j == (strlen(str) - 1)))
				{
					words[word_counter][1] = (char*)&str[j];
					word_counter++;
					i = j;
					break;
					IsWord = false;
				}
			}
		}
	}
	return word_counter;
}

int wordMeaning(const char str[81], const char word[21], const char satellites[5][21], int range)
{
	int word_number = -1, satellites_counter = 0, M = 0, N = 0, i, j;
	char word_start, word_end, str_local[100], str_local_fin[81];
	char* satellite_number, *w_start, *w_end;

	char satellites_local[40][21];

	bool isWord = true;


	char* words[40][2];

	for (int i = 0; i < strlen(str_local); i++)
	{
		str_local[i] = 0;
		str_local_fin[i] = 0;
	}

	strcat(str_local, str);

	int word_counter = strToWords(str_local, words);

	//strncmp ne rabotaet
	for (i = 0; i < strlen(str_local); i++)
	{
		if (str[i] == word[0])
		{
			for (j = 0; j < strlen(word); j++)
			{
				if (str[i + j] != word[j])
					isWord = false;
			}

			if (isWord == true)
			{
				word_start = str[i];
				word_end = str[i + j - 1];
				break;
			}
		}
		isWord = true;
	}


	for (i = 0; i < word_counter; i++)
	{
		if (*(words[i][0]) == word_start && *(words[i][1]) == word_end)
		{
			word_number = i;
			break;
		}
	}

	for (i = 0; i < 5; i++)
	{
		if (strlen(satellites[i]) != 0)
			M++;
	}


	i = word_number - range;
	if (i < 0)
		i = 0;
	strncpy(str_local, str, strlen(str));

	if (word_counter < range * 2)
		range = range / 2;

	int ilocs = 0, iloce = 0;
	for (j = 0; j < strlen(str); j++)
	{
		char* local = (str_local + j);
		if ((local == words[(word_number + range)][1]) || (local == words[(word_number)][1] && word_number == (word_counter - 1)))
		{
			for (int k = 0; k < strlen(str); k++)
			{
				//char* local2 = (str_local+k);
				if ((char*)(str_local + k) == words[i][0] && i != 0)
					for (int l = k; l < strlen(str); l++)
						if (!isalnum(str[l]))
							if (str_local[l - 1] == *words[i][1] || (str_local[l] == *words[i][1] && l == strlen(str_local)))
								ilocs = k;
			}
			int lenCounter = 0;
			for (int k = ilocs; k < 81; k++)
			{
				if ((char*)(str_local + k) == words[word_number + range][1])
					iloce = lenCounter;
				lenCounter++;
			}
			strncpy(str_local_fin, (str + ilocs), ++iloce);
			//iloce++;
			for (int k = iloce; k < strlen(str_local_fin); k++)
			{
				str_local_fin[k] = 0;
			}
			break;
		}
	}

	if (word_number == -1)
		return -1;

	//bool isStarted = false, isFinished = false;

	for (j = 0; j < M; j++)
	{
		if (strstr(str_local_fin, satellites[j]) && (strcmp(word, satellites[j])))
		{
			char* local = strstr(str_local_fin, satellites[j]);
			for (int k = 0; k < strlen(str_local_fin); k++)
			{
				/*char* local2 = (str_local_fin+k);
				if(local2 == local && k!=0)
					if(!isalnum(str_local_fin[k-1]))
					{
						w_start = strstr(str_local, satellites[j]);
						w_end = strstr(str_local, satellites[j])+strlen(satellites[j])-1;
						N++;
					}*/
				if (k == local - str_local_fin)
				{
					if (k != 0)
					{
						if (!isalnum(str_local_fin[k - 1]))
						{
							int satLen = 0, wordLen = 0;
							for (int p = k; p < strlen(str); p++)
							{
								if (isalnum(str_local_fin[p]))
									wordLen++;
								else
									break;
							}
							for (int p = 0; p < strlen(satellites[j]); p++)
							{
								if (isalnum(satellites[j][p]))
									satLen++;
								else
									break;
							}
							if (satLen == wordLen)
							{
								w_start = strstr(str_local, satellites[j]);
								w_end = strstr(str_local, satellites[j]) + strlen(satellites[j]) - 1;
								N++;
							}
						}
					}
					else if (k == 0)
					{
						int satLen = 0, wordLen = 0;
						for (int p = k; p < strlen(str); p++)
						{
							if (isalnum(str_local_fin[p]))
								wordLen++;
							else
								break;
						}
						for (int p = 0; p < strlen(satellites[j]); p++)
						{
							if (isalnum(satellites[j][p]))
								satLen++;
							else
								break;
						}
						if (satLen == wordLen)
						{
							w_start = strstr(str_local, satellites[j]);
							w_end = strstr(str_local, satellites[j]) + strlen(satellites[j]) - 1;
							N++;
						}
					}
				}

			}
			/*w_start = strstr(str_local, satellites[j]);
			w_end = strstr(str_local, satellites[j])+strlen(satellites[j])-1;
			N++;*/
		}
	}

	if (N == 1)
	{
		for (int m = 0; m < word_counter; m++)
		{
			if (*(words[m][0]) == *(w_start) && *(words[m][1]) == *(w_end) && m != word_number)
			{
				return m;
			}
		}
		//return i;
	}
	else
		return -1;
}

int main()
{
	char str[100], word[30], sentences[20][81], satellites[6][21], *words[40][2];
	int i, j, range, M, sentCounter, answer;

	//word[0] = NULL;

	printf("str:");
	gets_s(str);
	if (strlen(str) > 81)
	{
		printf("Invalid data");
		//_getch();
		return 0;
	}

	printf("word: ");
	gets_s(word);
	if (strlen(word) > 21)
	{
		printf("Invalid data");
		return 0;
	}
	/*if(!isalnum(word[0]))
	{
		if(strlen(word)>22)
		{
			error_printf("Invalid data");
			return 0;
		}
		/*for(i=0; i<20; i++)
			word[i] = word[i+1];
		word[20] = 0;/
	}
	else if(strlen(word)>21)
	{
		error_printf("Invalid data");
			return 0;
	}*/

	printf("range:");
	scanf("%d", &range);
	if (range < 1 || range>5)
	{
		printf("Invalid data");
		//_getch();
		return 0;
	}

	printf("M:");
	scanf("%d", &M);
	if (M < 1 || M>5)
	{
		printf("Invalid data");
		//_getch();
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	printf("satellites:");
	for (i = 0; i < M; i++)
	{
		//gets(satellites[i]);
		scanf("%s", &satellites[i]);
	}

	for (i = 21; i > 0; i--)
	{
		word[i] = word[i - 1];
	}
	word[0] = 0;

	sentCounter = separateToSentences(str, sentences);

	for (i = 0; i < 21; i++)
	{
		word[i] = word[i + 1];
	}
	word[strlen(word) - 1] = 0;

	if (sentCounter == 0)
	{
		printf("%d", -1);
		
		return 0;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////

	for (i = 0; i < sentCounter; i++)
	{
		//wordCounter = strToWords(sentences[i], words);
		answer = wordMeaning(sentences[i], word, satellites, range);
		if (answer != -1)
		{
			printf("%d", answer);
			break;
		}
	}


	if (answer == -1)
		printf("%d", answer);

	return 0;
}
