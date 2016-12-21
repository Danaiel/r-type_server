// --- Projet RType
// Representation d'un Client
# ifndef UCLIENT_HH_
# define UCLIENT_HH_

// librairie standard.
# include <iostream>
# include <string.h>
# include <stdio.h>
# include <sstream>
# include <unistd.h>

// librairie socket.
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>

# define RECV_TAILLE 500

class UClient
{
public:
	// --- Constructeur ---
	UClient(int idConnect, struct sockaddr_in info);
	UClient(const UClient &tmp);
	~UClient(void);
        UClient &operator=(const UClient &tmp);

        // --- Communication ---
	std::string			Brecv(void);
	std::string			NBrecv(void);
	void				Bsend(const std::string msg);
	void				NBsend(const std::string msg);
	
	// --- Fermeture ---
	void				close();

	// --- Getteur ---
	int					getIdConnect();
	struct sockaddr_in  getInfo();
	bool				getRunning();
	std::string			getName();

private:
	int					_idConnect;  /*identifiant du socket client.*/
	struct sockaddr_in	_Info;  /*Information sur le client.*/
	std::string			_name;
	bool				_Running;
};

# endif /*!UCLIENT_HH_*/
