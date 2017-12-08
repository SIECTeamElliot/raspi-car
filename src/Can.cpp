#include "../include/Can.h"

int Can::initFilters() 
{ 
	// defining filters for CAN :
	struct can_filter rfilter[nbFilters];

	for(int i = 0; i < nbFilters; i++)
	{
		rfilter[i].can_mask = CAN_SFF_MASK;
		rfilter[i].can_id = idFilters[i];
	}

	return setsockopt((*this->canSckt), SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

}	

int Can::initSocket()
{
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	printf("[init_all] starting socket\n");

	if(	( *(this->canSckt) = socket(PF_CAN, SOCK_RAW, CAN_RAW) ) < 0) {
		perror("Error while opening socket");
		//	return -1;
	} else { 
		this->enable = true;
	}

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl((*this->canSckt), SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// bind the socket to a can interface
	if(bind((*this->canSckt), (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		//return -2;
	}
}

Can::Can() : enable(false), canSckt(new int)
{
	initSocket(); 
	initFilters();
}

Can::~Can() 
{
	if( listening ) 
	{
		delete listenThread; 
	}
	close(*this->canSckt); 
}


#define TH_NAME "listen"
void Can::listenTask()
{
	printf("%s Starting thread\n",TH_NAME);
    struct can_frame canFrame;
    printf("%s Socket number : %d\n",TH_NAME,(*this->canSckt));
    int nbytes;
  

  while (1){
   
    nbytes = read((*this->canSckt),&canFrame,sizeof(struct can_frame));

    // Checking that there are no errors raised by read
    if (nbytes < 0){
      perror ("[Listen] can raw socket read \n");
    }

    // Checking that the frame received is complete 
    if (nbytes < sizeof(struct can_frame)){
      perror("[Listen] read: incomplete CAN frame");
    }

    // affichage du paquet reçu
    if(DEBUG){
      printf("%s Received var number %d = %d \n",TH_NAME,canFrame.can_id,canFrame.data[0]);
    }
    // TODO rajouter une sécurité sur la data
    if (sizeof(canFrame.data[0])>0){
      listenCallback(nbytes, canFrame.data);
    }

  }
}

int Can::sendFrame(struct can_frame *frame, char data)
{
	(*frame).data[0]=data;
	return write(*this->canSckt, frame, sizeof(struct can_frame));
}

int Can::startListening(void (*callback)(int nbBytes, unsigned char * data))
{
	if( !listening && enable ) 
	{
		listenThread = new std::thread (&Can::listenTask, this); 
		listening = true; 
	}
}

int Can::stopListening()
{
	if( listening && enable ) 
	{
		delete listenThread;
		listening = false;
	}
}