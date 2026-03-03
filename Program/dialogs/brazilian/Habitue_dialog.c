#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Seleção do tipo de bêbado (beta)";
			link.l1 = "Bêbado";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Jogador de cartas";
			link.l2.go = "Beta_test_card";
			link.l3 = "Jogador de dados";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Bêbado selecionado";
			link.l1 = "Continuar";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Jogador de cartas (30% de chance de se irritar imediatamente)";
			link.l1 = "Continuar";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Jogador de dados (30% de chance de se ressentir imediatamente)";
			link.l1 = "Continuar";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Eu posso até estar bêbado, mas não sou idiota. Se eu beber com você agora, os soldados vão me pegar no dia seguinte. Nem pensar!","Eu não sou inimigo da minha própria cidade. Não vou beber com você!",""+GetSexPhrase("companheiro","moça")+", é melhor você sair daqui enquanto ainda pode...");
				link.l1 = RandPhraseSimple("Bem, como quiser...","Heh, sabe, não preciso ficar bêbado assim. Não é o momento certo pra isso."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, senhorita"+GetSexPhrase("ter","s")+", com certeza, já ouvi falar de você, he-he. O pessoal nas tavernas diz que você é encrenqueiro e duelista. Eu digo que nossa gente não se assusta fácil, mas ninguém quer morrer por uma caneca de rum. Só de sentar perto de você já fico desconfortável, então é melhor eu recusar.";
				link.l1 = LinkRandPhrase("Então, já vai tarde!","Cai fora, enquanto ainda estou de bom humor...","Vai, vai! Cai fora, comida de peixe!");
				link.l1.go = "exit";
				link.l2 = "Espere, eu queria fazer uma pergunta...";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Não fique na minha frente, não consigo ver as moscas na caneca!";
            link.l1 = "Eu não estou de pé...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hic! Oh, "+GetSexPhrase("amigo, você com certeza parece um marinheiro experiente","moça, você com certeza parece uma velha lobo do mar")+"! Talvez você pudesse me pagar um copo de rum?";
						link.l1 = "Posso até ser um velho lobo do mar, mas isso não quer dizer que vou pagar bebida pra vagabundo...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Eu adoraria me juntar à sua companhia.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "E por que isso?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Uma partida de cartas, talvez? Um jogo bem interessante!","Que tal jogarmos uma partida de cartas? O que me diz?");
										link.l1 = "E por que não? Claro, vamos jogar.";
										link.l1.go = "Cards_begin";
										link.l2 = "E quais são as regras do seu jogo?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Agora não.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Não, não vou mais jogar cartas com você.";
						    			link.l1 = "Como você disser.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Uma partida de dados, talvez? Um jogo bem interessante!","Que tal jogarmos uns dados? O que acha?");
										link.l1 = "E por que não? Claro, vamos jogar.";
										link.l1.go = "Dice_begin";
										link.l2 = "E quais são as regras do seu jogo?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Agora não.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Não, não vou mais jogar dados com você.";
					    				link.l1 = "Como você disser.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Você estava trapaceando!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Saia da minha mesa! Agora!"," Oh? O quê? Quem é? Hic... Cai fora!");
	                        link.l1 = RandPhraseSimple("Beber condena sua alma pecadora! Caia em si!","Não seja grosseiro comigo.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Olha como fala, seu cachorro! Ou eu te ensino a ter respeito.","E se eu te der uma pancada na cabeça agora, acho que isso vai te ajudar a ficar sóbrio.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Não vou te contar nada, moça"+GetSexPhrase("ter","s")+"! E eu duvido que mais alguém vá querer conversar com você, já que isso sempre traz problemas. Mas, olha, as pessoas costumam ter memória curta, então daqui a um mês ou dois talvez esqueçam da sua aventura, se você não fizer questão de lembrar, claro, he-he! Adeus, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "Certo...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Bem, então vamos começar...";
			link.l1.go = "Cards_begin";
			link.l3 = "Não, não é para mim...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Então vamos definir a aposta primeiro (insira a aposta).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Acho que tenho que ir.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Você é um trapaceiro notório. Não vou jogar com você.";
                link.l1 = "É tudo mentira! Bom, tanto faz.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Vejo que você está sem um tostão, "+GetSexPhrase("amigo","querida")+". Volte quando estiver rico.";
                link.l1 = "Certo.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Já perdi tudo o que tinha. Hoje não é meu dia de sorte.";
                link.l1 = "Certo.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Você está rindo de mim ou o quê?! Está brincando de "+iLa_Puesta+" pesos?! Vamos jogar por apostas razoáveis, ou tô fora!";
				link.l1 = "É, você tem razão. Precisamos aumentar um pouco as apostas.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Mudei de ideia, não vou jogar.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Jogar por uma quantia tão alta? Não, vou deixar passar, a menos que mudemos a aposta.";
				link.l1 = "É, você tem razão. Precisamos diminuir um pouco a aposta.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Na verdade, decidi não jogar mesmo.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Certo, vamos jogar por "+iLa_Puesta+" moedas.";
			link.l1 = "Distribua as cartas!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Então, qual é a aposta? (Digite a aposta)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Acho que no fim das contas não vou jogar...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Bem, então vamos começar...";
			link.l1.go = "Dice_begin";
			link.l3 = "Não, não é para mim...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Vamos fazer a aposta (insira o valor).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Acho que tenho que ir.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Você é um trapaceiro notório. Não vou jogar dados com você.";
                link.l1 = "É tudo mentira! Bom, tanto faz.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Vejo que você está sem um tostão, "+GetSexPhrase("amigo","querida")+". Volte quando estiver rico.";
                link.l1 = "Certo.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Já perdi tudo o que tinha. Hoje não é o meu dia de sorte.";
                link.l1 = "Certo.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Você está rindo de mim ou o quê?! Está brincando de "+iLa_Puesta+" pesos por dia?! Vamos jogar por apostas razoáveis, ou tô fora!";
				link.l1 = "É, você tem razão. Precisamos aumentar um pouco as apostas.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Mudei de ideia, não vou jogar.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Jogar dados por uma quantia tão alta? Não, vou passar, a menos que mudemos a aposta.";
				link.l1 = "É, você tem razão. Precisamos diminuir um pouco a aposta.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Na verdade, decidi não jogar mesmo.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Certo, vamos jogar por "+iLa_Puesta+" moedas por dado.";
			link.l1 = "Vamos nessa!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Então, qual é a aposta? (Digite o valor)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Acho que no fim das contas não vou jogar...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Bem, h-hic! As coisas vão bem. Hic! Você nem percebe chegando. Hi-ic! Esse rum é bom. Rum preto da Jamaica. hic!\nAqui, sirva-se de uma dose!";
			link.l1 = "Certo, por que não.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Desculpe, amigo, eu preciso ir.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Canecas e rostos vão e vêm... Hic... Até eu cair no chão. Eu bebo o tempo todo... Hic! Cadê a bebida... E qual é a graça disso...";
			link.l1 = "A bebida está aqui e as garotas são bonitas, todas querem um bucaneiro, mas só o rum parece ser meu.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Não tenho tempo para isso.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Quando estiver triste, não tente pensar, venha aqui, vamos beber! Tudo vai ficar bem, sou seu amigo, e você é meu também!";
			link.l1 = "Ter um amigo é mesmo bom, quando você se vai ele espera, com um amigo não há rancor, mas quando o rum acaba só sobra discussão. Então vamos beber, camarada, antes que eu vá e me atrase... ";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Hic! Agora sim! Bem melhor! E aí? Vai me pagar um rum ou não?","Sente-se, "+GetAddress_Form(npchar)+", vamos tomar um gole de bom e velho rum jamaicano. Isso nunca faz mal à saúde. E se você quiser saber das novidades - não há lugar melhor do que esta taverna, pode acreditar. Um pouco de dinheiro, umas doses de rum decente - e você vai descobrir tudo o que precisa saber, e até mais, confie num velho frequentador...","Heh, por favor, sente-se, "+GetSexPhrase("meu bom amigo","senhorita")+", vamos tomar um drink... Por que não aproveitar uma bebida em boa companhia? Dá pra ouvir muita coisa interessante se você for paciente e beber devagar, em pequenos goles... Tem capitão se gabando das próprias aventuras, e muitos outros deixando escapar coisas importantes quando perdem o controle... Muita gente passa o tempo lá, e muitos têm algo pra contar, pode acreditar, "+GetSexPhrase("meu bom amigo","Senhorita")+".");
			link.l1 = "E por que não! Barman! Rum para nós dois!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Claro! Você sabia... até igrejas estão sendo saqueadas por bandidos!";
				link.l1 = "Bem, isso parece coisa de pirata, quem mais...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Que piratas? Só uns marujos de terra firme, e com certeza esses malditos locais... Se fossem de fora, não saberiam quando os cofres da igreja estavam cheios. E dificilmente teriam se metido nessa encrenca, de qualquer jeito.";
				link.l1 = "Rapazes ousados, isso com certeza. Eles abriram com tanta valentia uma tranca de porta tão frágil...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. E espertos também. Quem se arriscaria desse jeito?";
				link.l1 = "É verdade. Toda a paróquia estava juntando dinheiro para doar à igreja, e agora esses espertalhões fizeram fortuna com isso? Com certeza vão ser pegos. Agora todo mundo vai estar atrás deles.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Duvido muito. Quem vai procurar por eles? Eles acabaram de roubar a igreja e sumiram da cidade, desapareceram como o vento. A mata é enorme, enorme mesmo, você ficaria procurando por eles lá até o fim dos tempos. E depois de alguns meses, ninguém mais vai se lembrar disso, pode apostar!";
				link.l1 = "Acho que não. Certas coisas não podem ser perdoadas.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "A memória de um homem é como uma canoa furada. As pessoas esquecem e perdoam. Mas Deus?! Ele vê tudo. É d'Ele que você deve ter medo. Olha, faz uns dez anos aconteceu uma coisa terrível com um velho camarada meu. Ele também não tinha respeito pelo Criador, e por pouco não foi direto pro diabo do mar...";
				link.l1 = "Desculpe, amigo, preciso ir. A gente fala sobre esse seu camarada outra hora. Até mais.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Claro, eu lembro desse cara... Não, eu não sei. Mas, olha, você pode perguntar pra nossa garçonete sobre ele. Enquanto ele morou aqui, ela passou todas as noites com ele. Aquela ali é uma vadia, com certeza. Talvez ele tenha contado alguma coisa pra ela.";
				link.l1 = "Valeu pelo conselho, amigo. Vou lá falar com ela.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "É, coisas muito estranhas podem acontecer em alto-mar às vezes. Na minha última viagem eu vi algo rea-lmente...";
				link.l1 = "Vai em frente, me conte, só não exagera demais. Enquanto isso, vou buscar mais rum pra você.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Eu juro por Deus, nobre"+GetSexPhrase("senhor","senhora")+" - Eu vi com meus próprios olhos... Um navio navegava, mas em vez de marinheiros havia uns macacos enormes... ou macacos-prego... macacos, sabe.";
				link.l1 = "O quê?! Me diga, amigo, você também está bebendo de plantão?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Que eu fique cego se estiver mentindo! Nunca ouviu falar do camarão macaco? Maldição, camarão ha-ha! ... O navio macaco.";
				link.l1 = "Que navio de macaco?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh-ho, eu te digo, eu vi com meus próprios olhos. Havia uma tempestade. Não dava pra enxergar nada, e então o navio apareceu do nada. Velas rasgadas. A vela de proa estava quebrada, assim como a vela principal, e por Deus, tudo estava destruído! E mesmo assim ela avançava contra o vento!\nE tinha macacos no convés... um monte deles, parecia até uma colônia de focas! E um gorila de verdade estava no leme! Tinha quase três metros de altura, camisa vermelha, e dentes de tubarão no lugar de uma cruz no peito... Os olhos brilhando em vermelho, presas reluzentes, ele nos viu e gritou alguma coisa...";
				link.l1 = "Você está mentindo descaradamente, amigo. Sabe, a gente vê cada coisa quando está bêbado. Daqui a pouco vai me dizer que ela era o Holandês Voador.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Não, ela não era holandesa. Estou dizendo a verdade! Era uma barca, e na popa havia uma inscrição - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Maldição! Acho que já sei de quais 'macacos' você estava falando. Realmente, o rum solta a língua — é só prestar atenção...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Tá vendo – eu te disse! E você não acreditou em mim!.. Tá bom, vamos virar mais uma, depois eu tô pronto pra ir.";
				link.l1 = "Certo, obrigado por compartilhar essa história interessante. Preciso ir agora. Boa sorte pra você, camarada.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "Não, capitão. A vida de marinheiro não é pra mim. Sabe, eu também já tive um navio, mas... tive um azar danado.";
			link.l1 = "Escute – vi um navio incomum ancorado ao largo – 'Meifeng' é o nome dela. Nunca vi um navio assim antes. De quem será? Talvez esteja à venda? Gostaria de dar uma olhada.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Que nada, capitão. Duvido que aquele chinês vá vender o navio dele pra você ou pra qualquer um.";
			link.l1 = "Um chinês? Existem chineses em Curaçao? E ainda por cima capitão do próprio navio?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Tem sim, como você pode ver. Mas na verdade, esse navio não é dele – pertence à Companhia de Comércio. Dizem que o senhor Rodenburg, o vice-diretor e agora governador interino, é o dono.";
			link.l1 = "Então, Matthias Beck se aposentou?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Mynheer, você realmente deveria visitar a terra com mais frequência – ou pelo menos se manter informado das novidades. Matthias Beck foi destituído e jogado atrás das grades até que tudo seja esclarecido.";
			link.l1 = "Não me diga! Realmente, tenho passado tempo demais no mar. E quando foi que isso aconteceu?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Actually, just a couple of days ago. A courier brigantine arrived in port. It was not in the best shape; clearly, it had participated in fierce combat. The captain went straight to mynheer Rodenburg with his report, and in just a few hours Matthias Beck was arrested by mynheer Rodenburg and the commandant on suspicion of collaborating with English intelligence.";
			link.l1 = "Você está dizendo coisas terríveis. Como o governador de Curaçao pode ser um espião inglês?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Francamente, eu mesmo mal posso acreditar. Ouvi dizer que em breve o diretor da Companhia, o próprio Peter Stuyvesant, vai chegar aqui. Pelo visto, ele vai conduzir a investigação pessoalmente.";
			link.l1 = "Então você está certo. Pode ser arriscado incomodar o senhor Rodenburg neste momento.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Boa ideia, capitão! Ainda mais agora que a 'Meifeng' está sendo carregada. Ela acabou de voltar de uma viagem à costa sul do continente, e logo vai zarpar de novo. E, olha, coisas estranhas estão acontecendo por lá. Marinheiros holandeses e guardas da Companhia foram dispensados, e estão montando outra tripulação. E eu juro por todas as canecas de rum que já bebi na vida, esses novos voluntários são de outro tipo, só piratas, bandidos e assassinos!";
			link.l1 = "Um milagre, de fato! Que pena! Um navio tão bonito... Bem, o destino quis diferente... Obrigado pela história interessante e pelas novidades! Foi um prazer conversar com você!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Bem, obrigado pela companhia e pelo rum, capitão! Apareça de novo qualquer hora!";
			link.l1 = "Claro que vou!";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? Eu sei, eu sei... Esse seu colega é bem antissocial. Um lobo solitário, por assim dizer. Ele navega com seu bote ao longo da costa da ilha o dia todo, até anoitecer. O pessoal acha que ele é pescador, mas na verdade ele mergulha atrás de pérolas... Heh! Eu sei disso, com toda certeza!";
				link.l1 = "Hein! Então... pode me dizer onde posso encontrá-lo?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Não, juro que nunca ouvi falar dele... Mas você - Hic! Pode perguntar ao nosso barman - ele deve saber com certeza!";
				link.l1 = "Hum... Tá bom, vou perguntar mais por aí. Valeu pela companhia, camarada. Até mais!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Claro, posso sim! Todas as manhãs ele pode ser encontrado na praia, em "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Só venha o mais cedo possível, senão ele zarpa e você vai ter que esperar até a manhã seguinte.";
			link.l1 = "Obrigado! Você me ajudou muito, amigo! Até mais!";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "Ele estava rondando nosso estaleiro, fazendo perguntas aos carpinteiros navais sobre uma coisa e outra. E foi isso que acabou prejudicando ele. Algumas pessoas avisaram o comandante sobre gente suspeita circulando pela cidade, então ele foi detido, e depois descobriram que ele não era comerciante coisa nenhuma.";
			link.l1 = "Imagino que ele estava planejando roubar algum projeto secreto do seu construtor naval?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Quem sabe? Mas tenho quase certeza de que ele estava interessado no galeão 'Alacantara' desde o começo! Hic! Eu posso jurar! Esse navio está sendo equipado pelo próprio Senhor Governador, então aposto que aquele canalha tentou descobrir alguma coisa sobre ela.";
			link.l1 = "Ha! Isso é bem provável. Com certeza o governador vai carregar ela com algo valioso...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Isso nem precisa dizer! Deve ser algo realmente digno de atenção, eu te falo! Ah, e ouvi dizer que os pescadores viram um navio de guerra estrangeiro nessas águas... provavelmente uma fragata. Talvez seja de lá que veio aquele espião?";
			link.l1 = "É, pode ser... Certo, amigo, obrigado pela companhia, mas eu tenho que ir!";
			link.l1.go = "exit_sit";
			Trial_Habitue_DlgExit();
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "À sua saúde e à sua generosidade!";
				link.l1 = "Amigo, você viu um chinês pela cidade?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("amigo de verdade","grande moça")+"! Prazer em te conhecer! Saúde!","Hic! Esse rum é ótimo! Hic... Saúde!","À sua saúde e à sua generosidade!");
			link.l1 = "Heh, esse rum é forte mesmo. Certo, preciso ir. Aproveite!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Mais uma taça, você se importa?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Parece que passei uma eternidade no mar. Alguma novidade?","O que dizem por aí? Com certeza, eu vou te pagar umas bebidas.","Me conta, camarada, quais histórias estão em alta nas tavernas ultimamente?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! Uma ideia esplêndida!";
					link.l1 = "Barman! Mais rum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "Pra você! Ah, droga! Quem é esse?";
					link.l1 = "Hã? O quê? Onde? Acho que estou vendo coisas.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Então vamos beber! Mais uma?";
					link.l1 = "Vai em frente!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Ei, você, "+GetAddress_Form(NPChar)+", você com certeza acha que todo mundo te admira, né? Pois se quer saber, pra mim você não passa de um bandoleiro qualquer!.. E um assassino! 'Nobre pirata'! Ha! Bandido é bandido... Hic... Seja em terra ou no mar..","Hic! "+GetSexPhrase("Ca... Canalha","No... Nojento")+"! Você quer que eu beba até desmaiar - hic - e aí vai roubar todo o meu dinheiro!");
						link.l1 = "Já vi que você já bebeu demais... Vai dormir pra passar... E eu preciso ir...";
						link.l1.go = "exit_sit";						
						link.l2 = "Não gostei do seu tom, camarada. Cuidado com o que fala, certo?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Quem você acabou de chamar de bandido, seu marinheiro de terra?! Quero ver o que vai dizer com um buraco na barriga!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Calma! Esqueceu? Eu sou seu único amigo de verdade!";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Por que está me encarando? Vai esperar eu desmaiar - hic - e depois vai roubar todo o meu dinheiro! De onde saiu toda essa ralé?! Hic... Não tem espaço pra uma pessoa decente nessa taverna?","Você me respeita?.. É, você mesmo! Você me respeita?! Fica esperto... Não sou alguém com quem se brinca... Um soco bem no meio da cara... E você já era...");
							link.l1 = "Amigo, você está bêbado feito um porco. Vai pra casa dormir... E eu também preciso ir...";	
							link.l1.go = "exit_sit";
							link.l2 = "Calma aí, camarada. Preste atenção com quem está falando.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "O que você acabou de dizer?! Vou te ensinar uma lição!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Calma! Já esqueceu de mim? Eu sou seu único amigo de verdade!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Escute! Você é um bom homem! Talvez possa me ajudar... com uma certa questão?";
					link.l1 = "Não, acho que preciso ir agora.";
					link.l1.go = "exit_sit";
					link.l2 = "Claro! Hic! Somos amigos... não somos? Hic!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...E então eu a-agarrei o sabre dele pela l-lâmina...";
						link.l1 = "...e então ela disse...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...E então eu a-agarrrei a lâmina do sabre dele...";
						link.l1 = "...hic! ...e então ela disse...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "O p-ponto é q-que um dos s-soldados me insultou. S-Só isso!";
			link.l1 = "Um s-soldado? N-não, acho melhor deixar pra lá.";
			link.l1.go = "exit_sit";
			link.l2 = "Calma! Já se esqueceu de mim? Eu sou seu único amigo de verdade!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Você? Que tipo de amigo é você? N-não! Você... você quer me matar! É isso mesmo!";
			link.l1 = "Bem, com certeza você já bebeu o suficiente. Até logo.";
			link.l1.go = "exit_sit";
			link.l2 = "O quê? Eu vou te provar que eu n-não vou te matar! Eu... eu vou cortar sua mão!... S-sem ela, você não pode ser morto!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Leve "+GetSexPhrase("ele","ela")+" afaste-se de mim!";
			link.l1 = "Calma... hic... Não vai doer!... É menos dolorido que fazer a barba!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Não tente me intimidar! Hic! Não me assusto tão fácil assim!.. E você – você devia estar pendurado na forca... Junto com todos os seus – hic! Pode se exibir o quanto quiser – mas ainda fede a peixe podre! E eu não vou medir as palavras quando – hic! – falar com gente como você! Todos vocês me dão nojo!";
			link.l1 = "Argh, por que estou perdendo tempo falando com um bêbado desses... Acho melhor eu sair pra tomar um pouco de ar fresco...";
			link.l1.go = "exit_sit1";
			link.l2 = "Você é atrevido demais, camarada. Vou enfiar suas palavras de volta na sua garganta!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "O quê?! Eu vou te estrangular com as minhas próprias mãos! Hic... Ninguém escapou de mim - hic! - até agora!";
			link.l1 = "Você não é um porco bêbado? Pra estragar uma noite tão boa... Tá bom, vai caçar suas baratas - eu tô fora daqui.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Vejo que você não vai ficar quieto. Muito bem, então está na hora de te ensinar boas maneiras.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Chegue mais perto, seu canalha! Você vai receber o que merece!",RandSwear()+"Eu vou te dar o que você merece!","Ha! Muito bem, lobo do mar - vamos ver como você se sai em terra firme!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Juro que você vai se arrepender!","Vou cortar essa sua língua suja para poupar os ouvidos!"),RandPhraseSimple("Vou te abrir de cima a baixo, do rabo até esse buraco imundo que você chama de boca!","Juro que vou fazer você calar a boca!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Ei, rapazes! Vamos varrer esse lixo da nossa cidade!";
				link.l1 = RandPhraseSimple(RandSwear()+"Façam suas orações, desgraçados!","Oh, então você não está sozinho?! Que bom pra você – vai ter companhia no inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Chegue mais perto, seu canalha! Você vai receber o que merece!",RandSwear()+"Eu vou te dar o que você merece!","Ha! Certo, lobo do mar - vamos ver como você se sai em terra firme!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Juro que você vai se arrepender!","Vou cortar essa sua língua suja até as orelhas!"),RandPhraseSimple("Vou te abrir igual a um porco, do rabo até esse buraco imundo que alguns chamam de boca!","Juro que vou fazer você calar a boca!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Ei, rapazes! Vamos varrer esse lixo da nossa cidade!";
				link.l1 = RandPhraseSimple(RandSwear()+"Façam suas orações, bastardos!","Ah, então você não está sozinho?! Que bom pra você – vai ter companhia no inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "Ei, não entendi! Assim que virei a esquina, um novato já pegou meu lugar. Cai fora daqui!";
			link.l1 = "Sempre a mesma coisa: você senta à mesa, e descobre que ela já está ocupada... Fique aí, eu já estava de saída mesmo.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Mais uma frase dessas saindo dessa sua boca imunda e vai ser a última coisa que você vai dizer, entendeu?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Eu não sei se este lugar era mesmo seu, mas não vou deixar você falar assim comigo. Cuidado com as palavras.";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Vamos lá, canalhas! Vocês estão prestes a se fartar!",RandSwear()+"Agora vou te despir de verdade!","Ha! Vamos lá, marinheiro - quero ver do que você é capaz em terra firme!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Juro que você vai se arrepender disso!","Vou arrancar essa sua língua maldita!"),RandPhraseSimple("Vou te abrir de cima a baixo, das suas tripas até esse buraco imundo que você chama de boca!","Juro que vou fazer você calar a boca!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Vamos lá, pessoal! Vamos tirar essa escória da nossa cidade!";
				link.l1 = RandPhraseSimple(RandSwear()+"Rezem, seus bastardos!","Ah, você não está sozinho! Bem, vai ter companhia no inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Vamos lá, canalhas! Vocês estão prestes a se fartar!",RandSwear()+"Agora vou te despir de verdade!","Ha! Vamos lá, marinheiro - quero ver do que você é capaz em terra firme!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Juro que você vai se arrepender disso!","Vou arrancar essa sua língua maldita!"),RandPhraseSimple("Vou te abrir de cima a baixo, do seu traseiro até esse buraco imundo que alguns chamam de boca!","Juro que vou te fazer calar a boca!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Vamos lá, pessoal! Vamos tirar essa escória da nossa cidade!";
				link.l1 = RandPhraseSimple(RandSwear()+"Rezem, seus bastardos!","Ah, você não está sozinho! Bem, vai ter companhia no inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "C-claro, todos nós nos conhecemos! Por que a pergunta?";
            link.l1 = "Eu queria visitar o agiota e descobri que ele vendeu a casa antiga. Você sabe onde ele mora agora?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Por que você precisa dele a essa hora, hic? É só ir ao banco de manhã!";
            link.l1 = "Estou precisando de dinheiro urgentemente. Que os ricaços trabalhem um pouco por uma vez! Esse tipo sempre diz que a gente só vive pedindo, reclamando e nunca paga o que deve.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, sim, deixa ele trabalhar! Você sabe onde morava o nosso glorioso capitão Fleetwood?";
            link.l1 = "Claro, quem não conhecia o Richard. Agora o banqueiro mora lá?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Você tem razão. Quando chegar lá, amigo - diga a ele que está se achando demais.";
            link.l1 = "Heh-heh, pode deixar. Até logo.";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "Ha-ha-ha, já vi um chinês? Todos nós já vimos ele!";
			link.l1 = "O que é tão engraçado? Não estou falando de um circo itinerante, se é isso que você quer dizer. Estou falando de um lutador, um oficial da marinha.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, entendi o que você quer dizer! Sim, eu vi ele. Mesmo depois de ficar sóbrio, não consegui parar de ver ele...  Não consigo esquecer disso!";
			link.l1 = "Isso é interessante. Continue. Vamos tomar mais uma - você provavelmente está bebendo agora para esquecer tudo isso. Me conte o que você viu antes de fazer isso.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Circo itinerante, uma ova! Ele pulava, girava e rodopiava com aquele sabre — nunca vi alguém tão habilidoso e assustador com uma arma.";
			link.l1 = "Parece mesmo com ele. Com quem ele estava brigando? Você se lembra?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Os guardas, camarada! Ele também está olhando feio pra eles! Mas acho que ele sempre tem essa cara. O que você acha?";
			link.l1 = "Eu não sei, camarada. Continua. Eles acharam que ele era um espião? Por que os guardas atacaram ele?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Quem sabe? Eles estavam tentando descobrir o que ele estava fazendo na cidade...";
			link.l1 = "Então, eles prenderam ele? Ou...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, nem pensar! Eles não conseguiram pegá-lo. Ele derrubou os guardas na cidade e fugiu para a selva. Mandaram vários grupos atrás dele, mas nenhum voltou. Dá pra acreditar? Ele transformou aquela caverna numa verdadeira fortaleza!";
			link.l1 = "Já é alguma coisa. Vai descansar e tenta esquecer isso. Acho que vou indo agora – minha cabeça está girando.";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "Não vi ele pessoalmente – anda rondando o gabinete do governador, né! Mas a tripulação dele fez uma baita festa aqui.";
			link.l1 = "É mesmo?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Todo mundo diz que ele é um comerciante. Mas a tripulação dele não parecia ralé de taverna, estou te dizendo! Eles pareciam como se... como se... qual é a palavra...?";
			link.l1 = "Entendi. Obrigado pela companhia, amigo. Se cuida.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Estou comemorando! E quem disse que estou sozinho? Você está aqui, camarada! E quanto ao Matt, isso ia acontecer mais cedo ou mais tarde.";
			link.l1 = "O que te faz dizer isso? Ouvi dizer que ele era um pirata incrivelmente sortudo, abençoado pela Sorte durante anos!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, não foi só a Sorte, hein! Ele era um pirata solitário, não fazia parte da Irmandade! E esses não duram muito... Mas ouvi gente dizendo que ele já esteve sob a proteção do Levasseur.";
			link.l1 = "É isso mesmo, quem anda sozinho não dura muito. Bem, aproveite. Tenho que ir, camarada.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Eek, não, n-nunca vi ele. Quem é ele?";
			link.l1 = "Ele é o capitão de um dos navios mais rápidos do Arquipélago, o brigue 'Banten'. Já ouviu falar dele?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Ah, não, eu não me interesso por navios, amigo, ai! Que tal mais uma xícara?";
			link.l1 = "Não pra mim. De qualquer jeito, não consegui o que queria aqui.";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
