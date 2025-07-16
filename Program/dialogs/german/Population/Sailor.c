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
					dialog.text = "Guten Tag, "+GetAddress_Form(NPChar)+". Ich weiß, dass Sie Kapitän Ihres eigenen Schiffes sind. Ich habe ein Angebot für Sie.";
					link.l1 = "Ich höre zu, "+GetAddress_FormToNPC(NPChar)+". Was für ein Deal?";
					link.l1.go = "crew";
					link.l2 = "Entschuldigung, "+GetAddress_FormToNPC(NPChar)+", aber ich bin in Eile.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("He, Kapitän! Was wollen Sie von einem gewöhnlichen Seemann?","Guten Tag, Herr. Wie kann ich Ihnen helfen?","Guten Tag, mein Herr. Wünschen Sie etwas?");
				link.l1 = "Freut mich, dich zu treffen, Kumpel! Mein Name ist "+GetFullName(pchar)+". Hast du einen Moment zum Reden?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche einige Informationen über diese Kolonie.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Einfach nur Hallo sagen. Bis dann!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Wieder Sie, Herr? Was wollen Sie noch?";
				link.l1 = "Hast du eine Minute zum Reden?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche einige Informationen über diese Kolonie.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Nein, Kumpel, es ist nichts. Viel Glück!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" zu Ihren Diensten, guter Herr! Was möchten Sie wissen?","Freut mich, mit Ihnen zu sprechen, Kapitän!","Nun... Ich denke, ich habe noch etwas mehr Zeit zum Reden...","Leider muss ich jetzt gehen. Lebewohl!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hast du etwas Interessantes zu erzählen?","Hast du etwas Interessantes zu erzählen?","Haben Sie etwas Interessantes zu erzählen?","Sicher. Viel Glück!",npchar,Dialog.CurrentNode);
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
			link.l1 = "Nun, ich bin bereit, Ihren Vorschlag zu besprechen. Wie viele von euch gibt es und was könnt ihr gut?";
			link.l1.go = "crew_1";
			link.l2 = "Es tut mir leid, Seemann, aber ich habe schon genug Männer. Du solltest dir einen anderen Kapitän suchen.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "Es gibt "+sti(npchar.quest.crew.qty)+" von uns und wir werden nur zusammen angestellt. Wir können alle grundlegenden Seemannsaufgaben erledigen."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Hört sich an wie die Männer, die ich suche. Was ist mit eurer Anzahlung?";
				link.l1.go = "crew_2";
				link.l2 = "Es tut mir leid, Matrose, aber im Moment brauche ich andere Fähigkeiten. Du solltest dir einen anderen Kapitän suchen.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Entschuldigung, Matrose, aber ich habe nicht genug Platz auf meinem Schiff. Du solltest dir einen anderen Kapitän suchen.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" für jeden. Und dann der übliche Seemannslohn pro Monat. Wir werden nichts Übertriebenes verlangen, Kapitän.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Du bist eingestellt! Nimm deine Münzen. Jetzt geh zu meinem Schiff, es heißt '"+pchar.ship.name+"', direkt im Hafen. Der Bootsmann wird euch allen Hängematten in der Mannschaftsquartieren zuweisen und eure Mahlzeiten besorgen.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Leider kann ich es mir nicht leisten, euch alle zu bezahlen. Ihr solltet euch einen anderen Kapitän suchen.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Aye aye, Kapitän! Ich werde die Jungs zusammenrufen und wir werden sofort aufbrechen.";
			link.l1 = "Sei schnell, wir segeln auf einen Augenblicks hinweis.";
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
			dialog.text = NPCharSexPhrase(NPChar,"He, steck dein Schwert weg, Käpt'n. Keiner von uns braucht Probleme, oder?","He, steck dein Schwert weg, Kapitän. Keiner von uns braucht Probleme, oder?");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Wie du sagst.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
