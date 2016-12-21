// --- Projet RType
// Representation d'un Client
# ifndef WCLIENT_HH_
# define WCLIENT_HH_

// librairie standard.
# include <iostream>
# include <sstream>
# include <string>
# include <cstdio>

// librairie socket.
# include <winsock2.h>
# pragma comment(lib, "ws2_32.lib")

# define RECV_TAILLE 500

class WClient
{
public:
	// --- Constructeur ---
	WClient(SOCKET id, SOCKADDR_IN info);
	WClient(const WClient &tmp);
	WClient				&operator=(const WClient &tmp);
	~WClient();

	// --- Communication ---
	std::string			Brecv(void);
	std::string			NBrecv(void);
	void				Bsend(const std::string msg);
	void				NBsend(const std::string msg);

	// --- Fermeture ---
	void				close();

	// --- Getteur ---
	SOCKET				getIdConnect();
	SOCKADDR_IN			getInfo();
	bool				getRunning();
	std::string			getName();

private:
	SOCKET		 _idConnect; /*identifiant du socket client.*/
	SOCKADDR_IN  _Info; /*Information sur le client.*/
	std::string _name;
	bool		_Running;
};

# endif /*!WCLIENT_HH_*/

