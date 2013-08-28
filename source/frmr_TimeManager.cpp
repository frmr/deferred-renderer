#include "frmr_TimeManager.h"

void frmr::TimeManager::UpdateDeltaTime()
{
	deltaTime = (float) ( (float) elapsedTime / (float) timeBase );
}

void frmr::TimeManager::Start()
{
	timer.restart();
}

void frmr::TimeManager::Stop()
{
	elapsedTime = timer.restart().asMilliseconds();
	UpdateDeltaTime();
}

float frmr::TimeManager::GetDeltaTime() const
{
	return deltaTime;
}

int32_t frmr::TimeManager::GetElapsedTime() const
{
	return elapsedTime;
}

frmr::TimeManager::TimeManager()
	: timeBase( 4 ),
	  deltaTime( 1 ),
	  elapsedTime( 1 )
{
}

frmr::TimeManager::~TimeManager()
{
}
