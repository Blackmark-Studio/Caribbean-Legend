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
					dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。お前が自分の船の船長だってことは知ってるぜ。取引の話があるんだ。";
					link.l1 = "聞いているぞ "+GetAddress_FormToNPC(NPChar)+"「どんな取引だ？」";
					link.l1.go = "crew";
					link.l2 = "「すまない」 "+GetAddress_FormToNPC(NPChar)+"、しかし急いでいるんだ。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("おい、船長！俺みたいな下っ端水夫に何の用だ？","ごきげんよう、旦那。ご用件は何でしょうか？","ごきげんよう、旦那。何かご用でしょうか？");
				link.l1 = "会えて嬉しいぜ、相棒！俺の名前は "+GetFullName(pchar)+"。ちょっと話せるか？";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","この植民地について少し情報が必要なんだ。");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "ちょっと挨拶したかっただけだ。またな！";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "またお前か、旦那？今度は何の用だ？";
				link.l1 = "少し話せるか？";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","この植民地について少し情報が必要なんだ。");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "いや、相棒、なんでもねえよ。幸運を祈るぜ！";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" お任せください、旦那！何をお知りになりたいですか？","お話できて嬉しいぜ、船長！","「そうだな……まだ少し話す時間はありそうだ……」","残念だが、もう行かなくちゃならねえ。じゃあな！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("俺に面白い話でもあるのか？","俺に何か面白い話でもあるか？","俺に面白い話でもあるのか？","もちろんだ。幸運を祈るぜ！",npchar,Dialog.CurrentNode);
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
			link.l1 = "さて、提案について話し合う準備はできているぜ。\nお前たちは何人いるんだ？それに、どんな腕前を持ってるんだ？";
			link.l1.go = "crew_1";
			link.l2 = "悪いな、水夫よ、だがもう十分な人数がいるんだ。別の船長を探した方がいいぜ。";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "「ある」 "+sti(npchar.quest.crew.qty)+" 俺たちは一緒にしか雇われねえぜ。水夫の基本的な仕事なら全部できる。"+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "俺が探している連中みたいだな。前金の話はどうする？";
				link.l1.go = "crew_2";
				link.l2 = "悪いな、水夫。でも今は他の技能が必要なんだ。別の船長を探した方がいいぜ。";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "悪いな、水夫。でも俺の船にはもう空きがねえんだ。他の船長を探した方がいいぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" 一人につき、そして普通の水夫の月給だ。それ以上は要求しねえよ、船長。";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "雇ってやる！これが報酬だ。さあ、俺の船へ行け、名は『"+pchar.ship.name+"「そうだ、港のすぐそばだ。甲板長が全員に乗組員区画のハンモックを割り当てて、食事の班も決めてくれるぜ。」";
				link.l1.go = "crew_3";
			}
			link.l2 = "残念だが、全員分の支払いはできねえ。自分で別の船長を探すんだな。";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "了解だぜ、船長！すぐに野郎どもを集めて出発するぜ。";
			link.l1 = "さっさとやれ、すぐにでも出航するぞ。";
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
			dialog.text = NPCharSexPhrase(NPChar,"おい、剣を納めてくれよ、船長。俺たち誰も揉め事なんて望んじゃいねえだろ？","おい、剣を収めてくれよ、船長。俺たち誰も揉め事なんて望んじゃいねえだろ？");
			link.l1 = LinkRandPhrase("よし。","ご希望の通りに。","おっしゃる通りです。");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
