//
// basic_datagram_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP
#define BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
# include <boost/asio/datagram_socket_service.hpp>
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)

#include <boost/asio/detail/push_options.hpp>

namespace lslboost {
namespace asio {

/// Provides datagram-oriented socket functionality.
/**
 * The basic_datagram_socket class template provides asynchronous and blocking
 * datagram-oriented socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Protocol
    BOOST_ASIO_SVC_TPARAM_DEF1(= datagram_socket_service<Protocol>)>
class basic_datagram_socket
  : public basic_socket<Protocol BOOST_ASIO_SVC_TARG>
{
public:
  /// The native representation of a socket.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename basic_socket<
    Protocol BOOST_ASIO_SVC_TARG>::native_handle_type native_handle_type;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// Construct a basic_datagram_socket without opening it.
  /**
   * This constructor creates a datagram socket without opening it. The open()
   * function must be called before data can be sent or received on the socket.
   *
   * @param io_context The io_context object that the datagram socket will use
   * to dispatch handlers for any asynchronous operations performed on the
   * socket.
   */
  explicit basic_datagram_socket(lslboost::asio::io_context& io_context)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(io_context)
  {
  }

  /// Construct and open a basic_datagram_socket.
  /**
   * This constructor creates and opens a datagram socket.
   *
   * @param io_context The io_context object that the datagram socket will use
   * to dispatch handlers for any asynchronous operations performed on the
   * socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(lslboost::asio::io_context& io_context,
      const protocol_type& protocol)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(io_context, protocol)
  {
  }

  /// Construct a basic_datagram_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a datagram socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param io_context The io_context object that the datagram socket will use
   * to dispatch handlers for any asynchronous operations performed on the
   * socket.
   *
   * @param endpoint An endpoint on the local machine to which the datagram
   * socket will be bound.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(lslboost::asio::io_context& io_context,
      const endpoint_type& endpoint)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(io_context, endpoint)
  {
  }

  /// Construct a basic_datagram_socket on an existing native socket.
  /**
   * This constructor creates a datagram socket object to hold an existing
   * native socket.
   *
   * @param io_context The io_context object that the datagram socket will use
   * to dispatch handlers for any asynchronous operations performed on the
   * socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   */
  basic_datagram_socket(lslboost::asio::io_context& io_context,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(
        io_context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_datagram_socket from another.
  /**
   * This constructor moves a datagram socket from one object to another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(io_context&) constructor.
   */
  basic_datagram_socket(basic_datagram_socket&& other)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(std::move(other))
  {
  }

  /// Move-assign a basic_datagram_socket from another.
  /**
   * This assignment operator moves a datagram socket from one object to
   * another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(io_context&) constructor.
   */
  basic_datagram_socket& operator=(basic_datagram_socket&& other)
  {
    basic_socket<Protocol BOOST_ASIO_SVC_TARG>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_datagram_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a datagram socket from one object to another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(io_context&) constructor.
   */
  template <typename Protocol1 BOOST_ASIO_SVC_TPARAM1>
  basic_datagram_socket(
      basic_datagram_socket<Protocol1 BOOST_ASIO_SVC_TARG1>&& other,
      typename enable_if<is_convertible<Protocol1, Protocol>::value>::type* = 0)
    : basic_socket<Protocol BOOST_ASIO_SVC_TARG>(std::move(other))
  {
  }

  /// Move-assign a basic_datagram_socket from a socket of another protocol
  /// type.
  /**
   * This assignment operator moves a datagram socket from one object to
   * another.
   *
   * @param other The other basic_datagram_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_datagram_socket(io_context&) constructor.
   */
  template <typename Protocol1 BOOST_ASIO_SVC_TPARAM1>
  typename enable_if<is_convertible<Protocol1, Protocol>::value,
      basic_datagram_socket>::type& operator=(
        basic_datagram_socket<Protocol1 BOOST_ASIO_SVC_TARG1>&& other)
  {
    basic_socket<Protocol BOOST_ASIO_SVC_TARG>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the socket.
  /**
   * This function destroys the socket, cancelling any outstanding asynchronous
   * operations associated with the socket as if by calling @c cancel.
   */
  ~basic_datagram_socket()
  {
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One ore more data buffers to be sent on the socket.
   *
   * @returns The number of bytes sent.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code socket.send(lslboost::asio::buffer(data, size)); @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().send(
        this->get_implementation(), buffers, 0, ec);
    lslboost::asio::detail::throw_error(ec, "send");
    return s;
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One ore more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().send(
        this->get_implementation(), buffers, flags, ec);
    lslboost::asio::detail::throw_error(ec, "send");
    return s;
  }

  /// Send some data on a connected socket.
  /**
   * This function is used to send data on the datagram socket. The function
   * call will block until the data has been sent successfully or an error
   * occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent.
   *
   * @note The send operation can only be used with a connected socket. Use
   * the send_to function to send data on an unconnected datagram socket.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, lslboost::system::error_code& ec)
  {
    return this->get_service().send(
        this->get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous send on a connected socket.
  /**
   * This function is used to asynchronously send data on the datagram socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected datagram
   * socket.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(lslboost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
      void (lslboost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a WriteHandler.
    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_send(this->get_implementation(),
        buffers, 0, BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<WriteHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_send(this->get_implementation(),
        buffers, 0, init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Start an asynchronous send on a connected socket.
  /**
   * This function is used to asynchronously send data on the datagram socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @note The async_send operation can only be used with a connected socket.
   * Use the async_send_to function to send data on an unconnected datagram
   * socket.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
      void (lslboost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a WriteHandler.
    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_send(this->get_implementation(),
        buffers, flags, BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<WriteHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_send(this->get_implementation(),
        buffers, flags, init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @returns The number of bytes sent.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * lslboost::asio::ip::udp::endpoint destination(
   *     lslboost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.send_to(lslboost::asio::buffer(data, size), destination);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().send_to(
        this->get_implementation(), buffers, destination, 0, ec);
    lslboost::asio::detail::throw_error(ec, "send_to");
    return s;
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().send_to(
        this->get_implementation(), buffers, destination, flags, ec);
    lslboost::asio::detail::throw_error(ec, "send_to");
    return s;
  }

  /// Send a datagram to the specified endpoint.
  /**
   * This function is used to send a datagram to the specified remote endpoint.
   * The function call will block until the data has been sent successfully or
   * an error occurs.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   *
   * @param destination The remote endpoint to which the data will be sent.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent.
   */
  template <typename ConstBufferSequence>
  std::size_t send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      lslboost::system::error_code& ec)
  {
    return this->get_service().send_to(this->get_implementation(),
        buffers, destination, flags, ec);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send a datagram to the specified
   * remote endpoint. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * lslboost::asio::ip::udp::endpoint destination(
   *     lslboost::asio::ip::address::from_string("1.2.3.4"), 12345);
   * socket.async_send_to(
   *     lslboost::asio::buffer(data, size), destination, handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
      void (lslboost::system::error_code, std::size_t))
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a WriteHandler.
    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_send_to(
        this->get_implementation(), buffers, destination, 0,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<WriteHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_send_to(
        this->get_implementation(), buffers, destination, 0,
        init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send a datagram to the specified
   * remote endpoint. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent to the remote endpoint.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param destination The remote endpoint to which the data will be sent.
   * Copies will be made of the endpoint as required.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,
      void (lslboost::system::error_code, std::size_t))
  async_send_to(const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a WriteHandler.
    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_send_to(
        this->get_implementation(), buffers, destination, flags,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<WriteHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_send_to(
        this->get_implementation(), buffers, destination, flags,
        init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @returns The number of bytes received.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code socket.receive(lslboost::asio::buffer(data, size)); @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().receive(
        this->get_implementation(), buffers, 0, ec);
    lslboost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().receive(
        this->get_implementation(), buffers, flags, ec);
    lslboost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the datagram socket. The function
   * call will block until data has been received successfully or an error
   * occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received.
   *
   * @note The receive operation can only be used with a connected socket. Use
   * the receive_from function to receive data on an unconnected datagram
   * socket.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags, lslboost::system::error_code& ec)
  {
    return this->get_service().receive(
        this->get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous receive on a connected socket.
  /**
   * This function is used to asynchronously receive data from the datagram
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @note The async_receive operation can only be used with a connected socket.
   * Use the async_receive_from function to receive data on an unconnected
   * datagram socket.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(lslboost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
      void (lslboost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a ReadHandler.
    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_receive(this->get_implementation(),
        buffers, 0, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<ReadHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_receive(this->get_implementation(),
        buffers, 0, init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Start an asynchronous receive on a connected socket.
  /**
   * This function is used to asynchronously receive data from the datagram
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @note The async_receive operation can only be used with a connected socket.
   * Use the async_receive_from function to receive data on an unconnected
   * datagram socket.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
      void (lslboost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a ReadHandler.
    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_receive(this->get_implementation(),
        buffers, flags, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<ReadHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_receive(this->get_implementation(),
        buffers, flags, init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @returns The number of bytes received.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * lslboost::asio::ip::udp::endpoint sender_endpoint;
   * socket.receive_from(
   *     lslboost::asio::buffer(data, size), sender_endpoint);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().receive_from(
        this->get_implementation(), buffers, sender_endpoint, 0, ec);
    lslboost::asio::detail::throw_error(ec, "receive_from");
    return s;
  }
  
  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws lslboost::system::system_error Thrown on failure.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags)
  {
    lslboost::system::error_code ec;
    std::size_t s = this->get_service().receive_from(
        this->get_implementation(), buffers, sender_endpoint, flags, ec);
    lslboost::asio::detail::throw_error(ec, "receive_from");
    return s;
  }
  
  /// Receive a datagram with the endpoint of the sender.
  /**
   * This function is used to receive a datagram. The function call will block
   * until data has been received successfully or an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received.
   */
  template <typename MutableBufferSequence>
  std::size_t receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      lslboost::system::error_code& ec)
  {
    return this->get_service().receive_from(this->get_implementation(),
        buffers, sender_endpoint, flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive a datagram. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code socket.async_receive_from(
   *     lslboost::asio::buffer(data, size), sender_endpoint, handler); @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, lslboost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
      void (lslboost::system::error_code, std::size_t))
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a ReadHandler.
    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_receive_from(
        this->get_implementation(), buffers, sender_endpoint, 0,
        BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<ReadHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_receive_from(
        this->get_implementation(), buffers, sender_endpoint, 0,
        init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive a datagram. The function
   * call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param sender_endpoint An endpoint object that receives the endpoint of
   * the remote sender of the datagram. Ownership of the sender_endpoint object
   * is retained by the caller, which must guarantee that it is valid until the
   * handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const lslboost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * lslboost::asio::io_context::post().
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler,
      void (lslboost::system::error_code, std::size_t))
  async_receive_from(const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a ReadHandler.
    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    return this->get_service().async_receive_from(
        this->get_implementation(), buffers, sender_endpoint, flags,
        BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
#else // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
    async_completion<ReadHandler,
      void (lslboost::system::error_code, std::size_t)> init(handler);

    this->get_service().async_receive_from(
        this->get_implementation(), buffers, sender_endpoint, flags,
        init.completion_handler);

    return init.result.get();
#endif // defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
  }
};

} // namespace asio
} // namespace lslboost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_DATAGRAM_SOCKET_HPP