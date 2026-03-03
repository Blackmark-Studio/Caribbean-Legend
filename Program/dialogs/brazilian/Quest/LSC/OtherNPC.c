// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "Olhem só, rapazes! Vejam quem veio nos visitar! Um ladrão saqueando os baús dos outros! Venha cá! E você, camarada, nem pense em se fazer de bobo ou sacar a espada – não vou errar de tão perto... Chad vai ficar muito feliz em te ver!";
			link.l1 = "Mas eu... eu acabei de chegar!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "Você está certo, ha-ha! Você acabou de se meter numa bela encrenca, camarada... E não vai sair dessa. Agora, entregue suas armas e venha comigo! A cela no 'Tártaro' está te esperando faz tempo, ladrão!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "Não tente roubar nada daqui. Eu vou ficar de olho em você.";
			link.l1 = "Seja muito bem-vindo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "Vai e faz o que o Chad mandou. Não fala demais!";
			link.l1 = "Sim, estou a caminho...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "Ei! Que diabos você está fazendo aí? Desgraçado! Agora você está acabado!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "Ei, que diabos você está fazendo aqui, caramba? Onde está o Barbier?";
			link.l1 = "Nosso amigo Adolfo está... indisposto. Ele não pôde vir à reunião, então me pediu para ficar na cabine dele por um tempo e esperar por você.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "Ei, que diabos você está fazendo aqui, caramba?";
			link.l1 = "Nosso amigo Adolfo está... indisposto. Ele não pôde vir à reunião, então pediu que eu viesse em seu lugar. Por assim dizer.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "Parece estranho... ele estava bem esta manhã, e agora está doente.";
			link.l1 = "Bem, você sabe como as coisas acontecem. O ataque repentino de febre...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "Ah, não gostei da sua cara. Você está mentindo. Barbier jamais confiaria esse encontro a outra pessoa. Fala, desgraçado, quem é você e o que fez com ele?";
			link.l1 = "Sabe, você também não é grande coisa de se ver. Já te disse que o Barbier está doente. Você é lerdo ou quer que eu repita? Era pra ele te entregar a chave e...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "Droga! Você me encontrou...";
			link.l1 = "Isso mesmo, canalha! Você não vai encostar um dedo nela! Prepare-se para morrer!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "Você é "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. O que foi?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "O Tubarão me enviou. Ele pediu pra você ir vê-lo o quanto antes. Ele tem algo importante pra você.";
			link.l1 = "Qual a pressa?.. Tudo bem, estou indo para o 'San Agustin' agora mesmo.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "Você é "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. O que foi?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "Ah, estou cansado de te procurar... O Tubarão e Layton Dexter. Eles pedem que você vá vê-los imediatamente. É um assunto muito importante, então apresse-se.";
				link.l1 = "É mesmo? Tudo bem, vou para o 'San Agustin' imediatamente.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "Ah, estou cansado de te procurar... O Almirante Layton Dexter pediu que você vá vê-lo imediatamente. É um assunto muito importante, então vá depressa.";
				link.l1 = "Almirante?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "Sim. Como segundo no comando, ele se tornou nosso almirante após a morte do Tubarão.";
			link.l1 = "Entendi. Tudo bem, vou para o 'San Agustin' imediatamente.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, então é você... Eu me lembro de você, foi o último a falar com Chimiset. Você o matou?";
				link.l1 = "Corta essa! Você sabe muito bem que não fui eu. Acho que você sabe quem é o assassino.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, é tão chato ficar aqui o dia todo! Se ao menos você trouxesse rum e cartas, camarada, a gente podia jogar uma aposta...";
				link.l1 = "Desculpa, camarada, não tenho tempo pra isso agora. Talvez depois.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "Tenho alguns palpites, sim, mas não tenho fatos. Ninguém viu a morte do homem negro. Há boatos por toda a ilha de que nós, o povo do Tubarão, somos os responsáveis, e dizem que algum recém-chegado fez isso a mando do almirante. Entende agora? Então não vá até os Rivados, especialmente agora. Eles estão furiosos demais.";
			link.l1 = "Tá bom. Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "Ah, é tão entediante ficar aqui o dia todo! Se ao menos você trouxesse rum e cartas, camarada, a gente podia jogar uma aposta...";
			link.l1 = "Desculpa, camarada, não tenho tempo pra isso. Talvez depois.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "O que você quer, camarada?";
			link.l1 = "Hm. E o que você faz aqui? Onde está Axel?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "Axel está ocupado. Ele está em uma reunião com Donald Greenspen e vai ficar com ele até o fim do dia. Então, se quiser comprar alguma coisa, fale com ele amanhã de manhã. E eu estou cuidando da loja, então nem pense em roubar nada...";
			link.l1 = "Entendi. E por que ele está fazendo isso hoje? Tudo bem, eu venho aqui amanhã de manhã.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("Já te contei tudo. Volte aqui amanhã.","Não me enche, camarada. Cai fora!","Não me irrite, seu idiota!","Vá embora!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudo bem.","Entendi, entendi.","Cala a boca...","O quê?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "O que você quer, senhor?";
			link.l1 = "Hm... Me desculpe, senhora. Perdoe minha ousadia e falta de educação, mas quero lhe perguntar uma coisa: você conhece um homem chamado Ole Christiansen?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "Repita o que você acabou de dizer... Ole Christiansen? Ole?!";
			link.l1 = "Sim. Também o chamam de Garoto Branco por causa da cor incomum do cabelo dele. Você o conhece?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "Conheço ele?! Ele é meu filho e está desaparecido há uma década! Você sabe onde ele está, senhor? Me diga logo onde ele está, o que aconteceu com ele?!";
			link.l1 = "Calma, senhora, não se preocupe assim. Ele está bem. Ele está no meu navio. Só precisa desembarcar e vir até aqui.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "Oh... Parece que o Senhor finalmente ouviu minhas preces! Você não faz ideia de como eu fiquei preocupada quando ele sumiu! E a culpa foi minha, só minha! Onde você o encontrou? Ele não é uma criança comum... bem, você deve saber do que estou falando.";
			link.l1 = "Eu sei. Sim, ele é especial. E não mudou nada. Parece que ainda é uma criança. Eu o encontrei em uma ilha. Nos conhecemos por acaso. Ele me pediu uma conta branca... droga!... Uma pérola.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "Uma pérola? Meu Deus! Foram as pérolas que fizeram meu filho sumir! É tudo por causa daquele maldito colar!";
			link.l1 = "É verdade que o Ole... deixou a casa porque quebrou seu colar de pérolas?... Acalme-se, senhora, não chore!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "Sim, é verdade. O Ole rasgou meu colar no cais e todas as pérolas caíram na água. Eu xinguei tanto ele, e meu falecido marido... puniu ele. Ole sumiu no dia seguinte. Você não imagina o quanto me culpei por isso!";
			link.l1 = "Ole vem coletando pérolas há anos. Ele as chama de contas brancas. Juntou todas para você e me pediu para trazê-las até você. Só sabia que era uma casa com telhado vermelho. Mas finalmente consegui te encontrar.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "Coletando pérolas?! Meu Deus! Eu me sinto tão culpada pelo meu pobre menino! Eu... e ele ficou coletando pérolas! Ai!";
			link.l1 = "Acho melhor chamar seu filho, senhora. Ele estava tão ansioso para te ver. Disse que você ficaria feliz ao ver as pérolas. Mas acho que você vai ficar feliz, não por causa delas...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "Mynheer... você seria tão gentil. Traga meu Ole para mim. Quero abraçá-lo e pedir seu perdão...";
			link.l1 = "Certamente, senhora. Eles vão trazê-lo aqui imediatamente.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "Bem, senhora, aqui está seu filho – Ole Christiansen. A senhora o reconhece?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "Mynheer... Me desculpe, não perguntei seu nome... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", senhora. Capitão "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "Capitão, você não faz ideia do quanto sou grato pelo meu filho! Você o ajudou e trouxe até aqui. Você me fez voltar a viver! Farei tudo pelo meu menino, vou dar a ele todo o amor que lhe faltou todos esses anos.";
			link.l1 = "Fico feliz por você, senhora. E pelo Ole também. Ele é um bom rapaz e me ajudou numa situação difícil. Tem um coração bondoso. Conheço um homem que o Ole salvou da morte.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "Mynheer, insisto que venha aqui amanhã ou quando tiver um tempo. Quero lhe agradecer pelo meu filho. Neste momento estou um pouco... bem, você entende.";
			link.l1 = "Sim, senhora.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "Volte aqui amanhã. Vou recompensá-lo como merece por tudo de bom que fez por meu filho e por mim.";
			link.l1 = "Tudo bem. Com certeza vou te visitar!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "Ah, aqui está você, senhor "+GetFullName(pchar)+"! Venha, sente-se...";
			link.l1 = "Obrigado! E como está o Ole?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "Ah, você não faz ideia do que fez! Foi um alívio para o coração de uma mãe aflita... Eu lhe devo muito, e vou rezar por você para sempre.";
			link.l1 = "Você me faz corar, senhora...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "Sempre soube que é a humildade que faz as pessoas nobres de verdade... Preparei alguns presentes pelo que você fez. Sim, sim! E nem pense em recusar! Aqui, pegue isto... Primeiro, um baú cheio de dobrões. Segundo, leve este amuleto encantado, chamam de Escaravelho. Meu marido era o dono dele, e tenho certeza de que ele ficaria feliz em saber que seu tesouro ficará com um capitão tão nobre, que trouxe meu filho de volta para mim. Meu marido era carpinteiro, costumava dizer que o Escaravelho fazia seu trabalho render mais rápido. Espero que este anel lhe seja útil. Você merece usá-lo, sem dúvida! E por fim, leve minhas ferramentas de costura. É um belo conjunto. Com ele, você vai poder criar muitas coisas boas.";
			link.l1 = "Oh! Estes são presentes realmente valiosos para qualquer capitão! Obrigado, senhora.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "E quero que saiba que as portas da minha casa estão sempre abertas para você, a qualquer hora. Aqui você sempre encontrará comida, uma garrafa de bom vinho e tudo mais que desejar.";
			link.l1 = "Obrigada por suas palavras gentis, senhora. Ficarei feliz em vê-la quando voltar a esta cidade.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "Não deixe de vir!";
			link.l1 = "E agora eu preciso ir. Adeus e boa sorte!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "Ah, capitão "+GetFullName(pchar)+"! Que bom te ver! Sente-se, vou te servir uma bebida...";
			link.l1 = "Obrigado! Só queria te cumprimentar e saber como você estava. Fico feliz que você e Ole estejam bem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só isso! Assim que me perdi em contemplação, você resolveu mexer no meu baú!","Veio mexer nos meus baús? Não vai sair impune!");
			link.l1 = "Maldição!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio fuçar nos meus baús? Não vai sair impune!";
			link.l1 = "Garota tola!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
