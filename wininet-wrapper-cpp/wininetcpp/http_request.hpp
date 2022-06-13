#ifndef _HTTP_REQUEST_HPP_
#define _HTTP_REQUEST_HPP_

namespace wininetcpp
{
	class HttpMethod
	{
	public:
		enum Method
		{
			Get,
			Post,
			Put,
			Patch,
			Delete,
		};

		HttpMethod() = default;

		constexpr HttpMethod(Method method)
			: method(method)
		{
		}

		constexpr const TCHAR* c_str() {
			switch (method)
			{
			case Method::Get: return _T("GET");
			case Method::Post: return _T("POST");
			case Method::Put: return _T("PUT");
			case Method::Patch: return _T("PATCH");
			case Method::Delete: return _T("DELETE");
			default:
				return nullptr;
			}
		}

	private:
		Method method;
	};


	class HttpRequest
	{
	public:
		HttpRequest(HttpMethod method, std::wstring uri)
			: method_(method)
			, uri_(uri)
		{
		}

		virtual ~HttpRequest() {}

		HttpMethod method() const { return method_; }
		const TCHAR* uri() const { return uri_.c_str(); }

	private:
		HttpMethod method_;
		std::wstring uri_;
	};
}

#endif