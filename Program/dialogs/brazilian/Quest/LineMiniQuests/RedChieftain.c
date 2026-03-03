void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Isto é um bug. Avise os desenvolvedores.";
			link.l1 = "Eu vou!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Como vai, cara-pálida. Vejo que você é o capitão da grande canoa. Eu sou Kanauri. Sou o chefe de Cayman – a poderosa tribo Arawak. Quero conversar com você.";
			link.l1 = "Estou ouvindo, chefe. Que problemas te trouxeram até mim?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "O que você quer de mim, seu macaco de pele vermelha? Volte para suas selvas e não me incomode com seus pedidos.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! O capitão branco não aprendeu a ser educado? Eu fiz uma oferta. Você ia ganhar um bom dinheiro, mas agora vou embora. Adeus, cara-pálida.";
			link.l1 = "Vai, desaparece...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Irmão branco, perspicaz como a coruja, astuto como a serpente. Problema chegando para o índio. Grande-grande canoa de homens brancos veio à minha aldeia. Eles levaram muitos Cayman, meu povo, colocaram na canoa deles e levaram para a Mãe de Todas as Águas...";
			link.l1 = "Espera... você está dizendo que seu povo foi escravizado por homens brancos de um navio?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Você fala a verdade, irmão branco. Sei que esses rostos-pálidos não são seus amigos. Esses homens brancos cruéis da tribo espanhola. Eles levam meu povo. Mas eu os encontro. Os espanhóis fazem os índios trabalhar do amanhecer ao anoitecer, mergulhar fundo no seio das Águas-Mães, buscar conchas cheias das lágrimas dos deuses.";
			link.l1 = "Buscar pérolas... Isso é um trabalho cruel.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Você fala a verdade, irmão branco. Sei que essas pessoas não são suas amigas. Elas são da tribo inglesa. Eles levam meu povo. Mas eu os encontro. Os ingleses fazem os índios trabalhar do amanhecer ao anoitecer, mergulhar fundo na Mãe das Águas, buscar conchas cheias das lágrimas dos deuses.";
			link.l1 = " Mergulho de pérolas... Isso é um trabalho duro.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Os índios adoecem e morrem por causa da escravidão. Os brancos não têm piedade dos índios. O chicote e a pistola são a lei do homem branco para o índio. Estou velho. Não tenho mais homens para lutar. Os Arawaks de Cayman são um povo pacífico, fomos nós que inventamos o cachimbo da paz. Peço a você, irmão branco, que use seu chicote e sua pistola contra os brancos maus, salve os índios Arawak.";
			link.l1 = "Você está me pedindo para declarar guerra? Você precisa entender, chefe, meus recursos são limitados.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Não vá para a guerra. Índio livre. Meu povo. Nós damos a você todas as lágrimas dos deuses que temos nas canoas. Mate o homem branco mau, ajude o índio, pegue as lágrimas dos deuses, venda por muito wampum. Um monte de wampum";
			link.l1 = "Ah, entendi agora. Não, Canauri, não posso te ajudar. Não posso fazer isso agora – meu navio precisa de reparos e estou sem suprimentos...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "Nesse caso, será um prazer. Vamos conversar sobre os detalhes. Onde estão os seus? Você disse que já tinha encontrado eles...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Posso esperar, irmão branco... Ficarei neste porto por mais uma lua, procurando um protetor para o meu povo. Me encontre aqui quando estiver pronto.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Você voltou, irmão branco? Vai me ajudar a punir os homens maus e salvar o índio?";
			link.l1 = "Pronto como nunca estive.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Eu ainda preciso me preparar.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Eu estarei aqui, irmão branco.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Fico muito feliz que você aceitou, irmão branco!";
			link.l1 = "Vamos falar dos detalhes, Canauri. Onde estão os seus? Você disse que já tinha encontrado eles...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "Eles estão acampados na Enseada de Carupano, perto do acampamento espanhol chamado Cumana. Todos os dias eles saem para o mar em barcos, mergulham na água, fundo, bem fundo...";
				link.l1 = "Entendi. E os espanhóis ficam de olho neles enquanto mergulham?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "Eles acampam em Cabo Perlas, perto do acampamento inglês chamado Blueweld. Todos os dias saem para o mar em barcos, mergulhando fundo, bem fundo...";
				link.l1 = "Entendi. E, claro, os ingleses estão de olho neles?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Sim, duas grandes canoas de rostos-pálidos com bastões de fogo e facas grandes. Acampamento na praia também está guardado – índio não pode escapar.";
			link.l1 = "Que tipo de navios? Consegue descrevê-los? Eram grandes? Como eram as velas?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Essa canoa é grande, mas Canauri já viu maiores. A vela da frente está bem, bem inclinada, formando três lados assim. (Ele desenha três velas latinas e uma vela trapezoidal na terra) Em cima é estreita, embaixo é larga.";
			link.l1 = "Parece e soa como uma escuna...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri não conhece essa palavra. Cara-pálida precisa ter muito cuidado se vir outra canoa – eles desembarcam o índio e esperam até que a outra canoa vá embora.";
			link.l1 = "Filhos da mãe cautelosos... como é que eu chego perto deles?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Se o irmão cara-pálida pegar uma canoa pequena, pode se aproximar da costa sem ser visto. Eu mostro o caminho. Mas traga só uma canoa pequena, senão o cachorro cara-pálida vê e põe o índio pra correr do barco pra dentro da mata...";
			link.l1 = "Entendi. Vou precisar de uma lugre ou uma escuna pequena pra essa missão. Ótimo. Uma escuna contra dois saveiros... Meu Deus... e eu achando que isso ia ser fácil!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Vamos, irmão branco? Temos menos de uma lua.";
			link.l1 = "Sim. Suba no meu navio, chefe. Vamos direto ao ponto!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Obrigado, irmão branco! Você salvou a tribo Arawak de Cayman! Temos uma grande dívida com você. O caminho está livre dos cães de cara-pálida e os índios podem correr livres pela selva. Damos a você todas as lágrimas dos deuses que restaram nos barcos.";
			link.l1 = "Bem, vamos ver do que você é capaz...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("Fico feliz que as lágrimas dos deuses sejam suas, irmão dos Arawak!","Índio agradece, bravo rosto-pálido!","Fique com a nossa pesca, irmão branco!");
			link.l1 = LinkRandPhrase("Fico feliz em ajudar você!","Obrigado, irmão de pele vermelha!","Ótimo!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri agradece de novo, irmão de pele clara! Você salvou todas as canoas com os índios! Para Canauri, é muito importante salvar cada canoa, porque você também salvou o neto de Canauri, que os malditos de pele clara levaram para a escravidão. Quando era criança, meu neto adorava nadar, e Canauri deu a ele este amuleto encantado para que não se afogasse. Agora o neto não quer mais nadar e me devolveu o amuleto para que eu possa entregá-lo a você, irmão de pele clara. Espero que as lágrimas dos deuses e este presente sejam uma recompensa justa pela vida de um aruaque. Agora nos despedimos – é hora de voltarmos para nossa aldeia.";
				link.l1 = "Boa sorte, Cunauri! Fico feliz que seu neto tenha sobrevivido! Espero que esse mal nunca mais recaia sobre você!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri agradece de novo, irmão de rosto pálido! Espero que as lágrimas dos deuses sejam recompensa suficiente pelas vidas dos índios. Agora adeus, vamos para nossa aldeia.";
				link.l1 = "Boa sorte, Cunauri! Nunca mais caia na escravidão!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
