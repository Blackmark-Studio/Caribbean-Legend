// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Monsieur, você escolheu um péssimo momento pra bater papo. A guarnição inteira tá te procurando. É melhor dar o fora logo...";
			link.l1 = "Não se preocupe. Não vou demorar.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Bem-vindo, capitão. Gostaria de ouvir uma proposta interessante? ";
				link.l1 = "Por aqui, todo tipo de gente parece ter esse tipo de proposta, e eu sou um homem curioso. O que é? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Bom dia. Bem-vindo à minha botica. Tenho remédios para tratar a maioria das doenças e enfermidades. O que posso lhe oferecer?";
			link.l1 = "Escuta, John, estão dizendo por aí que alguém está morando no seu apartamento, no segundo andar...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Bom dia. Fico feliz em vê-lo na minha botica. Tenho remédios para tratar a maioria das doenças e males. O que posso lhe oferecer?";
				link.l1 = "Olá, senhor Murdock. Estou aqui em nome de Lucas Rodenburg. Ele me enviou até você para tratar de um assunto relacionado a Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Boa tarde. Qual é o seu problema? Tenho xarope para tosse e pó para diarreia!";
				link.l1 = "Olá, Sr. Murdock. Estou aqui em nome de Lucas Rodenburg. Ele me enviou para conversar com você sobre uma questão relacionada a Richard Fleetwood.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, aqui está o cão de aluguel do Rodenburg... Hercule, Longway - poderiam vir aqui?\nMatem esse homem!";
				link.l1 = "Espere, eu tenho uma receita!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Boa tarde. Fico feliz em vê-lo na minha farmácia. Tenho remédios para tratar a maioria das doenças e enfermidades. O que posso lhe oferecer?";
			link.l1 = "Nada no momento, obrigado. Estou me sentindo muito bem.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Olá, visitante inesperado. Você não cobre o rosto com uma máscara e não parece um ladrão. Portanto, concluo que precisa de outra coisa de um pobre boticário. Talvez algo para diarreia?";
			link.l1 = "Olá para você também, Johan van Merden. Trago saudações de Hercule Tonzag. Vejo que conhece o nome.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, então aqui está você. Bem, já conheceu o Hercule? ";
					link.l1 = "Sim. Chegamos a um acordo. John, vou ajudar o Hercule, e tenho várias perguntas para você sobre o Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Olá! Fico feliz em te ver, "+pchar.name+"!";
					link.l1 = "Olá, John. Descobriu alguma coisa sobre o Fleetwood?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Você chegou tarde. O pássaro já voou da gaiola. Charlie Knippel passou por Willemstad e trouxe uma moça de lá para o Richard. Agora eles vão zarpar para a Inglaterra com um esquadrão militar em um ou dois dias. Fleetwood já foi, você não vai vê-lo mais nesta vida.";
					link.l1 = "Droga. Eu tinha esquecido completamente do Richard e perdi a noção do tempo. Até mais.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Bem-vindo de volta, "+pchar.name+"! Nada para você agora. Não há novidades sobre Fleetwood, e Charlie Knippel ainda não voltou de Curaçao...";
					link.l1 = "E ele nunca vai conseguir. Nem ele, nem o seu brigantim.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, temos visitas! Olá, Charlie! Boa tarde, senhorita!";
					link.l1 = "Boa tarde, John! Permita-me apresentar minha acompanhante, a noiva do Richard, a encantadora Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Fale mais baixo... O que você vai fazer agora?";
					link.l1 = "Próximo? Eu preferia dormir um pouco, mas infelizmente não tenho tempo pra isso. Vou arrancar o Fleetwood do buraco onde ele se escondeu e terminar o trabalho do Hercule.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Terminou de escrever? Deixa eu ver... Meu Deus, Charlie, você é mesmo um doido varrido! Não acha que exagerou um pouco nos detalhes? Quero dizer, a parte sobre os dedos, as orelhas e o rosto da senhorita Shneur? Você tem um talento meio doentio, isso é certo. Droga, acho que vou perder o almoço!";
					link.l1 = "Estou blefando, John. Não vou matar a garota. Eu poderia fazer ela perder um dedo... Mas nada além disso. Ela ainda tem mais nove, afinal.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Deu tudo certo? Eu vejo nos seus olhos – você conseguiu!";
					link.l1 = "Sim. Fleetwood aceitou meus termos. A armadilha está se fechando. Agora é só esperar.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, bem-vindo de volta, meu amigo! O que você pode me contar?";
					link.l1 = "Fleetwood está morto. Tudo saiu conforme o planejado. Ele chegou à ilha, onde eu preparei uma emboscada na praia. Lutou bastante, mas não adiantou. Só um de nós saiu andando daquela praia.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Certo "+pchar.name+", eu tenho uma proposta séria para você. O assunto sobre o qual vou falar é muito perigoso, mas, considerando a forma como você lidou com o Fleetwood, tenho certeza de que você dá conta. Você tem um... dom raro para resolver problemas difíceis.";
					link.l1 = "Fico lisonjeado. Continue falando.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Bem-vindo de volta, "+pchar.name+"! Alguma novidade boa pra mim?";
					link.l1 = "John, de agora em diante você pode dormir sem uma faca debaixo do travesseiro. Lucas não é mais uma ameaça para você. Ele está preso e trancado, e em breve será enviado para a Holanda, onde será julgado por insurreição, tentativa de assassinato e outros delitos.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Que bom te ver, "+pchar.name+"! Você está vivo – e isso é ótimo. Alguma novidade?";
					link.l1 = "Sim. Van Berg se foi de vez. Como você disse, ele me encontrou e atacou no pior momento possível. Van Berg era um osso duro de roer, mas no fim eu dei conta dele.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Precisa de mais alguma coisa?";
			link.l1 = "Não, John, nada. Estou indo embora.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Boa tarde. Fico feliz em vê-lo na minha botica. Tenho remédios para a maioria dos males e enfermidades. O que posso lhe oferecer?";
			link.l1 = "Nada no momento, obrigado. Estou me sentindo muito bem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Não faço ideia do que está falando, senhor. Quem é Lucas Rodenburg? Não tenho negócios com os holandeses. Deve estar enganado.";
			link.l1 = "O quê? O senhor Rodenburg me mandou até você!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Deixe-me dizer mais uma vez – não conheço nenhum homem chamado Mynheer Rodenburg. Quanto aos holandeses, não faço negócios com eles. Só há duas coisas que não suporto neste mundo: gente intolerante com a cultura dos outros, e os holandeses. Então, se não precisa de nenhum remédio, por favor, me deixe trabalhar.";
			link.l1 = "Cada vez mais estranho...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Então, então... Você veio da parte do senhor Rodenburg? Certo. Estou ouvindo.";
			link.l1 = "Preciso marcar um encontro com o capitão Fleetwood em um lugar discreto. Peguei emprestado o 'Mirage' do Jacob van Berg, o corsário holandês que o Sr. Fleetwood está tão ansioso para capturar. Gostaria de avisá-lo que o 'Mirage' estará convenientemente fundeado na costa de Dominica em breve. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Jacob te deu o navio dele? Hm, então agora você precisa de alguém para avisar o Sr. Fleetwood que o 'Mirage' logo estará na costa da Dominica, já que por certos motivos você mesmo não pode contar isso ao Richard...";
			link.l1 = "Exatamente. O senhor Rodenburg recomendou que eu tratasse desse assunto com você.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "Neste caso, Charlie Knippel é o homem que você procura. Um amigo leal do Fleetwood... e também seu espião. Fale com ele e conte tudo o que quiser que Richard saiba. Mas cuidado, Knippel pode parecer bem simples, mas de bobo não tem nada.\nVocê o encontra numa cabana pequena, não muito longe da praia. Ele deve estar lá.";
			link.l1 = "Entendi. Obrigado, senhor Murdock. Até logo!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Sério? Eu achei que o pobre Gaston já estava queimando no inferno fazia tempo.";
			link.l1 = "Pode ser, mas com certeza não existe ninguém como o Gaston. Encontrei a cabeça dele no esconderijo de um velho judeu numa ilha secreta. Mesmo assim, ele conseguiu mandar lembranças pra você. Também disse que temos um inimigo em comum: o senhor Rodenburg. Tonzag comentou que talvez você tenha documentos importantes para o Lucas, que poderiam tirá-lo do buraco onde se esconde em Curaçao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Ele estava certo. É o meu arquivo que tira o sono do Rodenburg. Parece que ele ainda está por aqui só por causa disso. A questão é que prometeram a ele um cargo confortável no Comitê de Diretores da Companhia, lá nas Províncias Unidas. Se as informações deste arquivo, que contém muita coisa interessante sobre o passado e o presente do Lucas, vierem a público, as ambições dele vão por água abaixo. Nesse caso, o melhor que pode esperar é ser decapitado em vez de enforcado.";
			link.l1 = "Me entregue o arquivo, e eu cuidarei do nosso inimigo.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Você deve me achar um tolo. Só estou vivo porque ainda estou com isso comigo. Como posso saber que você não está trabalhando para o Lucas agora?";
			link.l1 = "Você vai ter que acreditar em mim - ou morrer.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Resposta errada, você vai morrer aqui e agora! Longway, gongji!";
			link.l1 = "Oh ho, o chinês sai das sombras! Fiquem tranquilos, vou acabar com vocês dois!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Finalmente, você está de pé de novo. Tive medo que não fosse acordar.";
			link.l1 = "O quê...? Quem é você? Onde diabos eu estou? Como vim parar aqui?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Calma, não faça tantas perguntas de uma vez, não é bom se empolgar tanto assim. Meu nome é John Murdock, sou farmacêutico aqui em St. John's. Você desmaiou numa briga com os homens do Fleetwood. Preciso dizer que eles te deram uma bela surra... Foi o Hercule quem te trouxe aqui para minha botica e, bem, tratei dos seus ferimentos com minhas poções e remédios.";
			link.l1 = "Hercule? Quem? O homem que veio me ajudar na rua? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Sim. É ele mesmo. Aliás, ele quer falar com você. Você precisa encontrá-lo na cidade. Consegue andar? Ótimo. Saia à noite – use o túnel secreto que começa atrás da porta no térreo da minha casa. Não saia antes de escurecer – os homens do Fleetwood estão te procurando.";
			link.l1 = "É... Onde está meu navio?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Seu navio foi apreendido e sua tripulação se dispersou, temendo serem mortos pelos homens de Fleetwood. Sinto muito.";
				link.l1 = "Merda...";
			}
			else
			{
				dialog.text = "Ela está no porto, no lugar de sempre.";
				link.l1 = "Ufa... que bom saber disso. Achei que tinha perdido ela.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Você deveria conhecer o Hercule. Vá até a cidade à noite pelo túnel secreto. Ele vai se aproximar de você. Agora descanse um pouco, preciso voltar ao meu trabalho.";
			link.l1 = "Certo, John. E... obrigado pela sua ajuda e por ter me curado!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood? O que você quer saber sobre ele?";
			link.l1 = "Tudo. Me conte tudo o que você sabe. Pelo visto, não é segredo pra você por que o Hercule veio pra Antígua. Estou do lado dele.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Muito bem. Capitão Richard Fleetwood da Marinha Real— quer dizer, da Comunidade... droga, sempre esqueço que aquele fanático do Cromwell está no comando e mudou o nome. De qualquer forma, Fleetwood é um bom combatente e um marinheiro experiente. Ele comanda uma escuna chamada 'Valkyrie'— um navio excelente, diga-se de passagem, com uma tripulação de marinheiros e fuzileiros de elite. Ele trava uma guerra particular contra as Províncias Unidas em geral e contra a Companhia Holandesa das Índias Ocidentais em especial. Já saqueou incontáveis navios mercantes holandeses e fez o preço do seguro disparar. O governador de Curaçao colocou uma recompensa recorde pela cabeça dele.";
			link.l1 = "Hum... Parece um tanto estranho um oficial da 'Marinha da Commonwealth' virar pirata...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Sim, de fato. Ele está andando na corda bamba. Os ingleses não reconhecem oficialmente suas ações e se recusam a se envolver, mas na verdade o incentivam nos bastidores. Tenho motivos para acreditar que ele está de alguma forma ligado à rede de espiões inglesa no Caribe, e esses canalhas não são gente com quem se deva brincar";
			link.l1 = "Um homem sério... Só isso? Hercule me falou de um dos assistentes dele... outro Charlie... como é mesmo o nome... Canister? Cannonball?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Sim, existe esse sujeito. Charlie Knippel foi artilheiro-mor na Marinha Inglesa, agora está aposentado. Hoje leva uma vida tranquila na costa. Ele é os olhos e ouvidos de Fleetwood em St. John's, então tome cuidado com ele e nem pense em perguntar sobre Richard – você pode acabar na prisão ou coisa pior.";
			link.l1 = "Entendi. Você pode me contar mais alguma coisa relevante sobre o Fleetwood?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Um ídolo para todas as mulheres de Antígua, dos dezesseis aos sessenta anos. Parece que é só isso que dá pra dizer sobre ele. Bem, acho que você já sabe o que aconteceu com ele agora. Ele fica deitado, lambendo as feridas.";
			link.l1 = "Ele deve ter algumas fraquezas ou vícios...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "O que você quer dizer?";
			link.l1 = "Bem, talvez ele goste de apostar, beba demais ou não resista a uma bela mulher – algo assim. Ele é casado?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Não, é solteiro. Quanto ao que você mencionou – ele não é conhecido por nada disso.";
			link.l1 = "Entendo. Mas talvez ainda haja algo especial nele? Mesmo alguém como ele deve ter algum ponto fraco!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Não sei. Olha, vamos fazer assim. Volte daqui a uma semana e eu vou investigar a vida pessoal do Fleetwood. Combinado?";
			link.l1 = "Fechado. Obrigado, John! Estarei aqui em uma semana.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Sim, mas não muito, infelizmente. E receio que não seja de grande utilidade, de qualquer forma.";
			link.l1 = "Desembucha! Cada pequeno detalhe é importante se tiver qualquer relação com o Fleetwood.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Não faz muito tempo, Richard resgatou dois refugiados judeus de uma ilha desconhecida – um velho e sua filha, a caminho de Willemstad. O navio em que viajavam foi afundado por piratas. Fleetwood os trouxe secretamente para Curaçao, arriscando o próprio pescoço. Já se passaram alguns meses desde então. Agora ele enviou seu fiel cão, Charlie Knippel, para Willemstad...";
			link.l1 = "Hmm... Como isso está conectado?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Consegui descobrir que o Charlie recebeu uma ordem para trazer uma moça de Willemstad, uma judia chamada Abigail Shneur. Sim, a mesma garota da ilha. Parece que o Richard se apaixonou por ela, já que está mandando seu melhor agente para buscá-la.\nÉ só isso. Não sei se isso ajuda em alguma coisa.";
			link.l1 = "Oh ho ho! Hahaha! Parece que nosso solteirão convicto caiu pelos encantos astutos da judia. Excelente trabalho, John, obrigado! Agora, quando nosso amigo Knippel parte para Curaçao?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Ele partiu ontem.";
			link.l1 = "E em qual navio?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Eu sabia que você ia perguntar isso. Ele está em uma brigantina a serviço da Commonwealth—ah, que se dane, da 'Royal Navy'. O nome dela é 'Zeekalf'.";
			link.l1 = "'Zeekalf'? Esse é um nome bem holandês para um navio inglês... ahhh, entendi.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Você pensa rápido... O nome antigo dela era 'Royal Mary', mas para esta viagem ela foi batizada de 'Zeekalf'. E está navegando sob a bandeira holandesa.";
			link.l1 = "Sua ajuda foi indispensável, John. Estou partindo agora. Voltarei em breve, e vou precisar do seu quarto no segundo andar, onde você me hospedou enquanto eu me recuperava.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "O que você está aprontando?";
			link.l1 = "Eu te conto tudo quando voltar. Me deseja sorte, John! Até logo.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Sério? Por que você tem tanta certeza?";
			link.l1 = "Porque o Charlie está no fundo do mar, servindo de comida pros peixes. Eu abordei o 'Zeekalf' e mandei o Knippel pro inferno. Claro, antes dei uma interrogada nele... Ele carregava uma carta que me permitiu me passar pelo Knippel quando fui falar com a nossa judia Abigail, a querida do nosso valente Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... Isso é esperto. Então, você está dizendo que...";
			link.l1 = "Sim. Trouxe a judia para Antígua. Ela está a bordo do meu navio. Agora tenho uma carta na manga no meu jogo com Fleetwood! Ele fará qualquer coisa por ela...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Tem certeza? Pode ser que as coisas não sejam tão simples quanto você dá a entender...";
			link.l1 = "Ah, sim, tenho certeza absoluta. Pela carta, entendi que o pai da Abigail era contra o casamento dela com o Richard por causa de dinheiro. Eu sei, típico sogro judeu. Então o Fleetwood resolveu pagar um dote ao pai dela – 200.000 pesos! Me diga, quantas moças no mundo valem tanto dinheiro assim?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Certamente não era uma judia! Nunca conheci uma cristã que valesse tanto assim na minha vida, isso é certo. "+pchar.name+", você é um canalha astuto. O que vai fazer com ela?";
			link.l1 = "Vou trazer a judia para cá e vamos mantê-la no seu quarto. Vou dizer a ela que Richard foi para o mar e ainda não voltou, então ela será nossa hóspede por uma semana. Ela pensa que eu sou Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "Interessante. Então você decidiu deixar a garota na minha casa? Hmm...";
			link.l1 = "John, ela é judia. Uma estrangeira sem pátria, trazida de uma colônia holandesa. Aqui em St. John's ela não é ninguém, ninguém a conhece. Fique tranquilo, podemos fazer o que quisermos e ela não vai ousar dizer uma palavra. Não tem um tostão ou um amigo sequer. E de qualquer forma, ela não será nossa hóspede por muito tempo. Vou atrair Fleetwood usando ela como isca, e depois disso não precisaremos mais dela.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Você está começando a me assustar, Charles. Você não vai se aproveitar dessa garota, vai? Ou acabar com ela do mesmo jeito que fez com o Knippel?";
			link.l1 = "Não, claro que não. 'Canalha astuto' eu posso ser, mas não sou inimigo de moças bonitas – judias ou cristãs. Nem das feias, aliás. Se ela se comportar, vou levá-la ao pai dela em Willemstad quando tudo isso acabar. O velho sovina provavelmente vai se ajoelhar e me agradecer por tê-la salvado daquele inglês traiçoeiro.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Ela tem um papel a cumprir nessa farsa. Quando o espetáculo acabar, não terei mais utilidade para ela.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Entendi, então por enquanto eu preciso cuidar dela.";
			link.l1 = "Não vou insistir, amigo. Se você for totalmente contra isso, ela pode ficar a bordo do meu navio. Mas aí vou ter que acorrentá-la por segurança e mantê-la no porão com os ratos para protegê-la da minha tripulação. Ter uma mulher a bordo é novidade para eles, sabe. Seria uma pena tratar uma moça tão bonita desse jeito.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Entendi, então por enquanto eu preciso cuidar dela.";
			link.l1 = "Não vou insistir, amigo. Se você for totalmente contra isso, ela pode ficar a bordo do meu navio. Mas aí vou ter que acorrentá-la por segurança e mantê-la no porão com os ratos para protegê-la da minha tripulação. Ter uma mulher a bordo é novidade para eles, sabe. Seria uma pena tratar uma moça tão bonita desse jeito.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Entendi. Muito bem, traga ela aqui. É meu dever ajudá-lo na sua luta contra Fleetwood. Traga ela e eu vou preparar o 'quarto de hóspedes' para ela.";
			link.l1 = "Obrigado, John. Eu sabia que podia contar com você.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh! É um prazer. Fico feliz em receber uma mulher tão importante e... elegante. Senhorita, poderia subir ao segundo andar, por favor? O jantar está à sua espera e a cama já está pronta. Tenho certeza de que vai querer descansar bem depois de uma viagem tão longa.";
			link.l1 = "Sim. Abigail deve estar cansada depois de uma viagem tão longa desde Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Você já tem um plano?";
			link.l1 = "Sim. Precisamos escrever uma carta para o Richard exigindo um resgate pela Abigail. Marcar um encontro em alguma ilha deserta — como Turks. E se ele não aceitar, digamos assim, mandamos a namorada judia dele de volta em pedaços.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Por que tanta complicação com uma ilha desabitada?";
			link.l1 = "Território neutro. É mais seguro. De qualquer forma, não vou levar a Abigail. Preciso do Fleetwood. Com certeza ele prepararia uma emboscada em Antígua, mas em Turks ele não teria essa vantagem.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Justo. Quem vai entregar a carta? É muito perigoso.";
			link.l1 = "Um estranho. Escolha um bêbado da taverna, alguém que pareça confiável. Ele vai topar qualquer coisa por umas moedas de rum. Se Richard matá-lo num acesso de fúria, mandamos outro. E vamos incluir um dos dedos da Abi na carta. Isso vai deixar ele bem mais obediente.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Não se preocupe, John. Tenho certeza de que não vai chegar a esse ponto. Você só precisa encontrar um mensageiro e eu escrevo a carta imediatamente. Você tem papel e tinta?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Sim, eu sei. E por acaso conheço um bêbado perfeito também. Recomendo o Jack Harrison. Ele passa todas as noites na taverna, enchendo a cara de rum. Você vai encontrá-lo sem dificuldade.";
			link.l1 = "Ótimo, traga-me pena e tinta e vou escrever a carta de resgate para Richard.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Quando você vai entregar a carta para ele? Vai ficar de olho na entrega enquanto acontece?";
			link.l1 = "Claro. Richard não é bobo, mas duvido que ele vá se arriscar. Pelo menos, espero que não. Não quero machucar a garota, mas farei isso se for preciso. Bem, está na hora de encontrar o bêbado que você mencionou. Jack... qual era o nome completo dele?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "O nome dele é Jack Harrison. Ele costuma ir à taverna à noite. Tome cuidado!";
			link.l1 = "Vai ficar tudo bem. Espere por mim.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Bem, eu não diria isso. Fleetwood é astuto e perigoso. Além disso, é um espadachim habilidoso e um marinheiro experiente. Ele não será uma presa fácil.";
			link.l1 = "Eu parei de escolher o caminho mais fácil quando cheguei ao Caribe. Bem, John, está na hora de eu ir. Aliás, você comentou que o nosso valente Fleetwood tem um bom navio, não foi?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Ele tem a melhor brigue que já vi. E olha que já vi muitas.";
			link.l1 = "Isso é bom. Gosto de bons navios. Hora de levantar âncora!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Estou sem palavras! Uma combinação excelente, uma ideia brilhante e uma execução impecável! Meus parabéns, "+pchar.name+"! E você ainda conseguiu capturar a chalupa dele como prêmio!";
				link.l1 = "Obrigado! E onde está o Hercule? Gostaria de vê-lo. Da última vez que nos encontramos, ele me disse que eu poderia encontrá-lo com a sua ajuda.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Uma combinação excelente, uma ótima ideia e uma execução magistral! Meus parabéns, "+pchar.name+"!";
				link.l1 = "Obrigado! E onde está o Hercule? Gostaria de vê-lo. Da última vez que nos encontramos, ele disse que eu poderia encontrá-lo com a sua ajuda.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Estou esperando por ele a qualquer momento agora. Ele deve chegar aqui pelo túnel secreto. E você deveria se explicar para Abigail. Ela começou a se preocupar com a ausência do Richard.";
			link.l1 = "Certo, mas não deveríamos mandá-la para casa?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Ainda não... Preciso falar com você antes. Mas antes, espere o Hercule chegar. Vá consolar a Abigail. Conte uma história pra ela, invente alguma coisa. Depois venha para o porão. Certo?";
			link.l1 = "Sim, senhor, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Bem, chegou a hora de colocar as cartas na mesa. Como você já deve ter percebido, eu não sou apenas um simples boticário. Meu verdadeiro nome é Johan van Merden, e até pouco tempo atrás eu era agente da Companhia Holandesa das Índias Ocidentais e braço direito do vice-presidente, Lucas Rodenburg.";
			link.l1 = "Sério! Isso é interessante...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "It's different now. Lucas wants to leave the game and return to the Netherlands, so he needs to bury everything and everyone connected to his past\nI think I am still breathing only because of my archives, which contain all the information about Lucas's crimes... like the story of the 'ghost ship', which is just an ordinary pirate vessel under the command of the reckless and unprincipled scoundrel Jacob van Berg. Rodenburg hired the man to plunder and sink English trade ships\nVan Berg is also responsible for sinking the fluyt with Abigail and her father aboard. Abigail is an important figure in this game; Rodenburg also wanted her hand and heart, just like Fleetwood did, so I was quite surprised when you brought her here...";
			link.l1 = "Rodenburg... é dele que o pai excêntrico da Abigail estava falando!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Yes, that is why I want her to stay here for a while. She might be my last ace in the game against Rodenburg, though I would prefer not to use her any further; she is a good girl, I don't want her to suffer. I think that Lucas would choose my archive over her, if the choice were presented.\nSo, I propose that you become my ally in the game against Lucas... get rid of him, use any means necessary. The reward will be substantial.";
			link.l1 = "Hum... Não acho que vai ser mais difícil do que com o Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "No, you're wrong. In the end, Fleetwood was a lone wolf, acting on his own. Rodenburg is vice president of the Company. He is a very influential man; only the governor of Curacao has more power. Jacob van Berg is his agent, a very dangerous man. Lucas sits on his arse in Willemstad under the protection of the Company's guardsmen; they are as good as Fleetwood's men.\nThis is not going to be easy.";
			link.l1 = "As regras do jogo são as mesmas – atrair o tigre para fora da toca... Já tenho um plano. O que mais você pode me contar sobre o Lucas?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Bem, já te contei quase tudo. Ele tem um navio veloz chamado 'Meifeng' - Vento Belo. O capitão é um chinês chamado Longway - homem de confiança de Rodenburg. Ele também é um inimigo que você não gostaria de enfrentar. Não há amadores na tripulação de Lucas. ";
			link.l1 = "Já tínhamos uma carta na manga desde o começo – seu arquivo. Se ele valoriza mais a própria vida do que a judia, vai fazer de tudo para manter as informações do arquivo em segredo... Mas... esse arquivo existe mesmo, John? Ou você está blefando?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "O arquivo realmente existe. E o Lucas sabe disso. Já pensou em alguma coisa?";
			link.l1 = "Eu sei. John, se você fosse mesmo agente da Companhia, deveria saber de uma coisa.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "O quê exatamente? Pergunte.";
			link.l1 = "Preciso interceptar um navio da Companhia. De preferência, uma embarcação sem escolta — um mensageiro ou algo do tipo. Você pode me contar algo sobre isso?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Não tenho essa informação. Espere! Sei com certeza que a Companhia mantém um navio-paquete nas rotas entre Philipsburg e Willemstad uma vez por mês. Ele transporta documentos de negócios. É uma escuna chamada 'Hoop'.\nEla deve partir de Philipsburg hoje ou amanhã.";
			link.l1 = "Isso mesmo! Agora só preciso ir até as praias de São Cristóvão. A rota marítima para Curaçao passa bem ali.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Boa sorte, "+pchar.name+". Não vou te perguntar sobre os detalhes do seu plano. Estarei esperando pelo seu retorno!";
			link.l1 = "Vai dar tudo certo, John. Cuide da judia e trate-a bem!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Incrível! Eu não posso acreditar no que estou ouvindo! Como isso aconteceu?";
			link.l1 = "Capturei o navio de correio e enviei uma carta para Lucas em nome do Fleetwood, dizendo que tomei posse de um certo arquivo pertencente a um boticário de St. John's, e que em breve as provas de todas as suas falcatruas seriam conhecidas daqui até Amsterdã e Londres. Achei que ele fosse começar a me caçar, mas aconteceu o contrário.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas acusou Matthias Beck de traição e de negociar com os ingleses, mandou prendê-lo e se instalou no palácio do governador. Muito provavelmente, ele mandou eliminar o capitão do bergantim. Depois, ordenou ao seu fiel chinês do Meifeng que afundasse o navio com o diretor da Companhia, Peter Stuyvesant, a bordo!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg é um homem implacável. Mas nem eu imaginei que ele pudesse ir tão longe...";
			link.l1 = "Eu capturei o Meifeng e interroguei o Longway. Ele me contou tudo. Encontrei o Stuyvesant e o alertei sobre as intenções do Rodenburg, então navegamos juntos para Willemstad. Stuyvesant libertou Beck e prendeu Lucas. Ele está na prisão agora.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Você tem um talento de verdade, meu amigo... Deveria fazer carreira na Marinha da Companhia ou virar político nas Províncias Unidas – tem tudo para virar governador! E o que fez com o Longway?";
			link.l1 = "Eu o deixei ir. Ele se rendeu com honra, então não lhe fiz nenhum mal.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "Isso é bom. Longway é um homem decente, diferente do antigo chefe dele. Bem, "+pchar.name+", você fez um ótimo trabalho! Vou preparar sua recompensa, mas vou precisar de um tempo... Enquanto isso...";
			link.l1 = "John, pra ser sincero, tem um problema. Primeiro o Longway, depois o Rodenburg, os dois me disseram que o Jacob van Berg está me caçando. Isso é tão grave assim?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, isso é sério. Ele é um pirata impiedoso, um marinheiro e lutador habilidoso que faz o Fleetwood parecer um gatinho. Um caçador profissional. Foi ele quem destruiu os navios por ordem do Rodenburg.\nEle vai te encontrar, então você precisa se preparar. Eu mesmo devo tomar cuidado.";
			link.l1 = "Como posso encontrar esse van Berg?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Não sei. Lucas e Longway eram os únicos que sabiam onde encontrá-lo. Então tome cuidado e fique atento\nVou fechar o lugar. Use o túnel secreto se quiser me ver. E leve a judia embora, é perigoso demais para ela ficar aqui.";
			link.l1 = "Não se preocupe, John. Deixa ele aparecer que eu resolvo. Onde está a Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Ela foi à igreja. Sinto muito por ela. Ela tem estado muito abalada ultimamente.";
			link.l1 = "Bem... Que surpresa agradável. Talvez ela tenha percebido que Cristo é o Messias que seu povo tanto esperou. Bem, está na hora de levá-la de volta ao pai.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Ela queria te ver. Tenho certeza de que ela vai pedir para você levá-la de volta para casa.";
			link.l1 = "Abi, hein?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Bem , tenho que admitir que nos tornamos amigos. Não me arrependo de ela estar morando na minha casa, e graças a Deus ela nunca saberá por que foi trazida para cá.";
			link.l1 = "Certo, John, vou até a igreja encontrar Abigail. Depois sigo para Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Você... quebrou as bolas dele? Ah - uma metáfora. Bem, com ou sem bolas, você conseguiu! Parabéns!";
			link.l1 = "Eu não mentiria pra você, heh. Agora pode respirar aliviado, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Finalmente! Acho que é melhor deixar de lado todos esses jogos políticos e intrigas. Agora é hora de falar sobre a sua recompensa pelo trabalho.";
			link.l1 = "Bem, eu certamente agradeceria por isso.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Vou deixar o Caribe para sempre. Como forma de agradecer pela sua ajuda e por me resgatar das mãos de Rodenburg, estou lhe dando a escritura desta casa e da minha botica. Agora tudo é seu. Pegue as chaves.";
			link.l1 = "Que maravilha! Estou realmente feliz. Você tem uma casa muito confortável e uma adega aconchegante...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "E também, por favor, aceite esta quantia modesta de 100.000 pesos e este mosquete. Ele já me serviu fielmente, e tenho certeza de que servirá bem a você também.";
			link.l1 = "Eu não vou recusar presentes assim!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "No quarto lá em cima você vai encontrar um jovem filósofo natural. Ele é o melhor boticário que conheço. Foi ele quem preparou essas misturas que te ajudaram a se recuperar em poucos dias. Cuide da mesada dele e o conhecimento dele vai compensar todos os seus gastos com juros.";
			link.l1 = "Meu próprio rato de biblioteca? Muito bem, eu vou cuidar dele.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Tenho que me despedir agora. Vou até o porão arrumar minhas coisas. Amanhã não estarei mais aqui – vou zarpar de Antígua. Fico feliz por ter te conhecido e sou grato por você estar do meu lado, e não do lado dos meus inimigos.";
			link.l1 = "Também fico feliz em conhecê-lo, John. Talvez a gente se encontre de novo...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Nem nesta vida, meu amigo. Vou juntar minhas coisas. Adeus, "+pchar.name+"!";
			link.l1 = "Até logo, John! Boa sorte pra você!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, meu senhor, não dê ouvidos a essas bobagens. Não tem ninguém lá. É só o meu laboratório, estão preparando umas misturas, sabe...";
			link.l1 = "Falando sério agora, John. O nome Gino Gvineili te diz alguma coisa?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! Eu vejo nos seus olhos – estou certo... É lá que ele mora e para quem prepara suas ervas!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Senhor, estou lhe dizendo mais uma vez - não há ninguém aqui.";
			link.l1 = "Vamos deixar as desculpas de lado, John. Não vou fazer mal ao seu alquimista – mas se o padre Vincento de Santiago o encontrar, não posso garantir nada. O inquisidor já está planejando mandar seus 'Domini Canes' para Antígua...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "O que você quer dele?";
			link.l1 = "Só para conversar. Ele tem algumas informações bastante importantes para mim. Prometo que não vou entregá-lo à Inquisição, nem vou lhe fazer mal de forma alguma.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino é um sujeito gentil. Não acredite em nada do que o Padre Vincenzo disse sobre ele. E lembre-se – eu vou defender meu alquimista.";
			link.l1 = "Eu te dei minha palavra. Isso não basta pra você?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Suba as escadas, então. A porta está aberta. E espero que cumpra sua palavra.";
			link.l1 = "Pode deixar, eu vou.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Capitão, não gostaria de se familiarizar com as artes herméticas? Isso pode ser muito útil para você.";
			link.l1 = "Me desculpe, mas minha ocupação é um pouco diferente. Estou acostumado a segurar o cabo de uma espada – não frascos ou tubos de ensaio.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'Há mais coisas entre o céu e a terra do que sonha a sua filosofia.' Claro, adoraria. O que é preciso?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Como quiser. Eu só ofereci...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Você deveria aprender a misturar ervas com as próprias mãos. Mas não vai conseguir sem um kit de alquimista. Dê uma olhada nesta bolsa. Ela contém tudo o que um aspirante a alquimista precisa – tubos de ensaio, frascos, um alambique, espátulas, tubos de vidro, um bico de gás e muitas outras coisas parecidas...";
			link.l1 = "Muito interessante! E o que posso fazer com isso?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Bem, você não vai conseguir transformar chumbo em ouro, mas vai poder misturar ingredientes seguindo várias receitas e assim obter poções e outras coisas úteis.";
			link.l1 = "Receitas?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "True. You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there\n Use your alchemy tools, find or buy a mortar and pestle, look for a crucible; alas, I don't possess an extra one to give you. Herbs, spirits, potions, minerals, garbage – everything will do, provided you have the right recipe and tools.";
			link.l1 = "Muito interessante. E quanto você quer por esse kit?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Vinte mil pesos. Este é um kit de primeira e vai se pagar rapidinho.";
			link.l1 = "Está tirando sarro de mim, não é? Uma bolsa com vidrarias pelo preço de uma chalupa? Não, vou deixar passar.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Concordo. Acho que vai ser interessante tentar fazer algo com as minhas próprias mãos.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Você não vai se arrepender dessa compra, tenho certeza absoluta. É muito mais vantajoso preparar as poções você mesmo, conforme precisar, do que ficar indo às barracas dos herbalistas comprar tudo aos poucos. Além disso, nem sempre vai ser possível encontrar tudo o que precisa para vender. ";
			link.l1 = "Vamos aprender. Acho que consigo fazer isso!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("Ladrão, senhor! Guardas, peguem ele","Ladra, menina! Guardas, peguem ela")+"!!!","Olha só isso! No momento em que me perdi em contemplação, você resolveu mexer no meu baú! Ladrão! Peguem o ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Droga!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
