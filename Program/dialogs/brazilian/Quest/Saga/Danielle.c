// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
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
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Espere, bonitão! Acho que precisamos conversar.";
			link.l1 = "Eu te conheço? De qualquer forma, sempre tenho algumas horas livres para uma dama.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Não faça planos ainda, Capitão. Arrume uma garota mais jovem e com cara de tola para passar algumas horas a mais. Tenho um serviço para você. Na verdade, sou casada. O nome do meu marido é Nathaniel Hawk.";
			link.l1 = "Olha só! Então você deve ser aquele... ah, Dannie Hawk, o senhor Svenson falou de você.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Em carne e osso. Sim, eu sei que o Diabo da Floresta não tem muita consideração por mim—a recíproca é verdadeira—mas ele precisava te avisar que eu uso meu sabre não só porque é bonito. Então, vamos direto ao ponto, rapaz! Eu venho seguindo Svenson e seus visitantes há um tempo, porque foi ele quem mandou meu marido para a selva morrer. Achei que ele estivesse trabalhando com Jackman, mas agora vejo que não está. Eu estava escondida debaixo da janela durante a conversa de vocês. Não consegui escutar tudo, mas aprendi muita coisa útil. Você está mesmo disposto a encontrar meu marido e dar uma boa surra no Jackman? Ou só estava se gabando?";
			link.l1 = "Ouvir conversa alheia é errado, Madame Hawk. Mas vou perdoar se passar a me tratar com mais respeito. Se estou procurando Hawk ou não, isso diz respeito só a mim. Fale se tiver algo útil a dizer, ou me deixe em paz se não tiver. Não vou pedir duas vezes.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, que temperamento! Vamos lá, Capitão... Sei que meu jeito não te deixa à vontade, isso é certo. Vejo que você não é covarde e sabe o seu valor. Então... vamos nos conhecer melhor. Prometo que vou medir minhas palavras com você. Eu preciso de você, e você precisa de mim. Temos os mesmos objetivos. Me aceite na sua tripulação e não vai se arrepender. Vou te servir com lealdade e confiança até encontrarmos Nathan, te dou minha palavra.";
			link.l1 = "Considere-se aceita... Dannie. Svenson me disse que você já está procurando pelo seu marido. Encontrou algo interessante?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Não é muito, mas é o bastante para acusar Jackman de mentir. O desgraçado disse que os guardas da mina, aqueles que meu Nathan enfrentou, não faziam prisioneiros. E embora seja verdade que ninguém viu o corpo do meu marido na baía, como poderiam, se na verdade ele foi levado como prisioneiro para as minas? Olho de Cobra, um xamã do povo Miskito, o encontrou lá.\nEle também ajudou na fuga dele. Mas onde meu marido está agora continua sendo um mistério. O xamã ficou resmungando algo sobre um tal de Kukulcan que teria devorado ele, mas eu não entendi nada. Além disso, o nativo deixou bem claro que mulheres brancas não passam de motivo de piada para ele. Você devia falar com ele, talvez seja mais aberto com você.";
			link.l1 = "Já é alguma coisa! Essa notícia me anima. Onde posso encontrar esse índio?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Existe uma aldeia no meio da selva. Precisamos desembarcar na Baía de Amatique e seguir para oeste pela mata. Eu te mostro o caminho, caso não consiga achar sozinho. Um ídolo de pedra fica não muito longe da aldeia, e os nativos o veneram como um deus. Já estive lá algumas vezes. Nada demais, na verdade. Só uma pedra simples coberta de musgo.";
			link.l1 = "Interessante. Tudo bem, vamos lá. Vamos falar com o xamã e ver o que fazer depois. Pronto?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Claro! É claro, estou pronta. Tenho viajado desde que saí de Maroon Town. Além disso, não quero ser só mais uma das suas passageiras.";
			link.l1 = "Certo. Vamos para o meu navio.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Sim, capitão!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"Vamos! Vou te mostrar o ídolo de pedra de que o xamã indígena falou. É só um pilar de pedra comum. Vamos!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Ei! Olha só, é só uma estátua de pedra. Nada demais...";
			link.l1 = "Entendo... Mas aquela figura no topo é um tanto sinistra, não acha? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Todas as estátuas indígenas são assustadoras e sinistras. Já vi algo parecido antes. São todas iguais. Enfim, vamos, a aldeia está logo ali!";
			link.l1 = "Vamos!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "E então, o que me diz, "+pchar.name+"? O que aquele ventríloquo pele-vermelha te disse? Conseguiu tirar algo das palavras filosóficas dele?";
			link.l1 = "Você estava escutando escondido de novo, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Bem... um pouco. Sabe, nós mulheres somos assim mesmo. Mas você precisa entender – eu só me preocupo com meu marido. Eu realmente o amo. E daí se eu fico escutando escondida? Enfim, conseguiu descobrir algo útil?";
			link.l1 = "Estou tentando lembrar... não era fácil entender o Snake Eye. Mas parece que o ídolo que vimos ao entrar na aldeia é algum tipo de portal mágico que pode teletransportar pessoas.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Não me olhe assim. Não foi ideia minha e até agora minha cabeça está no lugar. Você me perguntou o que o xamã me disse, então estou te contando.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Por favor, me desculpe. Não vou mais olhar pra você desse jeito. Pode continuar.";
			link.l1 = "Ele disse que, quando Nathan quase foi pego por seus perseguidores, o índio mostrou a ele a estátua como uma forma de salvá-lo, chamando-a de Kukulcan e dizendo que ela engoliu Nathan inteiro e o cuspiu em outro lugar. Simplificando, parece que Nathan foi teleportado pela estátua.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Meu Deus, mas o que... Nathan e eu já nos metemos numa confusão parecida antes, e agora está acontecendo de novo. Já tivemos aventuras de sobra naquele templo indígena cheio de magia Maia...";
			link.l1 = "O que você acabou de dizer?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ah, não é nada, "+pchar.name+", não importa. Só lembranças da minha juventude selvagem. Mas como o Nathan conseguiu fazer aquilo? Digo, se teletransportar? Nós estávamos perto daquele ídolo, eu andava ao redor dele e tocava nele... é só uma pedra!";
			link.l1 = "O Olho de Cobra me contou que o ídolo ganha vida à meia-noite. Só então ele começa a brilhar com uma luz dourada, quando o espírito de Kukulcan entra nele. É nessa hora que você não deve tocá-lo. Ou talvez devesse...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Sinistro... E agora? Vamos esperar até a meia-noite e depois entrar na selva?";
			link.l1 = "Não. O xamã disse que o ídolo não só teleporta as pessoas, mas também consome suas vidas. Pelo que entendi, ele quis dizer que o ídolo drena a saúde delas. Olho de Cobra já passou por essas estátuas três vezes e sempre se curou com alguma poção especial depois de cada teleporte.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Você já pediu essa poção para ele?";
			link.l1 = "Claro. Mas, primeiro, só restam três frascos e, segundo, ele exigiu três amuletos em troca deles.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "E que tal fazermos isso sem a poção? Vamos até a estátua à noite e tocamos nela...";
			link.l1 = "Arriscado demais. Admito que o índio parece meio fora de si e pode estar nos enganando, mas não me parece um psicopata, então acredito que esteja dizendo a verdade. Lembro que você comentou algo sobre magia indígena... Você duvida que exista mesmo?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Sim, eu estava. Não tenho dúvidas, porque vi com meus próprios olhos. Então, acho que você está certo, não faz sentido arriscar.";
			link.l1 = "Exatamente. Por isso vamos encontrar os amuletos primeiro, depois pegar aquela poção maravilhosa com o xamã e ir até a estátua. Eu vou. Sozinho.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Por quê? E o que vai ser de mim?";
			link.l1 = "Você vai ficar no meu navio e comandar tudo enquanto eu estiver fora. Nem pense em discutir, Dannie. Só temos três frascos da poção. Ninguém sabe para onde o portal leva, se o xamã estiver certo e essa coisa realmente funcionar. Talvez eu nem consiga encontrar o Nathan lá.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Você é igualzinho ao Nathan. Todos os homens são iguais... Tá bom, eu concordo.";
			link.l1 = "Que bom que nos entendemos. Vamos, precisamos encontrar os amuletos.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "E daí? Conseguiu as poções?";
			link.l1 = "Sim. Consegui as poções e algumas instruções. Só falta ir até o ídolo à meia-noite e tocá-lo.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Você está com medo?";
			link.l1 = "Sim. Receio que o xamã possa ser simplesmente louco, e nenhuma teletransporte aconteça.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Então, então... Você não está mesmo com medo? Nem um pouquinho?";
			link.l1 = "Dannie, não me pressione... Se você realmente quer saber, então sim, não estou muito confiante, devo confessar.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Eu vou com você.";
			link.l1 = "Vai começar a discutir de novo? Achei que tínhamos um acordo...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Você me entendeu mal. Eu só vou ficar perto de você. Preciso garantir que a estátua funcione... ou que não funcione.";
			link.l1 = "Não tenho objeções. Mas nem pense em me seguir caso a estátua me 'engula'. Está me ouvindo?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Eu prometo. Não vou te seguir... Capitão.";
			link.l1 = "Ótimo. E, Dannie, parece que você não é tão vadia quanto dizem.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Você não me conhece muito bem, "+pchar.name+". Mas vamos deixar esse assunto pra depois.";
			link.l1 = "Vamos... Bem, é melhor nos prepararmos para nossa saída noturna!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Olha, "+pchar.name+"! Juro por tudo que é sagrado, tem uma luz estranha acima da estátua!";
			link.l1 = "Parece que o xamã não estava mentindo. E, se a escuridão não me engana, o topo da estátua já não parece mais tão de pedra assim.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Exatamente... Parece que é feito de ouro puro! Incrível!";
			link.l1 = "Chegou a hora, Dannie. Me deseja sorte e torce por mim. Não chegue perto do ídolo! Fique aqui.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Boa sorte, "+pchar.name+". Vamos torcer para que isso funcione... Você preparou a poção do xamã?";
			link.l1 = "Sim, está aqui comigo. Vai dar tudo certo, Dannie. Bem, lá vou eu! (Aperte T para ativar o ídolo)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Droga! Que tipo de monstro é você, pelo amor de Deus?! Vai pro inferno! Já vi criaturas piores na minha vida, até mesmo o próprio Van der Decken! Agora vou te mostrar o que está pedindo!";
			link.l1 = "(sussurrando) Dannie, espera! Pare com isso! Agora!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(sussurrando) Van der Decken? Ha-ha-ha-ha! Esse verme já me serve! Agora é a sua vez! Curve-se diante de mim, servo fiel! Você vai liderar meu exército de mortos!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Vai embora! Isso não pode estar acontecendo agora!";
			link.l1 = "(sussurrando) Danny, espera! Pare com isso! Agora!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ah?! O que você disse?! Dannie?";
			link.l1 = "(baixinho) Pare com isso agora! Guarde seu sabre! Deixe-me tirar isso!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Droga, seu monstro, parece que... "+pchar.name+"?!";
			link.l1 = "(baixinho) Ah... É mesmo!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Que diabos, você quase me matou de susto! Por pouco não te cortei com meu sabre!";
			link.l1 = "Eu vi isso... e por que você está tão exaltada, hein?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "É isso que eu sou... Ah, meu coração ainda está batendo tão forte no peito...";
			link.l1 = "Dannie, onde estamos agora? Não estamos longe da aldeia Miskito, certo?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Onde mais poderíamos estar! Esta é a estátua que fez você sumir. Aquilo foi espetacular! Vou lembrar disso pelo resto da minha vida.";
			link.l1 = "Entendi, você ficou me esperando aqui esse tempo todo?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Me diga, o que mais eu poderia ter feito? Depois que a estátua te engoliu, só me restava esperar que um dia ela te cuspisse de volta. Além disso, Olho de Cobra disse que esse era o desfecho mais provável.\nEu vivi com os Miskitos e fiquei de olho no ídolo todos os dias. Por que estamos falando dessas bobagens? Me conta! O que aconteceu lá fora? Onde você esteve?";
			link.l1 = "Dannie, essa história é longa demais, já vi tanta coisa... Mas para tirar isso do peito, vou te contar que encontrei o Nathaniel!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Você encontrou o Nathan? Onde ele está? E como ele está?!";
			link.l1 = "Não vou mentir – ele está vivo, mas em um estado péssimo. Ele não tinha a poção dos comanches e o ídolo drenou todas as forças dele. Está deitado numa cabine de um navio velho e caindo aos pedaços, numa ilha estranha chamada Ilha dos Navios Abandonados. Eu também fui teletransportado para lá, então Olho de Cobra estava certo!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Pobre Nathan... Onde fica essa ilha maldita? Como a gente chega lá?! Só pelo ídolo? Vou tentar comprar todas as poções de cura dos Miskitos e ir lá hoje à noite! De um jeito ou de outro, eu vou conseguir...";
			link.l1 = "Pare! Espere! Nathan está doente, mas não corre risco de vida. Um dos rapazes está cuidando dele e o alimentando. Se você passar pelo ídolo, vai acabar com a sua saúde, e a Ilha é realmente perigosa. É arriscado demais!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Então o que você está sugerindo? Que fiquemos de braços cruzados enquanto Nathan sofre, ou talvez até morre?";
			link.l1 = "Pare de ser histérica. Primeiro, eu disse que Nathan está doente, mas não morrendo. Eu falei com ele. Segundo, eu vou navegar até a ilha e você vai comigo.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Você sabe onde fica essa ilha?";
			link.l1 = "Claro que sim! Eu encontrei não só o Nathan lá, mas também o Shark Dodson. Tenho as coordenadas aproximadas da ilha e instruções de navegação para contornar os recifes ao redor. E agora vamos voltar para o meu navio para zarpar rumo a Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Para quê? Por que não podemos zarpar direto para a ilha agora?";
			link.l1 = "Dannie, preciso organizar uma expedição. Há uma grande escassez de mantimentos na Ilha, então vou comprar toda a comida que conseguir. Depois, terei que escolher um navio para navegar até lá, já que nem todas as embarcações conseguem passar pelos recifes da Ilha. E também quero falar com o Svenson antes...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Não vai demorar muito para preparar tudo. A ilha não fica longe daqui, está a noroeste de Havana, a leste do Golfo do México.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Certo... então vamos fazer isso. Você encontrou o Nathan, e isso é o mais importante. Obrigada! Ele está se sentindo mal lá?";
			link.l1 = "Bem... ele está doente. E além disso, está deprimido e desesperado. Sente sua falta. E sim, Nathan pediu para eu te dizer que te ama muito.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(enxugando uma lágrima) Velho tolo! Ele nunca me ouviu... "+pchar.name+", vamos para o seu navio! Quero zarpar o quanto antes!";
			link.l1 = "Claro, Dannie. E eu vou te contar sobre as minhas aventuras. Vamos!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Eu nunca vi um lugar como este antes. A ilha inteira é feita de navios!";
			link.l1 = "Eu te contei sobre isso, Danny...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Mas agora posso ver com meus próprios olhos. Enfim, me diga onde posso encontrar Nathaniel?";
			link.l1 = "Ele está dentro de um dos navios. Mas você vai ter que nadar até lá.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Não me importa. Me diga como chego nesse navio.";
			link.l1 = "Dannie, calm down. You and Nathan have been waiting for a long time, so just have a bit more patience! I will lead you to him; you will never find him on your own. I don't want you to run into the Narwhals or Rivados; you'll start arguing with them and it won't end well.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Certo, vamos então. Eu vou te seguir.";
			link.l1 = "Não se esqueça que vamos ter que nadar bastante.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Está tudo bem, eu posso lidar com isso.";
			link.l1 = "Fico feliz em ouvir isso... Logo você verá seu marido!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Droga! Meu amor...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Meu Deus, olha só pra você... Por que você fez isso consigo mesmo?!..(chorando) Você nunca me escuta, nunca! Eu te disse pra não entrar naquela selva! Mas você foi mesmo assim! Por quê, Nathan?!";
			link.l1 = "Dannie... Me desculpe. Eu não tive escolha, você sabe disso...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Eu sei disso! Ai, meu Deus, querida... o que aconteceu com você! (chorando) Está tudo bem, meu amor, vai ficar tudo bem... Eu estou aqui. Vamos te levar até os Miskitos, até Olho de Cobra. "+sld.name+"  me disse que o xamã seria capaz de te curar. Temos um navio... Vai ficar tudo bem!";
			link.l1 = "Dannie, querida... meu amor! Sua presença só me curou pela metade. Iremos para onde você quiser. Se for para Snake Eye, então vamos até ele.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Junte suas coisas. Ah, como eu sou idiota... Não tem nada pra juntar além de garrafas vazias. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... perdoe Nathan e a mim pela cena.";
			link.l1 = "Dannie! Perdoar você pelo quê? Está tudo bem. Você tem vergonha dos seus sentimentos?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Não, eu não sou... É só que...";
			link.l1 = "Ninguém jamais saberá sobre esta cena. Eu prometo. E ninguém vai saber o que aconteceu com Nathan. Os piratas de Maroon Town verão um Nathaniel Hawk forte e imponente!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Obrigado, "+pchar.name+"! Eu te devo uma... Vou levar meu marido para o navio. Não se preocupe, eu consigo levá-lo até lá, lembro o caminho. Vou colocá-lo na cama e ficar com ele. Vamos zarpar para Olho de Serpente assim que você terminar tudo o que precisa fazer aqui. Eu acredito na capacidade dele de se recuperar, Nathan.";
			link.l1 = "Tudo bem, Dannie. Não vamos ficar aqui por muito tempo mesmo. Tem certeza de que não precisa de ajuda?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Tenho certeza. Vamos chegar ao navio. Não se preocupe, não vou deixar meu marido morrer!";
			link.l1 = "Dannie, você é... maravilhosa!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(enxugando uma lágrima) Vai... só vai, "+pchar.name+"... e por favor, não perca tempo aqui!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "E daí? Ele vai curar meu marido? Me diga, ele vai curar mesmo?";
			link.l1 = "Dannie, Nathan vai ter que ficar aqui. Sozinho. O xamã pediu para não ser incomodado durante os rituais dele. Isso vale pra você também. Ele prometeu curar Nathaniel em até um mês.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Sabe, "+pchar.name+", agora finalmente posso respirar aliviada de novo. Tenho muita fé de que o xamã vai trazer meu marido de volta ao normal. Vou deixar Nathan aqui sem hesitar, porque se Olho de Cobra não conseguir curá-lo, ninguém conseguirá.";
			link.l1 = "Vai ficar tudo bem, Dannie. Olho de Cobra nunca mentiu pra mim. Eu confio nele.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Eu também. Vou ficar com você por um tempo, "+pchar.name+", você está de acordo com isso? Ainda precisamos encontrar aquele desgraçado do Jackman, afinal, ele é o responsável por todos os nossos problemas. Ele organizou a emboscada! Ele tomou o lugar do Nathan em Maroon Town! Ele roubou nossa fragata 'Centurion'!";
			link.l1 = "Concordo. Precisamos lidar com o Jackman. Nenhum de nós estará seguro enquanto Jackman estiver vivo. Mas não vai ser fácil matá-lo.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Tem algum plano, "+pchar.name+"?";
			link.l1 = "Ainda não. Preciso ir até Jan Svenson e pedir um conselho a ele. Vamos fazer uma coisa de cada vez, precisamos promover "+sTemp+" para o chefe da Irmandade da Costa primeiro. Então, precisamos conseguir o voto de cada barão pirata para fazer isso.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Certo, vamos até o Svenson. Vamos ver o que aquele velho rabugento tem a dizer...";
			link.l1 = "Sabe, você não deveria ser tão negativo com o Jan. Na verdade, seria muito melhor se fizesse as pazes com ele... afinal, todos nós temos o mesmo objetivo!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Mas só porque eu respeito você... Tá bom, "+pchar.name+", me desculpe. Não quis ofender o Svenson, só estou nervoso. Não vai acontecer de novo.";
			link.l1 = "Ótimo. Dannie, vai dar tudo certo. Eu te prometo isso!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Confio totalmente em você, "+pchar.name+". Vamos até Svenson?";
			link.l1 = "Vamos, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Sim? Estou ouvindo. Como posso ajudar você?";
			link.l1 = "Você faz ideia de onde o Jackman pode estar se escondendo? Você conhece esse desgraçado melhor do que eu. Talvez ele tenha algum lugar, uma base...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Mal posso dizer! O Jacob sempre foi muito reservado. Nunca ouvi falar de um esconderijo dele. Acho melhor tentarmos pensar com lógica... Vamos reler a carta que você recebeu do Knive. Talvez encontremos alguma pista ali.";
			link.l1 = "Vamos tentar...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Bem... fala sobre Isla Tesoro e um testamento... Isso te soa familiar?";
			link.l1 = "Jan e eu achamos que Blaze Sharp foi morto pelo Jackman na Isla Tesoro e o Tubarão levou a culpa. E um testamento... uma desgraçada... só pode ser sobre a Helen... Droga, como não percebi isso antes! Esse canalha deve estar navegando perto da Isla Tesoro!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Então não vamos perder tempo, "+pchar.name+"?";
			link.l1 = "Sim. Vamos para Isla Tesoro. O velho 'Marlin' vai nos ajudar nesse ataque.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Aquele desgraçado finalmente morreu... Não acredito - estou de volta ao convés do 'Centurion'! Conheço cada prego aqui, e parece que o navio também me reconheceu.";
			link.l1 = "Ela é sua de novo, Dannie. Sua e do Nathaniel.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "You can't even imagine how glad I am. Nathaniel used to talk about our ship often; he'll be glad to know that she is ours once again.";
			link.l1 = "O que você vai fazer agora, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Eu? Vou levar o navio até Sharp Town, contratar pelo menos o mínimo de tripulação e zarpar para Blueweld. Vou pedir ao Jan Svenson para cuidar do 'Centurion', ir até o povo Miskito e esperar lá até que Olho de Cobra tenha curado meu marido.";
			link.l1 = "Você vai mesmo visitar o Jan Svenson? Estou surpreso...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", tudo isso é por sua causa. Estive pensando nas suas palavras: 'todos nós temos o mesmo objetivo'. Lembra? Quero fazer as pazes com Svenson, afinal, ele ajudou a trazer Nathan de volta pra mim. Já passou da hora de parar de discutir.";
			link.l1 = "Palavras sábias, Dannie! Nathaniel vai poder retomar seu lugar em Maroon Town assim que estiver melhor.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Talvez... é que, veja, barão pirata é um cargo eleito. E se os outros decidirem contra?";
			link.l1 = "Deixe o Svenson cuidar disso. Ele consegue convencer qualquer um. A eliminação do Jackman também vai ajudar.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Tudo bem. De qualquer forma, preciso fazer do Svenson meu aliado... "+pchar.name+"! Quero te agradecer por tudo que fez por mim e pelo Nathan. Você salvou meu marido e nos devolveu tudo o que tínhamos perdido. Eu te devo essa.";
			link.l1 = "Vamos lá, Dannie. Somos amigos.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Quero que saiba que sempre ficaremos felizes em vê-lo em Maroon Town. Procure por nós lá quando tiver um tempo. Nathaniel e eu vamos encontrar uma forma de recompensá-lo.";
			link.l1 = "Meu Deus do céu, Dannie! Aceito seu convite com prazer. Vamos sentar, beber e conversar sobre como você e Nathan afundaram o Van der Decken...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Ele contou? Ah, nem me fale disso...";
			link.l1 = "Fine, Dannie. You've got a lot of work ahead of you, and I have to visit our sworn friends - Marcus and Barbazon. I hope you'll let me turn this cabin upside down; I'm sure there are plenty of interesting things in Jackman's chests.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Claro, você acha mesmo que eu iria reclamar?";
			link.l1 = "Legal. Na verdade, é uma pena me despedir de você, Dannie... Te vejo em Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", estou tão feliz em te ver! Estamos de volta a Maroon Town e Nathan está de volta ao seu lugar de direito. Na verdade, todo mundo na vila está contente com isso. Agora tudo vai voltar a ser como era antes! Sou realmente grato pela sua ajuda generosa!\nQuero te dar um presente. Aqui, fique com isto. Este talismã pode facilitar muito uma luta para você. E esta fórmula vai te permitir fazer mais deles por conta própria.";
			link.l1 = "Obrigado, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Isso não é tudo. Também encontrei dois baús cheios de ouro aqui. Eram do Jackman, sem dúvida. Aceite-os como um sinal da minha gratidão. E nem pense em recusar! Eu sei quanto dinheiro você gastou para ajudar a mim e ao Nathan.";
			link.l1 = "Tá bom, tá bom, Dannie, eu aceito!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excelente! "+pchar.name+", quero que saiba que, a partir de agora, você é nosso melhor amigo. Nathan e eu vamos ficar sempre felizes em te ver em Maroon Town! Venha nos visitar mais vezes!";
			link.l1 = "Obrigado! Vou ficar feliz em te ver de novo, então me aguarde!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "O que podemos fazer por você, "+pchar.name+"?";
				link.l1 = "Infelizmente, estou de saída... Adeus, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "E aqui está "+GetFullName(pchar)+". Dá pra ver pela sua cara que você não perdeu tempo!";
					link.l1 = "Tenho que admitir, você sabe se divertir! Obrigado, adorei a noite.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Fico feliz em ver você, "+pchar.name+"! Rum, vinho? Ou uma moça?";
			link.l1 = "Obrigada, Dannie! Eu só queria te ver...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "A garota? Quieto, Danny! Você não quer me encontrar todo picotado e dobrado direitinho na sua porta, quer? Ha-ha. Minha fiel dama, que está bem ali fora, não me perdoaria por essas travessuras.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Uma garota? Isso parece interessante, Danny. Estou sentindo falta de... ouvir o coração de uma mulher... Acho que devo dar uma olhada – você não indicaria qualquer uma, não é?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Sério? Por que está tão pálido? Ha-ha, era só uma brincadeira. Cuide dela, ouviu?";
			link.l1 = "Claro. Ela vale mais pra mim do que todos os tesouros dessas bandas!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "Assim está melhor, ha-ha. Vai lá, sua querida provavelmente já está ficando nervosa.";
			link.l1 = "Adeus, Danny. E obrigado pela sua preocupação, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Garanto que essa jovem beldade sabe mesmo como te proporcionar momentos inesquecíveis, "+pchar.name+". Divirta-se! Ela vai estar te esperando no quarto da taverna.";
			link.l1 = "Obrigado, Danny. Estou a caminho. Não quero perder nem um minuto!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", você é sempre bem-vindo em Maroon Town. As melhores garotas são suas!";
			link.l1 = "Oh, Danny. Juro, este lugar já é minha segunda casa.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "E aqui está o meu capitão. Hoje você é só meu! Venha, estive te esperando por tanto tempo...";
			link.l1 = "Ah, é mesmo? Você não pode esperar mais? Então, vamos direto ao que interessa!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Meu capitão... você realmente sabe como conquistar uma mulher! Nunca vivi nada parecido antes! Quem sabe você não fica mais algumas horinhas?","Já vai embora, meu querido?");
			link.l1 = RandPhraseSimple("Eu sabia que você não ia querer me deixar ir tão fácil assim. Adeus, querido. Grandes coisas me esperam...","Infelizmente, o trabalho me chama. Mas talvez a gente se encontre de novo...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Finalmente, Nathan e eu podemos respirar aliviados de novo! Aquele maldito desgraçado do Jackman está morto! Sinto pela 'Centurion', mas já tinha aceitado a perda dela quando aquele canalha a roubou de mim. Então, não me preocupo tanto.";
			link.l1 = "Mas eu sei. Eu sou um idiota! Todas as provas afundaram no fundo do mar junto com o navio. Elas poderiam ter nos ajudado na votação para o novo chefe da Irmandade da Costa. Agora... está tudo perdido.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Não fique tão chateado! Essas coisas acontecem. Da próxima vez você terá mais sorte... Enfim. Quero te agradecer pelo que fez por mim e pelo Nathan. Você salvou a vida do meu marido. Eu te devo muito.\nQuero que saiba que Maroon Town sempre vai receber você de braços abertos. Visite eu e o Nate quando puder. Vamos encontrar uma forma de te retribuir.";
			link.l1 = "Certo, Dannie. Eu vou te visitar, com certeza. Já vai embora?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Sim, eu vou até os Miskito. Espero que Olho de Cobra já tenha curado o Nathan. Depois voltaremos para Maroon Town.";
			link.l1 = "Heh, já me acostumei tanto com você, é uma pena ter que me despedir... Boa sorte, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Ah, não se faça de boba, querida. Charles, essa apaixonadinha ficava rondando aquele ídolo dia e noite, e não parava de encher o pobre Olho de Cobra de perguntas. E depois ainda correu pra casa e trouxe alguma coisa pra ele, não foi isso?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Ah, obrigada pelo espetáculo, Charles. A cidade inteira de Maroon vai comentar sobre isso, ha-ha!";
			link.l1 = "Não tenho dúvidas de que essa é sua nova prioridade – garantir que isso aconteça.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "Na verdade, está bem no fim da minha lista. Não fique bravo com a garota – é a primeira vez dela. Quando Nathan e eu tivemos nossas aventuras, o arquipélago inteiro também ria da nossa cara.";
			link.l1 = "Vamos mudar de assunto e de clima. Já cansei desse ídolo, vamos embora.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Combinado, vamos nessa, herói.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "O que você quer, Capitão?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, quero te pedir um conselho!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Ouça minhas ordens!";
            Link.l1.go = "stay_follow";
			link.l2 = "Não é nada. Dispensado!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Troque o tipo de munição das suas armas de fogo.";
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
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
