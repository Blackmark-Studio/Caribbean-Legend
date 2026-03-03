// Куранай - индеец
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
				dialog.text = "창백한 얼굴의 개가 하얀 형제자매들을 다치게 했어. 나는 너랑 말 안 해. 가.";
				link.l1 = "오...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "하얀 형제는 무엇을 원하지?";
				link.l1 = TimeGreeting()+". '하얀 형제'? 말해 봐, 왜 너희 인디언들은 우리를 하얀 형제라고 부르거나 창백한 얼굴의 개라고 부르지, 응?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("안녕, 쿠라나이. 요즘 정의의 섬에서는 무슨 일이 있었어?", "섬에 무슨 새로운 일이라도 있었어?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "뭘 찾았는지 보여 줘봐, 내가 뭐라도 살지 모르니까...";
					link.l3.go = "trade";
				}
				link.l5 = "그냥 어떻게 지내는지 궁금해서 와봤어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "여기서는 모두 평화롭게 살아, 하얀 형제. 나는 하얀 형제를 창백한 개라 부르지 않아. 모든 창백한 얼굴이 개는 아니지, 인디언 중에도 '붉은 피부 개'라고 부르는 놈들 많아.";
			link.l1 = "철학자처럼 들리는군.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "나는 네 말을 이해 못하겠어, 하얀 형제. '철학자'가 무슨 뜻이야?";
			link.l1 = "상관없어, 붉은 피부 형제여. 난 네 생각하는 방식이 마음에 들어. 내 이름은 "+GetFullName(pchar)+". 너는 이름이 뭐야?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "쿠라나이가 내 이름이오. 백인 형제의 이름을 알게 되어 기쁘오.";
			link.l1 = "쿠라나이... 그래, 또 보자!";
			link.l1.go = "exit";
			link.l3 = "섬에 대해 몇 가지 묻고 싶은 게 있어, 쿠라나이.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "물어봐라, 하얀 형제여. 내가 대답하지.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기엔 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기 정의의 섬에서 무슨 일을 하시나요?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "집에 가고 싶어?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "섬에서 평화롭게 지내나요? 여기서 싸움이나 다툼이 일어나기도 하나요?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "나와 내 부족의 전사 일곱 명이 우리 섬에서 멀지 않은, 맑은 날이면 보이는 작은 섬으로 항해하기로 했어. 우리는 대나무로 뗏목을 만들고 떠났지. 그런데 갑자기 폭풍이 닥쳐와 우리를 망망대해로 데려가 버렸어. 우리가 얼마나 빨리 땅과 섬이 사라지는지 미처 깨닫지 못했지.\n우리는 수많은 밤과 낮을 바다 위에서 떠돌았어. 내 형제들은 모두 목마름과 굶주림으로 죽었지. 나만 홀로 남았어. 영혼들이 나를 불쌍히 여겨 이 섬까지 뗏목을 이끌어 준 거야.";
			link.l1 = "그렇군... 슬픈 이야기네.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "나는 물고기를 잡아. 작살로 물고기를 때려. 가끔, 아주 가끔 큰 게를 맞혀. 그럴 때면 나는 기뻐. 게는 맛있거든, 아주 맛있어. 게 한 마리면 며칠은 충분해. 그리고 나는 또 큰 게가 없는 한 곳에서 바닥까지 잠수해. 노란 돌, 파란 돌, 검은 돌, 그리고 진주를 주워. 큰 것도, 작은 것도. 그런 다음 나는 그걸 하얀 형제, 하얀 자매에게 팔아.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "집에 가고 싶어. 하지만 집이 어디지? 마을이 어디 있는지도, 거기로 어떻게 항해해야 하는지도 모르겠어.";
			link.l1 = "흠, 정말 미안하네...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "나르발과 리바도스 부족은 자주 서로 싸워. 두 명의 추장이 있는데, 한 명은 다른 한 명을 증오하지. 언젠가는 한 명이 다른 한 명을 죽일 거야. 나는 그걸 봐. 우리 나머지는 평화롭게 살고 아무도 해치지 않아. 가끔 백인 형제들이 불술을 마시고 욕을 하긴 하지만... 죽이진 않아. ";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("멈춰라, 창백한 놈! 네 것이 아닌 건 가져가지 마!", "내가 안 볼 때 창백한 얼굴 놈이 훔쳐 갔다고?! 아니야!", "저 광산은 내 거야, 창백한 놈! 네 것이 아닌 건 절대 못 가져가게 해!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털려고 작정했나? 가만두지 않겠다!";
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
			dialog.text = LinkRandPhrase("나는 하얀 형제의 벗은 칼을 보고 싶지 않아. 집어 넣어.", "백인 형제자매들은 네가 칼을 들고 다니는 걸 좋아하지 않아. 멈춰, 형제.", "영웅 흉내 내지 마, 하얀 형제. 칼 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.", "그래.", "미안해...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "나는 여기서 평화롭게 살고 있어. 손에 무기를 들고 다니는 건 옳지 않아.", "멈춰, 하얀 형제여. 칼 집어넣어라, 그거 무서워.");
				link.l1 = LinkRandPhrase("좋아.", "뭐, 그러든가.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "하얀 형제여, 칼 집어넣어. 그거 보면 신경이 곤두서...", "백인은 칼을 쥐면 쓸 생각이 있다는 뜻이지. 집어넣어...");
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
