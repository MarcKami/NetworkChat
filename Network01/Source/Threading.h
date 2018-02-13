#include "Protocol.h"

class Threading : public Protocol {
public:
	Threading();
	~Threading();

	void Enter();
	void Update();
	void Exit();

private:

};
