//
// Created by gelidus on 10.4.2015.
//

#include "ByteStream.h"

using namespace std;

ByteStream::ByteStream() { }

ByteStream::ByteStream(Byte *input, unsigned int length) {
	this->write(input, length);
}

ByteStream::~ByteStream() {

}

shared_ptr<Byte> ByteStream::read(unsigned int length) {
	auto bytes = new Byte[length];

	for (int i = 0; i < length; i++) {
		bytes[i] = this->streamBuffer.front();
		this->streamBuffer.pop_front();
	}

	return shared_ptr<Byte>(bytes);
}

void ByteStream::write(Byte *bytes, unsigned int length) {
	for (int i = 0; i < length; i++) {
		this->streamBuffer.push_back(bytes[i]);
	}
}
