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
			dialog.text = "Cieszę się, że znowu cię widzę.";
			link.l1 = "Potrzebuję twoich usług ponownie.";
			link.l1.go = "relation";
			link.l2 = "Powinienem iść.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Chcę ci zaproponować umowę."link.l4.go ="D_ListyStatku_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Pozwól, że się przedstawię. Jestem człowiekiem, który może załatwić dla ciebie dobre słowo u dowolnego gubernatora tutaj. Oczywiście nie jest to za darmo, ale wierz mi, że moje usługi są warte swojej ceny. Nie pożałujesz zapłacenia za moje talenty.";
				link.l1 = "Ciekawe. Mów dalej.";
				link.l1.go = "relation";
				link.l2 = "Może następnym razem.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Jakie są twoje warunki?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Taka królewska hojność! Oczywiście, że się zgadzam!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Nie, żadnej umowy.";
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
			dialog.text = "Zobaczmy, jak mogę ci pomóc.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Chcę się pogodzić z Anglią.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Chcę się pojednać z Francją.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Chcę pogodzić się z Hiszpanią.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Chcę się pojednać z Holandią.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Chcę się pogodzić ze szmuglerami.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Potrzebuję listu kaperskiego.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Masz jakieś licencje handlowe?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Mam pytanie o własność kolonii.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Wiesz, chyba lepiej poradzę sobie sam.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Zawsze je mam i z różnych okresów. Licencja którego kraju cię interesuje?";
		    link.l1 = "Anglii";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Francji";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Hiszpanii";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Holandii";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Wiesz, lepiej sobie z tym poradzę sam.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Okres?";
		    link.l1 = "30 dni";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 dni";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 dni";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Zmieniłem swoje zdanie.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Czyli, licencja handlowa"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" za "+sti(npchar.LicenceType)+" dni, cena wynosi "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Zgadzam się.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Zmieniłem zdanie.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Oto jest. Nie zapomnij podnieść przyjazną flagę podczas wchodzenia do portu. I pamiętaj, że patrol może sprawdzić datę licencji.";
			link.l9 = "Dziękuję.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Doskonale! Wróć, gdy zdobędziesz wystarczająco dużo pieniędzy.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Wspaniale. Przede wszystkim musisz udowodnić swoją lojalność wobec narodu"+" przez doskonałą obsługę. Idź do dowolnego gubernatora"+//NationNameGenitive(sti(NPChar.nation))+" i wykonaj kilka jego misji. Wtedy udzieli ci licencji.";
			link.l1 = "Powiedz mi, "+GetAddress_FormToNPC(NPChar)+", czy mogę ominąć tę nudną formalność?";
			link.l1.go = "patent_1";
			link.l2 = "Żegnaj, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Masz na myśli łapówkę!? Chcesz, żebym sam dla ciebie wykonał licencję?";
			link.l1 = "Dokładnie!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Nie. Do widzenia, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Nie mam takich relacji, aby to zrobić. I nie mogę ci dostarczyć pustego blankietu licencji ze wszystkimi pieczęciami i znakami.";
            link.l1 = "Szkoda. Do widzenia."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "W porządku, mogę to dla ciebie załatwić. Jakiej licencji potrzebujesz?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Anglii";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Francji";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Hiszpanii";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Z Holandii";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Wiesz, że lepiej poradzę sobie z tym sam.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "To jest błąd, jeśli go zauważysz, skontaktuj się z ALexusB";
                    link.l1 = "Wygląda dobrze dla mnie. Zgadzam się na twoje warunki!";
                    break;
                case HOLLAND :
                    dialog.text = "Holandia to prawie pokojowe naród. Zdobędziesz wielu przyjaciół i kilku wrogów. A sama licencja będzie cię kosztować "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Wygląda dobrze dla mnie. Zgadzam się na twoje warunki!";
                    break;
                case FRANCE :
                    dialog.text = "Przyjaciele i wrogowie Francji staną się twoimi. Będziesz mógł zatapiać statki ich wrogów. A sama licencja będzie cię kosztować "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Brzmi dobrze! Naprawdę nie zależy mi, komu powinienem służyć! Francja będzie w porządku.";
                    break;
                case SPAIN :
                    dialog.text = "Hiszpania ma wielu wrogów i oni także staną się twoimi! Hiszpania to naród wojowników morskich. A sama licencja będzie cię kosztować "+pchar.PatentPrice+" pesos.";
                    link.l1 = "To jest to, czego chciałem! Weź te żałosne monety za walki i misje dla wysoko postawionych osób!";
                    break;
                case ENGLAND :
                    dialog.text = "Szczerze mówiąc, tak angielski gubernator generalny napełnia swoją kieszeń. A sama licencja będzie cię kosztować "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Bardzo dobrze. Daj mu moje krwawe pieniądze, które zdobyłem dzięki kontrabandzie i abordażom!";
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

			link.l2 = "Nie, to nie dla mnie.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Cieszę się, że doszliśmy do porozumienia.";
			link.l1 = "Żegnaj, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = "Dobrze. To będzie cię kosztować "+Pchar.questTemp.Relations.sum+" pesos.";
			Link.l1 = "Zgadzam się.";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Zmieniłem zdanie.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Znakomicie, załatwię wszystko. Będą z tobą współpracować.";
			Link.l99 = "Dzięki.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Hm... Nawet nie wiem, co powiedzieć. Oczywiście mogę spełnić twoją prośbę o nawiązanie pokoju z "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", to będzie kosztować "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Nie sądzę, że mam wybór. Weź moje pieniądze.";
				link.l1.go = "relation3";
			}
			link.l2 = "Nie, to za dużo. Do widzenia.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Wspaniale! Zaskakująco łatwo idzie mi z tobą rozmowa. Nie martw się, załatwię twój problem w ciągu 15 dni.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Twój problem zaraz zostanie rozwiązany. Po prostu usiądź i czekaj, nie może pójść szybciej.";
			Link.l99 = "Dzięki.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "O której z kolonii chcesz rozmawiać?";
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
			Link.l99 = "Nie. Nic.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Kolonia "+GetCityName(colonies[i].id)+", należało do "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", okup za zaniechanie prób odzyskania to "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Tak, dokładnie tego potrzebuję.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Nie, dziękuję. Nie jestem zainteresowany.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Dobrze, umowa jest w trakcie realizacji. Nie będzie żadnych prób schwytania "+GetCityName(colonies[i].id)+" znowu.";
			Link.l2 = "Dzięki. Miłego dnia.";
			Link.l2.go = "exit";
			Link.l3 = "Jeszcze jedno pytanie.";
			Link.l3.go = "relation";
		break;
	}
}
