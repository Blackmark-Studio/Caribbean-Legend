// Якоб Джекман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Hai qualcosa da dirmi? No? Allora vattene da qui!","Eh, "+pchar.name+"! Hai affari con me? No? Allora non disturbarmi.")+"","Credo di essermi spiegato abbastanza chiaramente, smetti di infastidirmi.","Sebbene mi sia spiegato chiaramente, continui a infastidirmi!","Bene, mi sto stancando di questa maleducazione, vai via, mostro.","ripeti",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Me ne sto già andando.","Certo, Jackman...","Mi dispiace, Jackman...","Ahi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, sarebbe meglio che te ne andassi da questo posto...","Sembra che tu sia impazzito, ragazzo. Volevi stendere un po' le mani? Senza offesa, ma qui non hai nulla da fare. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Dove posso trovare Jimmy Higgins?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Di nuovo io, Jackman. Dicono che stai cercando delle persone scomparse...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Si tratta del tuo prigioniero.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Ciao, Jackman. Riguardo alla tua missione...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Si tratta del tuo prigioniero.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", Sono felice di vederti! Cosa vuoi?","Cosa vuoi?","Di nuovo tu? Non disturbare la gente se non hai nulla da fare!","Tu sei "+GetSexPhrase("un bravo corsaro"," una brava ragazza")+", quindi puoi vivere per ora. Ma non voglio più parlarti.","ripeti",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Solo di passaggio.","Niente...","Bene, Jackman, mi dispiace...","Maledizione! Beh, come dici tu...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, faresti meglio a lasciare questo posto...");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Si tratta del tuo prigioniero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Davvero! Qualcuno ha bisogno di questo fannullone! È da diversi giorni che beve rum da solo nella sua capanna. Non ti consiglierei di andarlo a trovare. Non è un gran che di persona nemmeno quando è sobrio...";
			link.l1 = "Va bene, non sono neanche un santo. Dove si trova la sua baracca?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "È proprio di fronte alla taverna. Ha scelto un buon posto per bere velocemente.";
			link.l1 = "Grazie!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "E chi te l'ha detto? Quel ubriacone di Higgins? Hai scoperto qualcosa su Gladys Chandler o Henry il Boia?";
			link.l1 = "Niente di speciale, veramente, ma voglio sapere qualcosa di specifico su quel Boia.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Non c'è nulla da sapere. Pochi lo ricordano ora, ma vent'anni fa Henry era molto popolare tra le prostitute da Bridgetown a Tortuga. Puoi scommetterci! Un nostromo del 'Nettuno', sotto il comando del capitano Butcher in persona! Deve essere davvero vecchio ora se è ancora vivo, ovviamente.\nLe probabilità sono basse, ma sai, nulla è impossibile. Pagherò ventimila pesos per qualsiasi informazione su di lui, il doppio se me lo porti qui vivo.";
			link.l1 = "Quanto pagherai per Gladys e sua figlia?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Oh, lei non è sua figlia. Se mi porti quella ragazza viva, ti pagherò una manciata di dobloni. Non mi interessa Gladys. Domande?";
			link.l1 = "Vorrei sapere il motivo di questo trambusto, ma non chiederò. Sembra che possa accorciare la mia biografia.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Forse... Quei segreti non ti riguardano. Meno sai, più a lungo vivi. Non cercare di farmi di nuovo tali domande, perché ho iniziato a sospettare che ci sia qualcosa che non va in te. Sparisci prima che cambi idea.";
			link.l1 = "Arrivederci, barone!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ah! Ci incontriamo di nuovo, capitano "+GetFullName(pchar)+". Ammetto, sei un avversario degno, nonostante i tuoi tentativi di dipingerti come un sempliciotto a Maroon-Town. Ho scoperto qualcosa su di te, le tue trame con la Compagnia Olandese delle Indie Occidentali sono state scoperte... Ora capisco che tipo sei.";
			link.l1 = "Conosco anche il tuo tipo, Jacob. Quindi non creiamo illusioni.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "E come mi hai ingannato con 'Marlin'! Immagino che il mio povero fratello sia morto...";
			link.l1 = "Capisco che vuoi vendicare lui? Ma ho un lungo conto anche per te. Per Nathaniel accerchiato, sua moglie, la sua fregata, lo squalo diffamato, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? Non l'ho ucciso.";
			link.l1 = "Anche se è vero, il resto della mia lista è sufficiente. Sono stanco del tuo nome. Basta parole, Jackman! Le nostre lame parleranno!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Che sciocco veemente.. Dannazione a te! Ora è meglio che ti aggrappi! Jacob Jackman non è mai stato sconfitto! Carpacho, sei arrivato proprio in tempo! Vieni qui!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ah-ah. Pensi che ho solo un prigioniero qui? Nominalo.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". È qui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Era. L'ho venduto a quel proprietario di piantagioni di Barbados - colonnello Bishop, quando era qui una settimana fa.";
				link.l1 = "Maledizione...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Stavo pensando di venderlo a quel proprietario di piantagioni di Barbados, sarà qui tra una settimana o due... Hai un riscatto?";
				link.l1 = "Guarda, c'è un piccolo problema... In realtà, non ho molti soldi. Ma sono pronto a lavorare.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "È bene che tu non lo abbia venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Sei stato troppo lento... E perché ti importa di lui? Ho trattato solo con i suoi parenti.";
			link.l1 = "Hanno chiesto a me di venire qui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Beh, sei in ritardo. Non posso fare nulla.";
			link.l1 = "Ascolta, per quanto l'hai venduto se non è un segreto?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, non lo è. Ma non te lo dirò... Riderai se lo faccio. Ah-ah-ah-ah! Addio.";
			link.l1 = "Arrivederci...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Ebbene, ebbene.. Ho degli affari... Non so nemmeno da dove cominciare. Devo affondare un pirata che ha oltrepassato il limite.";
				link.l1 = "Non potrebbe semplicemente essere ucciso nella giungla?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Beh, "+pchar.name+", sai, non funziona così. Torna con i soldi e avrai il tuo debolucco, ah-ah.";
				link.l1 = "Bene. Ci vediamo.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Non è così che funziona il business, sai... Non ho bisogno della sua morte, devo insegnare a certa gente a stare alla larga dal mio bottino. Ma se va a nutrire gli squali, non mi dispiacerà.";
			link.l1 = "Perché non mandi i tuoi uomini a cercarlo?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Mh... Beh, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" ha convinto alcuni pirati che la loro parte di bottino è conservata nel nostro nascondiglio non lontano da "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Le loro due navi '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' ha levato l'ancora poco tempo fa e ha navigato verso "+sLoc+". Ora vedi perché non posso fidarmi dei miei uomini per fare quel lavoro?";
			link.l1 = "Lo faccio. Quanto tempo ho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "Da 12 a 15 giorni, non di più, suppongo. Non voglio che arrivino al nascondiglio, o sarà inutile affondarli con un carico prezioso. In quel caso, sarebbe meglio se lo portassero qui...";
			link.l1 = "Bene, sono dentro. Proverò a prenderli.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Non preoccuparti. I miei uomini lo consegneranno alla tua nave. E perché ti importa di lui?";
			link.l1 = "Non lo faccio. I suoi parenti mi hanno chiesto di consegnarlo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, va bene. Mi dispiaceva quasi di aver dato un prezzo così basso per il tuo uomo. Ha-ha-ha-ha. Addio.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Allora, , "+GetFullName(pchar)+", hai affondato il mio compagno? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. Non sono riuscito a prenderli. E non li ho incontrati al ritorno.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "L'ho fatto. Li ho mandati a nutrire gli squali.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Maledizione! Li hai incontrati o no, ora non importa! E qual sarà il tuo prossimo suggerimento?";
			link.l1 = "Forse hai un lavoro più facile per me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ascolta, Jackman, abbassa il prezzo per il prigioniero...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Addio allora...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Abbassare il prezzo? Ho appena perso la mia roba a causa della tua incompetenza! E adesso potrei alzare il prezzo! Puoi prenderlo per 200.000 pesos se vuoi, o puoi sparire di qui.";
			link.l1 = "È troppo costoso... Addio...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Maledizione, prendi le tue monete.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Bene, puoi prendere questo debole...";
			link.l1 = "Addio.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Oho! Ben fatto! Prendi il tuo debole e buona fortuna.";
			link.l1 = "Grazie. Addio.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Hai portato i soldi, Charles? Non scherzavo riguardo alla vendita dell'uomo alla piantagione.";			
			link.l1 = "Ascolta, "+NPChar.name+", c'è un problema... Non ho così tanti soldi. Ma sono pronto a lavorare.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È bene che non lo hai venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rapina!!! Questo è inaccettabile! Preparati, "+GetSexPhrase("ragazzo","ragazza")+"...","Ehi, che diavolo stai facendo lì?! Pensavi di potermi derubare? Sei finito...","Aspetta, che diavolo? Togli le tue mani! Si scopre che sei un ladro! Fine della linea, bastardo...");
			link.l1 = LinkRandPhrase("Merda!","Carramba!!","Maledizione!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Vattene da qui!","Vattene dalla mia casa!");
			link.l1 = "Ops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non infastidirmi con le tue chiacchiere da quattro soldi. La prossima volta non ti piacerà il risultato...";
        			link.l1 = "L'ho capito.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "È finita, niente chiacchiere.""Non voglio più parlare con te, quindi sarebbe meglio che non mi disturbassi.";
			link.l1 = RandPhraseSimple("Come desideri...","Bene allora...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Spero che mostrerai più rispetto e smetterai di essere maleducato? Altrimenti dovrei ucciderti. Sarebbe molto sgradevole.";
        			link.l1 = "Puoi starne certo, Jackman, lo farò.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Risolvere il problema? Capisci cosa hai fatto? Comunque, portami un milione di pesos e persuaderò i ragazzi a dimenticare le tue 'imprese'. Se l'idea non ti piace, allora puoi andare all'inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Bene, sono pronto a pagare.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Capito. Me ne vado.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bene! Considerati di nuovo pulito. Ma spero che non farai più cose così disgustose.";
			link.l1 = "Non lo farò. Troppo costoso per me. Addio...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}
