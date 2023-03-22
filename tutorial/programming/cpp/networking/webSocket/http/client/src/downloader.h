#ifndef DOWNLOADER 
#define DOWNLOADER 

#include "client.h"

enum FILE_ENCODING {length, chunked, connection, def};

class Downloader : public Client
{
	public:
		Downloader();
			bool download(std::string url);
		~Downloader();

	private:
		//For show.............
		long fileSizeShow = 0;
		int _byte_recv = 0;
		int _byte_write = 0;
		long totalDownSize = 0; 
		long _fileSize = 0;

		char* body;
		size_t index;

		std::string _header;
		std::string _fileType;
		FILE_ENCODING _encoding;
		std::ofstream output;

		//Functions.................
		inline void content_length();
		inline void chunked();
		inline void cleanUp();

		//Parser function......
		inline void parse_url(std::string url, std::string &hostname, 
								std::string &port, std::string &path, std::string &protocol);
		void parseHeader(std::string header, std::string &fileType, 
				long &fileSize, FILE_ENCODING &encoding);
};
#endif

