/*
 * RelationalTables.h
 *
 *  Created on: Oct 31, 2017
 *      Author: Ross
 */

#ifndef RELATIONALTABLES_H_
#define RELATIONALTABLES_H_


//Class definitions for the various tables required to model the DB
//Different combinations of attributes represent resultant
//tables from join and projection operations. All tables
//share the same template, implemented as a hash table(linked list)
//of their specified tuples(based on attributes)
//Table objects are only capable of Relational Operations necessary
//for fulfillment and optimization of the given queries.

class NSTTable{
	private:
		NSTEntry **table;
		int 	   tableSize;
	public:
		NSTTable();
		int hashFunc(string);
		void insert(NSTEntry);
		void printTable();
		/*Selection();
		Join();				Not used
		Projection();	*/
};

NSTTable::NSTTable(){
		int i;
		table= new NSTEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int NSTTable::hashFunc(string name){
	int key = 0;
	int length=name.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)name[i]);
	}

	return key % tableSize;
}



void NSTTable::insert(NSTEntry newEntry){
	int index;
	NSTEntry* walker;
	NSTEntry* prev;

	NSTAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.name);
	if(table[index]!=NULL)
	{	prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new NSTEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new NSTEntry();
		table[index]->setData(entryData);
	}

	return ;
}

void NSTTable::printTable(){

	int i;
	NSTEntry* walker;

	
	cout<<endl<<endl;
	cout<<"***************************"<<endl;
	cout<<"***Name-Spell-Type Table***"<<endl;
	cout<<"***************************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().name<<"\t";
			cout<<walker->getData().spell<<"\t";
			cout<<walker->getData().type<<endl;
			walker=walker->getNext();
		}

	}
	return ;
}

class STTable{
	private:
		STEntry **table;
		int 	   tableSize;
	public:
		STTable();//Hash Map
		int hashFunc(string);
		void insert(STEntry);
		STEntry* getEntry(int index){return table[index];}
		void printTable();
		//Selection();
		//Join();
		//Projection();
};

STTable::STTable(){
		int i;
		table= new STEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int STTable::hashFunc(string spell){
	int key = 0;
	int length=spell.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)spell[i]);
	}

	return key % tableSize;
}


void STTable::insert(STEntry newEntry){
	int	 	index;
	STEntry* walker;
	STEntry* prev;

	STAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.spell);
	if(table[index]!=NULL)
	{	prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new STEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new STEntry();
		table[index]->setData(entryData);
	}

	return ;
}

void STTable::printTable(){

	int i;
	STEntry* walker;

	
	cout<<endl<<endl;
	cout<<"**********************"<<endl;
	cout<<"***Spell-Type Table***"<<endl;
	cout<<"**********************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().spell<<"\t";
			cout<<walker->getData().type<<endl;
			walker=walker->getNext();
		}

	}
	return ;
}


class NSTable{
	private:
		NSEntry **table;
		int 	   tableSize;
	public:
		NSTable();
		int hashFunc(string);
		void insert(NSEntry);
		void printTable();
		//Selection();Not Used
		NSTTable* Join(STTable*);//Answers query 1 and 3
		//Projection();Not Used
};

NSTable::NSTable(){
		int i;
		table= new NSEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int NSTable::hashFunc(string name){
	int key = 0;
	int length=name.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)name[i]);
	}

	return key % tableSize;
}


void NSTable::insert(NSEntry newEntry){
	int index;
	NSEntry* walker;
	NSEntry* prev;

	NSAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.name);
	if(table[index]!=NULL)
	{	prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new NSEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new NSEntry();
		table[index]->setData(entryData);
	}

	return ;
}

NSTTable* NSTable::Join(STTable* table2){

	int i;
	int j;
	NSTTable *resultTable = new NSTTable();
	NSEntry* walker1;
	STEntry* walker2;
	NSTEntry newData;
	NSTAttributes newAttributes;

	for(i=0;i<tableSize;i++)//Every bucket in table 1(this)
	{
		walker1=table[i];
		while(walker1!=NULL)//There is something in the bucket
		{
			for(j=0;j<DEFAULT_SIZE;j++)//every index in table 2
			{
				walker2=table2->getEntry(j);
				while(walker2!=NULL)//There is something in the bucket
				{
					if(walker2->getData().spell == walker1->getData().spell)
					{
						newAttributes.name=walker1->getData().name;
						newAttributes.spell=walker1->getData().spell;
						newAttributes.type=walker2->getData().type;
						newData.setData(newAttributes);
						resultTable->insert(newData);
					}
					walker2=walker2->getNext();
				}
			}
			walker1=walker1->getNext();
		}
	}

	return resultTable;
}


void NSTable::printTable(){

	int i;
	NSEntry* walker;

	
	cout<<endl<<endl;
	cout<<"**********************"<<endl;
	cout<<"***Name-Spell Table***"<<endl;
	cout<<"**********************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().name<<"\t";
			cout<<walker->getData().spell<<endl;
			walker=walker->getNext();

		}

	}
	return ;
}


class NCMSLTable{
	private:
		NCMSLEntry **table;
		int 	   tableSize;
	public:
		NCMSLTable();
		int hashFunc(string);
		void insert(NCMSLEntry);
		NCMSLTable* Selection(const char*,const char*);
		//Join(); Not used
		NSTable* Projection(const char*,const char*);
		void printTable(void);
};

NCMSLTable::NCMSLTable(){
		int i;
		table= new NCMSLEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int NCMSLTable::hashFunc(string name){
	int key = 0;
	int length=name.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)name[i]);
	}

	return key % tableSize;
}


void NCMSLTable::insert(NCMSLEntry newEntry){
	int index;
	NCMSLEntry* walker;
	NCMSLEntry* prev;

	NCMSLAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.name);
	if(table[index]!=NULL)
	{	prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new NCMSLEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new NCMSLEntry();
		table[index]->setData(entryData);
	}

	return ;
}

NCMSLTable* NCMSLTable::Selection(const char* attr1,const char* attr2){


	NCMSLTable* resultTable = new NCMSLTable();
	NCMSLEntry* walker = NULL;
	int i=0;

	if(attr1=="Max" && attr2=="Level")
	{
		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{
				if(walker->getData().max == walker->getData().level)
						resultTable->insert(*walker);
				walker=walker->getNext();
			}
		}
	}

	return resultTable;

}

NSTable* NCMSLTable::Projection(const char* attr1, const char* attr2){

	NSTable			*resultTable= new NSTable();
	NCMSLEntry		*walker= NULL;
	NSAttributes	 newAttributes;
	NSEntry		 	 newEntry;
	int 			 i;

	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{	newAttributes.name = walker->getData().name;
			newAttributes.spell= walker->getData().spell;
			newEntry.setData(newAttributes);
			resultTable->insert(newEntry);
			walker=walker->getNext();
		}
	}
	return resultTable;
}

void NCMSLTable::printTable(){

	int i;
	NCMSLEntry* walker;

	
	cout<<endl<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"***Name-Class-Maxlevel-Spell-Level Table***"<<endl;
	cout<<"*******************************************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().name<<"\t";
			cout<<walker->getData().pClass<<"\t";
			cout<<walker->getData().max<<"\t";
			cout<<walker->getData().spell<<"\t";
			cout<<walker->getData().level<<endl;
			walker=walker->getNext();

		}

	}
	return ;
}

class NCMLTable{
	private:
		NCMLEntry **table;
		int 	   tableSize;
	public:
		NCMLTable();
		int hashFunc(string);
		void insert(NCMLEntry);
		NCMLTable* Selection(const char*,const char*);
		NCMLTable* Selection(const char*,const char*,const char*);
		void printTable();
		//Join();Not used
		//Projection();Not used
};

NCMLTable::NCMLTable(){
		int i;

		table= new NCMLEntry*[DEFAULT_SIZE];

		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int NCMLTable::hashFunc(string name){
	int key = 0;
	int length=name.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)name[i]);
	}

	return key % tableSize;
}


void NCMLTable::insert(NCMLEntry newEntry){
	int index;
	NCMLEntry* walker;
	NCMLEntry* prev;

	NCMLAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.name);
	if(table[index]!=NULL)
	{	prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new NCMLEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new NCMLEntry();
		table[index]->setData(entryData);
	}

	return ;
}

NCMLTable* NCMLTable::Selection(const char* attr1,const char* attr2){

	NCMLTable* resultTable = new NCMLTable();
	NCMLEntry* walker;
	int i=0;

	if(attr1=="Max" && attr2=="Level")
	{
		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{
				if(walker->getData().max >= walker->getData().level)
						resultTable->insert(*walker);
				walker=walker->getNext();
			}
		}
	}

	return resultTable;
}

NCMLTable* NCMLTable::Selection(const char* attr1,const char* comparator,const char* attr2){

	NCMLTable* resultTable = new NCMLTable();
	NCMLEntry* walker = NULL;
	int i=0;

	if(attr1=="Max" && comparator == ">=" && attr2=="Level" )
	{
		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{	
				if(walker->getData().max >= walker->getData().level)
				{	
					resultTable->insert(*walker);	
				}
				walker=walker->getNext();
			}
		}
	}
		

	return resultTable;
}

void NCMLTable::printTable(){

	int i;
	NCMLEntry* walker;

	
	cout<<endl<<endl;
	cout<<"*************************************"<<endl;
	cout<<"***Name-Class-Maxlevel-Level Table***"<<endl;
	cout<<"*************************************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().name<<"\t";
			cout<<walker->getData().pClass<<"\t";
			cout<<walker->getData().max<<"\t";
			cout<<walker->getData().level<<endl;
			walker=walker->getNext();
		}

	}
	return ;
}


class CLTable{
	private:
		CLEntry **table;
		int 	   tableSize;
	public:
		CLTable();
		int hashFunc(string);
		void insert(CLEntry);
		void printTable();
		CLEntry* getEntry(int index){return table[index];}
		//Selection();
		//NCMLTable Join(NCMTable);
		//Projection();
};

CLTable::CLTable(){
		int i;
		table= new CLEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int CLTable::hashFunc(string Class){
	int key = 0;
	int length=Class.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)Class[i]);
	}

	return key % tableSize;
}

void CLTable::insert(CLEntry newEntry){
	int index;
	int key;
	CLEntry* walker;
	CLEntry* prev;

	CLAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.pClass);
	if(table[index]!=NULL)
	{
		prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new CLEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new CLEntry();
		table[index]->setData(entryData);
	}

	return ;
}


void CLTable::printTable(){

	int i;
	CLEntry* walker;

	
	cout<<endl<<endl;
	cout<<"***********************"<<endl;
	cout<<"***Class-Level Table***"<<endl;
	cout<<"***********************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().pClass<<"\t";
			cout<<walker->getData().level<<endl;
			walker=walker->getNext();

		}

	}
	return ;
}


class SCLTable{
	private:
		SCLEntry **table;
		int 	   tableSize;
	public:
		SCLTable();
		int hashFunc(string);
		void insert(SCLEntry);
		SCLEntry* getEntry(int index){return table[index];}
		SCLTable* Selection(const char*,Spell);//Select single spell
		CLTable* Projection(const char*,const char*);//Project "Class" and "Level"
		void printTable(void);
};

SCLTable::SCLTable(){
		int i;
		table= new SCLEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int SCLTable::hashFunc(string spell){
	int key = 0;
	int length=spell.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)spell[i]);
	}	

	return key % tableSize;
}
void SCLTable::insert(SCLEntry newEntry){
	int index;
	int key;
	SCLEntry* walker;
	SCLEntry* prev;

	SCLAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.spell);
	if(table[index]!=NULL)
	{
		prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{	prev=walker;
			walker=walker->getNext();
		}
		walker = new SCLEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new SCLEntry();
		table[index]->setData(entryData);
	}

	return ;
}

SCLTable* SCLTable::Selection(const char* attribute,string value){

	SCLTable* resultTable = new SCLTable();
	SCLEntry* walker = NULL;
	int i=0;

	if(attribute=="Spell")
	{
		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{
				if(walker->getData().spell==value)
					resultTable->insert(*walker);
				walker=walker->getNext();
			}
		}
	}
	
	return resultTable;
}


CLTable* SCLTable::Projection(const char* attr1,const char* attr2){

		CLTable			*resultTable= new CLTable();
		SCLEntry		*walker= NULL;
		CLAttributes	 newAttributes;
		CLEntry		 	 newEntry;
		int 			 i;

		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{	newAttributes.pClass = walker->getData().pClass;
				newAttributes.level= walker->getData().level;
				newEntry.setData(newAttributes);
				resultTable->insert(newEntry);
				walker=walker->getNext();
			}
		}
		return resultTable;
}


void SCLTable::printTable(){

	int i;
	SCLEntry* walker;

	
	cout<<endl<<endl;
	cout<<"*****************************"<<endl;
	cout<<"***Spell-Class-Level Table***"<<endl;
	cout<<"*****************************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().spell<<"\t";
			cout<<walker->getData().pClass<<"\t";
			cout<<walker->getData().level<<endl;
			walker=walker->getNext();
		}

	}
	return ;
}

class NCMTable{
	private:
		NCMEntry **table;
		int 	   tableSize;

	public:
		NCMTable();//Base constructor
		void insert(NCMEntry);
		int hashFunc(string);
		NCMTable* Selection(const char*,Name);//Select single value from attr
		NCMTable* Selection(const char*,Name,Name);//Select 2 values from attr
		NCMSLTable* Join(SCLTable*);
		NCMLTable* Join(CLTable*);
		void printTable(void);
		void concat(NCMTable*);
		NCMEntry* getEntry(int index){return table[index];}
		//Projection(); Not used
};

NCMTable::NCMTable(){
		int i;
		table= new NCMEntry*[DEFAULT_SIZE];
		for(i=0;i<DEFAULT_SIZE;i++)
			table[i]=NULL;
		tableSize = DEFAULT_SIZE;
}

int NCMTable::hashFunc(string name){
	int key = 0;
	int length=name.length();
	int i;

	for(i=0;i<length;i++)
	{
		key=(key * 2)+((int)name[i]);
	}


	return key % tableSize;
}


void NCMTable::insert(NCMEntry newEntry){
	int index;
	NCMEntry* walker;
	NCMEntry* prev;
	NCMAttributes entryData= newEntry.getData();
	index=hashFunc(entryData.name);
	if(table[index]!=NULL)
	{	
		prev=table[index];
		walker=table[index]->getNext();
		while(walker!=NULL)
		{
			prev=walker;
			walker=walker->getNext();
		}
		walker = new NCMEntry();
		walker->setData(entryData);
		prev->setNext(walker);
	}
	else{
		table[index]= new NCMEntry();
		table[index]->setData(entryData);
	}

	return ;
}

NCMTable* NCMTable::Selection(const char* attribute,string value){

	NCMTable* resultTable = new NCMTable();
	NCMEntry* walker = NULL;
	int i=0;

	if(attribute=="Name")
	{
		for(i=0;i<tableSize;i++)
		{
			walker=table[i];
			while(walker!=NULL)
			{
				if(walker->getData().name==value)
					resultTable->insert(*walker);
				walker=walker->getNext();
			}
		}
	}
	else//attribute == "Class"
	{
		for(i=0;i<tableSize;i++)//For Each Bucket
		{
			walker=table[i];
			while(walker!=NULL)//Go through each bucket
			{
				if(walker->getData().pClass==value)//If you find a match
						resultTable->insert(*walker);//Add it to the results
				walker=walker->getNext();//Move to nexxt element
			}
		}
	}

	return resultTable;
}

NCMSLTable* NCMTable::Join(SCLTable* table2){


	int i;
	int j;
	NCMSLTable *resultTable = new NCMSLTable();
	NCMEntry* walker1;
	SCLEntry* walker2;
	NCMSLEntry newData;
	NCMSLAttributes newAttributes;


	for(i=0;i<tableSize;i++)//Every bucket in table 1(this)
	{	
		walker1=table[i];
		while(walker1!=NULL)//There is something in the bucket
		{	
			for(j=0;j<DEFAULT_SIZE;j++)//every index in table 2
			{	
				walker2=table2->getEntry(j);
				while(walker2!=NULL)//There is something in the bucket
				{	
					if(walker2->getData().pClass == walker1->getData().pClass)
					{	
						newAttributes.name=walker1->getData().name;
						newAttributes.pClass=walker1->getData().pClass;
						newAttributes.max=walker1->getData().max;
						newAttributes.spell=walker2->getData().spell;
						newAttributes.level=walker2->getData().level;
						newData.setData(newAttributes);
						resultTable->insert(newData);
					}
					walker2=walker2->getNext();
				}
			}
			walker1=walker1->getNext();
		}

	}
	return resultTable;
}

NCMLTable* NCMTable::Join(CLTable* table2){


	int i;
	int j;
	NCMLTable *resultTable = new NCMLTable();
	NCMEntry* walker1;
	CLEntry* walker2;
	NCMLEntry newData;
	NCMLAttributes newAttributes;


	for(i=0;i<tableSize;i++)//Every bucket in table 1(this)
	{	
		walker1=table[i];
		while(walker1!=NULL)//There is something in the bucket
		{	
			for(j=0;j<DEFAULT_SIZE;j++)//every index in table 2
			{	
				walker2=table2->getEntry(j);
				while(walker2!=NULL)//There is something in the bucket
				{	
					if(walker2->getData().pClass == walker1->getData().pClass)
					{	
						newAttributes.name=walker1->getData().name;
						newAttributes.pClass=walker1->getData().pClass;
						newAttributes.max=walker1->getData().max;
						newAttributes.level=walker2->getData().level;
						newData.setData(newAttributes);
						resultTable->insert(newData);
					}
					walker2=walker2->getNext();
				}
			}
			walker1=walker1->getNext();
		}

	}
	return resultTable;
}

void NCMTable::printTable(){

	int i;
	NCMEntry* walker;

	
	cout<<endl<<endl;
	cout<<"*******************************"<<endl;
	cout<<"***Name-Class-Maxlevel Table***"<<endl;
	cout<<"*******************************"<<endl;
	for(i=0;i<tableSize;i++)
	{
		walker=table[i];
		while(walker!=NULL)
		{
			cout<<walker->getData().name<<"\t";
			cout<<walker->getData().pClass<<"\t";
			cout<<walker->getData().max<<endl;
			walker=walker->getNext();

		}

	}
	return ;
}

void NCMTable::concat(NCMTable* table2)
{
	int i;
	NCMEntry* walker;
		
	for(i=0;i<tableSize;i++)
	{
		walker=table2->getEntry(i);
		while(walker!=NULL)
		{
			this->insert(*walker);
			walker=walker->getNext();
		}
	}

	return	;

}
#endif /* RELATIONALTABLES_H_ */
