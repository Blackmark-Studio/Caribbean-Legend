// Таннеке Эверс - просто девушка
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
				dialog.text = "날 내버려 둬, 나리. 나는 평화롭게 지내는 사람을 공격하는 자와는 말하고 싶지 않아!";
				link.l1 = "음...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "좋은 하루요! 내가 당신을 아나? 전에 본 적이 없는 것 같은데...";
				link.l1 = TimeGreeting()+". 나는 새로 왔어, 맞아. 내 이름은 선장 "+GetFullName(pchar)+"";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("안녕, 타네케. 정의의 섬에 새로운 소식이라도 있어?", "섬에 무슨 새로운 일이라도 있었어?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 와봤어. 좋은 하루 보내!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "전 선장이지. (씨익)";
			link.l1 = "뭘…? 아, 알겠군. 아니, 난 아직도 선장이야. 내 배는 스페인 본토 해안에 정박해 있지. 나는 바크선을 타고 여기까지 왔어. 아니, 거의 도착할 뻔했지. 그 바크선은 구멍이 나서 해안에서 두 마일 떨어진 곳에 가라앉았거든.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "그런데 어떻게 폭풍을 견뎌냈소?";
			link.l1 = "무슨 폭풍? 난 아무 폭풍도 기억나지 않는데...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "어떻게 모를 수가 있겠어? 정의의 섬 주위엔 항상 폭풍이 몰아치거든. 모두가 그렇게 말하지.";
			link.l1 = "음... 나는 운 좋게도 그걸 피할 수 있었지. 바다는 정말 고요했어... 실례지만, 이렇게 아름다운 아가씨의 이름을 알 수 있을까?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "오! 미안해, 자기소개를 깜빡했네... 내 이름은 타네케야. 만나서 반가워.";
			link.l1 = "나도 만나서 반가워, 타네케... 정말로 영광이야.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "그런데 왜 네 배를 바크로 바꿨지?";
			link.l1 = "정의의 섬에 대한 소문을 듣고, 내 눈으로 직접 확인해 보기로 했지. 내 배를 위험에 빠뜨리고 싶지 않아서 블루웰드에 정박시키고, 이 지역을 탐험하려고 바크선을 하나 샀어...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "이제 알겠군. 너도 아돌프 바르비에처럼 캡틴 알바라도의 책을 너무 읽고 베탕쿠르 제독의 금을 찾으러 온 거지. 안타깝게도, 선장, 바르비에 같은 교활한 놈도 못 찾은 걸 네가 찾을 수 있을지 의심스럽군.\n그리고 난 애초에 제독의 금이란 게 있다고 생각하지도 않아. 안토니오가 자기 할아버지를 대단해 보이게 하려고 지어낸 얘기일 거야.\n뭐, 이제 우리랑 같이 있게 되겠군! 여기 오는 건 쉬웠겠지만, 나가는 건 불가능해 — 살아서 나가려면 말이지.";
			link.l1 = "금이라고? 베탕쿠르 제독? 난 처음 듣는 얘기인데... 아무튼, 나는 이 섬을 무사히 떠날 생각이야. 너랑 이야기해서 즐거웠어, 타네케. 잘 가!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "물어보시오, 선장...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "정의의 섬을 떠나려고 해본 적 있어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기서 어떻게 지내고 있소?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "음... 여자들도 제독한테 음식을 사야 하나, 아니면 그냥 공짜로 주는 거야?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "나는 네덜란드 태생이지만 산티아고에서 살았어. 부모님이 나를 거기 있는 제랄디 은행가 집안에 하녀로 보내셨지. 그 집안 들어봤어? 3년 전에 그들 중 한 명이 커리어 루거를 타고 누에바 에스파냐로 떠났어. 나는 그를 따라가라는 지시를 받았지.\n항해 이틀째 되는 날, 우리 배는 스페인 국기를 단 브리건틴에게 붙잡혔어. 그쪽 장교가 우리 배에 올라와서 선장과 무슨 얘기를 했는데, 내용은 몰라. 선장은 화가 머리끝까지 나서 그 장교를 루거에서 쫓아냈지. 장교가 자기 배로 돌아가자마자, 그들은 우리에게 포격을 가했어.\n우린 도망치려 했지만 결국 그들이 우리 배에 올라탔어. 내 생각엔 그들이 내 주인인 제랄디를 노린 것 같아. 그들은 곧장 그의 선실로 달려가서 그를 족쇄로 묶고 데려갔거든. 나랑 선원들은 창고에 가둬졌지.\n나는 그들이 우리를 침몰시킬 줄 알았는데, 그냥 떠나버렸어. 선원들이 간신히 창고에서 빠져나왔지. 갑판에 나가보니 선장은 이미 죽어 있었어. 우리 중 누구도 제대로 항해할 줄 몰랐지.\n우리는 아무것도 모른 채 떠돌다가, 거센 폭풍에 휩쓸렸어. 몇 시간 뒤, 우리 루거는 외곽 고리로 내던져졌지. 아직도 거기 있어. 새벽이 되자, 나와 몇 남지 않은 생존자들이 루거의 장정선에 올라 정의의 섬까지 노를 저어왔어.";
			link.l1 = "정말 대단한 이야기네!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "아니. 내가 어떻게 알겠어? 쓸 만한 배도 없고, 장주로 나가려다간 죽으러 가는 거지. 말했잖아, 정의의 섬은 폭풍에 둘러싸여 있다고.\n예전에 이 방식으로 탈출하려던 현지인 다섯이 있었어. 그들은 난파된 인디아맨에서 건진 튼튼한 목재와 좋은 돛으로 제법 괜찮은 장주를 만들었지. 아홉 시간이나 조류와 싸우다가 겨우 망망대해로 나갔어. 며칠 뒤, 그들 중 한 명이 돛대 잔해에 묶인 채 외곽 고리로 돌아왔지... 완전히 죽은 채로.\n그 일 이후로 떠나려는 사람은 거의 없어.";
			link.l1 = "끔찍하군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "괜찮아. 저 거만한 고리대금업자 집안의 하인으로 사는 것보단 나쁘지 않지. 이곳에 익숙해지기만 하면, 오히려 정이 들 수도 있어. 많은 사람들이 그렇게 느끼거든. 그리고 그 클랜들, 나한텐 별로 신경 쓰이지 않아.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "물론 사지. 여자에게도 할 일이 많아. 청소, 요리, 남 돕기... 한가하진 않지만 그렇다고 죽어라 일하는 것도 아니야. 해적들은 평민들한텐 음식을 싸게 팔지만, 부족들한텐 가차 없이 바가지를 씌워. 그래서 굶지는 않아.\n나는 질리언이랑 나탈리를 도와주고, 나도 필요할 땐 그들이 날 도와줘. 우리끼리는 친구야. 섬에 또 다른 여자애가 있는데, 스페인 애야. 이름은 라모나. 근데 걔는 주로 혼자 지내고, 우리도 딱히 친구가 되고 싶진 않아.";
			link.l1 = "그건 왜지?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "음... 그냥 우리가 인생을 바라보는 관점이 다르다고 해두지. 그녀와 얘기해 보면 알게 될 거야.";
			link.l1 = "좋아...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("누구... 이런 맙소사, 도둑이다! 도와줘!", "잠깐 한눈 판 사이에 나를 털려고 해?! 도와줘!", "내 상자를 털기로 마음먹었나? 이대로 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "감히 내 물건에 손대다니! 누구 없나, 도와줘!";
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
			dialog.text = LinkRandPhrase("무기를 거두시오, 나리. 불안하게 하잖소.", "여기서는 칼을 들고 돌아다니는 거 용납 안 돼. 집어넣어.", "나리, 당신이 용감한 분이라는 건 이미 알고 있소. 굳이 칼을 휘둘러 증명할 필요는 없소...");
			link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기를 거두어 주시오, 나리. 당신 때문에 불안해지잖소.", "여기서는 칼 들고 돌아다니는 거 용납 안 돼. 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기를 거두시오, 나리. 불안하게 하잖소.", "나리, 당신이 용감한 분이라는 것쯤은 잘 압니다. 굳이 칼을 휘두르며 증명할 필요는 없소...");
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
