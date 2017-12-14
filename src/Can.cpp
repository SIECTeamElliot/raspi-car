#include "../include/Can.h"


// Construct a CAN object - must be call once 
Can::Can() : 
		enable(false), 
		canSckt(new int)
{
	idFilters = new unsigned int[1]; 
	idFilters[0] = (unsigned int) 0x100;
	initSocket(); 
	initFilters();
}

Can::Can(int nbFilters, unsigned int * idFilters) : 
		enable(false), 
		canSckt(new int), 
		nbFilters(nbFilters),
		idFilters(new unsigned int[nbFilters])
{
	//cpy
	initSocket(); 
	initFilters();
}

// Close the can socket and stop the listening
Can::~Can() 
{
	if( listening ) 
	{
		delete listenThread; 
		listening = false; 
	}
	close(*this->canSckt); 
}


// Init CAN filters with the ID defined in idFilters
int Can::initFilters() 
{ 
	if(nbFilters > 0) 
	{

		// defining filters for CAN :
		struct can_filter rfilter[nbFilters];

#ifdef DEBUG 
			std::cout << "CAN ID Filter init. to : "; 
#endif 

		for(int i = 0; i < nbFilters; i++)
		{
			rfilter[i].can_mask = CAN_SFF_MASK;
			// rfilter[i].can_id = idFilters[i];
			rfilter[i].can_id = 33;

#ifdef DEBUG
			std::cout << rfilter[i].can_id << "-"; 
		}
#else 
		}
#endif

		return setsockopt((*this->canSckt), SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
	}
	else
	{
		return 0; 
	}
}	

// Init CAN socket and store it in canSckt
int Can::initSocket()
{
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	std::cout << "[CAN] Starting socket." << std::endl;

	if(	( *(this->canSckt) = socket(PF_CAN, SOCK_RAW, CAN_RAW) ) < 0) {
		std::cerr << "Error while opening socket" << std::endl;
		return -1;
	} else { 
		this->enable = true;
	}

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl((*this->canSckt), SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	std::cout << "[CAN] Get interface name : " << ifname << "." << std::endl;

	// bind the socket to a can interface
	if(bind((*this->canSckt), (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		std::cerr << "Error in socket bind" << std::endl;
		return -2;
	}
}


// Listening task, launched in a thread
void Can::listenTask()
{
#ifdef DEBUG
	std::cout << "Starting the listening thread" << std::endl;
#endif 

    struct can_frame canFrame;
    int nbytes;
  

  while (1){
   
    nbytes = read((*this->canSckt),&canFrame,sizeof(struct can_frame));

    // Checking that there are no errors raised by read
    if (nbytes < 0){
      std::cerr << "[Listen] can raw socket read \n" << std::endl; 
    }

    // Checking that the frame received is complete 
    if (nbytes < sizeof(struct can_frame)){
      std::cerr << "[Listen] read: incomplete CAN frame" << std::endl;
    }

    // affichage du paquet reçu
#ifdef DEBUG
		std::cout << "[Received]: [" << canFrame.can_id << "] -> "; 
		for(int i = 0; i < nbytes; i++) 
		{ 
      		std::cout << canFrame.data[i] << "-"; 
      	}
      	std::cout << std::endl;
#endif

    // TODO rajouter une sécurité sur la data
    if (sizeof(canFrame.data[0])>0 && listenCallback != nullptr) {
      listenCallback(nbytes, canFrame.data);
    }

  }
}

// Sporadic CAN function to send message
int Can::sendFrame(struct can_frame *frame, int nbBytes, unsigned char * bytes) 
{
	if (nbBytes > CAN_MAX_DLEN) 
	{
		std::cerr << "[sendFrame]: Expected a CAN frame data length nbBytes < " << CAN_MAX_DLEN << std::endl; 
		return -1;
	} 


#ifdef DEBUG
	std::cout << "[Sent]: [" << frame->can_id << "] -> "; 
#endif 	
	(*frame).can_dlc = nbBytes;

	for(int i = 0; i < nbBytes; i++) 
	{
		(*frame).data[0] = bytes[0];
#ifdef DEBUG
		std::cout << bytes[i] << std::endl; 
	}
	std::cout << std::endl;
#else 
	}	
#endif

	return write(*this->canSckt, frame, sizeof(struct can_frame));
}

// Starts the listening thread
int Can::startListening(void (*callback)(int nbBytes, unsigned char * data))
{
	if( !listening && enable ) 
	{
		listenThread = new std::thread (&Can::listenTask, this); 
		listening = true; 
	}
}

// Stops the listening thread
int Can::stopListening()
{
	if( listening && enable ) 
	{
		delete listenThread;
		listening = false;
	}
}