void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un maledetto errore. Avvisa subito gli sviluppatori, per mille balene.";
			link.l1 = "D'accordo";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Salute, capitano. Desiderate qualcosa da me?";
			link.l1 = "Sì. Proprio così, "+GetAddress_FormToNPC(NPChar)+". C'è un passeggero sulla tua nave che m'interessa parecchio. Si chiama "+pchar.GenQuest.Marginpassenger.q1Name+". Voglio che il tuo passeggero diventi il mio. Se sei d’accordo, allora ognuno per la sua rotta e non ci vedremo mai più.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Ah sì? E se ti dicessi di no?";
			link.l1 = "Allora sarò costretto a farti cambiare idea con qualche bordata dei miei cannoni, che in questo momento sono già puntati verso di te. Non tentare la sorte, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (6-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (6-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Non ho altra scelta, allora. La sorte della mia ciurma vale più per me che la vita d’un solo uomo. Ma non te la caverai così facilmente! Non lo dimenticherò!";
				link.l1 = "Calmati, non ti prendere un colpo... Portami il mio nuovo passeggero!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Faresti meglio a lasciare la mia nave, signore, finché te lo permetto ancora. Non provare a spaventarmi. E guai a te se osi attaccare la mia nave, verrai ricacciato a forza all’istante. Sparisci, finché sono ancora di buon umore!";
				link.l1 = "T'ho avvertito. Sto arrivando. Ci vediamo presto, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Abbiamo già parlato, ricordi? Fuori dalla mia nave, dannato scroccone!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Argh, maledetto! Brucia all’inferno per le tue malefatte!";
				link.l1 = "Ti ho dato la possibilità di consegnarmi il passeggero senza spargimento di sangue... e tu hai rifiutato la mia offerta. Ora la colpa ricade solo su di te!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Argh, maledetto! Perché hai assaltato una nave pacifica? Non abbiamo né oro né merci di valore!";
				link.l1 = "Ma hai una persona preziosa a bordo..."+pchar.GenQuest.Marginpassenger.q1Name+". Voglio il tuo passeggero.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Tu... sei il lurido pirata!";
			link.l1 = "Meno chiacchiere, amico mio...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "E per questo hai fatto una strage sulla mia nave? Un mucchio di uomini sono crepati! Maledetto pirata!";
			link.l1 = "Meno chiacchiere, amico mio...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Cosa vuoi, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sei tu "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Sì, sono io. Vuoi presentare una richiesta? Allora sappi che...";
			link.l1 = "Aspetta un attimo, signore. Ho una richiesta un po’ diversa... Conosci forse qualcuno che si chiama "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Sì, la conosco... Certo che sì! Che succede?";
					link.l1 = "Si era cacciata in una faccenda assai spiacevole: i pirati avevano preso la sua nave. Per fortuna ho avuto l’occasione d’abbordare quei cani e salvare la poveretta. Mi ha parlato di voi, e così eccomi qui.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Sì, conosco quest’uomo assai bene. Che succede?";
					link.l1 = "S’era cacciato in una faccenda davvero sgradevole: la sua nave fu presa d’assalto dai filibustieri. Per mia fortuna, mi capitò l’occasione d’abbordare il loro vascello e liberare questo prigioniero. Mi ha fatto il vostro nome, ed eccomi qua.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Oh Dio! Dov’è finita adesso? Perché non l’hai portata qui?";
			link.l1 = "Lei è al sicuro. Quanto alla tua domanda... non è così semplice. Avrei potuto riportarla a casa io stesso, ma posso offrirti questa occasione. Ovviamente, per una piccola somma.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Non ci capisco un'acca...";
			link.l1 = "Perché non lo fai tu? Mi paghi in oro, io ti consegno la ragazza e tu potrai sfruttare la faccenda a tuo vantaggio... Vuoi prenderla in moglie, sbaglio? E con quelle monete rimetterò in sesto la mia nave, che s’è beccata un brutto colpo in quella scaramuccia coi pirati.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Oh Dio! Dov'è finito adesso? Perché non l’hai portato qui?";
			link.l1 = "È al sicuro. Quanto alla tua domanda... non è così semplice. Avrei potuto riportarlo a casa io stesso, ma potrei lasciare questa opportunità a te, visto che hai certi interessi nella sua famiglia. Naturalmente, per una modica ricompensa.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm...   Non ci capisco un'acca...";
			link.l1 = "Perché non lo fai tu? Mi paghi in oro, io ti restituisco il tuo compare e potrai sfruttare questa faccenda a tuo vantaggio. Ho delle informazioni, sai... Con quelle monete rimetterò a posto la mia nave, è stata malconcia in quello scontro coi filibustieri.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Ebbene, ebbene... e quanto vuoi, di grazia?";
			link.l1 = "Tieni a mente che voglio dobloni, non pesos.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Va bene, va bene... Allora, quanti dobloni vuoi?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Molto spiritoso. Va bene, fingiamo pure che la tua battuta fosse davvero divertente. Addio!";
			link.l1 = "Uhm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Va bene, accetto. Ho la somma richiesta. Dove si trova "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Sarà già al molo ormai. Allora puoi andare a prendere il passeggero.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Mi dispiace, ma non ho così tanti dobloni. Andrebbero bene dei pesos?";
				link.l1 = "Voglio dobloni, ma suppongo che il capitano della nave accetterà anche pesos... Dammi quelli.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "No, ho bisogno solo di dobloni.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Purtroppo, non ho una tale somma. Quindi non posso accettare la tua proposta, per quanto lo desideri.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Sire, vi rendete conto di quel che state blaterando? Sapete che questa somma è da folli? Fuori di qui, al diavolo!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Ehm... Signore, dovete andare dal medico, e subito. Pare proprio che abbiate una febbre da cavallo o... insomma, vi serve un dottore. E io ho le mani troppo piene. Addio!";
			link.l1 = "Uhm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Eccola qui, tutta la somma in pesos proprio come volevi... Dove sta "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Sarà già al molo ormai. Quindi puoi andare a prendere il passeggero..";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Non posso quindi accettare la tua proposta, per quanto lo desideri. Addio!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Che diavolo... Che sta succedendo qui?!";
			link.l1 = "È molto semplice, "+NPCharSexPhrase(NPChar,"compare","ragazza")+". Ora sei il mio caro passeggero. Un passeggero sorvegliato. Non provare a opporre resistenza, o finirai nella stiva con le merci.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Vuoi dire che sono il tuo prigioniero?";
			link.l1 = "Oh, no. Certamente no. Non un prigioniero, ma un caro ospite. Un ospite di gran valore...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Tu... pagherai caro le tue azioni!";
			link.l1 = "Hai sbagliato di nuovo, "+NPCharSexPhrase(NPChar,", compare",", caro")+". Non pagherò, ma sarò pagato. Basta chiacchiere, vai in cabina tua!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
