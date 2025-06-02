//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("Ahhh, dannazione! So chi sei! Solo un completo idiota salirebbe sulla tua nave come passeggero! Addio!","Oh, so chi sei! Non metterò mai piede sulla tua nave. Non sono un idiota...");
				link.l1 = RandPhraseSimple("Ehi, che vigliacco!","La gente è diventata così codarda in questi giorni!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Io sono "+GetFullName(NPChar)+". Ho sentito dire che stai prendendo passeggeri?";
				link.l1 = "Forse. Dipende dal mio profitto.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "Ho bisogno di essere portato alla taverna di "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", quello su "+XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination)+"Dat")+", per "+FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time))+", e per questo ti pagherò "+FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money))+". Sei d'accordo?";
			link.l1 = "Sì, lo faccio.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Non credo sia una proposta interessante.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернём его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Grazie. Hai adempiuto ai tuoi obblighi. Sono alla mia destinazione, ecco la tua ricompensa. Ecco a te.";
			Link.l1 = "Grazie.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("One person by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted, since "+ GetSexPhrase("he","she") +" had easily delivered him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Passenger named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He delivered","She delivered") +" him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " absolutelly safely.", 
				"I heard that you are a captain who keeps his word given to passengers. Huckster named " + GetFullName(npchar) + " is giving high praises to you."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterComplexReputation(pchar, "nobility",1);
			ChangeCharacterComplexReputation(pchar, "fame",1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear()+"Capitano, il tempo è scaduto. Quando, dannazione, arriverò finalmente a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?",RandSwear()+"Capitano, quanto tempo ancora vagheremo chissà dove?! Quando arriveremo a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?",RandSwear()+"Ascolta, capitano, ho bisogno di arrivare a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", e voglio avere una risposta chiara e semplice su quando accadrà!"),RandPhraseSimple("Capitano, ancora una volta devo sollevare una questione riguardo ai vostri obblighi. Quando arriveremo a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?","Capitano, la seconda volta che devo sollevare la questione sul mio viaggio. Quando, finalmente, vedremo la costa di "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?"),RandPhraseSimple(RandSwear()+"Capitano, chiedo per la terza volta - quando arriveremo a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?","Capitano, abbiamo perso un sacco di tempo! Quando mi porterai a "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?"),"Ascolta Capitano, questo è davvero troppo!","block",0,npchar,Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Per favore, scusa, avevo così tante cose da fare... In sette giorni sarai sicuramente dove devi essere.","Mi dispiace, "+GetAddress_Form(NPChar)+", davvero non avrei potuto adempiere ai miei obblighi nei tuoi confronti. Ma non preoccuparti, arriveremo in una settimana."),RandPhraseSimple("Devo scusarmi ancora una volta con te. Arriveremo alla tua destinazione in una settimana.","Di nuovo, mi dispiace. Arriveremo alla tua destinazione in una settimana."),RandPhraseSimple("E di nuovo devo chiedere il vostro perdono... Arriveremo alla vostra destinazione in una settimana.","E ancora una volta, mi dispiace. Arriveremo alla tua destinazione in una settimana, lo prometto."),"Capisco, "+GetAddress_Form(NPChar)+", ma per favore, abbi pazienza... Al massimo in sette giorni ti condurrò al tuo punto di destinazione!",npchar,Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Oh... un passeggero... Ti avevo dimenticato... Penso che troverai più comodo stare nella stiva, dove non mi darai più fastidio.","Beh-beh, non posso credere ai miei occhi! Uno sconosciuto sulla mia nave! Bene, allora taci e vai nella mia stiva, ora!"),"Per la seconda volta? Oh, davvero... Ma sai, forse, ti manderò nella stiva per un 'escursione'.","Per la terza volta? Che sfortuna, eh-eh... Beh, compagno, benvenuto nella mia stiva. Non avresti dovuto girare sul ponte della mia nave e disturbarmi.","Oh, capisco, è il grado più alto di irritazione! Basta con questa farsa. Benvenuto nella stiva. "+GetAddress_Form(NPChar)+".",npchar,Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("Bene, ma taglierò il tuo pagamento per il ritardo.","Bene, cercherò di crederti... Ma tieni a mente che ridurrò il tuo compenso!","Ebbene, non ho comunque dove andare, ma tieni a mente che ridurrò il tuo pagamento....");
			Link.l1 = LinkRandPhrase("Bene.","Bene, allora...","Va bene, come dici tu.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("Vorrei credere che questa volta tu stia per adempiere ai tuoi obblighi.","Spero davvero che questa sia la nostra ultima conversazione su questo argomento sgradevole.");
			Link.l1 = "Certo.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear()+"Che stiva? Non capisco!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "E cosa c'è ancora da capire? Da ora in poi sei mio prigioniero! Vai nella dannata stiva, muoviti!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "Solo uno scherzo... Tra sette giorni arriveremo nella tua città.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear()+"Pagherai per questo, "+GetSexPhrase("feccia","puzzolente")+"!";
			Link.l1 = "Tutti dicono così - ma alla fine tutti mi pagano!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("It has been reported that a captain named " + GetFullName(pchar) + " obliged to deliver a passenger by the name of " + GetFullName(npchar) + ", but didn't stay true to "+ GetSexPhrase("his","her") +" word. Besides, "+ GetSexPhrase("he","she") +" imprisoned a poor guy. That's what happens when you trust strange people...", 
				"What's wrong with this world?! Captain " + GetFullName(pchar) + " imprisoned a poor guy by the name of " + GetFullName(npchar) + ", despite him being a passenger on his ship...", 
				"People say, captain, that you are "+ GetSexPhrase("a real scoundrel","a really vile bitch") +". They say that poor " + GetFullName(npchar) + " was taken prisoner on board your ship. And you promised to deliver him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Very, very ugly ..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}
