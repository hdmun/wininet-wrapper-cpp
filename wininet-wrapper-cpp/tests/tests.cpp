#include "pch.h"
#include "CppUnitTest.h"
#include "http_client.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			wininetcpp::HttpClient client(_T("http://naver.com"));
			wininetcpp::HttpRequest request(wininetcpp::HttpMethod::Get, _T(""));

			client.SendAsync(request);
		}
	};
}
