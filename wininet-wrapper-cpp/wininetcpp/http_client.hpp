#ifndef _HTTP_CLIENT_HPP_
#define _HTTP_CLIENT_HPP_

#include "http_request.hpp"

namespace wininetcpp
{
	class HttpClient
	{
	public:
		HttpClient(std::wstring base_address)
			: base_address(base_address)
			, session(nullptr)
			, connection(nullptr)
		{

			session = InternetOpen(_T("WinInet HTTP Async Session"), // User Agent
				INTERNET_OPEN_TYPE_PRECONFIG, // Preconfig or Proxy
				nullptr,  // proxy name
				nullptr, // proxy bypass, do not bypass any address
				INTERNET_FLAG_ASYNC); // 0 for Synchronous
		}

		virtual ~HttpClient()
		{
		}

		void AddHeader(const std::wstring& header)
		{
			headers.push_back(header + _T("\r\n"));
		}

		void SendAsync(const HttpRequest& request)
		{
			do
			{
				if (!session)
				{
					break;
				}

				InternetSetStatusCallback(session, OnCallBack);

				INTERNET_PORT server_port = INTERNET_DEFAULT_HTTP_PORT;
				connection = InternetConnect(session,
					base_address.c_str(), //Name of the server to connect to
					server_port, //HTTP (80) or HTTPS (443)
					nullptr, // Do not provide a user name for the server
					nullptr, // Do not provide a password for the server
					INTERNET_SERVICE_HTTP,
					0, // Do not provide any special flag
					(DWORD_PTR)this); // Provide the context to be
				// used during the callbacks

				if (!connection)
				{
					break;
				}
				
				const DWORD dwRequestFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;

				auto request_handle = HttpOpenRequest(connection,
					request.method().c_str(),
					request.uri(),
					nullptr, // Use default HTTP/1.1 as the version
					nullptr, // Do not provide any referrer
					nullptr, // Do not provide Accept types
					dwRequestFlags, //(0 or INTERNET_FLAG_SECURE) | 
									// INTERNET_FLAG_RELOAD | 
									// INTERNET_FLAG_NO_CACHE_WRITE
					(DWORD_PTR)this);

				for (const auto& header : headers)
				{
					const DWORD dwModifiers = HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD;
					if (!HttpAddRequestHeaders(request_handle,
						header.c_str(),
						(DWORD)header.length(),
						dwModifiers)
						)
					{
						break;
					}
				}


			} while (false);
		}

	private:
		static void CALLBACK OnCallBack(
			HINTERNET hInternet,
			__in DWORD_PTR dwContext,
			DWORD dwInternetStatus,
			__in_bcount(dwStatusInformationLength) LPVOID lpvStatusInformation,
			DWORD dwStatusInformationLength)
		{
			
		}

	private:
		std::wstring base_address;
		std::vector< std::wstring > headers;

		HINTERNET session;
		HINTERNET connection;

		std::wstring error_message;
	};
}
#endif