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
		*this->referenceCount += 1;
	}

	void PtrData::ReleaseSmartReference() const
	{
		*this->referenceCount -= 1;
	}

#pragma endregion

#pragma region Weak Pointer Reference

	void PtrData::AddWeakReference() const
	{
		*this->weakCount += 1;
	}

	void PtrData::ReleaseWeakReference() const
	{
		*this->weakCount -= 1;
	}

#pragma endregion
}
