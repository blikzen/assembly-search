#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define o std::cout
#define s std::string 
#define v std::vector
#define ss search_space
#define i std::ifstream

//object to hold annotation specific consensus sequence
struct search_space{
	s annotation, space;
};

v<ss> load_consensus(auto *file){
	//read line delimited text file holding consensus sequence
	//push to vector of search space objects
	//each new object defined by > character indicating a chr or patch annotation.
	int annotation_count = -1;
	s line;
	v<ss> push;
	ss holder;
	i input(file);
	while (getline(input,line)){
		if(line.at(0) == '>'){ 
			//if hit annotation line, push empty struct, and assign annotation to object
			annotation_count++;
			push.push_back(holder);
			push.at(annotation_count).annotation = line;
		}else 
			//else concatenate line to string holding consensus, overflow at ~4.2B char
			push.at(annotation_count).space += line;
	}
	input.close();
	return(push);
}

v<s> load_query(auto *file){
	//read line delimited file with search queries
	//assign vector of strings
	s line;
	v<s> push;
	i input(file);
	while (getline(input,line)){
		push.push_back(line);
	}
	input.close();
	return(push);
}

void print_hits(auto &assembly, auto &query){
	//greedy search 
	//iterate through each ss object for each query string 
	for(query_token : query){
		for(assembly_token : assembly){
			//find first instance of query
			std::size_t found = assembly_token.space.find(query_token);
			if(found != s ::npos){
				//hits to stout
				o << assembly_token.annotation << "\t" << query_token << "\t" << found << "\n"; 
				bool hit = 1;
				while (hit){
					//find additional instances of query in ss consensus object offset by 1 
					found = assembly_token.space.find(query_token,found+1);
					if(found != s ::npos)
						//hits to stout
						o << assembly_token.annotation << "\t" << query_token << "\t" << found << "\n"; 
					else
						hit = 0;
				}
			}
		}
	}			
}

int main (int argc, char* argv[]) { 
	//usage: $ assembly-search dictionary.txt consensus-assembly.txt > output.txt 
	v<ss> assembly = load_consensus(argv[2]);
	v<s> query = load_query(argv[1]);
	print_hits(assembly, query);
}

