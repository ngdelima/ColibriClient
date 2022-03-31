#pragma once

#include"InputEvent.h"

class Listener
{
public:
	virtual ~Listener() {}
	virtual void onNotify(INPUT_EVENT _event) = 0;
};

class Publisher
{
public:
	virtual void addListener(Listener* _listener) = 0;
	virtual void notify(INPUT_EVENT _event) = 0;
};