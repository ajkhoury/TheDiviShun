#pragma once

#include <string>

enum eVarType
{
	VAR_TYPE_UNKNOWN = -1,
	VAR_TYPE_BOOL,
	VAR_TYPE_INT,
	VAR_TYPE_FLOAT,
	VAR_TYPE_STRING
};

class CVar
{
public:
	CVar() : type(VAR_TYPE_UNKNOWN) { memset(&val, 0, 4); }

	union ValueUnion
	{
		bool b;
		int i;
		float fl;
		char* str;
	};

protected:
	eVarType type;
	ValueUnion val;
};

class CVarBool : public CVar
{
public:
	CVarBool() {
		type = VAR_TYPE_BOOL;
		val.b = false;
	}

	CVarBool(bool bBool) {
		type = VAR_TYPE_BOOL;
		val.b = bBool;
	}

	inline bool operator==(const bool& rhs)	const { return  (val.b == rhs); }
	inline bool operator!=(const bool& rhs)	const { return !(val.b == rhs); }
	inline bool operator==(CVarBool& rhs)	const { return  (val.b == rhs.Get()); }
	inline bool operator!=(CVarBool& rhs)	const { return !(val.b == rhs.Get()); }
	inline operator bool()					const { return val.b == true; }

	inline bool operator=(const bool& rhs) { return val.b = rhs; }

	void Toggle() { val.b = !val.b; };

	void Set(bool bBool) { val.b = bBool; }
	bool Get() { return val.b; }
};


class CVarInt : public CVar
{
public:
	CVarInt() {
		type = VAR_TYPE_INT;
		val.i = 0;
	}

	CVarInt(int iInt) {
		type = VAR_TYPE_INT;
		val.i = iInt;
	}

	void Increment(int iAmount) {
		val.i += iAmount;
	}

	void Decrement(int iAmount) {
		val.i -= iAmount;
	}

	inline bool operator==(const int& rhs)	const { return  (val.i == rhs); }
	inline bool operator!=(const int& rhs)	const { return !(val.i == rhs); }
	inline bool operator==(CVarInt& rhs)	const { return  (val.i == rhs.Get()); }
	inline bool operator!=(CVarInt& rhs)	const { return !(val.i == rhs.Get()); }
	inline int  operator=(const int& rhs) { val.i = rhs; }

	void Set(int iInt) { val.i = iInt; }
	int Get() { return val.i; }
};

class CVarFloat : public CVar
{
public:
	CVarFloat() {
		type = VAR_TYPE_FLOAT;
		val.fl = 0.0f;
	}

	CVarFloat(float flFloat) {
		type = VAR_TYPE_FLOAT;
		val.fl = flFloat;
	}

	void Increment(float flAmount) {
		val.fl += flAmount;
	}

	void Decrement(float flAmount) {
		val.fl -= flAmount;
	}

	inline float operator+(const float& rhs)const {  return (val.fl + rhs); }
	inline CVarFloat& operator+=(const float& rhs) { val.fl += rhs; return *this; }
	inline CVarFloat& operator-=(const float& rhs) { val.fl -= rhs; return *this; }
	inline CVarFloat& operator=(const float& rhs) { val.fl = rhs; return *this; }
	inline operator float()					const { return val.fl; }

	inline bool operator==(const float& rhs)const { return  (val.fl == rhs); }
	inline bool operator!=(const float& rhs)const { return !(val.fl == rhs); }
	inline bool operator==(CVarFloat& rhs)	const { return  (val.fl == rhs.Get()); }
	inline bool operator!=(CVarFloat& rhs)	const { return !(val.fl == rhs.Get()); }

	void Set(float flFloat) { val.fl = flFloat; }
	float Get() { return val.fl; }
};

class CVarString : public CVar
{
public:
	CVarString() {
		type = VAR_TYPE_STRING;
		val.str = nullptr;
	}

	CVarString(char* pStr) {
		type = VAR_TYPE_STRING;
		val.str = pStr;
	}

	void Set(char* pStr) { val.str = pStr; }
	char* Get() { return val.str; }
};

struct CVars
{
	CVars()
	{
		varFireRate.Set(2080.0f);
		varReloadTime.Set(10.0f);
	}

	CVarFloat varFireRate;
	CVarFloat varReloadTime;
	CVarFloat varMovementSpeed;

	CVarBool varGlow;
	CVarBool varHealth;
	CVarBool varName;
	CVarBool varSkeleton;
	CVarBool varBoxes;
	CVarBool varHitbox;
	CVarBool varAABB;

	CVarBool varAimbot;
	CVarBool varNoVisRecoil;
	CVarBool varNoClipCamera;

};

extern CVars gVars;