// Unix Socket Client.
# ifndef USCLIENT_H_
# define USCLIENT_H_

// libriaire socket.
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>

// libriaire standard.
# include <iostream>
# include <string>
# include <unistd.h>

// Class Abstarct
# include "SClient.h"

# define RECV_TAILLE 500

class    USClient : public SClient
{
public:
	USClient(int port, std::string ip = "127.0.0.1");
	USClient(const USClient &tmp);
	~USClient(void);

	// Getter
	int							getIdSocket() const;
	struct sockaddr_in			getInfo() const;
	virtual std::string			getIp() const;
	virtual bool				getRunning() const;
	virtual int					getPort() const;
	virtual int					getServerPort() const;

	// Setter
	void						setIdSocket(int id);

	virtual void				connection();
	virtual int					closeSocket();

	virtual std::string			NBrecv(void); /*recevoir non bloquant.*/
	virtual void				NBsend(const std::string msg); /*envoyer non bloquant.*/

	virtual std::string			Brecv(void); /*recevoir bloquant.*/
	virtual void				Bsend(const std::string msg); /*envoyer bloquant.*/

	USClient					&operator=(const USClient &tmp);

private:

	struct sockaddr_in			_info;	/*Structure d'information sur la socket.*/
	int							_idSocket; /*idenfiant du socket.*/
	std::string					_ip; /*Ip du Serveur.*/
	int							_port; /*Port du Client.*/
	int							_ServerPort; /*Port du Serveur.*/
	bool						_running; /*Savoir si la socket est en route.*/
};

# endif /*!USCLIENT_H_*/