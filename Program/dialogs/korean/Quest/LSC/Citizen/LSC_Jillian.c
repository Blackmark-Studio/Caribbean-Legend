// Джиллиан Стайнер - просто девушка
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
				dialog.text = "저리 가! 거리에서 싸움이나 거는 놈이랑은 말 안 해.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "오... 안녕하세요! 깜짝 놀랐잖아요. 오시는 소리를 못 들었어요... 도와드릴 일이라도 있나요?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 나는 이 섬에 처음 온 사람이야. 여기 사람들을 알아가고 있는데, 이렇게 예쁜 아가씨를 그냥 지나칠 수 없더라고. 이름이 뭐야?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 도와줄까?";
				link.l1 = LinkRandPhrase("질리안! 잘 지냈어? 무슨 소식 있어?", "섬에 무슨 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그저 안부가 궁금해서 왔소, 마담. 안녕히 가시오!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "저를 부끄럽게 만드시네요, 나리, 하지만 기쁩니다. 칭찬해 주셔서 감사합니다. 제 이름은 질리안, 질리안 슈타이너입니다.";
			link.l1 = "정말 반갑군, 질리안.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "여기 처음이라고 했지? 어떻게 오게 된 거야? 난파선을 겪고 살아남은 거냐?";
			link.l1 = "뭐... 비슷한 거지. 나는 바크선을 타고 여기까지 항해했는데, 암초를 거의 통과할 뻔했어. 하지만 불행하게도 바깥쪽 고리에 부딪혀서 내 배가 침몰했지. 내 선원들 중에서 나 혼자만 이곳까지 헤엄쳐 올 수 있었어.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "오! 그래서 네가 정의의 섬을 일부러 찾아온 거야? 믿을 수가 없네!";
			link.l1 = "그래, 내가 좀 미쳤었지. 전설의 정의의 섬을 찾기로 결심했고, 결국 찾아냈어. 하지만... 이제 어떻게 떠나야 할지 모르겠군.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "너 정말 용감하거나 무모하구나. 여길 자진해서 항해해 오다니... 이제 우리랑 같이 여기 갇힌 거야; 수년 동안 이곳을 떠난 사람은 아무도 없었어.";
			link.l1 = "나는 아직 희망을 가지고 있어. 좋아, Jillian, 고마워, 이제 네 하루를 보내도록 할게. 그럼 이만, 마담!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "그래, 물론이지, "+pchar.name+". 듣고 있네.";
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
				link.l3 = "그럼 하루하루를 어떻게 보내고 있소?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "결혼하지 않았다고 했지... 이렇게 예쁜 아가씨에게 구애하는 이가 없단 말이야?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어. 미안...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "나는 부모님과 함께 영국에서 출항했어. 우리는 가난했고 신세계에서 새로운 삶을 시작하고 싶었지. 그런데… 우리 배가 폭풍에 휘말렸을 때 부모님이 돌아가셨어. 나는 간신히 살아남았어. 바깥쪽 고리의 난파선에 도착해서 하루 동안 정신을 잃고 누워 있었는데, 누군가가 나를 발견했지.\n나는 새로운 삶을 시작했지만, 아마도 부모님이 꿈꿨던 삶은 아닐 거야.";
			link.l1 = "미안해...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "그리고 어디로 가란 말이야? 누가 나를 받아주겠어? 집도 없고, 남편도 없고, 돈도 없어. 런던 빈민가랑 이 정의의 섬 말고는 아는 곳도 없고... 여기서 사는 게 내 운명이라면, 받아들여야지. 여자한테 일어날 수 있는 일 중에 최악은 아니니까.";
			link.l1 = "그렇군, 그러려니 하지.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "나는 주로 교회에서 줄리안 형제를 돕고 있어. 그리고 악셀 가게에서 이것저것 잡일도 해. 그렇게 돈을 벌지. 바깥쪽 난파선 위를 기어다니는 건 내겐 무리거든.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "히히... 구경꾼들은 많지, 하지만 쓸 만한 놈은 하나도 없어. 마음에 들지 않는 남자랑은 절대 같이 살고 싶지 않아. 내가 좋아하는 남자들은 나한테 관심도 없어. 나는 그냥 평범한 가난한 여자일 뿐이야...";
			link.l1 = "분명 누군가를 찾게 될 거야, 그리고 너에겐 앞으로 살아갈 날이 많이 남았지...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("아, 도둑놈!", "그 더러운 손 치워, 그건 내 거야!", "내가 내 상자를 열라고 허락한 적 없잖아!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 가슴에서 손 떼, 도둑놈아!";
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
			dialog.text = LinkRandPhrase("나리, 제발 무기를 거두어 주십시오. 저를 겁주고 계십니다.", "이 섬 사람들은 네가 칼 들고 돌아다니는 걸 싫어해.", "칼 들고 뛰어다니는 남자들은 나한테 아무런 인상도 못 줘. 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이 섬 사람들은 네가 칼 들고 돌아다니는 걸 싫어해.", "칼을 집어넣어 주시오, 나리. 무장한 사람들이 뛰어다니면 우리 모두 불안해진다.");
				link.l1 = LinkRandPhrase("좋아.", "실례합니다...", "미안합니다, 마담...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 제발 무기를 거두어 주십시오. 무섭게 하시잖아요.", "칼 들고 뛰어다니는 놈들 따윈 안 무서워. 집어넣어.");
				link.l1 = RandPhraseSimple("미안해...", "나는 이걸 치우고 있어.");
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
