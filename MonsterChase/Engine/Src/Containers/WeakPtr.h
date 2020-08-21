#pragma once

namespace Containers
{
	class PtrData;

	template <class D>
	class SmartPtr;

	template <class T>
	class WeakPtr
	{
	private:
		PtrData* _dataCounter;
		T* _objectPtr;

	public:
		WeakPtr();
		WeakPtr(const WeakPtr<T>& i_weakPtr);
		WeakPtr(const SmartPtr<T>& i_smartPtr);
		~WeakPtr();

		template <class U>
		WeakPtr(const SmartPtr<U>& i_smartPtr);

		// Operators
		template <class U>
		WeakPtr& operator=(const WeakPtr<U>& i_weakPtr);
		WeakPtr& operator=(const WeakPtr& i_weakPtr);
		explicit operator bool() const;

		// Utils
		unsigned long UseCount();
		unsigned long WeakCount();
		bool Expired();
		SmartPtr<T> Lock();
		void ClearWeakRef();
	};
}
