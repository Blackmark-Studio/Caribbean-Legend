// Сесил Галард - бабулька
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "너랑 말하고 싶지 않아. 너희는 아무 이유 없이 평화로운 주민들을 공격하고 싸움을 부추기잖아. 꺼져!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "뭐 필요한 거 있나, 젊은이?";
				link.l1 = TimeGreeting()+". 내 소개를 하지 - "+GetFullName(pchar)+". 나는 새로 온 사람이야.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 무엇을 도와줄까?";
				link.l1 = LinkRandPhrase("안녕, 세실. 요즘 재미있는 소문 들은 거 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "아-아, 이제 우리 정의의 섬과 여기 사는 사람들을 알아가고 있는 거야?";
			link.l1 = "정확히, 마담?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "할라르. 세실 할라르.";
			link.l1 = "만나서 반갑습니다, Halard 부인! 영광입니다.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "나도 그래... 그런데 자네는 어떻게 여기 오게 된 거지, 젊은이? 최근에 난파된 배는 기억이 안 나는데...";
			link.l1 = "나는 스페인 본토에서 바크선을 타고 항해하다가 폭풍에 휘말려 여기까지 떠밀려 왔어... 내 배는 섬에서 멀지 않은 곳에서 침몰했지.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "그렇다면, 당신은 정말 운이 좋은 거요. 이 섬에 멀쩡히 도착했다니 말이오. 폭풍이 정의의 섬 자체를 덮치는 일은 드물지만, 이 주변 바다에서는 예고도 없이 나타나서 아무리 튼튼한 배라도 산산조각 내버릴 수 있지!\n그러니 스스로 운이 좋다고 생각하고 이곳에 익숙해지시오. 기분 상하게 하려는 건 아니지만, 여기 오는 건 쉽지만 정의의 섬을 떠나는 건 거의 불가능하오. 지난 10년 동안 아무도 살아서 나간 적이 없었으니까.";
			link.l1 = "용서해 주시오, 하지만 나는 그렇게 쉽게 절망하지 않을 것이오. 만나서 반가웠소, 알라르 부인, 다음에 또 봅시다!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "그래, 젊은이?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "그런데 어떻게 여기 오셨습니까, 마담?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기서 오래 살았지, 그렇지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기 주민들에 대해 뭐 아는 거 있어?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기서 가장 흥미로운 사람들은 누구지?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "아주 오래전 일이라, 어떻게 된 건지 거의 기억이 안 나. 난 난파당했다는 것만 알아, 하지만 자세한 건... (어깨를 으쓱)";
			link.l1 = "흠.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "어릴 때부터였어. 가끔은 내가 여기서 태어난 게 아닐까 싶을 정도로 느껴지지... 하지만 그건 물론 사실이 아니야. 그래도, 분명히 여기서 죽게 되겠지.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "내가 할 말은 많지 않다, 젊은이... 정의의 섬에는 온갖 사람들이 모여 있지. 백인, 흑인, 인디언, 도망친 노예, 귀족, 국가의 죄수, 선원들... 예전엔 이보다 더 많았지. 모두 저마다의 사연과 습관이 있다네. 어떤 이는 여기 있는 게 만족스럽고, 또 어떤 이는 끊임없이 떠날 꿈만 꾸지.\n그리고 클랜들도 있지 - 나르발과 리바도스, 여기에 해적들이 균형을 맞추고 있어. 세상 어디에서도 볼 수 없는 다양한 사람들이 이곳에 섞여 살아가고, 비교적 평화롭고 조화롭게 지내고 있다네...";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "슈미트 나리, 나르발의 기계공이자 발명가... 산초 카르펜테로, 이곳의 바텐더... 그리고 이제는 샤크 도드슨 제독과 그의 친구 레이튼 덱스터도 있지.\n하지만 정말로, 직접 가서 이 사람들 중 몇 명이라도 만나보는 게 좋을 거야. 우리 정의의 섬 사람들에게 얼마나 흥미로운 이야기들이 많은지 너는 상상도 못 할걸.";
			link.l1 = "그렇게 생각해 보지...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("이봐, 도둑놈! 거기서 멈춰!", "등 돌린 노파를 털다니? 감히 그런 짓을 하다니!", "내 상자를 털기로 했나? 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "등 돌린 할머니를 털다니? 감히 그런 짓을 하다니!!";
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
			dialog.text = LinkRandPhrase("무기 집어넣어, 젊은이. 그거 보면 신경이 곤두서.", "있지, 이 정의의 섬에서 무기를 함부로 휘두르는 사람한테는 안 좋은 일이 생겨. 집어넣어.", "젊은이, 검을 집어넣어라. 늙은 여자를 놀라 죽게 만들 셈이냐!");
			link.l1 = LinkRandPhrase("좋아.", "그래.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기 집어 넣어라, 젊은이. 그거 들고 있으니 불안하구나.", "있지, 이 정의의 섬에서 함부로 무기를 휘두르는 사람들은 안 좋은 일을 겪게 돼. 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "그래.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기 집어넣어, 젊은이. 그거 들고 있으니 불안하군.", "젊은이, 칼을 집어넣어라. 늙은 여자를 놀라 죽게 만들 셈이냐!");
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
