// --- Projet RType.
//# include "stdafx.h"
# include <stdio.h>
# include <iostream>
# include <string>

# ifdef WIN32
# include "WSClient.h"
# else
# include "USClient.h"
# endif


int main()
{
	SClient *client = NULL;
	std::string    rep = "";
	int		_port = 4565; /* Port du serveur à laquelle je veux me connecter.*/
	std::string		_ip = "127.0.0.1";

# ifdef WIN32
	client = new WSClient(_port, _ip);
	std::cout << "* Running in Windows env" << std::endl;
# else // UNIX
	client = new USClient(_port, _ip);
	std::cout << "* Running in Unix env" << std::endl;
# endif 
	std::cout << "Client : " << _ip << "." << std::endl;
	// Connection ..
	client->connection();
	std::cout << "Connexion vers serveur -> ok." << std::endl;
	client->NBsend("Salut !!sdfqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqfsqfsqfffffffffffffffffffffffffffffffffffffffffffffffsqfsqfsqfqsfd");

	//delete client;
	return 0;
}
