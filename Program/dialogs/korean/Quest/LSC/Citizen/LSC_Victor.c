// Виктор Кассель - бандит
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
				dialog.text = "꺼져, 이봐. 난 죄 없는 사람들 싸움 붙이는 녀석들이랑 얘기하고 싶지 않아. 사라져!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "흠... 뭐야, 친구? 말이나 나누고 싶다면 실망하게 될 거야...";
				link.l1 = "아쉽군... 나도 이야기하고 싶었는데. 나는 여기 온 지 얼마 안 된 신참이라 사람들을 이제 막 알아가고 있어...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! 뭐야, 뭘 원해?";
				link.l1 = LinkRandPhrase("빅토르! 나한테 들려줄 소식 있나?", "섬에서 무슨 새로운 일이라도 있었어?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내나 궁금해서 왔어. 잘 가.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "새로 온 놈인가? 흠... 좋아. 나는 빅토르 카셀이다. 내가 기분 안 좋을 때는 건드리지 않는 게 좋을 거다. 아니, 기분 좋을 때도 마찬가지지. 쓸데없는 수다에 시간 안 써. 누가 들이대면, 난 더 세게 받아친다. 알아둬. ";
			link.l1 = "나는 "+GetFullName(pchar)+", 나도 세게 밀어붙일 수 있지만, 그럴 필요는 없길 바란다. 네가 사교적이지 않으면, 나도 귀찮게 하지 않겠다. 잘 가.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("빅토르! 나한테 들려줄 소식 있어?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "섬에 대해 몇 가지 질문을 하고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "빨리 해.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기서의 삶은 어떤 모습일까?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기서 가장 중요한 사람이 누구지?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "이 섬에서 돈을 벌 수 있는 곳이 어디지?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "왜 신경 쓰지? 난 그 얘기 하고 싶지 않아, 특히 모르는 놈이랑은 더더욱.";
			link.l1 = "제기랄... 미안.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "지루해 보여. 피곤하고, 따분하고, 아무 의미도 없는 지루함이지. 난 샤크 놈 해적들한테 붙을 거야 - 적어도 그 녀석들은 가끔 한판 붙으니까. 언젠가는 그놈들도 정의의 섬에서 빠져나갈 방법을 찾겠지. 그날이 오면, 나도 같이 있고 싶어.";
			link.l1 = "정말로...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "당연히 제일은 제독이지! 나르발과 리바도스를 손아귀에 쥐고 있는데, 걔네들은 어쩔 도리가 없어. 그 다음으로는 각 클랜의 우두머리들, 나르발의 도널드 그린스파이랑 리바도스의 블랙 에디가 있지. 그 다음은 나르발 상인 악셀 요스트가 오고. 그리고 선술집 주인 산초 카르펜테로도 빼놓을 수 없지 - 독한 술 없이는 못 버티거든, 허허!\n";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "상자들이야, 물론 있지. 하지만 먼저 자물쇠를 따야 해; 여기선 서로를 믿지 않으니 모든 상자에 자물쇠가 달려 있거든. 그리고 말인데, 친구, 제일 좋은 장신구들은 배 안에, 주인들이 지키는 곳에 숨겨져 있어.\n바깥쪽 고리도 탐험할 수 있지만, 썩은 갑판에 빠지지 않게 조심해. 아니면 거대한 게를 사냥할 수도 있어; 집게살은 꽤 비싼 값에 팔 수 있거든.";
			link.l1 = "알겠어...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("이봐, 이 개자식아! 나한테 까불지 말라고 했지. 내 가슴에서 손 떼!", "네가 성가신 놈인 줄 알았지. 감히 날 털려 한다면 제대로 맛 좀 보여주마!", "잘 됐군, 너한테 좀 거칠게 굴 핑계가 필요했거든!");
			link.l1 = "아르그!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자를 털기로 작정했나? 그냥 넘어가지 않을 거야!";
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
			dialog.text = LinkRandPhrase("이봐, 그 칼 좀 집어넣어. 우스꽝스러워 보여.", "있잖아, 친구, 그거 안 치우면 상어가 널 타르타로스에 던져버릴 거야...", "그 칼 치워, 바보처럼 보이잖아.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 그 칼 좀 집어넣어. 우스꽝스러워 보여.", "있잖아, 친구, 그거 안 집어넣으면 상어가 널 타르타로스에 처넣을 거야...");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 그 칼 좀 집어넣어. 우스꽝스러워 보여.", "그 칼 치워, 바보처럼 보이잖아.");
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
