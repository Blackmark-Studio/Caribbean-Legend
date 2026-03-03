void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Não temos nada para conversar.";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou cidadão desta cidade e gostaria que você abaixasse sua espada.","Escute, sou cidadão desta cidade e gostaria que você baixasse sua espada.");
				link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Tudo bem...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Tome cuidado, "+GetSexPhrase("amigo","garota")+", andando por aí com uma arma. Isso me deixa nervoso...","Eu não gosto quando há "+GetSexPhrase("homens","pessoas")+" andando na minha frente com a arma em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Entendi.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Vamos lá, camarada, mostra seus bolsos.";
			link.l1 = "O quê?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Você me ouviu. Rápido, menos palavras. Não gosto de conversar...";
			link.l1 = "Droga! E será que "+pchar.questTemp.different.FackWaitress.Name+" trabalhar com você?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Ela faz, ela faz... Me dá seu dinheiro ou eu te abro todo!";
			link.l1 = "Não! Eu vou te esfaquear!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Leve minhas moedas, desgraçado! Mas você não vai sair impune disso...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "É, não dá pra discordar disso. Até mais, camarada. E lembra: você não é bonito o bastante pra fazer as garçonetes desmaiarem. Seja mais esperto da próxima vez!";
			link.l1 = "...Vai logo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Como você disser...";
			link.l1 = "Isso eu faço...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Aqui estou! Quer alguma coisa comigo, bonitão?";
			link.l1 = "Caramba, isso saiu do controle rápido...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Não vamos perder tempo!";
			link.l1 = "Heh, não poderia concordar mais!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Bom dia. Meu nome é "+GetFullName(npchar)+". Eu sou o capitão do "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+"'."; 
			link.l1 = "Excelente! Finalmente, te encontrei.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Me encontrou?!";
			link.l1 = "Sim. Bem, eu trouxe seu diário de bordo, que você deixou no escritório do porto de "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Droga! Agora eu vejo onde perdi isso. Essa perda quase provocou um motim no meu navio...";
			link.l1 = "Então tudo acabou bem. Pegue seu diário de bordo e vamos falar do meu dinheiro.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Chegou na hora certa, ainda não comecei outro, então vou te pagar o máximo que puder. "+FindRussianMoneyString(sti(npchar.quest.money))+" e aceite algumas peças das minhas joias pessoais.";
				link.l1 = "Beleza. Pode pegar.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, sabe, eu já comecei um novo diário de bordo. Mesmo assim, o antigo ainda tem valor pra mim. Então, vou te pagar "+FindRussianMoneyString(sti(npchar.quest.money))+" e aceite algumas peças das minhas joias pessoais.";
					link.l1 = "Fechado então. Pegue seu diário de bordo.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Já comecei o novo diário de bordo. E passei todas as anotações do antigo. Não preciso mais dele, então não tem dinheiro pra você.";
					link.l1 = "Ótimo. Então toda essa perseguição foi à toa.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Obrigado. Adeus, "+GetSexPhrase("amigo","garota")+".";
			link.l1 = "O mesmo pra você...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ha, da próxima vez tenta acertar o timing.";
			link.l1 = "É verdade.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Saúdo você no convés do meu navio. Para ser sincero, você me deu um baita susto – achei que o Caçador de Montarias Caolho estava atrás de mim...";
				link.l1 = "Não, capitão, hoje estou de bom humor. Estou aqui para te ajudar.";
			}
			else
			{
				dialog.text = "Seja bem-vindo a bordo do meu navio!";
				link.l1 = "Oi, Cap! Eu estava te procurando.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Por quê?";
			link.l1 = "Você deixou seu diário de bordo na casa do mestre do porto de "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Droga, então era esse o lugar mesmo! Essa perda já me trouxe um bocado de problemas.";
				link.l1 = "Que tal uma recompensa?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Droga, agora vejo onde eu perdi! Obrigado, mas você demorou demais me procurando. Já comecei um novo diário de bordo. Mesmo assim, as anotações antigas ainda precisam ser passadas para o novo...";
					link.l1 = "E quanto?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Já comecei o novo diário de bordo. E passei todas as anotações do antigo. Não preciso mais dele.";
					link.l1 = "Então você não precisa de um diário velho? Sério?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Posso te pagar "+FindRussianMoneyString(sti(npchar.quest.money))+" e algumas das minhas joias. Isso é tudo o que posso oferecer.";
			link.l1 = "Tá bom então. Pegue seu diário.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Mais uma vez, obrigado. Adeus, amigo.";
			link.l1 = "Continue assim.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Com certeza. Se você está perseguindo alguém, então tem que ser mais rápido.";
			link.l1 = "Não perca seus diários de bordo para começo de conversa. Certo.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Eu achei que todos nós já tínhamos nos acalmado.";
			link.l1 = "Sim, é verdade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Saudações. O que você quer?";
			link.l1 = "Não é nada, só queria ouvir algumas novidades. Tem algo à venda?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Não tenho nada para te vender e nenhuma novidade. Aliás, sua presença aqui não é bem-vinda. Fui claro?";
			link.l1 = "Você é... Então, adeus, camarada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Eu já te disse, você não tem nada que fazer aqui!";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Por que você me atacou?!";
			link.l1 = "Tenho que devolver o navio ao dono.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Para que tipo de dono? Eu sou o dono!";
			link.l1 = "Não, você não é. Eu não sei quem é o dono deste navio. Mas ele foi roubado e eu preciso devolvê-lo.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Merda! Mas ainda não acabou pra mim. Pelo menos vou tentar te matar...";
			link.l1 = "Tentar é tudo o que você pode fazer.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Saudações, "+GetAddress_Form(NPChar)+". Vejo que você é o capitão do seu próprio navio? Meu nome é "+GetFullName(npchar)+" e quero te propor um acordo.";
			link.l1 = RandPhraseSimple("Me desculpe, mas eu preciso ir.","Me desculpe, mas não tenho tempo para conversar com você.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Estou ouvindo.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Então, escute. "+SelectNB_battleText()+"\nNão tenho nem tempo nem oportunidade para encontrá-lo. Porque ele nunca aparece por aqui. Acho que agora você entende, percebe o que estou prestes a lhe propor?";
						link.l1 = LinkRandPhrase("Imagino que tenho que encontrar alguém e trazê-lo até você?","Talvez, encontrar o desgraçado e trazê-lo até você?","Você quer que eu encontre esse homem e o traga aqui?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Então ouça."+SelectNB_battleText()+"\nNão tenho tempo nem oportunidade para encontrá-lo. Ele nunca aparece por aqui. Imagino que agora você entenda, você percebe o que estou prestes a lhe propor?";
						link.l1 = LinkRandPhrase("Imagino que você quer que eu encontre alguém e traga ele pra você?","Talvez, encontrar o desgraçado e trazê-lo até você?","Você quer que eu encontre esse homem e o traga aqui?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Então escute. Na verdade, "+npchar.quest.text+" está servindo na marinha como capitão. Ele nem sabe que eu também estou aqui!\nEu gostaria de encontrá-lo, mas não tenho tempo nem oportunidade para procurá-lo...";
					link.l1 = "Imagino que você quer que eu encontre esse capitão e conte a ele sobre você?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Não exatamente. Encontre-o, mas não precisa trazê-lo até aqui. Mate-o e isso será suficiente. Afunde ele junto com aquele navio imundo, atire nele, fure com sua lâmina – pouco me importa como, só faça esse desgraçado parar de envenenar o mundo com a presença dele. A recompensa será generosa.";
			link.l1 = "Ha! Fácil demais. Me diga o nome dele e o nome do navio.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" do(a) "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chamado "+npchar.quest.SeekCap.shipName+". Ele é um visitante frequente no porto de "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Eu vou te pagar "+FindRussianMoneyString(sti(npchar.quest.money))+" em dobrões de ouro.";
			link.l1 = "É tudo o que eu precisava saber. Vou ficar de olho atento no mar. E quando eu encontrar seu amigo, vou fazer ele... 'abaixando a voz' ...não sair muito vivo dessa.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Isso não é suficiente para esse tipo de trabalho.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Fico feliz que tenhamos feito um acordo. Estarei esperando pelo seu retorno.";
			link.l1 = "Onde vou poder te encontrar? Vamos esclarecer isso agora, não quero perder tempo te procurando.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Todas as manhãs eu vou à missa na igreja local. Você pode me encontrar lá todos os dias das 8 às 9 da manhã.";
			link.l1 = "Combinado então! Espere pelos resultados em breve.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Exatamente. Encontre-o e traga-o para mim. Vivo. Quero resolver isso pessoalmente. Vou te recompensar generosamente.";
			link.l1 = "Bem, posso tentar encontrá-lo, mas preciso de detalhes.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "O nome do desgraçado é "+npchar.quest.SeekCap.name+". Ele serve em "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chamado "+npchar.quest.SeekCap.shipName+", que está sob o comando de "+npchar.quest.SeekCap.capName+". O navio costuma ser visto no porto de "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Eu vou te pagar por este trabalho "+FindRussianMoneyString(sti(npchar.quest.money))+" em dobrões de ouro.";
			link.l1 = "Já chega pra mim. Vou ficar atento em alto-mar.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "Isso não é suficiente para esse tipo de trabalho.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Fico feliz que tenhamos fechado um acordo. Estarei esperando pelo seu retorno.";
			link.l1 = "Onde vou poder te encontrar? Vamos deixar isso claro agora, não quero perder tempo te procurando.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Todas as manhãs eu vou à missa na igreja local. Você pode me encontrar lá todos os dias das 8 às 9 da manhã.";
			link.l1 = "Combinado então! Espere pelos resultados em breve.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Exatamente! Encontre-o e diga que eu moro nesta cidade. Eu vou pagar pelos seus serviços.";
			link.l1 = "Bem... Posso tentar. Me conte os detalhes.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "O nome dele é "+npchar.quest.SeekCap.capName+". E ele serve em "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Ele costuma visitar "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Eu vou te pagar por este trabalho "+FindRussianMoneyString(sti(npchar.quest.money))+" em dobrões de ouro.";
			link.l1 = "Fechado! Acho que logo vou encontrar seu amigo.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Isso não é suficiente para mim.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Fico feliz que tenhamos feito um acordo. Estarei esperando o seu retorno.";
			link.l1 = "Onde eu vou poder te encontrar? Vamos deixar isso claro agora, não quero perder tempo te procurando.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Sempre vou ao culto vespertino na igreja local. Você pode me encontrar lá todos os dias das 18h às 20h.";
			link.l1 = "Combinado então! Espere pelo resultado em breve.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "E aí? O que você quer, senhor?";
			link.l1 = "Você é o capitão "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Sim, sou eu. Qual é o assunto?";
			link.l1 = "Um homem tem um grande interesse em você, o nome dele é "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Lembra?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Ouvi dizer que você tem muita mogno no seu porão. Gostaria de comprar. Você me vende?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "É a primeira vez que ouço esse nome. Deve estar enganado, capitão. Terminamos aqui?";
			link.l1 = "Hm. Tudo bem, me perdoe...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Ah, é mesmo? Mas ele se lembra muito bem de você. Até comentou sobre a sua dívida com ele...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Que dívida? Do que você está falando?";
			link.l1 = "A dívida de honra!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Você está enganado. Eu não negocio madeira nenhuma. Terminamos?";
			link.l1 = "Hum. Tudo bem, com licença...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "E daí? O que você quer, señor?";
			link.l1 = "Você é o capitão "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Sim, sou eu. Qual é o assunto?";
			link.l1 = "Um homem chamado "+sld.quest.SeekCap.name+" servir sob seu comando?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Sim. Ele é um dos meus oficiais. Agora me diga, por que está perguntando?";
			link.l1 = "Claro, eu vou te contar. Estou procurando esse homem a mando das autoridades de "+XI_ConvertString("Colony"+sld.city+"Gen")+", e eu tenho autoridade para prendê-lo e entregá-lo a "+XI_ConvertString("Colony"+sld.city)+". Peço que me ajude com essa questão para que possamos resolvê-la de forma pacífica.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Sério? E um homem assim serve na minha tripulação? Está falando sério?";
				link.l1 = "Não se preocupe com isso, "+GetAddress_FormToNPC(NPChar)+". Vou enviar um escaler até o seu navio e nós mesmos vamos levá-lo.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Não me diga. Sabe de uma coisa, senhor, eu não dou a mínima para o passado dele. Isso não me diz respeito. E quem é você, afinal? Autoridade? Sério? Ha! Não vou entregar meus homens para você nem para ninguém. Essa conversa acabou. Pode ir embora!";
				link.l1 = "Escolha errada... Uma péssima escolha!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Faça o que tiver que fazer.";
			link.l1 = "Pode deixar.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "Terminamos, capitão?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Bom dia. O que você quer, capitão?";
			link.l1 = "Você é o capitão "+GetFullName(npchar)+", estou certo?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Você tem razão. Tem algo para mim?";
			link.l1 = "Sim. Um homem chamado "+GetFullName(sld)+" está procurando por você. Ele quer que você o visite o quanto antes. Ele mora em "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha! Então ele também veio para o Novo Mundo? Então eu realmente deveria fazer uma visita a ele... Obrigado pela informação, senhor!";
			link.l1 = "De nada. Quem vai pagar pelo meu trabalho é o seu amigo. Boa sorte, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "Foi um prazer, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "O prazer foi meu, capitão.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". O que você quer?";
			link.l1 = "Ouvi dizer que você tem muita madeira de redwood na sua carga, e eu gostaria de comprar. Você vende?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Você está enganado. Eu não negocio nenhuma madeira, e sua visita aqui me parece bastante suspeita. Acho melhor você sair do meu navio!";
			link.l1 = "Tudo bem, só estava perguntando. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Está querendo confusão, senhor? Preciso repetir?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Por que você atacou meu navio, canalha?";
			link.l1 = "Eu estou aqui para lhe trazer os melhores cumprimentos de "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , do homem chamado "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Espero que você entenda a situação agora.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Impossível! Então não tenho mais nada a perder...";
			link.l1 = "E a sua vida?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Por que você atacou meu navio, canalha?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Tem alguma ideia? Pedi para você entregar seu oficial numa boa. Agora vou levar ele, você e esse seu barco!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Há um canalha servindo sob seu comando. O nome dele é "+sld.quest.SeekCap.name+". Autoridades de "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" estão mesmo ansiosos para vê-lo. Ele será preso e colocado no meu porão.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "E é por isso que você fez uma chacina no meu navio? Maldito! Ainda me resta um pouco de força... Eu vou te matar!";
			link.l1 = "Homens mais fortes já tentaram...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "O que me diz, capitão? Algum progresso com o meu assunto?";
			link.l1 = "Ainda não. Mas estou cuidando disso.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "O que me diz, capitão? Teve algum avanço com o meu assunto?";
					link.l1 = "Eu gosto. E você também vai gostar."+npchar.quest.SeekCap.capName+" está morto e o seu "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" está no fundo do mar.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "O que me diz, capitão? Algum progresso com o meu assunto?";
					link.l1 = "Eu sei. E você vai gostar."+npchar.quest.SeekCap.Name+" está sentado na cabine do meu navio, sob custódia.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, aqui está você. Fico feliz em vê-lo. Fui informado de que você teve sucesso na sua missão!";
					link.l1 = "Seu amigo veio te visitar?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Excelente! Eu sabia que podia contar com você. Aqui, pegue seu ouro. Você merece.";
			link.l1 = "Obrigado. Fale comigo de novo se arrumar outro inimigo.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Excelente! Vou mandar meus homens tirá-lo do seu navio imediatamente. Agora ele não vai escapar! Aqui está o seu ouro. Você fez por merecer.";
			link.l1 = "Obrigado. Pode me procurar a qualquer hora para um trabalho assim.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Sim, ele esteve aqui e me falou de você. Aqui, pegue seu ouro. Você merece.";
			link.l1 = "Meu agradecimento. Adeus, senhor!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Saudações, Capitão. Gostaria de pedir a sua ajuda.","Capitão! Você pode me ajudar? Por favor.","Capitão, estou pedindo a sua ajuda!");
			link.l1 = RandPhraseSimple("Estou ocupado.","Estou com pressa.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("O que foi?","Diga o que te aflige. Talvez eu possa ajudar.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Um ano atrás, um capitão prometeu me levar para "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+". Mas enquanto eu estava no navio dele, fui jogado no porão e depois vendido como escravo. Mal consegui sobreviver. Estive à beira da morte várias vezes... Enfim, quero lembrar meu 'amigo' de que ainda estou vivo."; // belamour gen
					link.l1 = "O que você quer dizer? Me diga exatamente o que você quer.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Minha esposa foi sequestrada. Um capitão, um pirata como dizem, estava cortejando ela. Minha esposa teve que ficar em casa por dias por causa do assédio dele. Tentei pedir ajuda às autoridades da cidade, mas não consegui. E agora...";
					link.l1 = "E agora?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Sabe, estou procurando um conterrâneo meu. Três anos atrás, chegamos juntos da Europa em busca de uma vida melhor. Acabamos nos perdendo. Mas, há pouco tempo, ouvi dizer que agora ele é capitão de um navio mercante! Tentei encontrá-lo sozinho, mas não consegui.";
					link.l1 = "E então?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Quero que você o encontre e mate. Quero tanto vê-lo morto que nem consigo comer...";
			link.l1 = "Entendi... Acho que posso te ajudar com isso. Me diga o nome dele e o nome do navio.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Desculpe, mas não estou interessado.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" do(a) "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chamado "+npchar.quest.SeekCap.shipName+". Eu vou te pagar  "+FindRussianMoneyString(sti(npchar.quest.money))+", além de todas as minhas joias."; // belamour gen
			link.l1 = "Entendi. Vou ficar atento no mar. Se eu encontrar o alvo... Considere-o morto então.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Eu não vou fazer nada por essa quantia. Procure outro tolo para se vingar.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Era isso que eu queria ouvir! Ah, agora posso comer! Finalmente! Preciso arranjar alguma comida...";
			link.l1 = "Bom apetite. Vou te procurar quando o trabalho estiver feito.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Vou estar esperando por você na igreja local.";
			link.l1 = "Bom.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Eu fui descuidado, e o desgraçado levou minha esposa e a embarcou no navio dele. Peço que encontre esse canalha!";
			link.l1 = "Hm, e por que eu deveria lutar contra outro canalha?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Eu não sou rico, mas será um prazer lhe dar todos os meus bens de valor! Se você libertar minha esposa e trazê-la até mim, eu lhe pagarei "+FindRussianMoneyString(sti(npchar.quest.money))+", além de todas as minhas joias.";
			link.l1 = "Certo, estou dentro. Me conte os detalhes. O nome dele, o navio, e o nome da sua esposa.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Não, amigo, por essa quantia eu não faço. Me desculpe...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "O nome dela é "+npchar.quest.SeekCap.name+". E o nome do bastardo é "+npchar.quest.SeekCap.capName+", ele nada por aí "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chamado "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Merda boia, camarada. Capitães navegam...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Sim, sim, me desculpe! Eu não sou marinheiro, espero que entenda...";
			link.l1 = "Está tudo bem, não se preocupe. De qualquer forma, volto assim que terminar.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Muito obrigado! Estarei esperando por você na igreja local. Mas peço que venha rápido. Estou realmente preocupado com minha esposa...";
			link.l1 = "É, eu também não invejo ela.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "O problema é que meu amigo não tem nenhuma propriedade. O navio dele é a casa dele. Então não consigo encontrá-lo, porque ele está sempre navegando. E eu não posso me dar ao luxo de viajar à toa, preciso ganhar dinheiro pra viver.";
			link.l1 = "Não posso te ajudar se você não tiver dinheiro...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Posso te pagar "+FindRussianMoneyString(sti(npchar.quest.money))+" e eu vou te dar todas as minhas joias. Isso é tudo o que posso oferecer agora.";
			link.l1 = "Esse valor me serve. Estou dentro. Aliás, você pode vir comigo como passageiro, assim verá seu amigo assim que o encontrarmos.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Isso não é suficiente para mim. Procure outra pessoa para fazer isso.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Não, acho que vou ficar por aqui. Não sabemos quanto tempo essas buscas vão durar e posso acabar perdendo todo o meu dinheiro. Tenho um trabalho aqui.";
			link.l1 = "Entendi. Agora me diga, quem é seu amigo e em qual navio ele está.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "O nome dele é "+npchar.quest.SeekCap.capName+". Pelo que sei, ele comanda um "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" named "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Entendi. Bem, vou falar de você para o seu amigo se eu encontrá-lo.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Obrigado. Estarei esperando por você na igreja local. Você receberá suas moedas quando o trabalho estiver concluído.";
			link.l1 = "Certo. Então, até logo, espere pelos resultados em breve.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Bom dia para você, capitão. Já tem algum resultado?";
			link.l1 = "Me lembra qual é o seu problema...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Imagino que fui vingado. É isso mesmo?";
					link.l1 = "Exatamente. "+npchar.quest.SeekCap.capName+" está morto e seu "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" está no fundo do mar.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Você encontrou minha esposa! Eu não acredito! Posso mesmo?";
					link.l1 = "Pode sim. Ela é minha passageira. Você pode levá-la de volta, se "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" é mesmo sua esposa...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Bom dia para você, capitão. Encontrou meu companheiro?";
					link.l1 = "Eu contei, e falei sobre você para ele.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "O quê? Você já esqueceu que eu pedi pra você vingar o capitão "+npchar.quest.SeekCap.capName+" por um ano da minha escravidão?";
					link.l1 = "Não, ainda não.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Eu não acredito no que estou ouvindo! Você esqueceu que pedi para você encontrar e resgatar minha esposa? Ela foi capturada pelo pirata chamado "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Eu não tenho.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Espere um segundo... Você esqueceu da sua promessa de encontrar meu conhecido chamado "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Eu não.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Excelente, eu estava certo sobre você! Então, como prometi, aqui estão suas "+FindRussianMoneyString(sti(npchar.quest.money))+" e joias. Obrigado pela sua ajuda.";
			link.l1 = "De nada...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Meu Deus! Você nos salvou! Por favor, aceite o seu "+FindRussianMoneyString(sti(npchar.quest.money))+" e joias. E saiba que rezaremos por você para sempre!";
			link.l1 = "Reze se quiser. Não tenho problema com isso.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Excelente!... Aqui, pegue "+FindRussianMoneyString(sti(npchar.quest.money))+" e joias. E obrigado, Capitão.";
			link.l1 = "De nada, amigo. Adeus...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Saudações, Capitão. Pode me ajudar?","Capitão! Poderia ajudar uma dama? Seria tão gentil...","Capitão, ajude "+GetSexPhrase("uma garota","eu")+".");
			link.l1 = RandPhraseSimple("Estou ocupado.","Me desculpe, "+GetAddress_FormToNPC(NPChar)+", mas eu não tenho tempo a perder...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Qual é o seu problema, "+GetAddress_FormToNPC(NPChar)+"?","Conte seus problemas, "+GetAddress_FormToNPC(NPChar)+". Vou tentar te ajudar.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Meu marido é comerciante, ele entrega mercadorias para todas as colônias da região. Três meses atrás, ele foi para o mar. Ainda não voltou!";
					link.l1 = "Você acha que aconteceu alguma coisa com ele?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Capitão, vejo que você é um capitão corajoso, um verdadeiro canalha","Capitã, vejo que você é uma mulher forte, que pode lidar com qualquer homem")+"...";
					link.l1 = "E por que você está dizendo isso, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Capitão, por favor, me ajude, eu imploro! Meu marido foi capturado! Você pode salvá-lo?";
					link.l1 = "Espera aí, não entendi. Quem foi capturado por quem?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "I don't know, but I still hope that he is just too busy to write to me. He could have sent me a letter; he knows that I worry about him!";
			link.l1 = "Não é seguro no mar, qualquer coisa pode acontecer...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Exatamente! Você entende do que estou falando. Você parece um "+GetSexPhrase("capitão corajoso","garota corajosa")+", então quero lhe pedir para encontrar meu marido. Estou disposta a lhe pagar "+FindRussianMoneyString(sti(npchar.quest.money))+", além disso, vou te dar todas as minhas joias.";
			link.l1 = "Certo. Vou contar ao seu marido sobre suas preocupações, se eu encontrá-lo no mar ou em qualquer outro lugar. Diga-me o nome dele e o nome do navio.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Não me interesso por uma quantia tão pequena.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "O nome dele é "+npchar.quest.SeekCap.capName+". Ele navega em um "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" named "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Entendi. Agora você precisa esperar. Tente passar a maior parte do tempo na igreja, assim posso te encontrar.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Estou dizendo isso, bom senhor, porque desejo contratá-lo para o tipo de trabalho ao qual está acostumado... por assim dizer.","Quero que você me ajude. Espero que você me entenda como mulher.")+"Um capitão me irritou e eu quero vê-lo morto.";
			link.l1 = "E o que aquela pobre alma te fez?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Esse canalha me enganou. Fingiu que estava apaixonado por mim, até me cortejou. E tudo isso só pra conseguir algo valioso do meu marido! E quando o cachorro conseguiu o que queria, disse que não significava nada... que éramos só amigos!";
			link.l1 = "Hum, talvez ele estivesse certo?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Eu pareço um idiota pra você?! Acha que não sei a diferença entre paquera e conversa fiada?";
			link.l1 = "Claro que sim...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Ele me usou, aquele canalha! Nunca vou perdoá-lo por isso!";
			link.l1 = "Sim, os homens são mesmo assim. Mas será que você consegue se acalmar? Não há nada de terrível nisso...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Nada de ruim?! "+GetSexPhrase("Você é um tipo de moralista, não é um pirata de verdade!","Parece que você nunca esteve numa situação dessas! Ah, claro, quem se arriscaria assim... e eu sou só uma mulher fraca...");
			link.l1 = "Tudo bem. Chega. Só quero saber o quão sérias são as suas intenções.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Droga, "+GetSexPhrase(" você simplesmente não faz ideia de como é a vingança de uma mulher rejeitada ","Você é uma mulher e deve saber como é ser rejeitada! Eu quero vingança ")+"!";
			link.l1 = ""+GetSexPhrase("É verdade, nunca vivi algo assim","Olha, sabe como é, ela só chorava um pouco, quebrava uns copos e logo passava")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Considere-se com sorte. Uma mulher rejeitada e enganada em suas expectativas é uma fúria, um demônio de saia! Nada no mundo poderia acalmar a raiva dela","E eu não sou como ela. Nada poderia suavizar minha raiva")+"!\nQuero que seja você a matá-lo pessoalmente. E antes de morrer, ele precisa saber quem está pagando pela morte dele...";
			link.l1 = "Hm, nem sei o que dizer... E quanto você vai pagar?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Tudo o que eu tenho. Vou te dar minhas joias e "+FindRussianMoneyString(sti(npchar.quest.money))+"! Fechado?";
			link.l1 = "Estou interessado. Diga o nome dele e o nome do navio.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Não estou interessado. Tchau.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "O nome do canalha é "+npchar.quest.SeekCap.capName+" e ele navega em um "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" chamado "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Considere feito, "+GetAddress_FormToNPC(NPChar)+". Espere por mim na igreja local. Espero que você consiga se acalmar um pouco...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Eu vou explicar. O problema é que meu marido, que é apenas um homem comum, foi capturado por piratas! Eles estavam matando todos e não pouparam ninguém...";
			link.l1 = "Parece que o capitão ousou resistir. Caso contrário, teriam poupado a tripulação.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Perhaps so, but my husband is an innocent soul. He was merely a passenger there. He had to tell them he was wealthy in order to save his life. The pirates spared him; he wasn't even put in the cargo hold.";
			link.l1 = "E como você sabe disso?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Ele conseguiu me enviar uma carta. Escreveu que está bem e está sendo mantido em uma cabine, diferente dos outros prisioneiros.";
			link.l1 = "E o que você pretende fazer? Não pode continuar assim. Mais cedo ou mais tarde, os piratas vão perceber quem ele realmente é.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Você também é pirata? Sim, sim, eu sei... Por favor, ajude a gente, salve meu marido! Ele descreveu aquele navio pirata e anotou o nome do capitão. Não vai ser difícil pra você encontrá-los!";
			link.l1 = "Não é tão fácil quanto você pensa. Todos os prisioneiros são o prêmio legítimo do capitão que capturou seu marido, e além disso, isso vai levar tempo.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Mas você pode pelo menos tentar! Além disso, você tem tempo suficiente para procurar. Meu marido não é bobo, e está fingindo ser um comerciante do Velho Mundo, então esses piratas não estão exigindo moedas dele por enquanto. Se você libertá-lo, eu lhe darei tudo o que tenho!";
			link.l1 = "E o que você tem?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Não muito, "+FindRussianMoneyString(sti(npchar.quest.money))+" e todas as minhas joias... Mas rezarei pela sua alma para sempre!";
			link.l1 = "Sim, isso realmente não é muito... Tudo bem, estou pronto para te ajudar.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Sinto muito, mas isso não é suficiente para mim.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Muito obrigado, muito obrigado mesmo!";
			link.l1 = "Você vai me agradecer se eu conseguir, então pare. É melhor me dizer o nome do seu marido e tudo o que souber sobre esses piratas.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "O nome dele é "+GetFullName(forName)+". Do Capitão "+npchar.quest.SeekCap.capName+", ele navega em "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chamado "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Entendi. Bem, agora você deve esperar e torcer para que eu tenha sucesso na minha busca. Fique na igreja, espere e reze ...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, capitão, que bom te ver! Agora, me conte, que novidades você tem sobre a minha tarefa?";
			link.l1 = "Hum, me lembra, "+GetAddress_FormToNPC(NPChar)+", de que tarefa você está falando?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, capitão, recebi uma carta do meu marido! Ele escreveu que você o encontrou.";
					link.l1 = "Sim, está certo, "+GetAddress_FormToNPC(NPChar)+". Seu marido, "+npchar.quest.SeekCap.capName+",  está bem e saudável. Ele só está muito ocupado...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "O que me diz, capitão? Fez o que pedi? O capitão "+npchar.quest.SeekCap.capName+" morto?";
					link.l1 = "Sim, ele está morto, "+GetAddress_FormToNPC(NPChar)+". Eu contei a ele quem era o responsável pela sua morte. A última coisa que ele ouviu na vida foi o seu nome.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Você salvou meu marido! Por favor, me diga que é verdade!";
					link.l1 = "Sim, é isso mesmo. Ele está no meu navio agora. Você pode vê-lo se "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"é realmente seu marido...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Você realmente esqueceu que prometeu encontrar meu marido? O nome dele é "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Ah, sim, claro... Eu não esqueci.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Eu não entendo! Você esqueceu que precisa matar meu agressor, um capitão chamado "+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "Ah, por favor, é claro que não. Seu pedido está em andamento, por favor, aguarde...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Jesus, capitão, você esqueceu sua promessa de libertar meu marido?";
					link.l1 = "Eu não lembro. Você se lembra... 'Espere e reze!'. Apenas espere, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Oh, Deus, eu estou tão agradecida! E sim, pegue o seu "+FindRussianMoneyString(sti(npchar.quest.money))+". E obrigado mais uma vez!";
			link.l1 = "Hum, de nada...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Excelente! Bem, pegue seu "+FindRussianMoneyString(sti(npchar.quest.money))+" e joias. Adeus...";
			link.l1 = "Adeus. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Tenho certeza que é ele! Meu Deus, capitão, sou tão grato. Pegue seu "+FindRussianMoneyString(sti(npchar.quest.money))+". Vou rezar por você todos os dias da minha vida!";
			link.l1 = "Parece bom...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Saudações ao meu colega. Quer alguma coisa"+GetSexPhrase(", camarada ",",  garota")+"?";
					link.l1 = "Seu nome é "+GetFullName(npchar)+", estou certo?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Sim, você é!";
			link.l1 = "Que pena pra você. Vou te dizer um nome, e é bom que você se lembre dele."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Lembra dele?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, eu... ";
			link.l1 = "Agora escuta, ele está muito bravo com você, camarada. Chegou a hora de pagar por vender um homem livre como escravo.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Pagar?! Que porra é essa que você tá falando?";
			link.l1 = "Quero dizer que vou te matar exatamente onde você está.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Pense bem, para quem você está trabalhando?! Esse homem é desprezível e o lugar dele é na plantação de açúcar!";
			link.l1 = "Bem, isso não é da sua conta. Agora você vai ter que responder pelo que fez!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Eu vou responder do único jeito que eu costumo!";
			link.l1 = "Continue...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "O que você quer?";
			link.l1 = "Quero te perguntar, você aceita passageiros? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "E o que isso tem a ver com você?";
			link.l1 = "Só estou perguntando.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Só estou perguntando... Olha, é melhor você sair daqui enquanto ainda estou te dando essa chance. Eu não gosto de você!";
			link.l1 = "Tá bom, tá bom, calma. Eu já tô indo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Já conversamos, então não me provoque!";
			link.l1 = "Eu não vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Saudações, colega! Precisa de alguma coisa?";
			link.l1 = "Gostaria de saber, você não levou a mulher embora de "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" chamado "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, você está certo, ela está na minha cabine! Garota bonita, pernas incríveis, aliás... Por que está perguntando?";
			link.l1 = "Amigo, essa mulher é casada. Isso está errado.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "E daí? Eu gosto dela e pronto. Não vou deixar um idiota esfarrapado se meter no nosso relacionamento só porque ele é o marido dela!";
			link.l1 = "Deixe-me te dizer que a Irmandade não aprova esse tipo de coisa, e se certas pessoas souberem do que você fez, o sinal negro vai ser enviado para você.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Vai começar a me dar sermão?";
			link.l1 = "Calma, só estava demonstrando um pouco de interesse... Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Já falamos sobre a mulher. Não quero discutir isso de novo!";
			link.l1 = "Tanto faz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Fico feliz em receber um colega no meu convés! O que deseja?";
			link.l1 = "Gostaria de saber se você sequestrou uma mulher de "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" chamado "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, você tem razão, ela está na minha cabine! Garota bonita, pernas incríveis, aliás!... Por que está perguntando?";
			link.l1 = "Amigo, essa mulher é casada. Isso está errado.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "E daí? Eu gosto dela e pronto. Não vou deixar um sujeito esfarrapado se meter no nosso relacionamento só porque ele é o marido dela!";
			link.l1 = "Deixe-me te dizer que a Irmandade não aprova esse tipo de coisa, e se certas pessoas souberem do que você fez, a marca negra vai cair sobre você.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Vai começar a me dar sermão?";
			link.l1 = "Calma, só estava curioso... Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "O que você quer de mim, seu verme?!";
			link.l1 = "Eu vim buscar a mulher que você tirou do marido dela. Lembre-se "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? O nome dela é "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Droga! Você nunca vai vê-la, assim como nunca vai ver suas próprias orelhas!";
			link.l1 = "Idiota. Eu posso vê-los no espelho. E vou cortar os seus!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Quem é você?";
			link.l1 = "Olá. Vim por você porque seu marido me pediu. Agora você está livre, e posso levá-la até ele.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "É um sonho?! É verdade?!";
			link.l1 = "É sim, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Louvado seja o Senhor! Estou pronto, vamos sair daqui!";
			link.l1 = "Claro, "+GetAddress_FormToNPC(NPChar)+", prepare-se para voltar em segurança para o seu marido.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Olá! Que bom encontrar um camarada em terra...";
			link.l1 = TimeGreeting()+", eu tenho alguns assuntos para tratar com você.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Um camarada seu está te procurando. Vocês navegaram juntos e chegaram aqui vindo do Velho Mundo."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+", lembra?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, claro que sei! E onde ele mora agora?";
			link.l1 = "Em "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Obrigado! Sabe, achei que você fosse um pirata!";
			link.l1 = "Sou. Mais ou menos. Ou talvez não seja. Mas enfim, estou de bom humor hoje, então não precisa se preocupar. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Tem algum problema? Desculpe, estou um pouco nervoso...";
			link.l1 = "Está tudo bem, camarada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+". O que você quer de mim? Eu sou só um humilde comerciante e...";
			link.l1 = "Eu sei, camarada. Não se preocupe tanto, dizem que isso faz mal pra saúde. Tenho um assunto pra tratar com você.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Que tipo de negócio?";
			link.l1 = "Um amigo seu está procurando por você. O nome dele é "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Você o conhece?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Ah, finalmente! Que maravilha... Me desculpe por ter sido tão rude, mas achei que você fosse um pirata.";
			link.l1 = "Sou eu. Mais ou menos. Ou talvez não seja. Mas enfim, estou de bom humor hoje, então não precisa se preocupar. Me pediram para te entregar uma mensagem e já cumpri minha parte. Seu camarada está em "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Que coisa! Você é um homem de honra. Muito obrigado!";
			link.l1 = "De nada. Adeus, e se cuida, amigo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Olá. Você quer alguma coisa?";
			link.l1 = "Seu nome é "+GetFullName(npchar)+", estou certo?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Sim, sou eu.";
			link.l1 = "Pode parecer tolice, mas sua esposa me pediu para dizer que está preocupada com você.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Entendi... Na verdade, eu estava ocupado demais, tem muitas oportunidades lucrativas e não posso perder dinheiro só porque minha esposa se preocupa demais.";
			link.l1 = "Mas você poderia ao menos escrever uma carta para ela e dizer que está bem.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Sim, você tem razão. Vou escrever para ela imediatamente! Obrigado por se envolver nos assuntos da nossa família!";
			link.l1 = "De nada, amigo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Bom dia. Em que posso ajudar?";
			link.l1 = "Seu nome é "+GetFullName(npchar)+", estou certo?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Sim, sou eu.";
			link.l1 = "Pode parecer tolice, mas sua esposa me pediu para dizer que está preocupada com você.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Putz, droga! Tive medo que fosse aquele caçador de recompensas famoso vindo atrás de mim, o tal do Steve Caolho. Ainda bem que me enganei\nVeja, estou tão ocupado com meu trabalho que não consigo arrumar tempo pra ela. Recebo propostas lucrativas o tempo todo e não posso recusá-las só por causa das preocupações da minha esposa.";			
			link.l1 = "Você está certo, claro. Mas você poderia ao menos escrever uma carta para ela e dizer que está bem.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Sim, você tem razão. Vou fazer isso assim que chegar ao próximo porto... Obrigado por se envolver nos assuntos da nossa família!";
			link.l1 = "De nada, amigo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Tenho minha gratidão, Capitão...";
			link.l1 = "De nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Fico feliz em te ver nesta cidade, capitão. Precisa de alguma coisa de mim?";
			link.l1 = ""+GetSexPhrase("Sabe, capitão... Ufa, nem sei como dizer!","Sim, eu tenho.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Diga como é.","Interessante, e o que é isso?")+"";
			link.l1 = " Eu tenho uma pergunta pra você. Você conhece uma mulher chamada "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, eu conheço. Não tive sorte com ela. Uma garota tola, posso te garantir...";
			link.l1 = "Hm... Sim, e essa garota tola me pediu para te matar. É isso....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Besteira.";
			link.l1 = ""+GetSexPhrase("Concordo. Me desculpe, mas há uma recompensa pela sua cabeça","Não é isso. Há uma recompensa")+". E eu vou pegar isso.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Está brincando, capitão?";
			link.l1 = ""+GetSexPhrase("Não, amigo.","Nem ia fazer isso!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Você não é meu amigo, seu idiota! Você nem pode se chamar de capitão. Você não passa de um brinquedo para essa raiva tola!","Droga! Uma desgraçada contratou outra! Que diabos está acontecendo neste mundo?")+"!";
			link.l1 = ""+GetSexPhrase("Olha o que fala, seu canalha.","Você a usou, então não se surpreenda que ela tenha decidido se vingar.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("Te incomodei?","Solidariedade feminina?!")+"";
			link.l1 = "Vamos acabar com isso!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Já falei com você. Cai fora, seu idiota!";
			link.l1 = "Idiota?! Então tá bom...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Que bom ver você a bordo, capitão. O que deseja?";
			link.l1 = "Tenho uma pergunta pra você. Você conhece uma mulher chamada "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, conheço sim. Não tive sorte ao conhecê-la. Uma garota tola, posso te dizer...";
			link.l1 = "Sim, e essa garota tola me pediu para te matar.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Capitão, não me faça rir. Se não tem nenhum assunto sério comigo, então me despeço de você.";
			link.l1 = "Adeus, então. Mas pense no que eu te disse.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Claro, capitão, como poderia ser diferente?!";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Não quero mais falar sobre esse assunto, capitão. Isso é ridículo demais.";
			link.l1 = "Tanto faz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "O que diabos está acontecendo aqui?! Por que vocês atacaram meu navio?";
			link.l1 = "A pedido da dama chamada "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Você a conhece?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Mas que diabos! Eu não acredito nisso...";
			link.l1 = "Você tem que ir! Você não conhece as mulheres, camarada? Elas sabem ser ferozes.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Bem, eu não vou morrer assim tão fácil. Obrigado pela conversa, já recuperei um pouco das minhas forças.";
			link.l1 = "Isso não vai te ajudar.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Fico feliz em ver você a bordo. Posso ajudar em algo?";
			link.l1 = "Pode sim. Estou procurando um homem chamado "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Este homem é meu prisioneiro e pretendo pedir resgate por ele.";
			link.l1 = "Quero levá-lo.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Infelizmente, isso é impossível. Se for só isso, peço que saia do meu navio.";
			link.l1 = "Certo, capitão, como quiser.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Já conversamos sobre o meu prisioneiro. Nada mudou.";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Prazer em conhecê-lo. Posso ajudá-lo?";
			link.l1 = "Pode sim. Estou procurando um homem chamado "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Esse homem é meu prisioneiro e pretendo pedir resgate por ele.";
			link.l1 = "Quero levá-lo.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Sinto muito, mas não é possível.";
			link.l1 = "Que pena...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Droga! Que diabos?!";
			link.l1 = "Preciso do seu prisioneiro chamado "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! De jeito nenhum, só por cima do meu cadáver!";
			link.l1 = "Já que você perguntou...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Quem é você?";
			link.l1 = "Eu sou o capitão "+GetFullName(pchar)+". Não se preocupe, estou aqui para levar você até sua esposa.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Droga, só posso estar sonhando!";
			link.l1 = "Posso te garantir que não é isso... Bem, agora já passou, vamos tirar você daqui.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Estou exausto, me ajude.","Eu não tenho mais forças para viver assim!"),RandPhraseSimple("Esse trabalho está acabando com a gente.","Os malditos guardas arrancaram a pele das minhas costas!"));				
				link.l1 = RandPhraseSimple("Que pena.","É, a vida é uma desgraça.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "Oh, capitão, sente-se comigo. Eu pago!";
					link.l1 = "Com prazer.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Olá, capitão. Você é um capitão, não é? Talvez até um capitão da marinha?\nSim, você deve ser habilidoso com a espada, diferente do meu filho inútil que vai morrer amanhã... Tudo por causa daquele desgraçado safado que pôs os olhos na moça por quem meu filho está interessado!";
						link.l1 = "Sim, eu sou um capitão, e minha espada já me salvou muitas vezes, mas e o resto desse seu discurso deprimente? Vai explicar?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Saudações, capitão. Diga-me, por acaso você é um pirata? Ah, claro que não! Você não é. Piratas têm uma aparência terrível, se comportam como animais, e aquele cheiro...";
						link.l1 = "Você guarda rancor dos piratas?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "Ei, você! Isso mesmo, você aí, onde estão seus modos? Por que diabos está parado aqui me incomodando? Olha só pra ele, que idiota! Estou falando com você! Dá licença! Tem gente de fora demais por aqui!";
							link.l1 = "Calma, não quis te incomodar. Me desculpe.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Cuidado com o que diz, ou corto sua língua fora, meu bom senhor.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Saudações, capitão. Tenho um pedido a lhe fazer. Se for um homem de honra, não vai se omitir.\nEntão, vou direto ao ponto: um nobre ficou em nossa taverna há um mês. Ele se revelou um devasso e um canalha! E mais, é um assassino!";
						link.l1 = "Se bem me lembro, a pena por assassinar um inocente é a forca. Ser um devasso e um bastardo também não vai te ajudar muito no tribunal. Estou certo?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Capitão, espere, eu lhe imploro. Você parece ser um espadachim habilidoso, muito melhor do que eu. Por isso, quero lhe pedir para me substituir.";
						link.l1 = "Interessante. Continue.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Por favor, eu te imploro, não vá embora! Espere... Você não ajudaria uma alma perdida numa questão que exige a intervenção de um oficial militar tão corajoso quanto você?\nVeja bem, tive uma briga sobre as plantações de uva locais com meu vizinho, que, aliás, é suspeito de envolvimento com contrabandistas. Sim, sim, e talvez até tenha negócios com piratas—como mais ele teria feito tanta fortuna em tão pouco tempo?\nEle não tinha nada além de uma barca há um ano, e agora quer tomar meus vinhedos, está ouvindo?! Meus vinhedos!";
						link.l1 = "Sinto muito pelos seus vinhedos. De verdade. Adeus.";
						link.l1.go = "exit";
						link.l2 = "Com licença, mas você não pode procurar as autoridades locais?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Capitão, capitão, eu lhe imploro! Proteja a honra de uma moça inocente!";
						link.l1 = "Não tenho tempo pra isso, bela. Procure outra pessoa...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Saudações, minha senhora. Não trema assim! O que aconteceu?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Bug. Avise os desenvolvedores.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Capitão, tenho sido perseguida de forma descarada por um oficial da nossa guarnição. Você deve ter ouvido os boatos imundos que ele espalha sobre mim, tentando me envergonhar!\nAi de mim, não tenho amigos capazes de proteger meu bom nome! Estou desesperada! Meu Deus, é ele! Me ajude!";
			link.l1 = "Não se preocupe, eu vou cumprir com isso.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Ah, aí está você, minha senhora! Mais um cavalheiro, é isso? Quando vai sossegar? Talvez nunca... Vai trabalhar no bordel, é o lugar mais adequado pra você...";
			link.l1 = "Oficial, pare de cuspir insultos ou vou te fazer calar do meu jeito!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Quem é você? A-ah, curtido pelo próprio mar, o valente capitão de um barquinho, acertei? E o que vai fazer, filhote... do mar?";
			link.l1 = "Essa dama é minha amiga! E eu vou te dar uma chance!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "O quê?! Você não vai me desafiar por causa disso...";
			link.l1 = "Chega! Vou te esperar perto do farol em duas horas. E não se esqueça de levar sua espada!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ah, eu sei de tudo, senhor! Você nem imagina o quanto sou grato a você! Que o Senhor te proteja!";
			link.l1 = "Fico feliz por ter ajudado você. Boa sorte!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ah, você é igual a todos os outros, me deixe!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+"... Mal ouso ter esperança, mas talvez sua espada possa proteger minha família desta vez?\nComo eu disse, meu filho não é um espadachim, mas terá que lutar um duelo ao amanhecer. Ah, se não fosse por aquela mulher e essa maldita honra\nMas ele não podia recuar, e agora está condenado, você não percebe? Estou desesperado—ele é meu único filho e herdeiro, então imploro que mate o canalha que desafiou meu garoto antes do amanhecer. Eu recompensarei você, dou minha palavra!\nVocê encontrará o homem na taverna "+sTemp+" - lá, onde canalhas como ele passam o tempo livre... Eu te imploro...";
			link.l1 = "Eu não me importo com você nem com seu filho. Me deixa ir!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Só assim? Tudo bem, vamos ver como isso termina.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Você vai mesmo ajudar meu filho? Oh, "+GetAddress_Form(NPChar)+"! Estarei rezando por você e pela sua sorte!";
			link.l1 = "Não vejo problema nisso... Espere por mim!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "O que diabos você quer de mim? Estou tentando descansar aqui e não quero ser incomodado. Tem muitos lugares vazios e gente disposta a ouvir, então me deixe em paz, senhor!";
			link.l1 = "Infelizmente, você vai ter que adiar seu descanso para tempos melhores.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "O quê?! E quem é você pra me dizer o que fazer?!";
			link.l1 = "Já se esqueceu de mim, hein? Mas eu me lembro de você! E o meu ponto é que canalhas como você envenenam o nosso mundo só de estarem por aqui!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ah?! Marinheiro, parece que você está completamente bêbado! É a primeira vez que te vejo! Mas não vou tolerar esse seu comportamento! Esta é sua última chance de salvar essa sua vidinha miserável! Peça desculpas agora, seu peixe-boi inchado, e eu vou esquecer essa sua fala insolente!";
			link.l1 = "Eu só dou explicações a homens de honra, não a porcos imundos!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Que porra é essa?! Tá procurando encrenca, verme de latrina?";
			link.l1 = "Vou calar essa sua boca suja com as próprias palavras, rato! Vou te esperar perto do farol em duas horas, e não esquece de trazer esse ferro velho enferrujado que você carrega no cinto!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha! Eu estarei lá!";
			link.l1 = "Até logo!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "Oh, é você! Está vivo, o que significa que...";
			link.l1 = "Sim, sou eu, e seu filho não precisa duelar amanhã de manhã...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Que dia maravilhoso! Preciso ir contar a boa notícia para minha esposa!\nCapitão, foi o destino que trouxe você para me ajudar. Aqui, aceite essas moedas e a gratidão da minha família!";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Cai fora, assassino de criança!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Eu? Graças a Deus, estou bem, mas minha irmã não teve tanta sorte. Ela trabalha numa taverna. Tem um corsário que costuma aparecer por lá, um sujeito muito perigoso. Pirata! O navio dele está no mar há pelo menos uma semana. Ele bebe, ameaça as pessoas e jura que vai matar quem tentar argumentar com ele. O pior é que minha irmã me contou que ele vive dizendo que vai levá-la embora, para Deus sabe onde, se ela não ceder aos desejos imundos dele! Eu não sei o que fazer! As autoridades não ligam para uma simples criada, e cidadãos pacíficos como eu têm medo desse corsário. Por favor, nos ajude a lidar com ele!";
			link.l1 = "Não tenho tempo para acalmar bêbados em tavernas. Fale com o comandante, ele é pago para resolver esse tipo de coisa.";
			link.l1.go = "exit";
			link.l2 = "Hm, um corsário ameaçador? Tudo bem, eu vou cuidar disso.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ah, obrigado, capitão! Tenho certeza de que ele vai te ouvir como um marinheiro escuta outro marinheiro! Faça com que ele deixe minha irmã em paz de uma vez por todas! Não somos ricos, mas vamos te pagar bem pelo seu esforço!";
			link.l1 = "Tudo bem, tudo bem... Já estou indo resolver seus problemas. Espere por mim!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "E daí? Você falou com aquele pirata? Ele vai nos deixar em paz?";
			link.l1 = "Espere um pouco. Já estou cuidando disso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "O que você quer? Não está vendo que estou tentando descansar aqui?";
			link.l1 = "Ora, ora... Eis o grande senhor dos copos de cerveja, ladrão de moças e a tempestade desta cidadezinha em pessoa, não é? E será que você é tão corajoso assim fora da cidade? Perto do farol, um duelo, em duas horas?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Tá se achando um herói, é? Tanto faz, camarada, hoje estou de bom humor, então vou te perdoar. Vai lá e me traz umas canecas de cerveja!";
			link.l1 = "Eu não sou seu amigo. Preciso repetir para um imbecil como você? Será que você é corajoso o bastante para aparecer em um duelo como faz na taverna?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Você está me desafiando?! Qual é o seu problema? Cansou da vida, quer morrer, seu desgraçado? Muito bem, se é isso mesmo que você quer, vou até o farol, arranco suas tripas e depois destruo essa maldita taverna também!";
			link.l1 = "Falar é fácil, espadas não são, então lembre-se de trazer a sua!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "E daí? Você falou com aquele pirata? Ele vai nos deixar em paz? Minha irmã disse que ele saiu da taverna e não voltou...";
			link.l1 = "Sim, eu falei com ele. O sujeito foi um pouco grosseiro, mas meus argumentos foram bem razoáveis e convincentes. Sua irmã não tem mais com o que se preocupar agora.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "Isso... acabou? Podemos respirar aliviados agora? Obrigado, capitão! E onde... onde está aquele canalha??";
			link.l1 = "Ele... ele está no navio dele. Decidiu deixar esta cidade o quanto antes.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Você prestou um grande serviço aos cidadãos desta colônia! Aqui, aceite esta recompensa pela sua ajuda! É algo modesto, mas você vai conquistar o respeito de todos os meus amigos e, acredite, eu tenho muitos deles!";
			link.l1 = "Meu agradecimento! Boa sorte para você e sua irmã. Espero que ela se case com um homem honrado. Adeus!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "Ah, é mesmo? E como você pretende me impedir?";
			link.l1 = "Com a minha espada, é claro, essa é a única maneira adequada para um porco insolente como você.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Perfeito! Estarei esperando por você perto do farol em duas horas.";
			link.l1 = "Legal! Com certeza eu vou estar lá.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Saia do meu caminho, covarde!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Capitão, aquele desgraçado não é tão simples assim. Tom, meu velho amigo, morreu num duelo contra ele, acusado de trapaça nas cartas! Ele era inocente, eu juro. Mas o governador disse que não houve crime naquele maldito duelo.";
			link.l1 = "Hm...   A culpa é toda do seu amigo. Jogar cartas desse jeito pode acabar mal pra saúde.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "É mesmo? Já apareceram quatro trapaceiros de cartas na nossa cidade nas últimas duas semanas. E todos eles tentaram enganar o nosso fidalgo? O que você acha disso? O que eu digo é que esse fidalgo é o verdadeiro trapaceiro. Se não acredita em mim, vá lá e veja com seus próprios olhos.";
			link.l1 = "Você quer apostar com ele? Não, eu não gosto de jogos de azar. Nem pensar.";
			link.l1.go = "exit";
			link.l2 = "Acho que vou fazer isso... Tem algo muito errado aqui.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Capitão, meus amigos e eu juntamos uma quantia para pagar o homem que vai revelar quem é esse nobre, e se vingar dele por tudo o que fez. Estarei esperando na cidade para lhe entregar sua recompensa assim que o serviço estiver concluído.";
			link.l1 = "Eu vou fazer isso se o que você está dizendo for verdade.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "Meus respeitos, senhor! Vejo um nobre e talvez... um jogador? Que tal uma partida?";
			link.l1 = "Claro! Vamos falar das apostas. Que tal 50 moedas?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Está brincando? Você não tem eles!";
				link.l1 = "Você está certo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "A aposta não importa, vamos jogar, isso é o que vale. Já quase esqueci como são as cartas, graças aos idiotas daqui.";
				link.l1 = "Bem, vamos começar.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Então, a aposta é de 50 moedas.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Espere um momento, o que é isso?.. Impossível! Senhor, você é um trapaceiro! Devolva minhas moedas!";
			link.l1 = "Você deve ter razões sólidas para me acusar,  "+GetAddress_FormToNPC(NPChar)+". É melhor você atirar neles agora mesmo, ou vai ser um duelo!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ah, assim mesmo? Muito bem, então um duelo! Hoje, em duas horas, perto do farol!";
			link.l1 = "Fechado!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Alguma novidade, capitão?";
			link.l1 = "Você estava certo, também fui acusado de trapaça, então tive que derrubar o desgraçado num duelo.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Viu só? Eu sabia disso! Muito obrigado por mim e pelos meus amigos! Aqui, pegue sua recompensa, capitão.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Did I tell you that I have come here to apply for a fencing tutor position? No? Well, the local governor is looking for a tutor for his nephew, and it suits me just perfectly. I know the basics of this art, though I have never tried it in practice.\nI almost had the job in my pocket, but it turned out that the local merchant has run into trouble; some dangerous-looking rascal is threatening him. The governor ordered me to deal with this matter to test my professional skills.";
			link.l1 = "Então faça isso. Adeus.";
			link.l1.go = "exit";
			link.l2 = "E o que esse canalha quer com o mercador, e por que você precisa de mim?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Eu achei que o homem fosse um mercenário, e com mercenários sempre dá pra negociar. Dívidas antigas, essas coisas... Mas ele estava mesmo decidido a continuar pressionando o comerciante. Eu queria te pedir pra ajudar o comerciante e a mim, salvando-o do mercenário e cumprindo as ordens do governador\nEu realmente preciso desse cargo, e não consigo me livrar do mercenário sozinho. Por favor, me ajude, e eu te dou cada moeda que consegui juntar, ou então vou ser obrigado a deixar a cidade envergonhado!";
			link.l1 = "Tá bom, tá bom, eu vou te ajudar... 'mestre da esgrima'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "O que você quer? Não está vendo que estou ocupado?!";
			link.l1 = "Incomodando um comerciante respeitável e fazendo esse escândalo!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah! Outro protetor? Sairia mais barato me pagar do que contratar guardas todo dia. Não sou muito fã desse trabalho de matar, prefiro resolver dívidas, então se você é mesmo esse herói, venha até o farol e vamos nos enfrentar num duelo. E se não for, então não cruze meu caminho de novo.";
			link.l1 = "Fechado! Vou te esperar lá.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Parece que você é ainda mais covarde do que eu...";
			link.l1 = "Sim, sou eu.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Alguma novidade, capitão?";
			link.l1 = "O mercenário está morto. Espero que o cargo seja seu agora?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Oh, capitão, obrigado! Pegue sua recompensa e eu vou informar o nosso governador!";
			link.l1 = "Adeus... mestre.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Mais uma?";
			link.l1 = "Saúde.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "E ainda mais!";
			link.l1 = "Espere um pouco! Para onde você está correndo?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Dane-se as perguntas! Beba!";
			link.l1 = "Tudo bem, mas quem sabe você me conta depois o que aconteceu com você?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Está mesmo interessado? Então escute enquanto ainda posso falar! Daqui a alguns dias não vou conseguir dizer mais nada, porque estarei morto... Sim, morto! E a culpa é do rum. Rum demais, e esse oficial, que parece ter sido trazido pelo diabo só pra me atormentar!\nÉ claro que eu não teria enfrentado o melhor espadachim da nossa guarnição e da cidade inteira se estivesse sóbrio, ou pelo menos não tão bêbado. Mas e agora? Estou perdido, arruinado, já estou morto! Que idiota eu sou...";
			link.l1 = "Sim, isso foi bem tolo. Mas é provável que você aja com mais sabedoria no futuro... se sobreviver ao duelo, é claro. Adeus.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Ficar bêbado também não é a melhor opção, oficial. Tenho certeza de que existe uma solução para esse problema.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Que tipo de solução? Desertar e perder minha reputação e o uniforme de oficial? Ou me matar para não ser abatido como um porco? Qual seria o seu conselho?";
			link.l1 = "Nem um, nem outro. Eu vou te ajudar, e vou tentar impedir que seu oponente te cause qualquer dano antes da hora do duelo. Onde posso encontrá-lo?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Está falando sério? Vai mesmo fazer isso?! Ah, eu juro, vou recompensar você de verdade!\nEle pode ser encontrado na cidade. A amante dele mora aqui, todos os oficiais já ouviram falar dela, mas infelizmente o endereço é desconhecido... Então aposto que você pode encontrar ele lá também.";
			link.l1 = "Já chega. Espere aqui por mim. Vou lá conversar com esse... 'melhor espadachim'.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Alguma novidade pra mim, senhor? Boas ou... nem tanto?";
			link.l1 = "Ainda não tenho notícias. Espere aqui. Vai ficar tudo bem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Tem alguma novidade pra mim, senhor? Boas ou... nem tanto?";
			link.l1 = "Acabou. Seu possível adversário não vai mais machucar ninguém... Agora você está seguro. Mas espero que tire uma lição disso e não seja agressivo com pessoas que você não conhece.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Você está brincando comigo, né? Eu... Eu sou realmente grato, "+GetAddress_Form(NPChar)+"! Aqui, pegue tudo o que eu tenho. Este é o meu salário, pode ficar com tudo!\nUma lição, você diz? Sim, droga, você está certo! Isso não vai acontecer de novo, eu te prometo. E obrigado mais uma vez por me dar outra chance!";
			link.l1 = "Está bem então. Adeus, oficial...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Obrigado novamente, "+GetAddress_Form(NPChar)+", pela sua ajuda!";
			link.l1 = "Você é sempre bem-vindo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Ei, que diabos? O que você está fazendo nos aposentos da minha dama? Saia daqui ou eu te arrasto à força!";
			link.l1 = "Eu ando onde quiser e não vou te denunciar por esse comportamento! À força? Vai lá, tenta!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Que insolência! Que atrevimento sem igual! Senhor, você está redondamente enganado! Saia desta casa imediatamente, ou juro que vai se arrepender de já ter nascido!";
			link.l1 = "Falar é fácil! Quem vai se arrepender é você, não eu, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Really? Beware then! If I kill you in this house, it will be murder. So your death won't tarnish my name; men of honour settle such matters near a lighthouse!\nI challenge you, "+GetAddress_Form(NPChar)+", you insolent man! You shall answer for your words! So, a duel in two hours?";
			link.l1 = "Claro, "+GetAddress_FormToNPC(NPChar)+" cara ousado.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "Então trate de estar lá na hora certa. Ainda dá tempo de pedir um réquiem ao nosso padre.";
			link.l1 = "Um réquiem por você? Você não vale nem um peso. Te vejo perto do farol!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Cai fora!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Você está falando do governador? Ha! 'Julgamento de Deus', foi isso que o governador me disse quando reclamei! Um duelo! O que você acha disso? Eu sou apenas um plantador tranquilo, que ama a paz, não um bandido ou um brigão\nIsso vai ser assassinato, não um duelo! E você, sem dúvida, é melhor nessas coisas do que eu. Por isso, peço que seja meu representante no duelo que está por vir. Acredite, não vou ficar em dívida com você.";
			link.l1 = "Quando será o duelo?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Hoje à noite, antes da meia-noite, perto do farol. Você vai me ajudar?";
			link.l1 = "Certo, eu vou te ajudar. Espere por mim na cidade!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Me conte o que aconteceu lá? Nós... Desculpe, você venceu?";
			link.l1 = "Tenho certeza de que vai se interessar em saber que houve uma emboscada. Talvez seu vizinho tenha preferido jogar pelo seguro e convidou mais alguns representantes em vez de apenas um, e todos eram bandidos experientes. Felizmente, sou um espadachim experiente.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Que canalha! Agora, imagino que o nosso governador não terá mais motivo para recusar meu pedido de prender esse patife! Muito obrigado! Pegue sua recompensa, preciso ir até a residência.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "É divertido jogar sem bugs, já que esses desgraçados são difíceis de encontrar.";
			link.l1 = "Relaxa, vou avisar os desenvolvedores.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ah, aí está você. Estes são meus amigos e segundos. Vamos começar?";
					link.l1 = "Estou ao seu dispor!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Todos estão reunidos. Está pronto?";
					link.l1 = "Sim, podemos começar!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Até que enfim! Já estava começando a achar que tinha andado tanto à toa... Vamos acabar logo com isso, deixei uma caneca de rum e uma bela moça me esperando na taverna!";
					link.l1 = "Tenho certeza de que você não vai mais precisar de nenhum dos dois!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Então você decidiu vir? Finalmente! Vamos começar então!";
					link.l1 = "Não se apresse assim, você pode acabar caindo sobre uma lâmina.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "E estes são meus segundos, senhor. Agora prepare-se para morrer!";
					link.l1 = "Depois de você.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Aqui estamos. Prepare sua espada, senhor!";
					link.l1 = "Com prazer, que vença o melhor!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Excelente, todos chegaram... Vamos começar, senhor!";
					link.l1 = "Vamos dançar!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "E quem é você? Não parece um cidadão comum, camarada...";
					link.l1 = "Então? Eu marquei um duelo com você?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha! Um duelo! Parece que você é o nosso cliente. Galera, vamos esfaqueá-lo e pegar logo nossa recompensa. Arranca as tripas dele!";
			link.l1 = "Uma emboscada? Que patético, vai precisar de muito mais do que isso pra me derrubar...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "Acha que vamos deixar você matar nosso amigo e sair impune? Às armas!";
				link.l1 = "Eu devia ter esperado isso de um desgraçado tão miserável!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Capitão, sua honra foi restaurada, você venceu. Mas permita-me lhe dar um bom conselho – vá embora da cidade e não apareça por aqui por um tempo...";
				link.l1 = "E qual é o problema?";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "Foi tudo por honra, e agora vamos buscar nosso amigo.";
				link.l1 = "Claro, não vou te impedir...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "O problema é que você matou um dos auxiliares do nosso comandante. Ele era um homem ruim e ninguém vai lamentar sua morte... mas o comandante gostava muito dele e nunca vai te perdoar pela morte do amigo.";
			link.l1 = "Obrigado pelo conselho, vou segui-lo com certeza. Até logo.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
