
int H_Slots = 200;

vector<List_ZHG> HInit()
{            
    
    vector<List_ZHG> H(H_Slots);
        
    return H;
}


void HBirthAdd ( vector<List_ZHG> & H , int d , long double BirthProb, int BirthState , vector<State> &  Microstates_X )
{
	//H[ NC ].pb = BirthProb;
	//H[ NC ].xb = BirthState;

    State & x_i = Microstates_X[ BirthState ];

    Zero_Homology_Group *h_i =  new Zero_Homology_Group();
    h_i->pb = BirthProb;
    h_i->xb = BirthState;
    
    int slot = HashFunction( H_Slots , x_i.vec , d );
    
    if ( H[slot].head == NULL )
    { 
		
        H[slot].head = h_i;
        H[slot].tail = h_i;
        h_i->NextH = NULL;
        h_i->PrevH = NULL;
        
    }
    else
    { 
        H[slot].tail->NextH = h_i;
        h_i->PrevH = H[slot].tail;
        h_i->NextH = NULL;
        H[slot].tail = h_i;
        
     }

}

void HDeathAdd ( vector<List_ZHG> & H, int d , int BirthState , long double DeathProb, int DeathState , vector<State> &  Microstates_X)
{

    State & x_i = Microstates_X[ BirthState ];
    
    int slot = HashFunction( H_Slots , x_i.vec , d );
    


    if ( H[slot].head == NULL )
    { 
		cout<<"Error: Cannot add DeathState without BirthState";
    }
    else
    { 
        Zero_Homology_Group *h_i =  H[slot].head;
 

        while ( h_i != NULL )
        {
            if ( h_i->xb == BirthState  )
            {
                h_i->pd = DeathProb;
                h_i->xd = DeathState;
                break;
            }
            h_i = h_i->NextH;

            cout<<"in HDeathAdd"<<endl;
        }
        
     }

}
