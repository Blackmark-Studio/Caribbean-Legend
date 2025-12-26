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
			dialog.text = "Que bom te ver de novo.";
			link.l1 = "Preciso dos seus serviços novamente.";
			link.l1.go = "relation";
			link.l2 = "Eu devo ir.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Quero te fazer uma proposta."link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Deixe-me me apresentar. Sou o homem que pode recomendar você a qualquer governador daqui. Não é de graça, claro, mas acredite, meus serviços valem o preço. Você não vai se arrepender de pagar pelo meu talento.";
				link.l1 = "Interessante. Continue.";
				link.l1.go = "relation";
				link.l2 = "Talvez da próxima vez.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Quais são seus termos?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Que generosidade real! Claro que eu aceito!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Não, sem acordo.";
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
			dialog.text = "Vamos ver como posso te ajudar.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "Quero me reconciliar com a Inglaterra.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Quero me reconciliar com a França.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "Quero me reconciliar com a Espanha.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Quero me reconciliar com a Holanda.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Quero fazer as pazes com os contrabandistas.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Preciso de uma carta de corso.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Tem alguma licença de comércio?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Tenho uma pergunta sobre a posse das colônias.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Sabe, é melhor eu mesmo cuidar disso.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Sempre tenho, de várias épocas. De qual país você quer a licença?";
		    link.l1 = "Da Inglaterra";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Da França";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Da Espanha";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Da Holanda";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Sabe, é melhor eu mesmo cuidar disso.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Período?";
		    link.l1 = "30 dias";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 dias";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 dias";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Mudei de ideia.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Então, a licença de comércio de"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" for "+sti(npchar.LicenceType)+" dias, o preço é "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Concordo.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Mudei de ideia.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "Aqui está. Não se esqueça de hastear uma bandeira amigável ao entrar no porto. E lembre-se de que a patrulha pode conferir a data da licença.";
			link.l9 = "Meu agradecimento.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Excelente! Volte quando tiver dinheiro suficiente.";
			link.l1 = "Tudo bem.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Excelente. Antes de tudo, você precisa provar sua lealdade à nação"+" por um serviço excelente. Vá até qualquer governador de"+//NationNameGenitive(sti(NPChar.nation))+" e concluir algumas das missões dele. Depois disso, ele vai te conceder uma licença.";
			link.l1 = "Me conte, "+GetAddress_FormToNPC(NPChar)+", existe alguma maneira de eu evitar essa formalidade tediosa?";
			link.l1.go = "patent_1";
			link.l2 = "Adeus, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Quer dizer um suborno!? Quer que eu faça uma licença pra você, é isso?";
			link.l1 = "Exatamente!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Não. Adeus, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Eu não tenho esse tipo de contato pra fazer isso. E não posso conseguir uma licença em branco com todos os carimbos e assinaturas.";
            link.l1 = "Que pena. Adeus."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "Certo, posso providenciar isso para você. Que tipo de licença você precisa?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Da Inglaterra";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Da França";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Da Espanha";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Da Holanda";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "É melhor eu mesmo cuidar disso.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Isto é um erro. Se você vir isso, por favor entre em contato com ALexusB";
                    link.l1 = "Parece bom para mim. Concordo com seus termos!";
                    break;
                case HOLLAND :
                    dialog.text = "A Holanda é quase uma nação pacífica. Você vai fazer muitos amigos e poucos inimigos. E a licença em si vai te custar "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Parece bom para mim. Concordo com seus termos!";
                    break;
                case FRANCE :
                    dialog.text = "Amigos e inimigos da França passarão a ser seus também. Você terá permissão para afundar navios dos inimigos deles. E a licença em si vai lhe custar "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Parece ótimo! Eu não me importo muito com quem eu sirvo! França está bom pra mim.";
                    break;
                case SPAIN :
                    dialog.text = "A Espanha tem muitos inimigos, e eles serão seus também! A Espanha é uma nação de guerreiros do mar. E a licença em si vai te custar "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Era isso que eu queria! Pegue essa quantia miserável de moedas por lutar e cumprir missões para gente importante!";
                    break;
                case ENGLAND :
                    dialog.text = "Pra ser sincero, é assim que o governador-geral inglês enche os bolsos. E a licença em si vai te custar "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Muito bem. Dê a ele o meu dinheiro sujo, que ganhei com contrabando e abordagens!";
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

			link.l2 = "Não, não é para mim.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Fico feliz que tenhamos fechado um acordo.";
			link.l1 = "Adeus, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "Certo. Vai te custar "+iDiplomatPseudoGlobal+" pesos.";
			Link.l1 = "Concordo.";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Mudei de ideia.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Muito bem, vou resolver tudo. Eles vão trabalhar com você.";
			Link.l99 = "Obrigado.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "Hm... Eu nem sei o que dizer. Claro que posso atender ao seu pedido de fazer as pazes com "+XI_ConvertString(Nations[i].Name+"Abl")+", vai custar "+FindRussianMoneyString(iDiplomatPseudoGlobal)+".";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "Acho que não tenho escolha. Fique com o meu dinheiro.";
				link.l1.go = "relation3";
			}
			link.l2 = "Não, é demais. Adeus.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Excelente! É surpreendentemente fácil lidar com você. Não se preocupe, vou resolver seu problema em 15 dias.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Seu problema está prestes a ser resolvido agora. Apenas sente-se e espere, não tem como ser mais rápido.";
			Link.l99 = "Obrigado.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "De qual colônia você quer falar sobre a posse?";
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
			Link.l99 = "Não. Nada.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony "+GetCityName(colonies[i].id)+", já pertenceu a "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", resgate para impedir novas tentativas de recaptura é "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Sim, exatamente o que eu preciso.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Não, obrigado. Não estou interessado.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Certo, o acordo está em andamento. Não haverá nenhuma tentativa de captura "+GetCityName(colonies[i].id)+" de novo.";
			Link.l2 = "Obrigado. Tenha um bom dia.";
			Link.l2.go = "exit";
			Link.l3 = "Mais uma pergunta.";
			Link.l3.go = "relation";
		break;
	}
}
