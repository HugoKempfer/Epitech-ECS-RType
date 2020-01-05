/*
** EPITECH PROJECT, 2019
** serialize
** File description:
** Opaque class type to hold literal serialized objects
*/

#ifndef SERIALIZE_HPP_8AQHEJUC
#define SERIALIZE_HPP_8AQHEJUC

#include <iostream>
#include <vector>
#include <type_traits>
#include <memory>
#include <sstream>
#include <cassert>
#include <unordered_map>
#include <functional>

#include "engine/concepts_impl.hpp"
#include "engine/uuid.hpp"
#include "network/message.hpp"

namespace Engine::Network
{
	/**
	 * @brief Opaque type containing a serialized object
	 */
	template <typename UUID> requires std::is_enum<UUID>::value
	class Archive
	{
		using byte = char *;

	public:
		Archive() = delete;
		Archive(UUID uuid, size_t size, void const * const payload) :
			typeUUID(uuid), size(size)
		{
			this->encode(payload);
		}

		Archive(Engine::Network::Message &msg) :
			typeUUID(msg.header.type), size(msg.header.payloadSize)
		{
			this->encode(msg.payload.data());
		}

		virtual ~Archive() = default;

		/**
		 * @brief Try to deserialize a class by providing a end type
		 *
		 * @return Deserialized version of the requested type
		 */
		template <typename T> requires serializable<T>
		T decode()
		{
			if (sizeof(T) != size) {
				throw std::runtime_error("POD type mismatch");
			}
			std::istream &buff = this->_stream;
			T payload;
			buff.read(reinterpret_cast<byte const>(&payload), size);
			return payload;
		}

		Message toMessage() const
		{
			return {
				{MessageType::UNRELIABLE_MESSAGE, this->size, this->typeUUID},
				{_stream}
			};
		}

		const UUID typeUUID;
		const size_t size;
	protected:
		std::stringstream _stream;

	private:
		void encode(void const * const buff)
		{
			_stream.write(reinterpret_cast<const char * const>(buff), size);
		}
	};

	/**
	 * @brief Container which handle the (De)serialization for a set of class
	 */
	template <typename UUID> requires std::is_enum<UUID>::value
	class SerializationFactory
	{
	public:
		SerializationFactory() = delete;
		SerializationFactory(UUIDContext &ctx) : _uuidCtx(ctx) {}
		SerializationFactory(UUIDContext &ctx,
				std::function<void(SerializationFactory<UUID> &)> initializator)
			: _uuidCtx(ctx)
		{
			initializator(*this);
		}

		~SerializationFactory() = default;

		/**
		 * @brief Give to the factory the capability of handling the provided class
		 *
		 * @param id POD-Class UUID obtained from world uuidCtx
		 */
		template <typename T> requires serializable<T>
		void registerMember(UUID id)
		{
			const int64_t typeId = _uuidCtx.get<T>();

			assert(!_deserializeFrom.contains(id));
			assert(!_serializeFrom.contains(typeId));
			_serializeFrom.insert({typeId, {id, sizeof(T)}});
			_deserializeFrom.insert({id, {typeId, sizeof(T)}});
		}

		/**
		 * @brief Serialize a registered class
		 *
		 * @param payload registered class
		 *
		 * @return Archive containing the serialized object
		 */
		template <typename T> requires serializable<T>
		Archive<UUID> serialize(T const &payload) const
		{
			try {
				auto &type = _serializeFrom.at(_uuidCtx.get<T>());
				return this->createArchive(type.first, type.second,
						reinterpret_cast<void const * const>(&payload));
			} catch (std::out_of_range &e) {
				throw std::runtime_error("Requested type not handled by factory");
			}
		}

		int64_t getArchiveTypeUUID(Archive<UUID> const &ar) const
		{
			return _deserializeFrom.at(ar.typeUUID).first;
		}

	private:
		Archive<UUID> createArchive(UUID uuid, size_t size, void const * const payload) const
		{
			return Archive<UUID>(uuid, size, payload);
		}

		std::unordered_map<UUID, std::pair<int64_t, size_t>> _deserializeFrom;
		std::unordered_map<int64_t, std::pair<UUID, size_t>> _serializeFrom;
		UUIDContext &_uuidCtx;
	};

} /* Engine::Network */

#endif /* end of include guard: SERIALIZE_HPP_8AQHEJUC */
