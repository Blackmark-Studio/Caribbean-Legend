// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Você! Você a trouxe aqui! Ela é sangue do sangue dele! Ela é sangue do sangue dela! A filha da prostituta veio ao túmulo da mãe! Ela vai morrer! E você não vai conseguir impedir! Não fique no caminho da Jessica! Deixe a vingança para mim!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Você não pode me ferir!\n O ar, a água, a terra, o fogo – eu ordeno que me ajudem!\n Que os mortos se levantem, que o fogo arda, que a água proteja a ponte e que o vento te eleve em suas asas e te jogue ao chão!\nDivirta-se!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ha! Você não pode me ferir!\nQue mais mortos se levantem e ataquem, que o fogo queime a pedra, que o vento te eleve e te jogue ao chão, e que a terra absorva sua força!\nAproveite!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Você não pode me ferir!\nQue o veneno cubra minha espada de lâmina flamejante, que o vento te envolva, que a água leve embora sua agilidade!\nMorra! Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Basta... Estou cansada. Estou derrotada... Tenha piedade do destino da infeliz Jessica!";
			link.l1 = "Certo... Vou poupar sua pobre alma do peso desse cadáver!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Eu conheço sua história, Jessica. Sinto muito que sua vida tenha sido tão triste e terminado assim. Você quer conversar comigo, não é? Bem, vou tentar esquecer que você tentou me matar recentemente e vou te ouvir, embora isso não seja nada fácil para mim...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Obrigada... Você já sabe sobre Beatrice Sharp e Lawrence... meu Lawrence. Matei ela sem hesitar, mas não consegui matá-lo. Eu não consegui, mas ele conseguiu. Jessica morreu...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... mas o voto de sangue, selado por um juramento terrível, continua sem ser cumprido. O poder desse voto vem da magia indígena. Ele ergueu o cadáver do túmulo.\nO ódio transformou minha alma em um deserto. Todos que vieram a este recife foram mortos por minhas mãos, e seus corpos se tornaram meus fantoches. Só posso pedir ajuda àquele que me derrotou...";
			link.l1 = "E o que posso fazer por você? A única coisa que posso fazer é poupá-lo do sofrimento...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Me ajude... Leve-me até ele.";
			link.l1 = "Para Lawrence Beltrope? E como é que eu deveria fazer isso? Minha tripulação vai fugir assim que te ver, ou vai te queimar sem pensar duas vezes. Aliás, você ainda consegue massacrar meus homens e 'controlá-los'...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "They won't see me. But you will. You must have already realised that I possess powers unavailable to the living. But I cannot board your ship without your permission. Take me to him.\nI won't stay with you for long. And I won't harm your people. Land me at Portland Bay in Jamaica at midnight; the following night we'll meet again and you will receive what you came here to find.";
			link.l1 = "Como você sabe por que eu estou aqui?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "I know a lot. More than the living do. I saw her... You need a document for her, and you will get it. You will get even more; I will give you something extra. Take me to him...";
			link.l1 = "Hum. Não gosto dessas suas intenções sanguinárias em relação à Helen. Nem pense em encostar nela. Afinal, ela não tem culpa pelas ações da mãe.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Você me derrotou. Eu não vou machucá-la... Eu prometo.";
			link.l1 = "Ainda não acabou. Vai retirar todas as suas maldições de mim? Admito, não gosto da ideia de viver com elas para sempre...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Não é tão simples assim... Quando nos encontrarmos em Portland Cove depois que eu... Eu te conto como se curar.";
			link.l1 = "Depois de você o quê?.. Como assim?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Depois do meu encontro com ele.";
			link.l1 = "Ah, ele não vai gostar nada disso. Já imagino. Muito bem, vamos resumir: primeiro, você promete que ninguém vai te ver, segundo, não vai fazer mal à minha tripulação, terceiro, nem vai pensar na Helen, quarto, vai me entregar o que estou procurando, e quinto, vai me livrar das suas maldições. Acertei?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Quase. Eu não vou te curar, mas vou te dizer como. Você vai ter que fazer isso sozinho.";
			link.l1 = "Certo. Fechado então. Eu deixo você embarcar no meu navio.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Ei! Onde você está? Você simplesmente sumiu...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Você cumpriu sua palavra - estamos na Jamaica. Venha aqui amanhã à noite e eu cumprirei minha promessa. Adeus.";
			link.l1 = "Adeus...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "Acabou, "+pchar.name+"...";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Acabou... Aqui, pegue, é isso que você procurava. Esta é a carta da minha rival, foi enterrada com ela. Está bem preservada. Eu a perdoei, e não existe mais ódio na minha alma.";
			link.l1 = "Você... encontrou ele? Com o Lawrence?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Sim. A última coisa que ele sentiu na vida foi puro horror. Não sinto pena dele.";
			link.l1 = "Que Deus perdoe a alma pecadora dele... Parece que nunca vou encontrá-lo.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Você não perdeu nada de valor. Ele era um homem muito ruim. Agora, devemos nos despedir, não há mais nada para eu fazer aqui. Meu voto foi cumprido e a magia perdeu seu poder. Eu prometi um presente para você. Aqui. Esta é minha Flamberge. Não preciso mais dela. Esta lâmina é única, você não encontrará outra melhor em nenhum lugar do mundo.";
			link.l1 = "Obrigado...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Agora, sobre você. Vá até Bridgetown, à igreja local, para que minhas maldições sejam removidas. Você encontrará um padre lá. Ele me conhecia pessoalmente. Fale com ele e ele lhe dirá o que fazer. Prepare vinte velas, você vai precisar delas.";
			link.l1 = "Tem certeza de que ele vai me curar?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Você vai fazer isso sozinho. Deus vai te guiar. Confie. Tudo vai dar certo.";
			link.l1 = "Certo, vou zarpar para Barbados imediatamente. E agora?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "E agora eu peço só mais uma coisa. Enterre meu corpo aqui nesta baía, à beira-mar. Esse é meu desejo. Talvez um dia você venha visitar o túmulo da pobre Jessica. Adeus, "+pchar.name+", e reze por mim...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Você me reconhece, Capitão?";
			link.l1 = "É... é você? Mas como?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Sim, "+pchar.name+", sou eu, sou a Jessica! Pelo menos, era assim que eu parecia há vinte anos.";
			link.l1 = "Então... eu morri? Mas quando? Como?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Você não está morto, "+pchar.name+". Você está na igreja em Bridgetown agora. Você está apenas... dormindo.";
			link.l1 = "Será que isso é só um sonho? Tudo parece tão real...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Acontece às vezes, "+pchar.name+". Deus ouviu você. Suas orações não só te curaram, mas também purificaram minha alma. Muito obrigado, "+pchar.name+"! E eu quero te pedir perdão pelo que aconteceu no recife. É... bem, só me perdoe. Eu não poderia partir sem pedir o seu perdão.";
			link.l1 = "Eu te perdoo, Jessica. Será que estou realmente vivo?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Você está... Não se preocupe. Logo você vai acordar. Eu só queria me despedir.";
			link.l1 = "Você é tão... linda!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Você gosta de mim? Sim, houve uma época em que os melhores pretendentes das Pequenas Antilhas me cortejavam, e a cada três piratas em Isla Tesoro, um estava pronto para duelar por mim.";
			link.l1 = "Mas você sempre precisou de só um... Hein, talismã ruivo! Só me diga, como foi que você acabou assim?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "Por causa da minha raiva. Por causa do meu ódio. Por não conseguir entender, perdoar e esquecer. Eu poderia ter começado uma nova vida, mas escolhi me dedicar a uma vingança tola e sem sentido. Você me libertou. Obrigado, "+pchar.name+"...";
			link.l1 = "Eu realmente tenho pena da sua vida...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Não... Você ainda tem seu talismã de gengibre...";
				link.l1 = "Meu o quê?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Não... Você ainda tem seu talismã de gengibre...";
				link.l1 = "Meu o quê?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Não... Pense na minha experiência amarga e não cometa os mesmos erros. E também não deixe que as pessoas que você ama os cometam.";
			link.l1 = "Vou pensar nisso e com certeza não vou cometer os mesmos erros de novo...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Pense um pouco. Ela está no seu navio.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Sim. Ela é a melhor que você vai ter na sua vida. Lembre-se disso. O amor dela é puro, a dedicação dela não tem limites. Ela é corajosa, jovem, mas desesperada e inexperiente. Ela não entende muita coisa. Cuide dela, proteja-a e não deixe ninguém se meter entre vocês. Ela é seu talismã...";
			link.l1 = "Eu... Eu nunca vou deixá-la, e vou protegê-la de qualquer perigo.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Ela está naquela ilha estranha feita de navios naufragados... Ela não está sozinha lá, mas se sente solitária. Todas as manhãs ela acorda pensando em você, todos os dias ela reza por você, todas as noites há uma luz em sua cabine e seu travesseiro está molhado de lágrimas...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Há uma filha entre vocês dois. A filha da mulher que um dia ficou entre Lawrence e eu. O destino do seu talismã está em suas mãos. Eles não podem coexistir, assim como Beatrice e eu não pudemos.";
			link.l1 = "Como você sabe disso?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "O outro lado... Revela muita coisa... A escolha é sua, mas lembre-se: Mary é a melhor que você vai ter na vida. O amor dela é puro, a devoção, sem limites. Ela é corajosa, jovem, mas desesperada e inexperiente. Não entende muita coisa. Precisa da sua proteção, do seu cuidado, do seu amor. Ela é seu talismã.";
			link.l1 = "Vou pensar nisso. Com certeza vou fazer isso...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"Eu preciso ir. Chegou a hora de dizer adeus... De verdade, desta vez. Não se esqueça da Jessica, e tente visitar o túmulo dela de vez em quando... Só você sabe onde fica.";
			link.l1 = "Claro, Jess. Vou visitar e rezar por você.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Obrigado. Adeus, "+pchar.name+"! Adeus!";
			link.l1 = "Adeus, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
