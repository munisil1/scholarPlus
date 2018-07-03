
#define Bio_Control (*(volatile unsigned char *)(0x84000250))
#define Bio_Status (*(volatile unsigned char *)(0x84000250))
#define Bio_TxData (*(volatile unsigned char *)(0x84000252))
#define Bio_RxData (*(volatile unsigned char *)(0x84000252))
#define Bio_Baud (*(volatile unsigned char *)(0x84000254))

void Init_Bio(void) {
	Bio_Control = 0x15;
	Bio_Baud = 0x07;
	usleep(100000); //wait for 100ms
}

unsigned char getChar_Bio(void) {
	while ((Bio_Status & 0x01) != 0x01)
		;
	return Bio_RxData;
}

unsigned char getbyte4() {
	unsigned char syn;
	syn = getChar_Bio();
	while (syn != 1)
		syn = getChar_Bio();
	getChar_Bio();
	getChar_Bio();

	return getChar_Bio();  //i am getting the 4th byte- unsigned char for spo2
}

unsigned char get_Pulse() {
	unsigned char syn;
	syn = getChar_Bio();
	while (syn != 1)
		syn = getChar_Bio();
	getChar_Bio();

	return getChar_Bio();
}

unsigned char get_HR(){
	unsigned char rev, sop, hrl, hrm;
	hrm = getChar_Bio();
	hrl = getChar_Bio();
	sop = getChar_Bio();
	rev = getChar_Bio();
	while(rev != 52){
		hrm = hrl;
		hrl = sop;
		sop = rev;
		rev = getbyte4();
	}
	if(hrl >= 128){
		return hrm;
		printf("hrm >> 7 is %d \n", hrm);
	}
	else
		return hrl;
}

unsigned char get_Spo2() {
	unsigned char rev, spo2;
	rev = getbyte4();
	//int i;
	//for (i = 0; i < 14; i++) {
		while (rev != 52) {
			spo2 = rev;
			rev = getbyte4();
		}
	//}
	return spo2;
}

