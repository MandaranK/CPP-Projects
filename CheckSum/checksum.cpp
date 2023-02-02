#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif
unsigned int add_checksum( unsigned int n );
void add_checksum( unsigned int array[], std::size_t capacity );
bool verify_checksum( unsigned int n );
unsigned int remove_checksum( unsigned int n );
void remove_checksum( unsigned int array[], std::size_t capacity );

unsigned int add_checksum( unsigned int n ) {
	int len{0};	// finding length of n
	unsigned int num = n; // variable with value n
	while (num > 0) {
		num /= 10;
		++len;
	}

	if (len > 8) {
		return UINT_MAX;	// return max unsigned int if larger than 8 digits
	}

	int arr_n[len];
	unsigned int num_2 = n;	// second variable with value n
	for (int i{len-1}; i >= 0; --i) {	// storing n digits into array
		arr_n[i] = num_2%10;
		num_2 /= 10;
	}

	for (int i{len-1}; i >= 0; i -= 2) {	// multiple every other digit by 2
		arr_n[i] *= 2;
		if(arr_n[i] > 9) {
			arr_n[i] = ((arr_n[i] - arr_n[i]%10) / 10) + (arr_n[i]%10);	// if multiplication > 9, add digits
		}
	}

	int sum{0};
	for (int i{0}; i < len; ++i) {	// sum up all digits
		sum += arr_n[i];
	}

	sum *= 9;	// sum times 9

	int checksumdigit{sum%10};

	/*int checksum{0};
	for (int i{0}; i < len; ++i)
	{
		int j = arr_n[i];
		if (j = 0) {
			checksum *= 10;
		} else {
			while (j > 0) {
				checksum *= 10;
				j /= 10;
			}
			checksum += arr_n[i];
		}
	}*/

	n *= 10;
	n += checksumdigit;	// array converted to integer

	return n;
}

void add_checksum( unsigned int array[], std::size_t capacity ) {
	for (int i{0}; i < capacity; ++i) {		// modifying each index of array and implementing add_checksum
		array[i] = add_checksum(array[i]);
	}
}

bool verify_checksum( unsigned int n ) {
	if (0 < n && n <= 999999999) {	// if greater than zero and less than 10 digit number
		if (n == add_checksum(((n - n%10)/10))) {	// checking if checksum is correct
			return true;
		}
	}
	return false;
}

unsigned int remove_checksum( unsigned int n ) {
	if (0 < n && n <= 999999999) {
		if (add_checksum(((n - n%10)/10)) == n) {
			return ((n - n%10)/10);
		}
	}
	return UINT_MAX;
}

void remove_checksum( unsigned int array[], std::size_t capacity ) {
	for (int i{0}; i < capacity; ++i) {		// modifying each index of array and implementing remove_checksum
		array[i] = remove_checksum(array[i]);
	}
}


#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{21352411};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif