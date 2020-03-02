#pragma once

namespace Containers
{
	template <class T>
	class SmartPtr
	{
	private:
		T* _objectPtr;
		long* _referenceCount;

		// Reference Management
		void AcquireNewReference(const SmartPtr& i_smartPtr);
		void ReleaseReference();

	public:
		SmartPtr(T* i_objectPtr = nullptr);
		SmartPtr(const SmartPtr& i_smartPtr);
		~SmartPtr();

		template <class U>
		friend class SmartPtr<U>;

		template <class U>
		SmartPtr(const SmartPtr<U>& i_smartPtr);

		// Access Functions
		T& operator&();
		T* operator->();

		// Operators
		SmartPtr& operator=(const SmartPtr& i_smartPtr);

		// Utils
		bool IsValid();
	};
}
