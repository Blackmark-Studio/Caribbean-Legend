// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Essa é a terceira vez hoje que você me pergunta isso...","Você está repetindo a mesma coisa feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Aye...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Escute, chegou por aqui um alquimista, um médico? Ele é italiano, tem uns trinta anos, se chama Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Escute, estou procurando um caçador chamado Fergus Hooper. Disseram que ele mora aqui. Onde posso encontrá-lo?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "Há cerca de um mês e meio, um tal de Jerome Sauvernier chegou à sua cidade. Você se lembra dele?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Não, não conheço. Temos herbalistas e médicos, mas nenhum com esse nome.","É a primeira vez que ouço um nome tão estranho. Não, nunca tivemos a visita do homem de quem você fala.","Não temos nenhum alquimista por aqui. Temos médicos, mas nenhum com esse nome.");
			link.l1 = "Entendi. Que pena. Vou continuar procurando!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus? Ele aparece bastante por aqui. Mas está na selva desde ontem. Não se preocupe, daqui a uma semana ele volta, tomando rum e contando vantagem das aventuras no mar. Mas tenho que admitir, ele é um caçador de primeira. Não conheço ninguém que pegue cobras como ele.";
			link.l1 = "Cobras? Hm. Quando devo voltar aqui para encontrá-lo?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Pelo menos três dias. Saiba que ele sempre aparece aqui não antes das seis da tarde e vai embora não depois das dez.";
			link.l1 = "Como ele é? Nunca vi esse sujeito antes.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Barbudo, de meia-idade, veste um casaco marrom, chapéu e botas longas.";
			link.l1 = "Merci! Você me ajudou muito, meu amigo. Até mais!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "Ah... Acho que sim. Sim, lembro desse cavalheiro. Não estava vestido com luxo, mas tinha dinheiro.";
			link.l1 = "Ele se machucou numa briga na sua taverna.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "E daí? Brigas acontecem aqui dia sim, dia não. Marinheiros bebem demais, trocam umas palavras – e aí ninguém segura mais. Você parece um homem experiente – com certeza isso já não te surpreende, não é?";
			link.l1 = "De jeito nenhum. A questão é que esse homem é um velho conhecido meu. Combinamos de nos encontrar aqui, mas acabei me atrasando um pouco. Você poderia me dizer onde posso encontrá-lo?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "Por que eu não deveria te contar, senhor? Como eu disse, ele tinha dinheiro de sobra – então alugou uma casa perto da capitania do porto. Uma casa notável, com telhado vermelho. Ele está escondido lá, quase não sai, cuidando da perna. De vez em quando aparece aqui para tomar um gole. Mas nunca é certo – tem dias que ele vem, tem dias que não.";
			link.l1 = "Então vou procurá-lo na casa dele. Obrigado pela informação. Até logo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
