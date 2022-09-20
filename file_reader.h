void read_SP_File( vector<State> & Microstates_X  , ifstream & inFile )
{
    //ifstream inFile;                    // build a read-Stream
	//inFile.open("./data.csv");


	int index=0;
	for(string line; getline(inFile, line); )   //read stream line by line
	{
		if(index==0)
		{	index++;
			continue;
		}

		istringstream in(line);
		
		vector<int> vec;
		long double xi_val;
		char c;
		while( in >> xi_val  )
		{
			//cout<<xi_val<<"\t";
			vec.push_back(xi_val);
		}
		//cout<<endl;
		vec.pop_back();
		Microstates_X.push_back(  State( vec  , int( vec.size() ) , xi_val )  );
		index++;
	}
}

void read_PS_File( vector<State> & Microstates_X  , ifstream & inFile )
{
    //ifstream inFile;                    // build a read-Stream
	//inFile.open("./data.csv");


	int index=0;
	for(string line; getline(inFile, line); )   //read stream line by line
	{
		if(index==0)
		{	index++;
			continue;
		}
			
		istringstream in(line);
		
		
		vector<int> vec;
		long double xi_val;
        long double prob;
		char c;

        if ( in >> prob  )
        {
            //Do nothing is already read the value from file
            //cout<<prob<<"\t";
        }

		while( in >> xi_val  )
		{
			//cout<<xi_val<<"\t";
			vec.push_back(xi_val);
		}
		//cout<<endl;

		Microstates_X.push_back(  State( vec  , int( vec.size() ) , prob )  );
		index++;
	}


}


int read_S_P_File( vector<State> & Microstates_X  , ifstream & s_ifile , ifstream & p_ifile  )
{
    //ifstream inFile;                    // build a read-Stream
	//inFile.open("./data.csv");
    string s_line;
    string p_line;
    vector< vector<int> > States_vec;
    vector<long double> Prob_vec;

    getline(s_ifile, s_line); // ignoring first line
    getline(p_ifile, p_line); // ignoring first line

	for( ; getline(s_ifile, s_line); )   //read stream line by line
	{
	
			
		istringstream in( s_line );
		
		vector<int> vec;
		double xi_val;

		while( in >> xi_val  )
		{
			//cout<<xi_val<<"\t";
			vec.push_back(xi_val);

		}

		//cout<<endl;

		//cout<<xi_val<<endl;
        //vec.push_back(xi_val);

        States_vec.push_back( vec );

	}

    //cout<<endl;
    
    long double prob;

    while( p_ifile >> prob  )
    {
        //cout<<prob<<"\n";
        Prob_vec.push_back(prob);
        
    }
	
   if (  Prob_vec.size() == States_vec.size()  )
    {
		
        for ( int i=0 ; i < int( Prob_vec.size() ) ; i++ )
        {
            
		Microstates_X.push_back(  State( States_vec[i]  , int( States_vec[i].size() ) , Prob_vec[i] )  );
        	//cout<<"D="<< int( States_vec[i].size() ) <<"\t["<< States_vec[i][0] << "\t" << States_vec[i][1] << "]\t"<<Prob_vec[i]<<endl;
            
        }

	
        return 0; //file is successfully read;
    }
    else
    {
        // Error:The number of states and number of probabilities are not same.
        return 1;
    }



}
