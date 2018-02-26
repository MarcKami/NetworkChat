#include "Threading.h"
//#include "NonBlocking.h"
//#include "SocketSelector.h"


void main() {
#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	Protocol* protocol = nullptr;
	sf::Packet sendPacket;
	char* myNick = " ";

	cout << "Enter your NickName: ";
	cin >> nick;

	std::string temp(myNick);
	nick = temp;

	sf::Socket::Status status = socket.connect(ip, PORT);
	if (status != sf::Socket::Done) {
		std::cout << "Error de conexion\n";
		exit(0);
	}
	else {
		std::cout << "Conectado al chat\n";
	}
#pragma endregion

	protocol = new Threading(&socket);

	protocol->Run();
}