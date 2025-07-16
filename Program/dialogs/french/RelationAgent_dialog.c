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
			dialog.text = "Heureux de vous revoir.";
			link.l1 = "J'ai besoin de vos services à nouveau.";
			link.l1.go = "relation";
			link.l2 = "Je devrais partir.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Je veux vous proposer un marché."link.l4.go ="D_LettresDeNavire_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Laissez-moi me présenter. Je suis l'homme qui peut parler en votre faveur auprès de n'importe quel gouverneur ici. Ce n'est bien sûr pas gratuit, mais croyez-moi, mes services valent leur prix. Vous ne regretterez pas d'avoir payé pour mes talents.";
				link.l1 = "Intéressant. Continuez.";
				link.l1.go = "relation";
				link.l2 = "Peut-être la prochaine fois.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Quelles sont vos conditions?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Une telle générosité royale ! Bien sûr, je suis d'accord !";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Non, pas d'accord.";
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
			dialog.text = "Voyons comment je peux vous aider.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Je veux me réconcilier avec l'Angleterre.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Je veux me réconcilier avec la France.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Je veux me réconcilier avec l'Espagne.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Je veux me réconcilier avec la Hollande.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Je veux me réconcilier avec les contrebandiers.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "J'ai besoin d'une lettre de marque.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Vous avez des licences commerciales ?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "J'ai une question sur la propriété des colonies.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Tu sais, je ferais mieux de m'en occuper moi-même.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "J'en ai toujours et de différentes périodes. Licence de quel pays voulez-vous ?";
		    link.l1 = "De l'Angleterre";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "De France";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "De l'Espagne";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "De Hollande";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Tu sais, je ferais mieux de m'en occuper moi-même.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Période?";
		    link.l1 = "30 jours";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 jours";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 jours";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "J'ai changé d'avis.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Alors, la licence commerciale de"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gén")+" pour "+sti(npchar.LicenceType)+" jours, le prix est "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Je suis d'accord.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "J'ai changé d'avis.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Voici. N'oublie pas de hisser un drapeau amical en entrant dans un port. Et souviens-toi que la patrouille peut vérifier la date de la licence.";
			link.l9 = "Mes remerciements.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Excellent ! Reviens quand tu auras assez d'argent.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Magnifique. Tout d'abord, vous devez prouver votre loyauté envers la nation"+" par une excellente portion pour cela. Allez à n'importe quel gouverneur de"+//NationNameGenitive(sti(NPChar.nation))+" et accomplis quelques-unes de ses missions. Ensuite, il te donnera une licence.";
			link.l1 = "Dites-moi, "+GetAddress_FormToNPC(NPChar)+", puis-je contourner cette formalité ennuyeuse?";
			link.l1.go = "patent_1";
			link.l2 = "Adieu, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Tu veux dire un pot-de-vin !? Tu veux que je te fasse une licence moi-même ?";
			link.l1 = "Exactement!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Non. Adieu, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Je n'ai pas ce genre de relations pour faire ça. Et je ne peux pas vous obtenir un blanc vierge de licence avec tous les timbres et signes.";
            link.l1 = "Dommage. Adieu."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "D'accord, je peux arranger ça pour toi. Quel type de licence as-tu besoin?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "De l'Angleterre";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "De la France";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "De l'Espagne";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "De Hollande";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Tu sais que je ferais mieux de m'en occuper moi-même.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "C'est un bug, si tu le vois, alors contacte ALexusB";
                    link.l1 = "Ça me semble bien. Je suis d'accord avec vos conditions !";
                    break;
                case HOLLAND :
                    dialog.text = "La Hollande est presque une nation pacifique. Vous vous ferez beaucoup d'amis et quelques ennemis. Et la licence elle-même vous coûtera "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Ça me semble bien. Je suis d'accord avec vos conditions !";
                    break;
                case FRANCE :
                    dialog.text = "Les amis et les ennemis de la France seront les vôtres. On vous permettra de couler les navires de leurs ennemis. Et la licence elle-même vous coûtera "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Cela me convient! Je me fiche vraiment de qui je devrais servir! La France ira bien.";
                    break;
                case SPAIN :
                    dialog.text = "L'Espagne a beaucoup d'ennemis et ils seront aussi les tiens ! L'Espagne est une nation de guerriers de la mer. Et la licence elle-même te coûtera "+pchar.PatentPrice+" pesos.";
                    link.l1 = "C'est ce que je voulais! Prends cette somme pathétique de pièces pour des combats et des missions pour des personnes de haut rang!";
                    break;
                case ENGLAND :
                    dialog.text = "Pour être honnête, c'est ainsi que le gouverneur général anglais remplit sa poche. Et la licence elle-même vous coûtera "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Très bien. Donne-lui mon argent du sang que j'ai obtenu par la contrebande et les abordages !";
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

			link.l2 = "Non, ce n'est pas pour moi.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Je suis content que nous ayons conclu un accord.";
			link.l1 = "Adieu, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = "D'accord. Cela vous coûtera "+Pchar.questTemp.Relations.sum+" pesos.";
			Link.l1 = "Je suis d'accord.";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "J'ai changé d'avis.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Très excellent, je vais régler tout. Ils travailleront avec toi.";
			Link.l99 = "Merci.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Hm... Je ne sais même pas quoi dire. Bien sûr, je peux satisfaire votre demande de faire la paix avec "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", cela coûtera "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Je ne pense pas que j'ai le choix. Prends mon argent.";
				link.l1.go = "relation3";
			}
			link.l2 = "Non, c'est trop. Adieu.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Splendide! Il est étonnamment facile de traiter avec toi. Ne t'inquiète pas, je réglerai ton problème en 15 jours.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Votre problème est sur le point d'être résolu maintenant. Asseyez-vous simplement et attendez, ça ne peut pas aller plus vite.";
			Link.l99 = "Merci.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "De quelle colonie dont vous voulez discuter la propriete?";
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
			Link.l99 = "Non. Rien.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colonie "+GetCityName(colonies[i].id)+", a appartenu à "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", la rançon pour arrêter les tentatives de reconquête est "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Oui, exactement ce dont j'ai besoin.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Non merci. Je ne suis pas intéressé.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "D'accord, l'affaire est en cours. Il n'y aura aucune tentative de capture "+GetCityName(colonies[i].id)+" encore.";
			Link.l2 = "Merci. Passe une bonne journée.";
			Link.l2.go = "exit";
			Link.l3 = "Une question de plus.";
			Link.l3.go = "relation";
		break;
	}
}
