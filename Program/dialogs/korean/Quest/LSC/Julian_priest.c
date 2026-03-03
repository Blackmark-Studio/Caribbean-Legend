// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "너랑 얘기하고 싶지 않아. 넌 아무 이유 없이 평화로운 주민들을 공격하고 싸움을 부추기잖아. 꺼져, 무신론자!";
				link.l1 = "원하시는 대로...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "네가 살아남은 것이 전혀 놀랍지 않다. 주님의 뜻은 신비하니까. 삶과 죽음은 그분의 손에 달려 있지.";
				link.l1 = "전적으로 동의합니다, 줄리안 형제님.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "정의의 섬의 성스러운 교회에 온 것을 환영한다, 아들아. 이곳의 문은 언제나 너에게 열려 있다네. 나는 줄리안 형제라 하네, 그리고 우리 위대한 주님의 종이라면 누구든 반갑게 맞이하지.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 만나서 반갑소, 줄리안 형제.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "당신에게서 물약을 좀 살 수 있을까?";
				link.l2.go = "potion";
				link.l3 = "성스러운 물건을 파는 게 있나?";
				link.l3.go = "amulet";
				link.l5 = "그냥 여기서 기도 좀 하고, 네가 어떻게 지내는지 보러 왔어. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "우리 교회를 더 자주 찾아주길 바라네. 영혼을 잘 돌보게, 내 아이야. 나는 네 몸도 치료해 줄 수 있네; 여기서 목사뿐만 아니라 의사로도 일하고 있으니.";
			link.l1 = "섬에 대해 몇 가지 물어보고 싶어.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "당신에게서 물약을 좀 살 수 있을까?";
			link.l2.go = "potion";
			link.l3 = "성스러운 물건을 파는 게 있소?";
			link.l3.go = "amulet";
			link.l4 = "가봐야겠어, 줄리안 형제. 또 보자!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "물론이지, 아들아. 어떤 물약이 필요하냐?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "간단한 치유 물약이오.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "치유의 엘릭서.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "해독제다.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "약초 혼합물.";
				link.l4.go = "potion4";
			}
			link.l5 = "미안하오, 줄리안 형제, 내 마음이 바뀌었소.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "물약? 90페소다, 아가야.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "가져가시오, 줄리안 형제.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "지금은 동전이 부족해... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "엘릭서? 500페소다, 아가.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "가져가시오, 줄리안 형제.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "지금은 동전이 부족해... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "해독제? 200페소다, 아가.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "가져가시오, 줄리안 형제.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "지금은 동전이 부족해... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "혼합물? 900페소다, 아들아.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "가져가시오, 줄리안 형제.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "지금은 동전이 부족해... 나중에 다시 올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "여기 있다. 약을 받아라. 신께서 인도해 주시길!";
			link.l1 = "감사합니다, 줄리안 형제님.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "네, 상처와 병으로부터 사람을 지켜주는 신성한 부적을 몇 개 드릴 수 있습니다. 어떤 부적이든 가격은 동일하게 금화 10더블룬입니다. 제가 드릴 수 있는 것은 "+XI_ConvertString(npchar.quest.amulet)+" 오늘.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "그래, 이 부적을 사고 싶어. 여기 네 금화다.";
					link.l1.go = "amulet_pay";
					link.l2 = "이 부적은 필요 없소, 줄리안 형제. 내가 원하는 걸 가져올 때까지 기다리겠소.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "지금은 동전이 부족해... 나중에 다시 올게.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "아니야, 아들아, 안타깝게도 더 줄 것이 없구나. 다른 날에 다시 찾아오너라, 그때는 뭔가 찾아줄 수 있을지도 모르지.";
				link.l1 = "좋아, 줄리안 형제.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "고맙다, 아들아. 네 돈은 잘 쓰일 것이다. 부적을 가져가고, 신의 축복이 있기를!";
			link.l1 = "감사합니다, 줄리안 형제님.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있다.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "어떻게 여기 오게 되었습니까, 줄리안 형제?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "당신 교구에는 몇 명이나 있습니까?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기서 물건 파는 사람 누구야?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "이 섬이 파괴될 위험이 있나? 폭풍 같은 건?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어. 미안해...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "많은 이들이 이곳에 오게 된 것과 같은 이유지, 아들아. 나는 아바나에서 누에바 에스파냐로 항해하던 중 폭풍에 배가 침몰했단다. 하느님께 감사하게도 살아남았고, 이제 여기서 그분을 섬기며 가난한 영혼들이 올바른 길을 찾도록 돕고 있지.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "내가 원하는 것보단 적지. 대부분의 나르발들은 자비보다는 폭력을 더 좋아하고, 리바도스는 가난하고 길 잃은 양들이지. 그들은 맹목적으로 이교도 의식을 행하며, 불멸의 영혼을 위험에 빠뜨리고 있어. 그들 중에 위험한 마법사가 한 명 있는데, 반드시 성스러운 종교재판으로 정화되어야 해.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "산초 카르펜테로가 플레론에 있는 선술집을 운영하고 있어. 거기서 음식, 술, 따뜻한 잠자리를 구할 수 있지. 악셀 요스트는 '에스메랄다'에서 온갖 물건을 팔고 있어. 거리의 사람들에게 물어보거라, 아들아; 바깥 고리에서 흥미로운 걸 발견하는 이들이 많으니.";
			link.l1 = "감사합니다!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "모든 것은 주님의 손에 달려 있단다, 아들아. 우리는 그분을 믿고 신뢰하지. 큰 재앙은 언제나 우리 정의의 섬을 비켜갔어\n폭풍은 자주 섬 밖에서 일어나지만, 여기서는 언제나 고요하단다.";
			link.l1 = "고맙소. 덕분에 마음이 놓였소.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐라! 내가 잠깐 생각에 잠긴 사이에, 네가 내 상자들을 뒤지기로 했구나!","내 내 상자를 뒤지려고? 가만두지 않겠다!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자들을 뒤져볼 생각이었어? 가만두지 않겠어!";
			link.l1 = "바보 같은 계집애!";
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
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋을 거야. 그거 들고 있으면 신경이 곤두서거든.","여기서는 칼을 들고 돌아다니는 거 용납 안 돼. 집어넣어.","이봐, 중세 기사처럼 칼 들고 설치지 마. 집어넣어, 너한테 안 어울리니까...");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이니 칼을 집어넣어 줬으면 하네.","이봐, 나는 이 도시의 시민이니 칼을 집어넣어 줬으면 하네.");
				link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, 친구. 무기 들고 돌아다니면 신경이 곤두서...","사람들이 무기를 뽑은 채 내 앞을 지나가는 건 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.","내가 가져간다.");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
