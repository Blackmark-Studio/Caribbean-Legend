// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","No decorrer deste dia inteiro, essa já é a terceira vez que você faz essa pergunta...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Hum, onde foi parar minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Um homem chamado François Gontier passou por aqui na sua cidade? Eu realmente preciso encontrá-lo.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Escuta, camarada, tem um navio vindo de Port Royal comprando seda para o estaleiro... uma seda muito especial, você com certeza já ouviu falar dela. Dizem que um vendedor dessa seda está morando em algum lugar deste povoado. Você tem alguma pista de como encontrá-lo? Tenho uma proposta de negócio para ele.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "Tenho cinquenta doblões comigo. Pegue-os e comece a falar.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Sim, ele esteve aqui. Estava alugando um quarto há alguns dias. Não era o sujeito mais agradável, vou te dizer. Além disso, era paranoico ao extremo com a ideia de estar sendo procurado. Vivia assustado, olhando para todos os lados. Você é a pessoa de quem ele tinha tanto medo?";
			link.l1 = "Não, não sou eu. Mas sabe, corsários têm muitos inimigos. Então, onde posso encontrá-lo? Eu e ele decidimos fazer um acordo, mas parece que ele sumiu do mapa.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Ele partiu para o mar no próprio navio. Não sei para onde. Ele não me contou sobre isso.";
			link.l1 = "Ah, que pena! Onde é que eu vou procurar por ele agora?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Eu não sei, amigo. Se eu soubesse, eu te diria.";
			link.l1 = "Certo, entendi. Vou perguntar para outra pessoa...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Hã, se você desconfia do nosso comerciante, aquele que cuida da loja, posso te garantir que não é ele, ele não trabalha com velame de seda. Contrabandistas também não aparecem por aqui, não tem porquê, já que não existe alfândega. E além disso, ninguém além do nosso comerciante faz negócios por aqui mesmo. Dá uma olhada, nós não somos esse tipo de gente, ha-ha!";
			link.l1 = "Mas alguém está fornecendo a seda para Port Royal – isso é inegável. Você tem alguma ideia de quem pode ser o fornecedor?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Contrabandistas de Port Royal, talvez? Ou piratas foras da lei? Devem estar descarregando o saque em alguma enseada escondida... Ha! Tive uma ideia, camarada. Tem um sujeito por aqui que sabe de tudo o que acontece nessas águas. Se ele não desconfia de nada, então não há mercadores de seda por aqui.";
			link.l1 = "Excelente! Qual é o nome do sujeito?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Hm... Estou tentando lembrar o nome dele, mas por algum motivo simplesmente não consigo...";
			link.l1 = "Que tal umas moedas para refrescar sua memória?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Acho que isso pode ajudar... Cinquenta dobrões de ouro certamente vão iluminar esta velha cabeça.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "Entendi. Aqui, pegue as moedas.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Entendi. Eu volto depois...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "Husky Billy is the man you need. He has been living on Jamaica for ages, knows every dog on the streets. Used to be a pirate and a pain in the Brits' asses until he got wounded about three years ago. Now he mostly fishes, hunts sharks, and gathers amber in Jamaica's bays. He leaves his old longboat only to buy more rum and crackers\nYou should look for him in the waters around Jamaica. They say he's sailing on the northern side, all the way to the easternmost point. But chasing a longboat is a fool's errand; you'd better stake out around the southwest corner—they say he's been seen near Cape Negril about once a week. His cockleboat is called 'The Fly Fish'.";
			link.l1 = "Obrigado, camarada. Você fez por merecer seu ouro.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Boa sorte, camarada! Espero que encontre o que está procurando!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
