// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pergunte o que quiser.","Estou ouvindo, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","É a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, lidando com assuntos coloniais, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"Verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Me desculpe, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Vossa Excelência, estou aqui a respeito do oficial preso, Lope Montoro...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já pegou tudo. O que mais você quer?","Restou alguma coisa que você não levou?");
            link.l1 = RandPhraseSimple("Só estou dando uma olhada...","Só estou conferindo, talvez eu tenha esquecido de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Malditos ladrões! Vocês ousam atacar Havana?! O que querem?!";
			link.l1 = "Pense por um instante, você vai entender.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Ouro, é claro! O que mais poderia interessar vocês, seus canalhas, além de ouro?! E nós não temos nenhum... Só umas poucas arrobas guardadas.";
			link.l1 = "Ha-ha... Não, não estamos interessados em ouro. Viemos aqui pelo marfim... o tipo negro. Você me entende?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha! Eu suspeitava que você tinha vindo atrás de escravos. Mas eles estão mantidos no forte. Nossas tropas de reforço já estão a caminho, e sua quadrilha será destruída em breve.";
				link.l1 = "Droga! Tá bom, senta aqui e não se mexa... Vamos sair daqui! Merda...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Mas como... Como você soube disso?";
				link.l1 = "Ha! Só um idiota reuniria 5.000 escravos num só lugar achando que ninguém perceberia. Eles fedem daqui até a maldita Tortuga... Espero que entenda que vamos tirá-los de você.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Muito bem, você venceu de qualquer forma e teremos que nos submeter à sua violência. Mas não espere escapar da justiça depois desse roubo e de afundar dois navios de guerra espanhóis.";
			link.l1 = "Não se exalte assim ou vai acabar tendo um ataque do coração. Sente-se aqui e não se mexa...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Que curioso... mais reclamações?";
			link.l1 = "Não, não, muito pelo contrário, excelência. Lope é um velho amigo do exército, lutamos juntos na Europa... Eu adoraria ajudá-lo, e vim pedir sua ajuda.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm... Bem, presumo que, já que veio até mim, já saiba dessa... história absurda?";
			link.l1 = "Sim, Vossa Excelência.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Eu sugiro que você procure don Rosario Gusman. Assim como você, ele quer ajudar don Lope Montero. Ele tentou entrar em contato com a vítima, mas as negociações não deram resultado. Encontre-se com ele, ele vai explicar os detalhes. Você pode encontrar don Rosario nas ruas das quatro às oito da tarde. Ele faz uma inspeção completa dos postos da guarda da cidade todos os dias.";
			link.l1 = "Obrigado, Vossa Excelência!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
