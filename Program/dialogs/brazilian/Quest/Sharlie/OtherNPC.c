// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Precisa de alguma coisa?";
			link.l1 = "Não, agora não.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Maldição, terra à vista! Acorde, Monsieur... seja lá qual for o seu nome... Chegamos!";
			link.l1 = "A-ah! Já é de manhã? Que calor e umidade infernais são esses?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Eu digo! Charles de Maure! Um nobre, sabia? Como você consegue beber com esse calor? Eu preferia um pouco de água, pelo amor de Deus.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Acostume-se, Monsieur. Este é o único clima que temos por aqui... sempre pode piorar.";
			link.l1 = "Como isso poderia ficar pior!? Estou só com uma camisa de linho e o suor já escorre pelas minhas costas!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Você vai ver, haha! Pode ser época de furacão! Anda logo, monsieur. O bote não vai esperar por você. Você não quer nadar até a Martinica, quer?";
			link.l1 = "Me dá só um instante, tá? Onde está minha espada? Ah, aqui está...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Você não está mais na Europa... Tome cuidado, Monsieur. Vivemos tempos difíceis. Dizem por aí que a Companhia das Ilhas Americanas vendeu a ilha da Martinica para uns fanáticos religiosos, cruzados ou algo assim. Ainda não percebi nada de estranho, pelo menos olhando da embarcação para a costa. Mas como ficamos fora por um tempo, muita coisa pode ter mudado na minha ausência.";
			link.l1 = "Cruzados? Que bobagem!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Seja verdade ou não, os boatos estão por toda parte. Já temos problemas de sobra. Canibais na selva, febre tropical, piratas, bandidos nos becos, sem falar nos espanhóis e ingleses...";
			link.l1 = "Ah, lá vamos nós de novo... Neste momento, o único problema que vejo é esse calor sufocante e os mosquitos... Tudo bem, estou pronto. Vamos?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Suba ao convés e entre no escaler, Monsieur. Bem-vindo ao Caribe!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Aqui não tem outro clima, 'Vossa Senhoria'. Se mudar, é só pra pior.";
			link.l1 = "O clima está insuportável, assim como tem sido minha companhia nesses últimos meses. Espero que haja gente decente no Arquipélago.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Pois bem, acho que todos ficaremos felizes em ver você finalmente nos deixar, monsieur. O barco está esperando. Não vá pular de alegria. E não se esqueça dos seus pertences – o navio vai seguir viagem, e pode dar adeus a eles se não levar agora.";
			link.l1 = "Como se eu fosse deixar eles para o seu prazer. Pesos, espada - parece que não fui roubado.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Somos gente honesta, claro, mas você faz bem em ficar atento – sempre fique de olho nas suas coisas, senão alguém pode limpar seus bolsos. Igualzinho à velha Europa. Ou a qualquer lugar, na verdade. Mas aqui não é como em casa. Uns fanáticos montaram base por aqui. Dizem que compraram a ilha inteira, e tudo em segredo. Então, fique esperto e não chame atenção.";
			link.l1 = "Que bobagem!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "É o que dizem. Seja grato por eu ter me dado ao trabalho de contar e me preocupar com a sua estadia aqui. Caso contrário, essa sua delicada rosa gasconha poderia murchar sob o nosso sol escaldante. Besteira ou não, fique atento – já temos problemas de sobra sem os fanáticos. Bandidos nos becos e na selva, piratas no mar e canibais de pele vermelha...";
			link.l1 = "Calma, calma! Eu me viro. Pode estar um pouco quente pra mim agora, mas lá em casa eu já sou calejado de sol, diferente, por exemplo, dos normandos. E se alguma coisa puder ser resolvida na espada, pode contar comigo. Mas esses mosquitos – isso sim é tortura! Bom, minhas coisas estão todas aqui. O barco está pronto, é isso?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Esperando ansiosamente. Espero que consiga chegar sozinho, monsieur? Siga em frente, e tomara que não se perca depois disso. Ah, e seja bem-vindo ao Arquipélago, heh-heh.";
			link.l1 = "É, valeu. O único consolo é que não vou ficar aqui por muito tempo.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Com licença, "+GetAddress_FormToNPC(NPChar)+", você poderia me dizer onde posso encontrar Michel de Monper? Ele deve estar em algum lugar da sua cidade.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hum... Vejo que você acabou de chegar por aqui, já que faz perguntas tão ousadas... Eu aconselho você a parar, ou vai acabar se metendo em encrenca. Quanto à sua pergunta... Fale com o Abade. Você o encontra na igreja.";
			link.l1 = "Obrigado!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Pare! Entregue suas armas imediatamente, Monsieur, e venha conosco!";
			link.l1 = "Mas que diabo é isso?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_enterSoldiers_2");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Que bom ver você, Monsieur de Maure. Qual é a ocasião?";
				link.l1 = TimeGreeting()+", oficial. Gostaria de falar sobre meu irmão, Michel de Monper. Extraoficialmente, é claro. Estou tentando descobrir mais sobre o tempo dele aqui no Caribe.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Como foi o interrogatório? Descobriu alguma coisa que valha a pena?";
				link.l1 = "Ah, sim. Tanto que estou levando este espanhol comigo de volta para o meu navio. Ele é uma testemunha importante e deve ser entregue em São Cristóvão para mais interrogatórios.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Qual é o seu negócio aqui, monsieur?";
				link.l1 = "Vim ver meu irmão, Michel de Montper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, devo lembrá-lo gentilmente de que está em um quartel militar. Por favor, comporte-se de acordo.";
				link.l1 = "Sim, senhor. Claro.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, preciso lembrá-lo gentilmente de que está em um acampamento militar. Por favor, comporte-se de acordo.";
				link.l1 = "Sim, senhor. Claro.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper está atualmente sob guarda em uma de nossas casamatas, detido por ordem pessoal do Chevalier Philippe de Poincy. Desça para o andar inferior. Lá você encontrará as casamatas que usamos como depósito e celas. Acho que você consegue se virar.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Olá, Monsieur. Posso ajudá-lo em alguma coisa?";
			link.l1 = "Obrigado, soldado, mas não, estou bem. Pode continuar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Obrigado por esperar, Monsieur. Então, está procurando por Michel de Monper? É irmão dele?";
			link.l1 = "Sim, está certo. Eu sou o irmão dele, Charles. Preciso vê-lo imediatamente. Michel está com problemas?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Infelizmente, ele está, Monsieur. Michel está preso em uma das casamatas lá embaixo. O Chevalier de Poincy, Governador-Geral das colônias francesas no Novo Mundo, assinou pessoalmente a ordem de prisão dele. Todos nós ficamos chocados. Seu irmão é um exemplo de virtude, disciplina e coragem — o orgulho da nossa Ordem! O pior é que nós, amigos dele, temos que mantê-lo atrás das grades e vigiá-lo como se fosse um criminoso qualquer! Fazemos de tudo para que ele fique o mais confortável possível, mas... prisão ainda é prisão.";
			link.l1 = "Do que ele é acusado? Ele cometeu algum crime?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "O gabinete do Governador-Geral acusou Michel de desfalque! Que absurdo! Todos nós aqui temos certeza de que é uma jogada política. Vou lhe contar algo em confiança. Michel tem participado de certas ações secretas em nome da Ordem. Talvez ele tenha descoberto mais do que devia. Ou pior, irritado alguns homens poderosos. Mas roubar dinheiro? Ninguém acredita nisso. É só um pretexto, não um motivo de verdade, um pretexto covarde e desprezível! Mas chega de palavras. Seu irmão está ansioso para vê-lo, tenho certeza de que ele mesmo vai lhe contar tudo.";
			link.l1 = "Ótimo. Onde fica a sua prisão?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Na nossa armaria subterrânea, bem aqui na cidade. Venha comigo. Eu te mostro o caminho.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_1");
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Aqui estamos. Esta é a nossa base de operações – o Capítulo Caribenho da Ordem Militar Hospitalária de São João de Jerusalém, de Rodes e de Malta. As casamatas ficam logo abaixo de nós. Siga pelo corredor, passe pelo refeitório e pela capela. A escada ali vai te levar ao andar de baixo. Procure um corredor com celas dos dois lados. Você vai encontrar seu irmão em uma delas, perto do fundo.\nVá, Charles, e que Deus te acompanhe. Por favor, ajude Michel! Ele é inocente, todos aqui estão prontos para jurar isso.";
			link.l1 = "O único motivo de eu ter vindo pra esse fim de mundo foi ver meu irmão. Espero pelo menos conseguir tirá-lo dessa enrascada.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_2");
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Então você estava procurando por Michel de Monper? E você é irmão dele?";
			link.l1 = "Sim, está certo. Eu sou o irmão dele, Charles. Preciso vê-lo imediatamente. Ele se meteu em encrenca, não foi?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Infelizmente, sim, Monsieur. Michel está preso e trancado em nossa prisão. O próprio Chevalier de Poincy, governador-geral das colônias francesas, deu e assinou as ordens. Todos nós ficamos chocados.\nSeu irmão é um exemplo de hombridade, firmeza e coragem, um orgulho da nossa Ordem! O pior é que nós, seus amigos, temos que trancar sua cela e vigiá-lo como se fosse um criminoso! Fazemos de tudo para aliviar sua situação, mas... prisão é prisão.";
			link.l1 = "Então, do que ele está sendo acusado? Ele cometeu algum crime?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Nonsense! Utter nonsense! They have accused Michel of embezzlement and stealing state funds. Ridiculous! We are all certain it is nothing but a political game. Michel was involved in secret operations of the Order; perhaps he discovered more than he ought to have.\nOr something else. But stealing money! No one believes that. It is merely a pretext, not a reason—such a crude and foolish pretext! But enough talk. Your brother is looking forward to seeing you; I am sure he will tell you everything himself.";
			link.l1 = "Ótimo. Onde fica a prisão?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Fica na nossa base subterrânea, aqui na cidade. Venha comigo. Vou te mostrar o caminho.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_3");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "E então ele se debruçou sobre a amurada e despejou tanto que o próprio Caribe ficou verde! Ha-ha-ha!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Oh! Charles, eu estava justamente contando aos rapazes sobre as nossas aventuras!";
			link.l1 = "Eu percebi. Escuta, Alonso. Eu... me tornei capitão.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Já? Achei que você fosse precisar de pelo menos um mês, ha-ha!";
			link.l1 = "Estou falando sério!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Were it only myself, I would sign on at once. But I have forty souls from the Ulysses with me. They have trusted me with their future; I must be sure you will not fail them\n"+
			"What sort of vessel have you?";
			link.l1 = "Um navio é um navio, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+". Por quê, isso importa tanto assim?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Sabe, depois do Ulysses, a gente prefere não servir em qualquer barquinho ou tartana. Já vimos seu navio, e os rapazes aprovaram\n"+"Agora, o dinheiro. Pedimos 4.800 pesos adiantados. Depois disso—dividimos os lucros como sempre. Nada fora do comum, pode acreditar. Consegue arranjar isso?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Muito bem feito! Aqui está sua moeda.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Infelizmente, não tenho tanto dinheiro comigo agora.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Você tem mantimentos no porão, capitão? E remédios? Não? Ora, assim não dá. Saia, compre o mínimo necessário para nossa viagem e depois volte para conversarmos. Vá até a loja e pegue o que precisar.";
				link.l1 = "Hum. Você tem razão. Tudo bem, vou fazer isso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah! Parabéns... Capitão! Vou reunir os rapazes agora mesmo e vamos para o seu navio.";
				link.l1 = "Fico feliz em retomar nossa aventura, Alonso. Prepare o navio para zarpar!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Bem, assim que você conseguir dinheiro suficiente, volte aqui. Você vai nos encontrar aqui na taverna. Não tem outros navios por perto mesmo. Vamos continuar bebendo e gastando tudo com mulheres, hahaha!";
			link.l1 = "Vou tentar voltar o mais rápido possível.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Voltou, capitão? Pronto pra me contratar junto com meus camaradas? Nossas bolsas já estão ficando leves, precisamos sentir a brisa do mar no rosto de novo!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Ainda não, ainda estou preparando tudo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Sim. Pegue seu adiantamento. Agora você está a meu serviço.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Capitão, em que posso ajudar?","Olá, Monsieur. Em que posso ajudar?","Bom dia. O que você quer?");
			link.l1 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de informações sobre esta colônia.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Só passando para cumprimentar. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("O que foi?","O que você precisa?");
			link.l1 = "Escute, "+GetAddress_FormToNPC(NPChar)+", é o seguinte... Estou procurando um navegador. Talvez você conheça alguém adequado para o trabalho aqui na cidade?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Um navegador? Hm. Bem, eu conheço um... Só tem um problema – ele está preso, na cadeia dos devedores. O coitado está trancado nas casamatas faz quase um mês, até que ele ou alguém pague o que deve.";
			link.l1 = "Um devedor? Hm... Qual é o nome dele?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "O nome dele é Folke Deluc. Pergunte ao comandante da prisão se quiser vê-lo. Mas duvido que deixem ele sair de lá, a menos que você pague a dívida dele, porque ele mesmo não vai pagar, hahaha!";
			link.l1 = "Talvez eu faça isso. Obrigado pela informação, amigo.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "A que devo tal honra, Monsieur?";
			link.l1 = "Olá, Folke. É simples, eu tenho um navio, mas não tenho navegador. E preciso de um. Então, comprei sua dívida...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Você está dizendo que me tirou daqui só para me colocar na sua tripulação?";
			link.l1 = "Exatamente. Acho que você vai me fazer recuperar rápido o dinheiro que gastei com você. Bem... vamos ver como as coisas vão andar.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Minha gratidão, Monsieur. Já estou farto desta cela úmida e imunda. Seria um prazer enorme voltar a bordo mais uma vez. Ah, o mar...";
			link.l1 = "Fico feliz que tenhamos chegado a um acordo, Folke. Mais uma coisa, você tem alguma outra habilidade além de comandar um navio?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Um pouco de tudo, capitão. Eu servi como tripulante de um corsário da Companhia Holandesa das Índias Ocidentais. Lá aprendi a lidar com canhões, então posso ser seu oficial de artilharia, se precisar. Comércio e abordagens são meus pontos mais fracos.";
			link.l1 = "Obrigado por compartilhar, agora venha comigo até o navio. Quero que observe a tripulação com seu olhar experiente enquanto eles preparam tudo para a partida. Depois, quero seguir para Guadalupe o quanto antes.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Sim, capitão! Vou te esperar na sua cabine. *Use o menu de ações enquanto estiver no mar para acessar a cabine e outras áreas do navio*";
			link.l1 = "Obrigado, Folke. Até mais a bordo.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Um belo lugre, capitão! Um navio pequeno, mas muito decente, com velame de primeira e estrutura sólida. Com um barco desses, não só chegaremos a Guadalupe em segurança, como poderíamos até cruzar todo o Caribe, se quisermos.";
			link.l1 = "Excelente. Pelo menos não joguei meu dinheiro fora num barco furado... Tem algum conselho antes de zarparmos, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Maldição, esse saveiro está vazando como uma peneira, capitão. Vai ser por um triz conseguirmos chegar até Guadalupe. Se quiser chegar inteiro a Basse-Terre, vamos ter que levar ela pro estaleiro pra consertar imediatamente.";
			link.l1 = "Eu não tive escolha, esse era o único navio à venda! E ainda me cobraram uma fortuna por ele. Como você sabe, não temos tempo para consertá-lo agora... Tem algum conselho antes de zarparmos?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Well, we are well supplied with powder and shot, Captain. This will do for now; only remember to replenish in time.";
				link.l1 = "Bem, isso nem precisa dizer. Mais algum comentário?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah! Obrigado por me lembrar. Por acaso tenho uma caixa inteira de balas comigo!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Não temos munição suficiente no paiol, capitão. Precisamos de pelo menos cem balas de canhão, balas encadeadas e bombas, além de cem sacos de balins e duzentos barris de pólvora. Compre o material necessário, capitão. Não vai custar muito, mas pode salvar nossas vidas se formos atacados por piratas ou espanhóis.";
				link.l1 = "Um investimento que vale a pena. Vou até o mercador.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...E há quanto tempo você anda carregando isso por aí?";
			link.l1 = "Quase duas semanas.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "Mas por quê, capitão?!";
			link.l1 = "Gosto de juntar bugigangas. Nunca se sabe o que pode ser útil.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Que pena pra você. Esse tipo de bala nunca vai caber nas nossas pistolas de brinquedo. Na verdade, nunca vi uma bala tão grande assim. Uma dessas mandaria a Adeline direto pro fundo do mar.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Já terminou de comprar munição, capitão?";
			if (bOk)
			{
				link.l1 = "Sim, já fiz isso. Mais algum comentário?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Agora não, ainda estou trabalhando nisso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Muito bem, você comprou armas suficientes para a tripulação. Se não tivermos armamento bastante, perderemos muito mais homens nas abordagens. Deus nos livre disso. Não se esqueça de conferir sempre a quantidade no porão de carga\nÉ sensato manter algumas armas a mais do que o necessário. Malditos ratos adoram roer os cabos e coronhas de madeira.";
				link.l1 = "Entendi. Vejo que ainda tem algo que gostaria de acrescentar?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "We don't have enough weapons on board for the crew. If we don't have enough weapons, we'll lose far more men during boarding actions. God protect us from that. As far as I understand, you have forty men in the crew\nBuy enough weapons for each, or even buy a few extra; fifty sets should suffice. It's prudent to keep a few more weapons than we'll need. The damn rats like to gnaw on the wooden handles and stocks.";
				link.l1 = "É isso que vou fazer. Volto já.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Já terminou de comprar as armas, capitão?";
			if (bOk)
			{
				link.l1 = "As armas estão no porão. Vejo que ainda há algo que você queira acrescentar?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Agora não, ainda estou trabalhando nisso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Não, acho que é isso. Temos comida suficiente, e você também já providenciou o rum para a tripulação. Isso é sensato, afinal, não há melhor remédio para qualquer mal do que um bom gole de rum fresco depois do turno. Marinheiros gostam e respeitam capitães que garantem a dose diária de rum. Você nunca vai querer ouvir seus homens perguntarem: 'Por que o rum acabou?'";
				link.l1 = "Podemos zarpar agora?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Yes. Food and rum. It's disastrous if you don't have enough food on board. Always have more victuals than you think you'll need. You never know how long a voyage will last - a dead calm or a strong gale can ruin any plan. The men will mutiny or die of hunger when the provisions are gone\nThe rum supply is not as critical, but I strongly recommend always keeping some on board; there's no better cure for all ailments than a nice cool jigger of rum after your shift. Sailors love and respect captains who give them their daily rum ration\nSo go and buy the supplies we need - at least a hundred crates of food and ten barrels of rum. You never want to hear your men ask: 'Why is the rum gone?'";
				link.l1 = "Acho que você tem razão. Vou falar com o comerciante de novo.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Já terminou de comprar nossa comida e rum, capitão?";
			if (bOk)
			{
				link.l1 = "Sim. Podemos zarpar agora?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Não, ainda estou trabalhando nisso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Sim, capitão. Podemos içar âncora e seguir para o norte em direção à Guadalupe, como o senhor pediu.";
			// belamour legendary edition -->
			link.l1 = "Mandou bem, Folke. Eu não teria conseguido sem você.";
			link.l1.go = "Folke_13";
			link.l2 = "Certo, vamos ao trabalho, vamos ver se você vale o dinheiro.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Então me nomeie como navegador e eu assumirei meu lugar no convés.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Então me nomeie como navegador e eu assumo meu lugar no convés.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Pronto para zarpar, capitão!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Capitão, me coloque como navegador, ou vamos encalhar rapidinho.";
				link.l1 = "Entendi, vou fazer isso agora.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Me desculpe. "+GetFullName(pchar)+"?";
			link.l1 = "Certo. Quanto lhe devo por esta ocasião, senhor?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Permita-me apresentar - "+GetFullName(npchar)+". Fui enviado aqui pelo Cesar Craig. Você deve conhecê-lo. Ele é o dono da taverna em Le Francois. Pelo que ele sabe, você está prestes a partir para Guadalupe. Ele gostaria de te oferecer um dinheiro fácil.";
			link.l1 = "Hm... Interessante! E como foi que Cesar Craig ficou tão bem informado?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "It's simple, captain. Your ship is the only one in St. Pierre at the moment; anyone with two ears and one eye knows everything about who you are and where you're headed. Out here in the colonies, rumours fly faster than seagulls. So, are you interested in hearing our offer?";
			link.l1 = "Claro. Nunca recuso a chance de ganhar um dinheiro.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Agora sim, meu amigo! Vejo que você tem faro para negócios. É o seguinte: Cesar precisa urgentemente que uma remessa de vinho seja entregue em Guadalupe. Duzentos barris, seu navio aguenta isso tranquilo. O pagamento é de dez mil pesos por um serviço fácil – Cesar está com pressa, e seu navio é o único no porto neste momento. Convenhamos, propostas tão lucrativas assim não aparecem todo dia.";
			link.l1 = "Dez mil pesos? Droga, está fechado!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Vá até Le Francois e fale com Cesar. Ele vai cuidar de tudo. Tudo o que você precisa fazer é ancorar na baía logo fora de Le Francois. Não me decepcione, o Cesar me prometeu mil pesos se eu te convencesse...";
			link.l1 = "Não se preocupe, pode considerar que estou convencido. Assim que eu estiver pronto para partir, vou zarpar direto para Le François.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Oba! Lá vou eu buscar meu milhar. Valeu, camarada!";
			link.l1 = "De nada...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Capitão, o grupo de abordagem está formado e pronto! Aguardando suas ordens!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Sim, senhor capitão! Preparem-se, rapazes, sigam o capitão! Um, dois, três!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Mierda, reforços franceses! Formem fileiras! Lorenzo, vá até o acampamento e soe o alarme! Morram, seus desgraçados!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Você entende que não estou autorizado a divulgar esse tipo de informação?";
			link.l1 = "Você entende que foi só graças à minha intervenção oportuna que St. Pierre não foi devastada pelos espanhóis? Meu irmão desapareceu, abandonando a Ordem! Ele deve ter feito isso por algum motivo. Eu, como representante de Sir Philippe de Poincy, estou autorizado a investigar!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Certo, certo, Monsieur de Maure. Vou responder às suas perguntas. Primeiro, acalme-se. Agora, pode perguntar.";
			link.l1 = "O que aconteceu antes de Michel ser preso sob custódia?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper estava negociando com alguns barões piratas para organizar uma troca de regime em Tortuga.";
			link.l1 = "Isso eu já sei. O que mais?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Ele também estava planejando uma operação diferente contra os espanhóis. Para ser mais exato – a captura de um navio espanhol carregando uma carga valiosa. Michel deveria atrair o alvo para debaixo dos canhões do pesado couraçado 'Gryffondor'. Ficamos um bom tempo sem notícias dele enquanto ele preparava tudo isso. Mas o plano deu errado. O transporte espanhol não apareceu, e o próprio Michel foi encontrado por pescadores locais, jogado nas margens da Baía de Le Marin, quase morto. Parece que a operação foi um fracasso. Guerra é guerra, e as coisas dão errado. Foi um milagre Michel ter sobrevivido, mas o Chevalier de Poincy ficou furioso. Ele acusou Michel de desviar dinheiro da Ordem e mandou prendê-lo. Claro, não acreditamos em nenhuma dessas acusações. Michel é um homem honesto, um verdadeiro cavaleiro da Ordem. Só Deus sabe o que fez o Governador-Geral perder a cabeça. Talvez o próprio Chevalier de Poincy lhe conte.";
			link.l1 = "Talvez. É só isso que você sabe?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Infelizmente, não há mais nada a dizer. Os detalhes das operações do seu irmão eram conhecidos apenas por ele mesmo e pelo Chevalier de Poincy. Somos cavaleiros da Ordem de São João de Malta. Cumprimos nossas ordens.";
			link.l1 = "Se o Chevalier confia tanto no Michel, é porque ele já teve sucesso em cumprir planos secretos antes. Você sabe de alguma missão bem-sucedida que o Michel realizou?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Com certeza. Esse fracasso recente do Michel de Monper também foi o primeiro dele, por isso ficamos surpresos com a reação do Chevalier. Não faz muito tempo, o 'Gryffindor' capturou um galeão espanhol carregado de prata graças ao planejamento cuidadoso do Michel. Só isso já deveria compensar dezenas de fracassos no futuro. E mesmo assim, seu irmão foi preso.";
			link.l1 = "Entendi. Você faz ideia do motivo pelo qual Michel fugiu de St. Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Suspeito que um conflito pessoal entre Michel e de Poincy foi o motivo da prisão dele. É claro que seu irmão teme que o Chevalier continue a persegui-lo mesmo depois de solto, então ele tomou precauções. E sabe de uma coisa, Monsieur de Maure? Ninguém aqui o culpa por isso!\nO homem trabalhou com coragem pelo bem da Ordem e, ainda assim, jogaram-no numa cela imunda logo na primeira falha, enquanto ele estava gravemente ferido! E nem foi um fracasso tão grande assim, ninguém morreu, nenhum navio afundou!\nAliás, esta conversa é totalmente confidencial e não vou repetir nada do que disse, nem sob juramento, entendido, Monsieur de Maure?";
			link.l1 = "Sim, senhor. Já até esqueci que tivemos essa conversa. Diga-me, será que o ataque espanhol a St. Pierre foi provocado pela Ordem atacando navios espanhóis? Talvez aquele mesmo galeão espanhol carregado de prata que você mencionou? Os castelhanos estavam extremamente determinados a encontrar sua base...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Doubt it. Very few people know about the Order's presence in the Caribbean, and all our sorties against the Spanish were carefully planned. Ask the Spanish officer we took prisoner; he is cooling his fiery Castilian temper in our casemates right now. We have already interrogated him. The attack on St. Pierre was an ordinary raid, organised by a Spanish grandee named Ramon de Mendoza y Riba for his own profit and to intimidate the French colonies. He also wanted to curry favour with the Escorial.";
			link.l1 = "Vou falar com esse espanhol. Onde posso encontrá-lo?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Lá embaixo, na mesma cela onde seu irmão ficou preso.";
			link.l1 = "Eu conheço o caminho. Volto depois de interrogar o espanhol. Talvez eu tenha mais algumas perguntas.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Bem, veja só! Você entende que eu não posso soltar esse prisioneiro, não é? Aquele canalha ajudou a liderar o ataque a St. Pierre!";
			link.l1 = "Oficial, esta é uma testemunha importante. O ataque a St. Pierre não foi um simples saque em busca de tesouros. Dom Ramon Mendoza estava procurando outra coisa. Precisamos estabelecer um motivo definitivo. Então, vai liberar este espanhol para mim ou preciso pedir permissão ao de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Por Deus Todo-Poderoso... Está bem, leve-o. Eu ia enforcar esse desgraçado mesmo na praça de St. Pierre, como o pirata comum que ele é... Agora ele é problema seu. Certifique-se de que ele não fuja da justiça!";
			link.l1 = "Sem dúvida. Responderei por este espanhol diante de de Poincy. Prendam esse prisioneiro e levem-no algemado até meu bote no cais da cidade.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Muito bem, capitão.";
			link.l1 = "Mais uma coisa, oficial. O nome Miguel Dichoso te diz alguma coisa?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Não. Nunca ouvi falar disso antes. Por que está perguntando?";
			link.l1 = "Tem certeza? Então você não conheceu ninguém com esse nome, nem aqui no seu acampamento, nem no palácio do governador, nem em nenhum lugar de St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Não, nunca estive. Lá de onde venho, não temos muita consideração pelos espanhóis.";
			link.l1 = "Certo. Enfim, já era de se esperar. Teria sido fácil demais... Obrigado, oficial! Você foi de grande ajuda.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "De nada... O que acha, Monsieur de Maure, onde está seu irmão agora?";
			link.l1 = "Eu também gostaria de saber a resposta para essa pergunta. E eu vou descobrir... mais cedo ou mais tarde. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Você é o capitão "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. O que posso fazer por você?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Saudações, capitão. Fui enviado até você pelo Padre Vincente. Tenho algo para você...";
			link.l1 = "Padre Vincento? Eu não trabalho mais para Sua Graça. Não depois que ele mandou Alonso de Maldonado, homem de confiança de Diego de Montoya, para me matar. Pode passar esse recado ao Reverendo Padre: ele falhou.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Espere, capitão. O padre Vincento previu que você reagiria assim e me alertou sobre isso. Garanto que Sua Graça não lhe deseja nenhum mal. Por favor, leia esta carta. É muito, muito importante.";
			link.l1 = "O padre Vincento não me deseja mal algum? Hm. Talvez ele também tenha deixado de te contar algo sobre mim e Dom de Maldonado? Não vejo motivo para acreditar em você.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Pegue esta carta, capitão. Leia e tome sua própria decisão. Só saiba que o destino de toda a cristandade está em suas mãos. Não leve isso de ânimo leve. Que Deus o abençoe e guie seus passos pelo caminho certo!";
			link.l1 = "Certo, me dê a carta.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Aqui está. Espero que tome a decisão certa. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Saudações, meu filho. Que o Senhor esteja com você.";
			link.l1 = "E também com o senhor, padre Adriano. Sua Graça disse que o senhor poderia me fornecer amuletos e remédios.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Sim, claro. Recebi uma remessa especial de Santiago só para você. Aqui estão amuletos abençoados e poções de cura. E para completar, uma rara e única tintura de Ometochtli que vai te deixar invencível em combate. Tudo isso é para você, meu filho. Pegue e veja como o Senhor é bom.";
			link.l1 = "Obrigado!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Se você precisar de mais ervas medicinais, posso lhe fornecer um frasco de cada por dia. Prepararei quantos forem necessários.";
			link.l1 = "Tenho minha gratidão, Padre Adriano. Vou me lembrar disso.";
			link.l1.go = "exit";
			link.l2 = "Ótimo. Estou precisando disso agora.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Deus te abençoe e te proteja, meu filho. O que deseja?";
			link.l1 = "Gostaria de comprar algumas poções de cura.";
			link.l1.go = "potion";
			link.l2 = "Nada por enquanto, estou me preparando para uma viagem. Só passei para dar um oi e saber como você está.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Claro, meu filho. De que remédio você precisa?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "É só um remédio simples.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Um elixir revigorante.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Um antídoto.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Uma mistura de ervas.";
				link.l4.go = "potion4";
			}
			link.l5 = "Desculpe incomodá-lo, pai. Mudei de ideia.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Uma essência curativa? Isso vai custar 90 pesos, meu filho. Pelos materiais, é claro.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Obrigado, pai.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Infelizmente, eu não tenho o dinheiro... Vou voltar mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Um elixir que faz bem à saúde? 500 pesos, meu filho.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Obrigado, pai.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Infelizmente, eu não tenho o dinheiro... Vou voltar mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Um antídoto? 200 pesos, meu filho.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Obrigado, pai.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Infelizmente, eu não tenho o dinheiro... Vou voltar mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Uma mistura de ervas? 900 pesos, meu filho.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Obrigado, pai.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Infelizmente, eu não tenho o dinheiro... Vou voltar mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "'Pois eu te devolvo a saúde e curo as tuas feridas, diz o Senhor.' Aqui está o seu remédio. Dominus vobiscum!";
			link.l1 = "Obrigado, padre Adrian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Capitão "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. O que você quer?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Tenho uma mensagem para você do Capitão Miguel Dichoso. Ele disse que você o conhece.";
			link.l1 = "Sim, já ouvi falar dele. Nunca tive a honra de conhecê-lo pessoalmente.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "O Capitão Dichoso gostaria de mudar isso. Ele quer se encontrar com você pessoalmente. Tem uma proposta para você sobre uma expedição ao coração do Caribe espanhol, até a cidade indígena perdida de Tayasal. Ele me disse que sua experiência, junto com o conhecimento dele, vai trazer ótimos resultados.";
			link.l1 = "Foram essas exatamente as palavras dele?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Certo. O capitão Dichoso estará esperando por você em São Cristóvão. Ele vai te aguardar na grande cripta do cemitério de Capsterville, para evitar olhos e ouvidos curiosos.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso me avisou que você hesitaria. Ele pediu que eu lhe desse garantias de que nada vai lhe acontecer durante as negociações, independentemente da sua decisão. E acrescentou que o que você encontrou numa certa ilha não passa de um pequeno aperitivo perto do que vai encontrar em Tayasal.";
			link.l1 = "É mesmo... isso é bem intrigante. Mas por que o capitão Dichoso não veio falar comigo pessoalmente? Por que ele mandou outra pessoa?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso primeiro procurou por você na Isla Tesoro, depois aqui, e agora foi para St. Christopher na esperança de te encontrar lá. Você é oficial do próprio Philippe de Poincy, não é? Eu deveria esperar por você aqui caso chegasse a Blueweld.";
			link.l1 = "Então está tudo claro. Certo, não vou perder tempo, preciso ir para Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Enfim nos encontramos, capitão "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Onde está Miguel Dichoso? E nem tente se esquivar dessa. Eu sei quem ele realmente é, e acho que você também sabe.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Suponho que este seja o próprio Miguel Dichoso bem aqui na minha frente?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Você supôs certo, capitão. Estamos no encalço um do outro há muito tempo, não é mesmo?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Eu sei que você está mentindo só de olhar pra você, camarada. Você não é o Dichoso. Eu li os registros do capitão da 'Santa Quiteria' e perguntei por aí sobre a aparência dele. Você não se parece com ele. Nem sequer tem uma cicatriz no rosto de um golpe de sabre. Vamos lá, até um farsante teria pelo menos tentado desenhar uma!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Exatamente. Pelo que entendi, estamos aqui para falar sobre a cidade perdida de Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha! Então não faz sentido continuar com essa farsa. Miguel já tinha me avisado que você era um sujeito astuto...";
			link.l1 = "Onde está Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Ele não está aqui. Fui autorizado a encontrá-lo e falar com você em nome dele.";
			link.l1 = "Não vou falar com um peão. Vim pelo rei. Onde ele está?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Não é um interlocutor agradável, capitão. Você perdeu a compostura.";
			link.l1 = "Chega de brincadeira, já entendi. É outra emboscada. Vocês precisam inventar truques novos.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Haha, acertou de novo! Meus homens estão esperando por você logo atrás da porta que leva às catacumbas. Além disso, tenho mosqueteiros escondidos atrás de cada lápide, prontos para atirar. Não há como escapar. Então, por mais repetido que esse truque seja, você caiu direitinho! Seu desejo de ver Tayasal falou mais alto que o bom senso!";
			link.l1 = "Você escolheu um ótimo lugar para brigar, canalha. Não vou precisar ir longe para enterrar você e seus comparsas.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Haha! Gosto do seu jeito! Igualzinho ao Miguel! Fale o que quiser, vocês dois são farinha do mesmo saco... Vou fazer exatamente como ele mandou – vou te mandar pro inferno rápido e sem dor. Às armas, rapazes!";
			link.l1 = "Homens melhores do que você já tentaram. Mande lembranças minhas ao Diabo, canalha!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Você realmente quer chegar à cidade? Eu entendo, capitão, mas não acho que seja uma boa ideia.";
			link.l1 = "Então sobre o que viemos conversar aqui?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Não estou procurando ter uma longa conversa romântica com você. Você está aqui, e isso já basta para mim.";
			link.l1 = "Chega de joguinhos, já entendi. É outra emboscada. Vocês podiam inventar truques novos, não acham?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Aguardando suas ordens, capitão!";
			link.l1 = "Vamos atravessar a selva até o cemitério de Capsterville. Quando chegarmos lá, não entrem no cemitério. Fiquem de prontidão logo fora do portão e prestem atenção enquanto eu entro. Se ouvirem barulho de luta, entrem imediatamente.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Aguardando suas ordens, capitão!";
			link.l1 = "Vamos atravessar a selva até o cemitério de Capsterville. Quando chegarmos lá, não entrem no cemitério. Tomem posições de tiro ao longo da trilha, cerquem o cemitério e fiquem atentos ao momento em que eu entrar. Todo esse plano cheira a emboscada. Assim que avistarem o inimigo, ataquem sem hesitar.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Aos seus comandos, capitão!";
			link.l1 = "Certo. Avante!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Capitão Hobart! Segundo as informações do nosso espião, os rebeldes estão escondidos nesta propriedade. Você tem cinco dragões à sua disposição. Revise o prédio e capture qualquer um que estiver se escondendo lá dentro! Não trate essa escória com delicadeza. Você está agindo em nome do Rei!";
			link.l1 = "Sim, senhor!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Filho do Mar!";
			link.l1 = "Ah... o quê? Está falando comigo?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Certo. Eu sou Folha de Cacau. Tenho negócios com você, Filho do Mar.";
			link.l1 = "Eu não faço ideia de como é o cacau, nem por que você tem esse nome. Mas tudo bem, diga logo o que precisa.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Vá até a cidade. Compre duas pistolas e dois conjuntos de dez pólvoras e balas. Traga tudo para mim. Tem uma recompensa. O Filho do Mar vai ficar satisfeito.";
			link.l1 = "Duas pistolas e vinte tiros? Só isso? Então por que você mesmo não compra?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Você não entende, branquelo? Quem é que vai me vender uma arma?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Sabe, já encontrei gente como você na Martinica antes... Canibais. Eles sequestraram uma moça e dois homens. Assaram e comeram um dos homens. Se algum deles tivesse uma arma, a gente não estaria tendo essa conversa.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "E por que você precisa de uma arma de fogo, Folha de Cacau? Pretende matar alguém?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Folha de Cacau não é um bandido, minha luta é só com os guerreiros da sua tribo. Rostos-pálidos vêm para nossa terra, nos fazem escravos. Folha de Cacau luta sozinho. Levar um escravo. Nem bom, nem ruim. Assim é a vida. Índio, branco, não faz diferença. Armas de fogo fazem diferença.";
			link.l1 = "E por que você precisa de uma arma de fogo, Folha de Cacau? Pretende matar alguém?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Lutar. Mas em igualdade de condições. Os brancos têm armas de fogo, os índios não. Isso não é justo. E ter uma arma de fogo para um índio é uma proteção contra injustiça, humilhação ou insulto dos brancos.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Certo, capitão. Os rostos-pálidos nos menosprezam.";
			link.l1 = "Eu reparei. Lá na Europa, eles falam bonito sobre ensinar a verdadeira fé aos índios e como todos convivemos em harmonia nas plantações...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu talvez não entenda o capitão, mas entende a folha de cacau. Ele busca vingança.";
			link.l1 = "Parece que sim... Você também não quer se vingar dos nossos recentes captores?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Talvez. Mas Tichingitu não vai recorrer a isso. Tichingitu está com você agora. E Tichingitu pensa por si mesmo. Haveria sangue demais derramado. Sangue branco. Sangue indígena. Sofrimento demais. Isso não está certo.";
			link.l1 = "Sim, já está ruim, e ajudar o Folha de Cacau a conseguir armas só vai piorar as coisas... Mas ele tem razão. E eu ainda preciso pagar a tripulação em breve.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Use a sua própria cabeça, capitão.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "O Filho do Mar fala demais. Parece uma comadre de bigode.";
			link.l1 = "Quem? Me explica isso, Folha de Cacau. Eu também sou um rosto-pálido, e você está me pedindo armas para lutar contra rostos-pálidos. Isso não é contraditório? Por que veio falar comigo?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Eu ouvi sua conversa com aquele índio de roupas estranhas. Você não é como os outros rostos-pálidos. Você entende Tichingitu. E tenho certeza de que entende Folha de Cacau também.";
			link.l1 = "Oh... O que você vai oferecer por armas, Folha de Cacau?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "As lágrimas dos deuses. Vocês as chamam de pérolas. Muitas pérolas.";
			link.l1 = "Já tomei minha decisão, Folha de Cacau. Espere aqui, vou até o armeiro. Vou comprar o que preciso e volto.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Já tomei minha decisão, Folha de Cacau. Já tenho o que você precisa. Aqui está.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Já tomei minha decisão, Folha de Cacau. Não quero arranjar confusão à toa. Não vou te dar armas de fogo. Pode ir embora.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Uh-oh! O Filho do Mar tem uma mosquete? Você vai pagar caro por uma mosquete!";
			link.l1 = "Não, mas um canhão do meu navio serve? Vai embora agora, Folha de Cacau, antes que nos vejam e prendam.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Negócio fechado! Filho do Mar, se for entrar na selva, leve uma arma de fogo. Se encontrar um índio, faça um acordo.";
			link.l1 = "Vou me lembrar disso. Adeus, Folha de Cacau.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "A Folha de Cacau vai esperar.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, parece que temos uma reunião de nativos aqui!\nQuer voltar pra cadeia, cachorro?\nO que está fazendo aqui, Monsieur?";
			}
			else
			{
				dialog.text = "Pare! O que está fazendo aqui, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Ei, canalha, estava esperando por este cidadão de bem?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Todos os rostos pálidos parecem iguais para mim. Mas nunca vi este aqui. Você, guerreiro, faça o que tiver que fazer comigo. Isso já está ficando cansativo. Folha de Cacau está pronta para encarar os espíritos da floresta.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "O inferno te espera, não os espíritos da floresta.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Capitão, você está dispensado. Fique fora do meu caminho. Proteger a cidade é coisa séria.";
			link.l1 = "Entendi... Mas e quanto a esse índio?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Qual é o seu interesse nos índios, Monsieur? Embora... bem, claro, você acabou de chegar da Europa Como está Paris? Ainda esmagam ratos nas ruas, ou já começaram a convidá-los para a comunhão? Veja, aqui nós temos nativos no lugar dos ratos. Fazem negócios com bucaneiros, atacam madeireiros, comem gente, maldição Três dias atrás, algum gênio já tinha vendido um mosquete para um desses aí. E adivinha? Esses desgraçados mataram todos os soldados da patrulha, liderados, aliás, pelo meu amigo e camarada. Encontramos o colono traidor e penduramos ele ao sol, para servir de exemplo. Dar armas de fogo para índios! Isso é traição! Traição contra a França! Estamos de olho nesse macaco colorido faz tempo, já ficou conhecido em vários eventos Bem, agora ele vai ter o fim rápido e merecido. Pode seguir em frente, Capitão. Não se meta em assuntos que não lhe dizem respeito. Você não faz parte dessa guerra... Ainda não... Ou faz?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Confiável) Veja bem, oficial... Sou o capitão Charles de Maure, hóspede de Fadey, o Moscovita. Temos certo interesse nesse índio... então vamos evitar atrapalhar o trabalho um do outro. Concorda, tenente?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Atitudes em relação aos recém-chegados, atitudes em relação aos nativos... Colonos, nativos... Ainda não entendo muito bem tudo isso, mas neste momento, tenente, a comparação não está a seu favor... À batalha!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Você tem razão, tenente, não sou mesmo. Adeus.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Hum! Entendido, capitão. Por favor, transmita meus cumprimentos ao Monsieur Fadey. Esquadrão, retomem a patrulha!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Ih, caramba!";
			link.l1 = "É, bom, até eu fiquei surpreso que isso deu certo. Aqui estão suas mercadorias, Folha de Cacau.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "O Filho do Mar fala bem. Salvar um índio não é pouca coisa! Uma grande recompensa o espera!";
			link.l1 = "Caramba, isso sim é um bom saque... E uma pedra com um buraco, e algum tipo de amuleto.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "O Filho do Mar tem um mosquete? Pague caro por um mosquete!";
			link.l1 = "Não, mas um canhão do meu navio serve? Vai embora agora, Folha de Cacau, antes que nos vejam e prendam.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Negócio fechado! Filho do Mar, se for entrar na selva, leve uma arma de fogo. Se encontrar um índio, faça um acordo.";
			link.l1 = "Vou me lembrar disso. Adeus, Folha de Cacau.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Ih, decisão ruim, Filho do Mar. Por que você fez isso?";
			link.l1 = "Ugh... Cinco minutos atrás parecia certo... Agora já não tenho tanta certeza... Eu matei um dos meus, afinal. O que eu faço agora? E se descobrirem? Droga! Droga!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Agora vai ter uma invasão. Os soldados vão matar todo mundo. Duas patrulhas não vão perdoar. Folha de Cacau foge. E você, Filho do Mar... por quê. Folha de Cacau vai morrer de qualquer jeito. Os espíritos querem assim.";
			link.l1 = "Oh... Nosso acordo ainda está de pé?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Má decisão, Filho do Mar. Mas obrigado. Uma grande recompensa.";
			link.l1 = "Nem tão grande assim, se pensar bem...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Filho do Mar, se você sobreviver e depois for para a selva, leve uma arma de fogo. Se encontrar um índio, tente negociar.";
			link.l1 = "Vou lembrar disso no futuro. Adeus, Folha de Cacau.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Saudações, Capitão Charles de Maure. Meu nome é Charles Barbier. Posso tomar um momento do seu tempo?";
			link.l1 = "Capitão de Maure... Sim, sou eu! Por favor, continue, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Sempre é um prazer encontrar um colega, ainda mais um que compartilha meu nome! Tenho uma proposta para você, capitão. Veja bem, preciso de escolta até St. Pierre, e...";
			link.l1 = "Eu conheço St. Pierre! Mas isso é só uma viagem de dois dias! E devo confessar, ainda sou meio inexperiente como escolta. Assumi o comando deste navio só faz uma semana.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Sua honestidade é apreciada, Capitão. Charles, perdoe minha informalidade, mas você é exatamente a pessoa de que preciso.";
			link.l1 = "Hum... Lembro de uma proposta parecida não faz muito tempo. Isso acabou levando a uma emboscada de piratas perto de Le François.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Ouvi falar desse incidente, por isso vim atrás de você\nPrimeiro, estou transportando uma carga bastante valiosa, e sempre há predadores à espreita. No entanto, sua recente vitória sobre aqueles piratas perto de Le Francois vai fazer os canalhas de lá pensarem duas vezes\nSegundo, sua ligação com Fadey Moscovita é uma ótima recomendação.";
			link.l1 = "Um argumento convincente, Monsieur. E que compensação você propõe por esse favor?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Não é um favor, Capitão, mas sim um negócio vantajoso para ambos! Eu lhe pago quarenta moedas de ouro para me escoltar até St. Pierre sem demora.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Confiável) Já que estou indo na direção oposta, Monsieur, vou precisar do pagamento adiantado.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Não é uma má proposta – eu já estou indo pra lá mesmo. Fechado!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Carga valiosa, você diz? Lamentavelmente, Monsieur, já tive minha cota de aventuras por enquanto.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "É difícil recusar um jovem tão sério, capitão. Aqui estão seus quarenta dobrões. Vamos zarpar sem demora? Tempo é dinheiro.";
			link.l1 = "Não vamos demorar, Monsieur. Em breve estaremos zarpando.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Excelente! Vou me preparar para a partida imediatamente!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Entendo, Capitão. Não vou incomodar. Adeus, tenha um bom dia.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Obrigado pela escolta exemplar, capitão. Fico feliz que não tivemos nenhum incidente.";
				link.l1 = "Foi um prazer fazer negócios com você, Monsieur. Agora, com licença, tenho muito a resolver.";
			}
			else
			{	
				dialog.text = "Obrigado pela escolta exemplar, capitão. Fico feliz que não tivemos nenhum incidente. Aqui está seu pagamento – quarenta doblões, integralmente.";
				link.l1 = "Foi um prazer fazer negócios com você, Monsieur. Agora, com licença, tenho muito a resolver.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Sim, Charles? Você parece preocupado. Aconteceu alguma coisa?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Bem, já que você é uma pessoa confiável, e conhece o Fadey... Olha, comércio é um negócio arriscado, não é?";
			link.l1 = "Se você diz.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Consegui comprar um lote de cordas por uma pechincha em Guadalupe de... você sabe quem. Minha ideia era vendê-las rápido em St. Pierre e usar o dinheiro pra comprar café e revender em Willemstad. Parecia um bom plano.";
			link.l1 = "Não duvido da sua integridade, Monsieur, mas tudo isso me soa meio suspeito. Você fala da sua carga como se fosse ouro. Enquanto isso, meu navio está cheio dessas cordas que não valem quase nada.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, estas cordas são de altíssima qualidade, feitas com cânhamo superior e trançadas nas fábricas do czar de Moscou. Elas têm usos estratégicos e são empregadas no cordame dos navios de guerra. Os ingleses monopolizam as rotas comerciais com Moscóvia, proibindo o livre comércio dessas cordas. Outras nações disputam ferozmente para garantir todo o estoque disponível para seus estaleiros na Europa também.";
			link.l1 = "Então, é isso que chamam de contrabando?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Obrigado, mas contrabando não me interessa.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Pena! O comércio honesto pode até te render um bom lucro, mas nunca vai te deixar realmente rico. Mas veja bem, eu não puxei essa conversa meio arriscada à toa. Quero te oferecer um carregamento de cordas. Os contrabandistas daqui vivem na taverna e vão disputar essa mercadoria. Só pensa: hoje mesmo você pode ganhar um bom dinheiro sem nem precisar sair para o mar.";
			link.l1 = "Quanto você está pedindo pela carga?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Dez mil pesos. É uma quantia modesta, e revender as cordas para contrabandistas vai render um bom lucro.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Eu nunca me perdoaria se deixasse passar uma oportunidade dessas. Pegue a prata e garanta que as mercadorias sejam entregues ao meu navio sem demora.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Isso é um empreendimento arriscado, meu amigo. Que tal chegarmos a um acordo? Aceito suas cordas por sete mil.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "É uma quantia considerável, Monsieur. Compreendo sua situação, mas não posso assumir um risco desses.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Minha gratidão, Charles! Você me salvou da ruína financeira! As mercadorias serão despachadas rapidamente e com o máximo cuidado\nPermita-me lhe dar um conselho como colega comerciante: assim que contratar um bom intendente, compre café em Saint-Pierre e venda com lucro em Willemstad. Os capitais locais pagam muito bem por produtos coloniais, exportando-os para a Europa com grandes ganhos. Boa sorte nos seus negócios, amigo!";
			link.l1 = "Adeus, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				Notification_Skill(true, 25, SKILL_COMMERCE);
				dialog.text = "Minha gratidão, Charles! Você me salvou da ruína financeira! As mercadorias serão despachadas rapidamente e com o máximo cuidado\nPermita-me lhe dar um conselho como colega comerciante: assim que contratar um bom intendente, compre café em Saint-Pierre e venda com lucro em Willemstad. Os capitalistas locais pagam muito bem por produtos coloniais, exportando-os para a Europa com ótimos ganhos. Boa sorte nos seus negócios, amigo!";
				link.l1 = "Adeus, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				Notification_Skill(false, 25, SKILL_COMMERCE);
				dialog.text = "Não posso, Capitão. Minha mercadoria é séria e merece ser tratada com seriedade. A maioria dos capitães livres não ousa negociar bens estratégicos. Infelizmente, não há espaço para barganha aqui.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Eu nunca me perdoaria se deixasse passar uma oportunidade dessas. Pegue a prata e garanta que as mercadorias sejam entregues ao meu navio sem demora.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "É uma quantia considerável, Monsieur. Compreendo sua situação, mas não posso aceitar um risco desses.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Que pena! Adeus, Capitão.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Problemas, capitão.";
			link.l1 = "E então?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Nosso navegador foi preso e levado para a masmorra local. Dívida, pelo que dizem.";
			link.l1 = "O quê, de novo?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "Ele é um sujeito travesso, Capitão.";
			link.l1 = "Que péssima hora! Sem um navegador, estamos presos aqui. Vou ter que tirar ele dessa de novo! Vou falar com o comandante...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Permissão para falar, Capitão?";
			link.l1 = "Pode ir em frente.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Por que passar por todo esse trabalho? Um homem como ele só vai trazer problemas para o navio.";
			link.l1 = "Eu tenho escolha? Quase não há outros navegadores disponíveis, então minhas opções são bem limitadas.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "É verdade, um navegador de primeira é difícil de encontrar, mas você ainda não precisa de um mestre, só de alguém competente. Sua situação mudou na última semana, você sabe disso, não é? Não precisa mais aceitar qualquer um só pra completar a tripulação. Agora estão comentando por aí como você derrotou aquele pirata e sobre os contatos que você tem. A tripulação está com você também, Capitão, a gente gosta de você.";
			link.l1 = "Isso é reconfortante, Alonso. E o que a tripulação acha do Deluc?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "You learn quickly, Cap’n. The crew says that while he is a capable officer and treats us fair, he is not worth the bother. A big merchantman just let its officers go—perhaps look in the tavern? The right fellow is bound to be there. And forget Deluc; that’s the word among the men.";
			link.l1 = "Obrigado pelo conselho, Alonso. Eu sabia que podia contar com você. Volte para o navio e fique de vigia enquanto eu resolvo isso.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Afirmativo!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Alonso_DlgExit");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Cap...";
			link.l1 = "Eu tenho um milhão de perguntas, mas vou fazer só uma: como você conseguiu arranjar novas dívidas se esteve comigo o tempo todo, me ensinando navegação!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Tenho vergonha de admitir, Capitão, mas já vinha pegando dinheiro emprestado de vários agiotas muito antes de entrar para sua tripulação. Meu plano era ficar discreto e trabalhar no seu navio até juntar o suficiente para pagar todas as minhas dívidas. Mas cometi o erro de sair do navio para me envolver com uma certa mulher aqui em St. Pierre, e os soldados me pegaram bem debaixo do nariz dela. Não fiz novas dívidas na Martinica, já que você pagou a última por mim, eu juro!";
			link.l1 = "Você é um imbecil, Deluc, e me fez virar motivo de chacota em St. Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Impressionante, Folke. Obrigado pela história.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "O que vai fazer, Capitão? Consegue me tirar dessa de novo? Não vai ser fácil encontrar outro navegador, sabia...";
			link.l1 = "Fique aqui por enquanto. Vou decidir o que fazer. Talvez eu volte ao banqueiro.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "O que vai fazer, Capitão? Consegue me tirar dessa de novo? Não vai ser fácil encontrar outro navegador, sabia...";
			link.l1 = "Fique aí por enquanto. Vou tomar uma decisão. Talvez eu vá falar com o banqueiro de novo.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Não é como se eu tivesse para onde ir...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Folke_DlgExit_1");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Capitão, obrigado. Você pagou minhas dívidas, mas agora devo a você uma dívida ainda maior – a minha vida. E sou realmente grato por isso! Garanto que não encontrará um homem mais leal do que eu em todo este mundo!";
			link.l1 = "Acho que algumas dívidas só podem ser pagas contraindo outras. Vamos voltar ao trabalho, Folke. Ainda há muito o que fazer no mar.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Não se esqueça disso, Deluc. Da próxima vez eu simplesmente atiro em você.";
			link.l2.go = "Del_Folke_11b";
			Del_Ohrannik();
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Sim, senhor capitão!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Sim, senhor capitão!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			AddDialogExitQuestFunction("Del_Folke_DlgExit_2");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Precisa de um oficial, capitão?";
    		Link.l1 = "Um oficial? E no que você é bom?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Não, já tenho um conjunto completo.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Sou o melhor navegador dessas águas. Também entendo um pouco de medicina. E estou pronto para lhe fazer um favor e servir sob seu comando.";
			Link.l1 = "E quanto você quer?";
			Link.l1.go = "Del_price";
			Link.l2 = "E que tipo de especialista você é?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Infelizmente, eu já tenho um navegador.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Acho que podemos concordar em 4.000 pesos.";
			Link.l1 = "Isso não é um pouco exagerado?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Concordo. Considere-se parte da tripulação.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Você não vale esse dinheiro.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Mudou de ideia, capitão? Decidiu que um novo navegador não faria mal?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Algo assim. Quanto você quer?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "E do que você é capaz?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Tenho um jogo completo. Até mais.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Certo... Acho que posso aceitar 2500 pesos. O que me diz?";
				Link.l1 = "Agora sim. Você está dentro.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Sinto muito, capitão, mas eu valho exatamente o que pedi. Se for demais para você, então procure outra pessoa.";
				Link.l1 = "Certo, eu concordo. Vou te levar.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "É isso que vou fazer. Adeus.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Obrigado, capitão. Você não vai se arrepender da sua escolha.";
					Link.l1 = "Espero que sim.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Vejo que está sem dinheiro, capitão! Sinto muito, mas não trabalho fiado.";
					Link.l1 = "Oh, diabo!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Obrigado, capitão. Você não vai se arrepender da sua escolha.";
					Link.l1 = "Espero que sim.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Vejo que está sem dinheiro, capitão! Sinto muito, mas não trabalho fiado.";
					Link.l1 = "Oh, diabo!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Vou só terminar minha bebida, capitão, e então vou para o navio. Não se preocupe, estarei lá a tempo.";
			Link.l1 = "Está bem. Se você se atrasar, vou te fazer esfregar o convés!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			DialogExit();
			AddDialogExitQuestFunction("Del_shturman_DlgExit");
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Tá bom, tá bom! Eu me rendo, droga!";
			link.l1 = "Agora você é meu prisioneiro, mas logo vai se ver em St Pierre diante da forca.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Então é isso... Como você soube onde me encontrar?";
			link.l1 = "O Governador me explicou pessoalmente a situação.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Que canalha! Deve ter descoberto meus planos e resolveu me ferrar na frente do covil dele, só pra dar o exemplo pras outras tripulações!";
			link.l1 = "Mais uma ofensa a Sua Excelência, e sua viagem para St. Pierre será rápida e inesquecível.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "É? Não tô falando de vossa excelência, camarada. Tô falando do Jacques, o Justo.\nDroga, os boatos eram verdadeiros! O Barbazon percebeu que eu tava virando uma ameaça, então me entregou pro governador pra me tirar do caminho dele. Por isso você sabia exatamente onde eu tava – e me pegou totalmente desprevenido, ha ha!";
			link.l1 = "Você está delirando. O Governador da Martinica jamais se rebaixaria a negociar com um líder pirata!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "É, claro. Talvez não diretamente, mas acho que ele fez um acordo com o Barbazon. É conveniente pra ele: um pirata perigoso é enforcado, os relatórios ficam bonitos e as 'despesas da operação militar' são justificadas. Eu já servi, sabia? Então eu sei como as coisas funcionam por lá. E você? Serve na guarnição?";
			link.l1 = "Eu sirvo ao meu país, e esta conversa acabou. Bem-vindo à cela.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Calma aí, amigo. Eu não sou castelhano, e hoje não estava no mar para saquear mercadores franceses. Eu tenho princípios, droga! Que tal fazermos um acordo, hein?";
			link.l1 = "Está perdendo seu tempo, pirata. Para a cela com você.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Tentando escapar da forca?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Eu tinha uma pista quente aqui, e te dou uma parte se me deixar ir. Minha vida vale só uns poucos milhares em prata, mas posso te render muito mais – e sem pagar imposto.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "É uma oferta tentadora... Mas a pirataria não é exatamente o meu forte.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Eu não sou um pirata!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Você que decide, camarada. Se quer ser um homem de fortuna ou um capitão sem um tostão, mas cheio de princípios. Se quiser dinheiro de verdade e liberdade, vai ter que se meter em um pouco de tudo. Aproveite qualquer oportunidade.";
			link.l1 = "Você realmente sabe usar as palavras...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Hum... Acho que vou te levar até St. Pierre. Parece ser o certo a fazer.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Então vá para o inferno, então!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Então, temos um acordo?";
			link.l1 = "Sim. Diga quem é o seu líder, e você está livre para ir.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Tem um inglês esperto no Henry, uma barca. Ele está quase terminando sua pequena viagem de comércio, levando mercadorias das plantações francesas para Willemstad por um bom lucro. Logo vai sair da Martinica para Curaçao. É um trabalho fácil – sem escolta, e a barca está cheia de coisas valiosas, mas quase sem defesa. Ele está demorando demais, então os boatos já começaram. Meu conselho, amigo? Não seja tímido na taverna. Com alguns drinques para os locais, eles acabam contando uns segredos.";
			link.l1 = "Por que sem escolta?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "De que outra forma um inglês faria negócios discretamente em Curaçao? A Inglaterra e a Holanda estão em guerra aberta, conseguir uma licença de comércio é complicado e ainda por cima caro.";
			link.l1 = "Mas não há guerra entre França e Inglaterra. O que acontece se eu atacar um navio neutro?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Nenhum, se você for discreto. A tripulação com certeza vai se gabar dos seus feitos heroicos no próximo porto, mas enquanto você não atacar navios ingleses ou holandeses com frequência, não deve ter problemas. Aproxime-se do Henry com bandeira francesa. Carregue os canhões com metralha, reduza a distância, solte a Negra, dispare algumas rajadas e aborde aquela desgraçada. É simples, camarada.";
			link.l1 = "Vamos ver isso. Vou cumprir minha palavra e te soltar. Não me dê motivo para me arrepender.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Não vou. Boa caçada, camarada.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Eu vou cuidar dos seus problemas com jogo. Ei! Se controla, homem! Ou você se recompõe, ou eu mesmo vou te fazer entrar nos eixos.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, me desculpe, mas o senhor está sendo um pouco incômodo.";
			link.l1 = "Sim, claro. Tenham um bom dia, senhores.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Capitão de Maure! Espere!";
			link.l1 = "Sim, tenente?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Mal consegui acompanhar você. Houve... um pequeno contratempo, Capitão. Que confusão!";
			link.l1 = "Respire fundo e se acalme, por favor.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Certo, certo. Escuta, depois que carregarmos os canhões, ainda vai sobrar espaço no porão?";
			link.l1 = "Ainda estou aprendendo, então não tenho certeza absoluta, mas imagino que deveria haver.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Excelente! O Comando quer apoiar a operação em Porto Bello de todas as formas possíveis, então ordenaram que mais duzentos barris de pólvora fossem entregues ao Warlike. Pode não parecer muito, mas alguns tiros extras podem mudar o rumo da batalha!";
			link.l1 = "Muito bem, tenente. Estou pronto para fazer a minha parte. Carregue a pólvora – não me importo nem um pouco.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Obrigado, Capitão. Vou avisar nossa equipe de carregamento imediatamente. Felizmente, eles ainda não terminaram com o "+PChar.Ship.Name+"' ainda. Boa sorte na sua missão!";
			link.l1 = "Obrigado, embora tenha sido bem caótico até agora. Até logo, Tenente.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Meu Deus, Capitão! Graças aos céus que você está bem!";
			link.l1 = "O que diabos aconteceu?! O que fizeram com meu navio?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Eu não sei, Capitão! Eu só estava me despedindo de uma moça daqui que conheci há pouco... Ah, droga! Eugenie!";
			link.l1 = "Ela está morta, "+npchar.name+". Me desculpe, mas precisamos nos concentrar e ver se algum dos nossos tripulantes foi ferido.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Mal nos conhecíamos... Aaah! Droga! Relatando, Capitão: a maior parte da tripulação estava em terra quando aconteceu a explosão – felizmente. Os rapazes estavam aproveitando uma folga antes da nossa próxima grande viagem. Mas a guarda do navio... Receio que não haja sobreviventes. Olhe ao redor! Os destroços feriram ou mataram gente até aqui, neste cais! É um milagre nós dois estarmos ilesos.";
			link.l1 = "E o navio? Ela está bem?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Ela está?! Me desculpe, Capitão. É difícil dizer com certeza, mas parece que a explosão aconteceu no convés superior, não embaixo. Não vejo nenhum incêndio ativo, e parece que escapamos de danos maiores.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "Mas que diabos, Capitão?!";
			link.l1 = "Estou perguntando a mesma coisa, coronel!";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Se cuide, de Maure! Você aceitou esse trabalho da Marinha, assumiu responsabilidade por canhões pesados — propriedade da Coroa, de importância estratégica! Você entende o que esses canhões significam para toda a operação?! Sua negligência colocou quase quatrocentos homens e um navio de guerra francês em risco! Você está prestes a ser julgado por traição aqui!";
			link.l1 = "Calma, coronel! Milagrosamente, parece que meu navio sobreviveu, e sua carga preciosa está quase toda intacta... quase.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "O que você quer dizer com 'na maioria das vezes'?!";
			link.l1 = "Não posso garantir que as duzentas medidas de pólvora, embarcadas de última hora por um dos seus tenentes, não tenham sido danificadas. Elas deveriam ser carregadas por último, e provavelmente foram essas que explodiram.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Que bobagem é essa, Charles? Que tenente? Que pólvora? Eu não dei nenhuma ordem assim!";
			link.l1 = "Esse tenente devia ser do seu destacamento. Não perguntei o nome dele, mas parecia saber da operação.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ah, droga! Parece que os castelhanos também gostam de jogar sujo... Eu vou cuidar dessa situação desagradável, Capitão. Mas você ainda tem um trabalho a fazer: tem certeza de que seu navio está pronto para navegar?";
			link.l1 = "Ela está flutuando, mas com certeza precisa de reparos significativos.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Sem tempo pra isso, Capitão. Zarpem imediatamente e cumpram a missão. Está em jogo algo grande demais pra esperar.";
			link.l1 = "Não podemos ter pelo menos um dia, pelo amor de Deus? O estaleiro local poderia fazer os reparos necessários! E a minha tripulação?! Certamente há feridos!";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = " Caso você não tenha notado, o estaleiro está em chamas. Ainda estamos tentando descobrir se foi intencional ou apenas uma consequência da explosão. Só posso lhe prometer que seus feridos receberão cuidados médicos, e a Coroa arcará com os custos do enterro dos mortos.";
			link.l1 = "Você está falando sério? Isso é o melhor que você pode oferecer?";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Capitão, a França precisa da sua ajuda com urgência. Vou providenciar as tábuas, e se você agir com esperteza, seu navio estará quase totalmente reparado quando chegar à Jamaica.";
			link.l1 = "Com licença, mas quais tábuas? E por que a Jamaica?";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Sua tripulação pode fazer reparos de emergência no mar usando tábuas – o principal material de conserto. E a Jamaica fica bem perto de uma das rotas para Porto Bello. Se não perder tempo, dá para terminar os reparos e recrutar uma tripulação completa por lá.";
			link.l1 = "Muito bem, então. Vou zarpar imediatamente, Coronel.";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Por que a pressa, querido?";
			link.l1 = "Querido, agora não tenho tempo pra isso. Não está vendo o que está acontecendo?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Ah, os problemas de agora são graves, mas posso ver pela sua mão que há mais vindo por aí.";
			link.l1 = "Qualquer um pode perceber isso mesmo sem olhar para a minha mão, que, aliás, está de luva. Muito bem, vou entrar no jogo: quanto custa evitar uma catástrofe hoje em dia?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Eu não tenho esse poder, bonitão. E mesmo que tivesse, não teria como bancar isso. Mas ainda posso te ajudar... com o seu navio. A garota está em um estado lamentável, meu querido.";
			link.l1 = "Eu nunca soube que o seu povo cigano tivesse ambições em carpintaria.";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Você, querida, está longe de ser carpinteira. Acha mesmo que só as tábuas vão consertar o navio? Elas só vão te atrapalhar se não tiver um mestre carpinteiro...";
			link.l1 = "Ou?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Existe um amuleto poderoso, venerado pelos locais. A madeira se curva à sua vontade, e até quem nunca mexeu com carpintaria descobre talento ao usá-lo. É seu por apenas mil pesos, querido.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Muito bem, temos um acordo. Preciso de toda ajuda que puder conseguir.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Não tenho tempo para suas feitiçarias. Vá em paz, bruxa, e não se intrometa.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("You have received Amulet 'Teredo'");
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute aqui, você. Sou um cidadão respeitador das leis desta cidade. Peço que não ande por aí com a espada à mostra como um bandido.","Senhor, por favor, a lei é clara: não se pode andar com armas desembainhadas dentro dos muros da cidade.");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Como quiser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
