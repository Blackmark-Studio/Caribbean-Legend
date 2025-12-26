// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Finalmente, vejo o famoso capitão francês "+GetFullName(pchar)+" em carne e osso. Ouvi muito sobre seus feitos. Você é um soldado valente e, espero, um filho leal e fiel de nossa Mãe, a Santa Igreja Católica Romana. Sente-se, meu filho. Não precisa ficar de pé por minha causa. Dominus vobiscum! ";
				link.l1 = "Et cum spiritu tuo, Sua Excelência. Minha viagem até aqui foi longa e difícil... Per aspera ad astra e tudo mais...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Sim, vejo nos seus olhos que você tem novidades para mim. Estou todo ouvidos.";
				link.l1 = "Excelência, encontrei seu secretário desaparecido...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Você trouxe notícias de San Jose para mim, meu filho?";
				link.l1 = "Sim, Sua Excelência. Descobri o que aconteceu com nosso conhecido em comum, Miguel Dichoso, e sua fragata desaparecida. Assim que o navio dele entrou no Atlântico a caminho da Espanha, foi imediatamente pego por uma tempestade contrária e arremessado de volta ao Caribe.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pax vobiscum, meu filho... Em que posso ajudá-lo?";
				link.l1 = TimeGreeting()+", Sua Excelência. Tem alguma novidade sobre o nosso acordo?"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Você queria alguma coisa, meu filho?";
			link.l1 = "Não, nada, pai.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "Concordo, Sua Excelência. Cumpri as tarefas que me foram dadas. O senhor já tem o pirata covarde que roubou os vasos sagrados da Igreja. Agora estou devolvendo todos os itens que foram levados: a custódia, a cruz e o turíbulo. Fique com eles para a paróquia de Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Agradeço de coração pelo seu fiel serviço à Santa Madre Igreja e à paróquia de Santiago, meu filho. Suas ações não ficarão sem recompensa. Os paroquianos fizeram uma oferta para o bravo guerreiro que recuperou seus pertences roubados, e eu a entrego com prazer em nome deles. 'O trabalhador é digno do seu salário.'";
			link.l1 = "Muito obrigado, Vossa Excelência. Que surpresa agradável!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "O serviço fiel à Santa Igreja é sempre fielmente recompensado, "+pchar.name+". Eu, da minha parte, espero que você continue sendo um guerreiro dedicado à defesa e proteção da Cristandade, pois há uma ameaça mortal pairando sobre nós como a mítica Espada de Dâmocles.";
			link.l1 = "O que poderia ser isso, Vossa Excelência?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Talvez você esteja destinado a ser nosso campeão na batalha que se aproxima contra os poderes e principados das trevas deste mundo, meu filho, pois há muitos sinais e presságios de que algo maligno está chegando.";
			link.l1 = "Sinais e presságios?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Muitos, meu filho... Um deles é o seu desejo de buscar o ouro perdido dos índios pagãos de Tayasal, pois aquilo que guardam em seu tesouro é justamente o que representa perigo para todo o mundo cristão.";
			link.l1 = "Poderia me esclarecer um pouco sobre esse ouro, reverendo Padre? Já ouvi a história do seu desaparecimento, mas que tipo de ameaça o senhor menciona?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Escute com atenção, meu filho, e saiba que tudo o que está prestes a ouvir é só para os seus ouvidos. Muito antes de Miguel Dichoso tirar aquele tesouro pagão da antiga cidade indígena, eu já havia interrogado um homem cativo dos índios Itza sobre nossa missão no Caribe. O povo Itza é descendente dos maias, um império poderoso que se perdeu séculos antes mesmo de Cristóvão Colombo e seus homens pisarem no Novo Mundo. O Império Maia dominava as tribos vizinhas com mão de ferro, usando poderes indescritíveis que lhes foram concedidos por pactos infernais com demônios. Magias sombrias compradas com o sangue de gerações de sacrifícios humanos. \nEsse homem Itza sabia sobre Tayasal, uma cidade maia perdida e o mal incrível que ainda está selado lá dentro. Ele nos contou tudo o que sabia. Se esses selos forem abertos, as consequências seriam apocalípticas. Desde então, fiz tudo o que pude para impedir que esse mal terrível fosse despertado. Escrevi para o Escorial e para Roma, pedindo ajuda desesperadamente.\nEles ouviram e enviaram Dom Ramon de Mendoza y Riba, que estabeleceu sua base em Providência e começou a procurar Tayasal. Foi então que descobri que o bom Dom Mendoza tinha... motivações diferentes para encontrar a cidade perdida. Em vez de evitar o fim do mundo, ele queria servir a Mammon, não a Cristo.\nPor isso Deus o abandonou e enviou o anjo da morte para o acampamento dele. Todas as suas ações foram inúteis e só levaram à morte sem sentido de soldados espanhóis e índios convertidos fiéis. Escrevi ao Escorial pedindo a dispensa de Ramon de Mendoza por absoluta incompetência, e eles concordaram em afastá-lo de suas funções, mas...";
			link.l1 = "Miguel Dichoso chegou.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Exatamente. Aquele aventureiro enviado pelo diabo encontrou Tayasal junto com os tesouros dos antigos maias. No entanto, a alegria de Don Mendosa durou pouco. Todos esses tesouros desapareceram junto com o Dichoso a caminho da Espanha. É provável que, junto com todos os lingotes de ouro e ornamentos, Miguel tenha levado consigo uma fonte ancestral de feitiçaria, a máscara aterrorizante de um antigo deus-demônio maia chamado Kukulcan.";
			link.l1 = sTemp+"Mas que mal é esse de que fala, Vossa Excelência? Como sabe disso?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "É um mal que traz a morte para todos os cristãos batizados do Caribe, do Novo Mundo, e talvez até do Velho Mundo também. O fim virá como um ladrão na noite, e ninguém vai sequer perceber o que aconteceu. E já há sinais disso por toda parte!";
			link.l1 = "Que presságios? Eu não entendo...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Meu filho, você está mesmo tão cego que nem percebe? Isso já acontece há vinte e cinco anos, quase sem parar!";
			link.l1 = "Gostaria de mencionar humildemente, Vossa Excelência, que a duração da minha vida corresponde exatamente a esse período, sem falar que passei a maior parte dos meus anos na Europa. Minha ignorância deveria ser, de certa forma, perdoada.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Entendi. "+pchar.name+". Agora, você não percebeu coisas estranhas acontecendo pelo Caribe desde que chegou da Europa? Não acha curioso que feitiçaria, magia negra e outros rituais tenham muito mais poder aqui do que lá? Amuletos pagãos encantados por xamãs indígenas têm um poder real, que qualquer um sente só de segurá-los.\nAté nossos alquimistas cristãos – que Deus os faça enxergar o erro de seus caminhos! – já dominam a arte de criar objetos encantados. Eles não percebem que, ao fazer isso, estão servindo ao próprio Diabo. Você não sente a presença antinatural de algo infernal espreitando logo além do canto do seu olhar?";
			link.l1 = "Tem razão, pai. No começo isso me surpreendeu, mas agora acho que já me acostumei... Afinal, este é o Novo Mundo!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Mas nem sempre foi assim. A escuridão de que falo chegou aqui há uns vinte e cinco anos e fica mais forte a cada dia que passa. Isso só pode significar uma coisa: 'isso' já chegou, 'isso' está entre nós, e 'isso' está agindo...";
			link.l1 = "De quem você está falando? Quem é esse misterioso 'isso'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "O inimigo jurado dos cristãos, desejando a destruição da Igreja e de toda a cristandade.";
			link.l1 = "...Você está falando do Anticristo?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Se é 'o' Anticristo ou apenas 'um' anticristo, não vou me atrever a dizer. Não importa o nome que essa besta assuma quando se veste de carne mortal numa grotesca paródia da Encarnação do Nosso Salvador. O que importa é o que ela pretende fazer. Estou aqui para impedi-la, e você vai me ajudar. Mas acabamos nos empolgando demais. Você é um homem de ação. Provavelmente preferiria ir direto ao assunto e pular a teologia, certo?";
			link.l1 = "Pelo contrário, aprendi muitas coisas novas e importantes com o senhor, Vossa Excelência. Estou pronto para ouvir mais.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Você é educado e bem criado, meu filho. Isso é bom. Agora, voltando ao motivo pelo qual veio falar comigo. Nosso objetivo comum é encontrar os tesouros de Tayasal levados por Dichoso. Provavelmente conseguiremos achar uma arma entre esses tesouros que poderemos usar na batalha que se aproxima contra o Diabo.";
			link.l1 = "Mas será que o Dichoso já deixou o Caribe e agora está sentado em uma pilha de ouro lá na Espanha ?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Não. Eu tenho provas de que esses tesouros ainda estão aqui no Caribe. Você não precisa saber das minhas fontes por enquanto, só precisa confiar em mim. Além disso, acho que o Dichoso mentiu para o barão.\nA história dele sobre as ruínas de Tayasal não bate com o que meu índio Itza me contou durante o interrogatório. Sem falar que o fato de o Dichoso ter sido o único sobrevivente da emboscada dos Mosquitos foi conveniente demais.";
			link.l1 = "Imagino que Don Mendoza também acredita nisso, já que ele atacou Saint-Pierre tentando encontrar Dichoso?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "As ações do barão não devem te preocupar, meu filho. Ele é movido apenas pela sede de ouro e pelo próprio interesse. Sua ganância será uma pedra no seu pescoço, enquanto ao redor dele homens e mulheres de bem lutam contra as forças do Inferno.";
			link.l1 = "Você tem alguma pista de onde devemos procurar pelo Dichoso e o tesouro?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Eu penso nisso a todo momento, meu filho, mas não tenho nada específico para te contar. Mas há um homem aqui que pode nos ajudar, um filósofo natural de Gênova. Trouxe-o comigo para ajudar a catalogar coisas do Novo Mundo que pudessem ser úteis à missão da Igreja. Ele testemunhou o interrogatório do índio Itza e, pelo que pude perceber, o que ouviu o chocou e, de forma perversa, o atraiu.\nO Diabo usou sua curiosidade como uma armadilha e o possuiu, corpo e alma. O Senhor lhe deu grande talento para a medicina e a alquimia, mas nosso genovês caiu na tentação da magia negra e da feitiçaria. Ele conversou com meu prisioneiro Itza várias vezes sem minha permissão, depois desapareceu. Precisamos encontrá-lo e salvar sua alma.";
			link.l1 = "Imagino que sou eu quem deve encontrá-lo?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Sim, meu filho. Ele é o primeiro passo para encontrar o tesouro e a arma que podemos usar contra as forças do mal que nos ameaçam.";
			link.l1 = "Quem é esse genovês?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "O nome dele é Gino Gvineili. Tem trinta anos, mais ou menos. É um médico e alquimista talentoso. Como eu disse, agora ele estuda magia negra. Segundo minhas melhores informações, ele está escondido em alguma das colônias inglesas no Caribe.\nEncontre Gino Gvineili, meu filho. Se você conseguiu encontrar aquele pirata que roubou os objetos sagrados da nossa igreja, então também vai conseguir achar meu secretário fujão e trazê-lo até aqui. Vou rezar para que Santo Antônio interceda por você.";
			link.l1 = "Entendi, Sua Excelência. Não vou perder mais um minuto. Até logo!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Eu tinha plena certeza de que você diria isso, "+pchar.name+". Agora minha fé se fortalece ainda mais pela certeza de que você me foi enviado pela própria mão da Divina Providência. Onde está meu filho miserável e pródigo?";
			link.l1 = "Receio que você não vá gostar do que está prestes a ouvir, mas não tenho escolha. Seu secretário está morto.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Que Deus salve a alma dele e perdoe seus pecados... Como isso aconteceu, meu filho?";
			link.l1 = "Encontrei o Gino em Antígua. Ele estava escondido lá, em um dos prédios antigos construídos sob o laboratório. Não quis vir comigo de boa vontade. Quando ouviu seu nome e percebeu que eu estava disposto a usar a força, ele tirou um frasco de líquido transparente das dobras da roupa comprida e bebeu tudo de uma vez...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "E então algo terrível aconteceu: ele ficou vermelho, depois azul-escuro. Caiu no chão, convulsionando em espasmos, e em menos de um minuto morreu em uma agonia horrível. Um forte cheiro de amêndoas tomou conta do quarto.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Coitado... Até os últimos momentos da vida dele foram marcados pelo pecado, tirando a própria vida. Que perda trágica. Vou rezar pela alma dele...";
			link.l1 = "Depois que ele morreu, revirei a casa dele e encontrei este fólio lá. Será que pode te interessar, ou talvez nos ajudar na nossa busca? Tem umas anotações estranhas e esotéricas aqui...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "Este é o almanaque do pobre Gino. Ele fazia anotações aqui sobre todas as suas explorações. Dê isso para mim, meu filho, vou estudar o que está escrito. Talvez encontremos alguma pista.\nEmbora você não tenha trazido Gino Gvineili de volta para mim, estou satisfeito com seus esforços, meu filho. Agora tenho novidades para você.";
			link.l1 = "Estou ouvindo, pai.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Consegui informações de que a ilha de Trinidad foi o último lugar onde viram a fragata de Dichoso. Também sei uma data aproximada — início de abril de 1654.   Vá até Trinidad e tente descobrir qualquer coisa sobre o destino da fragata: para onde ela seguia, quais eram os planos do capitão, qualquer pista que você conseguir. Sei que já faz muito tempo e que a memória das pessoas tem limites, mas quem está se afogando agarra qualquer esperança.";
			link.l1 = "Vou fazer tudo o que estiver ao meu alcance.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Deixe-me ver sua carta de salvo-conduto. Vou acrescentar a permissão para você visitar a colônia de San José.";
			link.l1 = "Aqui.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Aí está... isso é tudo. Não se esqueça de hastear a bandeira espanhola no seu navio. Venha à frente e receba a bênção de Deus, meu filho!";
			link.l1 = "Um momento, Vossa Graça. Posso lhe fazer uma pergunta?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Sim, claro. O que você gostaria de saber?";
			link.l1 = "Na nossa última conversa, você mencionou um índio Itza que te contou sobre Tayasal. Tenho pensado muito nisso... Me diga, esse homem tinha algo com ele? Algum objeto, escrito, qualquer coisa assim? Isso pode ser útil.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Sem itens especiais, meu filho. Apenas uma tanga, algumas joias primitivas, um cachimbo de bambu com ervas e um pedaço de couro grosseiro usado como mordaça.\nTudo isso foi enviado para Don Ramon de Mendoza y Riba. Mas lhe garanto, não havia nada de interessante.";
			link.l1 = "Entendi. Obrigado, pai. Até a próxima!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Que o Todo-Poderoso te abençoe e te proteja... O que aconteceu com Miguel Dichoso? Você descobriu alguma coisa?";
			link.l1 = "Infelizmente, não consegui. A última coisa que as testemunhas puderam me contar foi que o Santa Quiteria foi levado por ventos fortíssimos na direção da Martinica. Ninguém sabe ao certo se o navio foi salvo ou se naufragou. Mas eu desconfio que Miguel Dichoso conseguiu escapar com vida.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "O que te fez decidir isso, meu filho?";
			link.l1 = "A chave é que a fragata estava escondida em algum lugar na direção da Martinica. E, bem recentemente, um cavalheiro destemido chamado Diego de Montoya, um dos homens do próprio Don Ramon de Mendoza, atacou Saint-Pierre com o objetivo de encontrar Miguel Dichoso, que supostamente estava se escondendo lá.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Então, o barão acha que o Dichoso se escondeu com os franceses...";
			link.l1 = "Conheço bem Saint-Pierre e o governador Jacques Dyel du Parquet, Vossa Excelência. Ninguém lá conhecia um espanhol chamado Miguel Dichoso. Pode me dizer como encontrar Diego de Montoya? Gostaria de falar com ele sobre Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Tem certeza de que ele estaria disposto a falar com você, meu filho? Acho que não, a menos que a conversa seja à base de espada e pistola.";
			link.l1 = "Será que o seu nome pode deixá-lo mais receptivo?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+". Duvido que o homem de confiança de Dom Mendoza estaria disposto a chegar a um acordo com você. Ordenar que ele venha a San Diego para uma audiência comigo pode ser uma opção, mas também não tenho certeza se Diego seria totalmente sincero comigo.";
			link.l1 = "O que faremos agora, pai?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Deixe-me sozinho por um tempo, meu filho. Preciso digerir o que você me contou e juntar tudo com o que já sei de outras fontes. Depois disso, vou lhe dizer qual será nosso próximo passo. Passe aqui mais tarde.";
			link.l1 = "Sim, Vossa Graça. Pode deixar. Vou dar notícias de tempos em tempos...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Deus te abençoe, meu filho... O que posso fazer por você?";
			link.l1 = "Tem alguma novidade, Vossa Excelência?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Agora não, meu filho. Mas não desanime. Eu e minha equipe estamos cuidando disso. Passe aqui mais tarde.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Sim, meu filho. Tenho algumas informações sobre Miguel Dichoso. Não foi em vão que acreditei que Dichoso ainda estivesse vivo e no Caribe. Parece que Don Diego de Montoya estava certo. Recebemos a confirmação de um homem que reconheceu Miguel Dichoso pelo rosto, dizendo que o cavalheiro desaparecido foi visto no assentamento pirata de Le Francois, na Martinica, em abril de 1654, depois do sumiço do Santa Quiteria...";
			link.l1 = "Então, a fragata naufragou nas costas da Martinica?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Calma, meu filho. No momento, não temos nenhuma informação sobre qualquer naufrágio em Martinica nessa época. E uma fragata não é uma chalupa. A destruição de uma fragata certamente teria chamado atenção e criado uma enorme oportunidade de pilhagem para os abutres locais.";
			link.l1 = "Será que vale a pena procurar pela costa e pelas praias para encontrar o que restou do navio?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Meu filho, Dom Diego de Montoya, já fez tudo isso e não obteve resultado. Continue ouvindo. Meus informantes em Providence dizem que o Barão tem certeza de que o Santa Quiteria ainda navega pelo Caribe, embora sob outro nome.\nPor isso ele está caçando Miguel Dichoso com tanta determinação. Segundo ele, o Santa Quiteria foi visto perto da Isla Tesoro, e recentemente apareceu sob bandeira inglesa, escoltado por um esquadrão militar.";
			link.l1 = "O quê? Isso é inacreditável. Disseram que seria impossível resistir a uma tempestade daquela magnitude... E agora a Santa Quiteria não só sobreviveu, como está navegando sob a bandeira inglesa? Essas duas coisas não batem. O que fez o Barão decidir que era mesmo a Santa Quiteria? Será que esse navio é realmente tão único assim?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ah, sim. Esta fragata foi construída com as técnicas mais avançadas da Europa. Ela está muito bem armada para a sua categoria, e sua velocidade permite escapar de qualquer um que tenha mais poder de fogo. Foi o que minha fonte me disse.";
			link.l1 = "E ela não se chama mais Santa Quitéria agora?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Isso, infelizmente, eu não sei... Vá para Isla Tesoro, "+pchar.name+", e tente descobrir algo sobre a fragata do Dichoso. Talvez assim a gente consiga encontrar o antigo capitão dela também, dois coelhos numa cajadada só. Ou dois ratos numa armadilha.";
			link.l1 = "Considere feito, Vossa Excelência!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Fico feliz que você tenha decidido me ver, meu filho.";
			link.l1 = "Olá, Vossa Excelência. Depois de me encontrar com Dom Alonso de Maldonado, nunca imaginei que voltaria a vê-lo.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Dom Alonso de Maldonado desobedeceu minhas ordens diretas. Eu havia proibido expressamente que ele te confrontasse, meu filho, pois sabia como isso terminaria para ele. E o que previ acabou acontecendo. A missão dele era te escoltar até Tayasal, já que ele já estivera lá antes.\nAlém disso, o esquadrão dele e uma companhia de soldados espanhóis deveriam te proteger de um ataque dos Itza ou dos Mosquitos. Alonso agiu de forma indigna, movido por um desejo egoísta de vingança.\nEle não só fracassou na expedição a Tayasal e condenou os soldados e navios sob seu comando, como também plantou em seu coração a semente da desconfiança e do ressentimento contra mim. Te asseguro, meu filho, estou totalmente do seu lado. Precisamos ficar juntos diante desta escuridão que nos cerca.";
			link.l1 = "Eu gostaria de acreditar nisso.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Fique tranquilo, "+pchar.name+". Eu, um servo leal e devoto de nosso Senhor e Salvador Jesus Cristo e representante de Sua Igreja, sou movido por um único propósito: impedir o fim do mundo até que todas as almas tenham a chance de ouvir a palavra de Nosso Senhor Bendito. E isso significa impedir que o artefato diabólico, atualmente nas mãos de um índio possuído por demônios, cumpra seu propósito. Eu suspeitava disso desde o início, e só agora tenho plena certeza. Você foi escolhido pelo Senhor como Seu campeão na batalha contra Satanás.";
			link.l1 = "Mas o que te faz dizer isso, pai?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Você conseguiu fazer algo que nem eu, com a ajuda de todos os meus agentes, nem o Barão Mendoza e Dom Diego, nem ninguém mais conseguiu. Você achou a maldita ilha e foi atrás do artefato de Kukulcán nela. Não foi?";
			link.l1 = "Sim, eu tenho a máscara de Kukulcán.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "E você diria que tudo isso aconteceu por acaso? Por coincidência? 'O coração do homem traça o seu caminho, mas o Senhor dirige os seus passos.' Meu filho, o Todo-Poderoso guiou você até aqui! Ele fortaleceu sua mão na batalha, conduziu seus passos pelo caminho certo e te protegeu nos momentos de perigo! 'Eis que a espada do Senhor desce para julgar Edom, sobre o povo que destinei à destruição!'";
			link.l1 = "Ehm... Pai, mas a missão já está praticamente cumprida. Eu tenho a máscara. Isso não significa que a casca possuída por Kukulcan não pode entrar na nossa história e mudá-la...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Você está enganado, meu filho. O demônio pode atravessar aquele portão com ou sem essa máscara. A máscara só facilita para ele realizar seus feitos sombrios. A única coisa que pode detê-lo é a destruição completa dos portões infernais.";
			link.l1 = "Don Alonso me disse a mesma coisa...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "E ele estava certo! Em nome de Nosso Senhor Jesus Cristo e de Sua Santíssima Mãe, eu te conclamo a empunhar a Cruz contra esse mal, meu filho! Você não pode recusar a grande missão que lhe foi confiada. Eu e toda a cristandade dependemos de você, meu filho.";
			link.l1 = "Excelência, isso é demais. Eu realmente me sinto... um tanto constrangido...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Sua modéstia é louvável, meu filho, mas agora não é hora de bancar o inocente envergonhado. Não seja covarde nem tema, pois o Senhor, seu Deus, vai à sua frente para lhe dar a vitória! Entre nessa batalha pelos seus entes queridos, por todos os cristãos... e, se não for por eles, então por você mesmo, porque se aquele demônio sair vitorioso, você perecerá junto com todos os outros.";
			link.l1 = "Acho que você me convenceu, pai. Eu estava em dúvida sobre minha situação em relação à expedição para Tayasal, mas agora não tenho mais nenhuma hesitação. Com o que você pode me ajudar?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Apenas dois homens sabiam como chegar a Tayasal: Alonso de Maldonado e Miguel Dichoso. Don Alonso está morto. E Dichoso... Disseram-me que ele foi visto recentemente em Sharptown, na Isla Tesoro. Talvez ainda esteja lá. Você precisa encontrar Dichoso e convencê-lo a ser seu guia.\nCom ouro ou pela força, faça esse homem levá-lo até Tayasal. Lá você encontrará os portões do inferno, e lá você irá selá-los.";
			link.l1 = "E quanto aos homens?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "A última companhia de soldados que tive estava sob o comando de Alonso de Maldonado. Infelizmente, não tenho como reunir outra tropa de soldados espanhóis. Já esgotei todo o meu crédito com a guarnição local. Você vai ter que se virar com seus próprios homens, meu filho. Mas vou te ajudar no que mais eu puder.";
			link.l1 = "Que tipo de ajuda?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Devemos aproveitar todas as vantagens que temos nesta luta, tanto materiais quanto espirituais. Pedi ao Padre Adriano que venha me encontrar nesta capela em cinco dias. Ele trará consigo amuletos sagrados para você. Amuletos que podem ajudar os guerreiros de Cristo na batalha. Ele também vai lhe fornecer todo tipo de poções. Quanto a mim, aceite esta lâmina, meu filho.\nEsta é uma espada antiga dos Cavaleiros Templários, uma arma formidável de nossos antepassados. Ainda afiada, brilhando com a bênção da Igreja. Só os maiores cavaleiros tiveram a honra de empunhá-la. Pegue-a, tenha orgulho dela, e esmague os inimigos de nossa Fé com o nome de Jesus Cristo nos lábios!";
			link.l1 = "Muito obrigado! Esta espada é simplesmente incrível. Estou sem palavras...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Deus te abençoe, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "Amém!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "E agora vá, meu filho. Que Deus te proteja, que Ele nunca te abandone, nem na sua busca, nem no seu caminho, nem na batalha. Procure por Miguel Dichoso e siga para Tayasal com a ajuda dele. Não se esqueça do Padre Adrian, ele vai te providenciar todos os amuletos e remédios de que você precisar. Agora é hora de eu voltar para Santiago. Adeus, meu filho. Vaya con Dios.";
			link.l1 = "Adeus, Padre Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
