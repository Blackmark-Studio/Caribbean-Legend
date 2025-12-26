// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Boa tarde. Você deve ser "+GetFullName(pchar)+"?";
			link.l1 = "Você está certo, Monsieur LeCroix. Capitão "+GetFullName(pchar)+" às suas ordens. Fadey, o Moscovita, me recomendou você...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Sim, sim. Meu caro amigo Fadey me contou tudo sobre você e sua situação. Soube que era você assim que o vi na porta. Diga-me, capitão, que tipo de navio você comanda?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah... No momento, eu não tenho um navio, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Eu tenho um "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+", o nome dela é "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Ora, que tipo de capitão é você então, se não tem um navio? Me desculpe, monsieur, mas nesse caso não tenho nenhum trabalho para lhe oferecer. Tudo de bom, mande lembranças ao Fadey!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Bem, isso simplesmente não serve. Isso não é um navio, senhor, é um barquinho! Lamento, monsieur, você não se encaixa no papel. Dê lembranças ao Fadey por mim, tenha um bom dia!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Você e eu já discutimos tudo, monsieur. Não foi?";
			link.l1 = "Sim, Monsieur LeCroix... Estou a caminho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Excelente. Nesse caso, você combina comigo. Está pronto para zarpar imediatamente?";
			link.l1 = "Sim, monsieur, estou pronto. O que devo fazer?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Você deve entregar um pequeno lote de pólvora e bombas em Port-au-Prince, na Hispaniola francesa. O comandante está esperando por isso há algum tempo, então não perca tempo, você tem cerca de dez dias restantes\nRespeitosamente "+GetFullName(sld)+" vou cuidar de entregar e carregar isso no seu navio. O comandante vai te pagar cinco mil peças de oito pelo serviço.";
			link.l1 = "E esse é todo o trabalho?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "De jeito nenhum, monsieur. O comandante vai explicar o trabalho de verdade quando você trouxer as munições. Essa carga é só um pequeno aperitivo do que te espera. Mas não se preocupe, se fizer o serviço direitinho, vai ganhar um bom dinheiro.";
			link.l1 = "Você tem toda a minha atenção, monsieur. Meu navio está pronto para receber a carga a bordo.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Então não vamos perder tempo, capitão! Vá para o seu navio e prepare-se para zarpar.";
			link.l1 = "Estou indo!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Em que posso ajudá-lo, senhor?";
			link.l1 = "Boa tarde, capitão. Você é Florian Shoke, presumo?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Sou eu. E você é do navio de correio vindo de Port-au-Prince, se não me engano?";
			link.l1 = "Sim, tenho quinze canhões para você. O prazo foi apertado, quase não consegui...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. O senhor tem um senso de humor peculiar! Por algum motivo, não vejo quinze canhões sendo descarregados do seu navio...";
				link.l1 = "Veja bem, tivemos um vazamento e tivemos que jogar parte da carga ao mar...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Bom te ver, capitão?..";
				link.l1 = ""+GetFullName(pchar)+". Capitão "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Prazer em conhecê-lo. Vamos direto ao assunto e embarcar esses canhões. Isso não vai ser fácil, então vou precisar da ajuda dos seus homens.";
			link.l1 = "Vamos dar um jeito. Ei você, prepare o sistema de roldanas no vergueiro!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Seu idiota! Se você não consegue nem lidar com uma tarefa simples dessas, vai acabar afundando na próxima tempestade. Volte para o seu navio, capitão, e faça algo em que seja melhor, como entregar flores para damas da nobreza. Melhor ainda, volte para a Europa e deixe o Novo Mundo para homens de verdade. Tenha um bom dia, senhor!";
			link.l1 = "Mas...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Ufa, isso deu trabalho e me deixou com sede! Obrigado pelo serviço, capitão! Aqui está sua recompensa, duzentos dobrões.";
			link.l1 = "Obrigado!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			dialog.text = "Mas isso não é tudo, capitão. Gostaria de ganhar mais 75 escudos de ouro duplos?";
			link.l1 = "Parece interessante, mas depende do que o senhor vai me pedir em troca.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Não vou mentir, é perigoso. Como você talvez já saiba, estou à espreita de um galeão espanhol carregado de mercadorias valiosas. O navio está no estaleiro para reparos. Segundo minhas fontes, ele deveria ter partido ontem, mas isso não aconteceu\nAlém disso, meu informante em Portobelo não apareceu no ponto de encontro para me trazer as novidades que eu esperava. Suspeito que os espanhóis o prenderam. Eu te pago para se infiltrar em Portobelo e descobrir duas coisas: por que o galeão ainda está lá e o que aconteceu com meu agente. Topa?";
			link.l1 = "Receio não ter o preparo adequado para uma operação dessas. Sou um cavalheiro, não um espião. Posso acabar me metendo em encrenca e não vou conseguir te ajudar.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Parece perigoso, mas lucrativo. Vou arriscar. Qual é o nome do seu homem, e como se chama o galeão?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Bem, você não se acha? Eu entendo você. Então adeus, capitão, e mais uma vez obrigado pela sua ajuda!";
			link.l1 = "Tudo de bom, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Então, preste atenção. O nome do meu homem é Sylvan Laforet, mas em Portobello ele atende por Jaime Silicio, um comerciante. O galeão se chama 'Alcantara'. Recomendo que você entre na cidade à noite, pela selva. Os guardas de Portobello andam muito desconfiados ultimamente, sem falar que o desaparecimento do Sylvan não é um bom sinal de que ele esteja vivo e bem. Você tem dois dias antes que eu precise sair daqui, antes que as patrulhas espanholas nos encontrem. Boa sorte, monsieur!";
			link.l1 = "Até logo, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Já conversamos sobre tudo, capitão, não foi?";
			link.l1 = "Sim. Estou a caminho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Como estão as coisas, capitão? O que conseguiu descobrir?";
			link.l1 = "As coisas estão indo mal, Monsieur Shoke. Eu não sou um bom espião, eles me descobriram muito rápido. Tive que fugir da cidade depois de lutar com alguns guardas. A única coisa que consegui descobrir é que seu homem, Sylvan Laforet, foi preso e está na cadeia.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Maldição! Isso não é nada bom... Você descobriu alguma coisa sobre o galeão?";
			link.l1 = "Não, não fiz isso.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Droga. Eu realmente preciso de informações sobre isso. Mas esse prêmio é grande demais pra desistir! De qualquer forma, vou tentar mandar outro informante pra lá... Capitão, peço que não me deixe por enquanto. Posso precisar da sua ajuda. Você pode esperar mais um dia enquanto eu tento descobrir algo sobre o Alacantara?";
			link.l1 = "Claro, eu vou esperar! Quero compensar aquele fracasso.";
			link.l1.go = "florian_9";
			link.l2 = "Acho que não. Pelo visto, não sou bom nesses jogos. Vou pra casa.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Bem, essa é sua escolha. Tudo de bom, Capitão.";
			link.l1 = "Adeus, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Como estão as coisas, capitão? Conseguiu descobrir algo?";
			link.l1 = "As coisas não vão nada bem, Monsieur Shoke. Eu não sou um grande espião, me descobriram rapidinho. A única coisa que consegui descobrir é que seu homem, Sylvain Laforet, foi preso e está sendo mantido em algum lugar.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Então vá para o seu navio, capitão. Amanhã, mais ou menos nesse mesmo horário, ou um pouco mais tarde, você vai precisar me visitar. Talvez até lá eu já tenha descoberto alguma coisa. Não pise em terra, espere por mim no seu navio!";
			link.l1 = "Certo. Vou fazer isso.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "E capitão, pegue esta bolsa. Seus esforços não foram totalmente em vão, afinal. Pelo menos agora sabemos o que aconteceu com o pobre velho Sylvan...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Capitão, no momento não tenho novidades. Ainda estamos esperando...";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Como estão as coisas, capitão? O que conseguiu descobrir?";
			link.l1 = "Está feito. Seu homem, Sylvain Laforet, foi preso e está na cadeia. Acabou para ele.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Maldição! Que horror... Você descobriu alguma coisa sobre o galeão?";
			link.l1 = "Sim. Ela já está sendo preparada para zarpar faz um tempo, mas o governador de Portobello pretende mantê-la no cais. No momento, ele está esperando uma barca chamada 'Puebla' chegar de Cartagena com uma carga de pólvora para a 'Alcantara'. Segundo um marinheiro do galeão, eles não têm pólvora suficiente e o governador teme os piratas.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Que interessante!";
			link.l1 = "Mas se Puebla não chegar em três dias, então o Alacantara vai parar de esperar e zarpar.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Excelente trabalho, capitão "+GetFullName(pchar)+"! Estou muito satisfeito! Aqui, pegue sua recompensa. Você realmente merece!";
			link.l1 = "Obrigado! Você tem mais alguma tarefa para mim?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 75);
			dialog.text = "Você está lendo meus pensamentos, "+GetFullName(pchar)+"! Yes, damn it! Since Alacantara is low on gunpowder, I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run out before ours, haha!\nYou should make sure that the supply barkentine Puebla never reaches Portobello. I can't sail close to the shore; patrols will notice my frigate easily and drive me off before I can intercept Alacantara\nYou can deal with Puebla on your own. Find her and get rid of her. Sink her or take her as a prize, I don't care. Just prevent her from getting here!\nIf you succeed, then go to Guadeloupe and see Gerard LeCroix. I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Fechado! Vou partir agora mesmo para interceptar o Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a moment, Monsieur Choquet. The fact is, I'm still... let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate; you obviously have more than one naval battle behind you. If it's not too much trouble, could you... how should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Que bom que você chegou, capitão. Acabei de receber informações do meu espião e tenho uma missão importante para você.";
			link.l1 = "Pode falar, estou ouvindo.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "The Alacantara is ready to set sail, but the galleon's captain is waiting for the barkentine 'Puebla' to arrive from Cartagena loaded with ammunition. Apparently, the Alacantara doesn't have enough gunpowder, so the Spanish are not ready to set sail yet. But the captain's patience has its limits, and if Puebla doesn't come in three days, then the galleon will leave Portobello without her.\nThe Alacantara is low on gunpowder; I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run out before ours. Your objective is to intercept the Puebla and destroy her. Sink her or take her as a prize, I don't care. Just prevent that resupply barkentine from getting here!\nIf you succeed, then go to Guadeloupe and see Gerard LeCroix. I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Fechado! Vou partir agora mesmo para interceptar Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a moment, Monsieur Choquet. The fact is, I'm still... Let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate; you obviously have more than one naval battle behind you. If it's not too much trouble, could you... How should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Quer que eu lhe dê uma aula sobre táticas de combate naval? Com prazer, capitão! Ainda mais porque é do meu próprio interesse: quero ter certeza de que você vai conseguir interceptar o 'Puebla'.";
			link.l1 = "Não, não foi isso que eu quis dizer. Tudo bem, esquece: tenho certeza de que não vou ter problema nenhum em interceptar uma barquentina.";
			link.l1.go = "florian_19";
			link.l2 = "Sim, era exatamente isso que eu queria dizer. Tenho certeza de que esse novo conhecimento não vai me fazer mal.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Então, a primeira coisa que você precisa lembrar é que metade da batalha é ganha ou perdida antes mesmo de começar. Muito depende de quão preparados você e seu navio estão para isso.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Primeiro, certifique-se de que seu navio está em boas condições. Se houver buracos no casco, não será difícil para o inimigo mandar você para o fundo. E se você tiver trapos pendurados no lugar das velas, isso vai limitar bastante sua mobilidade. O inimigo pode facilmente fugir se o equilíbrio de forças não estiver a seu favor ou, pior ainda, alcançar você e forçar uma batalha desfavorável – ou até mesmo abordar seu navio imediatamente. Além disso, com as velas rasgadas, vai ser difícil conquistar a vantagem do vento – ou seja, conseguir ficar a barlavento do adversário, que é onde você quer estar.";
			link.l1 = "Vantagem do vento, entendi. Mais alguma coisa?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Garanta que você tenha homens suficientes. Até o navio mais poderoso, com canhões de 42 libras, se torna inútil se só tiver um artilheiro correndo para recarregar três canhões e ninguém para cuidar das velas. No geral, eu simplesmente abordaria um navio assim na hora e tomaria posse dele.";
			link.l1 = "Entendi, homens suficientes.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Além disso, fique de olho nos seus canhões: com o tempo, eles se desgastam e podem explodir. O estado dos canos piora, e se seus canhões começarem a explodir no meio de uma batalha, isso pode acabar muito mal para você. Eu mesmo não tive sorte nenhuma: o lote de canhões com que naveguei tinha vários defeitos de fundição. Se você não tivesse trazido uma reposição a tempo, eu teria simplesmente desistido da operação, já que o Militant ficaria muito atrás do Alcântara em poder de fogo. Ferramentas precisam ser trocadas na hora certa.";
			link.l1 = "Agora eu entendo por que isso era tão importante!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Além dos canhões, fique de olho na quantidade de munição. Alcântara vai cair nas minhas mãos por causa disso. Se ela estiver com pouca pólvora, não vai conseguir sustentar uma batalha longa – vai precisar partir logo para o combate corpo a corpo. E é aí que eu vou aproveitar: minha fragata é mais rápida, um galeão pesado não vai conseguir fugir dela. Mas eu também não preciso chegar tão perto: vou forçar um duelo de artilharia à distância e, quando a pólvora da Alcântara acabar, vou me aproximar, varrer o convés com bala de canhão e abordar o navio.";
			link.l1 = "Situação desesperadora...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Exatamente. Fique de olho na sua pólvora e munição. Se acabar com as balas sólidas, provavelmente não conseguirá afundar um navio inimigo. Se ficar sem balas de canhão de uva, não terá chance de abordar se estiver em desvantagem numérica. Se não tiver balas encadeadas ou knipples, não conseguirá alcançar o inimigo nem fugir dele se ele for mais rápido. Todos os tipos de munição são importantes.";
			link.l1 = "Instrutivo, obrigado.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "E, finalmente, dependendo do tipo e do tamanho do seu navio e do navio inimigo, use as táticas apropriadas. No mar, há sempre um equilíbrio entre poder de fogo e velocidade. Num navio grande e lento, não faz sentido perseguir uma brigue ou uma corveta para abordar — você nunca vai alcançar sem antes enfraquecê-la com balas de corrente. Nesses casos, é mais sensato destruí-la à distância e depois vasculhar os destroços. Se ainda assim precisar abordar um navio desses, é melhor usar um navio rápido e manobrável.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Ao mesmo tempo, não tente enfrentar um navio de linha de igual para igual com uma brigue. Uma salva de um monstro desses pode despedaçar o casco de embarcações menores em estilhaços. Aproveite sua vantagem em velocidade e manobrabilidade, derrube os mastros e o cordame, depois se aproxime e varra o convés com bala de canhão, se ainda precisar abordar. Se precisar afundá-lo... não será uma tarefa fácil, mas é possível. Você pode abordar e incendiar o paiol de pólvora, mas nunca é vergonhoso bater em retirada. Um bom capitão salva seu navio e sua tripulação de uma morte certa, em vez de se entregar ao heroísmo desnecessário. Lembre-se: discrição e prudência muitas vezes valem mais do que coragem cega.";
			link.l1 = "Muito obrigado, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Fico feliz em ajudar, capitão. Espero que esse conhecimento lhe seja útil no futuro.";
			link.l1 = "Tenho certeza de que isso vai ajudar. Vamos interceptar o 'Puebla'!";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Esse sotaque seu é bem diferente, señor. Ou devo dizer 'monsieur'? Quer ver o Jaime Silicio? Talvez vocês possam dividir a mesma cela. Levem ele, rapazes!";
			link.l1 = "Bem, se não gosta do meu sotaque, talvez eu possa te apresentar à esgrima francesa!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
