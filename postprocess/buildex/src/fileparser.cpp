//file parser and other file operations are grouped in this file
#include "fileparser.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "canonicalize.h"

#define MAX_STRING_LENGTH 100

void print_cinstr(cinstr_t * instr);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
 
cinstr_t * get_next_from_ascii_file(ifstream &file){
 
	cinstr_t * instr;
	char string_ins[MAX_STRING_LENGTH];

	//we need to parse the file here - forward parsing and backward traversal
	file.getline(string_ins,MAX_STRING_LENGTH);
	
	string string_cpp(string_ins);

	cout << string_cpp << endl;

	instr = NULL;

	if(string_cpp.size() > 0){

		instr = new cinstr_t;
	
		vector<string> tokens;
		tokens = split(string_cpp, ',');
		
		//now parse the string  - this is specific to the string being outputted
		instr->opcode = atoi(tokens[0].c_str());

		//get the number of destinations
		instr->num_dsts = atoi(tokens[1].c_str());

		int index_op=0;
		int i;
		for(i=2; i< 3*instr->num_dsts + 2; i+=3){
			instr->dsts[index_op].type = atoi(tokens[i].c_str());

			instr->dsts[index_op].width = atoi(tokens[i+1].c_str());

			if(instr->dsts[index_op].type == IMM_FLOAT_TYPE){
				instr->dsts[index_op++].float_value = atof(tokens[i+2].c_str());

			}
			else{
				instr->dsts[index_op++].value = atoi(tokens[i+2].c_str());

			}
		}
		
		//get the number of sources
		instr->num_srcs = atoi(tokens[i++].c_str());

		index_op = 0;
		int current = i;
		
		for(; i< 3*instr->num_srcs + current; i+=3){
			instr->srcs[index_op].type = atoi(tokens[i].c_str());
			instr->srcs[index_op].width = atoi(tokens[i+1].c_str());
			if(instr->srcs[index_op].type == IMM_FLOAT_TYPE){
				instr->srcs[index_op++].float_value = atof(tokens[i+2].c_str());
			}
			else{
				instr->srcs[index_op++].value = atoi(tokens[i+2].c_str());
			}
		}
		
		instr->eflags = atoi(tokens[i].c_str());
	
	}
	
	return instr;
 
 }
 
void go_forward_line(ifstream &file){
	
	char array[MAX_STRING_LENGTH];
	file.getline(array,MAX_STRING_LENGTH);
	
 }
 
bool go_backward_line(ifstream &file){
 
	int value = '\0';
	unsigned int pos;

	file.seekg(-1,ios::cur);
	pos = file.tellg();

	
	while((value != '\n') && (pos != 0)){
		file.seekg(-1,ios::cur);
		value = file.peek();
		pos = file.tellg();
	}
	
	pos = file.tellg();

	if(pos == 0){
		return false;
	}
	
	
	file.seekg(1,ios::cur);  

	
	return true;
 
 }
 
void reverse_file(ofstream &out, ifstream &in){
	
	char value[MAX_STRING_LENGTH];
	in.seekg(-1,ios::end);
	in.clear();

	bool check = true;
	while(check){
		go_backward_line(in);
		in.getline(value,MAX_STRING_LENGTH);
		out << value << endl;
		//cout << value << endl;
		check = go_backward_line(in);
	}
	
 }
 
cinstr_t * get_next_from_bin_file(ifstream &file){
	return NULL;
 }

void print_cinstr(cinstr_t * instr){
	 cout << instr->opcode << ",";
	 cout << instr->num_dsts << ",";
	 for(int i=0; i<instr->num_dsts; i++){
		 cout << instr->dsts[i].type << ",";
		 cout << instr->dsts[i].width << ",";
		 cout << instr->dsts[i].value << ",";
	 }

	 cout << instr->num_srcs << ",";
	 for(int i=0; i<instr->num_srcs; i++){
		 cout << instr->srcs[i].type << ",";
		 cout << instr->srcs[i].width << ",";
		 cout << instr->srcs[i].value << ",";
	 }
	 cout << instr->eflags << endl;
 }