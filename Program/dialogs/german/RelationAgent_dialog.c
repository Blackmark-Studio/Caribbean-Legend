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
			dialog.text = "Schön, dich wieder zu sehen.";
			link.l1 = "Ich brauche deine Dienste wieder.";
			link.l1.go = "relation";
			link.l2 = "Ich sollte gehen.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Ich möchte Ihnen ein Angebot machen."link.l4.go ="D_Schiffsbriefe_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Lassen Sie mich mich vorstellen. Ich bin der Mann, der für Sie bei jedem Gouverneur hier ein gutes Wort einlegen kann. Natürlich ist es nicht umsonst, aber glauben Sie mir, dass meine Dienste ihren Preis wert sind. Sie werden es nicht bereuen, für meine Talente zu bezahlen.";
				link.l1 = "Interessant. Mach weiter.";
				link.l1.go = "relation";
				link.l2 = "Vielleicht nächstes Mal.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Welche Bedingungen haben Sie?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "So eine königliche Großzügigkeit! Natürlich stimme ich zu!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Nein, kein Deal.";
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
			dialog.text = "Lass uns mal sehen, wie ich dir helfen kann.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Ich möchte mich mit England versöhnen.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Ich möchte mich mit Frankreich versöhnen.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Ich möchte mich mit Spanien versöhnen.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Ich möchte mich mit Holland versöhnen.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ich möchte mich mit den Schmugglern versöhnen.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Ich brauche einen Kaperbrief.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Hast du Handelslizenzen?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Ich habe eine Frage bezüglich des Besitzes von Kolonien.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Weißt du, ich sollte das besser selbst in die Hand nehmen.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Ich habe sie immer und aus verschiedenen Zeiten. Lizenz aus welchem Land möchtest du haben?";
		    link.l1 = "Von England";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Aus Frankreich";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Aus Spanien";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Aus Holland";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Weißt du, ich kümmere mich lieber selbst darum.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Periode?";
		    link.l1 = "30 Tage";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 Tage";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 Tage";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Ich habe meine Meinung geändert.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Also, die Handelslizenz von"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" für "+sti(npchar.LicenceType)+" Tage, der Preis beträgt "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Ich stimme zu.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Ich habe meine Meinung geändert.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Hier ist es. Vergiss nicht, eine freundliche Flagge zu hissen, wenn du einen Hafen betrittst. Und denk daran, dass die Patrouille das Datum der Lizenz überprüfen kann.";
			link.l9 = "Mein Dank.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Sehr ausgezeichnet! Komm zurück, wenn du genug Geld hast.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Prächtig. Zunächst musst du deine Loyalität gegenüber der Nation beweisen"+" durch eine ausgezeichnete Bedienung dafür. Gehe zu irgendeinem Gouverneur von"+//NationNameGenitive(sti(NPChar.nation))+" und erfülle einige seiner Missionen. Dann wird er dir eine Lizenz gewähren.";
			link.l1 = "Sag mir, "+GetAddress_FormToNPC(NPChar)+", kann ich diese langweilige Formalität umgehen?";
			link.l1.go = "patent_1";
			link.l2 = "Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Du meinst ein Bestechungsgeld!? Du willst, dass ich dir selbst eine Lizenz ausstelle?";
			link.l1 = "Genau!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Nein. Lebewohl, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Ich habe nicht die nötigen Beziehungen, um das zu tun. Und ich kann Ihnen kein leeres Lizenzdokument mit allen Stempeln und Zeichen besorgen.";
            link.l1 = "Schade. Leb wohl."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "In Ordnung, das kann ich für dich arrangieren. Welche Art von Lizenz benötigst du?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Von England";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Von Frankreich";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Aus Spanien";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Aus Holland";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Du weißt, ich würde es lieber selbst regeln.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Das ist ein Fehler, wenn du ihn siehst, dann kontaktiere ALexusB";
                    link.l1 = "Sieht gut aus für mich. Ich stimme Ihren Bedingungen zu!";
                    break;
                case HOLLAND :
                    dialog.text = "Holland ist fast eine friedliche Nation. Du wirst viele Freunde und wenige Feinde haben. Und die Lizenz selbst wird dich kosten "+pchar.PatentPrice+" Pesos.";
                    link.l1 = "Sieht gut aus für mich. Ich stimme Ihren Bedingungen zu!";
                    break;
                case FRANCE :
                    dialog.text = "Freunde und Feinde Frankreichs werden zu den Ihren. Sie dürfen die Schiffe ihrer Feinde versenken. Und die Lizenz selbst wird Sie kosten "+pchar.PatentPrice+" Pesos.";
                    link.l1 = "Klingt gut! Mir ist wirklich egal, wem ich dienen soll! Frankreich wird gut sein.";
                    break;
                case SPAIN :
                    dialog.text = "Spanien hat viele Feinde und sie werden auch Ihre sein! Spanien ist eine Nation der Seekrieger. Und die Lizenz selbst wird dich kosten "+pchar.PatentPrice+" Pesos.";
                    link.l1 = "Das ist genau das, was ich wollte! Nimm diesen erbärmlichen Geldbetrag für Kämpfe und Missionen für hochrangige Leute!";
                    break;
                case ENGLAND :
                    dialog.text = "Ehrlich gesagt, so füllt der englische Generalgouverneur seine Taschen. Und die Lizenz selbst wird Sie kosten "+pchar.PatentPrice+" Pesos.";
                    link.l1 = "Sehr gut. Gib ihm mein Blutgeld, das ich durch Schmuggel und Enterungen bekommen habe!";
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

			link.l2 = "Nein, das ist nichts für mich.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Ich bin froh, dass wir einen Handel abgeschlossen haben.";
			link.l1 = "Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = "Gut. Es wird dich kosten "+Pchar.questTemp.Relations.sum+" Pesos.";
			Link.l1 = "Ich stimme zu.";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Äußerst vorzüglich, ich werde alles regeln. Sie werden mit Ihnen zusammenarbeiten.";
			Link.l99 = "Danke.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Hm... Ich weiß sogar nicht, was ich sagen soll. Sicher, ich kann deinen Wunsch erfüllen, Frieden zu schließen mit "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abflug")+", es wird kosten "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Ich glaube nicht, dass ich eine Wahl habe. Nehmt mein Geld.";
				link.l1.go = "relation3";
			}
			link.l2 = "Nein, es ist zu viel. Lebewohl.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Prächtig! Es ist überraschend einfach, mit dir zu verhandeln. Keine Sorge, ich werde dein Problem in 15 Tagen lösen.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Dein Problem wird jetzt gelöst. Setz dich einfach hin und warte, es kann nicht schneller gehen.";
			Link.l99 = "Danke.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "Über den Besitz welcher Kolonie möchten Sie sprechen?";
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
			Link.l99 = "Nein. Nichts.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Kolonie "+GetCityName(colonies[i].id)+", hat gehört zu "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", Lösegeld für das Stoppen von Wiederergreifungsversuchen ist "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Ja, genau das, was ich brauche.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Nein danke. Ich bin nicht interessiert.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "In Ordnung, der Handel ist im Gange. Es wird keine Versuche geben zu fangen "+GetCityName(colonies[i].id)+" nochmal.";
			Link.l2 = "Danke. Hab einen schönen Tag.";
			Link.l2.go = "exit";
			Link.l3 = "Noch eine Frage.";
			Link.l3.go = "relation";
		break;
	}
}
