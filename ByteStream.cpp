//
// Created by gelidus on 10.4.2015.
//

#include "ByteStream.h"

using namespace std;

ByteStream::ByteStream() { }

ByteStream::ByteStream(Byte *input, unsigned int length) {
	this->write(input, length);
}

ByteStream::~ByteStream() { }


void ByteStream::write(const int &value) {
	const Byte *bytes = static_cast<const Byte*>(static_cast<const void*>(&value));

	this->write(bytes, 4);
}

void ByteStream::write(const short &value) {
	const Byte *bytes = static_cast<const Byte*>(static_cast<const void*>(&value));

	this->write(bytes, 2);
}


void ByteStream::write(const std::string &value) {
	const Byte *bytes = (const Byte*)value.c_str();

	this->write(bytes, static_cast<unsigned int>(value.length()) + 1);
}

void ByteStream::read(int &value) {
	shared_ptr<Byte> bytes = this->read(4);

	value = bytes.get()[0] | bytes.get()[1] << 8 | bytes.get()[2] << 16 | bytes.get()[3] << 24;
}

void ByteStream::read(short &value) {
	shared_ptr<Byte> bytes = this->read(2);

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

shared_ptr<Byte> ByteStream::read(unsigned int length) {
	auto bytes = new Byte[length];

	for (int i = 0; i < length; i++) {
		bytes[i] = this->streamBuffer.front();
		this->streamBuffer.pop_front();
	}

	return shared_ptr<Byte>(bytes);
}

void ByteStream::write(const Byte *bytes, unsigned int length) {
	for (int i = 0; i < length; i++) {
		this->streamBuffer.push_back(bytes[i]);
	}
}
