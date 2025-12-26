void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Quem é você, e que diabos está fazendo aqui parado?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Calma, amigo. Só estou de passagem. Não vou me meter no seu... seja lá o que for isso.";
			}
			else
			{
				link.l1 = "É? Esse farol é seu? Da próxima vez, coloque uma placa com seu nome em uma das palmeiras ou construa uma cerca, pelo amor de Deus.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Saia daqui! Se você estragar o negócio assustando um cliente, eu...";
			}
			else
			{
				dialog.text = "Escuta aqui, garoto, não faz a gente te chamar lá fora pra ver se sua lâmina é tão afiada quanto sua língua. Cai fora e...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Então, Frankie, qual é?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Não... Que me condenem, mas não reconheço nenhuma dessas caras.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "O quê?! Tem certeza?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Você acha que eu sou cego?! Tô te falando, o que...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Que diabos?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Quem atirou?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Você acha que somos idiotas, seu verme? Joguem as armas no chão, todos vocês! E você também!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Calma, oficial. Não fomos nós, não está vendo? Nossas armas estão exatamente onde estavam. E nem pense em pegar a sua!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Você está me dando ordens, seu desgraçado?! Prendam todos eles, agora!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Vai se ferrar! Isso não vai acontecer. Rapazes, às armas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Ei, ei, cuidado! Alguém pode acabar morto se você continuar balançando esse ferro desse jeito.";
			link.l1 = "Ha, quem?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Eu, é claro.";
			link.l1 = "O quê...? Quem diabos é você?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "É exatamente isso que estou tentando fazer. Vamos?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_DlgExit_1");
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Eu sou o Tommy! Tommy Irons. Acho que sim. E você, quem é? Você é uma mulher corajosa, viu, andando por aí desse jeito, hehehe.";
				link.l1 = "Corajosa, de fato. E não tenho medo de calar sua boca, se for preciso. Aqui faz calor, então me visto assim – não é pra te agradar, nem a quem pensa como você. Meu nome é Helen MacArthur. Meus amigos me chamam de Rumba, mas você com certeza não é um deles. E o que foi aquele 'eu acho' aí?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Eu sou o Tommy! Tommy Irons. Acho que sim. E você?";
				link.l1 = ""+GetFullName(pchar)+". E o que exatamente você quer dizer com 'acho'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Isso significa exatamente o que parece. Perdi a memória – apanhei feio numa batalha. Sabe, às vezes a gente perde tudo. Mas eu dei sorte. Só esqueci meu nome. Ainda bem que tenho esse pingente no pescoço escrito 'Thomas'. Mas prefiro Tommy. E Irons. Lutei nos Ironsides pelo Cromwell, lembra disso. Mas 'Ironsides' é muito comprido. Irons é bem melhor.";
			link.l1 = "Eu já entendi qual é o seu problema, Tommy. Então, me conta – o que foi? Você estava mirando em alguém em especial? Acertou o alvo? Ou só estava atirando por diversão? Não me surpreenderia.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Eu acabei com ele, e acabei pra valer! De todos os jeitos. Lembra daquele almofadinha? Ele seguiu meu rastro e trouxe soldados com ele. Um pelotão inteiro, só porque dormi com a esposa dele.";
			link.l1 = "Acertou mesmo, hein. Imagino que ele pegou vocês dois no flagra?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! Você não vai acreditar – não. A vadia confessou depois. Consciência pesada, ou talvez ela não tenha gostado tanto quanto eu, hehe. Quem sabe o que se passa na cabeça das mulheres? Eu não tô nem aí, ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hum, ela é meio esquisita.","Homens... Num momento vocês tentam entender o que se passa na nossa cabeça, no outro dizem que não ligam. Mas você está certo numa coisa – o que ela fez foi estranho. Ela devia simplesmente ter ido embora e esquecido tudo como um pesadelo ruim. É exatamente o que eu faria se fosse comigo.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Exatamente! Dizem que tem algo errado comigo. Sinto pena dos soldados que morreram. Eu sei como é, já fui só um soldado raso também. Não te contei isso?";
			link.l1 = "Sim, você fez. Dos Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Ah, é mesmo? Não lembro se contei ou não. Sabe como vim parar no Novo Mundo? Quer que eu te conte?";
			link.l1 = "Não, e isso não me interessa, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Seria, seria. Eu vou te contar.";
			link.l1 = "Certo, dane-se, atire logo. Digo, vai em frente.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Então não me interrompa! Onde eu estava? Ah, sim, eu estava ferido, entende? Recebi minha dispensa oficial porque estava do lado vencedor. Mas você precisava ver a cara daqueles burocratas! Achavam que eu estava fingindo, fazendo de conta que perdi a memória. Ficavam perguntando sobre a minha família.";
			link.l1 = "Bem, o que você disse para eles?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "O que eu disse para eles? Eu disse que não me lembrava. E não estava mentindo – nunca conheci meus pais. Fui criado pelas ruas, por trabalhadores e criados nos cortiços. Entrei para a Revolução por causa deles. Mas a ingratidão das pessoas é espantosa – se eu tivesse perdido um braço ou uma perna, teriam sido obrigados a dar uma aposentadoria imediata para um herói como eu. E, aliás, quase perdi a cabeça, literalmente!";
			link.l1 = "Então, como você veio parar no Novo Mundo, herói de guerra?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Duvida disso? Lutar pelo povo - o que pode ser mais heroico? Espero que um dia covardes como você descubram o que é liberdade de verdade!";
			link.l1 = "Embora a liberdade seja algo bom, de algum jeito você fez isso soar como uma ameaça. Certo, Tommy, continue.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "É. Recebi minha dispensa depois que a Revolução terminou, e aí percebi que não sabia fazer nada além de atirar e socar gente na cara. E não dá pra voltar pro exército — iam rir de mim, ainda mais depois de eu ter lutado tanto pra conseguir sair. Heh, acho que mesmo se eu tivesse realmente perdido um braço ou uma perna, aqueles burocratas iam achar que eu tava escondendo por aí pra costurar de volta depois que pegasse meus papéis de saída, ha-ha-ha!";
			link.l1 = "Engraçado isso. Mas você ainda não me contou como veio parar aqui.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Ah, como você é chato. Nunca te ensinaram a ter paciência, "+GetSexPhrase("garoto","minha garota")+"? Eu não tinha nada para fazer em casa além de caçar patos e cervos, então fui para o Novo Mundo. Naveguei com piratas por um tempo só pela diversão, e quando cansei da falta de lei, virei mercenário.";
			link.l1 = "Não é uma história muito original.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Talvez você tenha uma ideia melhor? Não está precisando de um guarda-costas, por acaso? Porque você parece... fraco. Fico preocupado que não vá muito longe, hehe. Lembre-se, é a comitiva que faz o rei. E uma companhia ruim pode derrubá-lo.";
			link.l1 = "E que tipo de "+GetSexPhrase("rei","rainha")+" eu estaria com uma comitiva como você? "+GetSexPhrase("Rei","Queen")+" do monte de esterco?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Não, não! Estou te fazendo uma proposta de verdade, e você...";
			link.l1 = "Ainda não recebi nenhuma proposta. Quanto você está pedindo pelos seus serviços, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "150 dobrões adiantados! Só pra eu ter certeza de que você está falando sério e não é um farsante. E depois disso, uma taxa mensal. Acho que podemos fechar um acordo.";
			link.l1 = "E você não...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... acha que tem coragem? Heh, nem vou discutir com você – viu como atirei naquele corno no farol? Primeiro tiro! E nada de pechinchar, se é isso que está pensando. Tem que mostrar que pode pagar por um profissional como eu.";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Sim, eu posso! 150 moedas de ouro. Aqui está.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Você teve sorte com aquele tiro. E agora está tentando se valorizar contando vantagem. Posso muito bem passar sem um profissional como você. É honra demais e dinheiro demais.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Não posso pagar agora, não carrego tanto dinheiro comigo. Fique aqui e não vá a lugar nenhum – vou buscar o ouro no navio e já volto.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(150);
			
			dialog.text = "Você não é tão ruim quanto eu pensava! Mas é bom garantir que eu não fique entediada. Seria um desperdício do meu talento, não acha? Tommy e "+pchar.name+"! Vamos agitar o Caribe!";
			link.l1 = "Aprenda a respeitar a hierarquia, Tommy. E outra coisa, é capitão para você. Entendeu?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Hehe, eu sei, Capitão Chato, "+GetSexPhrase("senhor","senhorita")+".";
			link.l1 = "Ah, já estou começando a me arrepender disso...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_Hire");
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Bem, você é um idiota, jovem "+GetSexPhrase("homem","mulher")+"! E totalmente sem juízo. Sugiro que corrija isso ou não vai durar muito. Principalmente no Arquipélago.";
			link.l1 = "Eu vou me virar sem você, Tommy. Adeus.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Você está falando sério? Um monte de soldados acabou de morrer aqui, gênio! Provavelmente vão mandar outro pelotão logo. Não, eu até poderia trancar a porta do farol e organizar uma defesa, mas será que eu quero? Não mesmo.";
			link.l1 = "E o que você sugere?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Me encontre numa caverna na selva. Vou te dar alguns dias pra conseguir o dinheiro pelos meus serviços – você sabe usar uma lâmina, talvez consiga se virar.";
			link.l1 = "Você está falando sério? Lá você vai ficar encurralado como um rato.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Só se eles vierem atrás de mim especificamente, com um destacamento grande. Então acho que vou ficar bem. Agora preciso ir – eles vão chegar logo. Até mais.";
			link.l1 = "É, eu também preciso ir, só por precaução.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Aí está você! Já estava começando a achar que você não tinha o que é preciso pra ganhar dinheiro. Às vezes penso que gente como você já nasce com esse dom. E quem não tem, acaba morrendo na miséria sem trabalhar um dia sequer como gente decente.";
			link.l1 = "Então tá, Tommy. Se não quer entrar para a minha tripulação, não entre. Vejo que você gosta de se esconder nesse buraco.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Você obviamente nunca se escondeu em buracos durante a temporada de chuvas na Irlanda, "+GetSexPhrase("garoto","minha garota")+"! Mas ir com você é melhor do que me esconder aqui. Agora, sobre aquele ouro...";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Aqui está o seu ouro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Eu ainda não consegui. Achei melhor conferir se você não tinha sumido pra outro lugar.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(150);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Agora sim! O que fazemos agora... Capitão?";
			link.l1 = "Antes de tudo, vamos sair desse lugar úmido, senão vou começar a espirrar.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Ah, você devia experimentar a guerra. Eu quase me sinto em casa em lugares assim.";
			link.l1 = "Entendi, então você recebeu sua dispensa e esqueceu do respeito e da hierarquia, hein, Tommy? Não se preocupe, não vou hesitar em te dar outra lição se for preciso. Agora vamos.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons nunca foge! Ele cumpre a palavra dele. E você, vai cumprir a sua?";
			link.l1 = "Estou trabalhando nisso.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Trouxe o ouro?";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Aqui está seu ouro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Eu ainda não consegui. Achei melhor conferir se você não tinha sumido pra outro lugar.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsJungleUhodit");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Escute, Capitão...";
			link.l1 = "O que foi, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Você teria uma carga extra de munição aí com você? Não só uma bala, mas um cartucho completo, embrulhado em papel.";
			link.l1 = "Isso é mais uma das suas piadas? Eu te dou balas e cartuchos sempre que precisa, o que for necessário. E por que exatamente um cartucho, e não um punhado?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Por que você está levando tão a mal o meu pedido? Não estou pedindo pérolas, só um cartucho. Até esperei o momento certo pra não te atrapalhar nos negócios ou ficar no seu caminho feito um maluco, hehe. Então... tem uma bala aí?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Sim, eu trouxe uma rodada. Aqui está. Só não venha fazer uma brincadeira idiota comigo com essa bala. Entendeu, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Agora não, não tenho. Não é como se eu andasse por aí com uma bala no bolso, pensando se o Tommy vai pedir por ela...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Bem, você tem razão, e percebe as coisas rápido, hehe. Mas receio que é aqui que nossos caminhos se separam, então.";
			link.l1 = "Você está falando sério? Ficou ofendido por causa de uma bala? Vamos, vamos até o navio e pegamos uma lá. Se você precisa tanto assim, eu arranjo uma, dez, o que você quiser.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Não. No fim das contas, você não tem nada de especial. Um bom capitão sempre consegue dar à sua tripulação tudo o que ela precisa. Então, vou embora.";
			link.l1 = "E se estivéssemos no mar, acabasse o rum, e você quisesse mais? Desamarraria o bote e partiria? Ou pularia na água?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha! Eu ri, mas nesse momento triste, nem uma boa piada resolve. Adeus, Capitão Chato.";
			link.l1 = "Então, vá pro inferno, Tommy. Adeus.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Não posso prometer nada, heh-heh. Uma boa piada deixa tudo mais leve. Mas obrigado, de qualquer forma.";
			link.l1 = "Certo, vamos lá, seu brincalhão.";
			link.l1.go = "BM_IronsFirstJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsFirstJungle");
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Ei, Capitão!";
			link.l1 = "Sim, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Tem outro cartucho de papel?";
			link.l1 = "O que aconteceu com o último? E qual era aquela piada do cartucho? Faz duas semanas que estou esperando alguma piada idiota sua, mas nada.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Ah, vai ser uma piada de matar, confia em mim. Você vai adorar, hehe. Só não juntei tudo ainda. E o cartucho?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Aqui está. Espero mesmo gostar da sua próxima pegadinha. E onde você colocou a última rodada? Eu te dou bastante dessas. Ou você guarda munição para briga em um lugar e para piada em outro?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Eu não carrego munição para as suas piadas idiotas, Tommy! Você podia ter pedido um lote inteiro em vez de só um cartucho duas semanas atrás!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Eu fiz! Achei que quem se diz meu capitão sempre cuida do que a tripulação precisa.";
			link.l1 = "Eu não estou fingindo ser nada, Tommy. Faz muito tempo que escolhi ser eu mesmo. Quem se sente à vontade comigo, ótimo. Quem não, tudo bem também.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, você e eu somos parecidos nesse aspecto. Mas eu tenho certos requisitos para o meu capitão. E você já não os atende mais, rapaz. É aqui que nossos caminhos se separam.";
			link.l1 = "Você está falando sério? Só porque eu não tinha uma maldita carga de papel?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Isso está fora de questão. Normalmente, eu aconselho as pessoas a fazerem o que quiserem e a aproveitarem a vida. Mas eu te aconselho a pensar mais no seu povo daqui pra frente. Adeus.";
			link.l1 = "E eu aconselho você a cuidar da sua cabeça – fizeram mais estrago nela do que você imagina. Adeus, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Você vai descobrir. Tudo a seu tempo, hehe.";
			link.l1 = "Ah, estou com um mau pressentimento sobre isso, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsSecondJungle");
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Tenho uma pergunta pra você, Capitão.";
			link.l1 = "O que foi, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Não adivinhou? Saber adivinhar é uma habilidade útil, hehe. Você, eu, a selva... Faz umas duas semanas que tivemos essa conversa. Preciso de outro cartucho de papel.";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Isso está virando tradição, não é? Já faz duas semanas – Tommy pede um cartucho. Aqui está. Quantos mais você vai precisar pra essa sua piada?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Quanto tempo mais, Tommy?! Até quando isso vai durar? Vocês, Ironsides, só recebem uma bala antes de cada batalha?! Eu não sou obrigado a ficar carregando munição o tempo todo por causa das suas manias, sabia disso!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Na verdade, como meu capitão, é seu dever me fornecer tudo o que preciso para a batalha e muito mais.";
			link.l1 = "Você está confuso, Tommy. É seu dever obedecer às ordens do seu capitão. Eu sempre forneço tudo a vocês – remédios, munição, rum. O fato de você não pegar o que precisa na hora certa e depois agir como um mendigo é culpa só sua!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Você é tão esperto – por que ainda não fez nada de relevante por aqui? Eu te digo por quê. Porque você não pensa no futuro e nunca está preparado pra nada. Você não faz ideia do que está fazendo, seu chato. Não vou aceitar alguém assim como meu comandante, então adeus.";
			link.l1 = "E você não usa a cabeça pra nada! Já vai tarde, seu idiota maldito!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Essa aqui serve, hehe.";
			link.l1 = "Então finalmente você se acertou, hein? Mas pra quê?";
			link.l1.go = "BM_IronsThirdJungle_6";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
   				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Eu só estava brincando com você, queria ver se você voltava a ficar rabugento. Hehe. Mas obrigado pelo cartucho.";
			link.l1 = " Suas piadas são estranhas, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Velho Reasley, você disse... Frankie, o Corno, não é? Aquele que você atirou no farol? Então vocês se conhecem faz tempo, né?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "O quê? Ah, droga, deixei escapar. Mas não ligo – nunca fui bom em mentir ou guardar segredos.";
			link.l1 = "Imagino que a segunda bala era para alguém em especial, não era, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Certo, gênio. Olha, eu me conheço e sei o que quero, e não tenho vergonha disso. Por isso não me importo com o que você pensa – vou te contar tudo, por que diabos não.";
			link.l1 = "Então, me conte. Não vai fazer mal saber o que você está aprontando.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Olha, não me interrompa, como você sempre faz. Tinha dois canalhas na companhia comigo – Francis Reasley e Gabriel Callow. Uns verdadeiros ratos! Pior ainda do que aqueles burocratas que não queriam aceitar minha demissão, que, como você sabe, não foi nada fácil de conseguir.";
			link.l1 = "E o que eles fizeram? Principalmente o segundo, o Callow. Você também dormiu com a esposa dele? E ele também mandou soldados atrás de você?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Fica de boca fechada, tá bom? Embora... eu não me importaria, hehe. Mas não. Os realistas nos atacaram naquele dia. Até a cavalaria veio. Eles eram muitos mais. Gabe e Frankie fugiram feito coelhos assustados. Mas eu fiquei com os rapazes. Fui o único que sobreviveu. Esqueci muita coisa da minha infância e juventude, mas isso não.";
			link.l1 = "E você quer vingança só porque eles fugiram? Nem todo mundo luta por um ideal. Todo mundo quer sobreviver. Ou quase todo mundo. Mesmo quem luta pela Revolução pode ter entrado por acaso e se arrependido depois.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, se eu caçasse cada covarde, teria que atirar no mundo inteiro. Covardes, que se danem. Mas eles me traíram. Disseram pra todo mundo que fui eu quem traiu a Revolução e massacrou toda a nossa companhia a mando dos aliados do Rei. Eu menti pra você sobre uma coisa, Capitão.";
			link.l1 = "O que foi? Além do fato de que você mentiu dizendo que o Frankie te persegue só por causa do que você fez com a esposa dele?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Não, não! Eu não menti pra você, só não te contei tudo. Tem uma diferença. O que eu menti foi sobre a demissão. Não houve demissão nenhuma. Teve um tribunal. E o velho Tommy teve sorte — decidiram não enforcar ele, mas mandá-lo pras pedreiras nas colônias do sul. Barbados, pra ser exato.";
			link.l1 = "É, foi sorte mesmo. Quantos anos você trabalhou lá?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Nenhuma. Desde que o tribunal dos homens me condenou por causa daqueles ratos, o tribunal lá de cima resolveu me poupar. Assim que cruzamos para o Arquipélago, sentimos o clima - nosso navio foi abordado por piratas.";
			link.l1 = "Então, em vez das pedreiras e plantações de Barbados, você foi vendido por piratas como escravo? Mas você disse que nunca trabalhou nas pedreiras.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Foi o que eu disse – alguém lá em cima resolveu me salvar. Que resgate foi esse, hehe! Você entendeu certo – os piratas derrotaram aqueles que gostavam de abusar de homens acorrentados e amarrados. Mas ainda assim foi uma luta feroz, tão quente quanto o sol daqui. E nossos salvadores também tiveram algumas baixas. Então eles ofereceram a todos a chance de se juntar a eles.";
			link.l1 = "E você se juntou a eles? Você disse que navegou com piratas.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Com certeza! Foram os melhores anos da minha vida. Jack Mills era um capitão com C maiúsculo – espero que um dia você seja como ele. Naveguei no 'Crane' dele por uns dois anos, até que...";
			link.l1 = "... até você se cansar da vida sem leis, como disse? Por que diz que aqueles foram os melhores anos da sua vida?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "É... até eu ouvir falar que aqueles dois traidores também vieram parar no Arquipélago. Sim, eu sei, te disse que estava cansado dessa vida de pirataria e tudo mais. E já falei que não me importo com o que você pensa. Isso continua sendo verdade, mas eu não te conhecia direito quando nos vimos pela primeira vez. Não sabia como você ia reagir. Por isso falei coisas diferentes.";
			link.l1 = "Você é um mentiroso, Tommy! Mas tudo bem, por que você deixou o 'Crane'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Porque Jack era um verdadeiro líder, ele disse que não faria um desvio por causa de um homem, não esperaria por ele, não buscaria vingança, nem se meteria com oficiais importantes da Marinha Britânica em vez de atacar navios mercantes cheios de riquezas.";
			link.l1 = "Oficiais de destaque? Acho que o Frank era civil.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "É, ele nem sempre foi assim. Sempre foi meio, sabe, suspeito. E quando tentou armar pra alguém, foi expulso em desgraça. Tentou trabalhar num navio mercante, mas trabalho honesto não era com ele. Acabou ficando por aqui.";
			link.l1 = "Mesmo assim, não diria que ele é um oficial respeitável.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Não se esqueça do Gabe. Ele virou tenente lá na terra. E conseguiu sua patente aqui em Port Royal como capitão do navio, o 'Principio'.";
			link.l1 = "Não parece muito inglês.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Bem lembrado! O navio passou de mão em mão feito uma moça de porto, então já viu de tudo. Mas ainda está em boas condições. E o Gabe é um capitão habilidoso, maldito seja.";
			link.l1 = "E o Jack tinha medo de lidar com ele? Ele é mesmo tão bom quanto você diz?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Tá bom, tá bom! Na verdade, ele só não queria perder tempo comigo. Falando no Jack, gostei de umas tradições que vi primeiro com ele – andar na prancha e distribuir marcas negras. Isso me deu uma ideia engraçada na época.";
			link.l1 = "Marcas... pretas? Você quer dizer uma marca negra, certo? E o que foi, Tommy? Acho que ele nem saberia o que fazer se você tivesse dado uma marca negra pra ele. Foi isso que aconteceu? Você queria entregar, e ele te atacou assim que te viu, então você correu pro farol, e ele levou um grupo de soldados com ele, dizendo que você era um pirata?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Prefiro chamar de marca negra. Soa melhor assim. Uma simples marca negra não teria feito ele perceber nada. Mas uma marca negra feita com nosso lenço de seda, que era uma característica marcante da nossa companhia – isso, ele entenderia. Coloquei discretamente no bolso dele. Depois, garanti que ele me visse indo para o farol. O resto, você já sabe.";
			link.l1 = "E os contrabandistas?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Lugar errado, hora errada. Até senti um pouco de pena deles. Mas só um pouco, hehe.";
			link.l1 = "E para o Frankie?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Quem se importa agora? Temos problemas maiores para resolver. Sobra o Gabe. Isso vai ser complicado. Precisamos...";
			link.l1 = "Nós?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Bem, uma coisa é ouvir uma história interessante, outra é criar a sua própria! Então, é o seguinte. Vamos precisar deixar outro sinal negro especial para o Gabe – já preparei um. Depois, seguimos o rastro dele até Portland Cove, onde vamos resolver tudo sem deixar vestígios.";
			link.l1 = "E onde vamos plantar isso?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, era disso que eu falava quando disse que queria que você fosse mais como o Jack, Capitão. Vamos lá, não seja chato, dá pra ver seus olhos brilhando!";
			link.l1 = "Na verdade, eu estava bem interessado na sua história.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "Na casa dele, é claro! Que tipo de pergunta é essa? Ele está instalado em Port Royal. Então você e eu vamos atracar na enseada, assim podemos sair da ilha se algo der errado.";
			link.l1 = "Você sabe onde fica a casa dele?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Não. Mas não é difícil descobrir. Vamos perguntar pros bêbados – eles venderiam a própria mãe por uma ou duas doses. E aí, o que acha do meu plano?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Se ele é o capitão de um navio a caminho da Jamaica, está sempre patrulhando as águas da ilha. Atacar sob bandeira falsa é melhor do que tentar qualquer coisa na cidade.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Não é perfeito, e você está apostando muito na sorte. Mas, no geral, dá pra fazer. Estou com você, Tommy. Você se livrou de um, não vai deixar o outro escapar, vai?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Não vou me envolver na sua vingança nem arriscar minha relação com a Inglaterra por essa aventura, onde tudo depende tanto do acaso, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Você é corajoso, Capitão! Estou começando a gostar de você. Mas o Gabe do velho 'Principio' não é presa fácil – ele é muito mais perigoso do que outros capitães em um navio como aquele.";
			link.l1 = "O que você pensa de mim, um covarde, Tommy? Vamos abordar ele nós mesmos, e você pode ter uma conversa cara a cara com ele. Entregue a marca negra pouco antes de ele ser deposto.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Heh, talvez você não seja um covarde, mas ele é, embora seja esperto. Ele nunca ataca um soldado ou mesmo um pirata com um navio maior. Se vê algo assim no horizonte, se esconde debaixo da proteção do forte.";
			link.l1 = "Hum, e quanto aos navios mercantes?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Sim, isso pode funcionar! Mas, de novo, nada maior que uma barca ou barquentine! Gabe não é só um covarde – ele nunca foi ganancioso a ponto de deixar isso superar sua cautela.";
			link.l1 = "Vamos torcer para dar certo, Tommy. Então, uma barca ou barquentina de quinta classe com bandeira espanhola ou holandesa. Prepare-se para reencontrar seu velho companheiro de guerra!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Eu sabia que podia contar com você! Quem sabe um dia você seja até um capitão melhor que o Jack. E quanto à minha sorte... Me trouxe até aqui, então vou confiar nela de novo. Vamos, então?";
			link.l1 = "É, vamos resolver isso logo. Quanto mais rápido acabar, melhor.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, eu tinha esperanças, mas já esperava por isso – você não tem coragem pra esse tipo de coisa, "+GetSexPhrase("jovem","minha garota")+" . Todo capitão de verdade já passou por situações assim, em que teve que lidar discretamente com ratos. Às vezes, até com os próprios ratos.";
			link.l1 = "Imagino que você espera que eu caia nessa provocação e diga que mudei de ideia, que vou provar que sou um capitão de verdade, né, Tommy? Mas eu entendo seu desejo de vingança. Não vou te obrigar a sair da tripulação como o Jack fez. De quanto tempo você precisa pra isso? Até lá, já vou ter chegado à Jamaica.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, você está amadurecendo. Quase te respeito por não ter caído nessa. Mas não precisa esperar e vir me buscar depois – eu vou resolver isso sozinho. No fim das contas, tudo o que eu queria era alguém disposto a fazer algo por mim como meu capitão. Então, adeus. Cuide da Inglaterra, ha-ha.";
			link.l1 = "Você é mesmo estranho. Mas como quiser. Adeus! E boa sorte com sua vingança, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsThirdJungle_Otkaz");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Ótimo, podemos recuar rapidamente daqui se for preciso. Pegue isto – entregue o bilhete e a marca negra para o Gabe assim que descobrir onde ele mora e quando ele está em casa.";
			link.l1 = "Ah, então agora é você quem manda, Tommy. Mas lembre-se, ainda sou seu capitão. O que pretende fazer enquanto eu estiver na cidade?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, como eu poderia esquecer disso, Capitão Chato? Se o Gabe me vir nas ruas, ele vai ou soar o alarme ou fugir da ilha, aquele covarde desgraçado. Fica tranquilo, vou preparar uma emboscada bem aqui, hehehe.";
			link.l1 = "Uma emboscada, é isso? Tudo bem, Tommy. Vamos dar ao seu velho camarada de guerra uma recepção à altura, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hic! Esse rum está excelente! Hic... Saúde!";
				link.l1 = "Escuta, camarada, o que andam dizendo por aí sobre o Capitão Gabriel Callow?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Velho Gabe?! Só coisas boas! Ora, hic, o que é isso?";
			link.l1 = "Ah, é mesmo? Que bom saber. Olha, temos um problema com um pirata. O Comandante cuida mais dos assuntos em terra, e eu não quero incomodar Sua Senhoria.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Então vá direto falar com o Gabe, estou te dizendo! Não há capitão mais honesto ou corajoso na cidade do que o Gabe. Até o Coronel Doyley tem grande respeito por ele. Ele comanda um navio que já foi do próprio Nicolas Sharp, acredita nisso?";
			link.l1 = " Ainda não estou bêbado o bastante pra acreditar nisso, camarada.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Ah, mas é claro que é você! É o Principio! Reconhece o nome, hein?";
			link.l1 = "Um navio-prêmio espanhol, é isso? Por quê?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Quando foi a última vez que você viu um rosa com seus próprios olhos, hein? Eu sei do que estou falando, eita!";
			link.l1 = "Bem, eu não sei se o design do navio é tão incomum assim.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Mas é sim! Ninguém comandaria uma sucata dessas hoje em dia, com tantos navios novos por aí! Pararam de construir esses modelos nos estaleiros faz quase t-trinta anos! O Nic mesmo navegou nela, tô te dizendo.";
			link.l1 = "Certo, eu vou comprar. Então, ela é o navio. Como é que esse traste ainda não desmoronou?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Bem, ela já não é tão rápida quanto foi nos seus melhores anos – assim como eu depois de mais uma dose, ha-ha-ha! Mas um bom capitão ainda consegue tirar algo dessa velha senhora. O Gabe também tenta não colocá-la na linha de fogo.";
			link.l1 = "Então por que o navio ainda não foi rebatizado? Talvez Navio de Sua Majestade Espancador, sob "+sStr+" antigo regime?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... Trad-trad-tradição, eita! O próprio Nic nunca mudou o nome dela depois de fugir de uma plantação espanhola em Cuba. Ele nunca quis esquecer aquela experiência – e os espanhóis também não! Deixa eu te contar, aquela batalha perto da costa de Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, né? Hã, a última vez que ouvi esse nome foi quando eu era criança. Não achei que alguém ainda conhecesse ou lembrasse dessas pedras abandonadas.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Onde fica isso?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Ou será que foi, ai, Highrock? N-não, com certeza não foi lá... Mas enfim, isso não importa! Nic lutou e venceu naquele navio rosa, uma vitória inacreditável contra a escuna Cuttlefish, enviada atrás dele por Desmond Ray Beltrop, Barão Pirata. Eles derramaram o sangue um do outro por muito tempo, até que Nic derrubou o próprio Desmond.";
			if (startHeroType == 4)
			{
				link.l1 = "Caramba, isso é impressionante! Mas também, não se espera menos do Nicholas. Os Sharps e os Beltrops estão sempre juntos, depois separados – pelo visto, a história realmente se repete de vez em quando.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Impressionante. Então, como foi que Sharp se despediu do navio? Ele vendeu a embarcação no estaleiro?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Não. Depois daquele abordo, ela começou a fazer água, então o Nic a abandonou. Depois, com a maré alta, a pink foi trazida para a praia, bem perto da cidade.";
			link.l1 = "Como se alguém estivesse interessado naquele destroço.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, mas a Marinha ficou interessada! Gente prática. Viram um navio sob a bandeira inglesa, mas com nome espanhol, e ficaram curiosos. Nic morreu alguns anos depois, mas o navio continuou navegando, mudando de dono, sempre de forma sangrenta.";
			link.l1 = "Essa é só mais uma história de navio fantasma, enquanto a capitania do Gabe é bem real. Então, acho que vou procurá-lo. Você sabe onde ele mora?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha! Claro, hic, eu sei! Todo mundo sabe! O velho Gabe mora perto do moinho velho. É só dar a volta na taverna e olhar pra cima... hic!";
			link.l1 = "Quando ele está em casa? Parece que é um homem ocupado.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Isso mesmo, camarada! Ele tem muito o que fazer. Só está em casa à noite, a partir das dez horas. E acorda todo dia às seis em ponto, sozinho. Uma disciplina de ferro!";
			link.l1 = "Muito obrigado! Já tive o bastante dessas histórias de piratas por enquanto.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Você é mesmo... Rumba? Já ouvi falar de você... mas nunca soube que você se voltasse contra os seus!";
				link.l1 = "E eu não fiz isso. Meu problema não é com meu país. É com você, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Você não é um mercador...";
				link.l1 = "Surpresa, Gabe! Disseram que você era cauteloso, até covarde. A ganância nublou seu julgamento, não foi? Nenhum comerciante procuraria um confronto como eu fiz.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Comigo? Qual é o problema? A gente podia conversar direito na minha casa, ou até na sua. Como capitães, e... O que VOCÊ está fazendo aqui?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "De fato. Então, quem é você? Não, dane-se você, na verdade. Quem é aquele...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, é você...?";
			link.l1 = "Ah, sim, Gabe. E eu vim para te punir pelo que você fez comigo naquele dia.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Me punir?! Cuidado com o que diz, Thomas! Se alguém aqui merece punição, esse alguém é você! Você prometeu que traria reforços! E nós esperamos, morrendo sob as balas e espadas da cavalaria do Rei!";
			link.l1 = "Eu corri feito louco pra buscar ajuda! Mas fui alcançado por outra maldita tropa! Os malditos apoiadores do Charles estavam por toda parte! Me encurralaram, quase morri! Ainda bem que acharam que eu tinha morrido. Mas sabe o que eu vi, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "O que foi, Tom? Você está disposto a inventar qualquer história só para esse homem continuar acreditando em você?!";
			link.l1 = "Heh, esse homem não vai me trair de jeito nenhum. Ele não é um rato como certas pessoas.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Ele não tem escolha! Atacar um navio da Marinha Inglesa!";
			link.l1 = "Ah, ele teve escolha desde o começo. E escolheu me ajudar. Você e o Frankie também tiveram escolha. Vocês escolheram fugir para não morrer. E depois voltaram e me encontraram quase morta. E contaram suas mentiras nojentas no tribunal. Vocês sabiam que ninguém ia me ouvir porque eu tinha levado uma pancada na cabeça e perdido a memória!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Ninguém teria te ouvido de qualquer jeito. Você sempre foi um... desastre, Thomas.";
			link.l1 = "Ah, então você não está escondendo o que fez naquele dia. Tenho algo pra você, Gabe. Uma marca negra. Mas de que adianta te dar isso agora que o navio já foi tomado e estamos prestes a abrir suas tripas, hee hee hee hee hee hee...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BM_IronsClone5_function"); // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Bem, o Gabe foi deposto, hehehe. Faz tempo que eu queria dizer isso. Pena que você não pode mais ouvir, camarada. Ou será que pode? Talvez lá do Inferno.";
			link.l1 = "Vamos lá, Tommy. Mesmo que ele não tenha ouvido, ele viu e sabia que isso era exatamente o seu plano e vingança. E não havia nada que ele pudesse fazer a respeito.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, você está certa! Isso mesmo! Obrigado por me ajudar com isso. Sabe, eu achei que você era só uma garota mimada com roupa chamativa que ganhou um navio pra passear. Mas você é uma capitã de verdade! Aposto que até o Jack teria trabalho com você.";
			}
			else
			{
				dialog.text = "Hehe, você tem razão! Isso mesmo! Obrigado por me ajudar com isso. Sabe, acho que você é tão bom capitão quanto o Jack. Ou até melhor!";
			}
			link.l1 = "Ah, agora você está me elogiando. Obrigada. Acho que sim.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "De jeito nenhum. Não é bajulação, não. Como você deve ter notado, eu quase nunca elogio ninguém assim. Então cala a boca e agradeça por eu te considerar tanto assim";
			link.l1 = "Eu não diria que gosto do jeito que você está falando, embora eu fique feliz que, no geral, você me veja como um bom capitão. Mas... a cadeia de comando, Tommy, a cadeia de comando.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ah, vamos lá! Sinto que tudo o que passamos juntos nos aproximou, Ellie. Podemos ser mais do que apenas capitã e oficial. Admita – mesmo que só para você mesma, você sente isso também.";
				link.l1 = "Só nos seus sonhos mais loucos, Tommy. E é Helen, não Ellie. Mas acho que agora você pode me chamar de Rumba.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Ah, qual é, seu chato! Acho que já não somos só capitão e oficial, mas verdadeiros amigos. Você não acha?!";
				link.l1 = "Heh. Talvez. É melhor ser seu amigo do que seu inimigo. E já que etiqueta claramente não é o seu forte, acho que vou ter que me acostumar com isso.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Eu tenho um... presente para você, Capitão.";
			link.l1 = "Opa, olha só isso! Um ponto negro? Você quer que eu seja deposto também, hein, Tommy? Quer ser o capitão no meu lugar? Ha-ha-ha-ha! E eu achando que éramos parceiros.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "É uma MARCA negra, seu idiota. Sabe, estou começando a achar que assim que bordei a caveira e os ossos nesse lenço, ele começou a me trazer sorte. Não sei explicar. Fique com ele. E... se quiser, pode pegar emprestada minha espada fiel e a armadura... o que sobrou dela, ha-ha! Vai ser útil! Você vai longe. E eu quero ver isso acontecer. Não quero que você morra por uma bala perdida.";
			link.l1 = "Valeu, camarada! Vou fazer o meu melhor. E você – só observa e admira, ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Admirar, claro, ha-ha-ha. É. Então, o que você decidiu fazer com este navio? Por um lado, ele já não serve pra muita coisa. Por outro, não existem mais navios como esse. E acho que nunca mais vai existir outro igual.";
			if (startHeroType == 4) 
			{
				link.l1 = "Ainda não decidi... Sabe, Tommy, sinto uma certa ligação com este navio. Não sei explicar. Então, vamos tirar logo esse cadáver fedorento daqui. Se não houver vazamentos no porão, talvez eu fique com essa garota para mim.";
			}
			else
			{
				link.l1 = "Eu não sei, Tommy. Ainda não decidi. Por enquanto, vamos nos livrar do corpo do Gabe. Vai que a gente acaba ficando com o navio.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Bem, você fez um ótimo trabalho com aquele navio antigo, Capitão! E embora eu quisesse acabar com o Gabe com minhas próprias mãos, não vou desafiar o Criador menosprezando essa vitória.";
			link.l1 = "Isso não seria necessário, Tommy. Espero que sua alma esteja em paz agora.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Sinto que tudo o que passamos nos aproximou, Ellie. Podemos ser mais do que apenas capitã e oficial. Admita – mesmo que só para você mesma, você sente isso também.";
				link.l1 = "Nem nos seus sonhos mais loucos, Tommy. E é Helen, não Ellie. Mas suponho que agora pode me chamar de Rumba, se parar com a bajulação.";
			}
			else
			{
				dialog.text = "Eu nunca fui tão feliz na minha vida! Obrigado por me ajudar a passar por isso. Sabe, acho que você é tão bom capitão quanto o Jack. Ou até melhor!";
				link.l1 = "Oh, você me lisonjeia. Obrigada pela comparação também, eu acho.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "De jeito nenhum. Não é bajulação, pode acreditar. Como você já deve ter notado, eu quase nunca elogio ninguém assim. Então cale a boca e fique feliz por eu pensar tão bem de você.";
				link.l1 = "Não posso dizer que gostei do jeito que você falou, mas fico feliz que, no geral, me veja como um bom capitão. Mas... a hierarquia, Tommy, a hierarquia.";
			}
			else
			{
				dialog.text = "De jeito nenhum. Não é bajulação, não. Como você já deve ter percebido, eu quase nunca elogio ninguém assim. Então cale a boca e fique feliz por eu pensar tão bem de você.";
				link.l1 = "Eu não diria que gosto do jeito que você falou, mas fico feliz que, no geral, você me veja como um bom capitão. Mas... a hierarquia, Tommy, a hierarquia.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Ah, qual é, seu chato! Me parece que nós dois já não somos apenas um capitão e seu oficial, mas sim verdadeiros amigos. Você não acha?!";
				link.l1 = "Heh. Talvez. É melhor ser seu amigo do que seu inimigo. E já que etiqueta claramente não é o seu forte, acho que vou ter que me acostumar com isso.";
			}
			else
			{
				dialog.text = "Ah, qual é, seu chato! Me parece que nós dois já não somos só capitão e oficial, mas sim verdadeiros amigos. Não acha?!";
				link.l1 = "Heh. Talvez. É melhor ser seu amigo do que seu inimigo. E já que etiqueta claramente não é o seu forte, acho que vou ter que me acostumar com isso.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Tenho um... presente para você, Capitão.";
			}
			else
			{
				dialog.text = "Tenho um... presente para você, Capitão.";
			}
			link.l1 = "Opa, olha só isso! Uma marca negra? Você quer que eu seja deposto também, é isso, Tommy? Quer ser o capitão no meu lugar? Ha-ha-ha-ha! Eu pensei que éramos parceiros.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "É uma MARCA negra, seu idiota. Sabe, estou começando a achar que assim que bordei a caveira e ossos nesse lenço, ele começou a me trazer sorte. Não sei explicar. Fique com ele. E... se quiser, pode pegar emprestada minha espada fiel e a armadura... o que sobrou dela, ha-ha! Vai ser útil! Você vai longe. E quero ver isso acontecer. Não quero que você morra por uma bala perdida.";
			link.l1 = "Valeu, camarada! Vou fazer o meu melhor. E você – fique de olho e admire, ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			Notification_Reputation(true, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Quem precisa acreditar numa coisa dessas... Me desculpe, senhorita. "+TimeGreeting()+". Como posso te ajudar? Você parece muito preocupado.";
			}
			else
			{
				dialog.text = "O quê? Quem aparece a esta hora da noite? Você parece preocupado, senhor. Em que posso ajudar?";
			}
			link.l1 = "Peço desculpas por interromper seu descanso, Capitão Callow. Meu nome é "+GetFullName(pchar)+", e eu venho em nome de um dos seus antigos companheiros de armas.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Qual camarada? Tive muitos, tanto no Velho Mundo quanto no Novo.";
			link.l1 = "A princípio, eu só pretendia deixar algo em um dos seus baús. Ou talvez sobre a mesa, para que você percebesse mais rápido. Diz respeito a um homem do seu passado. Aqui, dê uma olhada e leia você mesmo.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Uma marca negra? Não me lembro de nenhum pirata entre meus camaradas. Ou será que alguns dos rapazes se meteram nessa vida? Seda preta? Sério mesmo... Ah, Thomas. Me surpreende ver um homem como você lidando com aquele canalha.";
			link.l1 = "Peço desculpas, mas não cabe a você chamá-lo de canalha. Você fugiu do campo de batalha e difamou o Tom. Talvez depois tenha se arrependido e se tornado um oficial exemplar aqui no Arquipélago, mas isso não muda o passado.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Ele te contou isso? Não me surpreende – ele sempre soube encontrar a pessoa certa pra ouvir suas histórias. Thomas tinha lábia. Você não conhece ele, nem a verdadeira história, nem no que está se metendo. Posso te contar – já que não vou conseguir dormir mesmo.";
			link.l1 = "Nunca é uma má ideia ouvir. Continue, Capitão Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Então, o Thomas diz que fui eu quem fugiu e depois o difamou? Pois fique sabendo que foi exatamente o contrário! Quando a cavalaria do Rei se aproximou, o Tom disse que ia buscar reforços. Então nós não recuamos — esperamos. Nossa companhia inteira foi massacrada! Se não tivéssemos esperado pelos reforços que ele prometeu, poderíamos ter recuado e sobrevivido! No fim, só sobramos eu, o Frankie e o maldito Thomas.";
			link.l1 = "Então o que você está dizendo é...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Estou dizendo que o sangue dos nossos rapazes está nas mãos do Tom tanto quanto nas dos realistas. Ele ainda teve sorte de ser condenado à prisão e não à forca! E agora ainda tem a ousadia de guardar rancor e me desafiar para um duelo! Ele não é digno disso!";
			link.l1 = "Então você não vai? Você sabe o que isso significa. As leis da honra valem para todos.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Claro que sim. E é por isso que eu vou. Precisamos terminar o que nosso tribunal republicano não pôde por causa das antigas honrarias militares do Tom. E você... você parece uma pessoa decente. Eu aconselharia a escolher melhor suas companhias. Não se envolva com o Tom e gente como ele.";
			link.l1 = "Mas agora o Thomas é meu subordinado, um oficial no meu navio. "+GetSexPhrase("Vou ficar de olho nele e não vou deixar que ele se envergonhe ainda mais, caso sobreviva ao encontro com você.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "E o que você faria no meu lugar, Capitão Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "É, se o Tom conseguiu te convencer com a história dele, não vai ter dificuldade em fazer isso de novo.";
			link.l1 = ""+GetSexPhrase("Mas pelas leis da honra, não posso traí-lo. Eu estou","Eu estou")+" responsável pelos meus homens... Não vou ser como ele. E daqui pra frente vou ser mais cuidadoso e crítico com ele, se ele sobreviver.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "É uma decisão difícil. Mas não vou tentar te convencer do contrário. Bem, adeus, "+GetSexPhrase("senhor","senhorita")+" - Ainda preciso me preparar para encontrar o Tom.";
			link.l1 = "Adeus, Capitão Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Que a justiça seja feita! Me ajude a derrubar o Thomas, "+pchar.lastname+". Ele é um canalha raro e um covarde, mas um excelente atirador – não vai ser fácil. Mas juntos...";
			link.l1 = "Hum, ajudar você a derrotar o Thomas? Existe muita honra em um duelo assim? Vocês podem resolver isso entre si, e eu vou ficar fora dessa.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Conhecendo ele, duvido que terei um duelo justo. Ao se manter neutro, você só está apoiando a injustiça. Estou certo?";
			link.l1 = "Parece que você conhece o Tom melhor do que eu, e sabe como ele realmente é. Você está certo – ele já está preparando uma emboscada na Baía de Portland, e está contando com a minha ajuda – assim como você agora.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Então não é um duelo, mas uma briga. Mas não estou sugerindo que matemos o Thomas nós mesmos. Vamos prendê-lo! Vou trazer soldados, e vamos terminar o que não conseguimos no Velho Mundo. Se tentarem absolvê-lo de novo, vou escrever para o Coronel ou até trazê-lo aqui para o julgamento. Se o Thomas não largar as armas, a culpa será dele.";
			link.l1 = "Isso soa muito melhor.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Fico feliz em saber disso, "+pchar.lastname+"! Eu sei que pode não ser fácil para você tomar uma decisão dessas, mas te garanto, você fez a escolha certa. E para provar isso, vou te ajudar com mais uma coisa.";
			link.l1 = "O que foi, Capitão Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Aqui, pegue isto. Não é um presente, é só um empréstimo – o Thomas, como eu disse, é um lutador de primeira, e é melhor enfrentá-lo com uma arma decente, não com um pedaço de ferro enferrujado. O próprio coronel Doyley me deu essa beleza, mas para uma luta de verdade, eu sempre prefiro uma espada larga.";
			link.l1 = "De fato, é uma espada magnífica. Obrigado.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Não me agradeça – estou te emprestando, não dando de presente, lembra? Agora vá até a enseada e faça sua parte com o nosso querido Tom enquanto eu busco reforços. Te vejo lá.";
			link.l1 = "Te vejo lá, Capitão Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			Notification_Reputation(false, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Quem é você, moça? Deve ter vindo ao lugar errado. Eu, ahn, não pedi nenhum serviço noturno.";
				link.l1 = "Helen MacArthur. E controle seus desejos, Sr. Callow. Sou uma moça decente. O clima daqui me faz sentir calor, até à noite. Não ficou envergonhado de dizer isso para uma desconhecida? Disseram que o senhor é um oficial exemplar.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Quem é você, e o que quer? Não gosto desse seu sorriso, senhor.";
				link.l1 = ""+GetFullName(pchar)+". E você não é muito hospitaleiro, Sr. Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Você cumprimenta estranhos de outro jeito a essa hora?";
			link.l1 = "Me disseram que você não está em casa em outros horários.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Claro que não sou - tenho serviço, dever e trabalho honesto, palavras que parecem desconhecidas para você, pelo seu jeito de se apresentar.";
			link.l1 = "Tanta autoconfiança! Mas, afinal, você não teria convencido o coronel Doyley e os outros da sua honestidade de outro jeito. Eu não preciso de nada de você, Gabe, mas um velho conhecido seu precisa. Aqui está.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Convencido? Gabe? Digo! Um ponto negro? Então você é um pirata? Espere um pouco... seda preta... será que isso é... Ah, entendi. Thomas, seu desgraçado, ainda está bravo comigo e com o Frank por termos te denunciado, ha ha ha ha!";
			link.l1 = "Ouça! Tom é oficial no meu navio e merece respeito. Ele é um dos melhores atiradores do arquipélago.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Eu não disse que ele era um mau atirador. Mas vejo que você não conhece o Thomas muito bem. Foi ele quem nos traiu. Mas percebo que não adianta discutir com você – vocês realmente se merecem.";
			link.l1 = "Não me importo. Guarde suas histórias para Doyley e todos aqueles ingênuos. Se você é tão corajoso e honrado quanto dizem, aceite o desafio e venha agora. Então, aceita?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Eu sei, eu sei. Agora saia da minha casa antes que eu chame os guardas.";
			link.l1 = "Será um prazer, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Por que você está tão nervoso? Está com medo, é isso?";
				link.l1 = "Qualquer um ficaria nervoso vendo um homem correndo com uma mosquete na mão – eu nem te reconheci de primeira. O que você está fazendo aqui, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Como foi? Ei, ei, por que está me olhando assim? Você me assustou, hehehe.";
				link.l1 = "Quem está assustando quem! Quem é que está fugindo desse jeito?! Combinamos de receber os convidados na enseada!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, bem, talvez. Cansei de esperar – tanto pelos nossos queridos convidados quanto por você. E decidi que este lugar era mais apropriado para uma emboscada de verdade. Afinal, sou um caçador, não um duelista.";
			link.l1 = "Entendi.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Então. E aí, deixou meu presente na casa do Gabe? Demorou, hein. Eu seria bem mais rápido se pudesse entrar na cidade. O que foi, capitão, tá distraído? O que houve?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Confiável) Estou nervoso. Gabe é um covarde, mas não é burro. E se, em vez dele, vier um pelotão inteiro de soldados? Ou se eles se aproximarem da enseada e afundarem nosso navio antes?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l2 = "O Gabe me viu. Tive que fugir.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				Notification_Perk(false, "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, entendi - nem eu tenho certeza se isso vai dar certo. É a primeira vez que algo tão grande acontece com você, né? Fica tranquilo, acontece. Já pensei em tudo. Se os soldados vierem sem o Gabe, a gente só vai embora. Se vierem com o Gabe, eu meto uma bala entre os olhos dele e, de novo, a gente só vai embora. E se um navio aparecer na baía, corremos pra Maroon Town - eles não vão se atrever a ir lá, e aí decidimos o que fazer depois.";
			link.l1 = "Vejo que você pensou em tudo mesmo, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Claro que sim. Agora vamos esperar nosso convidado...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, você é tão bom ladrão quanto eu sou realista. Mas por que não olha nos meus olhos... Capitão? Você estava falando com o Gabe, não estava?";
			link.l1 = "Não, do que você está falando? Por que eu sequer falaria com ele?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Porque vocês só sabem falar. Só falam, falam. Então, o que o nosso querido Gabe te contou?";
			link.l1 = "Isso importa, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Francamente, não. Só funciona se você não me apunhalar pelas costas. Mas parece que já fez isso. Ele te convenceu a ficar do lado dele, não foi?";
			link.l1 = "Não. Não exatamente. Abaixe a arma, Tommy. Eu te prometo, nada de irreparável precisa acontecer. Você pode trabalhar nas pedreiras, talvez. Vou pedir ao Gabe para ter piedade. Vou até pedir ao Coronel Doyley, se for preciso.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Que bom samaritano você é. Mostrando piedade só pra eu tossir até perder os pulmões depois de anos na pedreira? Eu não volto mais pros navios-prisão. Nunca mais. E você... Eu devia saber que era só mais um rato. Tem algo no seu jeito de olhar. Vou acabar com você primeiro, assim lidar com o Gabe vai ser mais fácil depois.";
			link.l1 = "Você não nos deixa escolha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Bem, vejo que você já fez isso, "+GetSexPhrase("senhor","senhorita")+". E eu estava reunindo um grupo, achando que ter vantagem numérica faria o Tom pensar duas vezes antes de baixar as armas.";
			link.l1 = "E você demorou, Capitão Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Eu te disse, estava reunindo homens. Os melhores da nossa guarnição. O Tom é um soldado veterano, afinal. Mas pra quem estou dizendo isso? Muito bem, "+GetSexPhrase("Senhor.","sentir falta")+" "+pchar.lastname+". "+GetSexPhrase("Tenho orgulho de você, rapaz","Tenho que admitir, moça, você tem beleza, inteligência e habilidade em igual medida")+". Como te disse quando nos conhecemos, você fez a escolha certa. Agora a justiça foi feita.";
			link.l1 = "Deu tudo tão certo pra você. Está se sentindo orgulhoso?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Bem, eu não sou um soldado veterano, mas sei lutar, como você deve ter notado. Mas obrigado, senhor. Justiça não é uma palavra vazia para mim.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "E isso é louvável, "+GetSexPhrase("rapaz","moça jovem")+". No entanto, ainda falta uma coisa para completar este belo dia.";
			link.l1 = "Hum, e o que é isso? Tom já foi derrotado, afinal.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Você tem algo que me pertence. Por favor, devolva minha bela espada italiana. Não é só um palito de dente, afinal, mas uma lembrança – um presente do próprio Coronel Doyley.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "É... Então, Capitão Callow... a rapieira sumiu. Eu perdi. Me desculpe.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, claro. Por favor. Não foi minha intenção pegar isso. Não vou mentir – eu gostaria de ficar com ele. Mas aqui está, Capitão Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Tenho uma proposta melhor para você, Capitão.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Mas você acabou de chamar isso de palito de dente. Além disso, disse que nem gosta de rapires. Eu, por outro lado, mereço uma recompensa.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Qualquer um teria querido ficar com essa beleza! Obrigado por tê-la devolvido para mim. Muita gente teria sido teimosa no seu lugar.";
			link.l1 = "É seu. Suponho que terminamos aqui?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Não estou interessado. Apenas devolva a rapieira, e vamos nos separar em bons termos, "+GetSexPhrase("Senhor.","senhorita")+" "+pchar.lastname+".";
			link.l1 = "Imagino que essa rapieira é valiosa pra você porque gosta de armas com história, não é? Eu tenho uma igualzinha, e essa é daquelas que a gente prefere levar consigo do que deixar guardada numa gaveta.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "É mesmo? Bem, não posso prometer que vamos chegar a um acordo, mas estou ouvindo. De fato, me interesso por armas com história. Mas esta rapieira foi um presente do Coronel. Por isso ela é tão valiosa para mim.";
			link.l1 = "Você disse que gosta de espadas largas. Aqui. Ela pertenceu ao nosso querido Tommy. Imagine tudo o que essa arma já enfrentou ao longo dos anos. E tudo o que ainda vai enfrentar com você.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Você é bem persuasivo, rapaz! Empunhando a espada do Thomas... que ironia. Bem, leve o florete. Mas saiba que não estou me desfazendo dele facilmente.";
			link.l1 = "Fico feliz que conseguimos chegar a um acordo. Suponho que isso seja um adeus, Capitão Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "O QUÊ?! Como você pôde... Como pôde perder uma maldita espada inteira?! Você é um idiota!";
			link.l1 = "Calma! É só uma espada. Você nunca usaria mesmo. Tom está morto – não é isso que importa agora?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = " Só uma rapieira?! Era o meu tesouro! Um presente do próprio Coronel Doyley! Não me importa que eu nunca tenha usado!";
			link.l1 = "Então você não devia ter me dado, não é mesmo?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "É melhor você ficar de boca fechada agora, "+GetSexPhrase("Senhor.","senhorita")+" "+pchar.lastname+". Podíamos ter seguido caminhos diferentes em paz. Mas agora... agora quero te dar uma lição, "+GetSexPhrase("rapaz","moça jovem")+".";
			link.l1 = "Cemitérios estão cheios de professores como você.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Claro que sim. Mas você não pode simplesmente pegar a arma pessoal de um oficial só porque lhe deu uma ajudinha, pode?";
			link.l1 = "Eu até concordaria, mas você nem usa isso mesmo. Vai ficar só pendurado num prego no seu quarto. Comigo, pelo menos, vai ter um uso de verdade. O coronel Doyley não vai checar se você perdeu, vai?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Isto não está em discussão, rapaz. Eu te disse desde o começo, não é um presente. Me entregue a rapieira. Agora.";
			link.l1 = ""+GetSexPhrase("Eu não sou um dos seus soldadinhos de brinquedo","Eu não sou uma dessas prostitutas de porto suas")+", para receber ordens suas. Sou capitão de navio, assim como você. A espada fica comigo, goste você ou não.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Parece que o Thomas teve mesmo um grande efeito sobre você. Então morra por isso, se é o que você tanto deseja.";
			link.l1 = "Eu penso exatamente o mesmo!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Aqui, fique com isto. Eu não preciso disso mesmo. Considere como uma lembrança deste dia. Tente não ser tão ingênuo daqui pra frente. E não deixe canalhas como o Thomas te envolverem nos esquemas sujos deles.";
			link.l1 = "Hein, você está me dando o ponto negro, Capitão Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Bem, nenhum de nós é pirata, não é, "+pchar.name+"? Que isso sirva de lembrança. Se cuide, o Arquipélago precisa de homens como você. "+GetSexPhrase("Talvez eu sugerisse entrar para a Marinha e escrever uma recomendação para o Coronel Doyley...","")+"";
			link.l1 = "Lamento, mas não posso aceitar sua oferta, Capitão.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Vou pensar nisso. Pensar de verdade.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Adeus, senhor.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Como quiser. Bem, adeus. "+GetSexPhrase("Senhor.","senhorita")+" "+pchar.lastname+". Você merece carregar o que restou dos Ironsides. Adeus.";
			link.l1 = "Despeça-se, senhor.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Não gostei do seu tom, "+GetSexPhrase("senhor","senhorita")+". Qual é o seu ponto?";
			link.l1 = "Você ficou enrolando de propósito, reunindo seus 'melhores homens'. Pra quê? Pra capturar um único homem? Era só ter chamado uns soldados que patrulham a cidade e vindo me ajudar na hora!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Trouxe carne de canhão?! O Tom não era só um guarda da cidade como eles. Ele tinha um treinamento e uma experiência completamente diferentes — ele é um maldito Couraçado, igualzinho a mim! Como é que você não percebe isso?";
			link.l1 = "Ah, pelo contrário, eu percebo muito bem. Foi por isso que você e eu estávamos aqui – para cruzar espadas com o Tom, enquanto os rapazes o capturavam vivo. Além disso, você também é Ironclad. Da mesma companhia, inclusive. Estava com tanto medo de enfrentá-lo cara a cara?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Como você ousa me acusar de covardia, jovem "+GetSexPhrase("homem","senhorita")+"! Pergunte a qualquer um, e vão te contar em detalhes sobre as façanhas que realizei por esta cidade.";
			link.l1 = "Eu ainda não terminei. Já começo a duvidar se essas ‘façanhas’ foram mesmo obra sua. Você queria que eu e o Tom nos matássemos pra ficar com toda a glória. Já fez isso antes, não fez?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Já cansei das suas acusações, "+GetSexPhrase("Senhor.","senhorita")+" "+pchar.lastname+". Você quer conflito? Vai ter. Agora mesmo.";
			link.l1 = "A verdade dói, não é, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! Faz tanto tempo, tantos invernos sombrios! E olha só pra você – ainda com essa cara de convencido, maldito!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! Eu deveria estar satisfeito, pois hoje finalmente vou realizar com minhas próprias mãos o que nosso sistema de justiça falhou em fazer por anos. E como estou de bom humor, vou permitir que você largue suas armas e venha conosco. Talvez até seja mandado de volta para a prisão. Nesse caso, eu mesmo vou escoltá-lo até lá.";
			link.l1 = "Heh, me faça parar! Acha que dois caras do seu lado vão me impedir!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Quem disse que são só eles que estão comigo? Estou falando da pessoa que está ao seu lado agora.";
			link.l1 = "O quê?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... você está, como sempre, sozinho neste mundo. Quase sinto pena de você!";
			link.l1 = "Malditos ratos! Desgraçados!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "O que isso quer dizer?! O que ele quis dizer com isso?!";
			link.l1 = "Tommy, escuta...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "É exatamente isso que estou fazendo! Me diga que ele está mentindo!";
			link.l1 = "Infelizmente, ele está certo. Abaixe suas armas. Ninguém precisa morrer hoje. Eu mesmo vou falar bem de você, assim você não será enforcado. Quem sabe um dia você até volte a ter uma vida honesta.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Isso não cabe a você decidir! E muito menos a você! Quem precisa de inimigos com um comandante desses! Mais um maldito rato.";
			link.l1 = "Vamos, Tommy. Não existe fuga limpa para gente como você.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Um lugar na sua tripulação, no seu navio, já seria um começo, se ao menos você tivesse coragem de defender seus homens! Mas isso já não importa mais. Malditos sejam, todos vocês! Vou arrancar as tripas covardes de vocês, seus ratos. E você, Gabe, vou tentar te levar comigo...";
			link.l1 = "Espera, Tommy, não!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Parabéns, "+GetSexPhrase("rapaz","moça jovem")+"! Estou impressionado que você conseguiu fazer o Thomas acreditar que tudo estava indo conforme o plano dele - ele tinha faro para traição.";
			link.l1 = "Ah, obrigado, claro, Capitão Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Tem algo te incomodando, "+GetSexPhrase("Sr.","senhorita")+" "+pchar.lastname+"?";
			link.l1 = "Tom... ele não estava só bravo por eu estar do seu lado. Havia um desespero verdadeiro e uma incompreensão na voz dele, como se...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...como se ele fosse a vítima aqui. Era de se esperar. Lembre-se, Charles, um monstro pode sentir dor. Mas isso não o impede de ser um monstro. Muitos criminosos realmente acreditam, de coração, que são justos e inocentes.";
			link.l1 = "Vou tentar lembrar disso. Acho que terminamos aqui, não acha, Capitão?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "Em geral, sim, mas ainda falta uma coisa para completar este belo dia.";
			link.l1 = "Oh? O que foi?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Você demorou, hein. Então resolvi dar uma olhada por aqui. De qualquer forma, acho melhor a gente armar uma emboscada aqui do que bancar duelistas na praia. Conseguiu achar a casa do Gabe e deixar tudo à mostra?";
			link.l1 = "É claro que eu fiz, por quem me toma, um idiota? Na verdade, eu sou seu capitão, Tommy. O que isso faria de você, se servisse a um idiota?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, você não faz ideia de quantas vezes já tive que lidar com esse tipo de bobagem no serviço! Mas, felizmente, não é o nosso caso. Muito bem, então. Estamos esperando companhia. Pronto?";
			link.l1 = "Bem, a menos que toda a frota ou a guarnição de Port Royal apareça aqui, estou pronto.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? Então é mesmo você...";
			link.l1 = "Claro que sou eu mesmo, ou você esperava outra pessoa, Gabe? Heh, você está pálido, como se tivesse visto um fantasma. E também está mais gordo do que era lá na Velha Inglaterra.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Agora tenho certeza de que é mesmo você. Grosso como sempre. Mas tudo bem, logo vou calar essa sua boca imunda de uma vez por todas, seu desgraçado.";
			link.l1 = "Ha-ha-ha, agora sim estamos falando! Sabe, você realmente me decepcionou, Gabe. De novo! Era óbvio que você precisava trazer mais homens só pra me enfrentar sozinho. E somos dois aqui! Ou foi só isso que conseguiram te dar, seu covarde?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Chega! Não vejo mais sentido em continuarmos essa conversa.";
			link.l1 = "Concordo com você nisso! "+pchar.name+"! Para a batalha, Capitão!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, aí está! Descanse em paz, seu desgraçado.";
			link.l1 = "Então, está satisfeito, Tommy? Sabe, muita gente só piora depois de se vingar.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, você leu isso em algum lugar? Nunca entendi gente tão fraca. Bah! Estou satisfeito? Estou tão feliz que poderia até mijar nas calças! Aqueles desgraçados foram a origem dos meus maiores infortúnios!";
			link.l1 = "Fico feliz por você. Não tem mais ninguém de quem precise se vingar? Devo esperar mais piadas sobre cartuchos de papel da sua parte?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Calma, o Gabe foi o último. E quanto às piadas – não se preocupe, não vai ter mais nenhuma, pelo menos não com você.";
			link.l1 = "Vamos voltar para o navio então?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "A gente acabaria voltando pra ela de qualquer jeito, tendo ou não alguém pra me vingar. Mas espera aí...";
			link.l1 = "Ah, então ainda não acabou...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "É, é sim. Tem algo que quero te contar. É algo que digo para pouquíssimas pessoas. E não vou repetir. Se você rir de mim, vou ficar muito bravo com você.";
			link.l1 = "Prometo não rir. Aliás, acho suas piadas mais tensas do que engraçadas.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Ótimo. Então... Sou muito grato por você ter decidido me ajudar em vez de fazer o que o Jack fez. Você é um verdadeiro amigo, Capitão. Obrigado. Ah, e... se quiser, pode pegar emprestada minha espada fiel e minha armadura... O que sobrou dela, ha-ha!";
			link.l1 = "Bem, obrigado por dizer isso. Não é todo dia que se ouve algo assim dos seus oficiais. Vamos lá, camarada.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Sim, capitão?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				Link.l1 = "Tommy, parece que é aqui que nossos caminhos se separam.";
				Link.l1.go = "SharlieEpilog_Irons_1";
				break;
			}
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Então, Rumba, sobre quais ossos vamos dançar esta noite?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Sim, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Estou ouvindo, capitão.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, preciso te pedir uma coisa muito séria. Existe um... um ídolo de pedra dos índios. E vou precisar de ajuda. Só posso pedir isso aos meus amigos mais próximos, como você. Recém-chegados ou quem ainda não confio de verdade não serve.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, pare de contar as gaivotas. Já conferiu toda a carga? Me dê um relatório completo e uma previsão.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, a partir de hoje, preciso que você compre certos produtos nos portos.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, você pode me informar tudo sobre o navio?";
					Link.l12 = "Tommy, estou ficando meio cansado. Você poderia abastecer certos produtos em cada porto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Prepare um relatório sobre o estado do navio e tudo o que há a bordo, Tommy.";
					Link.l12 = "Você poderia abastecer certos produtos durante nossas paradas no porto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Conte tudo o que tenho no navio e faça um relatório sobre o estado geral dele.";
					Link.l12 = "Preciso que você compre essas mercadorias durante nossas paradas em cada porto.";
				}
			}
			//////
			Link.l1 = "Ouça com atenção as minhas ordens!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Alguém está, com certeza. Mas por enquanto, siga minhas ordens.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Escute minhas ordens... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Que bom, porque tenho uma nova tarefa pra você, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Escute minhas ordens, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Nada, Tommy. Fique tranquilo.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Vamos ver no que vai dar, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Não, Tom, nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Não, nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Nada, está tudo bem.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Eu nem comecei a mexer no estoque. Você devia agradecer por eu estar calculando nossos lucros e prejuízos, quanto mais barganhando com aqueles mercadores gananciosos. Estoque não é comigo, nunca precisei disso no exército, e não vai ser agora que vou começar.";
			Link.l1 = "Isso aqui não é o exército, Tommy. Mas tudo bem, entendi, não vou te forçar.";
			if (startHeroType == 4)
			{
				dialog.Text = "Eu não sou escriba, Ellie. Conheci um sujeito, Daniel Crimson, que vivia dizendo que era escriba, mas mal tinha visto um campo de batalha. Mesmo assim, o homem era uma fera na briga. Mas esse não sou eu, e não vou mentir sobre isso. Inventário não é comigo. Já estou cuidando das nossas contas por sua causa. Não força a barra.";
				Link.l1 = "Tá bom, Tommy, eu não vou.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Olha, eu não sou escriba. Nunca exigiram isso de soldados comuns como eu, nem mesmo no exército. Vamos manter essa regra.";
				Link.l1 = "Certo, melhor não.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "A única coisa que eu consigo contar é quantos inimigos já derrubei, ha-ha-ha. E mesmo assim, às vezes perco a conta. Sou um soldado simples, sabe? Quem diabos entende de navio – passei a maior parte da vida em terra firme.";
				Link.l1 = "Parece que vou ter que fazer isso eu mesmo.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Por quem me toma, um intendente de quinta categoria? Lá em casa, só tínhamos desprezo por esses covardes de meia-tigela. Não sou nobre, mas ainda tenho meu orgulho.";
			link.l1 = "Certo, certo, se você não quer, então não quer.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Olha, eu era um soldado simples e honesto, não um intendente, minha garota. Não entendo muito disso e nem quero começar a aprender. É como te pedir pra montar e desmontar um mosquete contra o tempo.";
				Link.l1 = "Bem, eu poderia nomear de cor cada parte do cordame fixo e móvel deste navio. Mas como quiser, Tom. Assunto encerrado.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Não, eu não consegui. Talvez você tenha esquecido, ou talvez nem saiba disso, então vou explicar. Para você, isso seria uma tarefa rotineira, mas no nosso exército, não tratamos muito bem o pessoal de suprimentos e apoio. Por favor, não me coloque no mesmo grupo que eles.";
				Link.l1 = "Ha-ha, bom, bom.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Olha, eu te respeito, claro, mas não vou me trair fazendo algo que não posso ou não aguento. Mal aprendi a contar naquela época, e agora você quer que eu vire fornecedor de verdade. Aliás, a gente não gostava deles – economizavam munição, água, comida, e ainda por cima tudo era velho.";
				Link.l1 = "Hum, tudo bem, vamos esquecer isso.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ah, uma ordem, é? Você gosta dessas coisas de exército e toda essa disciplina, não é? Eu preferia que você só dissesse o que precisa ser feito.","Você parece um sargento ou algo assim. Isso não combina com você – é bonita demais pra isso. Não teria durado um dia no exército. Mas estou ouvindo.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Aparentemente, você realmente é fã de uniformes, exercícios e tudo isso. Mas tudo bem, continue.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Qual deles?";
			}
			
            Link.l1 = ""+GetSexPhrase("Não vá a lugar nenhum e não faça nada – só observe, entendeu? Eu te conheço.","Fique exatamente onde está, entendeu?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Fique aqui, não vá a lugar nenhum e não toque em nada.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Fique aqui e não deixe ninguém passar.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Me siga e não se distraia com nada – nem esposas perdidas, nem velhos camaradas de guerra que apareçam do nada.","Fique perto, tudo bem? Quero que cubra minhas costas.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Venha comigo. Dá pra ver que você está perdido em pensamentos.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Me siga, a menos que tenha parado por algum motivo.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Preciso que você atire em algo diferente desta vez.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Preciso que você use munição diferente na próxima luta.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Você vai usar munição diferente na próxima batalha.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Mude o tipo de munição do seu mosquete.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Troque sua arma principal para combate.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Eu gostaria que você mantivesse uma certa distância entre você e seus inimigos.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Eu gostaria que você mantivesse uma certa distância do inimigo, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Mantenha uma certa distância entre você e o inimigo, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Que tipo de projéteis? Espero que você tenha feito cada um com cuidado, porque vai saber onde eles vão cair, hehe.","Eu atiro em qualquer coisa por você. Seja o que for, mas nunca de festim, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Estou sentindo que algo interessante está para acontecer! Certo, do que se trata?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Lutando de novo... Certo, que tipo?";
			}
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

		case "SetMusketBullets":
			Dialog.Text = "Selecione o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "No início da luta você vai usar:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mosquete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Mesmo se você apanhar lá, hehe? Entendi, vou só assistir.","Quer me transformar em guarda? E se você acabar apanhando ou algo assim?")+"";
            Link.l1 = ""+GetSexPhrase("Ei, cuidado! A gente dá um jeito se chegar a esse ponto.","Bem, você não vai ficar aí parado só olhando, vai? Se acha mesmo que seu capitão é tão incrível quanto diz, faça alguma coisa.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Mesmo mirando na cabeça? Tá bom, tá bom, não me olha assim, eu entendi.";
				Link.l1 = "Espero que sim.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Não tenha medo, ninguém vai passar por aqui.";
				Link.l1 = "Se você não sente falta de ninguém, claro. Mas tudo bem.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Muito engraçado. Mas entendi o que você quis dizer.","Ah, não se preocupe, estou sempre do seu lado, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Bom.","Deus, você é insuportável, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Bem, estou tentando me lembrar de algo muito importante. E então percebo que nem sei o que é, já que perdi a memória naquela época, então não vai dar em nada. Certo, vamos.";
				Link.l1 = "Engraçado, tenho que admitir.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Bem, estou aqui porque você mesmo mandou eu ficar. Já estou indo, já estou indo.";
				Link.l1 = "Hmm, tudo bem, tudo bem.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Que tipo de distância? Lembre-se que, além de vinte jardas, não vou conseguir mirar direito. A não ser, claro, que você não precise que eu acerte nada de verdade, hehe.","Como se eu fosse querer chegar perto de homens fedorentos depois de ficar perto de você. Então, qual é a distância? Mas lembre-se, não consigo mirar meu tiro além de vinte jardas. Ninguém consegue.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Certo, qual a distância? Mas já vou avisando que não vou conseguir atirar com precisão e calma a mais de vinte metros no calor da batalha.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Tá bom. O quê? Lembra que além de tudo... bem, nós não somos mais crianças, você e eu sabemos disso.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Você não deveria tentar fazer graça.","Você ainda tem muito o que aprender comigo sobre humor, minha garota. Mas está melhorando!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Nem foi sua pior piada. Quem sabe um dia você até pare de ser tão rabugento, heh-heh.";
					Link.l1 = "Ah, tudo bem.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, boa piada.";
					Link.l1 = "Na verdade, eu só... tudo bem.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Então eu vou ficar parado e segurar a minha posição. Se você lutar com eles de muito longe, quem vai se arriscar é você, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, você podia só ter me pedido pra segurar a posição, em vez de falar de distâncias e números.";
					Link.l1 = "Bem, o mais importante é que você me entendeu.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Entendi, vou segurar a posição aqui. Depois traga eles mais perto pra eu atirar.";
					Link.l1 = "Com certeza.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Olha, eu sei que você queria que todo tiro meu fosse como aquele no farol, mas isso não vai acontecer. Lá era uma boa posição. Calmo e tranquilo. Não dá pra repetir isso no meio da batalha.";
				link.l1 = "Hum. Então fique a uns vinte metros de distância.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Eu sei que você ia gostar disso, todo mundo ia gostar, mas como daquela vez no farol, isso não vai funcionar mais. Vou precisar de um bom lugar, e que ninguém chegue perto de mim, senão meus nervos vão me trair.";
					Link.l1 = "Hmm, tudo bem.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Com certeza aperfeiçoei minhas habilidades desde então, mas o impossível continuará impossível – no calor da batalha, eu jamais conseguiria repetir aquele tiro do farol. Nem mesmo com um rifle de pederneira.";
					Link.l1 = "E o impossível é possível, Tommy. Mas tudo bem, não é não.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Muito bem. Vou manter exatamente essa distância, mas se estivermos lutando dentro de uma taverna ou caverna, eu saio pra fora pra garantir, hehe.","Vou tentar. Mas os conveses e os espaços apertados podem impor suas próprias condições.");
			link.l1 = ""+GetSexPhrase("Não tem graça, Tommy. Comporte-se direito, e nada de piadas ou dessas suas pegadinhas idiotas.","Eu sei disso, Thomas, não sou burra.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Vou tentar lembrar.";
				Link.l1 = "Beleza, estou contando com você.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Sim, capitão.";
				Link.l1 = "Fique à vontade, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Ajudar com o quê, roubar isso? Mas por quê? Fico lisonjeado, claro, mas você podia ter dito tudo faz tempo. Vai, fala logo.";
			link.l1 = "Fala direito, hein? Quer saber? Dane-se – não me importo com o jeito que você fala, desde que esteja do meu lado. Então, sobre aquele ídolo. Com ele, você pode... viajar magicamente para outro lugar. Não me olha assim – eu sei como isso soa. Mas já passei por isso antes e vi tudo com meus próprios olhos. É... seguro, se você tomar um elixir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Vejo que você já tomou uns drinks. Ou melhor, não, parece estar sóbrio. E dizem que sou eu quem fala besteira...";
			link.l1 = "Você vem comigo ou não? O ídolo deve nos levar até uma antiga cidade maia, e ninguém sabe o que nos espera lá. Você é uma das poucas pessoas em quem acredito que posso confiar num momento difícil. E agora chegou esse momento.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Estou com um mau pressentimento sobre tudo isso. Se você não fosse meu capitão, eu diria que você devia estar num hospício. Daqui a pouco vai dizer que Deus existe.";
			link.l1 = "Ele faz isso, Tommy. E, para minha surpresa, descobri neste arquipélago que não são só os nossos. Você mesmo pode ver toda a malandragem que acontece por aqui. E provavelmente já percebeu a influência de amuletos abençoados ou amaldiçoados.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Diabruras também existem em casa. E sempre tiveram uma explicação normal. Desculpe, capitão, mas não vou dançar em volta de ídolos de pedra com você. Atirar em inimigos, tudo bem. Posso ter perdido a memória, mas não perdi o juízo. Pelo menos, acho que não.";
			link.l1 = "Bem, não posso te obrigar. Então... como quiser, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Duvido que você tenha coragem de atirar neles, valentão, se tem medo de chegar perto do ídolo.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh, tá bom, tá bom, não faz essa cara. Olha, se você voltar depois de rodar em volta daquele ídolo, aí eu penso no assunto da próxima vez.";
			link.l1 = "Pode ser que não haja uma próxima vez. Volte para o navio, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Não é que eu tenha medo, não me entenda mal. Mas eu costumo confiar no meu instinto, ele nunca me deixou na mão todos esses anos. E agora ele está me dizendo que nada de bom vai sair disso. E de qualquer forma... Ah, deixa pra lá, você vai acabar se ofendendo.";
			link.l1 = "Pode falar.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Bem, se é assim! Eu aceitei lutar ao seu lado. Mas e se, vamos imaginar, esse negócio realmente funcionar? E se for amaldiçoado? Eu não vou morrer por ninguém, me desculpe.";
			link.l1 = "Agora você mostrou quem é, Tommy. Eu precisava das pessoas mais leais. E agora vejo que você não é uma delas. Eu vou embora. E você... faça o que quiser.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Olha só pra ele. No fim das contas, ficou ofendido.";
			link.l1 = "Cale a boca. Se nos acha tão repugnantes, não precisa voltar para o navio.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Mas que surpresa! Está falando sério? Bem, talvez seja melhor assim. Não quero ficar com gente sem graça que nem entende uma piada. Nesse caso... adeus, Sua Excelência.";
			link.l1 = "Adeus, Tommy. E vai para o inferno.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_tieyasal_otkaz");
		break;
		
		// Эпилог
		case "SharlieEpilog_Irons_1":
			dialog.text = "Ha. Veja só, aprendeu a fazer piada. Quase como eu. Mas não vou cair nessa isca, nem pense nisso.";
			link.l1 = "Você não entendeu – isso não é brincadeira. Estou indo para a Europa, ver meu pai. Claro, você pode ficar aqui e esperar... mas não sei quanto tempo isso vai levar.";
			link.l1.go = "SharlieEpilog_Irons_2";
		break;
		
		case "SharlieEpilog_Irons_2":
			dialog.text = "Ah, você não é tão bom pra fazer piada com essa cara. Então tá me chutando? Depois de eu salvar sua pele? Depois de tudo que fiz por você?";
			link.l1 = "Não dramatiza, Tommy. Você só estava fazendo seu trabalho – e recebia por isso. Reconheço, você é bom no que faz. E se decidir esperar, ficarei feliz em te ter a bordo de novo. Mas por agora...";
			link.l1.go = "SharlieEpilog_Irons_3";
		break;
		
		case "SharlieEpilog_Irons_3":
			dialog.text = "Muito nobre da sua parte, porra. Pois obrigado, capitão traidor, senhor. Vamos anotar assim – 'o cão fiel pode esperar pelo dono, se não morrer de tédio'.";
			link.l1 = "Não leve pro lado pessoal. É só como as coisas aconteceram.";
			link.l1.go = "SharlieEpilog_Irons_nothing";
			link.l2 = "Entendo que você esteja bravo. Eu também ficaria no seu lugar. Vou te pagar um mês de salário extra, além do que te é devido. Espero que não guarde rancor.";
			link.l2.go = "SharlieEpilog_Irons_salary";
			link.l3 = "Sei que essa notícia te pegou de surpresa, e você tem todo o direito de ficar indignado. Estou disposto a te pagar três meses de salário extra além do combinado.";
			link.l3.go = "SharlieEpilog_Irons_salary_X3";
		break;
		
		case "SharlieEpilog_Irons_nothing":
			dialog.text = "Que se dane a situação. E você também. Me arrependo de ter me metido contigo. E sabe de uma coisa? Não é você que tá me mandando embora – eu que tô caindo fora.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
		break;
		
		case "SharlieEpilog_Irons_salary":
			dialog.text = "Guarde essas moedinhas pros mendigos. Eu não preciso da sua caridade.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Irons_salary_X3":
			dialog.text = "Três salários? Que generosidade... Fiquei até emocionado. Manda essa esmola pra cá. Vou gastar com bebida pros rapazes na taverna – em homenagem ao capitão Charles de Mor: modelo de lealdade, símbolo da amizade, exemplo a ser seguido.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Irons_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Irons_exit");
		break;
	}
} 