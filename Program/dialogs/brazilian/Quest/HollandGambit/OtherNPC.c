// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug. Avise os desenvolvedores.";
			link.l1 = "Eu vou!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Que sorte a minha! Capitão, por acaso preciso muito de uma escolta para Philipsburg, e é urgente...";
			link.l1 = "Você é Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Mas que diabos, já sou mais famoso que o vice-rei! Quem é você? O que quer?";
			link.l1 = "Eu sou o Capitão "+GetFullName(pchar)+". Fui enviado até você por Lucas Rodenburg. Estou autorizado a colocar você e seu navio sob minha proteção.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, o senhor Rodenburg deve ter ouvido meus pedidos de ajuda! Veja, há um corsário...";
			link.l1 = "Vamos pular os detalhes da sua história, eu já os conheço.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Claro! Já perdi tempo demais... Preciso chegar a Philipsburg em no máximo duas semanas.";
			link.l1 = "Então vá para o seu navio e prepare-se para zarpar. Vamos partir imediatamente!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Muito obrigado pela sua ajuda, capitão! Sua proteção chegou na hora certa. Por favor, aceite minha gratidão e estes 5.000 pesos.";
			link.l1 = "Hum... Esta não é uma recompensa muito generosa por salvar uma vida...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Além disso, vou mandar uma carta para o senhor Rodenburg assim que tiver oportunidade – elogiando ao máximo suas ações. Agora preciso ir.";
			link.l1 = "Bem, então adeus, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Senhor! Espere... parece que você deixou cair alguma coisa...";
			link.l1 = "O quê? Ah?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Desculpe, meu amigo – precisei te dar um golpe leve pra você não causar confusão. Imagino que sua cabeça esteja doendo, mas enfim, você vai sobreviver. Se sobrar tempo pra isso...";
			link.l1 = "Quem é você, diabos, e o que está acontecendo aqui?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Calma, calma, meu amigo – senão vou ter que te acalmar de novo. Não queremos que aqueles soldados entrem aqui, batendo suas espadas velhas, não é? Precisamos conversar em paz.";
			link.l1 = "Me devolva minha espada, seu bastardo, e a gente vai conversar numa boa, eu juro!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Você é um sujeitinho esperto, não é? Não precisa sacar a lâmina por enquanto. Me diga o que quero saber e, talvez, você saia daqui inteiro. Fui claro? Então vamos conversar um pouco.\nVai ficar calado? Ótimo, então temos um acordo. O que você levou do Rodenburg para o banqueiro?";
			link.l1 = "Uma carta.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Esperto. Eu sei que não era um buquê de margaridas. O que tinha naquela carta, garoto?";
			link.l1 = "Como eu vou saber? Não costumo ler a correspondência que me confiam. Vai ver era uma carta de amor. Você sabe o que dizem sobre gente poderosa...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Um capitão honesto é coisa rara de se ver nesses tempos miseráveis. Bem, isso não é boa notícia pra você. O que aquele maldito banqueiro disse quando recebeu o pacote? Que tipo de negócio ele tem com os holandeses?";
			link.l1 = "Estão negociando perfume contrabandeado da França... ou esterco de vaca da Baviera, eu acho.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "A pergunta era sobre compensação por alguma coisa. É tudo o que eu sei.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Você é um sujeito corajoso... E ainda tem senso de humor. Seria uma pena matar você. Gaston teria gostado de você. Mas... fique aqui por enquanto. Preciso ir checar uma coisa, e Miguel vai cuidar de você enquanto eu estiver fora.";
			link.l1 = "Eu juro, 'meu amigo' – você vai se arrepender disso! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Lá se vai a arrogância... Quando as coisas apertam, nosso valente capitão até que mostra um pouco de juízo. Podia ter feito isso bem antes e nos poupado tempo e dor de cabeça. Enfim, preciso ir checar uma coisa, mas depois volto e conversamos, se ainda for necessário, claro. Fique aqui por enquanto. O Miguel vai cuidar de você enquanto eu estiver fora.";
			link.l1 = "Eu juro, 'meu amigo' – você vai se arrepender disso! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Mas é claro. Fique quieto, 'herói' – talvez ainda dê tudo certo.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Fique aqui e torça para que sua flexibilidade valha a pena.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Que diabos?!";
			link.l1 = "Prepare-se para morrer, seu canalha!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Que confusão! Eu estava me perguntando o que era todo esse barulho. Meus parabéns – você é mesmo esperto!";
			link.l1 = "Mais esperto do que você imagina... Vamos ver agora do que você é capaz contra um adversário armado!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "O senhor Lucas Rodenburg quer vê-lo imediatamente. Vá até ele agora mesmo.";
			link.l1 = "A caminho.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "O que você quer de mim?";
			link.l1 = "Sua cabeça!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nada, deixa pra lá.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Você de novo? O que você quer de mim?! Se explique!";
			link.l1 = "Sua cabeça!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nada, deixa pra lá.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "Você de novo? O que está fazendo fuçando por aqui? Não gosto nada disso. Muito bem, vou te prender e te mandar para o gabinete do comandante para um interrogatório. Rapazes, peguem esse aí!";
			link.l1 = "Mas eu só queria...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Quem é você e o que quer? Se explique!";
			link.l1 = "Me desculpe, senhor, parece que vim à casa errada. Peço desculpas.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Gostaria de ver Richard Fleetwood.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Isso mesmo. Você está falando com a pessoa errada. Seja gentil e vá embora imediatamente!";
			link.l1 = "Sim. Claro.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Sério? Quem foi que te disse que ele morava aqui? Isso me parece suspeito... Certo, vou te prender e te mandar para o gabinete do comandante para interrogatório. Rapazes, prendam esse homem!";
			link.l1 = "Mas eu só queria ver o Richard...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Ladrões? Espiões? Segure bem o seu chapéu agora!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah! O que esse cara está fazendo aqui? Rapazes, temos um espião entre nós! Às armas!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Capitão, interrogamos esse canalha, como você mandou. Tivemos que cauterizá-lo um pouco... Ele estava com essa carta. Tentou engolir, mas não deixamos. Como suspeitávamos, ele devia pegar uma garota em Willemstad e levá-la para o chefe dele.";
			link.l1 = "Uma carta? Deixe-me ver. Depois eu mesmo falo com ele.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Quais são suas ordens, Capitão?";
			link.l1 = "Jogue o corpo ao mar. E prepare-se para desembarcar!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Enterre-o no mar com todas as honras militares. Aquele velho lutou bravamente até o fim. Ele ainda carregou e mirou aquele canhão mesmo depois de ter sido derrubado do suporte. Uma verdadeira pena. Em outro mundo, talvez fôssemos companheiros...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Sim, Capitão!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Sim, senhor capitão!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Preparamos o chinês para o interrogatório, como o senhor ordenou, capitão. Ele não tinha nada consigo, nenhum documento. Um braseiro foi montado, e estamos esquentando as algemas e as tenazes até ficarem em brasa.";
			link.l1 = "Bom trabalho, Alonso. Mas antes de começar, gostaria de tentar conversar com ele. Talvez ele decida colaborar de boa vontade?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Como quiser, capitão.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Sim, Capitão?";
			link.l1 = "Coloquem algemas nele e fiquem de olho o tempo todo até chegarmos a Guadalupe. Vocês três devem permanecer aqui sempre. Vão responder por ele com a própria vida.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Sim, senhor, Capitão!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ic! Boa noite, senhor! O que vai querer? Será que poderia pagar uma bebida para um velho bêbado? E eu...";
			link.l1 = "Escuta aqui, velho bêbado... Você é o Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Oh! Sim, sou eu. Quem mais poderia ser? Por quê? O que é que va-a-mos fa-zer co-o-m um ma-ri-nhei-ro bê-bado-o-o...";
			link.l1 = "Meu Deus do céu, me dá paciência! Que marinheiro o quê? Tá estampado na sua cara que você é um novato em terra firme... Quer ganhar um dinheiro?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Eu sempre quero ganhar dinheiro. O que devo fazer? Mas não vou matar ninguém. Nem roubar nada. E você não faz meu tipo.";
			link.l1 = "Você não vai precisar matar ninguém, e duvido que você seja capaz disso. Você é desajeitado demais. Agora. Aqui está uma carta. Pegue e entregue na casa à esquerda da residência do governador. É para Richard Fleetwood.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Para Richard Fleetwood? Não... Vão me prender assim que me virem.";
			link.l1 = "Cale a boca e escute. Ninguém vai te prender. Você vai dizer que veio da parte do Charlie Knippel sobre a Abigail. Vão deixar você entrar. Repita o que eu disse.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Quem é Abigail? Eu conheço o Knippel...";
			link.l1 = "Não é da sua conta. Quanto menos souber, mais tempo vai viver. Bem, estou esperando. Repita.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Vim a mando do Charlie Knippel sobre a sua... Abigail. Isso mesmo. ";
			link.l1 = "Muito bem. Você vai receber 5.000 pesos pelo trabalho.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pesos? Oh... Só por entregar uma carta?";
				link.l1 = "Não. Você vai receber outra carta. Leve-a até a taverna e sente-se aqui. Eu vou pegá-la de você. Não faça nenhuma besteira, e não tenha medo – vou estar de olho em você e por perto. Pegue essa quantia como adiantamento, assim você pode ficar tranquilo.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Cinco mil? Você tem mesmo esse dinheiro todo?";
				link.l1 = "Ha! Claro que tenho. Vou trazer agora.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Você trouxe os cinco mil?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Sim. Aqui está. Não se preocupe.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Não. Espere. Eu volto já.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Devo ir agora, senhor?";
			link.l1 = "Não, na manhã de quinta-feira... Claro, é agora, seu cabeça-dura! Agora termina teu rum e vai!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, aqui está você, senhor... Eu queria não ter feito isso. O Richard ficou furioso quando terminou de ler. Achei que ele fosse me matar.";
			link.l1 = "Mas aí está você! Não se preocupe – ele jamais teria coragem de fazer isso – você era valioso demais pra ele naquele momento, ha-ha! Você nem imagina o quanto...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Preciso de uma bebida... Aqui está a resposta dele para você.";
			link.l1 = "Me dá isso! E fica de boca fechada!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Vai ser difícil para mim falar nos próximos dias... Adeus... Espero nunca mais te ver.";
			link.l1 = "Calma aí, velho bêbado, ha-ha-ha! O que faremos com um marinheiro bêbado... Beba e relaxe – já acabou tudo!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Por que diabos você atacou meu navio? Não tenho nem riquezas nem dinheiro—só papéis, que não servem pra nada pra você mesmo!";
			link.l1 = "Cale a boca. Você perdeu, então agora vai me ouvir. Não preciso nem do seu navio, nem dos seus papéis. Preciso que entregue este recado ao seu chefe, aquele rato imundo do Lucas Rodenburg. Diga a ele que o capitão Fleetwood manda lembranças.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Capitão Fleetwood? Mas...";
			link.l1 = "Vai entregar esta carta para o seu chefe – ou prefere que eu te atravesse com a espada? Posso muito bem encontrar outro candidato para a entrega. Só pra constar, eu assalto navios dessa sua Companhia imunda todo fim de semana, só por tédio mesmo.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Certo, Sir Fleetwood. Eu vou entregar.";
			link.l1 = "Ótimo. Agora podemos nos despedir, Mynheer. Considere-se com muita sorte hoje. E não se esqueça de visitar uma igreja quando chegar!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Fui preso injustamente! Não tenho nenhuma ligação com os ingleses! Isso tudo são intrigas do Rodenburg. Não importa. Peter Stuyvesant vai chegar em breve – ele vai resolver tudo!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "O senhor Lucas Rodenburg não deseja receber ninguém neste momento. Por favor, tenha a gentileza de deixar a residência imediatamente.";
			link.l1 = "Hum. Entendi. Vou tentar passar aqui daqui a uma semana...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Vamos para a residência, Capitão. Já mandei meus homens ao forte para buscar informações sobre Matthias Beck. Se ele realmente estava preso, já deve ter sido solto e trazido para a cidade. Venha comigo!";
			link.l1 = "Sim, senhor Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! O que está acontecendo aqui? Onde está Matthias Beck? É verdade que você o mandou para a prisão?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Olá, senhor Stuyvesant. Tenho provas da ligação dele com a inteligência britânica e diretamente com o capitão Fleetwood. Ele avisou aquele maldito inglês para atacar nosso brigue-correio e tomar a correspondência confidencial da Companhia.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Onde você conseguiu essa informação?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, o mensageiro também transportava outros documentos importantes da Companhia – não apenas os relatórios de rotina. Agora todos estão nas mãos dos britânicos. Por isso decidi prender Beck.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Droga! Isso é uma verdadeira usurpação de poder! Você tem ideia do que está fazendo, Lucas? Onde está o capitão da escuna-correio?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Ele foi para Philipsburg, senhor.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Certo, então. Mandei soltarem o Beck. Vão trazê-lo aqui e então nós três vamos conversar.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "Certo, não me importo. Nós três - tudo bem. Vamos conversar.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "You will pay for your lawlessness, Rodenburg! Your accusations are absurd. You didn't even let me see the captain of the brigantine! You haven't presented any evidence; all the accusations come from you personally.\nI swear to the Lord, I am innocent! I do not and did not have any contact with the Brits!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Ah, é mesmo? Então como o Fleetwood ficou sabendo do nosso bergantim e que ela carregava mais do que só os documentos de sempre?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg está mentindo. Richard Fleetwood jamais poderia ter atacado a brigue-correio.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "E quem é você, senhor? Com que direito faz tais afirmações?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+". Eu mesmo eliminei o capitão Fleetwood, atraindo-o para uma armadilha. O corpo dele está sendo devorado por gaivotas nas praias de Turks. As autoridades não conseguiram nos proteger, nós, comerciantes holandeses, da agressão dele, então eu mesmo dei um fim nisso. E tudo isso aconteceu antes do brigue-correio ser saqueado...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood simplesmente não poderia ter feito isso, ele já estava morto. Fiquei sabendo por moradores na taverna que Mathias Beck foi preso, então decidi investigar o caso, porque sempre acreditei que o senhor Beck é um homem de reputação impecável...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "People in the port told me that you loaded your xebec with all kinds of criminals and mercenaries, while the Company's guardsmen were left ashore. I followed your ship and captured her, slaying every cutthroat you hired. I interrogated Captain Longway; in exchange for his freedom, he told me everything, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Você planejava tomar o poder em Curaçao e ordenou que Longway afundasse o galeão do senhor Stuyvesant. Conhecendo seus métodos, tenho certeza de que o pobre capitão da bergantim está morto. Você deve ter organizado um ataque ao navio-correio para criar um precedente, estou certo? E esse ato foi executado pelo seu assassino, Jacob van Berg? Longway me contou muito sobre esse homem.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Isto... isto é uma mentira descarada! Do que está falando, senhor? Quem diabos é você?";
			link.l1 = "Sou um capitão independente que queria livrar o mar e a terra desse canalha do Fleetwood e acabei me envolvendo nas suas intrigas políticas! Avisei o senhor Stuyvesant sobre o perigo que corria. E estou aqui para acabar com os seus crimes em Curaçao – junto com as autoridades legais!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Que insolência! Você vai responder por suas palavras, senhor 'capitão independente'! Você...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Chega, Lucas. Você vai pagar pelos seus crimes! Já ouvi e vi o suficiente. Lucas Rodenburg, estou te prendendo por tentar tirar a vida do diretor da Companhia, por tentar tomar o poder à força e por suspeita de ter assassinado o capitão do navio-correio.\nAlém disso, tenho certeza de que vamos descobrir mais detalhes interessantes da sua biografia durante a investigação oficial. Você ficará sob custódia e será levado para Amsterdã, onde será julgado. Levem-no!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "Mas...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Capitão "+GetFullName(pchar)+"! Em nome da administração da colônia de Willemstad, peço que aceite nossa sincera gratidão por suas ações, que nos ajudaram a colocar aquele criminoso perigoso atrás das grades. Também gostaria de lhe agradecer pessoalmente, pois provavelmente lhe devo a minha vida.";
			link.l1 = "Eu agi pelo bem de todas as colônias holandesas, Mijnheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Sua modéstia impõe respeito, meu amigo. Agora gostaria de resolver algumas formalidades: já que você capturou o Meifeng apenas por bons motivos e em uma situação desesperadora, não pode haver reclamações. Mas este navio pertence à Companhia e peço gentilmente que o devolva.";
			link.l1 = "Certamente, senhor.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Por favor, venha à minha residência amanhã – você será homenageado em nome da República das Províncias Livres pelos seus feitos em prol dos nossos interesses. Peço gentilmente que não deixe a cidade.";
			link.l1 = "Certo, senhor. Passo aqui amanhã.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Quero também agradecer pessoalmente, capitão, pelo seu espírito empreendedor e pela ajuda na hora certa. Não se esqueça de voltar aqui amanhã, vou preparar um presente valioso para você.";
			link.l1 = "Obrigado, senhor Beck. Eu estarei lá!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", em nome da República das Províncias Livres, você está sendo premiado com uma arma pessoal e a quantia de 100.000 pesos pela sua iniciativa na eliminação do inimigo de todos os holandeses, o criminoso de Estado Richard Fleetwood. Parabéns!";
			link.l1 = "Obrigado, senhor Stuyvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Além disso, pela sua coragem sem igual, por ter desmascarado uma conspiração traiçoeira dentro da Companhia e pela ousada captura do ex-vice-presidente da Companhia, você receberá uma recompensa de 150.000 pesos. Também terá permissão para assinar contratos com a Companhia Holandesa das Índias Ocidentais\nTenho certeza de que nosso novo vice-diretor encontrará um cargo muito bem remunerado para um capitão tão valente como você.";
			link.l1 = "Obrigado! Vou me lembrar disso.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Saiba que você sempre pode contar com a minha ajuda em qualquer negociação, desde que aja do lado e no interesse da Holanda. Agora vamos ouvir o que o governador de Willemstad, Matthias Beck, tem a dizer.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Expresso minha sincera gratidão, capitão, pela sua coragem e perspicácia ao desvendar uma conspiração contra o Estado. Gostaria de lhe oferecer este valioso instrumento de navegação, indispensável para qualquer homem de guerra.";
			link.l1 = "Obrigado, senhor Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Quero que saiba: agora você é meu amigo, e isso significa muito para mim. Você será sempre bem-vindo na minha casa. Venha quando quiser, por qualquer motivo – terei prazer em ajudá-lo no que precisar.";
			link.l1 = "Fico feliz em ouvir isso, senhor!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "A Holanda se orgulha de você, Mynheer. Capitães como você são a base da Frota Holandesa no Caribe. Aqui está, por favor, aceite sua recompensa.";
			link.l1 = "Obrigado, senhor. É uma honra servir à Holanda!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Fico feliz em te ver. Como você está?";
			link.l1 = "Estou bem. Só passei aqui para te ver.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Olha só quem apareceu! É "+GetFullName(pchar)+". Recentemente enviamos nossos caçadores de talentos para trazê-lo até aqui. E esse serviço nos custou caro.";
				link.l1 = "Uhm... É melhor eu ir...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Você é capitão da Marinha Francesa? Ótimo, estou sem muito tempo, mas vou ouvir o que você tem a dizer. O que o traz aqui?";
				link.l1 = "Senhor Stuyvesant, vim de Saint Christopher com uma mensagem do Governador-Geral das colônias francesas, o Chevalier de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Com licença, capitão, mas estou extremamente ocupado agora e não posso lhe dar atenção. Fale com o senhor Mathias Beck, deixe que ele ouça o que você tem a dizer.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Do Chevalier de Poincy? Eu realmente não esperava que fosse tão fácil... aham... como está o Chevalier?";
			link.l1 = "Está tudo certo, senhor. Monsieur de Poincy me pediu para lhe entregar esta carta. Minha outra tarefa era escoltar "+sld.ship.name+"' com carga para sua companhia no porto de Willemstad. O navio está atracado e a carga está intacta.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Uma frota trazendo carga para a nossa companhia? Interessante... E a carta, Capitão?";
			link.l1 = "Aqui. Por favor, pegue.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (lendo). Uma inspeção do estado-mãe... Ahn... Hmm, isso é interessante, heh-heh... Aliás, Capitão, ouvi dizer que a França está em guerra com a Espanha no Caribe? O cerco e saque do forte San Jose, a destruição do esquadrão de guerra espanhol na costa leste de Cuba...";
			link.l1 = "Na costa oeste de Hispaniola, perto de Port-au-Prince, senhor. E o único objetivo do cerco a San Jose era conseguir uma compensação financeira dos espanhóis pelo ataque deles a Saint-Pierre. Já estamos em maus lençóis com a Espanha faz tempo... Quando devo voltar para receber a resposta?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Não vou te segurar, Capitão, você é um homem de ação, deve ter muitos compromissos e tenho certeza de que o Chevalier está ansioso pelo seu retorno. Por favor, aguarde aqui mesmo, na sala, por duas horas enquanto escrevo a resposta daquela carta. Sente-se e descanse, vão lhe servir vinho ou rum, se quiser...";
			link.l1 = "Minha gratidão, senhor, mas eu prefiro uma taça de bom vinho...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "A resposta para Monsieur de Poincy está pronta. Aqui, por favor, leve... Boa sorte, capitão.";
			link.l1 = "Obrigado, senhor. Adeus!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Olha só quem apareceu! É "+GetFullName(pchar)+". Recentemente enviamos nossos recrutadores para trazê-lo até aqui. E esse serviço custou caro.";
				link.l1 = "Uhm... Acho melhor eu ir...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Você veio de novo com uma mensagem do governador-geral Philippe de Poincy, não foi?";
				link.l1 = "Sim, senhor Stuyvesant. Nas margens de Sint Maarten houve um infeliz mal-entendido – um navio trazendo o inspetor de Paris, Barão Noël Forget, foi alvejado pelo forte de Philipsburg, e...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Com licença, capitão, mas estou extremamente ocupado agora e não posso lhe dar atenção. Fale com o senhor Mathias Beck, deixe que ele ouça o que você tem a dizer.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "E é por isso que você está aqui, Capitão. Não vou entrar em discussões diplomáticas: diga ao Chevalier que ele não está mais no comando de Sint Maarten. Já chega dele. E quanto à inspeção do governo central – que ele invente alguma coisa. Nunca foi difícil para de Poincy virar tudo de cabeça para baixo.";
				link.l1 = "É exatamente isso que devo dizer a ele?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "E é por isso que você está aqui, Capitão. Não vou entrar em discussões diplomáticas: seu senhor tem sido ganancioso demais em Sint Maarten ultimamente, então chegou a hora de conter essa fome insaciável. E acredito que ele entende isso muito bem. Quanto a você, Capitão Charles de Maure, também temos perguntas sobre os acontecimentos recentes envolvendo o bandido britânico chamado Richard Fleetwood, então você vai ter que ficar aqui por um tempo.\nSargento! Pegue as armas do capitão e leve-o ao gabinete do comandante!";
				link.l1 = "Atrassar um oficial francês em serviço é inaceitável!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Não poderia ter dito melhor, Capitão. Seu comandante vai entender tudo, mas não precisa entrar em detalhes, isso não vai mudar nada. Desejo tudo de bom para você. Sargento, conduza o Monsieur Charles de Maure até a saída!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Infelizmente, eu penso diferente. Sargento! Se eles resistirem, use a força!";
			link.l1 = "Você ainda não faz ideia de com quem está lidando, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "É um pouco estranho ver você, Capitão Charles de Maure, nesse papel... Espero que possa garantir imunidade àqueles que vêm até você para negociar..";
			link.l1 = "Pode ter certeza disso, senhor Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Então, você poderia me dar uma chance de ler o acordo que preparou? Pelo que entendi, ele inclui o conteúdo da carta?";
			link.l1 = "Exatamente, Mynheer, só que de forma oficial. Do lado da França – restauração das relações para a neutralidade, renúncia a qualquer reivindicação sobre a ilha de Sint Maarten. Do lado da Inglaterra – o fim da guerra comercial. Todos os detalhes estão descritos aqui ... E, claro, compensação financeira pelos prejuízos que sofremos por causa das ações militares que vocês iniciaram.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Por favor, seja gentil e me entregue o documento.";
			link.l1 = "Claro.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(lendo)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Já que você não me deixou escolha, vou assinar este acordo. Mas, para mim, a proteção de Willemstad e de seus habitantes é o que mais importa";
			link.l1 = "Então validaremos as três cópias com assinaturas. Estou autorizado pelo Governador-Geral Philippe de Poincy a endossar o documento pelo lado da França, e o Coronel Doily o assinará pela Inglaterra.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(assinando)...";
			link.l1 = "Perfeito! Agora só falta assinarmos isto...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Então, posso confiar que vai suspender o cerco agora?";
			link.l1 = "Sem dúvida. Espero que todos os termos do acordo sejam cumpridos pelo lado holandês, sem nenhuma violação.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Se não houver violações por parte da Inglaterra ou da França, então cumpriremos os termos do contrato, portanto não se preocupe.";
			link.l1 = "Sempre é melhor negociar do que lutar, Mynheer Stuyvesant. Agora você pode voltar em segurança para Willemstad. O cerco será levantado e nosso esquadrão logo deixará as águas de Curaçao.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Então, você é o Barão Noel Forget? Hã, e você deve ser o próprio Monsieur Charles de Maure! Saudações, Vice-Almirante! Não é à toa que dizem que você é o mais astuto conspirador do arquipélago — nunca se sabe de que lado você está em cada momento...";
			link.l1 = "O Vice-Almirante está do lado do Rei, e eu, como seu representante legítimo, também estou do seu lado neste momento.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "O rei está longe daqui, assim como a França, Barão, mas Saint Christopher e o Chevalier de Poincy estão bem próximos. Ele é o verdadeiro dono das colônias francesas. De fato... Mas diga, você veio atrás de algo que possa comprometer de Poincy perante o ministro das finanças?";
			link.l1 = "Exatamente, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Eu tenho esses documentos. Este aqui é um livro-caixa inteiro com as minhas contas e as do de Poincy sobre a mina e outros assuntos. Dentro, você também vai encontrar uma pilha de papéis ligados a esse negócio, todos assinados pessoalmente por Philippe de Poincy. Garanto que o conteúdo desses papéis, nas mãos certas, vai afundar o Chevalier mais fundo do que o fundo do Mar do Caribe.";
			link.l1 = "O que você quer por esse livro-caixa?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Estou vendendo por uma ninharia. Apenas um milhão de pesos em prata.";
			link.l1 = "Um milhão de pesos?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Isso mesmo, Barão. Esse valor vai pelo menos cobrir parte dos prejuízos causados pela guerra recente. Vou lhe dar um conselho: procure o Monsieur Charles de Maure. Durante o tempo em que serviu ao de Poincy e, aham... a outras pessoas, ele provavelmente fez uma fortuna enorme, então conseguir um milhão não deve ser problema para ele. Tenho quase certeza disso. Vou lhe dar um prazo – um mês. Depois desse tempo, se você não trouxer a quantia indicada, enviarei uma carta ao Chevalier, na qual descreverei os detalhes da sua visita a mim. Você pode imaginar o que acontece depois.";
			link.l1 = "Você está me chantageando! Você precisa entender que eu jamais teria um milhão nas colônias!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Claro que eu entendo. Por isso mesmo, apontei de imediato quem tem esse milhão. Se Monsieur de Maure recusar, é melhor que o senhor, Barão, zarpe para a Europa antes que o Cavaleiro receba minha carta, senão corre o risco de ficar aqui para sempre. Quanto ao Monsieur de Maure... claro, ele vai perder o posto de almirante, mas vai se safar... e talvez até se livre do de Poincy com seus métodos, o que, pra mim, está ótimo. Bem, senhores, vocês me ouviram. Estarei esperando vocês com o milhão daqui a um mês na minha residência. Entrada e saída livres, garantido.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "I never doubted, Vice Admiral Charles de Maure, that you would bring me this money. Perhaps I even asked too little of you, but oh well... The Baron is just a pawn in your next game, isn't he? Rank and money are not enough for you; now you want to take de Poincy's place, am I right? You must admit, a million is a small sum for the post of Governor General of the French colonies! You'll get this money back in a matter of months, given your iron grip.";
				link.l1 = "Pegue seu milhão, Mynheer. Agora quero receber o livro-caixa que me prometeu.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "É melhor você se concentrar em conseguir o milhão, Monsieur, ao invés de perder tempo com visitas inúteis.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Claro, Vice-Almirante. E não faça essa cara: quando você virar Governador-Geral, vai perceber que a Companhia Holandesa das Índias Ocidentais é um parceiro de negócios muito mais lucrativo do que os britânicos gananciosos e belicosos. Você não sabe que, se der um dedo a um inglês, ele pega a mão inteira? Se não sabe, vai aprender do jeito difícil. Então, ainda não estou me despedindo de você. Fique com seus papéis. Espero que seu barão seja competente o bastante para derrotar o Chevalier.";
			link.l1 = "Meu agradecimento. Adeus, senhor Stuyvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha! Olha só! O Jacob estava certo, como sempre – essa raposa veio pra ilha com um bom motivo. Parece que tem uma bela pilha de ouro nesse baú. Foi bem imprudente da sua parte aparecer aqui sozinho, camarada. Mas, pensando bem, isso só facilita o nosso trabalho!";
			link.l1 = "Aqueles canalhas me encontraram! Eu não esperava por isso... Mas não vou ser uma presa fácil!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Está procurando alguém?";
			link.l1 = "Sim, sou eu. Onde estão Solomon e Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "They don't live here anymore. They simply couldn't afford the place. Abigail, poor girl, is working as one of the governor's servants. She works hard every day to provide for herself and her father. Solomon drinks in the tavern every day; he can't bear what happened to them. They are now living in a small hut not far from the sea...";
			link.l1 = "Oh... Certo, obrigado pela informação. Preciso ir.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "O que mais gostaria de saber, senhor?";
			link.l1 = "Nada, deixa pra lá.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Capitão, você se apropriou indevidamente de um navio pertencente à Companhia Holandesa das Índias Ocidentais. Estou autorizado a confiscá-lo e usar a força caso resista. Esta é uma ordem de Peter Stuyvesant.";
			link.l1 = "Bem, se é uma ordem do próprio Peter Stuyvesant... Não vou entrar em guerra com a Holanda por causa de um navio. Pode levar.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Que bom que resolveu agir com sensatez.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Claro que está na hora de ir embora, você vai até ter escolta. Guardas! Peguem-no!";
		    link.l1 = "Me faça!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ei, escute! Como cidadão desta cidade, peço que não ande por aí com a espada desembainhada.","Sabe, como cidadão desta cidade, peço por favor que não ande por aí com a espada desembainhada.");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Como você disser...");
			link.l1.go = "exit";
		break;
	}
}
