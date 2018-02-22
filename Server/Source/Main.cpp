#include "Receptor.hpp"

void main() {

#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	vector<sf::TcpSocket*> aSockets;
	sf::TcpSocket incoming;
	int users = 0;
	vector<pair<string, originText>> aMensajes;

	sf::TcpListener dispatcher;
	sf::Socket::Status status = dispatcher.listen(PORT);
	if (status != sf::Socket::Done) {
		cout << "No se puede vincular al puerto 5000\n";
	}

	while (users < MAX_USERS) {
		if (dispatcher.accept(incoming) != sf::Socket::Done) {
			cout << "Error al aceptar conexión\n";
		}
		else {
			users++;
			aSockets.push_back(&incoming);
		}
	}

	dispatcher.close();

#pragma endregion

	Receptor_Selection r(aSockets, &aMensajes);
	thread t(r);

	//SEND
	sf::Packet sendData;

	for each (sf::TcpSocket* s in aSockets) {
		sf::Socket::Status status = s->send(sendData);
		if (status == sf::Socket::Error) {
			cout << "Ha fallado el envio de datos\n";
		}
		else if (status == sf::Socket::Disconnected) {
			cout << "Ha fallado el envio de datos\n";
			//Borrar abans del aSockets
			s->disconnect();
		}
	}

	//DISCONNECT AL SALIR/CERRAR
	for each (sf::TcpSocket* s in aSockets) {
		//Borrar abans del aSockets
		s->disconnect();
	}

	//ESPERAR A QUE ACABE "T"
	t.join();
}