#pragma once

template <typename T>
class IDynamicStructure
{
public:
	virtual bool add(T& t) = 0;
	virtual bool del(T& t) = 0;
	virtual bool search(T& t) = 0;
	virtual bool print(T& t) = 0;
};