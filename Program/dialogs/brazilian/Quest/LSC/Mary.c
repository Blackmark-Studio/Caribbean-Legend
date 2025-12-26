// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você precisa?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, eu conheço ele. É amigo dos Rivados e dos piratas. O Adolf jamais trabalharia com ele. Ei... você sente cheiro de pólvora? E tem sangue na parede... Ele matou o Adolf e agora está tentando enganar a gente! Só pode estar trabalhando pro Almirante! Matem ele!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "Ah, com licença... você pode me ajudar?";
			link.l1 = "Hm. Eu estou sempre pronto para ajudar uma mulher linda. Qual é o problema?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Olha, eu comprei um baú cheio de pedaços de metal da Sessile Gallard. Ela mora no Eva. O Jurgen prometeu forjar algo bom pra mim, né... Eu comprei, sim, mas não consigo levar pra ele. Maldição!\nVocê poderia levar o baú do Eva até o bloco dos Narvais na Esmeralda? Por favor, eu ficaria muito agradecida!";
			link.l1 = "E é só isso? Claro, moça, eu vou te ajudar. Sem problema.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Obrigada! Vou te mostrar onde está o baú.";
			link.l1 = "Milady...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "E aqui estamos nós... Agora me diz, seu desgraçado, onde está a chave?!";
			link.l1 = "Caramba! Ha, parece que não precisa de ajuda... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Espertinho, né? Fala menos, caramba! Cadê a chave? Me dá logo ou vai se arrepender!";
			link.l1 = "Tão grossa! Uma língua tão afiada pra uma moça tão bonita. Que chave?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "A chave que você pegou do Adolf Barbier. Não tente negar, te viram saindo da cabine dele. Adolf está morto e foi você quem matou... Agora, me dê a chave!";
			link.l1 = "Então era você, afinal... Você cometeu um erro, garota, um erro enorme!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "O que você disse...? Droga, você não é um ladrão qualquer! Ele trabalha para o Almirante! Derrubem ele, rapazes!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, é ele! Droga, ele trouxe reforços! Galera, matem todos eles!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Você chegou bem na hora... Eu nunca teria conseguido lidar com eles sozinha... Aff! Pra ser sincera, achei que era meu fim!";
			link.l1 = "Você lutou como uma Valquíria! Nunca vi uma garota tão linda lutar com tanta energia...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, olha só que cavalheiro, elogiando com a espada ainda na mão. Valeu pela ajuda. Você salvou minha vida, né? Agora se apresenta, cavalheiro, nunca te vi por aqui. Você é novo na ilha?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+", mas garotas bonitas podem me chamar de "+pchar.name+". . Eu sou nova aqui? Hm... Acho que sim.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Eu percebi. Eu teria notado um homem tão bonito por aqui. Meu nome é Mary, Mary Casper. Me chamam de Mary Ruiva, porque eu sou ruiva, né?";
			link.l1 = "Fico feliz em te conhecer, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Ah, eu estou duas vezes mais feliz... porque eu estaria morta se não fosse por você! Aquele desgraçado do Chad não estava blefando. Que rato! E eu fui uma tola de deixar as portas de baixo abertas. Foi assim que você entrou, não foi?";
			link.l1 = "Sim. Eu estava nadando ao redor da ilha tentando encontrar um lugar para subir na terra.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Entendi. Aquela porta destrancada quase me matou. O próprio Jurgen fez as fechaduras pra mim, você não consegue abrir sem a chave certa e arrombar não adianta. Além disso, eu não ficaria parada enquanto alguém tenta entrar – os quatro canos da minha pistola deixam quatro buracos numa porta ou num corpo, né? Ha-ha!  Mas esse maldito Chad não me deixa em paz. Se ele mandou capangas pra me 'convencer' a ficar do lado dele, é porque está levando isso a sério mesmo. Se não fosse por você, eu teria que dizer sim. Vou ter que ficar aqui cercada, "+pchar.name+", all right! Thank God I prepared for that; I have plenty of supplies and Jurgen is my neighbour, I've no quarrel with him.";
			link.l1 = "Mary, por que você não explica seus problemas direito? Eu vejo que você precisa da minha ajuda, mas não entendi nada do que saiu da sua boca.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Sim, eu preciso de ajuda, né? Agora estou sozinha. Briguei com o Donald, depois o Chad se revelou um canalha... Ai, desculpa, tô tagarelando de novo. Tá bom, vou te contar a situação em que me meti...";
			link.l1 = "Olha, eu ainda sou novo aqui, então não entendo muita coisa ainda. Quem é esse Chad que está tentando te 'convencer' ou te matar? E quem é o Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad é um pirata da tripulação do Almirante Shark Dodson, um carcereiro no Tártaro...";
			link.l1 = "Espera! Você disse Shark Dodson? Ele está aqui?!";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Você deve ter chegado hoje à noite, já que ainda não sabe disso. Onde mais o Tubarão estaria? Meus problemas começaram quando ele apareceu aqui há alguns meses. Mas, admito, a culpa é toda dos Narvais e dos Rivados. Quando o Tubarão chegou com a tripulação dele, queria montar uma base, mas o nosso povo e os Rivados não gostaram nada da ideia. Atacamos a escuna do Tubarão à noite e botamos fogo nela. Péssima ideia! A tripulação do Tubarão é feita de demônios, não de homens, né? Primeiro, eles destruíram nossos barcos, depois desembarcaram e começaram a massacrar a gente. Os Narvais recuaram e os Rivados fugiram o mais rápido que puderam. No fim, os piratas tomaram o San Augustine, onde ficam a maior parte dos mantimentos da ilha, e depois pegaram o Tartarus. O Tubarão prendeu nosso líder, Alan Milrow, que também era meu... meu grande amigo, e o mago dos Rivados, Chimiset. Ele mandou os dois apodrecerem nas celas do Tartarus como feras. É fácil nadar até o Tartarus daqui, e eu consegui visitar o Alan algumas vezes. Lá, conheci o Chad Kapper. O Tubarão colocou ele como carcereiro. Pedi pro Chad soltar o Alan, prometi dinheiro, mas ele tinha medo de desobedecer o Almirante. E aí o Alan foi assassinado na prisão. O Chad me contou que foi o Tubarão quem fez isso, né? Então fui até o Donald, que foi eleito líder no lugar do Alan, e exigi que ele atacasse os piratas imediatamente, mas ele recusou, disse que aqueles demônios do mar eram duros demais pra gente. Mandei ele se ferrar. Meu povo não servia pra nada, então fiz um acordo com o Kapper, aquele canalha que queria tomar o lugar do Tubarão. Tínhamos um plano: atrair o Almirante pra algum canto escuro e acabar com ele. Também achamos um atirador com um bom rifle. Ele podia acertar o Almirante do mastro do Fury. Agora, o mais interessante: anteontem à noite fui até o Tartarus pra contar algo importante pro Chad sobre o nosso plano. Nadei até o navio e ouvi o Chad conversando com dois Narvais. Descobri que não foi o Tubarão que matou o Alan. Foi o Chad. Ele espalhou o boato de que o Almirante era o responsável. O Chad matou o Alan por minha causa – primeiro pra me ter como brinquedo na cama dele, depois pra me usar pra se livrar do Tubarão. O Chad sabia que eu não ia parar até me vingar. Dá pra acreditar? Que verme!";
			link.l1 = "É, já conheci tipos como ele...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Filho da puta é pior! Ele... Eu nem tenho palavras pra descrever esse monstro! Depois que nadei pra longe, encontrei ele na manhã seguinte e falei exatamente o que eu pensava dele. Sim, falei que não queria ter nada a ver com o plano dele contra o Almirante.";
			link.l1 = "E ele não gostou nada disso, obviamente... Isso foi imprudente, Mary. Você devia ter sido mais cautelosa.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Eu sei, mas eu não consegui ficar de boca fechada. Aquele desgraçado matou o Alan e tentou me usar pros próprios interesses! Canalha! E claro, ele ficou furioso e jurou que eu ia me arrepender. Eu disse que ia cortar as bolas dele e dar pros caranguejos comerem!\nEle ameaçou mandar os capangas dele atrás de mim se eu não mudasse de ideia. Eu ri. Nunca achei que um Narval teria coragem de levantar a mão pra mim.";
			link.l1 = "Parece que você se enganou.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Aham, "+pchar.name+", I underestimated Chad and overestimated myself. He found cutthroats who'd stoop to attacking a lone girl in her own cabin. What do I do now? I can't trust anyone, not even trust my own people; these two we've killed are Narwhals. I knew both of them, all  right. As long as Chad is alive, I'm in danger. He'll send more men, no doubt.\nI'm scared to walk out the door; the sniper we found to assassinate Shark may shoot me from Rivados territory and slip away. I won't go to Donald - he won't listen.\nAnd the Admiral? 'Please, sir, I know I helped plan your assassination, but could you see your way through to forgiving me and saving me from my former mates?'\nHe'd send me to rot in the cells of Tartarus, if he didn't put a bullet in my brain. Fuck, I'm trapped! I'm going to sit here with my guns loaded until the food runs out and then... I don't know!";
			link.l1 = "Bom, nesse caso não tenho escolha a não ser te ajudar, né? Sua situação combina com os meus planos aqui de qualquer jeito...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Você quer me ajudar? Mas como? Vai matar o Chad?";
			link.l1 = "Isso faz parte do plano, sim.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Escuta, "+pchar.name+", eu agradeço a intenção, mas você está se metendo onde não deve. Chad é um dos amigos mais próximos do Almirante e, mesmo que você chegue até ele, não vai sair vivo dessa. Os piratas do Tubarão vão te matar. Eles não sabem da verdade, né.";
			link.l1 = "Calma. Eu preciso falar com o Tubarão de qualquer jeito.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Então, você também é pirata?! É melhor começar a falar. Invadiu meu lugar todo bonito, salvou minha vida, prometeu ajudar, mas eu não sei nada sobre você!";
			link.l1 = "Tá bom... Eu não sou pirata, mas no momento trabalho com um certo barão pirata: Jan Svenson. Vim aqui pra encontrar Nathaniel Hawk. Já ouviu falar dele?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Não, quem é ele?";
			link.l1 = "Outro pirata famoso. É uma pena que você não tenha conhecido ele, ele deve estar por aqui em algum lugar. Eu também estava procurando pelo Tubarão, mas não esperava encontrar ele aqui.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Mas como você veio parar aqui? Você está bem demais pra quem sobreviveu a um naufrágio.";
			link.l1 = "E por que você acha que eu naufraguei?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "É o único jeito de chegar aqui. O Tubarão é o único que já navegou até aqui.";
			link.l1 = "Bem, o Tubarão não é o 'único', como você pode ver.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Então, você tem um navio? Que ótimo!";
			link.l1 = "Não se empolga muito, Mary. Eu cheguei aqui de... de barca. Eu vim numa barca, mas ela afundou no fundo do mar.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Bem, como eu disse: um naufrágio. Agora você está preso aqui com a gente, né?";
			link.l1 = "Mary, deixa eu te contar meu plano. Você disse que o Chad estava planejando matar o Shark. Eu preciso do Shark vivo. Eu e o Jan vamos fazer dele o chefe dos piratas. Por isso eu preciso avisá-lo, porque pela sua história, tenho certeza que o Chad vai tentar, com ou sem a sua ajuda.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Provavelmente. Ele tem homens suficientes pra fazer isso acontecer...";
			link.l1 = "Isso significa que meu objetivo principal é conquistar a confiança do Tubarão e salvá-lo. Depois, vou atrás do Chad – oficialmente. Você tem alguma prova da culpa dele?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "Eu tenho a carta dele, que foi trazida aqui por um desses... idiotas aí no chão. Tem ameaças e detalhes nela que talvez interessem ao Almirante. Espera! E eu? O Tubarão vai descobrir que eu estava trabalhando com o Chad!";
			link.l1 = "Mary, você vai ficar sentada aqui com suas pistolas pra sempre, escondendo esse rosto lindo de todo mundo? Você acha mesmo que eu quero a morte de uma garota tão bonita na minha consciência? Mostra a carta primeiro, vamos ver o que eu posso fazer...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Aqui. O que você acha?";
			link.l1 = "Espera aí... (lendo). Sim, parece que o Chad é mesmo um daqueles canalhas especiais que infestam este mundo. Esta carta vai ser o suficiente pra deixar o Tubarão louco pra enforcar o Chad com as próprias mãos. Não se preocupe, minha senhora, vou garantir que o Tubarão nunca desconfie de você. Ele vai estar ocupado demais com o Chad, de qualquer jeito.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Você faria mesmo isso? Me promete, né! Jura pra mim que não vai me trair!";
			link.l1 = "Mary, eu juro pra você, não vou te trair. Eu não te salvei pra te ver morta depois.\nO Chad não vai te deixar em paz, isso é certo. Você sabe demais. Fique aqui até ele estar morto.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Eu vou ficar aqui. Prefiro não levar um tiro de um atirador ou ser esfaqueada pelas costas.";
			link.l1 = "Boa garota. Tranque todas as portas, inclusive as de baixo. Você está com a única chave?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Não. Tem outro. Você quer?";
			link.l1 = "Sim. Você confia em mim?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Bem, se o cavalheiro bonito que acabou de salvar minha vida me trair, não vai sobrar muito motivo pra viver mesmo... Pode pegar.";
			link.l1 = "Não tenha medo, linda! Eu não vou te decepcionar. Assim que eu resolver essa confusão, venho te ver. Tomara que não demore muito.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "Tá tudo bem, eu consigo segurar esse lugar por algumas semanas.";
			link.l1 = "Ótimo. Então não vou perder tempo. Vou tirar os corpos e depois falar com o Tubarão. Ele está no San Augustine, né?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Sim, ele está sempre lá. E saia do mesmo jeito que entrou aqui – não vou deixar você pôr os pés no convés superior do Ceres.";
			link.l1 = "E por que isso?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Porque você não vai poder me ajudar se morrer. Aqui é território dos Narval e eles vão te matar por ser de fora.";
			link.l1 = "Hm... Entendi. Bem, Mary, até logo. Eu volto assim que for seguro.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Pode me ver quando quiser, não tenho problema com isso, não. (risos)";
			link.l1 = "Adeus, bela dama!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Olá, "+pchar.name+", alguma novidade boa pra mim? Você está bem?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Seu conflito com Shark Dodson está resolvido. Ele não tem interesse em te caçar. Agora, a única coisa que importa pra ele é a traição do Chad.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Ainda não, Mary. Mas eu vou fazer tudo o que puder.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Ah, graças a Deus! Obrigada, eu não vou esquecer disso, né? Pelo menos não preciso me preocupar com o Almirante. E o Chad? O que o Tubarão fez?";
			link.l1 = "We convinced the Rivados to go after him. Layton Dexter removed the guards from the Tartarus and gave the gaol key to Black Eddie. The blacks freed their wizard Chimiset, but they failed to kill Chad; they got two of his Narwhal friends, but Chad ran away and is hiding somewhere.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Droga! Isso significa que agora eu tenho que tomar ainda mais cuidado!";
			link.l1 = "Calma, Mary. Tenho certeza de que ele está mais preocupado com o Shark do que com você. Ele provavelmente já sabe quem colocou os Rivados contra ele. Vai fazer de tudo pra matar o Shark, não você.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Não conte com isso. O Chad não é do tipo que deixa as coisas passarem tão fácil. Ai, estou tão cansada de viver com medo dele...";
			link.l1 = "Hm. Eu não achei que você fosse do tipo de mulher que se assusta fácil.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Eu não tenho medo de uma briga de verdade, mas ficar sentada esperando pra morrer? Isso me assusta muito "+pchar.name+", né?...";
			link.l1 = "Confia em mim, Mary: o Kapper já tem trabalho de sobra com o Almirante. Por enquanto... preciso do seu conselho.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Meu conselho? Que tipo de conselho?";
			link.l1 = "Eddie encontrou duas cartas escritas pelo Chad. Leia, talvez você descubra o que ele está tramando. Afinal, você estava no plano com o Chad...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Me dá aqui... (lendo). Axel é o nosso comerciante na Esmeralda, né. O Chad queria comprar uísque com ele? Estranho. Chad só bebe rum, diz que uísque é 'cachaça de camponês'...";
			link.l1 = "E o que dizer da segunda carta?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "'Marcello'? Marcello Ciclope, um ex-caçador real. Ele é o motivo pelo qual me recuso a sair desta cabine.";
			link.l1 = "Ele é o atirador que você contratou?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Sim. Mesmo com um olho a menos, o Marcello acerta uma mosca a doze metros, né? A missão dele era acertar o Tubarão usando um stutzen de longo alcance lá do gurupés da Santa Florentina, ou da plataforma da Fúria...";
			link.l1 = "Então ele ainda faz parte do plano do Chad pra matar o Tubarão. Mas... Eva? Cecille? Bebidas?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "A Eva é um navio neutro e Cecille é Cecille Halard, uma velhinha engraçada que mora a bordo. Ela se mudou pra lá há pouco tempo, vinda da Santa Florentina. Orelie Bertine é amiga dela. As duas estão na ilha desde antes de eu nascer, né?";
			link.l1 = "Hm. Que bobagem. Dois grandalhões se escondendo de uma velha só pra beber um barril de uísque juntos? Besteira... Hora e lugar estranhos pro Chad beber.";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Eu te disse que ele não bebe uísque, só rum... tem algo estranho nisso.";
			link.l1 = "Certo, vamos começar pelo Ciclope. Você sabe onde encontrá-lo?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Não. Ele é muito reservado. Ele caça pássaros todo dia no anel externo e ninguém sabe onde ele dorme. Ele costuma visitar os Rivados.";
			link.l1 = "Não é muita coisa pra começar... Bom, vou falar com o Axel, então. Talvez ele consiga entender isso. Até mais, Mary! Tranca a porta!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+", por favor, encontre o Chad rápido. Não consigo dormir desde o último ataque.";
			link.l1 = "Aguenta firme, querida. Vou fazer o melhor que eu posso.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Como ele chegou aqui? Ele veio para--?";
			link.l1 = "Sim, para te matar, Mary. Ele veio por meio da cabine do Jurgen e usou uma corda para descer até aqui.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! Que idiota eu sou! Esqueci desse caminho! O Chad contou pra ele, né? Tenho certeza!";
			link.l1 = "Provavelmente. Eu mal consegui chegar.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "E eu estava dormindo. Ele teria me matado num piscar de olhos... Mas como você sabia que ele estava vindo pra cá?";
			link.l1 = "Oh... Eu tenho meus truques, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Você me salvou de novo, bonitão. Você sempre aparece bem na hora, né? Como é que você faz isso?";
			link.l1 = "Olha, eu não sei. É só um dos meus muitos talentos. O seu cerco acabou – Chad Kapper está morto, assim como todos os amigos dele. O Ciclope era o último daquela tripulação podre.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Sério, "+pchar.name+"? Você não tá brincando comigo, né?";
			link.l1 = "De jeito nenhum. É que eu preciso descansar um pouco depois desses últimos dias...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Agora eu posso finalmente respirar aliviada! Obrigada... muito obrigada! Você é meu herói, né?";
			link.l1 = "Eu adoro ouvir isso – ser o seu herói, sabe? Só fico feliz que você esteja finalmente segura.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "E aí?";
			link.l1 = "O que foi, linda?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Por que você está só parado aí? Vem cá, cavalheiro.";
			link.l1 = "E fazer o quê?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Vem aqui e me abraça, me beija. Você quer isso, eu sei, né?";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Não me deixa...";
			link.l1 = "Estou aqui, Mary, querida...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Tudo pode esperar. Seu Almirante pode esperar, seus piratas podem esperar – esta noite é só nossa, né?";
			link.l1 = "Sim.";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "E todas as noites depois...";
			link.l1 = "Sim, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Você voltou... sem ela. Então, ela não conseguiu te tirar de mim.";
				link.l1 = "Mary, suas suspeitas não tinham fundamento. Você é a única pra mim. Sempre estive com você nos meus pensamentos e nos meus sonhos.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", por que você está lutando contra os Narvais? Eu moro no território deles – sou uma deles, caso tenha esquecido. Por favor, vá até o Fazio e faça as pazes, estou te implorando.";
				link.l1 = "Tá bom, Mary, vou fazer como você pediu, né?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", tem alguma coisa te incomodando. O que foi?";
				link.l1 = "Mary, preciso falar com você.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! Todos os Narvais estão falando de você!";
				link.l1 = "Sério, meu amor?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Esta espada larga é incrível! Obrigada! Quero te dar um presente também. Claro, não se compara ao seu, mas quero que aceite, né?";
				link.l1 = "Mary, eu valorizaria qualquer presente seu... obrigado, meu amor.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Dia cheio pela frente, né? "+pchar.name+"? Boa sorte!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, precisamos ir ver o Jurgen hoje.";
					link.l3.go = "narval";
				}
				link.l1 = "Obrigada, Mary! Não tenho dúvidas disso.";
				link.l1.go = "exit";
				link.l2 = "Hoje não, Mary. Quero descansar um pouco aqui. Tudo bem pra você, né?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Bem, "+pchar.name+", como você está? Correndo pela ilha como sempre, né?";
				link.l1 = "Sim, Mary. Tem muita coisa pra fazer...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = ""+pchar.name+", já está anoitecendo, do que você está falando? Fica aqui, vamos tomar uns drinks e relaxar, né? Todo o resto pode esperar até amanhã!";
				link.l1 = "(rindo) Claro, amor, não precisa dizer mais nada...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, vamos à taverna hoje, né?";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, querida, estou muito ocupado agora. Volto daqui a pouco.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Não esquece de me visitar à noite. E nem pense em me evitar, né?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, a gente precisa ir ver o Jurgen hoje.";
					link.l3.go = "narval";
				}
				link.l1 = "Claro, Mary, como eu poderia? É claro que vou te visitar.";
				link.l1.go = "exit";
				link.l2 = "Mary, quero descansar aqui esta noite. Você se importa, né?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "O que você está falando? Já está de noite! Você não vai a lugar nenhum, vai ficar aqui, comigo, né?";
			link.l1 = "(rindo) Seu desejo é uma ordem, meu bem...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Nem começa...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Uma ótima ideia, "+pchar.name+", né! Eu concordo!","Vamos, né? "+pchar.name+"! Sancho tem uma bela coleção de vinhos, tem muita coisa pra escolher!","Ah, eu adoraria, né? Sempre é divertido na taverna do Sancho e ele tem uma seleção ótima de vinhos!");
			link.l1 = "Vamos!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Claro, "+pchar.name+", quanto tempo você vai ficar?";
			link.l1 = "Vou ficar até o meio-dia...";
			link.l1.go = "rest_day";
			link.l2 = "Vou ficar até o anoitecer...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Claro, "+pchar.name+", quanto tempo você vai ficar?";
			link.l1 = "Vou ficar até o anoitecer...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Você voltou... sem ela. Então ela não conseguiu te tirar de mim!";
				link.l1 = "Mary, suas suspeitas eram infundadas. Você é a única pra mim. Sempre estive com você nos meus pensamentos e nos meus sonhos.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", por que você está lutando contra os Narvais? Eu moro no território deles – sou uma deles, caso tenha esquecido. Por favor, vá falar com o Fazio e faça as pazes, eu te imploro.";
				link.l1 = "Tá bom, Mary, eu vou fazer como você pediu.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Esta espada larga é incrível! Obrigada! Quero te dar um presente também. Claro, não se compara ao seu, mas quero que aceite, né?";
				link.l1 = "Mary, eu valorizaria qualquer presente seu... obrigado, meu amor.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Já vai embora, "+pchar.name+"? Boa sorte e não vai esquecer de mim, né...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, a gente devia ir ver o Jurgen hoje, né?";
					link.l3.go = "narval";
				}
				link.l1 = "Obrigada, Mary!";
				link.l1.go = "exit";
				link.l2 = "Mary, quero descansar um pouco aqui. Tudo bem pra você, né?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Você não vai para o seu Kukulcan, "+pchar.name+"?";
				link.l1 = "Ainda não, ainda estou me preparando.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Já está anoitecendo, "+pchar.name+". Por que você não fica aqui? Quero ficar com você.";
				link.l1 = "Tá bom, querido, eu vou ficar...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, vamos à taverna hoje, né?";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Boa sorte e não esquece de mim... Vem me ver à noite se puder, né?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, a gente devia ver o Jurgen hoje.";
					link.l3.go = "narval";
				}
				link.l1 = "Muito bem, querido.";
				link.l1.go = "exit";
				link.l2 = "Mary, quero descansar um pouco aqui. Você se importa, né?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "O que você está falando? Já é noite! Não, você não vai a lugar nenhum, vai ficar aqui, né!";
			link.l1 = "(rindo) Tá bom, eu fico...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Capitão "+pchar.name+"! Oficial Mary Casper pronta para servir sob seu comando!";
				link.l1 = "Muito bem, oficial! Eu ordeno que você suba a bordo do navio imediatamente. Mas antes... beije seu capitão!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "Isso foi incrível, meu bem... Bom dia!";
				link.l1 = "Bom dia, meu bem! Você é maravilhosa!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Você falou com o Donald? É verdade que o Almirante queria fazer uma aliança com os Rivados e lutar contra os Narvais? É verdade que você o convenceu do contrário? Vai haver paz entre os piratas e os Narvais?";
			link.l1 = "Sim, Mary. É isso mesmo.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", eu nem sei o que dizer... Dizem também que o Donald te considera um amigo. Quem sabe você acabe virando um dos Narvais, né!";
			link.l1 = "Vá ver o Donald quando puder – ele também quer fazer as pazes com você. Ele pede que você o perdoe pelas palavras dele e por não ter conseguido te proteger do Chad.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Dane-se o Donald! Mas... fico feliz em ouvir isso, claro. Eu vou vê-lo. Mas você! Eu... eu tenho orgulho de você, né?";
			link.l1 = "Meu Deus, Mary, você... ah, faz meu coração disparar!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Vamos conversar! Você está com problemas?";
			link.l1 = "Não. Mary... você se lembra da noite em que nos conhecemos? Depois que lidamos com aqueles dois canalhas, eu te disse que tinha chegado aqui em um navio.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Eu lembro, sim. Seu barco afundou e você teve que nadar até aqui... né?";
			link.l1 = "Eu menti. Você teria me achado louca se eu tivesse contado a verdade naquela hora. Não havia nenhuma barca. Usei o ídolo mágico de um deus indígena, Kukulcán, no Mar das Espanhas, pra chegar aqui.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... do que você está falando? Kukulcan?";
			link.l1 = "Mary, querida, você precisa acreditar em mim, porque não tem nada de racional nisso, e eu não posso contar isso pra ninguém, só pra você. Nathaniel Hawk sumiu ao tocar no ídolo indígena. Ele estava sendo perseguido e isso trouxe ele pra cá...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "...";
			link.l1 = "Eu estava procurando pelo Nathaniel. Falei com o xamã indígena e toquei no ídolo, igual o Hawk fez. Fui teletransportada para dentro do porão do San Augustine, saí por um buraco no casco... e o destino me trouxe até você.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Isso aqui é pra virar uma história engraçada pra contar pros nossos filhos um dia, ou você ficou maluco?";
			link.l1 = "Eu não estou bravo, Mary! Eu entendo que é difícil de acreditar – e deve parecer loucura pra você – mas, por favor... confie em mim.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Parece que as histórias do Eric eram verdadeiras...";
			link.l1 = "Quem é Eric? Que histórias?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric era um dos locais, um velho marinheiro, já morreu faz tempo. Quando eu era criança, ele costumava me contar histórias sobre um ídolo indígena, um santuário onde os Rivados sacrificavam pessoas aqui na ilha.\nQuem tocava nele... sumia... e nunca mais era visto. Eu achava que eram só histórias pra assustar criança.";
			link.l1 = "É verdade, Mary. O Eric não estava mentindo.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Por sorte, o navio com aquele ídolo terrível afundou. Nunca vi ele com meus próprios olhos.";
			link.l1 = "Eu encontrei, descansando no fundo.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Você mergulhou lá?! Aquele maldito inventor Vedecker te deu o traje dele? Tem caranguejo rastejando lá embaixo, né! Desgraçado! Te colocando em perigo desse jeito--!";
			link.l1 = "Mary, não se preocupe comigo. Eu sei lidar com os caranguejos. Eles não são tão perigosos quanto dizem. Estou procurando a estátua desde o meu primeiro dia nesta ilha e, finalmente, a encontrei.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "E o que vai acontecer agora?";
			link.l1 = "O ídolo é a única saída daqui. Eu cheguei a esta ilha por meio de um ídolo igualzinho ao que está no fundo do mar, e vou usá-lo de novo para voltar... Mary! Você está chorando? Ah, Mary, por favor, não...";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Por que eu não choraria? Eu vou chorar sim, né... (chorando) Essas coisas sempre acontecem com os meus homens! Eu vou ficar sozinha de novo!";
			link.l1 = "O que você acha que vai acontecer comigo? Você realmente acha que eu simplesmente te deixaria aqui?! Eu vou voltar pra te buscar, num navio. Eu preciso levar você e "+sTemp+"Nathaniel voltou pra mim. Você vai me seguir pelo mundo, né?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(chorando) Claro... claro que eu vou... Você vai voltar pra me buscar, né? Como diabos você pretende voltar pra ilha? Só o Tubarão sabe navegar até aqui – e nem pense em me esquecer, senão eu te arrebento quando te encontrar!";
			link.l1 = "Mary, chega! Claro que eu vou voltar pra você! Quem mais faria meu coração disparar desse jeito desde que te conheci? Não se preocupa, meu amor, o Shark já me passou as coordenadas e o caminho pra ilha. Eu vou te encontrar de novo.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Você disse que o ídolo do litoral espanhol te mandou pra cá, mas e se aquele lá de baixo te levar pra outro lugar, pra África talvez? O que é que eu faço então?!";
			link.l1 = "Kukulcan is an Indian god; it will take me somewhere in the Caribbean or the Spanish Main. I only need to find a settlement; then it will be easy for me to find my ship and crew.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(chora) Promete pra mim... não, jura pra mim que você vai voltar, né?!";
			link.l1 = "Mary, minha querida, eu juro pra você que vou voltar. E vou te tirar desse lugar miserável. Não vai precisar sentir minha falta por muito tempo. Chega dessas lágrimas.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Tá bom, "+pchar.name+"... ... Volta pra mim, vou estar te esperando, né! Quando é que você vai partir?";
			link.l1 = "Eu ainda não sei. Preciso me preparar primeiro, depois vou mergulhar e tocar na estátua. Vão dizer que eu me afoguei – não acredite neles. Vai dar tudo certo.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Entendi. "+pchar.name+", querido, me abraça... me beija...";
			link.l1 = "Mary... minha querida Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Por quê?";
			link.l1 = "Você vai ver. Isso vai ser uma surpresa agradável.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh, que interessante! Agradável? Né? Vamos logo, antes que eu morra de curiosidade!";
			link.l1 = "Você vai adorar, tenho certeza. Vamos!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Vamos, "+pchar.name+"!";
			link.l1 = "Claro...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Bem, "+pchar.name+", que surpresa você tem pra mim?";
			link.l1 = "Mary! Jurgen and I decided to make you a present from us both. This is a unique blade, a broadsword carrying the Narwhal name. There are only two of such swords in the world: the first was owned by Alan Milrow; this one will be yours. It is made of special iron, forged by Jurgen's masterful touch, which will never go dull or rust.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Minha querida... Todos os Narvais sabem o quanto você sofreu. Você merece carregar esta espada larga, símbolo do clã Narval. Use-a com orgulho. Esta lâmina será um terror para seus inimigos e vai te proteger bem na batalha.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Isso... é pra mim?...";
			link.l1 = "Sim, Mary. "+sld.name+"  pediu para eu fazer isso pra você, e trouxe um ferro único do fundo do mar. Nenhum aço se compara ao peso e à força desse material. Coloquei minha alma nessa espada, assim como fiz um dia com a do Alan.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "I don't know what to say... Thank you, Jurgen, thank you! I'll carry it with pride, and be worthy of it, I swear, all right! I don't train with broadswords often; I will now!";
			link.l1 = "Não tenho dúvida, moça.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... espera... você é o melhor homem que já conheci! Você é incrível, né? Sabe o que isso significa pra mim? Essa espada é o melhor presente que já ganhei! Você já fez tanto por mim, salvou minha vida duas vezes, e ainda assim consegue me surpreender! Obrigada, meu amor!";
			link.l1 = "Você merece isso, Mary. E eu vou continuar te surpreendendo todos os dias, até meu último suspiro! Seu sorriso me enche de alegria e fico feliz que tenha gostado do presente.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(risos) Obrigada! Que lâmina maravilhosa, né? Precisa de uma mão firme pra usar... Mal posso esperar pra começar a treinar com ela!";
			link.l1 = "Imagino que você vai pegar o jeito rapidinho. Corre lá pra sua cabine e experimenta, né?";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "É isso que eu vou fazer. Muito obrigada de novo, cavalheiro! "+pchar.name+"... Vem me ver hoje à noite, quando estiver pronto... (risos)";
			link.l1 = "Claro, minha senhora. Vejo você à noite.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Aqui, dá uma olhada. Encontrei isso em um dos navios no anel externo, dentro do baú de um capitão. Todo marinheiro experiente diz que esse amuleto é extremamente valioso para um navegador. Ele pode proteger um navio das piores tempestades. Muitos queriam comprá-lo, mas eu não quis vender... Eu queria que fosse seu, meu bem. Use esse amuleto para te proteger no mar.";
			link.l1 = "Obrigada, Mary! Muito atenciosa da sua parte, eu te amo!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Sério? Você gostou? Ah, que ótimo! Fico tão feliz, né?";
			link.l1 = "Este é um talismã muito raro e valioso. Claro que eu gostei! Obrigada, meu bem!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... você voltou. Eu fiquei esperando por você, olhando pro horizonte todo dia, né? Você voltou pra mim...";
			link.l1 = "Sim, Mary. Estou aqui como prometido. Deixa eu te abraçar, meu amor!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... You can't imagine what it's been like! The Narwhals said you drowned. They were all so sure you were dead. I kept telling them that you were alive... Of course, nobody believed me; they thought I'd gone mad after all that's happened.";
			link.l1 = "Mary... Minha querida! O que houve? Você está tremendo... está com frio?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Não, não estou com frio. Eu só... não quero falar sobre isso aqui. Vem na minha cabine depois. Quero conversar com você a sós, né? Você vai ver o Almirante e o Nathaniel agora?";
			link.l1 = "Sim. Preciso falar com o Tubarão e, claro, levar a Danielle até o Nathaniel. Não vou demorar. Te vejo logo, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Eu... Eu estou ansiosa para te ver. Venha o quanto antes, né?";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! Finalmente. Precisamos conversar, né!";
			link.l1 = "O que foi, Mary? Tem alguma coisa te incomodando. O que aconteceu?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "Ela apareceu... "+pchar.name+", quem é aquela vadia no seu navio?";
			link.l1 = "Vadia? Você tá falando da Danielle? Mas você já sab--";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Não, não a Danielle. Estou falando daquela loira quase pelada desfilando pelo convés do seu navio! Eu vi ela pelo telescópio, né!";
			link.l1 = "A-ah! Aquela é a Helen McArthur. Ela também está envolvida nessa história estranha, assim como a Danielle. Está servindo como minha oficial — mas só por enquanto, claro.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Oficial? Ela é sua oficial?!";
			link.l1 = "Bem, sim. Qual o problema nisso? Mary... droga, você está com ciúmes!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "É de se admirar?!... (em lágrimas) Eu fiquei te esperando esse tempo todo. Não dormi por sua causa, e você volta aqui com uma vadia--";
			link.l1 = "Mary! Para de chorar! O que está acontecendo com você? Você consegue abrir um homem sem pensar duas vezes, e mesmo assim seus olhos estão sempre molhados... Mary, querida, a Helen é só uma oficial, servindo temporariamente até alcançarmos nossos objetivos em comum, nada além disso.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I've been training hard with the broadsword you gave me, and I've mastered it perfectly!";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I've been training hard with rapiers and I've mastered them perfectly.";
			dialog.text = "(chorando) Capitão... Então eu também quero ser sua oficial, né? Eu sei lutar, você sabe disso! "+sTemp+" E eu atiro bem! Pode até ser que eu não saiba nada de navegação, mas aprendo rápido. Eu tenho talento, né?";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(concordo) Mary... Eu mesmo ia te oferecer o cargo. Não existe moça mais destemida ou habilidosa que você! Quero você ao meu lado!";
			link.l1.go = "adversary_hire";
			link.l2 = "(negar) Mary! Ser oficial de abordagem é perigoso! Você não entende o que está pedindo. Eu não posso arriscar a sua vida.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Não pode? Então aquela vadia loira pode ser oficial e eu não? Você tá mentindo, "+pchar.name+", você só não quer ficar comigo! (chorando) Então aquela garota é melhor do que eu, né?";
			link.l1 = "Mary, você não entende!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Eu sei! Eu vi o brilho nos olhos dela quando olhou pra você! Ela não é só uma oficial, né! Eu entendo isso. (chorando) Claro que eu não posso competir com ela – ela sabe comandar um navio...";
			link.l1 = "Mary, do que você está falando?";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "Acabou... (chorando) Vai embora! Volta pra sua vadia! E eu vou ficar aqui...! Me dá minha chave!";
			link.l1 = "Mas Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Vai embora...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Sério? Você realmente queria que eu fosse sua oficial? "+pchar.name+", droga, você não faz ideia do quanto isso me deixaria feliz! Eu quero tanto ser sua oficial... mas não no mesmo navio daquela loira!";
				link.l1 = "Mary, mas por quê?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Sério? Você realmente queria que eu fosse sua oficial? "+pchar.name+", droga, você não faz ideia de como eu estou feliz! Eu juro, não vou te decepcionar, você vai ver!";
				link.l1 = "Jesus, Mary, querida, você é preciosa. Você estava chorando há um minuto e agora seu rosto está todo iluminado! E, Mary, você não é só mais uma oficial pra mim. Você é muito mais do que isso e duvido que algum dia vá me decepcionar.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Talvez você só veja ela como sua oficial, mas duvido que ela só te veja como capitão. Eu vi o jeito que ela olhou pra você, eu conheço esse olhar, né? Mas só eu posso te olhar assim.";
			link.l1 = "Mary, querida, eu já te disse, eu não sinto nada por ela, e ponto final! Não tem nada entre a gente! Eu juro, caramba! Eu preciso da ajuda dela pra lidar com a bagunça que é a Irmandade da Costa. Se eu não ajudar ela, Jan Svenson não vai me ajudar a conquistar Tortuga, e eu preciso dele!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", querido, me abraça... Me desculpa. Eu acredito em você. Mas eu não vou conseguir ficar perto dela e ver ela flertando com você, né! Uma hora eu vou pegar minha espada e cortar ela ao meio!";
			link.l1 = "Acho que você teria mesmo... Você tem um temperamento forte, né?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "E se eu a matasse - você me deixaria... e por isso, eu nunca me perdoaria.";
			link.l1 = "E então, o que você sugere, Mary? O que devo fazer com ela?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Você disse que ela é uma oficial temporária. Eu me junto a você assim que você deixar ela em terra — de preferência numa ilha deserta. (risos) Eu te sigo até o fim do mundo, né?\nEntão me conta, "+pchar.name+" querido... ela é mesmo melhor do que eu?";
			link.l1 = "Besteira! Para com isso, Mary, não existe mulher melhor do que você!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Então prove. Eu não vou te dividir, "+pchar.name+"! Eu prefiro te deixar ir do que te dividir com outra pessoa, né?";
			link.l1 = "Tá bom, Mary. Vamos fazer um trato. Não posso me livrar da Helen agora – ela é fundamental pra minha missão. Vou ajudar ela com os problemas dela, fazer dela a rainha de Isla Tesoro, depois deixo ela ir, e aí não vai ter mais nada separando a gente. Com sorte, não vai demorar mais que um ou dois meses. Você espera por mim esse tempo todo?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Eu vou, né! Deixa eu deixar bem claro... Se você voltar pra mim, isso quer dizer que me escolheu em vez dela. E se não voltar... então é isso. Eu fico aqui e crio meu próprio clã – o clã Casper!";
			link.l1 = "Lágrimas de novo? Mary, vamos lá. Já chega disso! 'Encontrei meu próprio clã'... Sua boba, é claro que vou voltar! Eu jamais teria coragem de te deixar aqui no meio desses navios velhos e podres! Você iria inundar a ilha com suas lágrimas!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Volte o quanto antes então... "+pchar.name+", me beija, por favor...";
			link.l1 = "Eu volto. Eu prometo!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = ""+pchar.name+", voltou para me buscar?";
			link.l1 = "Claro! Eu já menti pra você alguma vez? Não aguentaria ficar longe de você e não pretendo me separar de novo... meu amor.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Sério? "+pchar.name+"! Eu vou te seguir aonde for! Nunca vou mentir pra você, nunca vou te trair, eu juro!";
			link.l1 = "Eu acredito em você, meu bem... Eu também não vou."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", querido, me abraça... A gente vai ficar juntos, né? Promete pra mim!";
			link.l1 = "Sim, nós vamos ficar juntos, Mary. Para sempre.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Assim como a Danielle e o Nathaniel?";
			link.l1 = "(rindo) Sim, igualzinho a eles.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Eu te amo! Acho que me casaria com você se você pedisse...";
			link.l1 = "Querida Mary... Claro – a gente conversa sobre isso depois. Sua vida nesse cemitério de navios acabou. Vamos tirar você daqui. Seja bem-vinda ao meu navio... e ao mundo lá fora, meu amor!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Vamos passar uma última noite juntos nesta ilha, a bordo do Ceres. Só nós dois. Não vou deixar você ir a lugar nenhum até o amanhecer, né?";
			link.l1 = "Bem, estamos atualmente no seu navio, não no meu... então vou seguir suas ordens, Capitã Casper.";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Sim, senhor!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Eu tive uma ideia...";
			link.l1 = ""+npchar.name+"? Não é seguro aqui. Eu mandei você ficar no navio--";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", puta merda, não tem lugar seguro nenhum! Tem pólvora suficiente nesse barco pra explodir a ilha inteira do mapa! Só escuta, né?";
			link.l1 = "Estou ouvindo, mas por favor, seja rápido.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "A corveta pirata e a fragata. Eles ainda acham que somos um dos deles... aquele tal de Knave, né? Então vamos pegar uns barris de pólvora, um estopim, e zarpar com a fragata.\nQuando estivermos lado a lado, acendemos o estopim, jogamos o barril pra eles e fugimos o mais rápido possível. Mandamos eles pelos ares, depois abordamos a corveta.";
			link.l1 = "Arriscado... embora... seu plano pode até funcionar. Mas só se conseguirmos enganá-los até estarmos perto o suficiente.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Eu digo que a gente tenta, "+pchar.name+"";
			link.l1 = "Tá bom. Vamos tentar. Rapazes! Peguem três barris de pólvora! Ha-ha, adoro como você pensa, "+npchar.name+"! Eu nunca teria pensado nisso sozinha.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Pode me agradecer depois... (pisca)";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Me apresentando como mandado, senhor! (risadinha) O que foi?";
			link.l1 = "O navio do Jackman está na Enseada Sabo-Matila: a fragata pesada Centurion. Esse navio já foi propriedade dos Hawkes, então devem haver itens e documentos importantes na cabine do capitão... Precisamos embarcar nela.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Damn me... How are you going to do that with our little bird? I looked through the spyglass; I've seen how many men and cannon Centurion's got, all right!";
			link.l1 = "Você tem razão. O Jackman tem pelo menos o dobro dos nossos homens, todos eles assassinos e mercenários experientes. Seria loucura abordar sem diminuir o número deles antes. E com o calibre dos canhões do Centurion, uma batalha prolongada no mar também está fora de questão. Eu não sei o que fazer...";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", eles ainda não nos reconheceram como inimigos, né? Tipo aqueles idiotas lá em Turks? Podemos usar nosso truque da pólvora de novo...";
			link.l1 = "Mary, eu acabei de dizer que precisamos abordar a fragata, não afundá-la!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Eu sei disso, "+pchar.name+"! Não vamos afundar ela. Vamos pegar alguns barris vazios de rum e enchê-los com pólvora, bala de canhão e estopins curtos. Depois vamos chegar perto da Centurion e jogar a bomba no convés dela.";
			link.l1 = "Ha! Você acha mesmo que isso vai funcionar?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Por que não? O costado deles é mais alto que o nosso, mas dois ou três homens — com a ajuda de roldanas — conseguem içar e lançar um barril cheio sem dificuldade. Aí a gente grita: 'Aqui tem rum de graça do Knave!' O barril explode antes mesmo deles entenderem o que aconteceu.";
			link.l1 = "A rajada de balins vai picar todo mundo no convés... Droga, até que é tentador.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Use cinco barris, "+pchar.name+". We have the element of surprise. They won't suspect a thing! But we've got to sail away after throwing the bomb so they don't board us though; once it blows, then we move back in and board them.";
			link.l1 = "E eles não podem nos identificar antes de jogarmos os barris... Droga, não vai ser fácil chegar perto deles. Jackman não é idiota como o Ghoul era.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Então é melhor você pegar seus melhores amuletos, "+pchar.name+". Confie na Mary Ruiva. Vale a pena tentar.";
			link.l1 = "Bem pensado, não temos nada a perder... Por que você não prepara os estopins?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Pode deixar, capitão! Pode contar comigo.";
			link.l1 = "Mary, você é maravilhosa!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Obrigada, "+pchar.name+"! Eu não vou te decepcionar!";
			link.l1 = "I know you won't; I hope we're the ones that don't let you down by fucking up this plan of yours... To arms!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Aí está você! Deu trabalho te encontrar... Isso foi incrível, capitão! Nunca vi um salto tão impressionante! Que herói! Mas confesso, quase me matou do coração. Um dia você ainda me mata com essas suas loucuras, viu, querido...\nAgora, quem diabos seria essa aí? Te deixo sozinho por um minuto e, quando vejo, já arrumou uma qualquer.";
			link.l1 = "Mary! Essa 'vagabunda' é Catherine Fox, filha do Coronel Fox, o comandante dos Raposas do Mar. Precisamos levá-la para Antígua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, é mesmo? Que delícia. Tá bom, você pode me contar sobre ela... hoje à noite. Na nossa cabine. Comigo. Sozinhos. Agora vamos, precisamos nos apressar!";
			link.l1 = "(suspiro) O que eu faria sem você, Mary? Catherine, vamos!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Meu Deus, você acordou! Seu desgraçado! Nunca mais me assuste desse jeito!";
			link.l1 = "Mary... querida, o que aconteceu? Minha cabeça está... ai...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando entramos na cabine do capitão, você estava deitado no chão, imóvel como um cadáver. Te pegamos e arrastamos para o nosso navio – ainda bem a tempo, porque os esqueletos que estavam espalhados pelo convés começaram a se levantar de novo. Meu Deus, foi assustador demais! Não podíamos fazer nada contra eles! Cortamos as amarras e tentamos zarpar, mas uma saraivada dos canhões deles danificou muito o nosso navio e perdemos o controle. Aqueles eram uns verdadeiros demônios, né? E aí içaram as velas e sumiram no horizonte num piscar de olhos. Nosso navio encalhou, então pegamos os botes e viemos para essa praia antes que a tempestade acabasse com ele. Muita gente morreu hoje, mas o navio sobreviveu no fim... por pouco.";
			link.l1 = "Bom trabalho, Mary... O que eu faria sem você?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Ah, deixa eu ver... talvez afogada? Presa naquele navio? Esmagada pelos mortos? Puta merda... e foda-se você também, "+pchar.name+", por me dar um susto desses!";
			link.l1 = "Shhh, Mary, shhh. Obrigado por me salvar, meu amor. Quanto tempo eu fiquei desacordado?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "A day. I cleaned your wounds, gave you medicine, and poured some rum into you. You should get well soon; don't you dare die on me!";
			link.l1 = "Eu prometo que não vou, meu bem. Mas... já me senti melhor...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Você já esteve melhor... Foi ela, "+pchar.name+"? Foi o 'Holandês Voador'? Já ouvi histórias, mas nunca imaginei...\nPor que eles nos perseguiram? E por que não atiraram em nós antes de embarcar?";
			link.l1 = "O capitão deles queria o amuleto, aquele sobre o qual falei com Tuttuathapak – o xamã indígena. Por isso eles nos abordaram, mas assim que o capitão deles conseguiu o amuleto, não precisavam mais de nós inteiros...\nQue pesadelo! Um navio tripulado pelos mortos! Inacreditável... Eu achava que já tinha visto de tudo de ruim que o Caribe podia oferecer.";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Era de se esperar que o 'Holandês Voador' viesse atrás de você, de todas as pessoas, mais cedo ou mais tarde. Meu Deus, isso foi suficiente pra me dar vontade de voltar pra igreja!";
			link.l1 = "Eu sei como você se sente. Preciso voltar àquela aldeia indígena, contar ao Tuttuathapak o que aconteceu. Aquele navio nos atacou por causa do amuleto! Espero que aquele diabo de pele vermelha tenha uma explicação pra me dizer por que diabos aqueles mortos-vivos queriam tanto esse negócio.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Tá bom, mas toma cuidado — você ainda tá um caco, né?";
			link.l1 = "Você é tudo o que eu preciso pra me curar. E... Mary, eu te amo...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Eu também te amo, meu amor... graças a Deus estamos vivos!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", nada me faz mais feliz do que estar nos seus braços, né... Vamos!",""+pchar.name+", eu estaria com você em cada momento acordada se fosse possível. Vamos!");
			link.l1 = RandPhraseSimple("Você é o melhor, meu amor...","Você é maravilhosa, meu amor...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Mmm, você foi incrível... como sempre é!","Isso foi incrível!");
			link.l1 = RandPhraseSimple("Fico feliz por poder te agradar, meu amor...","Eu te amo, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", eu adoraria estar nos seus braços agora, né... Mas não é a melhor hora – precisamos pegar aquele canalha do Thibaut antes que ele fuja.";
				link.l1 = "Você está certa como sempre, minha garota...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", nada me faz mais feliz do que estar nos seus braços, né... Vamos!",""+pchar.name+", eu estaria com você o tempo todo se fosse possível. Vamos!");
			link.l1 = RandPhraseSimple("Você é a melhor, minha garota...","Você é maravilhosa, minha bela ruiva...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", faz tanto tempo que a gente não transa... Você me esqueceu completamente, né! Vamos pegar um quarto pra essa noite e deixar os problemas pra outro dia.",""+pchar.name+", estou começando a achar que você me esqueceu completamente! Amor, quero passar um tempo... só nós dois. Vamos pegar um quarto para esta noite, né?",""+pchar.name+", onde você esteve? Tô morrendo de vontade de passar a noite com você, tomar um vinho e relaxar. Você ficou todo esse tempo no mar e esqueceu completamente de mim!");
			link.l1 = "Mary, querida, o que você está dizendo, 'me esqueceu completamente'? Boba... Mas é verdade que andei muito ocupado – os problemas que exigem minha atenção não têm fim. Me perdoa, meu amor. Vamos subir, esta noite sou todo seu. O mundo pode esperar!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Hoje não, querido. Tenho muita coisa pra fazer.","Mary, meu bem, como você pode pensar que eu te esqueci? Vamos passar um tempo juntos depois — agora, temos trabalho a fazer."),RandPhraseSimple("Você não sai da minha cabeça, Mary, mas agora não podemos baixar a guarda.","Mary "+npchar.lastname+", não temos tempo pra isso hoje."));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "(suspiro) Tá bom, acho que vou brincar sozinha na minha cabine... Né, capitão.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, querida, o que você está dizendo, 'esqueceu completamente de mim'? Boba... Mas é verdade, tenho estado ocupada demais – os problemas que exigem minha atenção não acabam nunca. Me perdoa, meu amor. Vamos subir, esta noite sou toda sua. O mundo pode esperar!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Ah, aí está você! Não gosta mais de mim, né? Fala logo!";
			link.l1 = "O quê?! Mary, que bobagem é essa? Por que você acha isso?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Então por que você anda visitando aquelas vadias, aquelas prostitutas de bordel? Eu sei que anda, não mente pra mim! Tem alguma coisa em mim que você não gosta quando a gente faz amor, né? (chorando) Me fala...";
			link.l1 = "Mary, Mary... calma, por favor, minha menina. Sim, eu estive no bordel algumas vezes, mas só por assuntos de trabalho. Eu não estava procurando diversão, não!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "E que tipo de 'assuntos de negócios' você tinha no quarto de cima? (chorando) Você está mentindo, "+pchar.name+"!";
			link.l1 = "Mary, querida, para com isso, por favor... Eu realmente tinha uns assuntos de negócios com a dona do bordel.  E sim, subi lá algumas vezes – da última vez foi por um assunto pessoal do governador: ele me pediu pra encontrar a aliança de casamento dele. Como eu poderia recusar Sua Excelência?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "...";
			link.l1 = "E como eu poderia explicar para a dona que eu precisava olhar debaixo da cama lá em cima? Não dava. Então tive que pagar por uma prostituta por uma noite só pra poder subir...\nNa segunda vez, me disseram que um comerciante tinha perdido os documentos do navio ali. Tive que pagar por outra garota pra poder vasculhar o quarto – e acabei achando os documentos, fui muito bem paga por eles, na verdade...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "...";
			link.l1 = "E na terceira vez eu estava ajudando o comandante local: tive que perguntar às prostitutas sobre um oficial da guarnição. Esse oficial era suspeito de espionagem e de negociar com piratas. No fim, conseguimos pegá-lo e eu recebi uma bela recompensa...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "...";
			link.l1 = "Tá vendo? Eu te disse, era só negócio. Mary, é você que eu amo e de quem preciso. Eu sou fiel a você, juro! Você acha mesmo que eu seria capaz de me deitar com alguma prostituta imunda do porto, tendo você? Como é que você pode pensar uma coisa dessas!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = "... Isso parece a maior besteira que já ouvi na minha vida. Mas... "+pchar.name+"... você está me dizendo a verdade? Você não transou com outra mulher pelas minhas costas, né?";
			link.l1 = "Mary, querida, não, eu juro que não. Você é a única mulher que eu amo, é verdade. Chega mais perto, querida. Deixa eu te abraçar... Enxuga essas lágrimas e, por favor, para de sentir ciúmes! Eu nem vou olhar pra um bordel de novo, se é isso que você quer!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "É isso que eu quero!... "+pchar.name+", eu fico com ciúmes porque eu te amo... e não quero te perder, né? Se alguma vagabunda ousar sorrir pra você, é a minha espada que vai atravessar ela na hora!";
			link.l1 = "Jesus, Mary, se acalma... não precisa matar ninguém! Você não vai me perder, eu prometo. Tá tudo bem, calma. Você é a única mulher pra mim – e a melhor do mundo, viu? Confia em mim.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", que pergunta estranha? Eu te amo. Você me salvou. Você acha mesmo que eu ia deixar você ir lá sozinho? Nem pense nisso, né! Eu tô com você! Quando a gente vai?";
			link.l1 = "Você tem razão, querido. Como eu poderia duvidar disso? Eu te aviso quando formos. Mas antes, precisamos nos preparar direitinho.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Estou pronta, "+pchar.name+". Eu te sigo até o Inferno e além!";
			link.l1 = "Obrigada, meu amor...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.MarySexBlock = "true"; // fix 22-03-20
			dialog.text = "O que temos desta vez, Capitão? Espanhóis? Piratas? Ou coisa pior?";
			link.l1 = "É pior, Mary, muito pior. O governador pretende visitar uma cortesã famosa e eu devo acompanhá-lo como pessoa de interesse. Conversas entediantes, vinho caro demais e nobres chatos.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Na verdade, é o contrário: um convite para um evento social, organizado por uma dama da nobreza. Sua Excelência me pegou de surpresa ao pedir que eu o acompanhasse, mas, para ser sincera, estou ansiosa por essa distração.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "O-ho! De fato, é ainda pior! Uma cortesã! Vinho fortificado! Farras! Sim, parece uma tortura pura, "+pchar.name+", seu filho da pu--";
			link.l1 = "Mary, calma, por favor. Não é como se eu estivesse indo lá para... não é um bordel! Bem... é um bordel, mas que eu seja amaldiçoado se não sou um homem honrado e de palavra. Você realmente não confia em mim, depois de tudo que passamos juntos? O governador só me pediu um pequeno favor e eu preciso ajudar, só isso!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Sim, já ouvi falar de alguns desses 'nobres', né? Já vi eles na sua companhia também. Ser cortesão é o pão de cada dia deles. 'Alta' sociedade, 'entretenimento' digno, que nada! Casamento não impede esses caras de visitar essas... aff... 'damas'. Eu esperava mais de você, "+pchar.name+". Bem, vocês, 'nobres', podem lamber o meu cu sujo.";
			link.l1 = "Mary, espera! Porra...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Nós dois merecemos umas férias. Heh, será que eles aguentam ver uma moça usando um casaco vermelho? Imagina só os cochichos nos cantos! Alguém com certeza vai desmaiar – isso ia ser divertido, né?";
			link.l1 = "Mary, minha querida, esse não é o tipo de festa pra levar uma dama... pelo menos não uma dama como você. É meio complicado, mas deixa eu te explicar--";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Uma moça como eu? Fala logo: eu não sirvo praqueles almofadinhas de peruca. Simples demais, gente comum demais, né? Não sou boa o bastante pra festas chiques, pro honrado monsieur Charles de Maure?";
			link.l1 = "No, not at all. You're amazing and I don't care about the kind of impressions we make on the people around us. The governor is trying to solve his problems with my help, as always. I will be like a valuable trophy for him; an interesting guest to impress the noble good-for-nothings.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Não, "+pchar.name+", tudo bem, eu entendi. Nobre com nobre – e a ralé fica do lado de fora. (faz uma reverência) Espero sinceramente que aproveite sua festinha, Meu Lorde Idiota. Falo com você quando voltar pra terra dos mortais, né?";
			link.l1 = "Mary, espera! Ah, merda...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Espero sinceramente que aproveite sua social, Meu Lorde Babaca. Falo com você quando voltar para a terra firme, né?";
			link.l1 = "Mary, ah, qual é!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Olha só isso, né! Nosso capitão perdido na alta sociedade!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Você some no bordel por um dia e agora a cidade inteira só fala disso. Charles, me dá só um bom motivo pra eu não enfiar o Narval no seu traseiro.";
			link.l1 = "Mary, eu vou te explicar tudo, mas depois. Agora preciso me preparar para um duelo – pode me matar se eu sair vivo dele. Enquanto isso, cuida do nosso novo navio pra mim, né? Ganhei ele como prêmio num jogo de cartas ontem à noite.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Dane-se o navio, que duelo é esse? Se for pra acreditar no que dizem por aqui, você vai lutar ou com o filho do rei ou com o próprio Papa. Me explica que porra tá acontecendo!";
			link.l1 = "Esse homem é o bastardo de um nobre muito influente, o Conde de Levi Vantadur. Foi ele quem me desafiou, e eu preciso vencer o duelo sem machucá-lo – para evitar a ira do pai dele.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Enquanto eu fico sentada na banheira que você acabou de ganhar. Você ficou maluco, Charles?";
			link.l1 = "Infelizmente, tem que ser assim. O governador me designou alguns oficiais nobres para serem meus segundos, para evitar qualquer confusão depois. Não posso levar você ou qualquer um da tripulação comigo, para garantir a integridade oficial do duelo. Isso é sério demais, me desculpe.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "... Sabe o que eu vou fazer agora? Vou subir naquele maldito navio e ficar realmente bêbada. Faça o que quiser, mas você acertou uma coisa: se aquele filho da nobreza não conseguir te matar, eu mesma faço isso.";
			link.l1 = "Mary, vai dar tudo certo, confia em mim. Agora, espera... Merda! Lá vamos nós de novo!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Aí está você! Não tivemos uma palavra sua o dia todo! Ouvimos os boatos no mercado e ficamos preocupados. Dizem que você andou apostando navios e mulheres, e até entrou num duelo com algum príncipe da coroa ou até com o próprio Papa! Que diabos está acontecendo?";
			link.l1 = "É complicado, Mary. Vai demorar um pouco pra explicar. Mas consegui ganhar uma fragata. Você vai ter que cuidar dela enquanto eu resolvo minha briga com o antigo dono, né?";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Então vai ter um duelo?! Quem era o dono anterior? Por que você está lutando com ele?";
			link.l1 = "É complicado, mas resumindo: ganhei o navio dele e a... dama dele. Ele me acusou publicamente de trapaça e me desafiou para um duelo. Esse homem é o bastardo de um nobre muito influente, o Conde de Levi Vantadur. Vou ter que vencer o duelo de algum jeito sem machucá-lo.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Então os boatos são verdade? Eu até entendo apostar um navio, mas... uma mulher, sério?";
			link.l1 = "Damn it, Mary, it's not like that at all! He won her from the governor; I won her back from him to release her, that's it. There is nothing more to it, I swear!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Olha, talvez isso seja normal pra vocês, nobres, mas pra mim não é, né! Faz o que quiser, fala o que quiser... vai morrer por ela se quiser! Eu, por mim, quero é ir pra porra do navio que você ganhou e bagunçar meu sótão com rum até não poder mais. Vai pro inferno, "+pchar.name+", Eu acreditei que o que a gente tinha era de verdade e que ia... que ia durar pra sempre. Acho que esperei demais, né!";
			link.l1 = "Mary, eu não dou a mínima pra aquela mulher! Só espera, por favor... Droga! Lá vamos nós de novo...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, você veio por mim! Eu sabia, nunca duvidei, né? Estou tão feliz em te ver!";
			link.l1 = "Eu também, Mary! Isso tudo tem me consumido... Graças a Deus que você está bem!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aliás, o que foi que você fez pra eles me soltarem tão fácil assim? Sem nem uma briga de verdade ou troca de tiros! Ah, e eu vi uma mulher no convés enquanto me arrastavam pra fora. O que aconteceu, Charles?";
			}
			else
			{
				dialog.text = "O que exatamente você fez pra eles me soltarem assim? Sem briga, sem tiro, nada! Eu vi uns pavões britânicos no convés quando estavam me trazendo pra fora. Que história é essa, Charles?";
			}
			link.l1 = "O que importa é que você voltou pra mim. Eu falhei com você, Mary. Me desculpa, de verdade! Espero que você consiga me perdoar de coração. Eu detesto como as coisas ficaram entre a gente.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Eu já fiz isso. Eu também sinto muito, né. Não devia ter levado tão pro lado pessoal o seu caso com aquela mulher... Eu devia ter montado uma vigia decente naquela noite – nunca teriam nos pegado tão fácil! Fui uma idiota!";
			link.l1 = "O passado é passado. Eu te amo e nunca mais vou te deixar daquele jeito. Eu prometo!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Desculpa por ter duvidado de você, Charles. Talvez... seja melhor eu não saber exatamente o que você fez, né? Estamos juntos de novo e isso é o que importa.";
			link.l1 = "Eu não tenho segredos pra você. Vou te contar...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Que história... duvido que mais alguém acreditaria nisso, né? Eu sabia! Eu sabia que essa sua noite 'social' tinha coisa estranha! Aqueles pavões nobres... uns desalmados! Pelo menos não errei sobre você – eu sabia que você era diferente, né?";
				link.l1 = "Tenho certeza de que muita gente por aí me acha bem pior. Um verdadeiro monstro de conto de fadas.";
			}
			else
			{
				dialog.text = "Que história... duvido que mais alguém acreditaria, né? Eu sabia! Eu sabia que sua 'noite social' tinha coisa estranha! Política, espiões, con-spi-ra-ções — e mesmo assim, você, de novo, salvou todo mundo, né! Meu herói.";
				link.l1 = "Não tenho tanta certeza disso... é bem provável que a guerra com a Grã-Bretanha comece em poucas semanas. Mas eu fiz o que precisava, Mary. Você significa tudo pra mim.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "I don't care what people think; if that's the case, you'll be my monster, Charles! And if people don't like it, let me talk to 'em. I'll always be by your side, all right!";
			}
			else
			{
				dialog.text = "Eu sei, Charles. Sempre soube... mas é bom ouvir você dizer isso. E eu também vou estar sempre ao seu lado, né!";
			}
			link.l1 = "Eu nunca duvidei, Mary. Vamos, o pessoal está preocupado. Hora de zarpar e cair fora daqui. Você está ao meu lado de novo, e aquele horizonte está esperando...";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Sim, sim, Capitão!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, é mesmo você? Eu quase perdi toda a esperança, né? Meu Deus, senti tanto a sua falta! Por favor, me perdoa, por favor!";
			link.l1 = "Não, me perdoe, eu não esperava por isso... Graças a Deus você conseguiu, Mary! Estou tão feliz!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Falando em perdão... pra ser bem sincera, tô pensando se te dou um tiro ou um abraço. É melhor você me contar o que diabos tá acontecendo, né?";
			link.l1 = "Eu te amo, Mary. Era só isso que eu queria te dizer.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Bem, isso não explica muita coisa, mas... Droga, Charles. Eu também te amo, né. Meu Deus, finalmente, eu tenho você comigo, enfim!";
			link.l1 = "E eu não quero passar o tempo que temos falando sobre coisas que não importam. Vem comigo e eu não vou ousar te deixar esta noite, mesmo que o céu desabe sobre esta cidade miserável. Eu nunca mais vou te deixar. Nunca.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Talvez... seja melhor eu não saber exatamente o que foi que você fez, né? Estamos juntos de novo e isso é tudo que importa...";
			link.l1 = "Eu não tenho segredos com você. Eu vou te contar...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Você está dizendo que essa... marquesa te ajudou a me trazer de volta? E que você quase começou uma guerra entre a Inglaterra e a França? Não me entenda mal – tudo isso é bem romântico, mas o que vai acontecer agora?";
			link.l1 = "Eu não faço ideia, Mary. Estamos juntos de novo, nada mais importa. Se aqueles no poder não conseguirem varrer tudo para debaixo do tapete... bem, estou preparado para cumprir meu dever diante da Coroa.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "E aquela marquesa sua? Trouxe ela de volta também? O português falou muito bem dela. Ele me garantiu que você resistiu às investidas dela como o castelo da Bastilha. Quero acreditar nele, né, mas quero ouvir isso da sua boca.";
			link.l1 = "Não tem nada acontecendo entre eu e a Madame Botot, Mary. Eu ajudei ela, ela me ajudou, só isso. Falando no Bartholomew, onde ele está?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Já faz tempo, né? Ele partiu logo depois que me trouxe aqui. Eu jurei que não ia pra aquele maldito bordel, então ele alugou um quarto pra mim, pagou adiantado por algumas semanas e simplesmente... foi embora. Ah, quase esqueci! Tenho uma carta pra você!";
			link.l1 = "Uma carta? Do Bartolomeu, o Português? Não estou gostando do rumo disso...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Vai lá, lê. Eu vou ver os rapazes. Devem estar preocupados. Todo mundo conseguiu sair bem? Espero que não se importe se a gente tomar uma ou duas taças lá embaixo. Não vai se meter em outra confusão até eu voltar, né?";
			link.l1 = "Tá bom, mas por favor, toma cuidado com eles, Mary, né? Eu preferia passar a noite com você do que ter que carregar gente bêbada de volta pro navio. Meu Deus, ainda não acredito que consegui ter você de volta!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Eu, você, a praia e um bom vinho – Charles, isso é tão romântico! A gente devia fazer isso mais vezes, né?";
			link.l1 = "Que bom que você gostou. Acho que a gente vai passar mais tempo juntos daqui pra frente, pra momentos assim.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "O que você quer dizer? Aconteceu algo com o navio? Por que você está de joelhos?";
			link.l1 = "Porque eu te amo, Mary. Você sabe disso, eu sei disso, o mundo inteiro sabe disso. Então aqui e agora, diante do mar e do céu, eu te peço, Mary Casper, me dê a honra de ficar ao meu lado diante do nosso povo e de Deus por todos os dias que nos forem dados. Eu, Charles de Maure, Chevalier de Monper, te pergunto... você aceita se casar comigo?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Eu sonhei com isso, né, mas de verdade... Eu... você já sabe minha resposta, Charles – ai, merda!";
				link.l1 = "Ha-ha! Deixa pra lá, é só vinho, e eu nunca gostei mesmo dessa camisa.";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, é claro que sim! Sim, sim, mil vezes sim!!! Você... este lugar... nada poderia me deixar mais feliz!!! Ai meu Deus, sinto que minhas bochechas vão rachar de tanto sorrir, né?!";
				link.l1 = "Você me faz feliz, Mary. Eu brindo a você, meu Sol ardente do Caribe!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Bebo à sua saúde, meu capitão e futuro marido, né? Você é a melhor coisa que já me aconteceu!";
			link.l1 = "Mas isso é só o começo — pra nós! E pro nosso futuro juntos! Tem tanta coisa esperando a gente!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Bebo à sua saúde, meu capitão e futuro marido, né? Você é a melhor coisa que já me aconteceu!";
			link.l1 = "Mas isso é só o começo – pra nós! E pro nosso futuro juntos! Ainda temos tanta coisa pela frente!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, fala com o Abade Benoit pra gente continuar, né? Mas eu não vou usar vestido. Espero que você não se ofenda.";
			link.l1 = "Mary, I love you in any outfit and ... well, you know. You can wear anything you like; anyone who has a problem with that can speak to me! But, I do want to consult you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Sabe, a maioria das pessoas que realmente ficaria feliz pela nossa felicidade nem vai poder chegar perto dessa ilha, né, quanto mais da igreja. Então... vamos casar aqui com todos esses bons cidadãos, como manda o figurino, e depois a gente navega até Isla Tesoro pra comemorar de verdade, com amigos de verdade! O que você acha?";
				link.l1 = "Ótima ideia! Vamos nessa. Vou falar com o Abade Benoit. Precisamos decidir quem vai, mandar os convites... tanta coisa pra fazer!";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Sabe, eu não tenho muitos amigos além do pessoal da tripulação. Então, chama quem você gostar deles, que eu vou ficar feliz, né?";
				link.l1 = "Como você quiser, meu bem. Vou falar com o Abade Benoit e organizar tudo. Você merece uma cerimônia magnífica.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Não se preocupe com os convidados, eu cuido disso, né? Vou escrever para nossos amigos e organizar tudo. Mas antes, me diz: quem você quer no nosso casamento?";
			link.l1 = "Meu ideal é você, eu e nossos amigos mais próximos. Depois de todas essas caras oficiais aqui na Martinica, vamos querer um pouco de sinceridade.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Vamos fazer deste um dia inesquecível. Chame todo mundo! Ninguém vai ficar de fora!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Olha, uma cerimônia a bordo com um capelão no convés ao pôr do sol, no mar aberto, já seria o suficiente pra mim, né? Mas, se é isso que você quer, vamos comemorar! Charles... Eu vou chorar. Me abraça, tá bom...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Tá bom, eu tô calma. Desculpa, é que tudo isso é novidade pra mim. Mas Charles, eu quero fazer parte da organização. A gente também precisa organizar uma festa pros rapazes, né, mas acho que a tripulação inteira não vai caber na igreja. Vou falar com a taverna, mas vamos precisar de bebida e dinheiro – você sabe como marinheiro gosta de festa.";
			link.l1 = "Tá bom, é isso que vamos fazer. O que eu preciso preparar?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Acho que, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos vão ser suficientes, né. "+sti(pchar.questTemp.LongHappy.MarryRum)+" barris de rum - não tem nada pior do que ficar sem bebida! Assim que juntar tudo, venha para a taverna. O resto eu resolvo.";
			link.l1 = "Tá bom, querido, te vejo lá.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Entendi. Mas também vamos ter que passar em Sharptown e preparar as coisas por lá. Acho que cinquenta barris de rum e umas duas dúzias de barris de vinho vão dar conta do recado, né? Mas, só por precaução, vou precisar de trezentos mil pesos.";
			link.l1 = "É bastante coisa, mas a ocasião merece, né? Eu vou dar um jeito, pode deixar. Agora, vou visitar o abade e depois passar em Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Ótimo, vamos juntar todo mundo, né? Mas a gente vai ter que passar em Sharptown e preparar tudo – vamos precisar de bebida pra encher um galeão! Acho que cem barris de rum e cinquenta de vinho vão dar conta. Mas, só pra garantir, vou separar quinhentos mil pesos. Não adianta nada se a festa acabar por falta de bebida, né?";
			link.l1 = "Sim, nossos amigos não podem morrer de sede – eu vou providenciar tudo, não se preocupe! Agora, vou visitar o abade e depois passar em Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Está tudo pronto, Charles. Vou providenciar para descarregarem a bebida, depois passo na taverna local, encontro o barão e entrego os convites. Fica aqui esperando, né?";
			link.l1 = "Você está no comando, querido! Eu vou só dar uma volta por aí. Nunca imaginei que expedições pela selva do Caribe espanhol seriam mais fáceis do que preparar um casamento!";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Terminamos aqui, Charles, né? Já resolvi tudo. Pode acreditar – vai ser maravilhoso! Só tem uma coisa... a taverna local pegou fogo durante uma festa semana passada. Mas já está quase reconstruída, maior e melhor do que antes! Todo mundo vai caber lá.";
			link.l1 = "Eu realmente espero que a gente não acabe queimando tudo de novo. Eu gostava muito do Velho Pica-pau! Enfim, ainda temos muito o que fazer. É hora de zarpar. Mary... você é incrível, sabia disso, né?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Então... vamos lá? Os convidados já chegaram, a igreja está pronta. Eu sei que somos mais próximos do que a maioria dos casais, e isso aqui são só algumas palavras bonitas num salão elegante, mas vou te contar – nem naquela cidade antiga dos índios eu fiquei tão nervosa, né?";
			link.l1 = "I'm sure it's absolutely normal, my love; I'm nervous too. I think Abbot Benoit is waiting, I'll go to him and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Tá bom, vou dar uma volta pela cidade, preciso esfriar a cabeça, né! Charles... você entende que não tem mais volta?";
			link.l1 = "Mary, querida, pra mim, não teve mais volta desde o momento em que nos conhecemos. Esperei por esse dia com todo o meu coração. Não se preocupe, vai dar tudo certo.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Eu, Charles Henry de Maure, Chevalier de Monper, te recebo, Mary Casper, como minha esposa, para ter e cuidar, de hoje em diante, na alegria e na tristeza, na riqueza e na pobreza, na saúde e na doença, até que a morte nos separe. Segundo a Santa Lei de Deus, na presença do nosso Senhor, faço este voto.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Eu, Mary Casper, te recebo, Charles de Maure, como meu marido, para ter e cuidar, de hoje em diante, na alegria e na tristeza, na riqueza e na pobreza, na saúde e na doença, até que a morte nos separe. Segundo a Santa Lei de Deus, na presença do nosso Senhor, faço este voto.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amém.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Isto é inacreditável, né? Eu... eu estou chorando, desculpa Charles, eu vou... meu nariz ficou vermelho, não ficou?";
			link.l1 = "Mary de Maure, minha esposa, você está tão linda hoje quanto em qualquer outro dia!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Obrigada, Charles, obrigada... Foi tudo tão solene e maravilhoso! Esse é o melhor dia da minha vida, né!!! Olha só como todo mundo tá feliz! Mas agora você precisa ir lá conversar com nossos convidados e receber os parabéns deles! Quando terminar, volta aqui – vamos dar uma olhada nos rapazes na taverna.";
			else dialog.text = "Obrigada, Charles, obrigada... Foi tudo tão solene e maravilhoso! Esse é o melhor dia da minha vida, né!!! Olha só como todo mundo tá feliz! Mas agora você precisa ir lá conversar com nossos convidados e receber os parabéns! Quando terminar, volta aqui – estão esperando a gente em Sharptown.";
			link.l1 = "Vou fazer isso agora mesmo, meu bem. Um beijo e já estou indo!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, meu amor, você já falou com nossos convidados?";
			link.l1 = "Ainda não, querida, eu volto já, tá?";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Sim, nunca recebi tantos 'parabéns' de uma vez só. E sabe de uma coisa? A maioria foi de coração!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Sim, sim! Tem sido igualzinho pra mim! Claro, algumas pessoas ficam claramente surpresas com a minha roupa, né? E eu tô tão animada que metade do que me disseram nem entrou na minha cabeça. Charles, o pessoal da taverna tá esperando a gente – a gente devia ir até eles. Eles vão adorar parabenizar o capitão deles, né?";
				link.l1 = "Vamos agora mesmo. Mas... eu queria terminar este dia num lugar mais romântico do que um quarto na taverna. Espero que você não se importe, minha esposa, de passar esta noite na nossa cabine? Ainda mais agora que não tem vigia no navio...";
			}
			else
			{
				dialog.text = "Sim, sim! Tem sido igual pra mim! Claro, algumas pessoas claramente se surpreendem com a minha roupa, né? E eu tô tão animada que metade do que me dizem passa direto por mim. Mas Charles, estão esperando a gente em Sharptown. Quando a gente parte?";
				link.l1 = "Agora mesmo. Não podemos deixar nossos convidados secarem nosso estoque de bebidas! Espero que não se importe de passar esta noite na nossa cabine, minha esposa?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Eu não me importaria de passar esse tempo numa cabana cheia de mosquitos numa ilha deserta, desde que eu tenha você.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Eu sinto o mesmo. Vamos, antes que os rapazes bebam todo o rum e toquem fogo na taverna.";
			else link.l1 = "Eu também te amo. Então... vamos zarpar!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ah, meu querido, estou tão feliz! Hoje é um dia maravilhoso...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Arranca a cabeça imunda dele, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Eu estou bem, né! E o Nathaniel, ele está vivo?";
			link.l1 = "Tanto sangue... Dannie, ele está respirando? Eu vejo ele respirando!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Mais rápido, querido, não perca tempo!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Vencemos, né! Desculpa o atraso. Ficamos presos lá em cima com uma dúzia desses desgraçados. Tive que me virar.";
			link.l1 = "Está tudo bem, eu cuidei das coisas aqui. Fico feliz por finalmente ter encerrado essa história com o Jacques... No fim, ele teve o que merecia.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Então vamos voltar pra Sharptown, né? A gente devia ver como o Nathaniel tá. Aquele maluco arriscou a vida por nós!";
			link.l1 = "Você tem razão, meu amor. Vai, estou logo atrás de você.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Aliás, meu bem, encontramos o Marcus! Ele estava no porão de carga, amarrado e desacordado.";
			link.l1 = "Vivo?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Bloody, but he'll heal. You can't break our baron, all right; barely awake and already craving a scrap!.";
			link.l1 = "Velho Marcus! Bom, vamos para a praia.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Desculpa, Charles, né, eu... eu fui dar uma volta. Vi que você tinha voltado, ouvi que todo mundo estava vivo e tinha vencido, mas eu... o que há de errado comigo, né?!";
				link.l1 = "Vai ficar tudo bem, meu amor, vai ficar tudo bem. Eu também estou triste. Mas vencemos, e Jacques Barbazon pagou pelos crimes dele.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Eu me sinto péssima pelo Gino, pelo Charles, né! Quando eu soube, não consegui acreditar!";
					link.l1 = "Eu também não consigo acreditar... Nunca imaginei que o dia terminaria assim.";
				}
				else
				{
					dialog.text = "Vencemos de novo, né? Meu marido é um furacão em cima desses barões metidos da Irmandade da Costa! Amigos vivos, inimigos mortos – é assim que tem que ser, né?";
					link.l1 = "Conseguimos, meu amor. Conseguimos.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Você mal consegue ficar de pé, né? Vamos lá, a Dannie achou uma casa nos arredores pra gente, não quero voltar pro navio agora. Vamos sentar e beber pelos nossos amigos que se foram – tudo isso é demais pra uma cabeça sóbria aguentar, né.";
			link.l1 = "Sim, Mary, vamos.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Eu me sinto péssima pelo Gino, pelo Charles, né! Quando eu soube, não consegui acreditar!";
				link.l1 = "Eu também não consigo acreditar... Nunca imaginei que o dia fosse terminar assim.";
			}
			else
			{
				dialog.text = "Desculpa o atraso, meu bem. Fui dar uma volta, aí te vi e corri o mais rápido que pude! A Danielle me parou quando o Gino disse que o perigo tinha passado. Que bom que você está bem!";
				link.l1 = "Eu também, meu bem. E nós vencemos. Barbazon está morto, e os barões estão reunindo o que sobrou de suas tripulações. A batalha acabou.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, você mal consegue ficar de pé! E ninguém consegue encontrar o Tichingitu.";
			link.l1 = "Jan gave me a tip... Let's take a walk to Sabo-Matila Cove; a few people saw him heading in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Olha só, aí está o nosso índio estoico, né? Vamos, o Dannie achou uma casa pra gente aqui nos arredores – você está acabado, Charles.";
			link.l1 = "Aí está ... me sequestra, minha bela. E que tudo pareça um pesadelo ruim quando amanhecer.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Don't get me wrong, husband; the church was luxurious, but here the atmosphere is so much more soulful, all right. Well... that's all, Charles. All our troubles are behind us. We can relax.";
			link.l1 = "Bem, não exatamente 'tudo', minha esposa – nossa vida continua juntos! Difícil dizer o que o futuro nos reserva. Então, vamos lá, tomar um drink com a nossa turma, e depois – você lembra: a cabine, o vinho, e nós dois...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Meu marido... essa palavra soa tão doce, né? Agora você é meu, pra sempre.";
			link.l1 = "Já sou sua faz tempo, e agora vou ser pra sempre, meu amor...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Estou tão feliz, Charles! E agora, tudo o que a gente fizer, vamos fazer juntos, né?";
			link.l1 = "Claro, meu bem! Lado a lado, juntos para sempre!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Receio que essa doença esteja afetando suas meninas, Rodrigo. Mantenha elas ocupadas com tricô ou algo assim!";
			link.l1 = "Essa conversa não vai dar em nada. Combinamos que vamos à igreja amanhã — pra rezar, claro.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Eu tenho tanto orgulho de você, meu amor!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Charles...";
			link.l1 = "O que você está pensando, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(ri) O fato é que eu e o Alan, a gente queria fazer na ilha o mesmo que você fez aqui";
			link.l1 = "Você é... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Ele era um sonhador e tanto – vocês dois teriam sido grandes amigos se ele tivesse sobrevivido.";
			link.l1 = "Nossos gostos certamente coincidem em pelo menos uma coisa...";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "O quê? Ha-ha-ha! Ah, cala a boca, Charles!\nDe qualquer jeito, isso é incrível... Nós demos tanta alegria pra esse povo!";
			link.l1 = "We gave them a chance; the rest, they've done on their own. So... what are you thinking?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Me procura depois e você vai descobrir...";
			link.l1 = "Ah, eu vou sim!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Eu gosto de lugares escuros e apertados. Me fazem sentir calma. Finalmente, posso organizar meus pensamentos\nÉ como se todas as minhas preocupações... simplesmente sumissem! Eu senti falta dessa sensação...";
			link.l1 = "Você precisa ver um médico.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "É como se você estivesse de volta ao Ceres.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "... Too bad I'm not alone. In silence, in darkness, in solitude, aye; that would be perfect.";
			link.l1 = "Continua sonhando, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Uma vez um caranguejo entrou na minha cama – eu cortei ele e comi, né?";
			link.l1 = "Continua sonhando, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Desgraçado mascarado! Ai! Me ajuda, meu bem – preciso quebrar essas grades!";
			link.l1 = "Quieto! Estou tentando descobrir o que fazer!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Querido, esses desgraçados mascarados estão por toda parte! Eles arrombaram o casco e estão rastejando por ele feito caranguejos! Temos que derrubar todos eles, né?";
			link.l1 = "Mary, fica aqui, assuma o comando! Afasta o navio da batalha – não vamos aguentar outro abordo, não!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "E pra onde você vai? Não vou deixar você ir embora, não!";
			link.l1 = "Eu preciso ajudar o Hercule e nossa tripulação! Confia em mim, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Sim, sim, querido!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vitória! Vem cá, meu bem! Quero você só pra mim por uma ou duas horas.";
			link.l1 = "Ah...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Vamos!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Ei, Hércules! Que bom te ver, barba grisalha!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary! Mary, espera! Preciso do seu relatório!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Hã? Bem, nós vencemos, né! Aquele maldito navio fugiu. Eu parti o crânio de um desgraçado ao meio!\nUfa, esses botões malditos!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Ai meu Deus, não olha pra mim, querido! Eu vou... ufa!";
			link.l1 = "Aguenta firme, garota. Eu tô aqui!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Preciso falar com você, né? Sério!";
				Link.l1 = "O que aconteceu, Mary? Tem algum problema?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Estou ouvindo, meu querido capitão!","Sim, "+pchar.name+", Tô ouvindo!","Tem algum trabalho pra mim, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, eu vou visitar a antiga cidade indígena Tayasal. Não vou mentir pra você: essa viagem é muito perigosa e, além disso, envolve usar aquele ídolo de que te falei. Você... vem comigo?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, me faça um relatório completo.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que estivermos atracados.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, preciso do seu conselho.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, tenho uma tarefa pra você...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Querido, eu te quero agora. Você está bem com isso?","Mary, que tal a gente... ficar juntos um tempo? Só nós dois.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, vamos alugar um quarto e ficar juntos, né?","Amor, eu quero ficar a sós com você... que tal alugarmos um quarto e esquecermos do mundo por algumas horas?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Não é nada, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, ela é uma beleza, né? Consertamos aquele buraco abaixo da linha d'água e secamos as velas. O quê... O que você esperava? Não me olha assim, nunca estudei pra ser intendente.";
			Link.l1 = "Desculpa, Mary, eu realmente não pensei direito nisso.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, eu tô bem! Já peguei meu casaco e minha lâmina. Mas obrigada por perguntar, é muita gentileza sua, né?";
			link.l1 = "Mas eu nem... Ah, deixa pra lá, querido, tá tudo certo.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Vem comigo e não fica pra trás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, troque a munição das armas de fogo.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolhendo o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Já vou, meu amor!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Agora mesmo, meu amor!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
