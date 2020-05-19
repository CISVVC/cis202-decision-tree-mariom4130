/*
   File: main.cpp
   
   Description:This program will create a decision tree for an animal
   guessing game.
   
   Author:Mario Mendez Suarez
   
   Email:mariom4130@student.vvc.edu
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "binary_tree.h"

Binary_tree read(istream& in)
{
	std::string data;
	int level;
	std::getline(in, data);
	level = atoi(&data[0]);
	const char * data_str = data.c_str();
	while(!isalpha(*data_str) && data.length() > 2){
		data_str++;
	}
	data = data_str;
	if(level == -1) return Binary_tree();
	Binary_tree left = read(in);
	Binary_tree right = read(in);
	
	return Binary_tree(data, left, right);
}

void write(ostream& out, const Binary_tree& tree, int level)
{
//    if tree.empty()
//        output -1 + \n to out
//        return 
//    output level + ' ' + tree.data() + \n to out
//    call write (out, tree.left(), level + 1)
//    call write (out, tree.right(), level + 1)
	if(tree.empty()){
		out << "-1\n";
		return;
	}
	out << level << " " << tree.data() << "\n";
	write(out, tree.left(), level + 1);
	write(out, tree.right(), level + 1);
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry)
{
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos)
    {
        article =  "an";
    }
    return article;
}

int main(int argc,char **argv)
{
    Binary_tree root;  
    // How to navigate depending on the answer
    string file = "questions.dat";
    std::fstream in(file);
    root = read(in);
    Binary_tree question_tree = root;
    bool done = false;
    while (!done){
    	std::string response;
    	Binary_tree left = question_tree.left();
    	Binary_tree right = question_tree.right();
    	if(left.empty() && right.empty()){
    		do {
    			std::cout << "Is it a " << question_tree.data() << "? (y/n): ", std::cin >> response;
    		} while (response != "y" && response != "n");
    		if(response == "y"){
    			std::cout << "I guessed it!\n";
    		} else {
    			string question;
    			std::cout << "I give up. What is it?: ", std::cin >> response;
    			std::cout << "Please give me a question that is true for a " << response << " and false for a " << question_tree.data() << "\n";
    			do {
    				std::getline(std::cin, question);
    			} while(question.length() == 0);
    			question_tree.set(question, Binary_tree(response), Binary_tree(question_tree.data()));
    		}
    		do {
    			std::cout << "May I try Again? (y/n): ", std::cin >> response;
    		} while(response != "y" && response != "n");
    		if(response == "y"){
    			question_tree = root;
    		} else {
    			done = true;
    		}
    	} else {
    		do {
    			std::cout << question_tree.data() << "(y/n): ", std::cin >> response;
    		} while (response != "y" && response != "n");
    		if(response == "y"){
    			question_tree = left;
    		} else {
    			question_tree = right;
    		}
    	}
    }
    write(in, root, 0);
}
