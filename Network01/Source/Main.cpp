#include "Threading.h"
//#include "NonBlocking.h"
//#include "SocketSelector.h"


void main() {
#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	Protocol* protocol = nullptr;
	string nick;
	sf::Packet sendPacket;

	cout << "Enter your NickName: ";
	cin >> nick;	
	socket.connect(ip, PORT);
#pragma endregion

	protocol = new Threading(&socket);

	protocol->Run();
}