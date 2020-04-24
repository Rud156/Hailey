#include "PtrData.h"

namespace Containers
{
	PtrData::PtrData()
	{
		this->referenceCount = new unsigned long(0);
		this->weakCount = new unsigned long(0);
	}

	PtrData::~PtrData()
	{
		delete this->referenceCount;
		delete this->weakCount;
	}

#pragma region Smart Pointer Reference

	void PtrData::AddSmartReference() const
	{
		unsigned long x = *(this->referenceCount);
		x += 1;
		*this->referenceCount = x;
	}

	void PtrData::ReleaseSmartReference() const
	{
		unsigned long x = *(this->referenceCount);
		x -= 1;
		*this->referenceCount = x;
	}

#pragma endregion

#pragma region Weak Pointer Reference

	void PtrData::AddWeakReference() const
	{
		unsigned long x = *(this->weakCount);
		x += 1;
		*this->weakCount = x;
	}

	void PtrData::ReleaseWeakReference() const
	{
		unsigned long x = *(this->weakCount);
		x -= 1;
		*this->weakCount = x;
	}

#pragma endregion
}
