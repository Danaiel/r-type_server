// Windows Socket Client
# ifndef WSCLIENT_H_
# define WSCLIENT_H_

// libriraire socket.
# include <Winsock2.h> /*Bibliothéque pour les sockets.*/
# pragma comment(lib, "ws2_32.lib")
# include <windows.h>
# include <Ws2def.h>
# include <Ws2tcpip.h>

// libriraire standard.
# include <cstdio>
# include <iostream>
# include <string>

// Class Abstract
# include "SClient.h"

# define RECV_TAILLE 500
//# define WINSOCK_DEPRECATED_NO_WARNINGS

class WSClient : public SClient
{
public:
	WSClient(int port, std::string ip = "127.0.0.1");
	WSClient(const WSClient &tmp);
	~WSClient(void);

	// Getter.
	SOCKET					getIdSocket() const;
	SOCKADDR_IN				getInfo() const;
	virtual std::string		getIp() const;
	virtual bool			getRunning() const;
	virtual int				getPort() const;
	virtual int				getServerPort() const;

	// Setter.
	void					setIdSocket(SOCKET id);

	virtual void			connection();
	virtual int				closeSocket();

	virtual std::string		NBrecv(void); /*recevoir non bloquant.*/
	virtual void			NBsend(const std::string msg); /*envoyer non bloquant.*/

	virtual std::string		Brecv(void); /*recevoir bloquant*/
	virtual void			Bsend(const std::string msg); /*envoyer bloquant.*/

	WSClient				&operator=(const WSClient &tmp);

private:

	SOCKADDR_IN			_info; /*Structure d'information sur la socket.*/
	SOCKET				_idSocket; /*idenfiant du socket.*/
	std::string			_ip; /*Ip du Serveur.*/
	int					_port; /*Port du Client.*/
	int					_ServerPort; /*Port du Serveur.*/
	bool				_running; /*Savoir si la socket est en route.*/
};

# endif /*!WSCLIENT_H_*/