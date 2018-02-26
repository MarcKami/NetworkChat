#include "Receptor.hpp"

void main() {

#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	vector<pair<string, string>> aMensajes;
#pragma endregion

	Receptor_Selection r(&aMensajes);
	thread t(r);

	//ESPERAR A QUE ACABE "T"
	t.join();
}