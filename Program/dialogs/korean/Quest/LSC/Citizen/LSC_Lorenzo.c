// Лоренцо Сольдерра - испанский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

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
				dialog.text = "너 같은 도적놈에게 할 말 없다. 썩 꺼져라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "흠, 너 프랑스 놈이냐? 우리 사이에 할 말은 없는 것 같은데.";
				link.l1 = "흥미롭군, 왜 안 되겠어? 이 정의의 섬에서는 국제적인 적대감이 별 의미가 없다고 생각해...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("적어도 최근 소식은 말해 줄 수 있겠어?", "섬에 무슨 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 와봤어. 잘 있어, 로렌초.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그럴 생각 없어. 나는 장교이자 신사야. 엘 에스코리알의 적들과는 유럽에서도, 카리브에서도, 이 정의의 섬에서도, 어디서든 어울리지 않아. 가던 길 가, 나리!";
			link.l1 = "후-읏. 원하는 대로 해...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
		case "meeting_no":
			dialog.text = "분명히 말했을 텐데: 나는 우리 나라의 적들과 어울리지 않아!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있다.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("프랑스 도둑놈! 내가 본때를 보여주마!", "개자식아! 내가 등 돌린 사이에 내 물건을 집어가? 죽여버릴 거야!", "내 물건을 훔치려는 거냐? 좋아. 검 연습 좀 하고 싶었거든, 재수 없는 프랑스 놈아!");
			link.l1 = "거만한 돈놈! 각오해라!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털려고? 가만두지 않겠다!";
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
			dialog.text = LinkRandPhrase("프랑스 놈, 무기는 집어넣는 게 좋을 거다, 아니면 내가 직접 쓰게 만들어 줄지도 모르니까...", "용기가 있다면 그 무기로 나를 시험해 봐도 좋아... 그렇지 않으면 집어넣어.", "칼을 들었다고 해서 귀족도 아니고 잘생겨지는 것도 아니야, 프랑스 놈. 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "프랑스 놈, 무기 집어넣는 게 좋을 거다, 아니면 내가 직접 쓰게 만들어 줄지도 모르니까...", "용기가 있다면 그 무기로 나를 시험해 봐라... 그렇지 않으면 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "그럴 필요 없어... 집어넣고 있으니까.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "프랑스 놈, 무기는 집어넣는 게 좋을 거다. 아니면 내가 직접 쓰게 만들어 줄지도 몰라...", "용기가 있다면 그 무기로 나를 시험해 봐도 좋아... 그렇지 않으면 집어넣어.");
				link.l1 = RandPhraseSimple("그럴 필요 없어, 내가 치울게.", "나는 그것을 치우는 중이야.");
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
