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
					dialog.text = "Buon giorno, "+GetAddress_Form(NPChar)+". Sono a conoscenza che sei il capitano della tua nave. Ho un affare per te.";
					link.l1 = "Sto ascoltando, "+GetAddress_FormToNPC(NPChar)+". Che tipo di affare?";
					link.l1.go = "crew";
					link.l2 = "Scusa, "+GetAddress_FormToNPC(NPChar)+", ma sono di fretta.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Ehi, capitano! Cosa vuoi da un comune marinaio?","Buongiorno, signore. Come posso aiutarla?","Buongiorno, signore. Desidera qualcosa?");
				link.l1 = "Contento di conoscerti, compagno! Il mio nome è "+GetFullName(pchar)+". Hai un minuto per parlare?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di alcune informazioni su questa colonia.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Solo volevo dire ciao. Ci vediamo!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Di nuovo lei, signore? Cosa vuole ancora?";
				link.l1 = "Hai un minuto per parlare?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve qualche informazione su questa colonia.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "No, amico, non è niente. Buona fortuna!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" al vostro servizio, buon signore! Cosa volete sapere?","Contento di parlare con te, capitano!","Bene... Suppongo di avere ancora un po' di tempo per parlare...","Sfortunatamente, devo andare ora. Addio!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hai qualcosa di interessante da dirmi?","Hai qualcosa di interessante da dirmi?","Hai qualcosa di interessante da dirmi?","Certo. Buona fortuna!",npchar,Dialog.CurrentNode);
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
			link.l1 = "Ebbene, sono pronto a discutere la tua proposta. Quanti siete e in cosa siete bravi?";
			link.l1.go = "crew_1";
			link.l2 = "Mi dispiace, marinaio, ma ho già abbastanza uomini. Dovresti trovare un altro capitano.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "Ci sono "+sti(npchar.quest.crew.qty)+" di noi e ci assumeranno solo insieme. Possiamo eseguire tutti i compiti di base di un marinaio."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Sembra che siano gli uomini che sto cercando. E il tuo anticipo?";
				link.l1.go = "crew_2";
				link.l2 = "Mi dispiace, marinaio, ma al momento ho bisogno di altre competenze. Dovresti cercarti un altro capitano.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Mi dispiace, marinaio, ma non ho abbastanza spazio sulla mia nave. Dovresti cercarti un altro capitano.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" per ognuno. E poi il salario mensile del marinaio comune. Non chiederemo nulla di eccessivo, capitano.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Sei assunto! Prendi le tue monete. Ora vai alla mia nave, si chiama '"+pchar.ship.name+"', proprio nel porto. Il nostromo vi assegnerà tutte le amache nei quartieri dell'equipaggio e si occuperà dei vostri pasti.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Sfortunatamente, non posso permettermi di pagare per tutti voi. Dovreste cercarvi un altro capitano.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Sì sì, capitano! Radunerò i ragazzi e partiremo immediatamente.";
			link.l1 = "Fatti in fretta, salpiamo al minimo preavviso.";
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
			dialog.text = NPCharSexPhrase(NPChar,"Ehi, infila la tua spada, cap. Nessuno di noi ha bisogno di problemi, vero?","Ehi, infila la tua spada, cap. Nessuno di noi ha bisogno di problemi, giusto?");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Come dici tu.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
