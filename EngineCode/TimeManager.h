#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <map>
#include <string>


//! TimeManager class
/*
	Handles the management of the time in game.
*/
class TimeManager
{
public:
	//! Destructor.
	~TimeManager(void);

	//! Controls the time of the game.
	void RandomTime();

	//! Sets the fps of the game as you want.
	/*
		\param1: fps value to set
	*/
	void SetFPS(unsigned int _fps);

	//! Updates the time and manages the fps of the game.
	void UpdateTime();

	//! Creates a new timer with a name and duration.
	/*
		\param1: timer name to include it in _mTimerMap
		\param2: timer duration to include it in _mTimerMap
	*/
	void StartNewTimer(const std::string _name, unsigned int _duration);

	//! Checks whether the timer has expired or not.
	/*
		\param1: timer name from _mTimerMap
		\return: true or false value
	*/
	bool HasTimerExpired(const std::string _name);

	//! Erases a timer that has already expired.
	/*
		\param1: timer name to erase it from _mTimerMap
	*/
	void StopTimer(const std::string _name);

	//! Prints active timers state in console.
	void PrintActiveTimers();

	//! Get for _mDeltaTime
	unsigned int GetDeltaTime() const { return _mDeltaTime; };
	//! Get for _mFPS
	float GetFPS() { return _mFPS; };
	//! Get for _mMsFrame
	float GetMsPerFrame() { return _mMsFrame; };

	//! Gets Singleton instance.
	/*
		\return: Instance of TimeManager (Singleton pattern)
	*/
	static TimeManager* GetInstance();

protected:
	//! Constructor of an empty TimeManager.
	TimeManager(unsigned int fps);

private:
	unsigned int							_mFPS;					/*< FPS value */
	unsigned int							_mMsFrame;				/*< Miliseconds value per frame */
	unsigned int							_mDeltaTime;			/*< Deltatime between frames */
	unsigned int							_mLastTime;				/*< Last time value registered */
	unsigned int							_mCurrentTime;			/*< Current time value */
	std::map<std::string, unsigned int>		_mTimerMap;				/*< Map that stores timers */
	static TimeManager*						_pInstance;				/*< Singleton instance */
};

#endif

