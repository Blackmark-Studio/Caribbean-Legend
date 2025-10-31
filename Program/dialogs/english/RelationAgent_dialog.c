int iDiplomatPseudoGlobal;

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
        npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Glad to see you again.";
			link.l1 = "I need your services again.";
			link.l1.go = "relation";
			link.l2 = "I should go.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "I want to offer you a deal."link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Let me introduce myself. I am the man who can put in a word for you with any governor here. It is not free, of course, but trust me, my services are worth the price. You won't regret paying for my talents.";
				link.l1 = "Interesting. Go on.";
				link.l1.go = "relation";
				link.l2 = "Maybe next time.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "What are your terms?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Such royal generosity! Of course I agree!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "No, no deal.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "Let's see how I can help you.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "I want to reconcile with England.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "I want to reconcile with France.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "I want to reconcile with Spain.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "I want to reconcile with Holland.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "I want to make peace with the smugglers.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "I need a letter of marque.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Got any trade licenses?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "I have a question about the ownership of colonies.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "You know, I'd better handle it myself.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "I always have them, from different periods. Which country's license do you want?";
		    link.l1 = "Of England";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Of France";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Of Spain";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Of Holland";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "You know, I'd better handle it myself.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Period?";
		    link.l1 = "30 days";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 days";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 days";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "I have changed my mind.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "So, the trade licence of"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" for "+sti(npchar.LicenceType)+" days, the price is "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "I agree.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "I've changed my mind.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Here it is. Don't forget to raise a friendly flag when entering a port. And remember that the patrol can check the license's date.";
			link.l9 = "My thanks.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Most excellent! Come back when you have enough money.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Splendid. First of all, you have to prove your loyalty to the nation"+" by an excellent service for it. Go to any governor of"+//NationNameGenitive(sti(NPChar.nation))+" and complete a few of his missions. Then he will grant you a license.";
			link.l1 = "Tell me, "+GetAddress_FormToNPC(NPChar)+", is there any way I can get around this tedious formality?";
			link.l1.go = "patent_1";
			link.l2 = "Farewell, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "You mean a bribe!? You want me to make you a licence myself?";
			link.l1 = "Exactly!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "No. Farewell, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "I don't have those kinds of connections to do this. And I can't get you a blank license with all the stamps and signatures.";
            link.l1 = "Too bad. Farewell."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "Alright, I can arrange that for you. What kind of license do you need?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Of England";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Of France";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Of Spain";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Of Holland";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "You know I'd better handle it myself.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "This is a bug. If you see it, please contact ALexusB";
                    link.l1 = "Looks fine to me. I agree to your terms!";
                    break;
                case HOLLAND :
                    dialog.text = "Holland is almost a peaceful nation. You will make many friends and only a few enemies. And the license itself will cost you "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Looks fine to me. I agree to your terms!";
                    break;
                case FRANCE :
                    dialog.text = "Friends and enemies of France will become yours. You will be allowed to sink ships belonging to their enemies. And the license itself will cost you "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Sounds good! I don't really care who I serve! France will be fine.";
                    break;
                case SPAIN :
                    dialog.text = "Spain has many enemies, and they will be yours as well! Spain is a nation of sea warriors. And the license itself will cost you "+pchar.PatentPrice+" pesos.";
                    link.l1 = "That's what I wanted! Take this paltry sum of coins for fighting and missions for high-ranking people!";
                    break;
                case ENGLAND :
                    dialog.text = "To be honest, this is how the English governor-general lines his pockets. And the license itself will cost you "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Very well. Give him my blood money, which I earned through smuggling and boarding!";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "No, it's not for me.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "I am glad that we have made a deal.";
			link.l1 = "Farewell, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "Fine. It will cost you " + iDiplomatPseudoGlobal + " pesos.";
			Link.l1 = "I agree.";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "I've changed my mind.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Most excellent, I will settle everything. They will work with you.";
			Link.l99 = "Thanks.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "Hm... I don't even know what to say. Of course I can grant your request to make peace with "+XI_ConvertString(Nations[i].Name+"Abl")+", it will cost "+FindRussianMoneyString(iDiplomatPseudoGlobal)+".";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "I don't think I have a choice. Take my money.";
				link.l1.go = "relation3";
			}
			link.l2 = "No, it is too much. Farewell.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Splendid! It is surprisingly easy to deal with you. Don't worry, I will settle your problem in 15 days.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Your problem is about to be solved now. Just sit and wait, it can't go any faster.";
			Link.l99 = "Thanks.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "Which colony's ownership do you want to discuss?";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "No. Nothing.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony "+GetCityName(colonies[i].id)+", has belonged to "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", ransom for stopping recapture attempts is "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Yes, exactly what I need.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "No thanks. I'm not interested.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Alright, the deal is in progress. There won't be any attempts to capture "+GetCityName(colonies[i].id)+" again.";
			Link.l2 = "Thank you. Have a nice day.";
			Link.l2.go = "exit";
			Link.l3 = "One more question.";
			Link.l3.go = "relation";
		break;
	}
}
