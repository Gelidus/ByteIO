//
// Created by gelidus on 10.4.2015.
//

#include "ByteStream.h"

using namespace std;

ByteStream::ByteStream() { }

ByteStream::ByteStream(Byte *input, unsigned int length) {
	this->writeBytes(input, length);
}

ByteStream::~ByteStream() { }

void ByteStream::write(const char &value) {
	this->streamBuffer.push_back(static_cast<const unsigned char>(value));
}

void ByteStream::write(const unsigned char &value) {
	this->streamBuffer.push_back(value);
}

void ByteStream::write(const int &value) {
	const Byte *bytes = static_cast<const Byte*>(static_cast<const void*>(&value));

	this->writeBytes(bytes, 4);
}

void ByteStream::write(const unsigned int &value) {
	this->write(static_cast<const int>(value));
}

void ByteStream::write(const short &value) {
	const Byte *bytes = static_cast<const Byte*>(static_cast<const void*>(&value));

	this->writeBytes(bytes, 2);
}

void ByteStream::write(const unsigned short &value) {
	this->write(static_cast<const short>(value));
}

void ByteStream::write(const std::string &value) {
	const Byte *bytes = (const Byte*)value.c_str();

	this->writeBytes(bytes, static_cast<unsigned int>(value.length()) + 1);
}

void ByteStream::write(const long long &value) {
	const Byte *bytes = static_cast<const Byte*>(static_cast<const void*>(&value));

	this->writeBytes(bytes, 8);
}

void ByteStream::write(const unsigned long long &value) {
	this->write(static_cast<const long long>(value));
}

void ByteStream::read(char &value) {
	value = static_cast<char>(this->streamBuffer.front());
	this->streamBuffer.pop_front();
}

void ByteStream::read(unsigned char &value) {
	value = this->streamBuffer.front();
	this->streamBuffer.pop_front();
}

void ByteStream::read(int &value) {
	shared_ptr<Byte> bytes = this->readBytes(4);

	value = bytes.get()[0] | bytes.get()[1] << 8 | bytes.get()[2] << 16 | bytes.get()[3] << 24;
}

void ByteStream::read(unsigned int &value) {
	shared_ptr<Byte> bytes = this->readBytes(4);

	value = bytes.get()[0] | bytes.get()[1] << 8 | bytes.get()[2] << 16 | bytes.get()[3] << 24;
}

void ByteStream::read(short &value) {
	shared_ptr<Byte> bytes = this->readBytes(2);

	value = bytes.get()[0] | bytes.get()[1] << 8;
}

void ByteStream::read(unsigned short &value) {
	shared_ptr<Byte> bytes = this->readBytes(2);

	value = bytes.get()[0] | bytes.get()[1] << 8;
}

void ByteStream::read(std::string &value) {
	Byte current;
	value = ""; // reset string value

	do {
		current = this->streamBuffer.front();
		this->streamBuffer.pop_front();

		if (current == '\0') {
			break;
		}

		value += current;

	} while (this->streamBuffer.size() > 0);
}


void ByteStream::read(long long &value) {
	shared_ptr<Byte> bytes = this->readBytes(8);

	value = bytes.get()[0] | bytes.get()[1] << 8 | bytes.get()[2] << 16 | bytes.get()[3] << 24 |
			bytes.get()[4] << 32 | bytes.get()[5] << 40 | bytes.get()[6] << 48 | bytes.get()[7] << 56;
}

void ByteStream::read(unsigned long long &value) {
	shared_ptr<Byte> bytes = this->readBytes(8);

	value = bytes.get()[0] | bytes.get()[1] << 8 | bytes.get()[2] << 16 | bytes.get()[3] << 24 |
					bytes.get()[4] << 32 | bytes.get()[5] << 40 | bytes.get()[6] << 48 | bytes.get()[7] << 56;
}

shared_ptr<Byte> ByteStream::readBytes(unsigned int length) {
	auto bytes = new Byte[length];

	for (int i = 0; i < length; i++) {
		bytes[i] = this->streamBuffer.front();
		this->streamBuffer.pop_front();
	}

	return shared_ptr<Byte>(bytes);
}

void ByteStream::writeBytes(const Byte *bytes, unsigned int length) {
	for (int i = 0; i < length; i++) {
		this->streamBuffer.push_back(bytes[i]);
	}
}
