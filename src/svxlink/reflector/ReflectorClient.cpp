/**
@file	 ReflectorClient.cpp
@brief   A_brief_description_for_this_file
@author  Tobias Blomberg / SM0SVX
@date	 2017-02-11

A_detailed_description_for_this_file

\verbatim
SvxReflector - An audio reflector for connecting SvxLink Servers
Copyright (C) 2003-2017 Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/

/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <sstream>
#include <cassert>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <AsyncTimer.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/

#include "ReflectorClient.h"



/****************************************************************************
 *
 * Namespaces to use
 *
 ****************************************************************************/

using namespace std;
using namespace Async;



/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Local class definitions
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Prototypes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/




/****************************************************************************
 *
 * Local Global Variables
 *
 ****************************************************************************/

uint32_t ReflectorClient::next_client_id = 0;


/****************************************************************************
 *
 * Public member functions
 *
 ****************************************************************************/

ReflectorClient::ReflectorClient(Async::TcpConnection *con)
  : m_con(con), m_msg_type(0), m_con_state(STATE_EXPECT_PROTO_VER),
    m_disc_timer(10000, Timer::TYPE_ONESHOT, false),
    m_client_id(next_client_id++), m_remote_udp_port(0)
{
  m_con->dataReceived.connect(mem_fun(*this, &ReflectorClient::onDataReceived));
  m_con->disconnected.connect(mem_fun(*this, &ReflectorClient::onDisconnected));
  m_disc_timer.expired.connect(mem_fun(*this, &ReflectorClient::onDiscTimeout));
} /* ReflectorClient::ReflectorClient */


ReflectorClient::~ReflectorClient(void)
{
} /* ReflectorClient::~ReflectorClient */




/****************************************************************************
 *
 * Protected member functions
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Private member functions
 *
 ****************************************************************************/

int ReflectorClient::onDataReceived(TcpConnection *con, void *data, int len)
{
  cout << "### ReflectorClient::onDataReceived: len=" << len << endl;

  assert(len >= 0);

  if (m_con_state == STATE_DISCONNECTED)
  {
    return len;
  }

  int tot_consumed = 0;
  while ((len > 0) && (m_con_state != STATE_DISCONNECTED))
  {
    ReflectorMsg header;
    size_t msg_tot_size = header.packedSize();
    if (static_cast<size_t>(len) < msg_tot_size)
    {
      cout << "### Header data underflow\n";
      return tot_consumed;
    }

    stringstream ss;
    ss.write(reinterpret_cast<const char *>(data), len);

    if (!header.unpack(ss))
    {
      // FIXME: Disconnect
      cout << "*** ERROR: Packing failed for TCP message header\n";
      return tot_consumed;
    }

    msg_tot_size += header.size();
    if (static_cast<size_t>(len) < msg_tot_size)
    {
      cout << "### Payload data underflow\n";
      return tot_consumed;
    }

    switch (header.type())
    {
      case MsgProtoVer::TYPE:
        handleMsgProtoVer(ss);
        break;
      case MsgAuthResponse::TYPE:
        handleMsgAuthResponse(ss);
        break;
      default:
        cerr << "*** WARNING: Unknown protocol message received: msg_type="
             << header.type() << endl;
        break;
    }

    data += msg_tot_size;
    len -= msg_tot_size;
    tot_consumed += msg_tot_size;
  }

  return tot_consumed;

#if 0
  m_unp.reserve_buffer(len);
  memcpy(m_unp.buffer(), data, len);
  m_unp.buffer_consumed(len);
  msgpack::unpacked result;
#if MSGPACK_VERSION_MAJOR < 1
  while (m_unp.next(&result))
#else
  while (m_unp.next(result))
#endif
  {
    msgpack::object obj(result.get());
    //cout << obj << endl;
    try
    {
      if (m_msg_type == 0)
      {
        unsigned msg_type = 0;
#if MSGPACK_VERSION_MAJOR < 1
        obj.convert(&msg_type);
#else
        obj.convert(msg_type);
#endif
        switch (msg_type)
        {
          default:
            m_msg_type = msg_type;
            break;
        }
      }
      else
      {
        switch (m_msg_type)
        {
          case MsgProtoVer::TYPE:
            handleMsgProtoVer(obj);
            break;
          case MsgAuthResponse::TYPE:
            handleMsgAuthResponse(obj);
            break;
          default:
            cerr << "*** WARNING: Unknown protocol message received: msg_type="
                 << m_msg_type << endl;
            break;
        }
        m_msg_type = 0;
      }
    }
    catch (msgpack::type_error)
    {
      cerr << "*** WARNING: The incoming message type have the wrong object type"
           << endl;
      disconnect("Protocol error");
    }
  }
  return len;
#endif
} /* ReflectorClient::onDataReceived */


void ReflectorClient::handleMsgProtoVer(std::istream& is)
{
  if (m_con_state != STATE_EXPECT_PROTO_VER)
  {
    disconnect("Protocol version expected");
    return;
  }

  MsgProtoVer msg;
  if (!msg.unpack(is))
  {
    // FIXME: Disconnect
    cerr << "*** ERROR: Could not unpack MsgProtoVer\n";
    return;
  }
  cout << "MsgProtoVer(" << msg.majorVer() << ", " << msg.minorVer()
       << ")" << endl;
  if ((msg.majorVer() != MsgProtoVer::MAJOR) ||
      (msg.minorVer() != MsgProtoVer::MINOR))
  {
    cerr << "*** ERROR: Incompatible protocol version: "
         << msg.majorVer() << "." << msg.minorVer() << ". Should be "
         << MsgProtoVer::MAJOR << "." << MsgProtoVer::MINOR << endl;
    stringstream ss;
    ss << "Unsupported protocol version " << msg.majorVer() << "."
       << msg.minorVer();
    disconnect(ss.str());
    return;
  }

  MsgAuthChallenge challenge_msg;
  memcpy(m_auth_challenge, challenge_msg.challenge(),
         MsgAuthChallenge::CHALLENGE_LEN);
  sendMsg(challenge_msg);
  m_con_state = STATE_EXPECT_AUTH_RESPONSE;
} /* ReflectorClient::handleMsgProtoVer */


void ReflectorClient::handleMsgAuthResponse(std::istream& is)
{
  if (m_con_state != STATE_EXPECT_AUTH_RESPONSE)
  {
    disconnect("Authentication response expected");
    return;
  }

  MsgAuthResponse msg;
  if (!msg.unpack(is))
  {
    // FIXME: Disconnect
    cerr << "*** ERROR: Could not unpack MsgAuthResponse\n";
    return;
  }
  cout << "MsgAuthResponse(<digest>)" << endl;

  m_callsign = msg.callsign();
  if (msg.verify("ThePassword :-)", m_auth_challenge))
  {
    sendMsg(MsgAuthOk());
    cout << m_callsign << ": Login OK from "
         << m_con->remoteHost() << ":" << m_con->remotePort()
         << endl;
    m_con_state = STATE_CONNECTED;
    sendMsg(MsgServerInfo(m_client_id));
  }
  else
  {
    cout << m_callsign << ": Access denied" << endl;
    disconnect("Access denied");
  }
} /* ReflectorClient::handleMsgProtoVer */


void ReflectorClient::sendMsg(const ReflectorMsg& msg)
{
  ReflectorMsg header(msg.type(), msg.packedSize());
  ostringstream ss;
  if (!header.pack(ss) || !msg.pack(ss))
  {
    // FIXME: Better error handling
    cerr << "*** ERROR: Failed to pack TCP message\n";
    return;
  }
  m_con->write(ss.str().data(), ss.str().size());

#if 0
  msgpack::sbuffer msg_buf;
  msgpack::pack(msg_buf, msg.type());
  if (msg.haveData())
  {
    msgpack::pack(msg_buf, msg);
  }
  m_con->write(msg_buf.data(), msg_buf.size());
#endif
} /* ReflectorClient::sendMsg */


void ReflectorClient::disconnect(const std::string& msg)
{
  cout << "### ReflectorClient::disconnect: " << msg << endl;
  sendMsg(MsgError(msg));
  m_disc_timer.setEnable(true);
  m_con_state = STATE_EXPECT_DISCONNECT;
} /* ReflectorClient::disconnect */


void ReflectorClient::onDisconnected(TcpConnection* con,
                                     TcpConnection::DisconnectReason)
{
  if (!m_callsign.empty())
  {
    cout << m_callsign << ": ";
  }
  cout << "Client " << con->remoteHost() << ":" << con->remotePort()
       << " disconnected" << endl;
  m_disc_timer.setEnable(false);
  m_con_state = STATE_DISCONNECTED;
} /* ReflectorClient::onDisconnected */


void ReflectorClient::onDiscTimeout(Timer *t)
{
  cout << "### ReflectorClient::onDiscTimeout" << endl;
  assert(m_con_state == STATE_EXPECT_DISCONNECT);
  m_con->disconnect();
  m_con_state = STATE_DISCONNECTED;
} /* ReflectorClient::onDiscTimeout */


void ReflectorClient::handleMsgAudio(const MsgAudio& msg)
{
  cout << "### ReflectorClient::handleMsgAudio" << endl;

} /* ReflectorClient::handleMsgAudio */


/*
 * This file has not been truncated
 */
