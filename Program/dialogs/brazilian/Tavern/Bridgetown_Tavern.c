// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","Esta já é a terceira vez que você me incomoda...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Quero uma bebida. Sirva-me o seu melhor rum.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Escuta, onde está o Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Você, por acaso, tem algum trabalho? Ou talvez possa sugerir algo?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Terminei o serviço. Fernando Rodriguez está morto.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Escute, chegou algum alquimista na cidade, um médico? Ele é italiano, tem uns trinta anos, se chama Gino Gvineili. Ouviu falar dele?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Aqui está sua bebida. O melhor rum para o nosso novo convidado! É uma ocasião especial, ou só veio matar a sede mesmo";
			link.l1 = "Aye, you could say it's a special occasion. I'm taking some slaves to Blueweld. I've recently modified my new brig's hold specifically for this purpose. I just stopped by a plantation and spoke with the overseer; he ordered a fine batch of 'black ivory' from me. So wait for me back at your tavern soon. I'll deliver the merchandise to Blueweld and then I'll be doing some more business here on Barbados, yo ho!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Sério? Ora, não há vergonha em beber por um bom negócio! Então, você diz que vai fazer negócios em Barbados? Que ótimo! Um brinde a você, capitão!";
			link.l1 = "Muito obrigado, amigo. Certo... Vou procurar um lugar onde eu possa me sentar.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston left town two days after your 'trader' act. You put on quite a show here, ha! Your deception was exposed quickly; this town is small and gossip travels fast. That made Gaston take his leave. No one has seen him here since. He did leave a letter for you, though.\nHe asked me to give it to you personally if you showed up here before he returned. Actually, you're not the first man looking for Gaston. There was a narrow-eyed big man and an old one, looked Spanish or Portuguese, I can't say for sure. But I can't forget his face—there was something very wrong about him...";
			link.l1 = "Me dê essa carta... Obrigado!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				Notification_Reputation(false, 48, "high");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Não preciso dos serviços de um canalha. Não tenho nenhuma tarefa que possa te oferecer.";
				link.l1 = "Ei, ei. Calma com as palavras, amigo!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				Notification_Skill(false, 35, SKILL_F_LIGHT);
				Notification_Skill(false, 35, SKILL_FENCING);
				Notification_Skill(false, 35, SKILL_F_HEAVY);
				Notification_Skill(false, 35, SKILL_PISTOL);
				// <--
				dialog.text = "Capitão, você é muito mole. Preciso de um lutador com mais reputação do que você. Volte quando souber usar melhor esse aço pendurado no seu cinto. E um pouco mais de precisão no tiro também não faria mal.";
				link.l1 = "Entendi. Então vou te fazer uma visita mais tarde.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Você realmente chegou na hora. Tenho uma tarefa que precisa ser feita imediatamente. Se você se sair bem, posso te apresentar a algumas pessoas influentes. Agora preste atenção, aqui está o que você precisa fazer.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Um hidalgo chegou recentemente de Sevilha, tentando escapar das consequências indesejadas de um duelo na Europa. Mas a vingança não conhece limites, e uma família nobre espanhola quer esse hidalgo morto. Cumpra o pedido deles por qualquer meio necessário.\nTraga o dedo do homem com o anel como prova. Além disso, traga qualquer outro item que encontrar no corpo dele. Está pronto para aceitar o trabalho?";
			link.l1 = "Se o pagamento for bom, então eu topo.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Trabalhar como assassino? Nem pensar!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Então cai fora e esquece do que a gente falou.";
			link.l1 = "Estou indo embora.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Sua recompensa será de 30.000 peças de oito, um bom dinheiro. Além disso, pode ficar com toda moeda que encontrar no corpo dele. Agora, vamos aos detalhes. O nome é Don Fernando Rodriguez, 35 anos, alto, moreno, veste-se como um oficial militar. É um bom marinheiro e um espadachim experiente\nNão sei onde encontrá-lo, só sei que está em algum lugar do Caribe\nProcure em todas as cidades espanholas até achá-lo. Você tem dois meses. Mais uma coisa: eu sei exatamente o que ele carrega com ele, então nem pense em esconder nada de mim. Alguma pergunta?";
			link.l1 = "Não tenho perguntas. Estou a caminho!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Você está com o dedo com o anel? Deixe-me ver.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Sim, claro. Aqui está.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Não. Fernando afundou nas águas junto com o navio dele, e o dedo afundou com Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "O dedo com o anel era uma condição obrigatória no contrato. Servia como prova da morte do cliente. Vai saber se o Rodriguez conseguiu chegar à costa depois do naufrágio? Você conferiu? Não. No fim das contas, você não cumpriu a tarefa, então nosso acordo termina aqui. Tudo de bom.";
			link.l1 = "Mas eu dei um fim nele. Ele se foi! Ah, maldição... Tem muitas outras coisas pra fazer no Caribe. Tchau.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Maravilha! Vou ficar com o dedo para mim. Agora, vamos ver o que tem nos bolsos dele. Vamos dar uma olhada no que você trouxe.";
			link.l1 = "Vá em frente, dê uma olhada...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, era só isso que eu precisava. Muito bem! Você fez um ótimo trabalho. Estou muito satisfeito com você.";
				link.l1 = "Obrigada! Sempre é bom receber elogios por um trabalho bem feito.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Eu te avisei, eu sei do que o Rodriguez nunca abriria mão. E não vejo o que preciso aqui. Você pegou essas coisas? Perdeu elas? Tanto faz. Não quero mais me envolver com você. Cai fora daqui.";
				link.l1 = "Ah, maldição...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Aqui está sua recompensa conforme prometido, trinta mil. E também tenho uma tarefa extra, de alta responsabilidade e alto risco, mas o pagamento será proporcional: 40.000 pesos.";
			link.l1 = "Estou ouvindo. Quem é o próximo cliente?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Desta vez, você vai caçar não um homem, mas um objeto. Você deve se infiltrar na casa de Richard Fleetwood, em Antígua, e roubar seu diário de bordo. Ele é um capitão inglês. O lugar é bem guardado, e o próprio Richard raramente visita a casa\nO plano é simples. O governador de St. John's vai organizar uma festa privada em dez dias, e Fleetwood estará presente. Você precisa entrar na casa dele à noite, entre uma e três horas. Só haverá um soldado lá dentro\nDê um jeito nele. Procure o diário no apartamento do Richard. Pegue esta chave.";
			link.l1 = "Hm... Interessante. Entendi o que preciso fazer. Estou pronto para começar!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Tome cuidado. Não entre na casa antes da data que eu te indiquei. Caso contrário, no melhor dos casos, vão só te expulsar, e no pior, você vai acabar atrás das grades. Repita para mim a data e o horário.";
			link.l1 = "Daqui a exatamente dez dias, entre uma e três da manhã.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Tudo bem. Pode ir. Boa sorte!";
			link.l1 = "Obrigado, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Não, não conheço. Temos herbalistas e médicos, mas nenhum com esse nome.","É a primeira vez que ouço um nome tão estranho. Não, nunca recebemos a visita do homem de quem você fala.","Não temos nenhum tipo de alquimista por aqui. Temos médicos, mas nenhum com um nome tão estranho.");
			link.l1 = "Entendi. Que pena. Vou continuar procurando!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
