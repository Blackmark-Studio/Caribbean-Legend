// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "꺼져, 친구. 이유도 없이 사람을 공격하는 놈들한테 할 말 없어!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "오! 여기 있었군. 막 너를 찾으러 가려던 참이었어. 네가 필요해, 친구.";
				link.l1 = "오늘따라 유난히 친근하군, 리처드. 자, 말해 봐. 뭐 원하는 거야?";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "뭐 원하는 거야? 솔직히 말해서, 오늘 기분이 별로야 - 사실, 마지막으로 기분 좋았던 때가 언제였는지도 기억이 안 나.";
				link.l1 = "정말 그렇게 심각해, 친구?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "오, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 원하는 거야?";
				link.l1 = LinkRandPhrase("이봐, 리처드, 요즘 소식 들은 거 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "기분이 좀 나아졌나 궁금해서 와봤어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "나쁘냐고? 아니, 나쁘진 않아. 그렇다고 좋지도 않고. 그래서... 뭐 원하는 거야?";
			link.l1 = "그냥 인사하려고 왔어. 나는 여기 새로 온 사람이니까, 정의의 섬을 좀 돌아다니면서 사람들을 알아가고 있어.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "정말인가? 좋아, 그럼. 나는 리처드 샴본이야. 오래전에 나는 귀중한 물건들을 거래했지, 그중엔 불법인 것도 있었고. 하지만 지난 아홉 해 동안은 난 난파선에서 쓸만한 것들을 뒤져서, 그것들을 음식이나 금과 바꿔 먹고살고 있어.";
			link.l1 = "그리고 나는 "+GetFullName(pchar)+", 선장...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "전 선장이라는 거지, 하하!";
			link.l1 = "사실 내 배는 지금 블루웰드에 있어; 여기엔 바크선을 타고 왔지.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "정말이야? 말도 안 돼! 그런데 네 바크는 지금 어디 있지?";
			link.l1 = "바닥에서...";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "아... 나는... 뭐, 됐다 친구야. 럼 좀 마시러 간다...";
			link.l1 = "행운을 빌지. 너랑 이야기해서 좋았어. 다음에 또 보자.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("이봐, 리처드, 요즘 소식 들은 거 있어?", "섬에서 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "전에 그랬던 적 없었나? 다들 힘든 날은 있지! 아무튼, 정의의 섬에 네가 뛰어난 싸움꾼이라는 소문이 돌고 있어. 솔직히 말해 봐, 그거 사실이야?";
			link.l1 = "사람들이 무슨 말을 했는지는 모르겠지만, 검 다루는 법은 내가 잘 안다.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "좋아. 들어봐, "+pchar.name+", 내가 바깥 고리랑 거기서 찾을 수 있는 귀한 물건들에 대해 말해줬던 거 기억나?";
			link.l1 = "리처드, 모두가 그 얘기를 하더군. 이 섬에서 그 반지 찾아 헤매는 게 유일한 오락거리인 것 같아. 정치적 음모 말고는 말이지.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "이보다 더 진실된 말은 없지, 하하! 본론으로 들어가지. (목소리를 낮추며) 바깥 고리에 손도 안 댄 배를 하나 발견했어. 상태가 아주 좋아, 이런 건 드물지.\n배가 커. 피나스야. 얼마 안 됐어, 두 달쯤 전에 여기로 밀려온 거지. 아직 아무도 눈치 못 챘으니, 우리가 먼저 털면 짭짤하게 한몫 챌 수 있겠어.";
			link.l1 = "나랑 같이 가자고?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "맞아! 핀네스의 선수 부분이 완전히 부서졌고, 저 빌어먹을 게들이 안으로 들어와서 창고에 둥지까지 틀었어. 놈들 눈에 띄지 않고 들어가는 건 불가능하고, 수면에서 본갑판으로 올라갈 방법도 전혀 모르겠어.\n나는 싸움도 잘 못 해. 칼도 몇 년째 만져본 적 없으니, 혼자서는 저 괴물들을 절대 못 죽여. 그래서 너한테 온 거야.";
			link.l1 = "그러니까 네 대신 그 배 안에 있는 게들을 전부 죽여 달라는 거군...";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "그래. 내 제안은 이거야: 내가 배로 가는 길을 알려주면, 네가 게들을 처리하고, 거기서 찾는 전리품은 반씩 나누는 거지.";
			link.l1 = "아니, 친구야, 난 관심 없어. 반쯤 가라앉은 배 안에서 게 떼랑 싸우느라 애쓸 만큼의 보상도 아니지. 더 무모한 놈을 찾아봐.";
			link.l1.go = "ring_exit";
			link.l2 = "흥미롭군... 나는 오랫동안 바깥 고리를 탐험할 생각을 하고 있었지. 좋아! 난파선을 보여 주면 내가 게들을 죽여주지.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "안타깝군... 실수하고 있는 거야; 바깥 고리에서 손대지 않은 난파선은 드물거든. 뭐, 네 선택이지. 잘 가라...";
			link.l1 = "잘 가, Richard...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "내가 너를 제대로 봤다는 게 기쁘군, 친구. 저 안에서 흥미로운 것들을 많이 발견하게 될 것 같은 예감이 들어...";
			link.l1 = "두고 보자고. 저 안에 게가 몇 마리나 있는지 알아?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "한 네댓 명쯤... 내가 본 건 그 정도야.";
			link.l1 = "좋아... 언제 출발하지?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "내일은 어때? 준비할 시간이 필요해. 줄리안 형제한테 해독제 좀 받아둬. 게 집게는 독이 있으니까. 조심해서 나쁠 건 없지. 내일 아침 여덟 시에 기울어진 갑판에서 만나자. 어디 있는지 알지?";
			link.l1 = "아니, 어디?";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "산 아우구스틴 뒤에 오래된 난파선이 있어. 뱃머리는 물에 잠기고 선미는 높이 들려 있어서 '기울어진 갑판'이라고 불리지. 수영해서만 올라갈 수 있어.\n밧줄 다리 양쪽 중 한 곳에서 물에 들어가, 산 아우구스틴의 뱃머리나 선미를 돌아서 기울어진 갑판으로 올라가면 돼. 거기서 우리 손대지 않은 난파선까지 수영해 가자.";
			link.l1 = "좋아. 내일 보자!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "여덟 시, 기울어진 사선 갑판.";
			link.l1 = "그래, 그래, 기억할게...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "아, 거기 있었군, 친구. 게 샐러드 만들 준비됐어?";
			link.l1 = "물론이지!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "좋아. 이제 고개를 바깥쪽 원으로 돌리고 봐. 저기 물 위로 솟아오른 난파선 두 척이 보이지?";
			link.l1 = "흠... 그래, 보여.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "저들 사이를 지나 바깥쪽 고리를 봐. 우리 쪽으로 뱃머리를 돌린 갈레온이 보이지?";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "그래, 나... 나 이제 보이는 것 같아!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "저 여자가 우리 목표야. 우리 핀네스는 그녀 뒤에 숨어 있어. 곧장 헤엄쳐 가, 절대 방향 틀지 말고. 거기서부터 내가 길을 안내해 줄게, 그리고 일이 끝나면 정의의 섬으로 돌아가는 방법도 알려주지.\n화물칸 입구는 핀네스 선수에 뚫린 구멍이야. 네가 게들을 전부 죽이기 전엔 난 그 안에 들어가지 않을 거야.";
			link.l1 = "우리 약속 기억하지. 네가 길을 안내하면 내가 게들은 처리할게. 갈까?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "그러지. 내가 따라가마.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "헤헤, 잘했어! 전부 처리한 것 같구나!";
			link.l1 = "나는 누가 분명히 '네댓 명'밖에 없다고 말했던 게 기억나는데...";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "이봐, 친구, 내가 인원 점검을 한 건 아니고 그냥 구멍으로 슬쩍 본 거야. 일부러 거짓말할 생각은 없었어!";
			link.l1 = "뭐, 알겠어. 화물창을 뒤져 볼까...?";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "물론이지! 그래서 우리가 여기 있는 거야.";
			link.l1 = "좋아, 시간 낭비하지 말자...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "잠깐 기다려, 친구. 내가 아직 가보고 싶은 곳을 다 확인하지 못했어. 좀 더 꼼꼼히 살펴봐. 어쩌면 더 값진 걸 찾을 수 있을지도 몰라.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "별거 없어. 여기엔 값나가는 물건이 하나도 없어서 아쉽지. 소금에 절인 소고기 통이나 코프라 상자뿐이야. 그래도 비싼 와인 한 상자는 찾았어. 너는 뭐 가져왔어?";
			link.l1 = "별거 없어. 값나가는 게 몇 개 있긴 한데, 나머지는 네 말대로 콘드비프랑 코프라야.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "모자라... 위층으로 올라가서 상갑판이랑 선실도 확인해 보자.";
			link.l1 = "가자.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "젠장! 저것 좀 봐! 망할 게 crab 놈들이 온 사방에 있잖아! 대체 어떻게 여기까지 기어 올라온 거야?!";
			link.l1 = "진정해! 여기서 가만히 있어, 움직이지 말고 조용히 해. 내가 저놈들 처리할 테니까...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "허! 네 칼솜씨에 대한 소문이 사실이었군! 나 혼자 여기 있었다면 벌써 바다로 뛰어들었을 거야.";
			link.l1 = "예전에 어떻게 밀수꾼 노릇을 했다는 거야, 이렇게 쉽게 겁을 먹으면서?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "우선, 그땐 내가 더 젊고, 힘도 세고, 무모했지. 둘째로, 나는 군인이 아니야 - 우리 밀수꾼들은 항상 피를 피하려고 하지. 셋째, 내 재주는 칼이나 권총이 아니라 돛과 키를 다루는 데 있어. 그리고 넷째, 여기서 몇 년을 살다 보니 마음이 약해졌어!\n그러니 나한테 화내지 마. 위 갑판을 확인해 보자. 배가 심한 싸움을 겪은 것 같아. 이 손상 좀 봐...";
			link.l1 = "네 말이 맞아. 배가 확실히 심한 공격을 받았어. 계속 찾아보자.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "그리고 장교 선실로 들어가는 입구도 찾아야 해.";
			link.l1 = "그럼 시간 낭비하지 말자. 게를 보면 나 불러!";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "또 아무것도 없어! 보석 몇 개뿐이야, 그게 다야. 뭐, 괜찮아. 갑판에는 원래 값진 물건이 잘 없지. 진짜 좋은 건 선실에 있을 거야. 저기 선장실로 들어가는 입구가 보여. 가서 확인해 보자.";
			link.l1 = "조심해, 안에 뭐가 기다리고 있을지 누가 알겠어. 아마 내가 먼저 들어가는 게 낫지 않을까?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "가자, "+pchar.name+". 이제 더 이상 당신 뒤에 숨지 않겠어.";
			link.l1 = "그럼 계속 해...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "운이 좋은 것 같군: 여기엔 게도 없고 다른 더러운 것도 없어. 그런데 젠장, 슬슬 열받기 시작하네; 겨우 두어 다스 더블룬이랑 잡동사니 몇 개밖에 못 찾았잖아!";
			link.l1 = "진정해. 기억해라: 귀중품은 항상 선장 선실에 보관돼 있지. 뭘 건질 수 있는지 보자!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "하하! 내 예상이 딱 맞았군! 나는 상인들의 버릇을 잘 알지. 배 여기저기에 비밀 은닉처를 만들어서 보물을 숨기는 걸 좋아하거든! 이 핀네스의 선장은 교활한 놈이었지만, 내가 그렇게 쉽게 속을 줄 알았나? 내가 뭘 찾았는지 좀 봐!";
			link.l1 = "보여 줘!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "사만 페소, 두 개의 상자에 가득 찬 두블룬, 에메랄드 한 꾸러미랑 보석 몇 개! 주인이 꽤 부자였지. 그래도 우리 고생한 보람은 있겠군. 더 많은 걸 기대했지만 말이야. 자, 전리품 나누자.";
			link.l1 = "훌륭해, Richard. 적어도 빈손으로 돌아가진 않겠군!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "음, 각자 갑판에서 찾은 건 그냥 자기 몫으로 하자고. 괜찮지? 상자나 찬장에서 뭐 좋은 거라도 건졌어?";
			link.l1 = "인디언 유물 몇 점, 부적, 문서 같은 것들이지.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "네가 가지도록 해. 어차피 제일 위험한 일은 네가 했으니까.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "좋아. 그리고 보물 사냥꾼인 네가 쓸모 있다고 생각할 만한 게 하나 더 있어. 저 책상 위에 선장 일지가 놓여 있더군. 그 안에 담긴 이야기는 참 슬프지만, 우리가 찾는 데 도움이 될 수도 있어. 화물칸 어딘가에 금으로 가득 찬 상자가 숨겨져 있대! 자, 읽어 봐!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "좋아. 하지만 한 가지 더 찾았어: 선장 일지야.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "그건 부정하지 않겠어, 하하!\n자, 이제 돌아갈 시간이야?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "그래. 배에 대해서는 아무한테도 말하지 마. 우리만의 비밀이야. 물론, 코프라는 필요 없지만 저 음식들은 다 쓸모 있을 거야. 이제 더 이상 제독한테서 안 사도 되겠네.";
			link.l1 = "좋아, 동의하지. 다른 사람들이 이 배를 당분간 못 찾길 바란다. 가자!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "읽어봤어?";
			link.l1 = "아직 아니야...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "그럼 읽어보자! 뭔가 중요한 걸 알게 될지도 모르잖아. 그리고 이 배가 어떻게 여기까지 오게 됐는지도 궁금하고. 읽어봐!";
			link.l1 = "흠. 좋아, 지금 읽어볼게...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "읽어봤어? 거기 뭐라고 적혀 있어?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "내가 읽었어. 들어봐, 이야기는 정말 슬프지만, 그 안에 화물칸에 금이 가득 든 숨겨진 상자가 있다는 내용이 나와! 읽어봐, 어쩌면 네가 그 상자가 어디 있는지 알아낼 수 있을지도 몰라.";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "잠깐만. 내가 읽어보고 알려줄게...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "정말이야? "+pchar.name+", 나는... 음, 글을 잘 읽지 못해. 거기 뭐라고 적혀 있는지 말해 줄래?";
			link.l1 = "간단히 말하자면: 이 핀네스는 신스페인 해안을 따라 남쪽에서 북쪽으로 카리브해를 건너고 있었소.\n그 과정에서 선장은 오리노코 하류 부족의 인디언 공주와 사랑에 빠져 결혼했지.\n그녀는 자기 부족이 제물을 바친다고 말했소...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "그들의 제물은 금덩이였지! 그러니 당연히 우리 선장과 일등항해사, 그리고 보급장교가 힘을 합쳐 그 금을 훔쳤어. 그걸 화물칸 상자에 넣고 코프라로 덮어놨지...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "하지만 그 신성한 인디언 성소를 약탈한 대가를 치른 것 같아. 배는 무풍지대에 갇히고, 식수가 바닥나고, 열병이 돌았으며, 해적들이 습격했지. 선원들은 인디언 소녀, 즉 선장의 아내를 탓하며 그녀를 바다에 던지라고 요구했어. 물론 선장은 거부했고, 결국 반란이 일어났지...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "선장은 싸움에서 졌어. 그의 마지막 기록에 따르면, 그는 자기와 인디언 아내를 선실에 가둔 채 문을 부수려는 자들을 모두 쏘았다고 해. 폭풍이 그들에게 다가오고 있었다고도 적혀 있는데, 아마 그 폭풍이 배를 정의의 섬으로 몰고 온 것 같아. 결국 그의 아내가 총에 맞았고, 반란자들이 그도 결국 죽였을 거라는 의심의 여지가 없어.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "흠, 그래, 그래, 슬픈 이야기지... 하지만 금은... 정말로 화물창에 금괴 상자가 있다는 거야? 어느 거지?! 찾아보자! 필요하다면 내가 오를롭 전체를 뒤집어 놓겠어!";
			link.l1 = "알았어, 알았어, 그래, 우리가 찾아볼게 – 진정해, 리처드!";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "하하! 찾았다! 저 반짝임 좀 봐! 상자 하나 가득이야! 여기 금덩이가 오천 개는 넘게 들어 있겠지! 이렇게 많은 금은 처음 본다!!";
			link.l1 = "축하한다, 동료야. 우리의 모든 노력이 결실을 맺은 것 같군! 그 많은 금을 어떻게 할까?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "무슨 말이야? 우리 반으로 나누자니까!";
			link.l1 = "내 말은, 그걸 어디에 둘 거야? 여기다 두고 갈 거야?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "하! 아니, 나는 금을 아무도 못 찾을 내 비밀 은닉처에 숨길 거야. 숨기는 건 내가 정말 잘하는 일이거든! 금의 절반은 이 통에 넣자 - 그게 내 몫이야. 해 지기 전에 내가 가져갈 거다.\n네 몫은 네가 알아서 해. 그래도 네 금도 네 은닉처로 옮기는 게 좋을 거야. 금이 사라져도 나한테 탓하지 마라. 나는 나름대로 정직한 놈이라 네 몫엔 손 안 댈 거다. 하지만 곧 다른 놈들이 이 배를 찾을 수도 있고, 그땐 눈에 보이는 건 뭐든 가져가려 들 거다.";
			link.l1 = "고마워. 내 금을 어떻게 할지 생각해 볼게. 그동안 네 몫은 저 통에 넣자...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "끝났어... 고마워, "+pchar.name+", 나와 함께 와줘서 고맙다. 너 없이는 이 일을 해낼 수 없었을 거야. 이제 타르탄을 한 척 지어야 할지 고민해봐야겠군... 여기서 떠나야지...\n아, 그건 나중에 걱정하자. 당장은 이 금을 내 은닉처로 옮기는 일만으로도 바쁠 테니까. 잘 가라, 친구. 네 몫을 현명하게 쓰길 바란다!";
			link.l1 = "잘 가, Richard. 오늘 정말 멋진 하루였어. 건강해!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "질문이 있나? 하, 좋아, 꼭 그래야 한다면...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "섬을 떠나고 싶어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "클랜 중 하나에 들어갈 생각 해본 적 있어? 예를 들면, 나르발 같은 데?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "바깥 고리에서는 흥미로운 것들을 많이 찾을 수 있다는 게 사실이야?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "십 년 동안 나와 동료들은 쿠바에서 정의의 섬까지 타르탄 배로 오가며 이곳 주민들과 교역했지. 우리는 섬의 위치를 철저히 비밀로 했고, 난파선에서 나온 물건과 금을 신선한 고기, 과일, 채소와 맞바꿨어. 그때가 좋았지!\n정의의 섬 주민들은 항상 식량 조달에 애를 먹었으니, 향신료를 곁들인 육즙 가득한 고기를 유럽보다 훨씬 비싼 값에 사줬어! 항해 한 번 할 때마다 토르투가의 창녀들을 전부 살 수 있을 만큼 벌었지.\n하지만 모든 일엔 끝이 있는 법. 이 지역의 폭풍이 점점 더 강해지고 자주 불어서 섬으로 항해하는 게 훨씬 위험해졌어. 내 선원들 중 일부는 장사를 접었지만, 나와 용감한 녀석 열두 명은 계속 버텼지.\n결국 어느 폭풍에 휩쓸려 섬에서 두 마일 떨어진 암초에 좌초됐어. 저 거센 파도를 어떻게 헤엄쳐 나왔는지 아직도 모르겠어. 이제는 내가 예전에 거래하던 이들 중 한 명이 되어버렸지.";
			link.l1 = "재미있는 이야기군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "하! 언젠가는 여기서 나갈 거야, 젠장, 하지만 거지꼴로는 아니지! 쿠바에 가서 뭘 하겠어? 남은 친구도 없고, 주머니도 텅 비었는데.\n바깥쪽 고리에 있는 배 하나만 찾으면 돼. 선창에 값진 화물이 가득하거나, 두블룬 더미라도 있으면 말이야. 그러면 새 타르탄선을 만들어서 폭풍을 뚫고 다시 문명 세계로 돌아갈 거야.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "내가 왜 그래야 하지? 사흘에 한 번씩 태양 아래서 불타는 듯이 서서 산 가브리엘에 사람들 못 오게 지키라고? 게다가, 그 사람들은 섬 출신이 아닌 사람은 잘 안 써. 결국 자기네 토박이들이니까... 네그로들도 마찬가지야. 그러니, 아니야. 난 그냥 혼자 있는 게 더 낫겠어.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "그래! 그게 여기 주민들이 살아남는 방식이지. 언제 파티를 여는지 알아? 새로운 배가 고리에서 난파할 때야.\n아직도 금과 물건이 가득한 손대지 않은 난파선이 많이 남아 있지만, 바깥 고리를 탐험하는 건 위험해. 그곳은 엉망진창이고, 혼자서 들어가면 안 돼. 밧줄에 걸리거나 미끄러져 떨어지면 끝장이야. 그렇게 죽은 사람이 많거든.";
			link.l1 = "흠... 그럼 조심할게.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("이봐, 내 물건에서 손 떼, 도둑놈아!", "이 섬에선 아무도 믿을 수 없어! 각오해라, 도둑놈!", "내 바다 상자 건드리지 마, 이 자식아!");
			link.l1 = "꺼져!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "죄 없는 여자를 털다니?! 이대로 넘어갈 줄 알지 마!";
			link.l1 = "어리석은 계집애!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("무기 집어넣어. 너 때문에 불안해지잖아.", "그 칼을 쓸 생각이 아니라면 집어넣는 게 좋겠어.", "그 무기 집어넣어, 사람들 다 겁주고 있잖아 - 나도 마찬가지고!");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "미안해...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "그 칼을 쓸 생각이 아니라면 집어넣는 게 좋겠어.", "무기 집어넣어. 너 때문에 불안해지잖아.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기 집어 넣어. 너 때문에 불안해지잖아.", "그 무기 좀 치워, 사람들 겁주고 있잖아 - 나도 포함해서!");
				link.l1 = RandPhraseSimple("알겠어.", "내가 가져간다.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
