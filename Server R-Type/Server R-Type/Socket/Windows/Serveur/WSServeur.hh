// --- Projet RType
// Windows Socket Serveur
# ifndef WSSERVEUR_HH_
# define WSSERVEUR_HH_

// librairie standard.
# include <iostream>
# include <vector>
# include <cstdio>

# include "SServeur.hh"
# include "WClient.hh"

// librairie socket.
# include <winsock2.h>
# pragma comment(lib, "ws2_32.lib")

class WSServeur : public SServeur
{
public:
	WSServeur(int port);
	WSServeur(const WSServeur &tmp); // Constructeur par recopie.
	~WSServeur(void);
	WSServeur		&operator=(const WSServeur &tmp);
 
	virtual void			connection();
	virtual int				acceptServeur();
	virtual int				closeSocket();
	virtual void			*ThreadacceptServeur(void);

	// Communication ...
	virtual void			NBsendto(int id, std::string msg);
	virtual void			Bsendto(int id, std::string msg);
	virtual std::string		NBrecv(int id);
	virtual std::string		Brecv(int id);

	// Gestion de la liste ...
	virtual int				removelistClient(int id);
	virtual int				removelistClient(std::string name);
	virtual void			removeAllListClient();
	int						addClient(SOCKET id, SOCKADDR_IN info);
	virtual void			printListClient() const;

	// Getter ...
	SOCKADDR_IN				getInfoServeur() const; /*Obtenir l'information sur la socket Serveur.*/
	SOCKET					getSocketServeur() const; /*Obtenir la socket du Serveur.*/
	virtual int				getPort() const; /*Obtenir le port du serveur.*/
	virtual bool			getRunning() const; 
	virtual int				getNbClient() const;

private:

	SOCKADDR_IN _Info; // On prépare l'adresse d'attachement local.
	SOCKET		_idSocket; /*identifant du socket.*/
	int			_port;
	bool		_Running; /*Etat de la socket.*/
	std::vector<WClient *>  _listClients;
};

void				*winThreadacceptServeur(WSServeur *server);

# endif /*!WSSERVEUR_HH_*/