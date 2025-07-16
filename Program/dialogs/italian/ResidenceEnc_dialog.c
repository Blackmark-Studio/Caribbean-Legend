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
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Gesù! Un uomo così disprezzabile nelle mie stanze! Vattene da qui o chiamerò le guardie!","Questo non può succedere... Chi ha lasciato entrare questo ratto nella mia casa? Vattene di qui, bastardo! Non hai niente da fare qui! Sparisci!","Sono arrivati tempi strani. I ratti si stanno infiltrando nella mia camera da letto! Vattene!");
				link.l1 = RandPhraseSimple("Piano là...","Guarda la tua bocca...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Cosa stai facendo nella mia camera da letto? Vattene da qui!","Che vergogna! Ti chiedo di lasciare immediatamente questo luogo!","Mi scusi, signore, ma non è stato invitato qui. Per favore, lasci la mia stanza!");
				link.l1 = RandPhraseSimple("Scusami... Me ne sto andando.","Scusa, porta sbagliata. Devo andare.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, cos'era quello?! Sono un tale sciocco! Camminando in giro, non ho visto nulla... Guardie!!!";
			link.l1 = "Taci!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Allontanati da qui, topo!","Allontanati immediatamente dalla tenuta del governatore, ratto!","Non mi importa cosa stai facendo a casa del governatore di "+XI_ConvertString("Colony"+npchar.city+"Gen")+"Ma il mio consiglio è sparisci, ora!");
				link.l1 = RandPhraseSimple("Tienila semplice, amico...","Attento alle tue parole!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Saluti! Sono un servo del governatore. Il mio nome è "+GetFullName(NPChar)+".","Vigilo su questo luogo, "+GetAddress_Form(NPChar)+".","Sai, "+GetAddress_Form(NPChar)+", il nostro governatore è un bravo uomo e ci paga bene...");
				link.l1 = RandPhraseSimple("Bene.","Mm, molto bene...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Allora hai deciso di derubare il governatore?! Guardie, prendete il ladro!!";
			link.l1 = "Chiudi la bocca!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("È meglio che te ne vada da qui, "+GetSexPhrase("amico","ragazza")+"...","Vattene!","Ho perso la porta, "+GetSexPhrase("amico","ragazza")+"? ? Questa tenuta appartiene al governatore di "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Me ne andrò quando voglio!","Non è affar tuo...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Oggi, mi è stato ordinato di servire qui. Bel posto...","Proteggo la proprietà di "+GetAddress_Form(NPChar)+".","È mio dovere proteggere la tenuta del governatore.");
				link.l1 = RandPhraseSimple("Buona fortuna, allora...","Mmm, capisco...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, sì. Finalmente! Sono pronto a venire con te, capitano.";
				link.l1 = "Così, senza più? Signora, sei sicura che è quello che vuoi?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Cosa?! Sei ubriaco, signore? Che scherzo idiota! Ti prego, vattene, ti supplico!"+sld.name+"! Guardie! Aiuto!";
				link.l1 = "Merda, è ora di andare.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Ebbene, naturalmente! Ah, il Signor Aruba ed io abbiamo avuto una relazione epistolare per molto tempo!";
			link.l1 = "Dato che è così, per favore, sali a bordo!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "No, signora, non va bene. Il mio onore non permette di mettere a rischio una donna, e chiaramente sei stata ingannata!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "In tal caso, mio caro capitano, prendi il tuo senso rurale dell'onore e infilalo nel tuo culo! Aspetterò un altro messaggero, qualcuno non così ottuso come te!";
			link.l1 = "Incantevole!";
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
