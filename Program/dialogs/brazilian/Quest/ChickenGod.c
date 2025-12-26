int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax, 
				float  EnergyP,
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Você não deveria ver isso.";
			link.l1 = "Hora de relatar um problema.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, rapaz. Não quero ser indelicado, mas como você entrou aqui? Eu recomendei fortemente à Madame que fechasse o estabelecimento enquanto eu estivesse hospedado.";
			link.l1 = "Uh-oh mesmo. Como deixaram você entrar? Por que esse bordel ainda não foi queimado por gente furiosa e temente a Deus?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Os dobrões de ouro abrem todos os caminhos e deixam os homens brancos mais felizes. Não é mesmo?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Consigo quase sentir o cheiro do ar envelhecido de Versalhes, onde você entrou com aquele rangido.";
			}
			link.l1 = "Não fale assim comigo, cara vermelha. É verdade que sou novo aqui, embora eu não saiba como você descobriu. Eu poderia atirar em você bem aí onde está e arrumar qualquer garota para passar a noite só para compensar o incômodo.";
			link.l1.go = "native_var1";
			link.l2 = "Não sei quem te contou essa bobagem, mas você fala com muita desenvoltura, tenho que admitir. É a primeira vez que vejo um nativo tão instruído.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+" Versalhes, uma ova!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Não, Capitão, você não sabe de nada. Estou perfeitamente segura aqui... por enquanto. Mas já que ficamos tão próximos tão rápido, vamos tentar de novo. Um drink?";
			link.l1 = "Posso fazer isso, você definitivamente despertou meu interesse.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo! Vejo que já estamos nos tratando pelos nomes e trocando provocações. Agora, sugiro que brindemos à paz e falemos de negócios.";
			link.l1 = "Posso fazer isso, você definitivamente despertou meu interesse.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Considerando o propósito deste lugar, seu comentário, Capitão, me preocupa bastante! Já estou preso aqui há quase um mês. Já tentei de tudo que pude imaginar, e estou pronto para escalar a parede de tanto tédio e falta de sentido.";
			link.l1 = "Então vá embora. Visite uma igreja por uma vez... embora eles não vão deixar você entrar.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Não é tão simples assim, já que sou obrigado a passar mais vinte e quatro horas neste bordel, de acordo com o meu... contrato.";
			link.l1 = "Soa terrível, claro, mas não vai ter minha compaixão. Alugar um bordel só pra você por um mês é um sonho realizado!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Teme teus desejos, Capitão. Não faço ideia de como chegou aqui, porque eu devia passar este mês sozinho. Sozinho com mulheres e vinho, mas lá pelo terceiro dia, só consegui ficar com o vinho. E hoje foi o dia em que até disso me cansei.";
			link.l1 = "E o que você quer que eu faça? Dividir um monte de garotas e vinho com você?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Talvez, mas eu sugiro que a gente aposte primeiro! Mil pratas por carta! Ah, meu nome é Agueybana, aliás.";
			link.l1 = "A minha é "+GetFullName(pchar)+". Claro, vamos jogar.";
			link.l1.go = "native_accept";
			link.l2 = "A minha é "+GetFullName(pchar)+" Mil pesos? Nada mal. Vou pensar no assunto, mas não prometo nada.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Mudou de ideia, capitão? Vamos?";
			link.l1 = "Claro, por que diabos não.";
			link.l1.go = "native_accept";
			link.l2 = "Ainda não.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Obrigado pelo jogo, capitão. Achei que isso fosse me fazer sentir melhor, mas não fez. Por favor, me deixe em paz – de algum jeito vou me virar mais um dia sozinho. Maldito seja aquele desgraçado!";
			link.l1 = "É só isso? Admito que minha decepção é maior do que a amargura de perder uma boa quantia de dinheiro.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Você nem deveria estar aqui, capitão. Mas se faz tanta questão de saber do que se trata... procure por um templo antigo no continente. E leve bastante tuunich kaane'. Aqui, fique com um.";
			link.l1 = "Uma pedra de cobra? Uma pedra com um buraco realmente combina com o lugar. Obrigado, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Até logo, capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Vixe! Obrigado, capitão! Uma pena pelo dinheiro, mas pelo menos voltei a sentir o gosto da vida!";
			link.l1 = "É, nunca vi ninguém ficar tão animado com uma rota dessas. Aliás, de onde veio todo esse dinheiro?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Que pergunta grosseira, capitão! Você jamais faria isso a alguém do seu nível. Mas a noite ainda é jovem, e ainda tenho bastante dinheiro. Que tal uma revanche?";
			link.l1 = "Por que diabos não? Vamos fazer mais uma!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Eu sugiro que desta vez joguemos dados e aumentemos um pouco as apostas. Também tenho uma história pra te contar, então alugue um quarto lá em cima pra nós dois. Tem ouvidos demais aqui! Eu agradeceria se você pudesse ir até a Madame e pagar pelo quarto. Infelizmente, meu crédito não cobre você.";
			link.l1 = "Alugar um quarto? Para dois? Aqui? Maldito seja, Agueybana! Estou fora daqui!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Ah, quer saber? Essa história vai acabar ou como uma boa anedota, ou como um banho de sangue bem caro. Minha espada fica comigo, então nada de gracinha, ha-ha! Espere aqui, vou resolver isso.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "E aí?";
			link.l1 = "Espero sinceramente que você tenha me chamado aqui só para beber e jogar.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Não se preocupe, capitão, não tenho interesse nessas bobagens! Mas, se você tivesse aparecido aqui no primeiro dia... ha ha! Vamos começar?";
			link.l1 = "Fortes fortuna adiuvat!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uau! Isso foi bom! Parabéns pela vitória, Capitão.";
			link.l1 = "Não exagere. Agora é a sua vez de me explicar que diabos está acontecendo aqui?";
			link.l1.go = "native_dice_story";
			link.l2 = "Você é estranho, Agueybana. Agora, se eu não sair daqui imediatamente, minha reputação como nobre e como homem ficará irremediavelmente manchada. Me dê minha prata e vamos cada um para o seu lado.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Que pena, eu estava esperando terminar o dia de outro jeito...";
			link.l1 = "É a primeira vez que vejo um homem tão incomodado por ganhar esse jogo de plebeu. Pode ao menos me explicar agora que diabos está acontecendo aqui?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Vai se ferrar, Agueybana! Já cansei disso!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "O máximo que eu puder, capitão. Não sei se devo, mas mesmo assim, você iluminou meus últimos dias... Neste bordel, quero dizer.";
			link.l1 = "E o que foi isso tudo?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Deixa pra lá... Escute aqui, homem branco! Eu sou o grande chefe do povo Taíno, Agueybana. Às vezes sonho que nasci cem anos antes e expulsei os invasores espanhóis das minhas ilhas! Mas, em vez disso, vendi três mil dos meus para as minas por dez dobrões cada um.";
			link.l1 = "Uma biografia digna. De repente me deu vontade de te dar um tiro, Agueybana, e te deixar apodrecendo nesse buraco fedorento de vinho azedo.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Tanto faz, capitão. Tudo o que eu sempre quis era ser como você.";
			link.l1 = "Como eu?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Já vi seus navios – verdadeiras maravilhas do engenho humano – e desejei ter um só pra mim. Vi suas mulheres em espartilhos apertados, e sonhei em tirar um com minhas próprias mãos. Vi até os piores dos seus comandantes com um poder que nenhum dos nossos líderes jamais sonhou. Ouvi histórias sobre a Europa e aquelas enormes casas de pedra onde as pessoas vivem de verdade, não só sobrevivem. E eu tive tudo isso! Mais ainda, estive na Europa e vi tudo isso no ano passado!";
			link.l1 = "Você já bebeu vinho demais, chefe. O único bilhete para a Europa que você conseguiria seria acorrentado, para a alegria do Vaticano e dos artistas de rua. O que você está dizendo é simplesmente impossível no mundo em que vivemos.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "Esse é o mundo em que vivemos, capitão. Já me disseram que o nosso mundo é errado, imaginário, e que qualquer coisa é possível.";
			link.l1 = "E quem foi o engraçadinho que te contou isso? Pelo visto, não te deixam entrar só em bordéis, mas em hospícios também!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Agora estamos chegando ao ponto da minha história. Você sabe como as coisas funcionam por aqui, não sabe? Espanhóis e ingleses pagam pelos nossos prisioneiros de guerra com armas, ferramentas e pólvora. Eu paguei pelos homens da minha tribo com o seu dinheiro. Por que você acha que é assim?";
			link.l1 = "Sinto que você está prestes a me iluminar.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Somente os deuses podem satisfazer nossos desejos mais profundos e vergonhosos. Se você não consegue viver a vida que quer, então peça para eles interferirem no destino. Só eles podem realizar nossos desejos mais secretos e vergonhosos. É assim que funciona. Mas aí está o problema: quase todos os nossos deuses já estão mortos, e mesmo quando estavam vivos, nunca se importaram com ouro. Por sorte, a natureza detesta o vazio, e um novo deus apareceu em uma das velhas pirâmides. Ele não se importa com quem você é: seja local ou europeu, vilão ou herói – basta pagar e você recebe o que pediu! Todas as tribos sabem disso, e alguns dos seus também. Eu paguei o preço em ouro e vivi como um de vocês. Amanhã faz um ano.";
			link.l1 = "Que deus? Para a Europa e de volta em um ano? E o ponto alto da sua viagem foi um bordel qualquer no Caribe? Ah, que se dane. Isso parece história de bêbado, e vou acreditar nela assim mesmo. Vamos beber e continue com sua história.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Tudo o que te contei é verdade. Não há mais nada para dizer.";
			link.l1 = "Você ainda não viveu tempo suficiente no nosso mundo, Agueybana. Toda história inspirada pela bebida, principalmente as contadas de boca cheia num bordel, precisa terminar com uma lição. Com certeza devemos filosofar antes de encerrar de verdade nosso salão.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Como elas geralmente acabam?";
			link.l1 = "Não sabe? Depende do gênero do participante, é claro! Troca socos com os homens, leva as mulheres pra cama. Às vezes a moda manda fazer o contrário, viu. Então, qual é a moral da sua fábula? Dinheiro não traz felicidade? Que tédio!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Essa não é a moral da minha fábula, como você disse. Mas já que você tocou no assunto, sinto que preciso dizer que não concordo com o seu ponto de vista. Pelo contrário, acredito que o dinheiro compra felicidade e torna as pessoas melhores.";
			link.l1 = "Besteira! Agora parece que você está se contradizendo. Você acumulou uma fortuna considerável negociando com o seu próprio povo. Lembra quanto lucrou ao todo? Quase trinta mil moedas de ouro? Pense um pouco, mas pra mim está claro que o dinheiro não te trouxe felicidade. Mas pelo menos te comprou esta bela suíte.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Certo, vou ajustar meu ponto inicial: o dinheiro melhora a vida e as pessoas.";
			link.l1 = "Assim está melhor, mas o que te faz pensar que isso torna as pessoas melhores? Então agora você é um exemplo de virtude? E quanto àqueles que não têm muito dinheiro? Vamos chamá-los de gente ruim?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Sabe, capitão, eu realmente aprecio essa conversa. Deixe-me esclarecer mais uma vez: o dinheiro melhora a vida e as pessoas, mas só aqueles que já têm uma centelha de virtude.";
			link.l1 = "Ouçam, ouçam! Então, nada de faísca pra você, hein?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Não. Eu era o chefe do meu povo e, diferente do dinheiro, o poder definitivamente corrompe os homens. Sabe de uma coisa, capitão? Olho pra você agora e percebo que um dia você vai encarar o mesmo dilema.";
			link.l1 = "Seu deus também te deu o dom da vidência? Então vá para Santiago, ouvi dizer que lá eles têm um interesse especial por médiuns e adivinhos de todo tipo.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Vamos terminar o nosso... aham, salão sem recorrer a brigas ou camas, por favor. Não consegui encontrar uma moral para minha história, então gostaria de propor um brinde.";
			link.l1 = "Você está completamente perdido, chefe. Mas numa coisa, você tem razão. Vamos só tomar um drink!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Que nossos desejos estejam sempre à altura das nossas necessidades. Obrigada, Capitão, esse é um final digno para... nossa noite. Se algum dia quiser comprovar a verdade da minha história, vá até o continente e encontre um templo antigo por lá. Leve consigo cento e treze tuunich kaane'. Eu tenho noventa e nove sobrando – fique com eles, e adeus!";
			link.l1 = "Um monte de pedras furadas? Combina bem com este lugar. Obrigado pela noite, Agueybana. Será que vou te ver de novo?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Não, você não vai. Tchau, capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Entendi, capitão. Para o bem ou para o mal, vou te dar uma dica sobre o tesouro. Afinal, você trouxe um pouco de luz para meus últimos dias... Neste bordel, quero dizer. Procure por um templo antigo no continente e leve uma pilha de tuunich kaane' até lá. Aqui, fique com um.";
			link.l1 = "Uma pedra de cobra? Que curioso, e uma pedra com um buraco combina mesmo com este lugar. Já cansei do seu jeito comigo!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Eu entendo que você está chateado, capitão. Para o bem ou para o mal, vou te dar uma dica sobre o tesouro. Afinal, você trouxe um pouco de luz aos meus últimos dias... Neste bordel, quero dizer. Procure por um templo antigo na grande terra e leve um monte de tuunich kaane' até lá. Aqui, pegue um.";
			link.l1 = "Uma pedra de cobra? Que encantador, e uma pedra com um buraco combina mesmo com este lugar. Já cansei do seu tratamento!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Adeus, capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Mais um? Ah, pelo amor de Deus, já estou de saco cheio de todos vocês!";
			link.l1 = "A-a-ah! Vá embora!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Ah? Isso, certo. Ajoelhe-se diante de mim, mortal! Contemple o poder da minha pirâmide!";
			link.l1 = "(grita desesperadamente)";
			link.l1.go = "joruba_2";
			link.l2 = "(mate o monstro)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Isso mesmo. Bem-vindo à minha humilde factoría, capitão.";
			link.l1 = "O-o que você é?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Admiro sua persistência. Qual vai ser o próximo passo, capitão? O que acha de fazer umas trocas?";
			link.l1 = "O-o que é você?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Não importa o que eu sou, o que importa é a função que desempenho. Neste momento, estou negociando acordos comerciais com os habitantes deste buraco para benefício mútuo.";
			link.l1 = "O buraco de rato? Você quer dizer este templo?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Your first and final warning, captain! However, this pyramid is indeed rather cramped; obviously, I've outgrown it.";
			link.l1 = "Você mencionou comércio. Que tipo de negócio você quer dizer?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Eu dou às pessoas o que elas mais precisam.";
			link.l1 = "Você realiza desejos? Como um gênio de conto de fadas? Meu Deus, o que está acontecendo aqui?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Não seja absurdo! Eu só ajudo as pessoas a conseguirem o que vieram buscar neste mundo da forma mais rápida e agradável possível.";
			link.l1 = "Você é algum tipo de xamã ou coisa assim?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Bem, você conheceu Agueybana, isso já deve te dar algumas ideias.";
			link.l1 = "Aquele pobre índio perdido e bêbado foi obra sua?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Não fui eu quem vendeu a tribo dele por algumas milhares de libras em ouro, não fui eu quem enfiou barris de bebida pela goela dele abaixo, e certamente não fui eu quem o obrigou a pegar toda doença, conhecida e desconhecida, de centenas de prostitutas. Ele me pediu para transformá-lo em um aristocrata branco, então eu fiz. Como o destino dele me ordenou.";
			link.l1 = "Você realiza desejos? Como um gênio de conto de fadas? Meu Deus, o que está acontecendo aqui?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Não seja absurdo! Eu só ajudo as pessoas a conseguirem o que vieram buscar neste mundo da forma mais rápida e agradável possível. Agueybana deveria salvar seu povo do jugo dos invasores europeus, mas em vez disso, ficou babando demais pelo espartilho da filha do comandante e resolveu penhorar o próprio.\nA partir daí, o único sentido que restou na vida dele foi perceber a profundidade do erro e recomeçar logo. Um ano na Europa, cirrose e o tempo que vocês dois passaram num bordel devem ter ajudado. Mas admito, ele teve umas férias e tanto, ha ha!";
			link.l1 = "Cirrose-o quê? Você é algum tipo de xamã ou coisa assim?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Ou algo assim. Mas você vai gostar da minha proposta. E, para variar, vou ficar realmente feliz em ajudar.";
			link.l1 = "Certo. Quanto?";
			link.l1.go = "joruba_9A";
			link.l2 = "Por quê? Eu sou especial?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Nada mal, capitão. Ou você é esperto ou tão burro quanto um jumento, mas suas chances acabaram de aumentar um pouco. O preço não vai ser problema.";
			link.l1 = "Você precisa matar alguém? Eu não faço esse tipo de coisa.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Porque o seu propósito nesta vida é encher de buracos um bom amigo meu, ha ha!";
			link.l1 = "Você quer que eu mate alguém? Não faço esse tipo de coisa.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Primeiro, você faz. Segundo, vamos realizar quatro grandes negócios e mais quatro menores. Cada um deles vai te deixar muito mais forte e aumentar suas chances neste mundo cruel e estranho. Se você fechar todos os acordos, eu garanto que um dia será capaz de sair por aí e enfrentar deuses de igual para igual, sem falar dos simples mortais.";
			link.l1 = "Parece divertido. Me conte mais sobre isso.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Escolha inteligente! Normalmente, meus discursos acabam com gente sendo levada para Blueweld achando que teve um ataque do coração, mas você está aguentando firme. Aqui está a lista de tarefas: alguns serviços de troca que espero que você resolva. Sem prazo, hehe.";
			link.l1 = "Curioso. Vou ler a lista depois. Mais alguma coisa?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Sim, a primeira grande transação. Dois mil dobrões é o preço.";
			link.l1 = "Talvez eu aceite... Mas isso é muito dinheiro! Por que você precisa de tanto? Posso pagar em pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "Você ficou louco? Com esse dinheiro eu poderia comprar uma fragata!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "A pirâmide precisa de reparos – a alvenaria às vezes cai na cabeça dos clientes e isso é péssimo para os negócios. Meus homens remendam tudo todo dia, mas nossa organização precisa urgentemente de dinheiro de fora para resolver isso de vez. Quanto aos pesos – não me agradam muito, já que o câmbio deles é bem instável.";
			link.l1 = "Você está sendo bem injusto com pesos honestos... Espera aí, você não está sozinho aqui?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Não, eu sou só a fachada de uma organização séria. Então, vai topar?";
			link.l1 = "Vou pensar no assunto, mas antes, quero saber o que estou recebendo por uma quantia tão alta.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Por que estragar a surpresa? Além disso, encare esse dinheiro como um imposto. Sua conquista mais valiosa será liberar os próximos negócios. As recompensas serão divinas. E únicas, veja bem, pois você não vai encontrá-las em nenhum outro lugar!";
			link.l1 = "Certo. Qual é mesmo o seu nome?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba, a Magnífica. Só mais uma coisa, "+pchar.name+", a entrada na pirâmide é permitida apenas uma vez por dia. Não faça os outros clientes esperarem e não venha me incomodar à toa.";
			link.l1 = "Não vejo ninguém fazendo fila... Adeus, sua majestade.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ah, capitão. O que você tem para mim?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Então fica para a próxima.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Nada mal, vou fazer bom uso desse ouro. Aqui, um pequeno amuleto que já pertenceu a um chefe Taíno muito virtuoso. Ajuda a carregar montes de ouro. Certamente ajudou ele, heh-heh...";
			link.l1 = "Obrigado, e espero não me arrepender. Qual é o próximo acordo?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Espera aí. Eu te dei uma pilha de ouro e recebi um pedaço de barro em troca? Quero meu dinheiro de volta!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "É? Sim, o próximo negócio. Este ouro deve bastar por enquanto, então é hora de pensar em bens mais espirituais. Preciso encontrar uma cura para mim.";
			link.l1 = "Por quê, você está se sentindo mal?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Minha alma está. Veja, os padres evitam minha humilde pirâmide desde aquele incidente com a Inquisição, então precisamos recorrer a métodos mais tradicionais. Eu preciso, bem, minha factoría precisa de quinze plantas de magarosa para continuar funcionando.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Isso é uma erva?";
			} else {
				link.l1 = "Eu sei o que é isso, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Vou ser honesto - é uma erva rara e de grande valor. Pense bem se você realmente vai passar anos coletando-a por todo o arquipélago.";
			link.l1 = "Não prometo nada, mas desejo boa saúde a você e espero que minha recompensa pela erva valha a pena.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "All right, I am officially calling it my day off! A bargain such as this is worth a real treasure. Behold!\nThis machete was once this close to splitting that imbecile Kanek's head! Therefore, it's very dear to me and I humbly ask you to take good care of it. It's old, but crafted extremely well; they don't make steel like this anymore.";
			link.l1 = "Kanek? Quem é esse?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Ah, vocês dois vão se encontrar. Agora, espero que você não seja um desses idiotas pomposos que desprezam trabalho manual? Se for, azar o seu, porque a segunda parte da recompensa são os esquemas para munição de carga dupla.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Ah, eu adoro essas coisas. Mas o que elas têm de especial? Uma carga dupla de pólvora não é novidade, então concluo que você claramente não saiu da sua pirâmide desde os tempos daquele facão de museu.";
			} else {
				link.l1 = "É só isso? Ei...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Não seja espertinho e preste atenção! Qualquer idiota pode encher um barril com dois montes de pólvora e arriscar ficar cego, queimar o rosto ou quebrar o nariz. Eu te ensino um truque: confira bem a qualidade da pólvora, moa até o ponto certo, coloque uma bala ou chumbo grosso e acrescente um dobrão picado. O estrondo vai despedaçar até uma couraça!";
			link.l1 = "Jogando dinheiro fora, hein? Bem a sua cara.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Você é insuportável! Tá bom, pega um morteiro de mão e uma dúzia de granadas pra ele também. Se você é tão esperto assim, vai conseguir os esquemas das granadas sozinho rapidinho!";
			link.l1 = "Muito obrigado, meu senhor. O que vem agora?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Você não vai gostar. Eu preciso de um navio... não, eu preciso do navio. Sabe, daqueles que têm uma história por trás.";
			link.l1 = "Por quê? Você nem é capitão.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Isso não te diz respeito! É melhor você se concentrar na sua recompensa, porque eu poderia muito bem te mandar limpar essa pirâmide de cima a baixo por isso, e ainda assim você me ficaria devendo!";
			link.l1 = "Você definitivamente não é um capitão, senão saberia que um navio precisa de um cais ou uma baía para atracar. Como diabos você espera que eu coloque um navio dentro da sua pirâmide?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Você reparou num lago gigante atrás da minha pirâmide, por acaso? Isso mesmo. É só atracar o navio certo no esquadrão ali perto que meus homens cuidam do resto. Agora cai fora daqui, você está atrasando a fila.";
			link.l1 = "Mas é claro. Adeus!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Ótimo! Entendido!";
			link.l1 = "Para de bancar o espertinho e me dá minha recompensa!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "E os outros dois? Não podia ter guardado pra você? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "E os outros dois? Não podia guardar pra você? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "E os outros dois? Não podia ter guardado pra você? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Porra, estou impressionado que você não quis ficar com ela pra você. Isso sim é o que eu chamo de um navio com história! Droga, William... Eu queria mesmo que você voltasse pra casa e abrisse um grande banco, como sempre sonhou.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Olhe só para isso! Você é uma vergonha para o seu posto, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince decidiu se livrar das provas comprometedoras na minha velha pirâmide? Eu aprovo!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Boa sorte explicando aos seus superiores a perda do navio-capitânia, Almirante. Ah, me perdoe, Governador-Geral.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Você é supersticioso ou só um tolo mesmo? Ela vale uma fortuna! Não sei se é uma troca justa, mas tanto faz.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Você é supersticioso ou só um tolo mesmo? Ela vale uma fortuna! Não sei se é uma troca justa, mas tanto faz.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Você é supersticioso ou só um tolo mesmo? Ela vale uma fortuna! Não sei se é uma troca justa, mas tanto faz.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Boa escolha! Eu adoro os castelhanos, sabia? Talvez eu a devolva pra eles quando terminar.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "De fato, você não tem coração, Capitão. Este navio exala traição. Eu vou ficar com ele.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "É, este navio pode até ter uma história... mas não foi fácil demais de conseguir? Ah, tudo bem. Seu caso é especial, minha querida, então vou aceitar. Pelo menos me faz lembrar dos meus tempos de juventude.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "É, esse navio pode até ter uma história... mas não foi fácil demais conseguir? Ah, quer saber, dane-se. Certo, capitão, vou deixar passar dessa vez, já que você mandou bem nas tarefas da minha lista. Eu fico com ele. Pelo menos me traz umas lembranças dos meus tempos de juventude.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "E já viu o padre? Bem, vai conhecer. E é melhor se preparar com cargas duplas para a pistola. Se isso não resolver, tente uma estaca de madeira.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "E já viu o padre? Bem, vai conhecer. E é melhor se preparar com cargas duplas para a pistola. Se isso não resolver, tente uma estaca de madeira.";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "E você já viu o padre? Bem, você ainda vai conhecê-lo. E é melhor se preparar com cargas duplas para a pistola. Se isso não resolver – tente uma estaca de madeira.";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "É, esse navio pode até ter uma história... mas não foi fácil demais conseguir? De jeito nenhum! Você ainda tem um monte de tarefas inacabadas na lista. Quando terminar tudo, a gente volta a falar desse sacrifício.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Eu te abençoo, "+GetFullName(pchar)+". Que o mar esteja a seu favor. Agora, vamos discutir a próxima transação...";
			link.l1 = "Como assim? Nem os caipiras mais bobos caem numa besteira dessas na nossa era da razão! Eu não coloquei um centavo na sua caixinha de caridade, eu te dei um navio de guerra de verdade!";
			link.l1.go = "joruba_insult";
			link.l2 = "Espere um segundo. O que exatamente a sua bênção significa para mim?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "A partir de agora, qualquer navio que você comandar terá um casco mais resistente, enquanto seus inimigos vão sofrer o contrário. Além disso, o tempo no mar vai passar mais devagar para você. E se isso ainda não for suficiente pra você botar esse buraco inteiro de joelhos, é melhor correr pro seu papai e pedir o dinheiro de volta!";
			link.l1 = "Se isso não funcionar, juro que volto aqui esta noite e queimo a sua pirâmide! Agora, me fale sobre o próximo negócio!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Está começando a gostar disso, hein, capitão? Pois saiba que eu também. Por que acha que escolhi essa pirâmide para ser meu escritório?";
			link.l1 = "Provavelmente porque a caça às bruxas ainda está acontecendo?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, não, não exatamente. Eu faço meus negócios aqui porque os melhores acordos exigem sangue. Esta pirâmide exige sangue. Eu exijo sangue. Sempre foi assim, e sempre será.";
			link.l1 = "Nem pense nisso, seu monstro. Eu não vou entregar vítimas para você matar!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "E quantos você já matou, hein? Espere, vou até te dizer o número exato: você, pessoalmente, matou "+(Statistic_AddValue(pchar,"Solder_s",0)+Statistic_AddValue(pchar,"Citizen_s",0)+Statistic_AddValue(pchar,"Warrior_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Citizen_g",0)+Statistic_AddValue(pchar,"Warrior_g",0))+" pessoas! Vocês ergueram uma montanha de cadáveres no altar da sua ambição e sede de riqueza! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"A dívida do seu irmão já matou mais gente do que uma guerra europeia comum! ";
			}
			dialog.text = dialog.text+"Nem venha querer me dar lição de moral aqui, ainda mais porque não vou te julgar. O sucesso de uns sempre é pago com as tragédias de outros, e os deuses, ah, os deuses, eles vão estar de olho e cobrando a parte deles!";
			link.l1 = "Eu não posso te dar uma resposta agora... Preciso sair daqui.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Está precisando urgentemente clarear a cabeça? Tudo bem, mas antes, me escute. Eu lhe darei poder e controle total sobre seu corpo e mente, se você me trouxer um homem de grande valor. Não um figurante, não um rato cinzento e sem rosto das ruas ou um desgraçado dos porões fedorentos. Traga-me um homem que o siga e desempenhe um papel importante na sua tragicomédia.";
			link.l1 = "Um dos meus oficiais? Você não podia ter caído mais baixo, Aruba! Se isso se espalhar...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Vou cuidar do sigilo como sempre faço. E antes que você comece a reclamar de novo, já aviso que existe outro jeito.";
			link.l1 = "O que isso quer dizer? Então eu não preciso arrastar meu próprio povo até o altar?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Não, mas você não vai gostar da alternativa. Se não quiser pagar com sangue, pode pagar com ouro. Três mil dobrões e a consciência limpa. O dinheiro faz isso e muito mais – eu adoro!";
			link.l1 = "Adeus, Aruba. Não quero mais falar com você.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Você sabe onde me encontrar.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Vamos fazer isso rápido antes que a Inquisição Espanhola apareça. Sangue ou ouro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Ouro, então. Aqui estão seus três mil, embora eu não consiga imaginar como você poderia gastar uma quantia tão enorme neste fim de mundo.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Sangue.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Deixa pra lá.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Terminou? Vamos falar sobre a minha recompensa.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Que assim seja. Diga o nome.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand não é um oficial, mas sim um mercenário implacável, então escolha outra vítima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Eu aceito o seu tributo. Você não precisa assistir.";
			link.l1 = "Não, não sei. Voltarei para buscar minha recompensa em uma hora.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Ótima escolha. Eu detesto limpar todo aquele sangue do altar, então prefiro ouro. Aqui, pegue esta poção – um presente de um bom amigo meu.";
			link.l1 = "O sabor não é nada ruim...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Terminou? Vamos falar sobre a minha recompensa.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Fale comigo sempre que quiser mudar o seu destino.";
			link.l1 = "Mas o que exatamente isso significa para mim?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Poder sobre si mesmo! Experimente algum dia e vai adorar. Enquanto isso, deixa eu te contar sobre a próxima transação. A mais importante.";
			link.l1 = "Já não tenho mais certeza se isso vale a pena!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Vamos, fala logo.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Você tem a oportunidade não só de mudar o seu destino, mas de se juntar aos gênios e deuses do nosso tempo. Sim, agora você pode transformar seu corpo e mente o quanto quiser, mas nunca vai ultrapassar seus próprios limites, pois uma pessoa comum não pode ser excelente em tudo. O que estou propondo é que você quebre essas barreiras.";
			link.l1 = "Quanto isso vai me custar? Mais sangue? Ouro?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Certo. Ou você me traz vinte e cinco mil dobrões ou um dos seus companheiros. Depois que terminarmos, não haverá mais negócios.";
			link.l1 = "Vou pensar nisso.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Você sabe onde me encontrar. E não hesite em me procurar sempre que quiser mudar o seu destino.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Como quiser.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Primeiro de tudo, essa é minha esposa, não uma noiva. Segundo, o seu problema é com os castelhanos, não comigo. E por fim, eu já a levei e dispensei seus homens. E quanto às intenções honrosas... Olhe para mim, não sou eu o próprio exemplo de um cavalheiro decente? Tlazolteotl, abençoe-o, para que um dia ele também conheça uma mulher de verdade. Ou um homem.";
			link.l1 = "Vai pro inferno, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Nada mal, obrigado. Para ser sincera, eu realmente não preciso disso, mas talvez eu use em algum salão ou sei lá. Em nome de Ishtar, eu te abençoo. Agora vá e peque.";
			link.l1 = "Que sensação estranha...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Eu vou levá-los. O quê? Eu também preciso de homens mortos na minha tripulação, assim como você, só que ao contrário de você, não posso sair por aí recrutando em tavernas. Agora, Bast, abençoe o herói em suas futuras empreitadas.";
			link.l1 = "Que sensação estranha...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "É, vamos ter que espalhá-las de novo, porque as pessoas vivem perdendo, e precisamos de clientes. Freya, proteja esse grande colecionador de pedras.";
			link.l1 = "Que sensação estranha...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Vamos fazer isso rápido antes que a Inquisição Espanhola apareça. Sangue ou ouro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Deixa pra lá.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Diga o nome.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "Isso é bem tentador, mas vou abrir uma exceção só desta vez – não vou aceitar seu sacrifício. Não vou contar isso para o seu "+sTemp+", mesmo que eu provavelmente devesse. Lembre-se de que você não é nada sem ela. Agora, suma daqui e não me incomode hoje.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand não é oficial, mas sim um mercenário implacável, então escolha outra vítima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Que assim seja. Aqui, pegue esta poção – um presente de um bom amigo meu.";
			link.l1 = "O sabor não é nada ruim...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Até a próxima, capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Enfim, acabou tudo!";
			link.l1 = "Hã?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Terminamos aqui, Capitão. Os acordos foram fechados, todos estão satisfeitos, e não há espaço para reembolsos. Nosso escritório está encerrando as atividades e se mudando.";
			link.l1 = "Espere um momento, Aruba. Já te dei muito ouro, pago com sangue, trouxe mulheres e prisioneiros para este covil infernal. Consigo lidar com eventos sobrenaturais que aparentemente acontecem no Caribe. Mas as nossas 'transações' com você desafiam toda a lógica. Por favor, explique.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Alguém está te prendendo aqui? A saída está bem ali, gênio!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Você está absolutamente certo, ninguém está me prendendo aqui. Não mais. E tudo isso graças a você, meu amigo.";
			link.l1 = "Que mudança repentina de opinião. Eu esperava ouvir uma história, mas até agora só escutei os desvarios sem sentido de um deus mesquinho preso numa pirâmide empoeirada.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Bem, todo mundo precisa desabafar de vez em quando, não é? Fico realmente feliz que você tenha vindo aqui porque, graças a você, finalmente posso partir deste mundo. Ouro, tripulação, equipamentos e um navio, meu amigo. Lembra? Soa familiar? Era só disso que eu precisava, e você me deu tudo.";
			link.l1 = "De nada. Mas isso ainda não explica esse seu jeito estranho de falar e esses poderes quase divinos. Se você é tão poderoso assim, já podia ter criado seu próprio navio, tripulação e ouro faz tempo!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Foi o que eu fiz, como pode ver. Cada um tem seus próprios métodos.";
			link.l1 = "Mas como assim? Quem é você, afinal?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Bem... é simplesmente o que eu faço. Nos vemos no novo mundo, "+GetPersonaName()+". Da próxima vez, espero que seja realmente algo novo. Obrigado e até logo.";
			link.l1 = "Não, eu nunca mais quero te ver.";
			link.l1.go = "exit";
			link.l2 = "Então até mais, Aruba... isso foi interessante.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Parece que todos os acordos foram cancelados. Hora de ir, capitão.";
			link.l1 = "Hora de você se f...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "Em nome da Inquisição Espanhola, diga seu nome!";
			link.l1 = "Capitão "+GetFullName(pchar)+". E é verdade o que dizem, ninguém espera a Inquisição Espanhola...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Essa piada nunca perde a graça, embora já tenha levado muitos cristãos inocentes à fogueira.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Brincadeira, Capitão. Você fez uma piada, eu também. Meu nome é Padre Emilio Bocanegra, e esses soldados de Cristo são meus guardas armados.";
			link.l1 = "O que posso fazer por você, padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Você conhece um tal de senhor Aruba?";
			link.l1 = "Sim, ele morou nessa velha pirâmide até pouco tempo atrás.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "O que você quer dizer com 'ele morava lá'? É possível viver lá? E por que 'até recentemente'?";
			link.l1 = "Esse senhor acabou de nos deixar em um navio há poucos minutos.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Como você sabe disso? A baía mais próxima fica a dias daqui!";
			link.l1 = "Esse lago deve ser maior do que parece. Não tenho outra explicação para você, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Coisas estranhas estão acontecendo nas terras do Vice-Reinado.";
			link.l1 = "Estas terras são inglesas, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Deixe que os hereges continuem pensando assim. Nós vamos recuperar o que é nosso, pode ter certeza. Perdoe-me, meu filho, por fazer tantas perguntas: Santiago me instruiu a conduzir uma investigação oficial sobre esta pirâmide... e seu antigo ocupante.";
			link.l1 = "O que exatamente aconteceu, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Como o caso provavelmente será encerrado, posso te entreter com uma pequena história.\nHá algum tempo, rumores sobre este lugar circulam por todo o continente. Recebemos relatos confiáveis de que várias pessoas que deixaram uma marca importante na história da região costumavam visitar este local com frequência no passado.\nNo entanto, Santiago só começou a dar atenção de verdade a esses rumores depois do incidente do Panamá.\nUm certo índio causou um grande alvoroço naquela cidade gloriosa e chegou até a fazer alguns sermões de tom bastante filosófico. Infelizmente, os habitantes do Panamá tiraram conclusões bem superficiais e passaram a acreditar que esta pirâmide guarda riquezas inimagináveis e realiza qualquer desejo.\nHeresia das mais puras, é claro... então tivemos que abrir um processo contra alguns moradores do Panamá e esse índio, Aguebana.";
			link.l1 = "Por que as autoridades do Panamá não fizeram nada a respeito disso?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Como sempre fazem nesses casos, alegaram que estavam enfeitiçados. Essa brecha na lei poderia ter sido fechada se tivéssemos interrogado Aguebana, mas ele morreu de repente.";
			link.l1 = "Como ele morreu?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "A bebedeira o matou. No entanto, sua morte não resolveu nossos problemas, pois a heresia já tinha se espalhado por todo o arquipélago, e centenas de pessoas fizeram uma espécie de peregrinação até esse antigo templo.";
			link.l1 = "Eu nunca vi tanta gente por aqui antes... Então, o que foi, você ia invadir Aruba e julgá-lo?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Claro que não, meu filho. O julgamento da Inquisição é severo, mas justo. Deve haver um bom motivo para um julgamento. Não, eu só ia recolher o depoimento do senhor Aruba e entregá-lo em Santiago.";
			link.l1 = "Bem, isso é uma pena para você.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Você nunca sabe, meu filho. É a vontade de Deus.";
			link.l1 = "Adeus, padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		InitGunExt(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,  0.0,    0, 0,  20, 0);
		InitGunExt(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,  0.0,    0, 0,  15, 0);
		InitGunExt(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,  0.0,    0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		
		InitGunExt(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,    0.0,    1, 0,  13, 0);
		InitGunExt(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		InitGunExt(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
	
	ref itm;
	
	makeref(itm, items[FindItem("mushket9")]);
	
	itm.type.t3.basedmg  = 3;
	itm.type.t3.shards  = 110;
	itm.type.t3.width   = 8.5;
	itm.type.t3.height  = 7.85;
	itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
	if(CheckAttribute(itm, "UpgradeStage"))
	{
		int iUpgradeStage = sti(itm.UpgradeStage);
		
		switch (iUpgradeStage)
		{
			case 2:	
				itm.type.t3.basedmg  = 3;
				itm.type.t3.shards  = 120;
				itm.type.t3.width   = 7.0;
				itm.type.t3.height  = 5.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_4");
			break;
			
			case 3:	
				itm.type.t3.basedmg  = 4;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 5.5;
				itm.type.t3.height  = 4.5;
				itm.type.t3.area    = XI_ConvertString("grapes_area_3");
			break;
			
			case 4:	
				itm.type.t3.basedmg  = 5;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 4.5;
				itm.type.t3.height  = 3.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_2");
				itm.type.t3.ChargeSpeed = 18;
			break;
		}
	}
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
