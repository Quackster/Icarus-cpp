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
    static const int VersionCheckMessageEvent = 4000;//4000
    static const int UniqueIDMessageEvent = 3521;//3659
    static const int AuthenticateMessageEvent = 1989;//1490
    static const int InfoRetrieveMessageEvent = 2629;//1978
    static const int CurrencyBalanceMessageEvent = 1051;//1277
    static const int LatencyTestMessageEvent = 878;//3307
    static const int LeaveRoomMessageEvent = 1429;//3781
    static const int NewNavigatorMessageEvent = 1540;//2845
    static const int SearchNewNavigatorEvent = 618;//1786
    static const int UserWalkMessageEvent = 2121;//2261
    static const int EnterRoomMessageEvent = 189;//2258
    static const int HeightMapMessageEvent = 3925;//815
    static const int EventLogMessageEvent = 143;//1787
    static const int RoomInfoMessageEvent = 2247;//3494
    static const int MessengerInitMessageEvent = 2782;//733
    static const int MessengerUpdateMessageEvent = -3412;//3412
    static const int MessengerSearchMessageEvent = 1194;//2760
    static const int MessengerRequestMessageEvent = 1706;//2826
    static const int MessengerAcceptMessageEvent = 2067;//3310
    static const int MessengerDeclineMessageEvent = 3484;//1384
    static const int MessengerDeleteFriendMessageEvent = 1636;//2169
    static const int MessengerTalkMessageEvent = 2409;//400
    static const int MessengerInviteMessageEvent = 1806;//2671
    static const int FollowFriendMessageEvent = 848;//3254
    static const int CanCreateRoomMessageEvent = 2411;//1968
    static const int CreateRoomMessageEvent = 92;//828
    static const int DanceMessageEvent = 1225;//1666
    static const int RoomEditInfoMessageEvent = 581;//2035
    static const int DeleteRoomMessageEvent = 439;//2126
    static const int SaveRoomMessageEvent = 3023;//915
    static const int AnswerDoorbellMessageEvent = 1781;//1491
    static const int EnterDoorbellMessageEvent = 2947;//2347
    static const int ChatMessageEvent = 744;//132
    static const int ShoutMessageEvent = 697;//1508
    static const int StartTypingMessageEvent = 2826;//1752
    static const int StopTypingMessageEvent = 1329;//998
    static const int ShowSignMessageEvent = 3555;//2604
    static const int CatalogueTabMessageEvent = 951;//3871
    static const int CataloguePageMessageEvent = 60;//530
    static const int PurchaseObjectMessageEvent = 3492;//2893
    static const int InventoryMessageEvent = 2811;//3991
    static const int ApplyDecorationMessageEvent = 2729;//1421
    static const int PlaceItemMessageEvent = 1809;//1414
    static const int MoveItemMessageEvent = 3583;//888
    static const int MoveWallItemMessageEvent = 1778;//3589
    static const int PickupItemMessageEvent = 1766;//103
    static const int InteractItemMessageEvent = 3249;//103
};