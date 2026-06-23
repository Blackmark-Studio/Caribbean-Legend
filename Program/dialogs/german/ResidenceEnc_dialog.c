void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && int(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jesus! Solch ein verabscheuungswürdiger Mann in meinen Gemächern! Geh weg von hier oder ich rufe die Wachen!","Das kann nicht sein... Wer hat diese Ratte in mein Haus gelassen? Verschwinde, du Halunke! Du hast hier nichts zu tun! Geh weg!","So seltsame Zeiten sind gekommen. Ratten kommen in mein Schlafzimmer! Geh weg!");
				link.l1 = RandPhraseSimple("Ruhig, Kumpel...","Halt dein Maul...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Was machst du in meinem Schlafzimmer? Verschwinde von hier!","Was für eine Schande! Ich bitte Sie, diesen Ort sofort zu verlassen!","Entschuldigung, Herr, aber Sie wurden hier nicht eingeladen. Bitte, verlassen Sie mein Zimmer!");
				link.l1 = RandPhraseSimple("Entschuldigen Sie... Ich gehe jetzt.","Entschuldigung, falsche Tür. Ich muss gehen.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, was war das?! Ich bin so ein Narr! Ich laufe herum, sehe nichts... Wachen!!!";
			link.l1 = "Halt den Mund!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Verschwinde von hier, Ratte!","Verzieh dich sofort vom Anwesen des Gouverneurs, Ratte!","Es ist mir egal, was du im Haus des Gouverneurs machst "+XI_ConvertString("Colony"+npchar.city+"Gen")+"Aber mein Rat ist, verschwinde jetzt!");
				link.l1 = RandPhraseSimple("Mach es einfach, Kumpel...","Achte auf deine Worte!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Grüße! Ich bin ein Diener des Gouverneurs. Mein Name ist "+GetFullName(NPChar)+".","Ich wache über diesen Ort, "+GetAddress_Form(NPChar)+".","Weißt du, "+GetAddress_Form(NPChar)+", unser Gouverneur ist ein guter Mann und zahlt uns gut...");
				link.l1 = RandPhraseSimple("Schoen.","Hm, sehr gut...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Also hast du beschlossen, den Gouverneur auszurauben?! Wachen, holt den Dieb!!";
			link.l1 = "Halt den Mund!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Du solltest besser von hier verschwinden, "+GetSexPhrase("Kumpel","Mädchen")+"...","Geh weg!","Verpasst die Tür, "+GetSexPhrase("Kumpel","Mädchen")+"? ? Dieses Anwesen gehört dem Gouverneur von "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Ich gehe, wann ich will!","Das geht dich nichts an...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Heute wurde mir befohlen, hier zu dienen. Schöner Ort...","Ich schütze das Anwesen von "+GetAddress_Form(NPChar)+".","Mein Befehl ist es, das Anwesen des Gouverneurs zu schützen.");
				link.l1 = RandPhraseSimple("Viel Glück dann...","Hmm, ich sehe...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = int(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (int(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ach, ja. Endlich! Ich bin bereit, mit dir zu gehen, Kapitän.";
				link.l1 = "So einfach? Senora, sind Sie sicher, dass Sie das wollen?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Was?! Bist du betrunken, Senor? Was für ein idiotischer Scherz! Bitte geh weg, ich flehe dich an! "+sld.name+"! Wachen! Hilfe!";
				link.l1 = "Scheiße, Zeit zu gehen.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Nun, natürlich! Ah, Senor Aruba und ich führen schon lange eine briefliche Beziehung!";
			link.l1 = "Da das der Fall ist, bitte kommen Sie an Bord!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Nein, senora, das wird nicht funktionieren. Meine Ehre lässt es nicht zu, dass eine Frau in Gefahr gebracht wird, und Sie sind eindeutig in die Irre geführt worden!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "In diesem Fall, mein lieber Kapitän, nehmen Sie Ihren ländlichen Ehrenkodex und stecken Sie ihn sich in den Arsch! Ich warte auf einen anderen Boten, jemanden der nicht so engstirnig ist wie Sie!";
			link.l1 = "Bezaubernd!";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
