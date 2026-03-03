// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

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
				dialog.text = "꺼져, 이봐! 난 죄 없는 사람을 공격하는 쓰레기랑 수다 떨 생각 없어.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "이봐, 딱 잘 왔군... 너랑 얘기할 일이 있어... 중요한 일이야.";
				link.l1 = "정말이야? 왜, 레너드... 내가 보기엔 지금 맨정신이군! 이런 드문 광경도 다 있네!";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "아-아... 헉! 이봐, 친구...";
				link.l1 = TimeGreeting()+". 이미 충분히 마신 것 같군, '친구'.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! 힉! 뭐 원해?";
				link.l1 = LinkRandPhrase("무슨 소식이야, Leonard?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 잘 지내는지 확인하고 싶었어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그래! 충분하냐고? 아니! 전혀 부족하지, 크- hic! 그래, 레너드 머스킷이 취했다, 이게 바로 정상이지!";
			link.l1 = "술을 좋아하나 보군? 그래, 내 이름은 "+GetFullName(pchar)+". 음... 만나서 반갑군.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "네가 그렇게 말한다면. 우리 모두 - 힉! - 이제 만났으니... 그래서, 이제 뭐하지?";
			link.l1 = "그래, 네가 너무... 바쁘면 할 수 없지... 다음에 얘기하자!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("여기 근처에 무슨 새 소식이라도 있어?", "섬에서 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "아-하하, 엿 먹어라! 그래, 친구, 나 지금 - 거의 - 술 안 취했어. 그리고 그 이유는 우리에게 기회가 생겼기 때문이지...";
			link.l1 = "무슨 기회란 말이냐? 말해라, 내 시간 낭비하지 말고!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "이봐, 돈 좀 벌고 싶어? 은 페소, 금 더블룬 말이야. 내가 방법을 알려줄게. 하지만 나랑 나눠야 해 – 같이 일하는 거니까.";
			link.l1 = "나는 돈 벌 일이라면 언제든 환영이지. 하지만 결국 네 제안이 얼마나 이익이 되는지, 그리고 얼마나... 합법적인지... 그게 관건이야.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "장사는 사실 합법적이진 않지만, 수익은 꽤 괜찮지... 그리고 우리는 욕심 많은 구두쇠를 그의 탐욕 때문에 벌줄 수 있어. 저 인간이 가난해질 일은 없어; 돈이 너무 많으니까.\n게다가, 다들 그놈한테 나눠줬으니 이제는 그가 은혜를 갚을 차례지. 그런데, 자네 술 좀 하나? 럼주 얼마나 마셔야 뻗는가?";
			link.l1 = "경우에 따라 다르지. 난 과음하는 버릇은 없거든... 이제야 자세한 얘기를 해줄 건가?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "좋아. 구체적으로 말해주지. 이 섬에 뚱뚱하고 못생긴 자식이 하나 있어, 주세페 파치오라는 놈이지. (침을 뱉는다) 그놈은 나르발, 리바도스, 그리고 이 섬 사람들까지 다 뜯어먹고 있지. 내가 한동안 지켜봤는데, 뭔가를 알게 됐어...\n캐롤라인호에 있는 그의 선실에 상자가 두 개 있어. 하나에는 서류가, 다른 하나에는 금과 은이 들어 있지. 둘 다 서로 다른 열쇠로 잠겨 있어. 그 뚱뚱한 자식은 항상 열쇠를 자기 주머니에 넣고 다녀.";
			link.l1 = "그래서 파치오를 털 생각이야? 미안한데, 난 안 껴. 그리고 아무한테도 말 안 할 테니 그나마 다행인 줄 알아. 딴 놈 구해.";
			link.l1.go = "facio_exit";
			link.l2 = "하! 흥미롭군! 계속해봐...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "안타깝군, 정말 안타깝지... 우리 둘 다 가질 금은 충분한데... 좋아, 그럼. 또 보자.";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "그의 선실로 통하는 문이 두 개 있어. 그 중 하나는 항상 잠겨 있는데, 금 상자를 여는 열쇠가 그 문도 열 수 있지. 내가 직접 그가 그렇게 하는 걸 봤어. 선실이랑 금을 얻으려면 그 열쇠 하나만 있으면 돼. 하지만 그 열쇠를 어떻게 구하지?\n내게 계획이 있어, 아주 훌륭한 계획이지. 순조롭게만 진행된다면 파지오는 무슨 일이 일어났는지, 누굴 탓해야 할지도 전혀 모를 거야. 그는 신비한 럼주와 보석 도둑의 소행이라고 생각하겠지. 문제는, 이 일을 해낼 철두철미한 동료가 필요하다는 거야. 이해했어?";
			link.l1 = "그래. 계속해.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "파지오는 산초네에서 앉아 술 마시는 걸 정말 좋아해. 그리고 내가 본 누구보다도 술을 잘 마시지! 본인도 그걸 잘 알아서, 술 마시기 게임을 직접 만들었어. 사람들이 파지오를 술로 이기려고 도전하는 게임이지.\n그한테 이 게임 하자고 하면, 분명히 응할 거야. 그리고 진짜 재미는 그 다음부터 시작이지.\n파지오랑 내기하고, 선술집에 가서 럼주 한 병 잡고, 둘 중 한 명이 테이블에 입 맞출 때까지 마시는 거야. 네가 먼저 뻗으면 모든 계획이 망가져. 나 혼자서는 못 하거든.\n그래서 네 머리가 괜찮은지 물어본 거야. 네가 해야 할 일은 파지오가 먼저 뻗게 만드는 것뿐이야. 나는 근처에서 기다릴게. 파지오가 쓰러지면, 내가 열쇠를 챙길 거야.\n그다음엔 그 뚱보를 위층 침대에 옮겨놓고, 파지오가 자는 동안 몰래 그의 선실에 들어가는 거지. 우리가 상자를 털고 나면 바로 열쇠를 돌려놓을 거야. 파지오는 상자를 열어보기 전까진 도둑맞은 줄도 모를걸, 하하!\n열쇠를 손에 넣으면, 네가 파지오 선실에 몰래 들어가서 챙길 수 있는 걸 다 챙겨. 나는 밖에서 망을 볼게. 상자 안에 든 건 반반 나눠 갖고, 각자 갈 길 가는 거지. 어때, 할래?";
			link.l1 = "교활한 계획이군! 그래, 나도 끼지.";
			link.l1.go = "facio_6";
			link.l2 = "아니, 친구. 난 사양할게. 술을 그리 잘 마시진 못하거든. 나보다 좀 더 튼튼한 다른 놈을 찾아봐.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "내가 너를 제대로 본 게 맞아서 다행이군. 이제 파지오에게 가서 저녁 아홉 시 이후 선술집에서 만남을 잡아라. 그 돼지 같은 놈을 네 방식대로 이기길 바란다! 행운을 빈다, 저녁에 보자!";
			link.l1 = "최선을 다할게... 잘 가!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "이봐, 너만 믿는다. 저 뚱뚱한 구두쇠를 술로 눌러버려...";
			link.l1 = "그래.";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "끝났어, 그 돼지는 위층에서 자고 있어. 내가 열쇠를 챙겼지. 잘하고 있네; 아직 술은 덜 취한 것 같군!";
			link.l1 = "정, 정말이야? 이렇게... 이렇게 취한 건 정말 오랜만이네. - 딸꾹! - 머리가 좀 어지러워... 딸꾹! 갈까?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "끝났어, 그 뚱뚱한 돼지는 위층에서 자고 있어. 열쇠는 내가 가지고 있지. 잘하고 있어; 네가 그 돼지를 진짜로 과음하게 만들었구나...";
			link.l1 = "있지, 그런데 - 헉! - 이렇게 취한 건 정말 오랜만이야. 머리가 빙빙 도네... 나 쓰러지기 전에 가자.";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "이봐, 친구, 뚱뚱한 놈보다 술을 더 못 마셨군... 아쉽네. 뭐, 그래도 시도는 했잖아...";
			link.l1 = "젠장, 저 자식은 무슨... 밑 빠진 통 같아. 아으, 나 좀 쉬어야겠어... 끝났으니까, 꺼져! 헉!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "그래. 가자! 캐롤라인호로 따라와! 그리고 딴 데로 새지 마, 우리 시간 별로 없어!";
			link.l1 = "그래, 가-가자!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "여기. 열쇠 가져가. 네가 필요한 상자는 입구 왼쪽에 있어. 가능한 한 빨리 최대한 많이 챙겨. 다시 잠그는 거 잊지 마! 무슨 일이 보이면 내가 문을 세 번 두드릴 거야. 뒷쪽 회랑으로 도망쳐.";
			link.l1 = "좋아. 조심해!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable haul... Why'd we even bother? Eh... fine, let's split what we've got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there'd be much more... Hardly worth the risk. Eh... fine, let's split what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought there'd be more. All right, let's split it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We've done well, partner! This is a lot of coin! Let's split it!";
						else
						{
							sTotalTemp = "Damn me! I never imagined the fat man's stash was so huge. Well done, partner! Let's split the loot!";
						}
					}
				}
			}
			dialog.text = "드디어구나! 그 구두쇠한테서 뭘 챙겼어? 보여 봐!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "아무것도 없었어. 그냥 부적 같은 자잘한 것들뿐이었지.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "찾았어 "+sPeso+" 그리고 "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "아냐! 이 모든 게 헛수고였던 것 같군... 아마 그 자식이 보물을 다른 상자에 숨겼나 봐. 에이! 좋아, 열쇠나 줘. 내가 돌려줄게. 잘 가라, 친구... 젠장...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "나눠 가지자.";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "좋아, 열쇠를 줘. 내가 돌려줄게. 잘 가라, 친구.";
			link.l1 = "행운을 빌어, 친구.";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone cleaned out his chest. It seems the mysterious thief did it.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Haven't you heard? Fazio was robbed! He was robbed while lying dead drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your feet! That's something.", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "정말이야?... 힉! 듣고 있어...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "어쩌다 여기까지 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "항상 술 마시나? 그리고 술값은 어디서 구하나?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기 주민들에 대해 뭐 알고 있는 게 있나?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기를 떠나 스페인 본토로 가고 싶어?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "에이! 있잖아, 기억이 안 나. 진짜야, 안 난다니까! 오래전 일이야. 어딘가로 항해하고 있었는데... 어떻게든... 아무튼, 결국 여기까지 오게 됐지. 힉!";
			link.l1 = "흠... 좋아...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "그래, 마신다. 나는 주정뱅이야... 술 마시지... 젠장, 할 게 아무것도 없으니까! 있잖아, 친구, 난 끝났어. 이 럼 한 병이 내 인생에서 유일하게 원하는 거야. 그러니 계속 마실 거다! 그리고 돈... 헤헤, 럼은 얼마 안 해.\n어차피, 나는 돈도 안 내도 돼. 럼으로 가득 찬 곳이 있는데, 가려면 헤엄쳐야 해. 그래서 너무 취해서 헤엄칠 수 없을 때만 럼을 사지... 헉! 지즈제제지제제... 아니, 어디로 헤엄쳐야 하는지는 안 알려줄 거야, 헤헤, 묻지도 마...";
			link.l1 = "유쾌하군.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "뭐라고 해야 할까 - 헉! - 그 사람들에 대해? 얘기하고 술 마시기 좋은 사람들이지. 주세페 파지오는 중요한 인물이야, 거물이지. 그의 상자엔 금이 넘쳐나... 푸! 구두쇠 놈... 그래도 늙은 레오나르드는 존중해, 선술집에서 술도 사주고.\n가끔은 뭔가를 대신 부탁하긴 하지만, 별거 아니야 - 헉!\n헤, 파지오가 얼마나 많은 두블룬을 갖고 있는지 알아? 아하하하! 카리브 최고의 선술집에서 평생 일 안 하고 세계 최고 럼만 마시며 살아도 남을 만큼이지. 그런데도 여기, 섬에 머물러. 돈이 아무리 많아도 그 놈에겐 늘 부족한가 봐...";
			link.l1 = "알겠어...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "떠난다고? 힉! 왜? 아니, 나는 본토도, 유럽도, 세상 어느 거지 같은 섬도 가고 싶지 않아. 거기 공짜 럼이 있냐? 없어! 공짜 럼 따위는... 없어, 하나도 없어 - 힉! 그러니까 나한테 거긴 아무 의미도 없는 거야... 친구, 난 여기서 잘 지내고 있어. 이봐, 이봐 - 힉! - 사람들한테 여기서 나가고 싶냐고 물어봐. 아무도 안 그래, 두세 명 빼고는 - 힉!";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("이봐, 돼지야, 내 - 헉! - 물건에 손대지 마!", "레오나르드가 술 좀 마신다고 만만하게 보는 거야, 응? 응?! 내가 똑똑히 보여주지!", "내 상자들에서 떨어져! 누가 널 보냈지, 그 뚱뚱한 돼지 파치오냐?!");
			link.l1 = "이 빌어먹을 주정뱅이 놈아!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 궤짝 건드리지 마라, 이 도둑놈아!";
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
			dialog.text = LinkRandPhrase("이봐 친구, 그 칼 좀 집어넣어. - 헉! - 누군가 다치겠어.", "너 아직 취하지 않았어... 칼 들 정도로 취한 건 아니지. 그만 집어넣고 와서 한잔해.", "저렇게 칼을 휘두르는 걸 보니 진짜 재수 없는 놈 같아. 집어넣어, 크- hic! - 집어넣으라고.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "개새끼야... 좋아.");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 그러면 안 돼 - 헉! - 칼 함부로 휘두르지 마. 그만둬.", "너 아직 취하지 않았어... 칼 들 정도로 취한 건 아니지. 그만 집어넣고 와서 한잔해.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐 친구, 칼 좀 집어넣어. - 헉! - 누군가 다치겠어.", "저렇게 칼을 휘두르는 걸 보니 진짜 멍청이처럼 보이네. 집어넣어, 크- hic! - 집어넣으라고.");
				link.l1 = RandPhraseSimple("미안해.", "나는 이걸 치우고 있어.");
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
