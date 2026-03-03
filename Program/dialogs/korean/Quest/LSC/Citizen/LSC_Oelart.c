// Оеларт Котеел - канонир
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
				dialog.text = "내 눈앞에서 꺼져라, 나리. 나는 무고한 사람을 공격하는 자들과 할 말이 없다.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕하시오, 나리! 이 날씨에 대해 어떻게 생각하시오?";
				link.l1 = TimeGreeting()+"... 나는 망망대해에서 만나는 폭풍만 아니면 어떤 날씨든 다 좋아하지...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("안녕하시오, 나리. 요즘 소식이 어떤가?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 왔어. 좋은 하루 보내, 나리!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "하하! 나도 같은 기분이야. 너는 처음 보는데... 내 이름은 오엘라르트 코틸이야. 네덜란드 전열함에서 포대장이었지.";
			link.l1 = ""+GetFullName(pchar)+". 나는 여기 처음 온 사람이야, 막 도착했지.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "나도 여기 온 지 1년도 안 됐어. 더 오래 머물고 싶지 않은데, 다들 나보고 그냥 있으라고 설득하려고만 해. 그래도 만나서 반가워!";
			link.l1 = "나도 만나서 반가워, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("안녕하시오, 나리. 요즘 소식이 어떤가?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있다.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기엔 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "섬을 떠나고 싶어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "이 섬이 어떻게 생겨났는지 알고 있나?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "그 클랜들의 배에 가본 적 있어?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "별로 특별할 것도 없어. 우리는 영국 스쿠너와 싸웠고 거의 이길 뻔했지. 놈들이 도망치길래 우리가 쫓았어. 하루가 지나고 거의 잡을 뻔했는데, 놈들이 우리 주돛대를 쏴서 결국 도망쳤지.\n그 후에, 강한 폭풍에 거의 침몰할 뻔했고, 해류에 휩쓸려 결국 우리 배는 바깥 고리 근처 암초에 내던져졌어. 살아남은 사람은 정말 얼마 없었지...";
			link.l1 = "슬프구나...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "그게 내 꿈이야. 이곳이 얼마나 지겨운지 너는 상상도 못 할 거야. 하지만 어떻게 떠나지? 전혀 모르겠어.\n여기엔 떠다니는 배도 없고, 새로 만들 기회도 없어. 그리고 장선으로 나가려 한다면 그건 자살 행위지. 폭풍이 그렇게 작은 배는 산산조각낼 거야.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "내가 정의의 섬에서 본 가장 오래된 난파선은 약 백 년 정도 되었지만, 바깥쪽 고리를 보면 섬이 훨씬 더 오래되었을 가능성도 충분히 있지. 위에서 아래까지 전부 배로 이루어져 있어서, 수심 몇 길 아래에는 정말 고대의 배들도 숨어 있을지 몰라, 눈에 보이지 않는 곳에 말이야.\n섬이 어떻게 형성되었는지에 대해서라면... 나는 해류와 폭풍이 표류하는 배들을 이곳으로 몰아와서, 인공 암초가 만들어졌다고 생각해. 그 위에 바깥 고리가 쌓인 거지.\n우리가 살고 있는 안쪽 배들은... 아마 제일 처음 이곳에 도착했거나, 어떻게든 바깥 고리를 뚫고 들어온 것일 거야. 충분히 가능한 일이야. 결국 제독과 그의 해적들도 자신들의 브리그선을 타고 우리에게 도착했으니까.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "나는 리바도스 땅에서 프로텍터와 벨라스코를 만났어. 블랙 에디가 한때 배의 대포에 대해 상담이 필요하다고 했지—왜였는지는 묻지 마, 그는 절대 말해주지 않았으니까. 그래서 흑인들 중 한 명이 나를 찾아와 암호를 알려줬어.\n경비병들이 아주 험악하니 암호 없이 통과하려고는 꿈도 꾸지 마.";
			link.l1 = "명심할게.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("나리, 뭐 하시는 겁니까... 아! 날 털고 있잖아! 그만둬!", "내가 잠깐 등 돌린 사이에 나를 훔치려 해?! 감히 어디서!", "내 바다 상자에서 손 떼, 도둑놈아!");
			link.l1 = "젠장...";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털기로 했나? 그냥 넘어가지 않을 거야!";
			link.l1 = "개년!";
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
			dialog.text = LinkRandPhrase("나리, 제발 무기를 거두어 주십시오. 불안하게 만드시네요.", "칼 들고 함부로 돌아다니지 마라, 다칠 수도 있으니까.", "칼 들고 무고한 사람들 주위를 뛰어다니는 게 그대가 생각하는 것만큼 용감한 일은 아니오, 나리. 칼 집어넣으시오.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 제발 무기를 거두어 주십시오. 불안하게 만드시는군요.", "칼 들고 막 돌아다니지 마, 다칠 수도 있으니까.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 제발 무기를 거두시오. 불안하게 하잖소.", "칼 들고 막 돌아다니지 마라, 다칠 수도 있으니까.");
				link.l1 = RandPhraseSimple("미안해.", "나는 그것을 치우고 있어.");
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
