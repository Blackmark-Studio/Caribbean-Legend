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
				dialog.text = RandPhraseSimple("Ahhh, verdammt! Ich weiß, wer du bist! Nur ein völliger Idiot würde als Passagier an Bord deines Schiffes gehen! Auf Wiedersehen!","Oh, ich weiß, wer du bist! Ich werde nie einen Fuß auf dein Schiff setzen. Ich bin kein Narr...");
				link.l1 = RandPhraseSimple("Heh, was für ein Feigling!","Die Leute sind heutzutage solche Feiglinge geworden!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(NPChar)+". Ich habe gehört, du nimmst Passagiere mit?";
				link.l1 = "Vielleicht. Es hängt von meinem Gewinn ab.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "Ich muss zur Taverne gebracht werden von "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", das auf "+XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination)+"Dat")+", für "+FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time))+", und dafür werde ich dich bezahlen "+FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money))+". Bist du einverstanden?";
			link.l1 = "Ja, das tue ich.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Ich glaube nicht, dass es ein interessantes Angebot ist.";
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
			dialog.text = "Danke. Du hast deine Verpflichtungen erfüllt. Ich bin an meinem Zielort, hier ist deine Belohnung. Bitte schön.";
			Link.l1 = "Danke.";
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
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear()+"Kapitän, die Zeit ist abgelaufen. Wann, verdammt nochmal, komme ich endlich dazu "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?",RandSwear()+"Kapitän, wie viel länger wollen Sie noch Gott weiß wo herumirren?! Wann kommen wir endlich an "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?",RandSwear()+"Hör zu, Kapitän, ich muss nach "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", und ich möchte eine klare und einfache Antwort bekommen, wann das passieren wird!"),RandPhraseSimple("Kapitän, einmal mehr muss ich eine Frage bezüglich Ihrer Verpflichtungen stellen. Wann kommen wir an "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?","Kapitän, zum zweiten Mal muss ich die Frage nach meiner Reise stellen. Wann werden wir endlich die Küste sehen "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?"),RandPhraseSimple(RandSwear()+"Kapitän, ich frage zum dritten Mal - wann kommen wir an "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?","Kapitän, wir haben eine Hölle von einer Zeit verloren! Wann bringen Sie mich zu "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?"),"Hör zu, Kapitän, das ist wirklich zu viel!","Block",0,npchar,Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Bitte entschuldigen Sie, ich hatte so viel zu tun... In sieben Tagen werden Sie sicher dort sein, wo Sie sein müssen.","Es tut mir leid, "+GetAddress_Form(NPChar)+", Ich hätte wirklich meine Verpflichtungen Ihnen gegenüber nicht erfüllen können. Aber mach dir keine Sorgen, wir werden in einer Woche ankommen."),RandPhraseSimple("Ich muss mich noch einmal bei dir entschuldigen. Wir werden in einer Woche an deinem Zielort ankommen.","Noch einmal, es tut mir leid. Wir werden in einer Woche an Ihrem Ziel ankommen."),RandPhraseSimple("Und einmal mehr muss ich um Ihre Entschuldigung bitten... Wir werden in einer Woche an Ihrem Zielort ankommen.","Und noch einmal, es tut mir leid. Wir werden in einer Woche an Ihrem Ziel ankommen, das verspreche ich."),"Ich verstehe, "+GetAddress_Form(NPChar)+", aber bitte, hab Geduld... In höchstens sieben Tagen bringe ich dich zu deinem Zielort!",npchar,Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Oh... ein Passagier... Ich habe dich vergessen... Ich glaube, du wirst es im Laderaum bequemer finden, wo du mich nicht mehr belästigen wirst.","Nun, ich kann meinen eigenen Augen nicht trauen! Ein Fremder ist auf meinem Schiff! Gut, dann halt den Mund und geh jetzt in meinen Laderaum!"),"Zum zweiten Mal? Oh, tatsächlich... Aber weißt du, vielleicht schicke ich dich für einen 'Ausflug' in den Laderaum.","Zum dritten Mal? Das ist aber schade, he-he... Nun, Kamerad, willkommen in meinem Laderaum. Du hättest nicht auf dem Deck meines Schiffes herumlaufen und mich stören sollen.","Oh, ich sehe, das ist der höchste Grad der Irritation! Also gut, genug von dieser Farce. Willkommen im Laderaum. "+GetAddress_Form(NPChar)+".",npchar,Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("In Ordnung, aber ich werde deine Bezahlung für die Verzögerung kürzen.","Also gut, ich werde versuchen, dir zu glauben... Aber denk daran, dass ich deine Gebühr kürzen werde!","Nun, es gibt sowieso nirgendwohin für mich zu gehen, aber behalte im Hinterkopf, dass ich deine Bezahlung kürzen werde....");
			Link.l1 = LinkRandPhrase("In Ordnung.","Gut, dann...","In Ordnung, wie du sagst.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("Ich möchte glauben, dass Sie dieses Mal Ihre Verpflichtungen erfüllen werden.","Ich hoffe doch sehr, dass dies unser letztes Gespräch zu diesem unangenehmen Thema ist.");
			Link.l1 = "Natürlich.";
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
			dialog.text = RandSwear()+"Welches Versteck? Ich verstehe nicht!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "Und was gibt es sonst noch zu verstehen? Ab jetzt bist du mein Gefangener! Geh zum verfluchten Laderaum, beweg dich!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "Nur ein Scherz... In sieben Tagen werden wir in deiner Stadt ankommen.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear()+"Du wirst dafür bezahlen, "+GetSexPhrase("Gesindel","Stinker")+"!";
			Link.l1 = "Jeder sagt das - aber am Ende zahlen sie alle mir!";
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
