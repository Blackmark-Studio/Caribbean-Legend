// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas perguntas?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas com tanta curiosidade no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos focar nisso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Hm, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Ouvi dizer que este estaleiro é especialista em melhorar a velocidade de navegação dos navios. Para isso, é preciso uma lona de vela de seda, que é bem rara. Gostaria... de conversar sobre isso?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Eu vim da senhorita MacArthur, sobre...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Inicie a reforma do navio!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Poderia ser mais claro, rapaz? O que exatamente te trouxe aqui? Se quer melhorar seu navio, vamos direto ao assunto.";
			link.l1 = "Não exatamente. O tipo de serviço que você faz exige materiais que não estão disponíveis na loja. Gostaria de lhe oferecer o mesmo tipo de materiais que você possa precisar.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Well, well... Hmm... Are you aware that only the authorities of this colony are permitted to deal with such strategic goods? You are free to provide your own silk for me to use in improving your ship; however, selling it is strictly forbidden. As is buying it from me—such activities will be fined rather heavily.";
			link.l1 = "Bem, isto não é uma loja, nem um escritório da alfândega...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Eu adquiro toda a lona de seda diretamente dos meus clientes, ou compro quantidades limitadas com permissão especial do governador. Se não tiver mais perguntas, por favor, deixe-me voltar ao meu trabalho.";
			link.l1 = "Hmm... Muito bem. Tenha um bom dia, senhor.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Imagino que esse serviço não será de graça?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Claro, Capitão, esses serviços não podem ser de graça, nem mesmo para Cromwell! Mas eu cumpro minha palavra e só vou cobrar em dinheiro – você não vai precisar contrabandear nada.";
			link.l1 = "Entendi. Quanto custa?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Depende do tamanho da sua nau capitânia, Capitão. Um navio de primeira classe vai lhe custar cinco mil dobrões, e um de quinta classe – apenas mil.";
			link.l1 = "Certo, volto até você assim que tomar uma decisão.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Excelente, agora tenho tudo o que preciso. Vou começar a trabalhar, então.";
			link.l1 = "Estou esperando.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Acho que é isso... Qualidade garantida.";
			link.l1 = "Obrigado! Vou dar uma olhada.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
