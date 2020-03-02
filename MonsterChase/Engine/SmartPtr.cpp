#include "SmartPtr.h"

#include <cassert>

namespace Containers
{
#pragma region Constructor And Destructor
	template <class T>
	SmartPtr<T>::SmartPtr(const SmartPtr& i_smartPtr)
	{
		assert(i_smartPtr != nullptr); // Don't know if this is correct

		this->_objectPtr = i_smartPtr._objectPtr;
		this->_referenceCount = i_smartPtr._referenceCount;

		*this->_referenceCount += 1;
	}

	template <class T>
	template <class U>
	SmartPtr<T>::SmartPtr(const SmartPtr<U>& i_smartPtr)
	{
		assert(i_smartPtr != nullptr); // Don't know if this is correct

		this->_objectPtr = i_smartPtr._objectPtr;
		this->_referenceCount = i_smartPtr._referenceCount;

		*this->_referenceCount += 1;
	}

	template <class T>
	SmartPtr<T>::SmartPtr(T* i_objectPtr)
	{
		this->_objectPtr = i_objectPtr;
		this->_referenceCount = new long(1);
	}

	template <class T>
	SmartPtr<T>::~SmartPtr()
	{
		ReleaseReference();
	}

#pragma endregion

#pragma region Pointer Access

	template <class T>
	T& SmartPtr<T>::operator&()
	{
		assert(this->_objectPtr != nullptr);

		return *this->_objectPtr;
	}

	template <class T>
	T* SmartPtr<T>::operator->()
	{
		return this->_objectPtr;
	}

#pragma endregion

#pragma region Operators

	template <class T>
	SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& i_smartPtr)
	{
		if (&i_smartPtr == this)
		{
			return *this;
		}

		ReleaseReference();
		AcquireNewReference(i_smartPtr);

		return *this;
	}

#pragma endregion

#pragma region Utils

	template <class T>
	bool SmartPtr<T>::IsValid()
	{
		return this->_objectPtr != nullptr;
	}

#pragma endregion

#pragma region Reference Management

	template <class T>
	void SmartPtr<T>::AcquireNewReference(const SmartPtr& i_smartPtr)
	{
		assert(i_smartPtr != nullptr);

		this->_objectPtr = i_smartPtr._objectPtr;
		this->_referenceCount = i_smartPtr._referenceCount;

		*this->_referenceCount += 1;
	}

	template <class T>
	void SmartPtr<T>::ReleaseReference()
	{
		*this->_referenceCount -= 1;
		assert(*this->_referenceCount >= 0); // Might be wrong

		if (*this->_referenceCount == 0)
		{
			delete this->_referenceCount;
			delete this->_objectPtr;
		}
	}

#pragma endregion
}
