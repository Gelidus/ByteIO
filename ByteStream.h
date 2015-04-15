//
// Created by gelidus on 10.4.2015.
//

#ifndef _PROJECT_BYTESTREAM_H_
#define _PROJECT_BYTESTREAM_H_

#include <iostream>
#include <string>
#include <deque>

enum class Endianness {
	BigEndian, LittleEndian
};

using Byte = unsigned char;

class ByteStream {

protected:
	Endianness endianness;
	Buffer streamBuffer;

public:
	ByteStream();
	ByteStream(Byte *input);
	~ByteStream();

public: // API


protected: // Helpers
	/**
	 * Reads specified ammount of bytes from the streamBuffer
	 *
	 * @param length specifies number of bytes to return
	 */
	Byte *read(unsigned int length);

	/**
	 * Writes specified bytes and ammount to the streamBuffer (top of it)
	 */
	void write(Byte *bytes, unsigned int length);

protected:
	using Buffer = std::deque<Byte>;

};


#endif //_PROJECT_BYTESTREAM_H_
