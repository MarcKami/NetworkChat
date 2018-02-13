#include "Threading.h"

Threading::Threading(sf::TcpSocket* socket, vector<pair<string, originText>>* aMensajes) {
	r = Receptor(socket, aMensajes);
}

Threading::~Threading() {

}

void Threading::Enter() {
	thread t(r);
}

void Threading::Update() {

}

void Threading::Exit() {

}