// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais dúvidas você tem?","Como posso ajudá-lo?"),"Você tentou me fazer essa pergunta não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Escute, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Você adivinhou, me desculpe...","Entendo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Dê uma olhada nesses brincos, monsieur. Encontrei-os no bolso de um bandido na selva. É claramente obra de um joalheiro de primeira, que, tenho certeza, não é daqui desse fim de mundo. O que me diz?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Eu sei que você tem um devedor chamado Folke Deluc. Diga-me, quão grave é a inadimplência dele?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Estou aqui para falar sobre a dívida do Folke Deluc.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Terminei sua tarefa, monsieur. Aqui está o seu... amigo espanhol.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Vim falar sobre...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Você trouxe 40 doblões?";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "Aqui está o dinheiro para o meu oficial...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Não, ainda estou pensando.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "E por que isso te interessa, posso saber?";
			link.l1 = "Eu preciso que este homem esteja livre, não atrás das grades. E, pelo que fui informado, até que essa dívida seja quitada com você, ele não será libertado. Estou interessado em pagar essa dívida.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, isso muda tudo. Também tenho interesse em reaver meu dinheiro... Esse Folke Deluc é um sujeito estranho. Ele pegou emprestado uma quantia relativamente pequena – cinco mil pesos. Simplesmente se recusou a devolver e começou a se esconder. No fim, os juros igualaram a dívida original, e ele acabou atrás das grades.";
			link.l1 = "Então, a dívida dele atualmente já acumulou dez mil?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Dez mil quatrocentos e cinquenta pesos, exatamente, monsieur. Então, a liberdade dele custa esse valor. Está disposto a me pagar? Fico um pouco surpreso...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Não se surpreenda. Aqui está o dinheiro.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Uma quantia considerável, de fato. Ouça, monsieur, talvez possamos chegar a um acordo? Por exemplo, pode ser que você tenha algo que eu possa resolver, e você poderia considerar meu favor no valor desses dez mil e quinhentos...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Sim, parece que você realmente precisa desse marinheiro se está disposto a desembolsar tanto dinheiro por ele. De qualquer forma, isso não é da minha conta, não é mesmo, monsieur? Aqui está a nota da dívida dele, agora você tem direito à dívida e pode cobrar o valor dele. Ah, e claro, aqui está também o pedido de soltura dele da prisão.";
			link.l1 = "Era exatamente isso que eu queria. Adeus, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Um favor? Lamento, mas não preciso de nenhum favor seu. Pelo menos por enquanto.";
			link.l1 = "Que pena. Então devo levar o dinheiro para Folke. Tchau!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Favor? Hm... Sabe, monsieur, eu teria recusado se tivesse vindo ontem, mas agora... sim, tenho algo que precisa ser resolvido, mas aviso, é bem perigoso.";
			link.l1 = "Perigoso por quê?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Pela sua preciosa vida, é claro. Então pense bem antes de aceitar e decida se está disposto a fazer algo assim ou não.";
			link.l1 = "Monsieur, perigo não é novidade para mim. Já estive em situações arriscadas tantas vezes. Então, vamos aos detalhes. Desde que não envolva derrotar sozinho toda a guarnição do forte, talvez eu consiga realizar o que você está sugerindo de forma tão misteriosa.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Certo. Então ouça. Esta noite, vários piratas e um prisioneiro vão sair do covil dos piratas em Le Francois e caminhar até a enseada de Le Marin. O prisioneiro é um oficial espanhol, grande especialista em engenharia de fortificações. Os ingleses pretendem usá-lo para seus próprios interesses, então vão enviar um navio de guerra para buscá-lo na enseada. Esse oficial é um velho amigo meu, e não quero que ele acabe como prisioneiro dos ingleses. Não posso pedir ajuda às autoridades locais porque estamos em guerra com a Espanha. Se eu tivesse mais tempo, contrataria homens capazes de resgatar o espanhol... desculpe, de resgatar meu amigo, mas infelizmente não posso! Você é o único em quem posso confiar para essa tarefa. Você deve ir até a enseada de Le Marin e... convencer os piratas a entregar o prisioneiro para você. Duvido que eles cooperem muito, então vai depender de você.";
			link.l1 = "Quantos piratas estarão no comboio?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Não sei. Talvez duas pessoas, talvez três ou quatro. Então, o que você diria?";
			link.l1 = "Já te disse que 'o perigo não me é estranho' e eu sei muito bem qual lado da espada segurar.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Você tem razão, é perigoso. Eu não vou atacar uma tripulação de piratas sozinho.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Essa é a sua decisão. Se acredita que não está à altura desse trabalho, é melhor recusar logo. Então, ficarei aguardando o dinheiro da dívida do Deluc.";
			link.l1 = "Certo. Vou levar o dinheiro para ele. Até mais!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Muito bem. Fico feliz em ouvir isso. Então você deve ir até a enseada Le Marin, os piratas estarão lá das sete da noite até as quatro da manhã. Não perca! E nem pense em usar um navio! Isso vai assustá-los, vá andando pela selva!\nTraga o prisioneiro para mim quando encontrá-lo, vou deixar a porta aberta. Recomendo esperar até uma da manhã antes de voltar para a cidade, porque você precisa evitar chamar a atenção dos guardas. Tome cuidado e boa sorte!";
			link.l1 = "Obrigado! Com certeza vou precisar de um pouco de sorte...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Espere um pouco! Vejo que você nem tem uma arma. Pegue uma das minhas. Também tenho algumas balas para ela. Acho que vai ser útil.";
			link.l1 = "Sim, isso com certeza vai ser muito útil. Obrigado, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "E agora vá, que Deus te ajude!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Maravilhoso! Fico muito satisfeito que você tenha conseguido resolver isso com sucesso. Suponho que não preciso saber os detalhes da operação, não é?  Então, meu caro hóspede espanhol pode se sentir seguro em minha casa agora...";
			link.l1 = "E quanto à dívida do Folke Deluc?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Of course, yes. Take his bill of debt; now you're entitled to his debt and have the right to ask for money from him. Well, and of course, petition for his release from prison. Have I done everything as promised?";
			link.l1 = "Sim, monsieur. Tudo está estritamente de acordo com o combinado. Agora, permita-me retirar-me.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Então, está pronto para pagar a dívida dele?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Sim. Aqui está o dinheiro.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Infelizmente, ainda não consegui juntar a quantia necessária...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Parece que você está certo, esses brincos são caros e com certeza foram feitos no Velho Mundo... O que posso dizer? Eu te dou trinta... não, até trinta e cinco dobrões de ouro por eles. Aceite o dinheiro, você não vai conseguir um preço melhor.";
			link.l1 = "Trinta e cinco doblões? Não é um preço ruim. Concordo. Aqui está.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Não. Acho que vou ficar com esses brincos para mim.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Eu sei, eu sei, Capitão. Seu navegador parece ter acumulado dívidas em quase todas as colônias francesas. Para ser sincero, já estou sabendo disso faz tempo. Consultei meus colegas, procedimento padrão, entende...";
			link.l1 = "E você não achou importante o suficiente para me informar durante nosso acordo anterior?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Por quê? Na época, minha principal preocupação era a dívida do Deluc comigo, que, aliás, era a maior de todas. Assim que você resolveu isso, avisei meus colegas imediatamente... Temos uma enorme frota de mensageiros profissionais, então não demorou muito para que uma pilha de contas do Deluc se acumulasse na minha mesa.";
			link.l1 = "Entendo... Você os comprou sabendo que tenho um interesse vital nele e meios para pagar... Isso é extorsão, Monsenhor.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "É apenas o meu trabalho, Capitão! A dívida total do seu navegador até hoje é de 40 dobrões e, veja bem, os juros continuam correndo... Vai pagar?";
			link.l1 = "Ainda não estou pronto para responder, mas vou pensar a respeito. Adeus!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Excelente! Você já sabe o que fazer agora – igual da última vez. Aqui estão os documentos – apresente-os ao comandante da prisão. Foi um prazer fazer negócios com você, Capitão.";
			link.l1 = "Não há muito o que aproveitar nesta situação. Adeus.";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
