/*
 * program2.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Ross Gideon
 */

#include <iostream>
#include <fstream>

using namespace std;
const int DEFAULT_SIZE=29;

#include "structs.h"	       //Other Definitions
#include "RelationalObjects.h" //Relational Set Objects(i.e. tuples)
#include "RelationalTables.h"   //Linked List Objects

void load_files(NCMTable*,SCLTable*,STTable*);

int main(){

	//Declare
	NCMTable* 	ncmTable = new NCMTable();	//These 3 tables store 
	SCLTable* 	sclTable = new SCLTable();	//ALL of the data 
	STTable*  	stTable  = new STTable();	//collectively and do not change
	

	NCMSLTable* 	ncmslTable;	//The following are temporary 
	NCMTable*   	tempNCM;	//working tables. They do change.
	NSTable*	tempNS;
	NSTTable*	tempNST;
	SCLTable*	tempSCL;
	CLTable*	tempCL;
	NCMLTable*	tempNCML;


	//Open/read files
	load_files(ncmTable,sclTable,stTable);
	ncmTable->printTable();
	sclTable->printTable();
	stTable->printTable();
	
	//Perform Queries

	//Query 1
	//Highest level types Jovani and William Know?
	
		tempNCM=ncmTable->Selection("Name","William");
		tempNCM->concat(ncmTable->Selection("Name","Jovani"));
		ncmslTable=tempNCM->Join(sclTable);
		ncmslTable=ncmslTable->Selection("Max","Level");
		tempNS=ncmslTable->Projection("Name","Spell");
		tempNST=tempNS->Join(stTable);
		

		cout<<endl<<endl;
		cout<<"Result: Highest level spell(s) and type(s) for Jovani and William"<<endl;
		tempNST->printTable();
	

	//Query 2
	//Names of char's that can learn "Wish"

		tempSCL=sclTable->Selection("Spell","Wish");
		tempCL=tempSCL->Projection("Class","Level");
		tempNCML=ncmTable->Join(tempCL);
		tempNCML=tempNCML->Selection("Max",">=","Level");
		
		cout<<endl<<endl;
		cout<<"Result: Names of the characters that can learn wish"<<endl;
		tempNCML->printTable();

	//Query 3
	//Highest level spells and types of all Clerics
	
		tempNCM=ncmTable->Selection("Class","Cleric");
		ncmslTable=tempNCM->Join(sclTable);
		ncmslTable=ncmslTable->Selection("Max","Level");
		tempNS=ncmslTable->Projection("Name","Spell");
		tempNST=tempNS->Join(stTable);
		
		cout<<endl<<endl;
		cout<<"Result: Highest level spell(s) and type(s) of all clerics"<<endl;
		tempNST->printTable();
			
	return 0;
}



void load_files(NCMTable* ncmTable, SCLTable* sclTable, STTable* stTable)
{	
	//Declare file streams
	ifstream inStream1,inStream2,inStream3;
	char x;
	int y;
	string word;	

	NCMEntry newNCM;
	SCLEntry newSCL;
	STEntry	newST;

	NCMAttributes attr1;
	SCLAttributes attr2;
	STAttributes  attr3;

	//Open Files
	inStream1.open("data1.txt");
	inStream2.open("data2.txt");
	inStream3.open("data3.txt");
	
	//Remove top of input files (junk)
	char	balls[256]; 
	inStream1.getline(balls,256);
	inStream2.getline(balls,256);
	inStream3.getline(balls,256);

		
	//NCM
	x=inStream1.get();
	while(inStream1)
	{	
		//Get Name
		while(x!=' ' && x!='\t' && x!='\n')
		{	
			word = word+x;
			x=inStream1.get();
		}
		attr1.name=word;
		word.clear();

		//Get WhiteSpace
		while(x==' ' || x=='\t' || x=='\n')
		{
			x=inStream1.get();
		}

		//Get Class	
		while(x!=' ' && x!='\t' && x!='\n')
		{	
			word=word+x;
			x=inStream1.get();
		}
		attr1.pClass=word;
		word.clear();
		
		//Get WhiteSpace and max
		while(x==' ' || x=='\t')
		{
			x=inStream1.get();
		}
		attr1.max=x - '0';

	
		newNCM.setData(attr1);
		ncmTable->insert(newNCM);
		x=inStream1.get();
	
		//Get new line
		while(x==' ' || x=='\t' || x=='\n')
		{
			x=inStream1.get();
		}			
	}	

	//SCL
	x=inStream2.get();
	while(inStream2)
	{	
		//Get Name
		while(x!=' ' && x!='\t' && x!='\n')
		{
			word = word+x;
			x=inStream2.get();
		}
		attr2.spell=word;
		word.clear();

		//Get whitespace
		while(x==' ' || x=='\t' || x=='\n')
		{
			x=inStream2.get();
		}


		//Get Class	
		while(x!=' ' &&  x!='\t' && x!='\n')
		{
			word=word+x;
			x=inStream2.get();
		}
		attr2.pClass=word;
		word.clear();

		//Get whitespace and level
		while(x==' ' || x=='\t' )
		{
			x=inStream2.get();
		}
		attr2.level=x - '0';	

		newSCL.setData(attr2);
		sclTable->insert(newSCL);

		x=inStream2.get();	
		x=inStream2.get();	

		//Get new line
		while(x==' ' || x=='\t' || x=='\n')
		{
			x=inStream2.get();
		}				
		
	}

	x=inStream3.get();
	while(inStream3)//Stop at eof
	{
		
		//Get Spell	
		while(x!=' ' && x!='\t')
		{
			word = word+x;
			x=inStream3.get();
		}
		attr3.spell=word;
		word.clear();

		//Get whitespace
		while(x==' ' || x=='\t')
		{
			x=inStream3.get();
		}

		//Get Type
		while(x!=' ' && x!='\t' && x!='\n')
		{	
			word=word+x;
			x=inStream3.get();
		}
		attr3.type=word;
		word.clear();

		newST.setData(attr3);
		stTable->insert(newST);	

		while(x==' ' || x=='\t' || x=='\n')
		{
			x=inStream3.get();
		}							
	}

	//Close files
	inStream1.close();
	inStream2.close();
	inStream3.close();

}