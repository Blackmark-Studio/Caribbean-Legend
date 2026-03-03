// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Você tem coragem de aparecer no gabinete do governador-geral?! Você é mesmo louco...","Como esses preguiçosos deixaram um inimigo invadir minha residência? Isso me escapa completamente...","Com certeza, meus guardas não valem uma moeda se qualquer vagabundo pode andar solto na minha residência..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("desgraçado","fedelho")+"?! Meus soldados já estão no seu encalço, "+GetSexPhrase("pirata imundo","fedelho")+"!",""+GetSexPhrase("Imundo","Imundo")+" Assassino, saia da minha casa imediatamente! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("canalha","canalha")+"Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Soldados não valem nada...","Você nunca vai me pegar."),RandPhraseSimple("Cala a boca, camarada, ou eu arranco essa sua língua imunda!","Estou te avisando, camarada: fica quieto ou eu corto sua cabeça e jogo ela por aquela porta pros seus cães de guarda..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ouvi dizer que você foi bem insistente ao pedir uma audiência. Meu nome é "+GetFullName(npchar)+". Eu sou o governador-geral das colônias de "+NationNameGenitive(sti(NPChar.nation))+", deputado da Coroa de "+NationKingsName(npchar)+" nessas águas. Agora, por favor, seja gentil e me diga, qual é o propósito da sua visita, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Meu nome é "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Ah, é você de novo? Então, o que deseja do governador-geral de "+NationNameGenitive(sti(NPChar.nation))+" desta vez?","E mais uma vez, você está me distraindo de assuntos importantes do Estado? O que você quer, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Quero conversar com você sobre trabalhar em nome da Coroa de "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Preciso falar com você sobre um assunto importante.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Vim a convite para participar da regata. Aqui está meu convite.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Me desculpe, mas tenho alguns assuntos para resolver.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "O que te traz aqui para me distrair de assuntos importantes do Estado?";
			link.l1 = "Queria conversar com você sobre trabalhar em nome da Coroa de "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Eu ia falar com você sobre um assunto importante.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Vim aqui para participar da regata. Aqui está meu convite.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "É só uma visita de cortesia, nada mais. "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Nesse caso, peço que saia do meu escritório e pare de me distrair do meu trabalho.";
			link.l1 = "Sim, sim, claro. Desculpe incomodar você.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Se você está procurando trabalho, fale com os governadores das colônias. Eles costumam precisar de capitães inteligentes e corajosos.";
			link.l1 = "Vou lembrar disso. Obrigado.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, que ótimo, fico feliz em vê-lo, capitão! Chegou na hora certa – a regata vai começar em poucos dias. Leu as regras da regata na carta que o mensageiro deve ter lhe entregue?";
			link.l1 = "Sim, senhor, eu fiz.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "E você já preparou 50.000 pesos – sua taxa de entrada, que será destinada ao prêmio?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Sim, claro. Por favor, aceite minha taxa.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Estou meio sem dinheiro no momento. Mas com certeza vou trazer assim que puder.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very well. If you win, your money will be returned to you fivefold. Now, you should know how not to break the rules of the regatta.\nDiscuss the details with Henry Stevenson; he should be in the residence's room. Meet with him, he will explain everything.";
			link.l1 = "Certo. Vou fazer como você disse.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Tudo bem, mas por favor não demore muito, capitão. A regata vai começar em breve.";
			link.l1 = "Entendi. Vou tentar trazer o dinheiro antes da regata começar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "E aqui temos o vencedor da regata! Olá, Capitão "+GetFullName(pchar)+"! Permita-me parabenizá-lo por esse sucesso tão merecido! Os vencedores da regata sempre fazem sucesso nas colônias inglesas, e com toda razão.";
			link.l1 = "Obrigado, senhor!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Agora vamos passar para a parte mais agradável para você - a cerimônia de premiação. O primeiro prêmio é de 250.000 pesos. Aqui está!";
			link.l1 = "Obrigado!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Além disso, você está apto a receber um conjunto de prêmios valiosos: "+sAdd+". Agora é tudo seu.";
			link.l1 = "Estou muito feliz, senhor! Sinceramente, eu não poderia esperar por isso.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Em nome de todas as colônias inglesas, fico feliz em agradecer por participar da regata e mais uma vez parabenizo você pela vitória! Se fez uma aposta, agora é a hora perfeita para procurar Sir Henry Stevenson e receber seus ganhos, caso ainda não tenha feito isso. Boa sorte para você, capitão!";
			link.l1 = "Muito obrigado por suas palavras gentis, senhor! Permita-me também agradecer por me dar a oportunidade de participar de um evento tão grandioso. Agora, por favor, permita-me despedir-me e retirar-me.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
