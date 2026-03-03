// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo, qual é a pergunta?"),"É a segunda vez que você tenta perguntar...","É a terceira vez que você tenta perguntar de novo...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda insiste em fazer perguntas!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"É verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, I have found a bandit's corpse in the jungle. He was killed by the Indians. There were earrings on his body; looks like they were brought here from Europe. Perhaps they belonged to one of the nobles in your town?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Vossa Excelência, a tarefa está cumprida! Contudo, lamento informar que o criminoso não sobreviveu ao confronto e, portanto, não enfrentará a execução.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Vossa Excelência, a tarefa está concluída! O prisioneiro aguarda seu destino em minha cela.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Cheguei por ordem do Governador-Geral Philippe de Poincy para assumir o comando da sua fragata armada.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Estou pronto para incorporar a fragata ao meu esquadrão.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Vim a seu convite, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Isso foi lamentável, Monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Vossa Excelência, obtive informações sobre um comércio ilícito que em breve ocorrerá nestas terras. Atrevo-me a dizer que este assunto pode ser digno de sua atenção.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Vossa Excelência, venho em busca de notícias sobre aquela embarcação de contrabando de que falamos.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Vamos ver o que você trouxe... Incrível! Simplesmente incrível, Charles! Esses são os brincos da minha esposa. Eu os dei a ela antes de deixar a Europa e vir para as colônias. Eles desapareceram há alguns meses em circunstâncias misteriosas. Eu sabia que tinham sido roubados!   Charles, fico muito feliz que você tenha vindo direto a mim, e não vendido algo de tanto valor para mim aos mercadores. Vou recompensá-lo por esse favor. Ouvi dizer que você pretende comprar um navio? Já que decidiu se lançar ao mar, sem dúvida vai precisar de um mapa do nosso arquipélago. Aqui, fique com ele. Tenho certeza de que será útil!";
			link.l1 = "Obrigado, Vossa Graça!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Que pena, Charles, mas precisamos lidar com a situação como está. Aqui está sua recompensa: cinco mil pesos, já descontados os impostos.";
			link.l1 = "É uma honra servir St. Pierre e a você pessoalmente. Apesar de a batalha ter sido difícil, confesso que até aproveitei um pouco.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Foi uma batalha difícil, Vossa Excelência. Meu navio sofreu danos consideráveis. Seria possível me compensar pelas minhas perdas?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles! Não tenho dúvidas de que você irá longe em nossas fileiras.";
			link.l1 = "Até nos encontrarmos novamente, Vossa Excelência.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Devo dizer que estou um pouco surpreso com seu pedido, Charles... Muito bem, considere mais dois mil pesos de minha parte, como um gesto de boa vontade. Adeus.";
			link.l1 = "Obrigado, Vossa Excelência.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Excelente, Charles! Fico feliz em informar que seu sucesso vai ajudar seus amigos malteses numa operação delicada... Aqui está sua recompensa: oito mil pesos, já descontados os impostos.";
			link.l1 = "É um prazer servir a St. Pierre, à Ordem e a você pessoalmente. Embora a luta tenha sido difícil, encontrei certa satisfação nela.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Foi uma batalha difícil, Vossa Excelência. Meu navio sofreu danos consideráveis. Posso solicitar uma compensação pelas minhas perdas?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! Tenho certeza de que você irá longe.";
			link.l1 = "Até nosso próximo encontro, Vossa Excelência";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Acho que você merece. Fique com mais dois mil por minha conta, como um gesto de boa vontade. Obrigado, meu amigo.";
			link.l1 = "Obrigado, Vossa Excelência.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "O navio está pronto, mas você não tem um espaço livre para ele em seu esquadrão. Capitão, reduza seu esquadrão e volte, então eu lhe entregarei a fragata imediatamente.";
				link.l1 = "Certo.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Sim, é claro, o navio está pronto para zarpar. O capitão está ciente e seguirá todas as suas ordens.";
				link.l1 = "Então estamos partindo. Adeus, Vossa Graça.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excelente. Prepare-se para receber seu novo navio. O capitão já está ciente e seguirá todas as suas ordens.";
			link.l1 = "Então estamos partindo. Adeus, Vossa Graça.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Capitão Charles de Maure, finalmente! Estive esperando ansiosamente por você! Por favor, entre, junte-se a mim.";
			link.l1 = "Bom dia para o senhor também, Vossa Excelência. Sempre há um motivo por trás de tanta cortesia de sua parte. O que é desta vez? Piratas, espanhóis, canibais índios?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Não seja irônico, Capitão. Não é culpa minha que nós dois sempre acabamos nos metendo em encrenca. Mas, por favor, não se preocupe, desta vez não vai ter tiroteio... provavelmente.";
			link.l1 = "Você me intriga, continue. Como posso ajudar?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Já ouviu falar do refinado estabelecimento da Madame Botot? Durante o cerco, nosso... bordel foi reduzido a cinzas. Um dia, uma certa dama se ofereceu para reconstruí-lo.";
			link.l1 = "Um incêndio num bordel e eu de fora? Aliás, levei um tiro dos espanhóis naquele dia também.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Que diabos, Charles, o que há de errado com você hoje? Seu senso de humor está fora de lugar! Mesmo que não seja um assunto de Estado, ainda assim é algo importante, para mim, pessoalmente! Preciso da sua ajuda! Pelo amor de Deus, se controle e me escute!";
			link.l1 = "Perdoe-me, Vossa Excelência. Sinto um enorme alívio, só isso. Para ser sincero, cansei de toda essa luta e conflito constantes. Achei que o senhor fosse me arrastar para mais um ciclo de violência. Por favor, continue. Nunca ouvi falar dessa Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Certo, esta dama honrada elevou o estabelecimento a um novo patamar. Agora é um lugar de alta e nobre sociedade, não mais um buraco imundo como antes. Um local de vícios refinados, vinhos caros e jogos de azar sem limites. Você verá tudo com seus próprios olhos!";
			link.l1 = "Vossa Excelência, não sou nenhum puritano e sua descrição foi bastante vívida, mas por que está me contando isso?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Porque você está na lista, por que mais?! Olha, eu me sinto culpado por causa da Marquesa e prometi te apresentar a ela em uma das festas dela amanhã. Juliana não faz isso com frequência, então, por favor, seja gentil e venha conosco. Sem brigas, tiros ou perseguições desta vez, eu prometo. Tudo será cortês e digno: vinho, belas mulheres, cartas e outros prazeres nobres.";
			link.l1 = "Cartas e prostitutas. Faz tempo, foi em outra vida. Mas ainda não entendi onde você quer chegar. Por que eu?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Está surdo? Juliana Botot, ela... coleciona rostos brilhantes e famosos. São eles que tornam suas festas especiais e sempre renovadas. Você já construiu uma reputação, e a marquesa esperou muito tempo para tê-lo como convidado. Meu deslize lhe deu uma chance, e não vou insistir se ela se recusar a me receber de novo. É tudo o que vou conseguir se não levar você até ela!";
			link.l1 = "Vossa Excelência, o senhor é um viúvo atraente e um governador... Por que se preocupar com a opinião de uma cortesã? São elas que deveriam buscar o seu favor, não o contrário.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "A marquesa Botot está sob a proteção do conde Henry de Levi-Vantadur – que, pela graça de Sua Majestade, é o chefe dos estados da Nova França na América do Norte. Acredite em mim, Charles, ninguém aqui quer se indispor com ele.";
			link.l1 = "Por pouco você não me enganou – achei que tudo isso era só desejo e paixão. Agora vejo que era política o tempo todo. Trivial, mas previsível. Muito bem, vou ajudá-lo. Vai ser doce reviver os dias da minha juventude, nem que seja por uma noite.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Capitão, você é um homem experiente, sem dúvida, mas não tente fingir ser um velho. Não se trata apenas de política. Eu valorizo muito a presença de Juliana e sou grato pela sua ajuda. Isso é importante para mim, de verdade. Venha à casa da Marquesa Botot depois do anoitecer, amanhã. Prometo que a política não vai estragar a noite.";
			link.l1 = "Vinho, cartas, mulheres. Como nos velhos tempos. Adeus, Vossa Excelência!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, o que aconteceu, você está péssimo!";
			link.l1 = "Angerran, maldito Chievous, Excelência. Ele roubou minha fragata ontem à noite. Executou minha tripulação de prêmio e partiu na neblina.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "É uma reviravolta desagradável, eu entendo, mas confie em mim — esse desfecho é bastante satisfatório. Você não está desesperado por navios e homens, enquanto de Levi Vantadour pagará uma quantia significativa para esconder a verdade sobre um certo duelo recente. Ou ele se lembrará do nosso papel em ocultar isso de graça, o que também vale muito. De Chievous agiu de forma desonesta duas vezes, mas agora está longe, enquanto ainda temos boas cartas para jogar contra ele.";
			link.l1 = "Três vezes, Vossa Excelência. Angerran admitiu que trapaceou no nosso jogo de cartas. Mas ele não vai me pagar com dinheiro, se é isso que está pensando. Ele passou dos limites. Havia uma certa pessoa naquele navio esta manhã... ela é muito querida para mim! Não vou deixar aquele canalha fazer nenhum mal a ela! Ouviu isso, Jacques, eu não vou permitir!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Acho que sei de quem você está falando – lembro de ter visto você com uma... moça, vestida como homem e armada até os dentes feito uma pirata. Charles, não seja tolo! Você teve sorte, escapou de uma encrenca enorme e agora o quê, quer se meter nisso de novo? Deixe pra lá. De Chievous está fugindo – graças a Deus! E quanto à sua 'companheira de armas' – ouça o conselho de um amigo – vá ver a Julianna e esqueça tudo isso.";
			link.l1 = "Fora de questão, excelência. Tem coisas que estão além da sua compreensão, está bem? Agora me diga tudo o que sabe sobre esse desgraçado. Para onde ele poderia ter ido depois de Saint Pierre? E não tente me dissuadir de novo – já enfrentei a Companhia Holandesa, desafiei barões piratas, governadores-gerais, até mesmo a Santa Inquisição! Não sou homem fácil de intimidar. Vou trazê-la de volta, custe o que custar!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, have you ever given any thought to the question of who appoints governor-generals? This is an entirely different world! You have barely scratched its surface; it is beyond your understanding, you are like a child in a gunpowder store. And you are asking me to hand you a lit candle. As for governor-generals: de Poincy himself never crosses the count, neither in matters of coin nor in matters of politics. Vice King, the term so popular among the commoners, would suit Henri de Lévis Ventadour just fine.";
			link.l1 = "E aqui estou eu, planejando acabar com o único herdeiro homem dele. Sei muito bem o risco que estou correndo. Agora, só me diga: tem alguma coisa útil que você sabe e que possa me ajudar?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "On any other day, I would take you reaching for your pistol as the end of our friendship, Charles. But I understand your current state of mind. That is why I am willing to let this go. I know nothing useful to you; the frigate sailed west early this morning. You should pay a visit to the Marquise... Wait, not like that! Julianna knows a great deal about your enemy, and she was personally... acquainted with his father for some time. Ask her. Unlike me, she won't try to stop you.";
			link.l1 = "Esse é o plano. Até logo, Excelência. Obrigado pelo seu tempo.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Mercadorias de contrabando, diz você? Hmm... muito intrigante. Por favor, esclareça-me com os detalhes da sua descoberta.";
			link.l1 = "Três dias atrás, uma embarcação carregada de contrabando deveria ancorar na Baía de Le Marin. O navio não apareceu no encontro, mas tenho bons motivos para acreditar que ainda chegará ao porto em breve. Talvez seus homens possam preparar uma recepção adequada para esses bandidos quando chegarem, Vossa Excelência.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "Uma embarcação sem nome transportando uma carga desconhecida... E você presume que eu deva enviar as forças de Sua Majestade com base em informações tão vagas?";
			link.l1 = "Vossa Excelência, reconheço que os detalhes são escassos. Mas, por favor, permita-me relatar como esta informação chegou ao meu conhecimento. (Cena)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Muito bem, vamos pôr sua inteligência à prova. Se de fato uma embarcação carregando contrabando lançar âncora nas costas de Le Marin, você será generosamente recompensado por seu serviço à Coroa. Volte a mim em três dias. Até lá, a névoa da incerteza terá se dissipado.";
			link.l1 = "Excelente. Então, nos vemos em três dias.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, Capitão! É um prazer recebê-lo mais uma vez. Sua informação foi realmente valiosa. Meus homens interceptaram a embarcação exatamente onde você indicou. Aqui estão — cento e cinquenta dobrões espanhóis, recém-cunhados e pesados na bolsa. Aceite-os com minha gratidão.";
			link.l1 = "Meus humildes agradecimentos, Vossa Excelência. É uma sorte que minha pequena informação tenha servido aos interesses da Coroa. Se surgir outra oportunidade, saiba que meu braço armado e meu olhar atento continuam à sua disposição.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
