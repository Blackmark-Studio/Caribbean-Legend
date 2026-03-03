// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já trouxe essa questão pela terceira vez hoje...","Olha, se você não tem nada a me dizer sobre assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Bom dia. Gostaria de saber onde está o Capitão François Gontier. Tenho um assunto importante.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Sou um comerciante, vim de Caracas, e seu colega da autoridade portuária local me pediu para entregar uma correspondência para você ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Sim, estou aqui pelo pagamento.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Um assunto importante, você diz? Vamos ver. Bem...  Francois Gontier, na corveta '"+pchar.questTemp.Slavetrader.ShipName+"'... De acordo com minhas anotações, o senhor Gontier estava indo para a Jamaica.";
			link.l1 = "Muito obrigado! Você foi de grande ajuda!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ah, então, finalmente! Você disse que é um comerciante? De novo estão tentando economizar nos mensageiros e adiando o envio até o último maldito... É, claro! É isso mesmo. E como é que eu vou equipar o esquadrão com eles nesse prazo?...";
			link.l1 = "Parece irresponsável...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "É uma forma de dizer! Bem, fazer o quê. A gente se encontra por aí... Estou falando sozinho, não liga. Escuta, por acaso você vai voltar?";
			link.l1 = "Bem, na verdade, eu ia vender mercadorias aqui e depois – sim, voltar para Caracas ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Ótimo! Agora vou escrever uma resposta para eles e pedir que você a entregue de volta. Então... entregue, por favor, dentro de dez dias, senão eles não terão tempo de fazer nada... E diga seu nome.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Meu nome é "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Meu nome é Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Espere um minuto... Anotado. Aqui está. Lembre-se: dez dias! Enquanto isso, vou analisar com mais atenção o que você me trouxe.";
			link.l1 = "Sim, eu me lembro. Adeus!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Espere um minuto... Eu não entendi... Mais uma vez, qual é mesmo o seu nome?";
			link.l1 = "Eu?.. Bem... Por que isso é tão importante?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "É muito importante! Diz aqui... Então... "+n+" "+month+"... Não, não é isso... 12, 50, 69, 55... Mas onde está... Ah, aqui está! A carta deve ser entregue pelo Capitão "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". E você disse que seu nome é... "+GetFullName(pchar)+"?";
			link.l1 = "Deve ter havido algum engano...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Não, não pode haver engano. Me devolva a carta que eu te dei. Preciso entender o que está acontecendo!";
			link.l1 = "Vamos lá... Eu vou entregar, vai dar tudo certo.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Não! Devolva a carta para mim! Guardas!!!";
			link.l1 = "Ah, quer fazer do jeito difícil, é?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			LICENSE_AddViolation();
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Espere um instante... Pronto. Vou colocar seu nome na carta de resposta. Aqui está. Lembre-se: você tem dez dias! Enquanto isso, vou ler com mais atenção o que você me trouxe.";
			link.l1 = "Sim, eu me lembro. Adeus!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Pagamento?..";
			link.l1 = "Em Caracas, seu colega me disse que você pagaria pela entrega da carta.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Não, olha, eles são completamente loucos lá! Agora eu que tenho que pagar por eles!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "E quanto eles te prometeram?";
			link.l1 = "Cinco mil pesos.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Dez mil pesos.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Aparentemente, eles decidiram viver lá às minhas custas... Não só se recusam a gastar dinheiro com mensageiros, confiando esse tipo de coisa a navios mercantes de passagem, como ainda me deixam com as despesas! Vou escrever uma reclamação contra eles para Havana!";
			link.l1 = "Eu entendo sua indignação, senhor, mas o que devo fazer?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Aparentemente, decidiram viver lá às minhas custas... Não só se recusam a gastar com mensageiros, confiando esse tipo de coisa a navios mercantes de passagem, como ainda me deixam com as despesas! Vou escrever uma reclamação contra eles para Havana!";
			link.l1 = "Entendo sua indignação, senhor, mas o que devo fazer?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, você não tem culpa da ganância dos oficiais da Nova Espanha em Caracas. Mas eu simplesmente não tenho esse dinheiro comigo agora. E os fundos só devem chegar amanhã... Espere aqui, por favor, vou até o agiota agora – e volto já.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Desculpe pela espera. Aqui estão seus "+makeint(pchar.questTemp.SharkGoldFleet)+" peças de oito. E, neste caso, eles mesmos vão pagar pela resposta em Caracas. Diga a eles que fui eu quem mandou.";
			link.l1 = "Certo, vou repassar. Obrigado, e boa sorte!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
