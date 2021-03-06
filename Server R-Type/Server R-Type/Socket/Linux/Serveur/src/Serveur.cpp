// --- Projet RType

// Librairie standrad.
# include <string>
# include <iostream>

// Librairie socket.
# include "SServeur.hh"

# ifdef WIN32
# include "WSServeur.hh"
# else
# include "USServeur.hh"
# endif

int main()
{
	int				_port = 4565; /*Port du Serveur.*/
	std::string		_ip = "127.0.0.1";
	SServeur		*_server = NULL;

	# ifdef WIN32
		_server = new WSServeur(_port);
		std::cout << "* Running in Windows env" << std::endl;
	# else // Linux
		_server = new USServeur(_port);
		std::cout << "* Running in Linux env" << std::endl;
	# endif
	std::cout << "Procedure de creation du Serveur -> ok" << std::endl;
	std::cout << "Serveur : " << _ip << ":" << _port << "." << std::endl;

	// Connection ...
	_server->connection();
	
	// Acception ...
	int it;
	while (1) /* Boucle infinie. Exercice : améliorez ce code. */
	{
		it = _server->acceptServeur();
		_server->printListClient();
		_server->NBrecv(it);
	}
	//delete _server;
	return 0;
}
