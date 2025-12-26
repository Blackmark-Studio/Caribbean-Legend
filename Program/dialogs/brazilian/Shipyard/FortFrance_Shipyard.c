// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas tão curiosas no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Hum, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Seu homem me disse que você queria falar comigo. Estou ouvindo.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "Terminei o trabalho. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" barris de resina estão nos meus porões de carga.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Sim, sim, capitão "+GetFullName(pchar)+". Vi seu navio entrando no nosso porto e imediatamente mandei meu criado até você. Vamos direto ao assunto então: você é novo por aqui, mas dizem que já se tornou um marinheiro experiente e que a sorte está do seu lado. Por isso tenho uma proposta de negócio para você.";
			link.l1 = "Interessante! Continue, me conte.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Have you ever heard of a special resin the Spaniards produce on the island of Trinidad? It is a rare resource of strategic value, used to fortify the hulls of ships. Every barrel costs a hefty sum because the Spanish direct all the resin to the needs of their Navy. Every colonial authority keeps trade in this good under strict control; to put it simply, it's pure contraband.   I need this resin for a special order. Of course, our store doesn't have it, and the same can be said about our local military warehouses—or perhaps they simply didn't want to sell it. It's irrelevant, really. What matters is that I need the resin, and I know where to get some. All I need is a captain who is comfortable with boardings.";
			link.l1 = "Acho que estou começando a entender o seu ponto...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Excelente. Agora preste atenção, um pequeno comboio comercial foi avistado perto de Trinidad, ou melhor dizendo, no porto de San Jose. Um dos navios está transportando um lote de resina de primeira, justamente a resina de que estou precisando urgentemente. Posso te contar mais, se você gostar da ideia de saquear os inimigos da nossa nação. O que me diz?";
			link.l1 = "Gosto da sua proposta. Estou pronto para tentar.";
			link.l1.go = "FMQM_3";
			link.l2 = "Vou deixar passar, monsieur. Meu navio e minha tripulação não estão nas melhores condições no momento.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Tudo bem, é seu direito fazer o que quiser. Desculpe por tomar seu tempo, capitão.";
			link.l1 = "Adeus.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "Então escute: o comboio é formado por três navios, a resina estará entre outras mercadorias em um "+sTemp+" chamado de 'Bensecho'. Este é o seu alvo principal. Como já disse antes, os espanhóis estão navegando de San Jose - Trinidad para San Juan - Porto Rico. Eles vão zarpar amanhã, então você pode escolher onde atacá-los.";
			link.l1 = "Entendi. E quanto à recompensa?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Tudo o que me interessa é a resina. Pago quinze dobrões de ouro por cada barril desse material. Segundo minhas informações, o 'Bensecho' transporta cerca de cem barris.";
			link.l1 = "Céus! Isso é uma fortuna!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Sim. Já te disse que essa mercadoria em especial é muito cara e rara.";
			link.l1 = "Você também me disse que isso é contrabando.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Não se preocupe, não vai ser preciso levar isso até a loja ou aos contrabandistas. Venha falar comigo quando terminar o serviço, vamos atracar seu navio no meu estaleiro para os reparos e descarregar toda a carga em segredo à noite. Ninguém vai desconfiar de nada.";
			link.l1 = "Você pensa à minha frente, mestre. Muito bem. Sem perder tempo então. Estou a caminho para zarpar.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Boa sorte, capitão.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Excelente! Vamos colocar seu navio no cais, como combinamos antes. Vamos descarregá-lo lá esta noite. Volte para o seu navio e deixe-me preparar o dinheiro para você.";
			link.l1 = "Vamos nessa.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
