// Глэдис МакАртур - приемная мать Элен
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
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, Capitão! Sabe, contei tudo para a Helen. Você não imagina o peso que saiu da minha cabeça!";
				link.l1 = "Você fez tudo certo, senhorita McArthur. A garota precisa saber a verdade. E estou aqui por causa dela.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Saudações, "+pchar.name+"! Que bom te ver! Quer um pouco de rum?";
				link.l1 = "Obrigado, senhorita McArthur, mas estou ocupado demais no momento.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "O que deseja, senhor?";
			link.l1 = "Você é a Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Sou eu. Não me lembro de você, rapaz. Então, quer me explicar o que deseja de mim?";
			link.l1 = "Estou interessado na história do desaparecimento de sua filha, senhorita McArthur. O que a fez pensar que ela sumiu? Ouvi dizer que Helen tinha uma tripulação muito habilidosa...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, I am absolutely certain! Look, my late husband's death anniversary was five days ago. Helen loved her father and she would never miss this date. She had only left for a few days to receive a shipment of redwood from the friendly Miskito people.\nThe Indians respect and fear our patron Jan Svenson; they would never harm her. Señor Svenson has already spoken to them. The wood was loaded on the same day. No one has seen Helen since.";
			link.l1 = "Talvez os piratas tenham atacado ela?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Que bobagem! Você já deve saber que o senhor Svenson é um dos cinco barões piratas e membro do Conselho dos Irmãos da Costa. Nenhum pirata pode caçar aqui sem a permissão dele. Mas pode ser algum novato...";
			link.l1 = "E os espanhóis? Será que ela pode ter encontrado uma patrulha espanhola?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Não entendo muito de política, mas dizem que as minas de ouro e prata daqui já estão completamente esgotadas, não restou muito tesouro pelo qual valha a pena arriscar a vida de nobres hidalgos. Por isso, eles são visitantes raros por aqui. Além disso, os índios são hostis a eles.\nUm encontro aleatório com uma patrulha espanhola não teria terminado mal para Helen, ela não tinha feito nada ilegal do ponto de vista deles. O 'Rainbow' estava sob bandeira holandesa e todos os documentos de Helen estavam em ordem, inclusive a licença de comércio.";
			link.l1 = "Aconteceu algo incomum antes da última viagem dela? Talvez algum evento estranho que você possa ter deixado passar?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, não! Graças a Deus, levamos uma vida tranquila aqui. Mas, algumas semanas atrás, a Helen recebeu uma carta de mais um pretendente indesejado, implorando por um encontro. Ela é uma moça bonita, mas não é rica.\nPor isso tem muitos admiradores, embora não goste de nenhum deles e não queira se casar. Já enganou muita gente desse jeito. Tão leviana, igualzinha à mãe dela!";
			link.l1 = "Você não parece ser esse tipo de mulher, senhorita McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "O quê? Ah, tanto faz, estou de coração partido. O que eu estava dizendo? Ah, sim, a carta. Enfim, essa carta foi escrita pelo Jimmy Higgins. Ele é um dos homens do Jackman e mora em Maroon Town. Ele visita nossa cidade com bastante frequência. Jackman também é um barão pirata, mas o senhor Svenson não gosta dele, não sei por quê.";
			link.l1 = "E a Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Ah, ela estava rindo alto. Tinha recebido uma proposta do capitão de uma corveta inglesa no dia anterior, e recusou até ele. E agora esse contramestre qualquer de uma velha canoa pirata... Nem pensar, a filha de Sean McArthur exige um marido mais à altura!";
			link.l1 = "E qual era o nome daquele capitão inglês?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Ah, como eu vou saber? Cavalheiros de verdade quase nunca aparecem por aqui. Desculpe, não quis te ofender. Pergunte ao Higgins. Ele deve lembrar o nome. O Jimmy tentou desafiar aquele capitão para um duelo por causa da Helen. Os amigos dele mal conseguiram impedir. Mas os dois foram embora de Blueweld alguns dias antes da Helen zarpar.";
			link.l1 = "Bem, obrigado por me contar sua história. Vou tentar encontrar quem você ama. Se eu descobrir algo, aviso você ou o senhor Svenson. Espero encontrar sua filha viva e inteira.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Você vai procurá-la? Que Deus esteja com você, que Ele te guie e fortaleça sua mão! Estarei rezando por você! Diga-me seu nome, homem honrado?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Espero voltar em breve com boas notícias, senhorita McArthur. Até logo!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Você tem alguma novidade sobre minha pobre filha, "+pchar.name+"?";
			link.l1 = "Me desculpe, senhorita McArthur, ainda não tenho novidades para lhe contar, mas não desanime. Vou continuar procurando. A ausência de más notícias já é uma boa notícia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Você chegou tarde demais, capitão. O corpo da minha pobre filha foi encontrado nas praias de Antígua. Meu Deus, como a torturaram antes de morrer! Eu falhei em proteger minha linda menina...";
			link.l1 = "Me desculpe. Não havia nada que eu pudesse fazer...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, rapaz, por favor, me deixe sozinho com minha dor...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Eu nem sei como te agradecer, capitão, por salvar minha filha. Ela me contou tudo e admiro sua coragem e honra. Aqui, aceite estes dobrões de ouro. Não é muito, mas ofereço de coração. E nem pense em recusar!";
			link.l1 = "Tudo bem, Gladys, eu não vou. Mas eu não salvei sua filha por dinheiro, e espero que você saiba disso.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Fique com esse dinheiro, Gladys. Você precisa mais dele do que eu.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Fico feliz por ter conseguido retribuir de alguma forma o seu gesto honrado. As portas da minha casa estarão sempre abertas para você. Helen e eu ficaremos felizes em recebê-lo a qualquer momento.";
			link.l1 = "Obrigada, senhorita McArthur. Vou visitar você e a Helen quando surgir uma oportunidade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, por favor... Eu só queria retribuir seu gesto nobre. Saiba que as portas da minha casa estão sempre abertas para você. Helen e eu ficaremos felizes em recebê-lo a qualquer momento.";
			link.l1 = "Obrigado, senhorita McArthur. Vou visitar você e a Helen quando surgir uma oportunidade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Capitão, você é sempre bem-vindo em nossa casa! Veio ver a Helen? Receio que ela tenha se trancado no quarto – deve estar exausta depois dos últimos dias. Não se preocupe, isso acontece com ela às vezes.";
				link.l1 = "Sério? Tem certeza de que ela está bem?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure! Sempre fico feliz em receber o salvador da minha filha em minha casa. Veio ver a Helen? Ela está no quarto, lá em cima. Depois da perda do 'Arco-Íris' e daquele resgate incrível, ela tem evitado sair. Nunca a vi tão confusa assim...";
			link.l1 = "Obrigada, senhorita McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure! Sempre fico feliz em receber o salvador da minha filha em minha casa. Veio ver a Helen?";
			link.l1 = "Não. Quero lhe fazer algumas perguntas e realmente espero que seja sincero comigo. A segurança da Helen depende disso. Este anel lhe é familiar?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Meu Deus! Este é... o anel do pai dela!";
			link.l1 = "Do senhor McArthur?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Não. Helen é nossa enteada, mas ela não sabe disso. Os pais dela morreram, então decidi criá-la como minha própria filha. Sean a adotou, mas nem ele sabia que ela não era minha filha.";
			link.l1 = "Então quem são os verdadeiros pais dela?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Eu sei que o pai dela era um pirata chamado 'Carniceiro' no navio 'Neptune'. Só o vi duas vezes. E a mãe dela era uma mulher jovem e linda, ruiva, vestida com roupas de homem. É basicamente tudo o que posso te contar sobre ela, além de que foi uma péssima mãe.\nEu jamais teria deixado um bebê assim nas mãos de estranhos. Os dois morreram tragicamente. E o mensageiro prometido apareceu vinte anos depois e acabou sendo você. Foi o Carniceiro que te mandou? Ele está vivo?";
			link.l1 = "Calma, senhorita Gladys! Não há motivo para suspeitar que o Açougueiro voltou, embora você seja a segunda pessoa a pensar nisso. Recentemente encontrei um homem que deveria lhe mostrar este anel...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "Um simples incidente o impediu de fazer isso a tempo, e ele sofreu a vida inteira por ter falhado com a última ordem do capitão. Morreu há pouco tempo e... bem, chega de notícias tristes. Diga-me, Gladys, a mãe da Helen deixou alguma lembrança para a filha? Alguma coisinha, talvez?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Ela me deixou um pedaço estranho de um mapa antigo. Disse brincando que era a herança dela. O que aquele pedaço de papel poderia valer? Acho que não passava de uma piada ruim. Ela estava animada demais, meio fora de si. Mas guardei esse 'presente'.\nVai saber... Se quiser, posso te dar, se prometer me contar a história toda um dia.";
			link.l1 = "Com certeza, senhorita McArthur. Vou levar este papel comigo por um tempo. Preciso falar com o senhor Svenson.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Você nos ajudou mais uma vez, Monsieur de Maure! E eu nem sei como agradecer. Por favor, aceite a pistola do meu marido, pelo menos. Ele sempre teve muito orgulho dela e dizia que era muito rara. Já faz tempo que está só guardada aqui. Que ela lhe seja útil! Pegue, por favor, leve-a!";
			link.l1 = "Obrigada, Gladys. Esta pistola é realmente excelente. Obrigado, e até logo.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Deixe esta pistola para a Helen. Eu já tenho armas suficientes.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Mas por que você continua recusando meus presentes? Isso me deixa chateado...";
			link.l1 = "Acredito que agora posso te fazer feliz. Vou devolver o ouro que o mensageiro deveria entregar a você pela guarda da filha do Capitão Butcher. Claro, esses dobrões não vão pagar todo o seu amor e lealdade, mas eles te pertencem por direito. Você pode fazer com eles o que quiser.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, Capitão! Eu nem sei o que dizer... Jamais imaginei que homens tão... honrados ainda existissem! Vá até minha filha e conte a ela as boas notícias!";
			link.l1 = "Estou a caminho, senhorita McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Você está falando sério? Como assim?";
			link.l1 = "A pedido do senhor Svenson, vou empregar Helen no meu navio como oficial. Ela está correndo grande perigo. Helen vai precisar de proteção confiável enquanto Jan e eu resolvemos essa situação. Espero conseguir garantir essa proteção.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, isso é maravilhoso! Eu jamais teria coragem de te pedir isso. Vai ser a melhor proteção possível para minha menina. Helen vai ficar tão feliz em poder navegar de novo!";
			link.l1 = "Obrigado pelo elogio, senhorita McArthur. Agora preciso ver sua... enteada.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Oh, Deus! Minha filhinha!";
			link.l1 = "Gladys, você não sabe bater antes de entrar?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Oh, me perdoem, jovens! Estou indo embora! Helen, lembre-se do que eu te disse!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Acho que desta vez ela só se esforçou demais. Ela me contou tudo, Capitão! Obrigado por ajudar ela a escolher um novo navio ontem!";
			link.l1 = "Hã? Hm, de nada. Adeus, senhora MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
