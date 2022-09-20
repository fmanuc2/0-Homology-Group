=> Introduction:
	
	This software computes persistent homology, given states and their probabilities.
	
=> Requirement:
	
	To use this software, you must have installed the latest version of C++ package on your machine.


=> Execute the main code:
	
	To execute the code, you need to have all files along with 'main.cpp' and latest version of C++. Then you can execute the main.cpp file with the following command:
	
	
	g++ main.cpp -o main

	
=> Input Data Representation:

	Important note:
		First row of input data is considered the header and our software ignores it.
		If your data does not have headers please provide headers otherwise first row will 
		be skipped.
	
	Input data can be in any format including txt, csv, and tsv and our package supports different types of input data representations like, 
	1. Single file containing states and probabilities
	2. Seperate files for states and probabilities.
	
	See Usage instructions for more details.
	
 
=> Usage:
 	 
 	Use the following command to run the executable file (main) on linux terminal.
 	If it shows a permission error, then change the permissions first and then execute it.
 	
 	To change permission run : chmod 777  main
	
	./main
	
	The above command will print following message, according to your data 
	make your own command to compute homology groups. 
	
	Usage: ./main <option(s)>
	Options:
		-h,	Show this help message
		-sp	Input file path containing states and probabilities (last column)
		-ps	Input file path containing probabilities (first column) and states
		-s	Input file path containing states
		-p	Input file path containing probabilities
		-o	Output file path. if not specified, default is out.txt
		-sort	yes/no default is yes
		

	Command Example:
		./main -s ./data/states.txt -p ./data/probs.txt  -o ./data/out.txt -sort yes
	
	
	If -sore yes: then a sorted probs, states index and vector, and their cluster index (PK) are outputed with the name of out.negmap (same name as output file with the format of negmap))
