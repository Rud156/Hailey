#pragma once
#include <functional>

namespace Containers
{
	struct PtrData;

	template <class T>
	class SmartPtr
	{
	private:
		PtrData* _dataCounter;
		T* _objectPtr;
		std::function<void(T)> _customDeleter;

		// Reference Management
		void AcquireNewReference(const SmartPtr& i_smartPtr);
		void ReleaseReference();

	public:
		SmartPtr(T* i_objectPtr = nullptr);
		SmartPtr(const SmartPtr& i_smartPtr);
		SmartPtr(T* i_objectPtr, PtrData* i_dataCounter);
		~SmartPtr();

		// template <class U>
		// friend class SmartPtr<U>; // TODO: Check if this is actually required

		template <class U>
		SmartPtr(const SmartPtr<U>& i_smartPtr);

		// Access Functions
		T& operator&();
		T* operator->();

		// Operators
		SmartPtr& operator=(const SmartPtr& i_smartPtr);
		explicit operator bool() const;

		// Utils
		bool IsValid();
		void SetCustomDeleter(void i_function(T));
		std::function<void(T)> GetCustomDeleter();

		// Friends
		template <class D>
		friend class WeakPtr;
	};
}
