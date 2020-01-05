/*
** EPITECH PROJECT, 2019
** message_inbox
** File description:
** Thread safe incoming message queue
*/

#include "network/socket.hpp"
#include "network/message.hpp"

namespace Engine::Network
{
	void MessageInbox::addToInbox(Message &msg)
	{
		std::lock_guard<std::mutex> msgInsert(_msgMutex);

		_incomingMsg.push(msg);
	}

	std::optional<Message> MessageInbox::checkInbox()
	{
		if (!_incomingMsg.size()) {
			return {std::nullopt};
		}
		{
			std::lock_guard<std::mutex> msgReading(_msgMutex);
			auto msg = std::make_optional<Message>(_incomingMsg.front());
			_incomingMsg.pop();
			return msg;
		}
	}

} /* Engine::Network */
