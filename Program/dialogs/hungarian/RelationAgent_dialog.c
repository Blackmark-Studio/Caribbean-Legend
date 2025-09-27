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
			dialog.text = "Örülök, hogy újra látlak.";
			link.l1 = "Újra szükségem van a szolgálataira.";
			link.l1.go = "relation";
			link.l2 = "Mennem kell.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Szeretnék egy üzletet ajánlani."
				link.l4.go = "D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hadd mutatkozzam be. Én vagyok az az ember, aki szólhat egy szót az érdekedben bármelyik itteni kormányozónál. Természetesen nem ingyen, de higgye el, hogy a szolgálataim megérik az árukat. Nem fogja megbánni, hogy fizetett a tehetségemért.";
				link.l1 = "Érdekes. Folytassa.";
				link.l1.go = "relation";
				link.l2 = "Talán legközelebb.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Mik a feltételei?";
			s1 = "Egy szerencsés véletlen folytán találtam egy legális csomagot a hajó irataival. Keresi ôket valaki?";
			s1 = s1 + "A hajó még mindig hajózik és a nyilvántartásban van, úgyhogy ne aggódj. Az a hülye tulaj csak elvesztette.";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Hadd lássam! Igen, a jelek itt valódiak. Ön egy szerencsés "+ GetSexPhrase("férfi","nô") +"! ";
			s1 = s1 + "Csak egy ilyen csomagra van szükségem, és felajánlhatom " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pezó. Mit szólna hozzá?";
			dialog.text = s1;
			link.l1 = "Micsoda királyi nagylelkûség! Természetesen egyetértek!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Nem, nincs üzlet.";
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
			dialog.text = "Lássuk, hogyan tudok segíteni.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Ki akarok békülni Angliával.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Ki akarok békülni Franciaországgal.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Ki akarok békülni Spanyolországgal.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Ki akarok békülni Hollandiával.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ki akarok békülni a csempészekkel.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Szükségem van egy páholylevélre.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Van kereskedelmi engedélyed?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Kérdésem van a gyarmatok tulajdonjogával kapcsolatban.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Tudja, jobb, ha egyedül intézem el.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Nekem mindig vannak, és különbözô korszakokból. Melyik ország engedélyét kéri?";
		    link.l1 = "Angliáéra.";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Franciaországé.";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Spanyolországé.";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Hollandiából";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Tudja, jobb, ha egyedül intézem el.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Idôszak?";
		    link.l1 = "30 nap";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 nap";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 nap";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Meggondoltam magam.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Tehát, a kereskedelmi engedély" + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + " a " + sti(npchar.LicenceType) + " napokra, az ár " + FindRussianMoneyString(iSumm) + ".";
		    link.l1 = "Egyetértek.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Meggondoltam magam.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Itt van. Ne felejtsd el felhúzni a barátságos zászlót a kikötôbe való belépéskor. És ne feledd, hogy a járôr ellenôrizheti az engedély dátumát.";
			link.l9 = "Köszönöm.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "A legkiválóbb! Gyere vissza, ha lesz elég pénzed.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Pompás. Elôször is bizonyítania kell a nemzethez való hûségét" + 
                          " egy kiváló szolgálatot tesz érte. Menj el" + //NationNameGenitive(sti(NPChar.nation)) +
                          " bármelyik kormányzóhoz, és teljesítsd néhány küldetését. Ezután ô megadja neked az engedélyt.";
			link.l1 = "Mondja, "+GetAddress_FormToNPC(NPChar) + ", megkerülhetem ezt az unalmas formaságot?";
			link.l1.go = "patent_1";
			link.l2 = "Farwell, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Úgy érted, megvesztegetéssel? Azt akarod, hogy én magam adjak neked engedélyt?";
			link.l1 = "Pontosan!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Nem. Viszlát, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Nekem nincsenek olyan kapcsolataim, hogy ezt megtegyem. És nem tudok önnek egy üres üres engedélyt szerezni minden bélyegzôvel és aláírással.";
            link.l1 = "Kár érte. Viszontlátásra."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "Rendben, elintézem magának. Milyen engedélyre van szüksége?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Angliáéra.";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Franciaországé.";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Spanyolországé.";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Hollandiából";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Tudod, hogy jobb, ha egyedül intézem el.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Ez egy hiba, ha látod, akkor vedd fel a kapcsolatot ALexusB-vel.";
                    link.l1 = "Nekem jónak tûnik. Egyetértek a feltételeiddel!";
                    break;
                case HOLLAND :
                    dialog.text = "Hollandia szinte békés nemzet. Sok barátot és kevés ellenséget szerezhetsz. Maga az engedély pedig "+pchar.PatentPrice+" pezóba fog kerülni.";
                    link.l1 = "Nekem jónak tûnik. Egyetértek a feltételeiddel!";
                    break;
                case FRANCE :
                    dialog.text = "Franciaország barátai és ellenségei a tiétek lesznek. Engedélyt kaptok, hogy ellenségeik hajóit elsüllyesszétek. Maga az engedély pedig "+pchar.PatentPrice+" pezóba fog kerülni.";
                    link.l1 = "Jól hangzik! Nem igazán érdekel, hogy kit szolgáljak! Franciaország rendben lesz.";
                    break;
                case SPAIN :
                    dialog.text = "Spanyolországnak sok ellensége van, és ôk lesznek a tiéd is! Spanyolország a tengeri harcosok nemzete. Maga az engedély pedig "+pchar.PatentPrice+" pesóba fog kerülni.";
                    link.l1 = "Ez az, amit akartam! Fogd ezt a szánalmas összeget érmékért harcokért és küldetésekért magas rangú embereknek!";
                    break;
                case ENGLAND :
                    dialog.text = "Hogy ôszinte legyek, az angol fôkormányzó így tölti meg a zsebét. Maga az engedély pedig "+pchar.PatentPrice+" pezóba kerül.";
                    link.l1 = "Rendben van. Add oda neki a vérdíjam, amit csempészésbôl és beszállással szereztem!";
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

			link.l2 = "Nem, ez nem az enyém.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Örülök, hogy megegyeztünk.";
			link.l1 = "Ég veled, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "Jól van. Ez a " + iDiplomatPseudoGlobal + " pezóba fog kerülni.";
			Link.l1 = "Egyetértek.";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Meggondoltam magam.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Kitûnô, mindent elintézek. Együtt fognak dolgozni veled.";
			Link.l99 = "Köszönjük!";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "Hm... Nem is tudom, mit mondjak. Persze, hogy teljesíthetem a kérésedet, hogy békét köss "+ XI_ConvertString(Nations[i].Name + "Abl") +", ez " + FindRussianMoneyString(iDiplomatPseudoGlobal) + "árába kerül.";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "Nem hiszem, hogy van más választásom. Fogadd el a pénzem.";
				link.l1.go = "relation3";
			}
			link.l2 = "Nem, ez túl sok. Viszontlátásra.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Nagyszerû! Meglepôen könnyû veled üzletelni. Ne aggódjon, 15 napon belül megoldom a problémáját.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "A problémája most fog megoldódni. Csak üljön és várjon, ennél gyorsabban nem megy.";
			Link.l99 = "Köszönjük!";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "Melyik kolónia tulajdonjogáról akarsz beszélni?";
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
			Link.l99 = "Nem. Semmit.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony " + GetCityName(colonies[i].id) + ", tartozott " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", váltságdíj a visszafoglalási kísérletek leállításáért " + FindRussianMoneyString(iSumm) + ".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Igen, pontosan erre van szükségem.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Nem, köszönöm. Nem érdekel.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Rendben, az üzlet folyamatban van. Nem lesz több próbálkozás a " + GetCityName(colonies[i].id) + " elfogására.";
			Link.l2 = "Köszönöm. További szép napot.";
			Link.l2.go = "exit";
			Link.l3 = "Még egy kérdés.";
			Link.l3.go = "relation";
		break;
	}
}
