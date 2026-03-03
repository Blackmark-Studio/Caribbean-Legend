// Джаспер Пратт - каторжник
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
				dialog.text = "날 내버려 둬, 나리. 난 죄 없는 사람 해친 놈들이랑 말 안 해! 너야말로 나보다 더 범죄자잖아!";
				link.l1 = "내가...?";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 나리. 뭐 필요한 거라도?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 나 여기 처음 왔어. 이름을 물어봐도 될까?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 원하는 거라도 있어?";
				link.l1 = LinkRandPhrase("안녕, Jasper. 요즘 소식 들은 거 있어?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 보러 왔어. 다음에 보자, Jasper!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "나? 나는 재스퍼 프랫이야. 사람들이 날 '섬의 죄수'라고 부르는 거 들었을 거야. 그래서 다들 나를 곁눈질로 보는 거지. 에이, 그런 놈들 신경 안 써. 나는 그냥 나일 뿐이야...";
			link.l1 = "네가 예전에 어떤 사람이었는지는 상관없어, 지금 어떤 사람인지만 중요해.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "모두가 너처럼 생각하는 건 아니라서 아쉽군, 이봐.";
			link.l1 = "글쎄, 나는 자유분방한 태도로 유명하지...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "잘했어. 걱정하지 마. 내 과거가 어떻든, 난 정의의 섬 주민들의 지갑이나 상자엔 손 안 대. 드디어 평화롭게 살 수 있어서 기뻐.";
			link.l1 = "만나서 반가워, Jasper. 다음에 또 보자!"
			link.l1.go = "나가기";
			link.l2 = LinkRandPhrase("안녕, Jasper. 요즘 소식 들은 거 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "대답해 줄 수 있으면 해주지. 물어봐.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "어떻게 정의의 섬에 오게 되었소?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기 마음에 들어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "사람들이 너를 곁눈질한다고 했지. 그거, 네 과거 때문이야?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "이 섬, 꽤 흥미롭지 않아?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "쿠바 플랜테이션에서 도망쳤지. 우리 다섯 명이었는데, 등골이 휘도록 일하거나 매일 두들겨 맞느니 차라리 죽는 게 낫겠다 싶었거든. 경비병들을 속여서 정글로 사라졌어. 해안에 도착하자 뗏목을 만들었지.\n토르투가로 가려고 했지만 우리 중 누구도 항해법을 몰랐으니 길을 잃고 말았어. 그러다 물도 다 떨어지고... 그 일은 더 생각하고 싶지 않아. 아무튼, 이 섬에 도착해서 살아남은 건 나 혼자뿐이었지.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "있잖아, 난 여기 마음에 들어. 플랜테이션에서 겪은 일들 생각하면, 이곳은 정말 지상낙원 같아. 난 많이 필요 없어... 음식 좀, 물, 저녁에 럼 한 잔이면 돼 - 그리고 여기선 아무도 내 가죽을 채찍질하려 들지 않지. 그거면 머물 이유로 충분해. 내 때가 오면 여기서 죽는 것도 기꺼이 받아들일 수 있어.";
			link.l1 = "그런 것 같군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "문제는, 이 섬이 도둑놈 놀이터가 됐다는 거야. 밤마다 들이닥치는데, 자물쇠 따위는 소용없지. 주로 해적들이 사는 제독 방 근처에서 약탈을 해. 누구나 한 번쯤은 자기 궤짝이 완전히 털린 적이 있지.\n도둑이 누군지 아무도 몰라서, 다들... 음... 전과 있는 사람들을 의심하고 있어.\n근데 이 도둑놈이 좀 이상해. 술병이랑 특정 장신구만 훔쳐가고, 진짜 값나가는 건 건드리지도 않아. 웃기지 않아?";
			link.l1 = "그래, 웃기네...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "그래. 이 섬 안쪽에 있는 배들 주위를 많이 헤엄쳐 다녔지. 물에서 나갈 수 있는 곳은 많지 않아. 산 아우구스틴, 밧줄 다리 양쪽으로 기울어진 갑판, 글로리아는 쓰러진 돛대 위로 올라가야 하고...\n피닉스 근처로 헤엄쳐서 세레스 쪽으로 돌면 메리 캐스퍼 선실로, 배의 선수 쪽을 통해 들어갈 수 있어.\n타르타로스 배 밑바닥에 난 구멍은 감옥으로 이어져. 산 아우구스틴 선수에도 구멍이 하나 있는데, 그건 제독의 저장고로 통하지. 하지만 거긴 들어가지 마. 경비병들이 널 베어버릴 거야. 타르타로스 맨 아래쪽 문이 잠겨 있는 데는 다 이유가 있으니까.\n그리고 물론 페르난다, 외딴 플라이트 배에도 올라탈 수 있지. 아무도 안 산다고들 하지만, 난 종종 선실 안에서 불빛을 봤고, 가끔은 술 마시는 노래 소리도 들려... 그리고 남자가 고통인지 슬픔인지 모를 울음소리도 들리더라.";
			link.l1 = "흥미롭군... 탐험할 게 정말 많아.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("아! 저기 도둑이다! 바로 저기 있어!", "내가 범죄자라니?! 손 떼, 나리!", "도둑을 찾았어! 여기 있어! 여기 있다고!");
			link.l1 = "잠깐, 안 돼!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 가슴에서 손가락 빼! 살려줘!";
			link.l1 = "젠장!";
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
			dialog.text = LinkRandPhrase("이봐, 제발 칼 좀 집어넣어! 사람들 겁주고 있잖아.", "그걸 아무한테나 흔드는 거 들키지 마라... 그러다간 타르타로스에 가게 될 거야.", "여기서 칼을 휘두를 필요 없어. 여긴 친구들끼리 있는 곳이니까.");
			link.l1 = LinkRandPhrase("좋아.", "미안해.", "좋아...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 나리, 그거 집어넣어. 여기선 칼 필요 없어.", "여기가 내 집이야, 그리고 사람들이 칼을 휘두르지 않으니까 안전하지. 그거 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "좋아, 그럼.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 제발 칼 좀 집어넣어! 사람들 겁주고 있잖아.", "여기가 내 집이야, 그리고 사람들이 칼 휘두르고 다니지 않으니까 안전하지. 그거 집어넣어.");
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
