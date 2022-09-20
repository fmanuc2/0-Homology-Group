

using namespace std;


int Base_Num = 13;

int  HashFunction(int total_slots , const vector<int> & x , int d )
{
	// UNIT_MAX = 4294967295;
	
	long unsigned int num = 0;

	for( int j =0 ; j < d ; j++ )
	{	
		num +=   x[j]*(j+1) + x[j]*Base_Num + j + pow( x[j] % Base_Num  , Base_Num );
        num = num % total_slots;
	}

	return int(num % total_slots);
}
