#pragma once

namespace Containers
{
	class PtrData
	{
	public:
		unsigned long* referenceCount;
		unsigned long* weakCount;

		// Constructor and Destructor
		PtrData();
		~PtrData();

		// Smart Pointer Reference
		void AddSmartReference() const;
		void ReleaseSmartReference() const;

		// Weak Pointer Reference
		void AddWeakReference() const;
		void ReleaseWeakReference() const;
	};
}
