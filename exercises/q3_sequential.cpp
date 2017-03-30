#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define PRIMARY_INDEX_RATIO 10

using namespace std;

bool has_three_arguments(int argc);
void inform_number_of_elements_pattern();
void inform_search_value_pattern();

bool create_sorted_list(vector<long long> &sorted_elements, int quantity_of_elements);
bool get_sorted_list_from_user(vector<long long> &sorted_elements, int quantity_of_elements);
void create_automatic_sorted_list(vector<long long> &sorted_elements, int quantity_of_elements);

bool create_primary_index_table(vector<long long> &primary_index, vector<long long> &sorted_elements);
int sequential_search(vector<long long> &primary_index, vector<long long> &sorted_elements, long long search_value);

int main(int argc, char* argv[])
{
	vector<long long> sorted_elements;

	if(!has_three_arguments(argc))
	{
		exit(1);
	}

	int quantity_of_elements = atoi(argv[1]);

	if(!create_sorted_list(sorted_elements, quantity_of_elements))
	{
		exit(1);
	}

	long long search_value = atoll(argv[2]);

	if(search_value < 1 || search_value > quantity_of_elements)
	{
		inform_search_value_pattern();
		exit(1);
	}

	vector<long long> primary_index;

	if(create_primary_index_table(primary_index, sorted_elements))
	{
		int search_index = sequential_search(primary_index, sorted_elements, search_value);
		if(search_index != -1)
		{
			printf("ELEMENT FOUND - Position: %d; Value: %lld\n", search_index, search_value);
		}
		else
		{
			printf("ELEMENT NOT FOUND\n");
		}
	}

	return 0;
}

/*
 * Check if the program was called with two arguments
 * First argument: program call
 * Second argument: number of elements
 */
bool has_three_arguments(int argc)
{
	bool has_three_arguments = true;
	if(argc != 3)
	{
		printf("Input Expected: ./<program_name> <number_of_elements> <search_value>\n");
		inform_number_of_elements_pattern();
		inform_search_value_pattern();
		has_three_arguments = false;
	}
	return has_three_arguments;
}

/*
 * Inform how the program expect to receive the number of elements
 */
void inform_number_of_elements_pattern()
{
	printf("<number_of_elements> must be between 10 and 1000000\n");
	printf("If you want to set your own elements,\n");
	printf("inform <number_of_elements> as 0. Remember:\n");
	printf("a new element must be greater than 0 and lesser \n");
	printf("than the previous element\n");
}

/*
 * Inform how the program expect to receive the search value
 */
void inform_search_value_pattern()
{
	printf("<search_value> must be between 1 and <number_of_elements>\n");
}

/*
 * Create Sorted List
 * If the creation was unsuccessful, return false, otherwise true
 */
bool create_sorted_list(vector<long long> &sorted_elements, int quantity_of_elements)
{
	bool is_creation_successful = true;
	if(quantity_of_elements == 0) // User chose to insert elements
	{
		if(!get_sorted_list_from_user(sorted_elements, quantity_of_elements))
		{
			is_creation_successful = false;
		}
	}
	else if(quantity_of_elements >= 10) // User chose to program create elements
	{
		create_automatic_sorted_list(sorted_elements, quantity_of_elements);
	}
	else // Unexpected choice
	{
		inform_number_of_elements_pattern();
		is_creation_successful = false;
	}
	return is_creation_successful;
}

/*
 * Get Sorted List from User
 * A new element must be greater than 0
 * A new element must be lesser than the previous element
 * return false if no element created, otherwise true
 */
bool get_sorted_list_from_user(vector<long long> &sorted_elements, int quantity_of_elements)
{
	bool has_elements = true;

	long long previous_element = 1;
	long long new_element;
	while(scanf("%lld", &new_element) == 1 && new_element > 0)
	{
		if(previous_element <= new_element)
		{
			sorted_elements.push_back(new_element);
			previous_element = new_element;
		}
	}
	if(sorted_elements.size() == 0)
	{
		has_elements = false;
	} else
	{
		for(auto element : sorted_elements)
		{
			printf("[%lld]", element);
		}
		printf("\n");
	}
	return has_elements;
}

/*
 * Create Sorted List
 * L = l + (l)+1 + ... + (l)+n
 * l = 1
 */
 void create_automatic_sorted_list(vector<long long> &sorted_elements, int quantity_of_elements)
 {
	 long long new_element = 1;
	 for(int i = 0; i < quantity_of_elements; ++i, ++new_element)
	 {
	 	sorted_elements.push_back(new_element);
	 }
 }

/*
 *
 */
bool create_primary_index_table(vector<long long> &primary_index, vector<long long> &sorted_elements)
{
	bool need_primary_index_table = false;

	int primary_index_size = sorted_elements.size()/PRIMARY_INDEX_RATIO;

	if(primary_index_size != 0)
	{
		need_primary_index_table = true;
		if(sorted_elements.size()%PRIMARY_INDEX_RATIO != 0)
		{
			++primary_index_size;
		}

		for(int i = 0; i < primary_index_size-1; ++i)
		{
			primary_index.push_back(sorted_elements[(i*PRIMARY_INDEX_RATIO)-1]);
		}
		primary_index.push_back(sorted_elements[sorted_elements.size()-1]);
	}

	return need_primary_index_table;
}

/*
 *
 */
int sequential_search(vector<long long> &primary_index, vector<long long> &sorted_elements, long long search_value)
{
	int size_primary = primary_index.size();
	int aux,auxSorted;
	for(aux=0; aux< size_primary; aux++){
		if(!(primary_index[aux] < search_value)){
			break;
		}
	}
	aux = aux*PRIMARY_INDEX_RATIO;
	for(auxSorted =0; auxSorted < 10; aux++){
		if(sorted_elements[aux] == search_value)
		{
			return aux;
		}
		if(sorted_elements[aux] > search_value)
			return -1;
	}
	return -1;
}