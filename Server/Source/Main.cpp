#include "Receptor.hpp"
#include "Listener.hpp"

void main() {

#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	vector<sf::TcpSocket*> aSockets;
	vector<pair<string, originText>> aMensajes;

	Listen_Server l(aSockets);
	thread t1(l);
#pragma endregion

	Receptor_Selection r(aSockets, &aMensajes);
	thread t2(r);

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
	t1.join();
	t2.join();
}