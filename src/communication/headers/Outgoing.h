/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
class Outgoing {

public:
    static const int AuthenticationOKMessageComposer = 1552;
    static const int CreateRoomMessageComposer = 106;
    static const int CreditsMessageComposer = 2588;
    static const int FlatCategoriesMessageComposer = 1625;
    static const int FloorMapMessageComposer = 2401;
    static const int FollowBuddyMessageComposer = 0x0A0A;
    static const int FollowErrorMessageComposer = 753;
    static const int FriendUpdateMessageComposer = 3412;
    static const int HeightMapMessageComposer = 3806;
    static const int HomeRoomMessageComposer = 704;
    static const int HotelScreenMessageComposer = 3825;
    static const int InitialRoomInfoMessageComposer = 2075;
    static const int InitMessengerMessageComposer = 2925;
    static const int LandingWidgetMessageComposer = 1351;
    static const int MessengerCategoriesMessageComposer = 249;
    static const int MessengerMessageComposer = 3922;
    static const int MessengerRequestsMessageComposer = 2344;
    static const int MessengerSearchMessageComposer = 2953;
    static const int MessengerSendRequest = 2061;
    static const int NavigatorCategories = 162;
    static const int NavigatorLiftedRoomsComposer = 2631;
    static const int NavigatorMetaDataComposer = 3732;
    static const int NavigatorSavedSearchesComposer = 591;
    static const int NavigatorPreferencesMessageComposer = 2478;
    static const int RemoveFriendMessageComposer = 3412;
    static const int RoomDataMessageComposer = 893;
    static const int RoomRatingMessageComposer = 2912;
    static const int RightsLevelMessageComposer = 2960;
    static const int YouAreNotControllerMessageComposer = 3674;
    static const int RoomSpacesMessageComposer = 1735;
    static const int RoomUpdateMessageComposer = 1091;
    static const int SearchResultSetComposer = 2247;
    static const int SecretKeyMessageComposer = 690;
    static const int SendPerkAllowancesMessageComposer = 2028;
    static const int UniqueMachineIDMessageComposer = 3683;
    static const int UserDisplayMessageComposer = 504;
    static const int RemoveUserMessageComposer = 3475;
    static const int UserObjectMessageComposer = 3762;
    static const int UserStatusMessageComposer = 2627;
    static const int CanCreateRoomMessageComposer = 3645;
    static const int RoomOwnerRightsComposer = 625;
    static const int HasOwnerRightsMessageComposer = 2037;
    static const int RoomSettingsDataMessageComposer = 1131;
    static const int MessageInviteMessageComposer = 141;
    static const int RoomEnterErrorMessageComposer = 1675;
    static const int GenericDoorbellMessageComposer = 2057;
    static const int GenericErrorMessageComposer = 524;
    static const int GenericNoAnswerDoorbellMessageComposer = 1868;
    static const int AcceptUserInsideRoomMessageComposer = 875;
    static const int ShoutMessageComposer = 2046;
    static const int ChatMessageComposer = 273;
    static const int TypingStatusMessageComposer = 2604;
    static const int FloodFilterMessageComposer = 626;
    static const int DanceStatusMessageComposer = 1005;
    static const int IdleStatusMessageComposer = 2932;
    static const int CatalogueTabMessageComposer = 3579;
    static const int BroadcastMessageAlertComposer = 1092;
    static const int CataloguePageMessageComposer = 2025;
    static const int PurchaseErrorMessageComposer = 519;
    static const int PurchaseNotificationMessageComposer = 1937;
    static const int FurniListNotificationComposer = 0x0F00;
    static const int UpdateInventoryMessageComposer = 3029;
    static const int InventoryMessageComposer = 3203;
    static const int RemoveInventoryItemComposer = 639;
    static const int PlaceFloorItemMessageComposer = 718;
    static const int PlaceWallItemMessageComposer = 1366;
    static const int FloorItemsMessageComposer = 3063;
    static const int WallItemsMessageComposer = 351;
    static const int MoveFloorItemMessageComposer = 1718;
    static const int MoveWallItemMessageComposer = 3630;
    static const int RemoveItemMessageComposer = 1744;
    static const int RemoveWallItemMessageComposer = 2793;
};
/*#pragma once
class Outgoing {

public:
    static const int AuthenticationOKMessageComposer = 1079;//1552
    static const int CreateRoomMessageComposer = 3001;//106
    static const int CreditsMessageComposer = 1958;//2588
    static const int FlatCategoriesMessageComposer = 3379;//1625
    static const int FloorMapMessageComposer = 1819;//2401
    static const int FollowBuddyMessageComposer = 3289;//2570
    static const int FollowErrorMessageComposer = -753;//753
    static const int FriendUpdateMessageComposer = 1190;//3412
    static const int HeightMapMessageComposer = 1232;//3806
    static const int HomeRoomMessageComposer = 2477;//704
    static const int HotelScreenMessageComposer = 726;//3825
    static const int InitialRoomInfoMessageComposer = 768;//2075
    static const int InitMessengerMessageComposer = 2900;//2925
    static const int LandingWidgetMessageComposer = 2394;//1351
    static const int MessengerCategoriesMessageComposer = 1329;//249
    static const int MessengerMessageComposer = 984;//3922
    static const int MessengerRequestsMessageComposer = 177;//2344
    static const int MessengerSearchMessageComposer = 2823;//2953
    static const int MessengerSendRequest = 1525;//2061
    static const int NavigatorCategories = 232;//162
    static const int NavigatorLiftedRoomsComposer = 1568;//2631
    static const int NavigatorMetaDataComposer = 1071;//3732
    static const int NavigatorSavedSearchesComposer = 2908;//591
    static const int NavigatorPreferencesMessageComposer = 3617;//2478
    static const int RemoveFriendMessageComposer = 1190;//3412
    static const int RoomDataMessageComposer = 306;//893
    static const int RoomRatingMessageComposer = 2454;//2912
    static const int RightsLevelMessageComposer = 680;//2960
    static const int YouAreNotControllerMessageComposer = 1068;//3674
    static const int RoomSpacesMessageComposer = 1897;//1735
    static const int RoomUpdateMessageComposer = 3743;//1091
    static const int SearchResultSetComposer = 1089;//2247
    static const int SecretKeyMessageComposer = 696;//690
    static const int SendPerkAllowancesMessageComposer = 1790;//2028
    static const int UniqueMachineIDMessageComposer = 3731;//3683
    static const int UserDisplayMessageComposer = 3857;//504
    static const int RemoveUserMessageComposer = 3839;//3475
    static const int UserObjectMessageComposer = 845;//3762
    static const int UserStatusMessageComposer = 3559;//2627
    static const int CanCreateRoomMessageComposer = 3568;//3645
    static const int RoomOwnerRightsComposer = 3675;//625
    static const int HasOwnerRightsMessageComposer = 1932;//2037
    static const int RoomSettingsDataMessageComposer = 3361;//1131
    static const int MessageInviteMessageComposer = 2138;//141
    static const int RoomEnterErrorMessageComposer = 200;//1675
    static const int GenericDoorbellMessageComposer = 2068;//2057
    static const int GenericErrorMessageComposer = 905;//524
    static const int GenericNoAnswerDoorbellMessageComposer = 797;//1868
    static const int AcceptUserInsideRoomMessageComposer = 735;//875
    static const int ShoutMessageComposer = 2888;//2046
    static const int ChatMessageComposer = 2785;//273
    static const int TypingStatusMessageComposer = 1727;//2604
    static const int FloodFilterMessageComposer = 803;//626
    static const int DanceStatusMessageComposer = 130;//1005
    static const int IdleStatusMessageComposer = 2306;//2932
    static const int CatalogueTabMessageComposer = 2140;//3579
    static const int BroadcastMessageAlertComposer = 1751;//1092
    static const int CataloguePageMessageComposer = 3277;//2025
    static const int PurchaseErrorMessageComposer = 1331;//519
    static const int PurchaseNotificationMessageComposer = 1450;//1937
    static const int FurniListNotificationComposer = 439;//3840
    static const int UpdateInventoryMessageComposer = 1619;//3029
    static const int InventoryMessageComposer = 3640;//3203
    static const int RemoveInventoryItemComposer = 3968;//639
    static const int PlaceFloorItemMessageComposer = 2076;//718
    static const int PlaceWallItemMessageComposer = 2236;//1366
    static const int FloorItemsMessageComposer = 2783;//3063
    static const int WallItemsMessageComposer = 580;//351
    static const int MoveFloorItemMessageComposer = 1104;//1718
    static const int MoveWallItemMessageComposer = 3408;//3630
    static const int RemoveItemMessageComposer = 2362;//1744
    static const int RemoveWallItemMessageComposer = 209;//2793
    static const int CommunityGoalHallOfFameWidget = 2208;
    static const int AvailabilityMessageComposer = 3690;
};*/