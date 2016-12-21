// Class Abstract pour les socket pour un client.
# ifndef SCLIENT_H_
# define SCLIENT_H_

// libriaire standard.
# include <cstdio>
# include <iostream>
# include <string>

class SClient
{
public:

	// Getter.
	virtual		int				getServerPort() const = 0;
	virtual		std::string		getIp() const = 0;
	virtual     bool			getRunning() const = 0;
	virtual     int				getPort() const = 0;


	virtual		void	connection() = 0;
	virtual		int		closeSocket() = 0;

	virtual		std::string		NBrecv(void) = 0;
	virtual		void			NBsend(const std::string msg) = 0;

	virtual		std::string     Brecv(void) = 0;
	virtual     void            Bsend(const std::string msg) = 0;

};

# endif /*!SCLIENT_H_*/