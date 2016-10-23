/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
class Incoming {

public:
    static const int VersionCheckMessageEvent = 4000;
    static const int UniqueIDMessageEvent = 282;
    static const int AuthenticateMessageEvent = 383;
    static const int InfoRetrieveMessageEvent = 1978;
    static const int CurrencyBalanceMessageEvent = 1277;
    static const int LatencyTestMessageEvent = 3307;
    static const int LeaveRoomMessageEvent = 3781;
    static const int NewNavigatorMessageEvent = 2845;
    static const int SearchNewNavigatorEvent = 1786;
    static const int CreateRoomMessageEvent = 828;
    static const int UserWalkMessageEvent = 2261;
    static const int EnterRoomMessageEvent = 2258;
    static const int HeightMapMessageEvent = 815;
    static const int EventLogMessageEvent = 1787;
    static const int RoomInfoMessageEvent = 3494;
    static const int MessengerInitMessageEvent = 733;
    static const int MessengerSearchMessageEvent = 2760;
    static const int MessengerRequestMessageEvent = 2826;
    static const int MessengerAcceptMessageEvent = 3310;
    static const int MessengerDeclineMessageEvent = 1384;
    static const int MessengerDeleteFriendMessageEvent = 2169;
    static const int MessengerTalkMessageEvent = 400;
    static const int FollowFriendMessageEvent = 3254;
};