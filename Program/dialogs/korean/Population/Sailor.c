//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "좋은 하루입니다, "+GetAddress_Form(NPChar)+". 네가 네 배의 선장이라는 것쯤은 알고 있지. 거래 하나 제안하지.";
					link.l1 = "듣고 있소, "+GetAddress_FormToNPC(NPChar)+". 무슨 거래지?";
					link.l1.go = "crew";
					link.l2 = "미안하오, "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 급하오.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("이봐, 선장! 평범한 선원한테 뭘 원해?","좋은 하루입니다, 나리. 무엇을 도와드릴까요?","좋은 하루입니다, 나리. 필요한 것이 있으십니까?");
				link.l1 = "만나서 반갑다, 친구! 내 이름은 "+GetFullName(pchar)+". 잠깐 이야기 좀 할 수 있을까?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("너한테 물어볼 게 있어.","이 식민지에 대해 정보를 좀 알고 싶소.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "그냥 인사하고 싶었어. 또 보자!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "또 오셨습니까, 나리? 또 무슨 일이십니까?";
				link.l1 = "잠깐 이야기할 시간 있어?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("너한테 물어볼 게 있어.","이 식민지에 대해 정보를 좀 알고 싶소.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "아니야, 이봐, 별일 아니야. 행운을 빌어!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" 나리, 언제든지 도와드릴 준비가 되어 있습니다! 무엇을 알고 싶으신가요?","당신과 이야기하게 되어 기쁩니다, 선장님!","음... 아직 더 이야기할 시간이 남아 있겠군...","유감이지만 이제 가야겠소. 안녕히 계시오!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나한테 해 줄 만한 흥미로운 얘기라도 있어?","나한테 흥미로운 얘기라도 있어?","나한테 해줄 만한 재미있는 얘기라도 있나?","물론이지. 행운을 빌어!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Me and my messmates were put shoreside from our last ship due to various sickness and injuries. But we are all healthy now and want to get back to work as sailors again. Do you want to hire us?"; break;
				case 1: sTemp = "Me and a few of my boys were paid off from a merchantman due to the end of its contract. We have been without a single piece of eight for a long time already so we want to get back to work again. Do you need some skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my mates just got back from a voyage two weeks ago. The ship's master has dismissed us and we've been having some great fun. But our pockets are empty now so it's time to set sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "좋소, 이제 그대의 제안을 논의할 준비가 되었소. 그대들은 몇 명이나 되며, 어떤 기술을 가지고 있소?";
			link.l1.go = "crew_1";
			link.l2 = "미안하네, 선원. 하지만 이미 사람이 충분하네. 다른 선장을 찾아보게.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "있다 "+sti(npchar.quest.crew.qty)+" 우리끼리만 함께 고용될 거야. 기본적인 선원 업무는 모두 할 수 있어."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "내가 찾고 있는 놈들인 것 같군. 선불은 어떻게 할 건가?";
				link.l1.go = "crew_2";
				link.l2 = "미안하네, 뱃사람. 하지만 지금은 다른 기술이 필요하네. 다른 선장을 찾아보는 게 좋겠군.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "미안하다, 선원. 내 배에는 자리가 부족해. 다른 선장을 찾아보는 게 좋겠어.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" 각각에 대해. 그리고 평범한 선원의 월급도 있습니다. 너무 과한 건 요구하지 않겠습니다, 선장님.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "고용됐어! 이 동전들 가져가. 이제 내 배로 가, 이름은 '"+pchar.ship.name+"', 바로 항구에서다. 보선장이 모두에게 선실 내 해먹을 배정하고 식사조도 정해줄 거다.'";
				link.l1.go = "crew_3";
			}
			link.l2 = "유감이지만, 너희 모두를 위해 돈을 낼 형편이 못 된다. 다른 선장을 찾아보는 게 좋겠어.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "알겠어요, 선장님! 녀석들 모아서 바로 출발할게요.";
			link.l1 = "서둘러라, 곧바로 출항할 거다.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 칼 집어넣으시오, 선장. 우리 중 누구도 문제를 원하진 않잖소, 그렇지?","이봐, 칼 집어넣으시오, 선장. 우리 중 누구도 문제를 원하지 않잖아, 그렇지?");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","말씀대로 하겠습니다.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
