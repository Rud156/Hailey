#include "WeakPtr.h"
#include "SmartPtr.h"
#include "PtrData.h"

#include <cassert>

namespace Containers
{
#pragma region Constructor And Destructor

	template <class T>
	WeakPtr<T>::WeakPtr()
	{
		this->_objectPtr = nullptr;
		this->_dataCounter = nullptr;
	}

	template <class T>
	WeakPtr<T>::WeakPtr(const WeakPtr<T>& i_weakPtr)
	{
		this->_objectPtr = i_weakPtr._objectPtr;
		this->_dataCounter = i_weakPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddWeakReference();
		}
	}

	template <class T>
	WeakPtr<T>::WeakPtr(const SmartPtr<T>& i_smartPtr)
	{
		this->_objectPtr = i_smartPtr._objectPtr;
		this->_dataCounter = i_smartPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddWeakReference();
		}
	}

	template <class T>
	WeakPtr<T>::~WeakPtr()
	{
		if (this->_dataCounter == nullptr)
		{
			return;
		}

		this->_dataCounter->ReleaseWeakReference();

		if (*this->_dataCounter->weakCount == 0 && *this->_dataCounter->referenceCount == 0 && this->_dataCounter)
		{
			delete this->_dataCounter;
		}
	}

	template <class T>
	template <class U>
	WeakPtr<T>::WeakPtr(const SmartPtr<U>& i_smartPtr)
	{
		this->_objectPtr = reinterpret_cast<T*>(i_smartPtr._objectPtr);
		this->_dataCounter = i_smartPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddWeakReference();
		}
	}

#pragma endregion

#pragma region Operator

	template <class T>
	template <class U>
	WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<U>& i_weakPtr)
	{
		if (&i_weakPtr == this)
		{
			return *this;
		}

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->ReleaseWeakReference();
		}

		this->_objectPtr = reinterpret_cast<T*>(i_weakPtr._objectPtr);
		this->_dataCounter = i_weakPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddWeakReference();
		}

		return *this;
	}

	template <class T>
	WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& i_weakPtr)
	{
		if (&i_weakPtr == this)
		{
			return *this;
		}

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->ReleaseWeakReference();
		}

		this->_objectPtr = i_weakPtr._objectPtr;
		this->_dataCounter = i_weakPtr._dataCounter;

		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->AddWeakReference();
		}

		return *this;
	}

	template <class T>
	WeakPtr<T>::operator bool() const
	{
		return this->_objectPtr != nullptr;
	}

#pragma endregion

#pragma region Utils

	template <class T>
	unsigned long WeakPtr<T>::UseCount()
	{
		if (this->_dataCounter == nullptr)
		{
			return 0;
		}

		return *this->_dataCounter->referenceCount;
	}

	template <class T>
	unsigned long WeakPtr<T>::WeakCount()
	{
		if (this->_dataCounter == nullptr)
		{
			return 0;
		}

		return *this->_dataCounter->weakCount;
	}

	template <class T>
	bool WeakPtr<T>::Expired()
	{
		if (this->_dataCounter == nullptr)
		{
			return true;
		}

		if (UseCount() == 0)
		{
			return true;
		}

		// This should not happen at any cost. This means that the implementation is wrong
		assert(this->_objectPtr != nullptr);
		return false;
	}

	template <class T>
	SmartPtr<T> WeakPtr<T>::Lock()
	{
		if (Expired())
		{
			return SmartPtr<T>(nullptr);
		}
		else
		{
			return SmartPtr<T>(this->_objectPtr, this->_dataCounter);
		}
	}

	template <class T>
	void WeakPtr<T>::ClearWeakRef()
	{
		this->_objectPtr = nullptr;
		if (this->_dataCounter != nullptr)
		{
			this->_dataCounter->ReleaseWeakReference();
		}

		this->_dataCounter = nullptr;
	}

#pragma endregion
}
