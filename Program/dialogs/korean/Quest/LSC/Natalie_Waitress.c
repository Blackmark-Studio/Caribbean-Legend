// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "오! 그리고 사람들이 당신이 익사했다고 하더군... 거짓말쟁이들!";
				link.l1 = "그래, 그놈들 했지! 하! 난 멀쩡해!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "좋은 하루요, "+GetAddress_Form(NPChar)+"! 처음 와봤나? 전에 본 적 없는 얼굴인데... 자주 들러주면 좋겠어, 산초가 정말 다양한 술을 내놓거든. 아, 그리고 내 이름은 나탈리야, 산초가 선술집 일 보는 걸 도와주고 있어.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 만나서 반갑소. 나를 전에 본 적은 없을 거요. 나도 여기 온 지 얼마 안 되었으니.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("재미있는 얘기라도 있어?","섬에 무슨 새로운 일이 있었나?","최신 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "최근에? 또 다른 배가 난파됐나? 나는 아무 소식도 못 들었는데... 아니면 튀람 나리처럼 돛대 잔해를 타고 여기 온 거야? 아, 내 호기심을 용서해 줘, 여자란 원래 그런 거니까.";
			link.l1 = "아니야, 괜찮아, 나탈리. 나는 바크선을 타고 여기 도착했는데, 그 배가 가라앉았어. 만나서 반가웠어. 또 보자!";
			link.l1.go = "exit";
			link.l2 = "아니, 괜찮아. 그냥 정의의 섬에 대해 몇 가지 물어보고 싶었을 뿐이야.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있다.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "너는 선술집에서 일하지. 주인에 대해 뭐 좀 말해줄 수 있나?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "그런데 어떻게 여기까지 오게 되었소?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기에는 몇 명이 살고 있지?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기서 새로운 얼굴을 봐도 전혀 놀라지 않나?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례하겠습니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "좋은 일만 있지,  "+GetAddress_Form(NPChar)+" 산초는 항상 다양한 술을 갖추고 있지. 오래된 와인부터 평범한 에일, 럼주까지 다 있어. 몇 년 전에 산초가 오래된 와인을 대량으로 발견했거든. 산초가 두 달 동안이나 병 상자를 가게로 옮겼지\n그래서 지금은 예전 군도에서나 총독들이나 마실 수 있었던 와인도 넉넉하게 있지. 럼주도 문제없어. 산초는 술뿐만 아니라 신선한 소식, 좋은 조언, 그리고 하룻밤 따뜻한 잠자리까지 마련해 줄 수 있어.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "아, 슬픈 이야기네요. 7년 전, 저는 구혼자와 함께 부모님 집에서 도망쳐 산티아고에서 벨리즈로 이주하기로 했어요. 항해사가 마인 근처에서 실수해서, 우리는 북쪽으로 잘못 항해했고 폭풍을 만났죠. 우리 배는 바깥 고리에서 멀지 않은 곳에서 침몰했어요\n그날 제 구혼자를 비롯해 대부분이 죽었어요. 살아남은 사람들과 저는 여기, 정의의 섬에서 새로운 삶을 시작했죠.";
			link.l1 = "슬픈 이야기군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "꽤 많지. 리바도스랑 나르발 두 부족은 인원도 많고, 여기서 수십 년을 살아왔거든. 평범한 사람들은 얼마 없지만, 선술집은 매일 밤마다 사람들로 가득 차. 난 겨우 술이나 따라주고 있는 셈이지.";
			link.l1 = "정말이야? 흥미롭군.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "우리가 왜 그래야 하지? 새로운 얼굴들이 자주 들어오거든. 여기 몇 명이나 사는지도 모르겠어. 가끔 어떤 남자를 처음 보는데, 그가 여기서 1년이나 살았다고 하더라고.";
			link.l1 = "음...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에, 네가 내 상자를 뒤지기로 했구나!","내 상자를 뒤지려고? 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자들을 뒤져볼 생각이냐? 가만두지 않겠다!";
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
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋을 거야. 그런 거 보면 신경이 곤두서거든.","여기서는 칼을 들고 돌아다니는 거 용납 안 돼. 집어넣어.","이봐, 중세 기사처럼 무기 들고 돌아다니지 마. 집어넣어, 너한테 안 어울려...");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이야. 그러니 칼을 집어넣어 줬으면 해.","이봐, 나는 이 도시의 시민이야. 그러니 칼을 집어넣어 줬으면 해.");
				link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, 친구. 무기 들고 돌아다니면 신경이 곤두서거든...","사람들이 무기를 뽑은 채 내 앞을 지나가는 건 싫어. 무섭거든...");
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
