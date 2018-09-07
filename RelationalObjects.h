#ifndef RELATIONALOBJECTS_H_
#define RELATIONALOBJECTS_H_

class NCMEntry{
	private:
		NCMAttributes 	data;
		NCMEntry*	next;
	public:
		NCMEntry(){next=NULL;}
		void setData(NCMAttributes newData){data = newData;}
		NCMAttributes getData();
		void setNext(NCMEntry* newNext){next=newNext;}
		NCMEntry* getNext(){return next;}

};
NCMAttributes NCMEntry::getData(){
	return data;
}


class SCLEntry{
	private:
		SCLAttributes 	data;
		SCLEntry*		next;
	public:
		void setData(SCLAttributes newData){data = newData;}
		SCLAttributes getData();
		void setNext(SCLEntry* newNext){next=newNext;}
		SCLEntry* getNext(){return next;}
};
SCLAttributes SCLEntry::getData(){
	return data;
}



class STEntry{
	private:
		STAttributes 	data;
		STEntry*		next;
	public:
		void setData(STAttributes newData){data = newData;}
		STAttributes getData();
		void setNext(STEntry* newNext){next=newNext;}
		STEntry* getNext(){return next;}
};
STAttributes STEntry::getData(){
	return data;
}




class NCMSLEntry{
	private:
		NCMSLAttributes 	data;
		NCMSLEntry*			next;
	public:
		void setData(NCMSLAttributes newData){data = newData;}
		NCMSLAttributes getData();
		void setNext(NCMSLEntry* newNext){next=newNext;}
		NCMSLEntry* getNext(){return next;}
};
NCMSLAttributes NCMSLEntry::getData(){
	return data;
}




class NCMLEntry{
	private:
		NCMLAttributes 	data;
		NCMLEntry*		next;
	public:
		void setData(NCMLAttributes newData){data = newData;}
		NCMLAttributes getData();
		void setNext(NCMLEntry* newNext){next=newNext;}
		NCMLEntry* getNext(){return next;}
};
NCMLAttributes NCMLEntry::getData(){
	return data;
}




class CLEntry{
	private:
		CLAttributes 	data;
		CLEntry*		next;
	public:
		void setData(CLAttributes newData){data = newData;}
		CLAttributes getData();
		void setNext(CLEntry* newNext){next=newNext;}
		CLEntry* getNext(){return next;}
};
CLAttributes CLEntry::getData(){
	return data;
}




class NSTEntry{
	private:
		NSTAttributes 	data;
		NSTEntry*		next;
	public:
		void setData(NSTAttributes newData){data = newData;}
		NSTAttributes getData();
		void setNext(NSTEntry* newNext){next=newNext;}
		NSTEntry* getNext(){return next;}
};

NSTAttributes NSTEntry::getData(){
	return data;
}



class NSEntry{
	private:
		NSAttributes 	data;
		NSEntry*		next;
	public:
		void setData(NSAttributes newData){data = newData;}
		NSAttributes getData();
		void setNext(NSEntry* newNext){next=newNext;}
		NSEntry* getNext(){return next;}
};
NSAttributes NSEntry::getData(){
	return data;
}

#endif /* RELATIONALOBJECTS_H_ */
