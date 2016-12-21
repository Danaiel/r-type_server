// --- Projet RType 
// Class Abstract pour le Serveur.
# ifndef SSERVEUR_H_
# define SSERVEUR_H_

// libriaire standard.
# include <stdio.h>
# include <iostream>
# include <string>

class SServeur
{
public:
	
	virtual		void			connection() = 0;
	virtual		int				acceptServeur() = 0;
	virtual		int				closeSocket() = 0;
	virtual		void			*ThreadacceptServeur(void) = 0;

	// Communication ...
	virtual	void				NBsendto(int id, std::string msg) = 0;
	virtual void				Bsendto(int id, std::string msg) = 0;
	virtual std::string			NBrecv(int id) = 0;
	virtual std::string			Brecv(int id) = 0;

	// Gestion de la liste ...
	virtual		int				removelistClient(int id) = 0;
	virtual		int				removelistClient(std::string name) = 0;
	virtual		void			removeAllListClient() = 0;
	virtual     void			printListClient() const = 0;

	// Getter ...
	virtual		int				getPort() const = 0; /*Obtenir le port du serveur.*/
	virtual     bool			getRunning() const = 0; /*Obtenir l'etat de la socket.*/
	virtual     int				getNbClient() const = 0;
};

#endif /*!SSERVEUR_H_*/
