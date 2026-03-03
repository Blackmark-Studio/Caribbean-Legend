// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Vocês têm Simon Morelle preso aqui. Ele é um contrabandista cujo saveiro foi afundado por uma patrulha há pouco tempo. Posso vê-lo?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Oficial, fui enviado aqui pelo senhor governador de Philipsburg. Ele me pediu para patrulhar a ilha e suas águas em busca de espiões ingleses. Sua Excelência também disse que você poderia me fornecer informações úteis.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Oficial, encontrei a patrulha desaparecida. Também encontrei os espiões britânicos. Eles estão aqui na ilha.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Sou eu de novo, oficial. Você prendeu os espiões?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "E por que o senhor precisa dele?";
			link.l1 = "Quero dizer a ele que é um maldito canalha e um patife. Espero que isso ajude quando ele estiver na forca.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! Vejo que tem senso de humor, senhor... Bem, dois mil pesos e pode seguir em frente.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Pegue, oficial. Obrigado!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Sabe, mudei de ideia. Prefiro gastar meu dinheiro na taverna.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "De nada... Siga em frente!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Como quiser, não terá uma oferta dessas da próxima vez.";
			link.l1 = "Não preciso disso mesmo. Até mais, oficial!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Útil? Ha! Pensando bem, espere. Tenho sim algo útil pra te contar. Uma das nossas patrulhas sumiu na selva. Eles já deviam ter voltado para o quartel, mas parece que preferem a companhia dos papagaios. Ou talvez algo realmente tenha acontecido. Se você encontrá-los durante suas buscas, diga para inventarem uma desculpa decente pelo atraso, senão não vão gostar das consequências... O comandante da patrulha se chama Jannes Hoffman.";
			link.l1 = "É só isso, oficial?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Sim, droga. Me desculpe, mas não tenho mais nada pra te dizer. Boa sorte, capitão.";
			link.l1 = "Obrigado...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "O quê?! Espero que não esteja brincando. Me dê um relatório!";
			link.l1 = "Encontrei uma patrulha perto de uma caverna na selva. Eles me pararam e perguntaram para onde eu ia e por quê, depois me deixaram seguir. Maldição, se aqueles não eram os ingleses disfarçados com uniformes holandeses! Também vi algo curioso na selva que parecia exatamente um grupo de homens nus escondidos nos arbustos. Imagino que o grupo de ataque britânico tenha desarmado sua patrulha e pegado seus uniformes.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Como você entende, eu não quis arriscar enfrentando um grupo de casacas vermelhas treinados, então corri até você para fazer o relatório.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Então, então... Uma caverna, é isso? Quantos você contou?";
			link.l1 = "Cinco homens. E sim, acho que eles entraram naquela caverna.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "I am sending a squad to the cave immediately! Captain, if the men you met are really British spies, you will receive a well-deserved reward. You are free to join the squad if you wish to assist the authorities in detaining those bastards and receive an extra reward; these are the governor's orders, after all. So, are you coming along?";
			link.l1 = "Não, oficial, caçar espiões é o seu trabalho. Certifique-se de enviar um esquadrão bem armado, essa escória é perigosa demais...";
			link.l1.go = "FMQN_7";
			link.l2 = "Acho que posso fazer isso. Seus homens vão encontrar os espiões mais rápido com a minha ajuda.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Sua escolha, capitão, vou levar seu conselho em consideração. Venha me ver amanhã para saber o resultado da nossa operação.";
			link.l1 = "Até amanhã.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Sua informação estava correta, capitão. Encontramos aqueles desgraçados dentro da caverna. Eles não demonstraram intenção de se render e partiram para a briga. Como resultado, eliminamos todos eles. Também encontramos a patrulha desaparecida. Estão vivos e bem, embora um pouco machucados... Obrigado, capitão, em nome de todos os bons cidadãos de Philipsburg. Sua vigilância será recompensada, como prometido. Por favor, aceite isto.";
			link.l1 = "Obrigado!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Você é sempre um hóspede bem-vindo em Sint Maarten. Agora, por favor, me dê licença, tenho outros assuntos a tratar.";
			link.l1 = "Eu também. Adeus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Muito bem. Sua ajuda é muito apreciada. Vá até os portões da cidade, o pelotão punitivo será reunido lá em uma hora.";
			link.l1 = "Um pequeno conselho, você deveria enviar os melhores soldados que tiver para essa missão. Esses espiões são perigosos.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Não se preocupe. Estou enviando nossos soldados mais experientes sob o comando do oficial Hans Shulte – o mestre espadachim de Philipsburg.";
			link.l1 = "Ótimo! Então não vamos perder tempo.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
