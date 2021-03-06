#include "SmartPtr.h"
#include "PtrData.h"

#include <cassert>

namespace Containers
{
#pragma region Constructor And Destructor

	template <class T>
	SmartPtr<T>::SmartPtr(const SmartPtr& i_smartPtr)
	{
		this->_objectPtr = i_smartPtr._objectPtr;
		this->_dataCounter = i_smartPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddSmartReference();
		}
	}

	template <class T>
	SmartPtr<T>::SmartPtr(T* i_objectPtr, PtrData* i_dataCounter)
	{
		this->_objectPtr = i_objectPtr;
		this->_dataCounter = i_dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddSmartReference();
		}
	}

	template <class T>
	template <class U>
	SmartPtr<T>::SmartPtr(const SmartPtr<U>& i_smartPtr)
	{
		this->_objectPtr = reinterpret_cast<T*>(i_smartPtr._objectPtr);
		this->_dataCounter = i_smartPtr._dataCounter;
		this->_customDeleter = nullptr;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddSmartReference();
		}
	}

	template <class T>
	SmartPtr<T>::SmartPtr(T* i_objectPtr)
	{
		this->_customDeleter = nullptr;

		if (i_objectPtr == nullptr)
		{
			this->_objectPtr = nullptr;
			this->_dataCounter = nullptr;
			return;
		}

		this->_dataCounter = new PtrData();
		this->_dataCounter->AddSmartReference();

		this->_objectPtr = i_objectPtr;
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

	template <class T>
	SmartPtr<T>::operator bool() const
	{
		return this->_objectPtr != nullptr;
	}

	template <class T>
	template <class D>
	bool SmartPtr<T>::CompareBaseType()
	{
		if (dynamic_cast<D*>(this->_objectPtr))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

#pragma endregion

#pragma region Utils

	template <class T>
	bool SmartPtr<T>::IsValid()
	{
		return this->_objectPtr != nullptr;
	}

	template <class T>
	void SmartPtr<T>::SetCustomDeleter(std::function<void(T)> i_function)
	{
		this->_customDeleter = i_function;
	}

	template <class T>
	std::function<void(T)> SmartPtr<T>::GetCustomDeleter()
	{
		return this->_customDeleter;
	}

#pragma endregion

#pragma region Reference Management

	template <class T>
	void SmartPtr<T>::AcquireNewReference(const SmartPtr& i_smartPtr)
	{
		this->_objectPtr = i_smartPtr._objectPtr;
		this->_dataCounter = i_smartPtr._dataCounter;
		this->_customDeleter = nullptr;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddSmartReference();
		}
	}

	template <class T>
	void SmartPtr<T>::ReleaseReference()
	{
		if (this->_dataCounter == nullptr)
		{
			return;
		}

		this->_dataCounter->ReleaseSmartReference();

		if (this->_objectPtr && *this->_dataCounter->referenceCount == 0)
		{
			if (this->_customDeleter)
			{
				this->_customDeleter(*this->_objectPtr);
			}

			delete this->_objectPtr;
		}

		// Only delete when the weak count goes to zero
		if (*this->_dataCounter->weakCount == 0 && *this->_dataCounter->referenceCount == 0 && this->_dataCounter)
		{
			delete this->_dataCounter;
		}
	}

#pragma endregion
}
