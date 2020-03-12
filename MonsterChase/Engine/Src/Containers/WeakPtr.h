#pragma once

namespace Containers
{
	struct PtrData;

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

		// Operators
		WeakPtr& operator=(const WeakPtr& i_weakPtr);
		explicit operator bool() const;

		// Utils
		unsigned long UseCount();
		unsigned long WeakCount();
		bool Expired();
		SmartPtr<T> Lock();
	};
}
