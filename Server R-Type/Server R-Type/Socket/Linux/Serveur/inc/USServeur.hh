// --- Projet RType
// Unix Socket Serveur.
# ifndef USSERVEUR_H_
# define USSERVEUR_H_

// libriaire standard.
# include <unistd.h>
# include <vector>

# include "SServeur.hh"
# include "UClient.hh"

// libriaire socket.
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>


class	USServeur : public SServeur
{
public:
	USServeur(int port);
	USServeur(const USServeur &tmp); // Constructeur par recopie.
	~USServeur(void);
	USServeur					&operator=(const USServeur &tmp);

	virtual void				connection();
	virtual int					acceptServeur();
	virtual int					closeSocket();
	virtual void				*ThreadacceptServeur(void);

	// Communication ...
	virtual void				NBsendto(int id, std::string msg);
	virtual void				Bsendto(int id, std::string msg);
	virtual std::string			NBrecv(int id);
	virtual std::string		    Brecv(int id);

	// Gestion de la liste ...
	virtual	int					removelistClient(int id);
	virtual int					removelistClient(std::string name);
	virtual void				removeAllListClient();
	int							addClient(int id, struct sockaddr_in info);
	virtual void				printListClient() const;

	// Getter ...
	struct sockaddr_in			getInfoServeur() const; /*Obtenir l'information sur la socket Serveur.*/
	int							getSocketServeur() const; /*Obtenir la socket du Serveur.*/
	virtual int					getPort() const; /*Obtenir le port du serveur.*/
	virtual bool				getRunning() const;
	virtual int					getNbClient() const;

private:

	struct sockaddr_in	_Info; // On prépare l'adresse d'attachement local.
	int					_idSocket; /*idenfiant du socket.*/
	int					_port;
	bool				_Running; /*Etat de la socket.*/
	std::vector< UClient *> _listClients;
};

void							*uniThreadacceptServeur(USServeur *server);

# endif /*!USSERVEUR_H_*/
