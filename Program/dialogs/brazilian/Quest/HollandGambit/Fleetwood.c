// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Saudações, capitão! Não se deixe enganar pela minha aparência, estou bem—quase cego, mas ainda assim bem. Permita-me apresentar: sou Richard Fleetwood.";
					link.l1 = "Bom dia, é um prazer conhecê-lo. Eu sou o capitão "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Eu pedi para você atracar seu navio. Você ao menos me escuta?";
						link.l1 = "Claro, eu cuido disso. Eu tomo conta.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Então, você está aqui de novo. Assuma o comando do 'Valkyrie' — minha tripulação já sabe dos detalhes — e navegue até Bridgetown. Visite todas as pessoas importantes da cidade e espalhe os boatos que combinamos. Depois, esteja pronto para o desgraçado atacar. Não troque de navio e não forme um esquadrão, senão ele vai suspeitar de uma armadilha e não vai aparecer\nVocê deve abordar o navio dele e levá-lo até St. John's. É fundamental que encontre o diário de bordo do pirata, pois é a única prova que teremos do envolvimento de Lucas Rodenburg. Tenho certeza de que você vai dar conta disso. Boa sorte, capitão.";
						link.l1 = "Obrigado! Vou cumprir o trabalho como combinamos.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Você voltou, capitão... Já sei tudo sobre a sua viagem.";
						link.l1 = "É mesmo? Então você deve saber que...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Você voltou, capitão... Já sei tudo sobre a sua viagem.";
						link.l1 = "É mesmo? Então você deve saber que...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Você voltou, capitão... Já sei tudo sobre a sua viagem.";
						link.l1 = "É mesmo? Então você deve saber que...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Você voltou, capitão... Já sei tudo sobre a sua viagem.";
						link.l1 = "É mesmo? Então você deve saber que...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Saudações, meu amigo! Que bom te ver! A Abigail está no seu navio?";
					link.l1 = "Infelizmente, não sei, Richard. Ela se recusou a ir comigo, porque sua partida seria um golpe duro para o pai, que já perdeu cada centavo. Decidi resolver o problema e encontrar o dinheiro de Solomon e aquela ilha...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Mais alguma coisa, capitão?";
				link.l1 = "Não, já estou indo embora.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Mais alguma coisa, capitão?";
				link.l1 = "Não, eu já estou de saída.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Maldito pirata! Você venceu a luta de abordagem, mas ainda assim cumprirei meu dever. Preparei tudo para incendiar o paiol de pólvora, e meu navio logo vai explodir junto com o seu 'Navio Fantasma'. Você nunca mais vai afundar um navio inglês. Morrerei com honra!";
			link.l1 = "I'm sorry to disappoint you, but you're wrong, Fleetwood. There are no pirates on my ship; I've dealt with them before. I needed you, and this ship served as a perfect trap.\nEnough with the pleasantries, I still have to kill you and get away from your flaming tub!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie has already informed me about your successful interception of the enemy's trade caravan. I am glad to meet you; England needs such brave captains. Now, let me tell you something of great importance.";
			link.l1 = "Estou ouvindo, senhor Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Um pirata tem cometido atos de violência por todo o arquipélago, fingindo ser o 'Holandês Voador', um lendário navio fantasma. Ele se faz passar pelo 'Holandês Voador', um navio fantasma famoso. Tenho certeza de que ele é holandês, mas voar ele não voa. Acredito que seja um mercenário a serviço de Lucas Rodenburg, o vice-diretor da Companhia Holandesa das Índias Ocidentais. Rodenburg declarou uma guerra comercial velada contra a Inglaterra – esse 'navio fantasma' ataca apenas embarcações mercantes sob a bandeira inglesa. É fundamental para a companhia enfraquecer nossa influência nesta região sem travar uma guerra de verdade. Venho caçando esse navio fantasma há algum tempo, mas seu capitão é um marinheiro muito experiente e o navio dele é rápido e escorregadio. Como é impossível pegar esse chacal em combate aberto, teremos que agir com astúcia, e a recente tentativa contra minha vida pode nos ser bastante útil. O que acha disso, capitão? Está com medo?";
			link.l1 = "Nem pensar. Eu teria prazer em ajudar você a encontrar e afundar esse desgraçado. Você ia me pedir isso, não é?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "You are right. Now, let's discuss the details. My men will spread rumours that I am on my deathbed and have sold my ship, the 'Valkyrie', to you. Next, we will proceed with our little deception. You will pretend to be a merchant who bought the brig from me and got rid of most of the cannons.\nTherefore, your task is to sail to Barbados and tell everyone there that your holds are filled with valuable cargo and your pockets are brimming with coins. Let them know that you are planning to set sail soon. Play the role of a greedy, simple, yet wealthy merchant.\nOur damned Dutchman gets his information about trading ships from Bridgetown. It is unknown who exactly supplies him with it. Everyone is under suspicion—from a local merchant to the governor, though the latter possibility is quite terrifying.\nTake command of my 'Valkyrie' and her crew. But first, you should leave all your ships here; I have already spoken to the local harbour master. It will cost 10,000 pesos per month for your flagship.\nOnce that's done, return to me and I will make the arrangements. Ah, captain, don't forget to take your cut for capturing the silver caravan, and ten thousand for the harbour master—the money is in the chest of drawers.";
			link.l1 = "Entendi, senhor Fleetwood. Vou falar com o mestre do porto.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Sim, estou ciente de que você falhou em sua missão de capturar o navio pirata. Todos os meus planos foram arruinados. Estou tomando a 'Valkyrie' de você. Pode ir agora, não preciso mais dos seus serviços.";
			link.l1 = "Me desculpe por isso. Adeus, Sr. Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Sim, estou ciente de que você perdeu a 'Valkyrie'. Isso foi totalmente inaceitável... Vou tomar o navio pirata capturado. Pode ir agora, não preciso mais dos seus serviços.";
			link.l1 = "Me desculpe por isso. Adeus, Sr. Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Sim, eu sei que você é um trapalhão de marca maior. Você não capturou o navio pirata e ainda perdeu minha 'Valkyrie'. Estou realmente decepcionado com você. Saia!";
			link.l1 = "Me desculpe por isso. Adeus, Sr. Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Sim, estou ciente de que você teve sucesso no nosso plano. Você eliminou o pirata perverso e capturou o navio dele. Qual é o verdadeiro nome dela?";
				link.l1 = "Miragem";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Sim, estou ciente de que você teve sucesso no nosso plano. Você eliminou o pirata infame e capturou o navio dele. Vou recuperar minha 'Valkyrie'. Pode ficar com a embarcação do pirata como prêmio. Considere também como uma espécie de... compensação. Seu navio ancorado no porto foi destruído pelo fogo quando o incêndio nos cais começou a se espalhar. Peço desculpas pelo transtorno, "+pchar.name+"... I hope the ghost ship will serve you better.\nI have ordered your new vessel to be cleaned of the stubborn dirt and seaweed. They will also dress your beauty in new sails of the finest cotton.\nFinally, please accept your reward of 100,000 pesos and this navigation tool. I have always wanted to present it to a worthy sailor, and you did an admirable job out there! Well, the time has come to say farewell; I have finished my business here and should return to Europe. Good fortune to you, captain!";
				link.l1 = "O mesmo pra você, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Miragem? Um nome bem apropriado, eu diria... Vou recuperar minha 'Valquíria' de você, então pode ficar com o navio pirata como prêmio. Considere isso uma espécie de compensação. Seu navio ancorado no porto pegou fogo quando o incêndio nos cais começou a se espalhar. Sinto muito, "+pchar.name+"... Espero que o navio fantasma lhe sirva melhor.\nMandei limpar sua nova embarcação daquela sujeira teimosa e das algas. Também vão vestir sua beleza com velas novas feitas do melhor algodão.\nPor fim, aceite sua recompensa de 100.000 pesos e este instrumento de navegação. Sempre quis entregá-lo a um marinheiro digno... Você fez um excelente trabalho lá fora, e estou orgulhoso de você! Você está com o diário de bordo do desgraçado?";
			link.l1 = "Sim, claro. Aqui está, pode pegar. Quero te perguntar uma coisa, há algum... asiático entre os capangas do Lucas Rodenburg?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Sim, existe. O chinês Longway, capitão do próprio navio, o 'Meifeng'. Você leu isso no diário do pirata? Vamos dar uma olhada...(lendo) Ora, ora. Como eu suspeitava, Lucas Rodenburg estava por trás de tudo isso! Bem, tanto faz, isso agora não é problema nosso... Nosso governador-geral vai lidar com esse canalha. Lucas Rodenburg vai ter que responder por tudo o que fez!";
			link.l1 = "Hm, interessante, e como o governador-geral inglês vai conseguir 'lidar' com um súdito da Holanda?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Sempre há interesses políticos em jogo, meu caro amigo... A Holanda vai ter que admitir que começou a guerra comercial contra a Inglaterra, mas é improvável que faça isso. Em vez disso, vão colocar toda a culpa no Rodenburg. Lucas pode perder o cargo, ou talvez não. De qualquer forma, a carreira dele vai sofrer um golpe duro. No entanto, isso não é mais problema nosso, capitão. Você cumpriu muito bem a sua parte. Por isso mesmo, tenho outro assunto bastante delicado para você.";
			link.l1 = "Estou ouvindo, Richard. Quem será o próximo inimigo da coroa inglesa a ser destruído desta vez?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Não, desta vez quero lhe pedir para cuidar de um assunto mais pessoal e tranquilo. Deixe-me contar uma breve história que, aliás, diz respeito ao seu 'Mirage'.";
			link.l1 = "Continue.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "I was on a raid, hunting the ghost ship a month before you and I met. It was south of Martinique, not far from longitude 64° 41'. We heard a fight going on somewhere in the distance, but the wind was too weak, so we didn't make it in time. An English flute was sunk by a ghost ship close to some small island which isn't even marked on the map\nI failed to catch the pirate and decided to visit that island, hoping to find any survivors. And I found them. A couple of Jewish refugees, father and daughter. The girl was called Abigail and she was beautiful! A living miracle... I took them aboard and delivered them to Curacao, though her father, Solomon, didn't show much sympathy to me\nAs far as I understood, he thought that I was the pirate who sank their vessel, old man didn't know much about ships or the differences between them. During that little voyage, Abigail and I became friends, or, to be completely honest, fell in love with each other. Isn't that a story?\nAnd I've recently found out that bastard Rodenburg has been courting my Abigail for a while, just think about it! I was going to bring her here, once I solved the matter concerning her father's lost money; he stashed every single coin he had on that island I mentioned. I failed to find its location. We cannot wait any longer\nSince my health still doesn't allow me to set sail myself, I am asking you to go to Willemstad, find Abigail and bring her here. Mention my name and she will trust you.";
			link.l1 = "Não vejo nenhum problema com isso. Estou pronto para zarpar agora.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Excelente! Fico feliz em poder contar com você, "+pchar.name+". Seu trabalho será bem pago, não se preocupe com isso.";
			link.l1 = "Não vou te fazer esperar muito. Até logo, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+", você realmente decidiu procurar a ilha? Estou impressionado com sua generosidade. Conseguiu encontrá-la?";
			link.l1 = "Sim, eu consegui. Infelizmente, é aqui que começam as más notícias. Eu mal consegui sair vivo daquele maldito lugar... Ainda tremo só de pensar nisso...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "O que aconteceu lá? Conte-me, meu amigo, não me deixe na expectativa!";
			link.l1 = "Cheguei à ilha e fui direto para a gruta onde o Solomon provavelmente tinha escondido o baú dele. Ele estava mesmo lá. Mas quando encostei, uma força estranha me lançou para trás. Ouvi uma explosão e fui jogado no chão, a uns três metros do baú...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Incrível!";
			link.l1 = "Eu mal sobrevivi a isso – fiquei com alguns arranhões doloridos. Quando comecei a recobrar a consciência, uns ruídos assustadores zuniam na minha cabeça e aquela criatura horrível surgiu do chão... meu Deus, que monstro!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Richard, eu não estou louco. Isso realmente aconteceu, embora eu mesmo mal consiga acreditar. Era um cadáver totalmente ressecado e pintado de um índio, com um monte de penas na cabeça. Esse monstro murmurou alguma coisa, depois sacou um enorme tacape indígena e me atacou!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Meu Deus... Ainda não entendo como consegui lidar com aquela coisa... Acertei tantas vezes que seria suficiente para matar uma dúzia de homens, e ainda assim continuava de pé... Quando recuperei o fôlego, abri aquele baú maldito... Não havia dinheiro lá dentro, mas tinha outra coisa. Veja só, é um item bem intrigante!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... terrível..."+pchar.name+", espera... Tenho certeza que é ele! É a cabeça do desgraçado que tentou me matar jogando pimenta nos meus olhos!";
			link.l1 = "Você conhece ele? O nome dele é Gaston, o barman de Bridgetown e apoiador do van Berg, o capitão do navio fantasma. Reconheci ele na hora, mas não faço ideia de quem o matou ou como a cabeça decepada dele foi parar no baú do Solomon naquela ilha desconhecida!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Você tem razão, é uma história realmente estranha e sombria. Misteriosa...";
			link.l1 = "Exato. Não fazia sentido voltar para Abigail porque o dinheiro já tinha sumido. Então vim aqui te contar. Talvez você, Richard, consiga entender essa confusão...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Eu? Não entendo nada disso aqui, igualzinho a você... Mas posso te dizer uma coisa com certeza – estou com um pressentimento ruim sobre isso..."+pchar.name+", me escute agora. Vá até Bridgetown para ter certeza de que... Gaston se foi de vez. Depois, peço que venha à Lagoa Blanca, em Curaçao, daqui a 20 dias. Charlie Knippel vai estar te esperando lá. Eu vou juntar o dinheiro para o pai da Abigail. Vou entregar para o Charlie, e você vai levar para Solomon e levar a Abigail até Antígua. Desta vez não haverá obstáculos, entenda isso. Vá, meu amigo!";
			link.l1 = "Está bem, Richard. Vou zarpar imediatamente.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Imagino que você seja o desgraçado que sequestrou minha Abigail. Charlie não voltou para mim, então só pode ser culpa sua também.";
			link.l1 = "Você tem razão, Sr. Fleetwood. Sou eu mesmo. O Charlie me ajudou a conquistar a confiança da Abigail graças à carta que você escreveu para ela. Mas vamos direto ao assunto... Trouxe o dinheiro?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Eu tenho. Mas quero ver a Abigail primeiro. Preciso ter certeza de que ela está viva e bem, já que não vou confiar na palavra de um canalha.";
			link.l1 = "O senhor não acha que não está em posição de impor suas condições?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Eu não quero mais brincar desse jogo. Abi vai ficar comigo, e você está preso nessa praia! Fogo!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Eu entendo isso, mas também não sou idiota. Nada de conversa sobre dinheiro até eu ver a Abigail. E daí? Estou esperando.";
			link.l1 = "Muito bem. Agora é hora de colocar minhas cartas na mesa, Capitão Fleetwood. Marquei nosso encontro aqui não por causa de dinheiro. Bom, claro que eu gostaria de recebê-lo, mas preciso de você antes.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Eu? Isso está ficando cada vez mais interessante... Acho que começo a entender o que realmente está acontecendo aqui. Diga-me, Abigail está viva? Ela está viva, ou você a matou, seu desgraçado?";
			link.l1 = "Suponho que vou deixá-lo na ignorância sobre o destino dela. Só precisa saber de uma coisa – ela não está aqui. Ela cumpriu muito bem o papel dela, e agora você está nas minhas mãos. O amor é mesmo uma coisa maravilhosa... Como mais eu conseguiria atrair uma raposa para fora da toca? Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Não fique tão contente ainda, canalha. Preparei uma recepção especial pra você nesta ilha, e não está nada certo quem realmente manda aqui! Então se prepare, você tem muito o que me contar – sobre Abigail, sobre Charlie. Você vai pagar pelo que fez com eles!";
			link.l1 = "Já estou tremendo de medo! Hora de acabar com essa conversa, senhor. Prepare-se para ir para o inferno, porque no céu não há lugar para você.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
