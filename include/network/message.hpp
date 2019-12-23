/*
** EPITECH PROJECT, 2019
** message
** File description:
** Network message structures
*/

#ifndef MESSAGE_HPP_BB8ZEWVR
#define MESSAGE_HPP_BB8ZEWVR

#include <iostream>
#include <functional>
#include <vector>
#include <cstring>

namespace Engine::Network
{
	enum MessageType {
		CONNECT,
		DISCONNECT,
		RELIABLE_MESSAGE,
		UNRELIABLE_MESSAGE,
		PING,
		PONG
	};

	struct MessageHeader {
		MessageType type;
		size_t payloadSize;
		int payloadType;
	};

	struct Message {
		MessageHeader header;
		std::vector<std::byte> payload;

		size_t getTotalSize() const
		{
			return sizeof(MessageHeader) + header.payloadSize;
		}

		std::vector<std::byte> getMessageBuffer() const
		{
			const auto headerSize = sizeof(this->header);
			auto buff = std::vector<std::byte>(this->getTotalSize());
			auto header = reinterpret_cast<char const *>(&this->header);

			std::memcpy(buff.data(), header, headerSize);
			std::memcpy(buff.data() + headerSize, this->payload.data(),
					this->header.payloadSize);
			return buff;
		}
	};

} /* Engine::Network */

#endif /* end of include guard: MESSAGE_HPP_BB8ZEWVR */
