#include "Threading.h"
#include "NonBlocking.h"
#include "SocketSelector.h"


void main() {

#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	vector<sf::TcpSocket*> s;
	char connectionType, mode, prot;
	Protocol* protocol = nullptr;
	string text1 = "\nConnected to: ";

	cout << "Enter (s) for Server, Enter (c) for Client: ";
	cin >> connectionType;

	if (connectionType == 's') {
		cout << "\nPROTOCOL\n- (1) for Threading\n- (2) for NonBlocking\n- (3) for SocketSelector\n\nYour selection: ";
		cin >> prot;

		sf::TcpListener listener;
		listener.listen(PORT);
		listener.accept(socket);
		text1 += "Client\n";
		cout << text1;
		mode = 's';
		listener.close();

		sf::Socket::Status status = socket.send(&prot, sizeof(char));
		if (status != sf::Socket::Done) {
			cout << "Ha fallado el envio de datos\n";
		}
	}
	else if (connectionType == 'c') {
		socket.connect(ip, PORT);
		text1 += "Server\n";
		cout << text1;
		mode = 'r';

		size_t protocolLength;
		sf::Socket::Status status = socket.receive(&prot, MAX_LENGTH, protocolLength);
		if (status != sf::Socket::Done) {
			cout << "Ha fallado la recepcion de datos\n";
		}
	}
#pragma endregion

	switch (prot) {
	case '1': //Threading
		protocol = new Threading(&socket);
		break;
	case '2': //NonBlocking
		protocol = new NonBlocking(&socket);
		break;
	case '3': //SocketSelector
		s.push_back(&socket);
		protocol = new SocketSelector(s);
		break;
	default:
		cout << "Error en el tipo de protocolo!\n";
		break;
	}

	protocol->Run();


}