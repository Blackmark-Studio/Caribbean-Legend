void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Canalha! Que surpresa para você!";
    		link.l1 = "O quê?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! Aqui não tem escravos! Você veio por causa deles, não foi?";
			link.l1 = "Merda. E eu aqui me perguntando por que diabos tinha tanto soldado numa pinassa mercante... Era uma armadilha!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Sim, desgraçado, é uma armadilha. Eu não sou um comerciante, sou um oficial militar! Mesmo tendo vencido a luta, você não vai escapar do julgamento!";
			link.l1 = "E por que isso? Vou acabar com você agora, afundar seu navio, e ninguém vai saber de nada.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Você está enganado. Seus negócios com aquele banqueiro foram descobertos. Em breve, o governador-geral saberá do seu pequeno esquema e você não vai escapar da forca. Mas vou te fazer um favor acabando com você aqui e agora!";
			link.l1 = "Tenta, seu cachorro do governador!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", em nome da lei, você está preso! Entregue suas armas e venha conosco!";
			link.l1 = "O que está acontecendo, oficial? Render-me? Com que direito?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Não tente se fazer de bobo, capitão! Seus negócios sujos foram descobertos. E pelo massacre que você cometeu e pelo navio de "+NationNameGenitive(sti(npchar.nation))+" que você afundou, vamos ver você enforcado!";
			link.l1 = "Bom, já que você falou desse jeito... Vai se foder!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Ei, o que você está fazendo aqui?!";
    		link.l1 = "Por que tanta grosseria, bom senhor? Aquele rato do Gontier está escondido por aqui, hein?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Não, ele não está! Saia!";
			link.l1 = "Parece que você está mentindo. Vou vasculhar a casa e conferir...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Vai se foder! François! Corre! Gente, me ajuda!";
			link.l1 = "Merda!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Oh! Por favor, não me machuque!";
    		link.l1 = "O quê...? Onde está Francois Gontier? Responda, sua vadia imunda, ou vai acabar igual àqueles seus comparsas!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Não, não, eu conto tudo! Ele pulou pela janela e correu de volta para o navio dele.";
    		link.l1 = "Que navio? Eu sei que não tem nenhum navio dele no porto. Não minta pra mim, garota, ou as coisas vão piorar...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Eu não estou mentindo, eu juro! Ele disse que desembarcou numa ilha pequena e chegou aqui num bote... Ele deve estar lá! Não me machuque!";
    		link.l1 = "Certo, parece que você está dizendo a verdade. Fique aqui e fique quieto. E tente fazer amigos de um jeito mais esperto da próxima vez. Mas, sabe, eu vejo nos seus olhos, e eles me dizem que você não tem juízo.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Tenha piedade! Misericórdia! Nós nos rendemos!";
    		link.l1 = "Ah, é mesmo? Vai pro porão de carga agora! Eu atiro em quem tentar bancar o esperto!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Ora, ora... O que temos aqui? Você não sabe que negociar mercadorias com pessoas não autorizadas, ou entre elas, é proibido na nossa colônia?";
			link.l1 = "É mesmo, oficial? Para ser sincero, é a primeira vez que ouço falar disso. Esse decreto foi aprovado há pouco tempo, não é?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "O quê, negociando "+GetGoodsNameAlt(iCGood)+"? Eu não vejo nenhum "+GetGoodsNameAlt(iCGood)+" por aqui, oficial. Só vejo essas moedas brilhantes... E ele vê o mesmo. Por que você e seus soldados não dão uma olhada nas nossas moedas também?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Você não sabia, né? Hmm... parece que está dizendo a verdade. Mas, ainda assim, você violou a lei. Não vou te prender, mas preciso multá-lo. E quanto à carga... vamos conversar sobre isso com o outro participante do acordo.";
				link.l1 = "E quanto é essa multa?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Não se faça de bobo, capitão! Todo mundo já sabe disso faz tempo, aliás. Estou prendendo vocês dois por contrabando, e a carga será confiscada.";
				link.l1 = "Eu não gosto de masmorras, oficial. Prefiro o mar aberto... e é pra lá que eu vou agora. Mas parece que só vou conseguir passar por cima do seu cadáver.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Não tenho escolha a não ser me render. Mas juro que eu realmente não sabia de nada!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Agora sim, estamos falando... Vamos ver suas moedas... Se não me engano, ouvi um número bem específico - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+" . Já que agora temos três participantes, gostaria de "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Isso é de você, e o mesmo do seu amigo.";
				link.l1 = "Certamente, oficial. Aqui estão minhas moedas reluzentes, ou melhor, suas moedas reluzentes – você só as deixou cair na praia por engano... E não há "+GetGoodsNameAlt(iCGood)+" aqui, ha-ha, como eu te disse.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Opa! Você é ganancioso demais, oficial. Sua mãe não te ensinou que a ganância não leva a nada? Acho que sairia mais barato resolver isso com a minha espada.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Está brincando, capitão? Vai tentar me subornar? Você está preso! Agarrem ele!";
				link.l1 = "Bem, se você não quer dar uma olhada no meu dinheiro, então dê uma olhada na minha espada!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Não tenho escolha a não ser me render. Mas juro que eu realmente não sabia de nada!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Sim, parece que você está certo... Nada de interessante aqui além de alguns cavalheiros e minhas moedas reluzentes. Você está livre para ir, capitão, e nós teremos uma conversa com seu parceiro.";
			link.l1 = "Até mais, oficial. Não machuque ele.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Agradeça ao meu bom humor.";
			link.l1 = "Obrigado, oficial. Eu realmente não fazia ideia... Aqui, estou pronto para pagar minha multa.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Imagino que você também não seja tão honesto assim, oficial. Sua multa é alta demais. Acho que vou ajudar esta colônia livrando-a da sua presença.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Certo. Pode ir agora. E aconselho que estude as leis locais para evitar situações como esta no futuro. Vá, precisamos lidar com o segundo participante desta negociação, ele sabia de tudo, com certeza.";
			link.l1 = "Bem, nesse caso, tenha um bom dia, oficial.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "O comandante vai lidar com você. Siga-me!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Bom dia. Precisa de alguma coisa?";
			link.l1 = "Sim, parceiro. Imagino que você seja o meu contato. Foi você quem roubou "+pchar.GenQuest.Device.Shipyarder.Type+"  do estaleiro local? Tudo indica que foi você, então não adianta discutir.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Eu imploro, meu senhor! Sim, eu roubei essa coisa estranha do estaleiro. Mas não consegui vender, ninguém quer um objeto desses. Então me livrei dele. Poupe-me, bom senhor, culpe minha fome, não a mim... Eu jamais teria coragem de roubar se não fosse por isso!";
					link.l1 = "Isso é um problema... E eu também não preciso de você. Preciso encontrar aquele "+pchar.GenQuest.Device.Shipyarder.Type+". Me diga, onde você jogou fora?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Eu imploro, meu senhor! Sim, eu roubei essa coisa estranha do estaleiro. Mas não consegui vender, ninguém quer um objeto desses. Eu te dou. Aqui, pegue, só não me machuque e não chame os soldados!";
					link.l1 = "Certo, você pode viver, bandido. Não preciso da sua pele, preciso desse instrumento. Entregue-o agora mesmo e suma daqui!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "O que você quer dizer? O que é "+pchar.GenQuest.Device.Shipyarder.Type+"? Não entendi!";
					link.l1 = "Você vai me entregar isso quando eu revistar você ou o seu cadáver! Me dê isso agora!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... O que é isso "+pchar.GenQuest.Device.Shipyarder.Type+"? Eu... e o que é isso?";
					link.l1 = "Não tente bancar o esperto ou fugir, eu vou te pegar de qualquer jeito. Só deixa eu revistar seus bolsos...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Logo atrás dos portões da cidade, não muito longe da selva. Por favor, senhor! Se o senhor realmente precisa disso, pode ir buscar sozinho. Deve estar lá ainda, tenho certeza.";
			link.l1 = "Eu deveria obrigar você a encontrar isso e trazer para mim, mas temo que acabaria gastando mais tempo procurando por você do que pelo "+pchar.GenQuest.Device.Shipyarder.Type+". Eu mesmo vou fazer isso. Mas vou te encontrar se estiver mentindo para mim!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Aqui, pegue. Obrigado, senhor!";
			link.l1 = "Bem, era isso que eu estava procurando... ha! Agora você está livre para ir. Vá. E tome mais cuidado da próxima vez.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Escuta, você está falando deste instrumento? Ele é meu e eu não roubei! E não vou te dar de graça. Se quiser, pague. "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Tudo bem. Eu vou te pagar. Aqui estão suas moedas, agora me entregue o instrumento!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Ah, é mesmo? Você achou mesmo que eu confiaria em você, ladrão miserável? Entregue o "+pchar.GenQuest.Device.Shipyarder.Type+" agora ou vou chamar os guardas, assim podemos ir juntos ao estaleiro e decidir de quem é realmente este instrumento.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Você é burro, ou o quê? Escuta aqui, desgraçado, você tem duas opções: ou me entrega o "+pchar.GenQuest.Device.Shipyarder.Type+" ou eu te esfaqueio e pego o instrumento do seu cadáver!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Bom negócio, capitão! Imagino que todos nós vamos receber nossa parte dos lucros, he-he... pode pegar.";
			link.l1 = "Chega de conversa, ladrão! Não pense que me enganou, só quero resolver isso em paz e sem mais problemas. Essas moedas não vão te servir de nada mesmo. Cai fora!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Não! Não chame os guardas! Eu... eu te dou esse maldito instrumento. Aqui, pega!";
				link.l1 = "Agora sim, bem melhor! Cai fora! Ou vai acabar pendurado na forca, é só questão de tempo.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Que guardas, capitão? Só estamos você e eu aqui. Você está discutindo demais, então vou ter que te acalmar... com a minha lâmina.";
				link.l1 = "Você ousa me ameaçar, seu verme?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah! Socorro! Assassino!";
				link.l1 = "Pare aí, cachorro!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Bem, vamos ver quem vai apunhalar quem, capitão!";
				link.l1 = "Você ousa me ameaçar, verme?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Procurando? Por favor, bom senhor!";
			link.l1 = "Agora escute, ou você entrega pacificamente o que acabou de roubar do estaleiro, ou eu vou te levar direto para o gabinete do comandante. De qualquer jeito, você vai me entregar, mas antes vão queimar seus calcanhares com ferro em brasa. Talvez até te enforquem depois. A escolha é sua.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Me devolva o que você roubou agora, seu desgraçado, ou eu acabo com você aqui mesmo!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Bem, você vai ter que me pegar primeiro se quiser me levar até o gabinete do comandante ...";
				link.l1 = "Pare aí, seu cachorro!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Não, não me leve até o gabinete do comandante! Eu mesmo te dou! Aqui, pega, é isso que você está procurando, não é? Ninguém compraria isso mesmo...";
				link.l1 = "Ah, acho que posso te levar até o forte mesmo assim... Tá bom, me dá a ferramenta e vai embora!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Ai! Não me machuque, eu te dou tudo o que tenho! Aqui, pode pegar!";
			link.l1 = "Agora sim, está falando direito! Cai fora, se eu te vir de novo nesta cidade, vou te entregar para o comandante. Adeus!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Pare aí mesmo, camarada! Precisamos de algo que você está carregando. Entregue, e depois siga seu caminho.";
			link.l1 = "O que é essa coisa de que você está falando?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Esses vadios de rua andam insolentes demais ultimamente... Preparem-se, canalhas!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Não se faça de idiota! Entregue o pacote e você vai sair vivo. Caso contrário... vamos arrancá-lo do seu cadáver!";
			link.l1 = "As chances estão do seu lado... levem, seus desgraçados, não tenho escolha.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Bem, pode tentar!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Cuidado com o que fala, camarada... Foi esperto da sua parte não arriscar a sorte. O fim teria sido o mesmo, ha-ha! Vai viver mais um pouco... Até mais.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Espere, "+GetAddress_Form(NPChar)+", não vá embora assim. Tenho um trabalho para você.";
			link.l1 = "Que assunto? Eu não te conheço.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Eu conheço você, capitão. Agora, direto ao assunto. Você acabou de receber "+pchar.questTemp.WPU.Current.Add+" em "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Não tente negar, sabemos disso com certeza – afinal, estamos procurando por esse documento há vários dias.";
			link.l1 = "Agora entendi. E daí?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Me entregue o pacote e nosso breve encontro termina aqui. Não tente bancar o herói, capitão, viemos buscar esses papéis e estamos prontos para enfrentar a guarnição da cidade, se for preciso\nComo deve imaginar, você será o primeiro a morrer se começar uma confusão. Então nos dê os documentos e cada um segue seu caminho como amigo.";
			link.l1 = "As chances estão do seu lado... levem, desgraçados, não tenho outra escolha.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Está tentando me assustar? Já vi peixinhos lutarem mais do que você jamais conseguiria! Cai fora.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Fico feliz que tenha sido sensato, capitão. Você se colocou em grande perigo ao aceitar esse trabalho. Agora vou me retirar, se não se importar.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "Foi a sua decisão...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Espere, "+GetAddress_Form(NPChar)+", não se apresse assim. Tenho um trabalho pra você.";
			link.l1 = "Que assunto? Fale logo, estou com pressa.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Eu sei quem você é. E também sei que você acabou de receber um "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" . Estes papéis são o motivo pelo qual estou tão ansioso para falar com você.";
			link.l1 = "E eu não quero discutir esse assunto com gente que eu nem conheço. Quer pegar esses papéis? Então me dá um motivo...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Chega, capitão! Eu pareço um ladrão? Sou um homem de negócios e represento os interesses de "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". Quero te oferecer um negócio muito lucrativo, mas não aqui. Vamos até um quarto da taverna para conversar sobre isso. Não vai tomar muito do seu tempo.";
			link.l1 = "Isso é suspeito demais... Não vou negociar com você, senhor! Cai fora!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm... Vamos ver o que você pode me oferecer. Mas nem pense em me atacar — não vai acabar bem. Vamos, eu vou te seguir.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Você é um homem teimoso e tolo, capitão! Eu te ofereci uma chance de ganhar dinheiro fácil. E você... você vai se arrepender.";
			link.l1 = "Cai fora!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Excelente! Venha comigo.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Agora podemos falar livremente.";
			link.l1 = "E qual é a sua proposta?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Como eu disse, tudo isso é sobre os papéis que você recebeu no escritório do porto. Só preciso de uma cópia deles, só isso\nVocê fica com o original, assim vão te pagar pelo serviço. Ninguém nunca vai saber o que aconteceu, além disso, vou te pagar muito bem.";
			link.l1 = "Com licença... Mas o pacote está lacrado. Você não vai conseguir fazer cópias sem quebrar o lacre!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Eu já esperava por essa pergunta. Vou ter que quebrar o selo, mas não se preocupe, vou conseguir restaurá-lo. Tenho um clichê duplicado e lacre, claro. Ninguém vai perceber que o pacote foi aberto.";
			link.l1 = "Você tem algum clichê falso sobre a administração do porto de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Por que está perguntando, capitão? Sim, eu tenho uma. Acha mesmo que estou brincando? Estou lhe oferecendo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" pela chance de ver esses papéis. Então, vai me entregar o pacote finalmente? Por favor.";
			link.l1 = "Pode levar, mas preciso que me devolva, e lacrados!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Quer saber, não vou. Não gosto disso.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Não se preocupe. Eu sou profissional. Sente-se e descanse um pouco. Vai levar cerca de uma hora.";
			link.l1 = "Tudo bem.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Eu não esperava por isso. Você é teimoso demais, capitão, então vou ter que te matar aqui mesmo e pegar o pacote de graça. Reze, porque eu sou tão bom com a lâmina quanto com clichês baratos.";
			link.l1 = "É você quem deveria rezar, espião!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Pronto. Como eu disse, foi feito da forma mais precisa possível. Pegue o pacote, como prometido "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". E eu preciso ir. Boa sorte, capitão, fico feliz que tenhamos feito um acordo.";
			link.l1 = "Adeus...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Saudações! Ah, que bom te ver!";
			link.l1 = "Bom dia. Hm, me diga, você não está no comando do "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Oh! E como você ficou sabendo sobre o "+pchar.questTemp.WPU.Escort.ShipName+"? Sim, eu sou o capitão dela. Ou melhor, era... O navio afundou não muito longe daqui.";
			link.l1 = "Ah, então eu te encontrei... Permita-me apresentar - "+GetFullName(pchar)+". Estou aqui a pedido do mestre do porto de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Ele me contou rapidamente sobre os problemas da sua caravana e me mandou procurar o seu navio.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Então, você é o capitão do grupo de resgate?";
			link.l1 = "Algo assim. Minha tarefa era encontrar seu navio ou uma prova de que ele havia afundado ou estava incapaz de navegar. Infelizmente, não encontrei o navio, mas o capitão está vivo, o que certamente é uma boa notícia...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Ah, me desculpe, esqueci de me apresentar. Eu sou "+GetFullName(npchar)+". Você já sabe como viemos parar aqui? A tempestade deixou nosso navio impossível de controlar\nAlguns dias depois, ele bateu nos recifes perto desta baía e o vendaval o destruiu em minutos. Só algumas dezenas da minha tripulação sobreviveram. O resto está no fundo do mar. Rezamos por suas almas todos os dias...";
			link.l1 = "Aceite meus pêsames, Capitão "+GetFullName(npchar)+". Me desculpe.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Thank you... The survivors have set up a camp on the shore, hoping for aid. You are just in time, captain! The local warlike Indians are aware of our presence; we will not stand a chance against hundreds of them if they attack us.\nThere is also a pirate ship cruising in this area; it looks like they are searching for us. Have you encountered this pirate, captain?";
			link.l1 = "Não, ainda não.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Louvado seja o Senhor por isso. Ele é um daqueles que nos atacaram antes daquela maldita tempestade. Como uma hiena, está ansioso para acabar com a presa ferida, por isso veio até aqui, para esta ilha.";
			link.l1 = "Entendi. Agora é hora de decidir o que faremos a seguir.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Decidir o quê, capitão? Leve a gente a bordo e vamos sair logo desse lugar amaldiçoado.";
			link.l1 = "Com certeza. Não consegui salvar o navio, mas pelo menos vou salvar a tripulação. Arrume seu acampamento e vou mandar trazer botes para cá. Bem-vindo a bordo!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Obrigado, capitão! Não vai demorar. Espere... Mas que diabos? Argh! Aqueles demônios de pele vermelha estão vindo atrás de nós de novo! Alarme! Às armas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Ufa, conseguimos... Viu, capitão, eu te disse que essa baía é o próprio inferno. Já é o terceiro ataque dos índios! Temos que sair daqui o quanto antes, não vamos aguentar mais um ataque.";
			link.l1 = "Sim, você está certo. Reúna todos que estiverem vivos e leve-os para o meu navio! Vou mandar trazer os botes imediatamente!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... O que você quer de mim? Cai fora, não quero conversar com você.";
			link.l1 = "Você é "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Sim, sou eu. E qual é o seu negócio?";
			link.l1 = "É bem simples. Tem alguém nesta cidade que já se cansou das suas artimanhas. Essa pessoa está de saco cheio delas. Agora eu olho pra você e entendo o motivo. Não apareça mais no bordel local ou vai arranjar encrenca. Entendeu?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Você... ousa me ameaçar, seu desgraçado? Vou te espetar na minha lâmina e assar você como um frango no espeto!";
						link.l1 = "Se prepara, seu desgraçado!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "O quê? Que truques? Não houve truque nenhum. Eu só fiquei bêbado e aproveitei algumas vezes no bordel. Ninguém é perfeito... Tá bom, tá bom, tá bom... Nunca mais vou usar os serviços delas. Satisfeito agora? Dou minha palavra.";
						link.l1 = "Espero que a palavra de honra signifique algo para você e que esteja ciente das consequências caso a quebre. Guarde isso na memória. Agora, adeus.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Você é um homem tão insolente, senhor! Juro que vou fazer você se arrepender dessas palavras antes do pôr do sol. Eu o desafio! Acho melhor resolvermos isso em particular, em algum lugar tranquilo. A selva serve perfeitamente, encontre-me lá em duas horas!";
					link.l1 = "Ótima ideia! Pelo menos não seria difícil esconder seu cadáver.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "O quê? Que truques? Não houve truque nenhum. Eu só fiquei bêbado e aproveitei umas vezes no bordel. Ninguém é perfeito... Tá bom, tá bom, tá bom... Nunca mais vou procurar os serviços delas. Satisfeito agora? Dou minha palavra.";
					link.l1 = "Espero que a palavra de honra signifique algo para você e que esteja ciente das consequências caso a quebre. Guarde isso na memória. Adeus por agora.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Espere! Pare! Eu me rendo! Poupe minha vida!";
			link.l1 = "E é assim que você fala agora!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Eu imploro, por favor, me poupe! Faço o que você quiser! Nunca mais apareço naquele bordel!";
			link.l1 = "Essa pose combina só com gente da sua laia. Espero que isso te sirva de lição pelo resto da vida. E comporte-se direito nesta cidade.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Claro, não vai mesmo. Sua trapaça termina aqui e agora.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Hora de ir pro inferno, desgraçado! Reze por si mesmo, mas faça isso rápido, não tenho o dia todo pra perder...";
			link.l1 = "Menos conversa, mais luta, seu verme!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "E lá está ele, aquele bastardo insolente! Vamos mostrar pra ele quem manda nessa cidade, rapazes!";
			link.l1 = "Ah, você é mesmo um degenerado! Mas eu te avisei. Você e seus capangas vão direto pro inferno agora mesmo!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Saudações. O que você quer?";
			link.l1 = "Você não é "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Você não vai acreditar em mim, haha. Eu quero a sua cabeça.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Não... Não é nada. Acho que me enganei. Desculpe incomodar você.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Que piada mais tola, senhor! Explique-se ou eu vou...";
			link.l1 = "E o que você vai fazer agora, seu miserável? Você prejudicou um homem bom e ele está realmente irritado. Então reze logo e faça isso depressa, porque estou com pressa.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "O que... o que você está fazendo, senhor! Socorro! Alguém me ajude! Assassino!";
			link.l1 = "And I thought you would spend your last seconds praying; at least you might have had a chance to reach the heavens...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Você de novo? Por que não me diz o que quer?";
			link.l1 = "Não é nada.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! O quê? Que diabos você está fazendo aqui, seu desgraçado? Quem te deixou entrar?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "A Liga precisa da sua vida, capitão...";
			link.l1 = "O quê? Droga!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou cidadão desta cidade e peço que guarde sua espada.","Escute, eu sou cidadão desta cidade e peço que guarde sua espada.");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Claro...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Tome cuidado, "+GetSexPhrase("amigo","garota")+", enquanto corro com uma arma. Fico nervoso...","Eu não gosto quando há "+GetSexPhrase("homens que","pessoas que")+" estão andando na minha frente com a arma em punho. Isso me assusta...");
				link.l1 = LinkRandPhrase("Entendi.","Está tudo bem.","Não se preocupe...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
