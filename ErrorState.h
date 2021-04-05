/***************************
Name: Jaron Bloom
Email: jbloom5@myseneca.ca
Section: C
**************************/

#include<iostream>
#ifndef ErrorState_H
#define ErrorState_H
namespace AMA {
	class ErrorState {
		char* mess;

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;
	};
	std::ostream& operator<< (std::ostream&, const ErrorState&);
}
#endif // !ErrorState_H

