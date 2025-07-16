#define DIPLOMAT_SUM 80000

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
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
 	    }
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
			dialog.text = "Contento di rivederti.";
			link.l1 = "Ho bisogno dei tuoi servizi di nuovo.";
			link.l1.go = "relation";
			link.l2 = "Dovrei andare.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Voglio offrirti un accordo."link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Lasciami presentarmi. Sono l'uomo che può parlare per te con qualsiasi governatore qui. Non è ovviamente gratis, ma fidati che i miei servizi valgono il loro prezzo. Non rimpiangerai di aver pagato per i miei talenti.";
				link.l1 = "Interessante. Continua.";
				link.l1.go = "relation";
				link.l2 = "Forse la prossima volta.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Quali sono le tue condizioni?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Una generosità così regale! Naturalmente sono d'accordo!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "No, niente accordo.";
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
			dialog.text = "Vediamo come posso aiutarti.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Voglio riconciliarmi con l'Inghilterra.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Voglio riconciliarmi con la Francia.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Voglio riconciliarmi con la Spagna.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Voglio riconciliarmi con l'Olanda.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Voglio riconciliarmi con i contrabbandieri.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Ho bisogno di una lettera di corsa.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Hai delle licenze commerciali?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Ho una domanda sulla proprietà delle colonie.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Sai, è meglio se me ne occupo da solo.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Ne ho sempre e di periodi diversi. Licenza di quale paese vuoi?";
		    link.l1 = "D'Inghilterra";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Della Francia";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Della Spagna";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Dell'Olanda";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Sai, è meglio se me ne occupo da solo.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Periodo?";
		    link.l1 = "30 giorni";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 giorni";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 giorni";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Ho cambiato idea.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Allora, la licenza commerciale di"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" per "+sti(npchar.LicenceType)+" giorni, il prezzo è "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Sono d'accordo.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Ho cambiato idea.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Eccola qua. Non dimenticare di issare una bandiera amichevole mentre entri in un porto. E ricorda che la pattuglia può controllare la data della licenza.";
			link.l9 = "Grazie mille.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Eccellente! Torna quando avrai abbastanza soldi.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Splendido. Prima di tutto devi dimostrare la tua lealtà alla nazione"+" da un eccellente servizio per questo. Vai da qualsiasi governatore di"+//NationNameGenitive(sti(NPChar.nation))+" e completa alcune delle sue missioni. Poi ti concederà una licenza.";
			link.l1 = "Dimmi, "+GetAddress_FormToNPC(NPChar)+", posso evitare questa noiosa formalità?";
			link.l1.go = "patent_1";
			link.l2 = "Addio, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Vuoi dire una tangente!? Vuoi che ti faccia una licenza da solo?";
			link.l1 = "Esattamente!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "No. Addio, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Non ho quel tipo di relazioni per fare questo. E non posso procurarti una licenza vuota con tutti i timbri e i segni.";
            link.l1 = "Peccato. Addio."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "Bene, posso organizzare questo per te. Di che tipo di licenza hai bisogno?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Dell'Inghilterra";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Della Francia";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Della Spagna";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Dell'Olanda";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Sai che sarebbe meglio se me ne occupassi da solo.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Questo è un bug, se lo vedi, allora contatta ALexusB";
                    link.l1 = "Sembra buono per me. Concordo con i tuoi termini!";
                    break;
                case HOLLAND :
                    dialog.text = "L'Olanda è quasi una nazione pacifica. Ti farai molti amici e pochi nemici. E la licenza stessa ti costerà "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Sembra buono per me. Accetto i tuoi termini!";
                    break;
                case FRANCE :
                    dialog.text = "Gli amici e i nemici della Francia saranno anche i tuoi. Ti sarà permesso di affondare le navi dei loro nemici. E la licenza stessa ti costerà "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Suona bene! Non mi importa davvero di chi dovrei servire! La Francia andrà bene.";
                    break;
                case SPAIN :
                    dialog.text = "La Spagna ha molti nemici e saranno anche i tuoi! La Spagna è una nazione di guerrieri del mare. E la licenza stessa ti costerà "+pchar.PatentPrice+" pesos.";
                    link.l1 = "È proprio quello che volevo! Prendi questa misera somma di monete per combattimenti e missioni per persone di alto rango!";
                    break;
                case ENGLAND :
                    dialog.text = "Ad essere onesti, è così che il governatore generale inglese riempie le sue tasche. E la licenza stessa ti costerà "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Molto bene. Dagli il mio denaro insanguinato che ho ottenuto attraverso contrabbando e abbordaggi!";
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

			link.l2 = "No, non fa per me.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Sono contento che abbiamo fatto un accordo.";
			link.l1 = "Addio, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = "Bene. Ti costerà "+Pchar.questTemp.Relations.sum+" pesos.";
			Link.l1 = "Sono d'accordo.";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Ho cambiato idea.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Eccellente, sistemero' tutto. Lavoreranno con te.";
			Link.l99 = "Grazie.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Mh... Non so nemmeno cosa dire. Certo che posso esaudire la tua richiesta di fare pace con "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", ti costerà "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Non credo di avere una scelta. Prendi i miei soldi.";
				link.l1.go = "relation3";
			}
			link.l2 = "No, è troppo. Addio.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Splendido! È sorprendentemente facile trattare con te. Non preoccuparti, risolverò il tuo problema in 15 giorni.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Il tuo problema sta per essere risolto ora. Siediti e aspetta, non può andare più veloce.";
			Link.l99 = "Grazie.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "Di quale colonia vuoi discutere la proprietà?";
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
			Link.l99 = "No. Niente.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colonia "+GetCityName(colonies[i].id)+", ha appartenuto a "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", il riscatto per fermare i tentativi di riconquista è "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Sì, esattamente quello di cui ho bisogno.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "No grazie. Non sono interessato.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Bene, l'affare è in corso. Non ci saranno tentativi di cattura "+GetCityName(colonies[i].id)+" di nuovo.";
			Link.l2 = "Grazie. Buona giornata.";
			Link.l2.go = "exit";
			Link.l3 = "Un'altra domanda.";
			Link.l3.go = "relation";
		break;
	}
}
