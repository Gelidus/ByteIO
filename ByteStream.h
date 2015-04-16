//
// Created by gelidus on 10.4.2015.
//

#ifndef _PROJECT_BYTESTREAM_H_
#define _PROJECT_BYTESTREAM_H_

#include <iostream>
#include <string>
#include <deque>

#include <memory>

enum class Endianness {
	BigEndian, LittleEndian
};

using Byte = unsigned char;
using Buffer = std::deque<Byte>;

class ByteStream {

protected:
	Endianness endianness = Endianness::LittleEndian;
	Buffer streamBuffer;

public:
	ByteStream();
	ByteStream(Byte *input, unsigned int length);
	~ByteStream();

public: // API

	/**
	 * Writes specified int value into the stream
	 *
	 * @param value to be written
	 */
	void write(const int &value);
	void write(const short &value);
	void write(const std::string &value);

	/**
	 * Reads int value from stream
	 *
	 * @param value to save into
	 */
	void read(int &value);
	void read(short &value);
	void read(std::string &value);

	/**
	 * Defines overloaded stream operator << for writing
	 */
	template <typename T>
	ByteStream& operator << (T &value) {
		this->write(value);
		return *this;
	}

	/**
	 * Defines overloaded stream operator >> for reading
	 */
	template <typename T>
	ByteStream& operator >> (T &value) {
		this->read(value);
		return *this;
	}

public: // Helpers
	/**
	 * Reads specified ammount of bytes from the streamBuffer
	 *
	 * @param length specifies number of bytes to return
	 */
	std::shared_ptr<Byte> read(unsigned int length);

	/**
	 * Writes specified bytes and ammount to the streamBuffer (top of it)
	 *
	 * @param bytes array of bytes to write
	 * @oaram length of bytes given
	 */
	void write(const Byte *bytes, unsigned int length);
};


#endif //_PROJECT_BYTESTREAM_H_
