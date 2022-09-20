#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <math.h>
#include <vector>
#include <iomanip>

#include "hash.h"
#include "classes.h"
#include "boundary.h"
#include "peak_detection.h"
#include "homology_group.h"
#include "components_neighboring_microstates.h"
#include "statespece_hash.h"
#include "neighbor_list.h"
#include "compute_H0_group.h"
#include "file_reader.h"

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v) {

  // initialize original index locations
  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values 
  stable_sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1].prob > v[i2].prob;});

  return idx;
}

bool compare_States( State  S1 , State S2  )
{
    return ( S1.prob   >  S2.prob  );
}

bool compare_ZHG( Zero_Homology_Group  G1 , Zero_Homology_Group   G2  )
{
    return ( (G1.pb - G1.pd)  > (G2.pb - G2.pd)  );
}



void show_usage(string name)
{
    std::cerr << "Usage: " << name << " <option(s)>\n"
              << "Options:\n"
              << "\t-h,\tShow this help message\n"
              << "\t-sp\tInput file path containing states and probabilities (last column)\n"
              << "\t-ps\tInput file path containing probabilities (first column) and states\n"
              << "\t-s\tInput file path containing states\n"
              << "\t-p\tInput file path containing probabilities\n"
              << "\t-o\tOutput file path, default is out.txt\n"
              << "\t-sort\tyes/no default is yes\n"
              << endl;
}



string prd(const double x, const int decDigits) {
    stringstream ss;
    ss << fixed;
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}

string prd(const double x, const int decDigits, const int width) {
    stringstream ss;
    ss << fixed << right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}


string center(const string s, const int w) {
    stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}



int main(int argc, char* argv[])
{
    if (argc==1)
    {
        show_usage(argv[0]);
        return 0;
    }

    vector<State> Microstates_X;
    vector<State> Microstates_X_sorted;

    bool Microstates_X_Is_Initialized = false ;
    string sp_file="";
    string ps_file="";
    string state_file="";
    string prob_file="";
    string output_file="out.txt";
    string sort="yes";
    string out_sort="";

    for (int i = 1; i < argc; i+=2 ) 
    {
        string arg = argv[i];

        if (  (arg == "-h") || (arg == "-H") ) 
        {
            show_usage(argv[0]);
            return 0;
        } 
        else if (  (arg == "-sp") || (arg == "-SP") )
        {
            
        
            ifstream sp_ifile;
            sp_ifile.open( argv[i+1] );

            if(sp_ifile) 
            {
                //cout<<"File exists";
                read_SP_File(  Microstates_X  ,  sp_ifile );
                sp_ifile.close();
                Microstates_X_Is_Initialized = true;

            } 
            else 
            {
                cout<< "'" << argv[i+1] <<"' file doesn't exist";
                return 0;
            }

            //cout<<"Reading sp file: "<< argv[i+1] << " ..." <<endl;
        }

        else if (  (arg == "-ps") || (arg == "-PS") )
        {
            ifstream ps_ifile;
            ps_ifile.open( argv[i+1] );

            if(ps_ifile) 
            {
                //cout<<"File exists";

                read_PS_File(  Microstates_X  ,  ps_ifile );

                ps_ifile.close();
                Microstates_X_Is_Initialized = true;
            } 
            else 
            {
                cout<< "'" << argv[i+1] <<"' file doesn't exist";
                return 0;
            }
            
            //cout<<"Reading ps file: "<< argv[i+1] << " ..." <<endl;

        }

        else if (  (arg == "-s") || (arg == "-S") )
        {
            ifstream s_ifile;
            s_ifile.open( argv[i+1] );

            if(s_ifile) 
            {
                //cout<<"File exists";
                s_ifile.close();

                state_file= argv[i+1] ;
    
            } 
            else 
            {
                cout<< "'" << argv[i+1] <<"' file doesn't exist";
                return 0;
            }

            //cout<<"Reading state file: "<< argv[i+1] << " ..." <<endl;
        }

        else if (  (arg == "-p") || (arg == "-P") )
        {
            
            ifstream p_ifile;
            p_ifile.open( argv[i+1] );

            if(p_ifile) 
            {
                //cout<<"File exists";
                p_ifile.close();
                prob_file= argv[i+1] ;
            } 
            else 
            {
                cout<< "'" << argv[i+1] <<"' file doesn't exist";
                return 0;
            }

            //cout<<"Reading probability file: "<< argv[i+1] << " ..." <<endl;
        }

        else if (  (arg == "-o") || (arg == "-O") )
        {
            ofstream ofile;
            ofile.open( argv[i+1]  );

            if(ofile) 
            {
                //cout<<"File exists";
                ofile.close();
                output_file = argv[i+1];
		out_sort= output_file.substr( 0 , output_file.length()-3  )+"negmap";

            } 
            else 
            {
                cout<< "'" << argv[i+1] <<"' output file name or path is invalid\n";
                cout<<"Using default name for output file 'out.txt'\n";
            }

            //cout<<"Write output in file: "<< argv[i+1] << " ..." <<endl;
        }
        else if (  (arg == "-sort") || (arg == "-SORT") )
        {
            //cout<<"Sort data before running algorithm?: "<< argv[i+1] <<endl;
            if ( ( string(argv[i+1]) =="no") || ( string(argv[i+1]) =="NO") || ( string(argv[i+1]) =="No") ||
                 ( string(argv[i+1])=="yes") || ( string(argv[i+1])=="YES") || ( string(argv[i+1])=="Yes") )
            {
                
                sort = argv[i+1];

            }
            else
            {
                cout<< "'" << argv[i+1] <<"' invalid parameter for sorting\n";
                cout<<"Using default parameter for sorting 'yes'\n";
            }
        }
        else
        {
            cout<< "Invalid command line option: '"<<arg<<"' , see uage.\n";
            show_usage(argv[0]);
        }

        
    }




    if ( Microstates_X_Is_Initialized == false )
    {
        if (state_file=="") 
        {
            cout<<"Missing: Please provide the name of the file containing States\n";
            return 0;
        }
        
        if ( prob_file==""  )
        {
             cout<<"Missing: Please provide the name of the file containing probabilities\n";
             return 0;
        }


        ifstream p_ifile;
        p_ifile.open( prob_file );

        ifstream s_ifile;
        s_ifile.open( state_file );

        if ( read_S_P_File(  Microstates_X ,  s_ifile  ,  p_ifile ) )
        {
            cout<<"Error:The number of states and number of probabilities are not same.\n";
            
            s_ifile.close(); 
            p_ifile.close();

            return 0;
        }

        s_ifile.close(); 
        p_ifile.close();
            
    }

	
    if ( sort == "yes" )
    {
       stable_sort( Microstates_X.begin(), Microstates_X.end() , compare_States );
       cout<<"*******Data is sorted*********\n";
    }
	
	vector<List_ZHG> H = Compute_H0_group( Microstates_X  );
	
	cout<<"Homolgy is computed\n";

    ofstream  ofile2 ;
    ofile2.open(  out_sort  );
    ofile2 << center("Prob", 18)  << " | "
           << center("State Index", 10)  << " | "
           << center("Pk",10)     << "  | "
           << center("Vector",10) << "\n" 
           << string( 65 , '-') << "\n";

    for (  int i=0 ; i < int( Microstates_X.size() ) ; i++  )
    {   State Si = Microstates_X[i];
        ofile2  << prd( Si.prob , 16 , 10) << " | "
                << prd( Si.sorted_index , 0 , 6) << "      | "
                << prd( Si.pk , 0 , 6) << "      | "
                << "[ ";

        for ( auto xi : Si.vec  )
        {   
            ofile2<<  prd( xi , 0 , 5 )  << " ";
        }

        ofile2<< "]" << "\n";
    }
    ofile2.close();




    ofstream ofile  ;
    ofile.open( output_file  );

    ofile << center("Birth Probability",10) << "  | "
		  << center("Death Probability",10) << "  | "
		  << center("Birth State Index",10) << "  | "
          << center("Death State Index",10) << "\n"
          << string( 80 , '-') << "\n";


    vector< Zero_Homology_Group  > H_new;
	for( int i=0 ; i < int( H.size() ) ; i++ )
	{   
        if ( H[i].head==NULL )
        {
            continue;
        }

        Zero_Homology_Group * h_i  = H[i].head;

        while ( h_i != NULL )
        {
            H_new.push_back( *h_i );
            h_i = h_i->NextH;
        }
    
	}


    stable_sort( H_new.begin(), H_new.end() , compare_ZHG );
    for (  auto h_i :  H_new ) 
    {
        ofile << prd( h_i.pb , (h_i.pb < 0 ) ? 15 : 16 , 18) << " | "
			  << prd( h_i.pd , (h_i.pd < 0 ) ? 15 : 16 , 18) << " | "
			  << prd( h_i.xb , 0 , 10)  << "         | "
              << prd( h_i.xd , 0 , 10)  << "\n";
    }
    ofile.close();


    cout<<"Please check '"<<output_file<<"' file to see computed Homology Groups.\n"; 
    cout<<"Please also check 'Prob_Index_Pk_Vec.txt' file to see \nProbabilities, State Index, Peak Index, and State Vector"<<endl;   
}


