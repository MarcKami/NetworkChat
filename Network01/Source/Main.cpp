#include "Threading.h"

int main() {

#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode, prot;
	Protocol protocol;
	string text1 = "\nConnected to: ";

	cout << "Enter (s) for Server, Enter (c) for Client: ";
	cin >> connectionType;

	if (connectionType == 's') {
		cout << "\nPROTOCOL\n- (1) for Threading\n- (2) for NonBlocking\n- (3) for SocketSelector\n\nYour selection: ";
		cin >> prot;

		sf::TcpListener listener;
		listener.listen(PORT);
		listener.accept(socket);
		text1 += "Client";
		cout << text1;
		mode = 's';
		listener.close();

		sf::Socket::Status status = socket.send(&prot, sizeof(char));
		if (status != sf::Socket::Done) {
			//Ha fallado el envío de datos
		}
	}
	else if (connectionType == 'c') {
		socket.connect(ip, PORT);
		text1 += "Server";
		cout << text1;
		mode = 'r';

		size_t protocolLength;
		sf::Socket::Status status = socket.receive(&prot, MAX_LENGTH, protocolLength);
		if (status != sf::Socket::Done) {
			//Ha fallado la recepción de datos
		}
	}
#pragma endregion

	switch (prot) {
	case '1': //Threading
		protocol = Threading(&socket);
		break;
	case '2': //NonBlocking
				//myProtocol = NonBlocking;
		break;
	case '3': //SocketSelector
				//myProtocol = SocketSelector;
		break;
	default:
		//Error en el tipo de protocolo
		break;
	}




	protocol.Run();

}