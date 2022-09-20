
void PeakAssign(int i, int j , vector<State> &  Microstates_X )
{
    
    State & x_i = Microstates_X[i];
    
    x_i.pk = Microstates_X[j].sorted_index;
    
}

int PeakFind( int i , const vector<State> &  Microstates_X )
{
    State x = Microstates_X[i];
    
    int peakId = -1;
    
    while ( x.pk != peakId )
	{
        peakId = x.pk;
        
        x = Microstates_X[ peakId ];
    }
    
    return peakId;
}
