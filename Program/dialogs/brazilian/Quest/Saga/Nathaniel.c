// Натаниэль Хоук - пиратский барон Марун-Тауна
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
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... quem é você, droga?.. Khe... (tosse forte e rouca) Maldita fraqueza...";
			link.l1 = "Saudações, Nathaniel. Você é Nathaniel Hawk, não é?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Sim, sou eu, se é que ainda posso me chamar assim. Já fui Nathaniel Hawk, mas agora sou só um saco de merda caído e triste. Maldita estátua! Ela sugou toda a vida de mim.";
			link.l1 = "Eu conheço bem esse sentimento...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "Como você poderia, rapaz, se nem percebe do que estou falando? A-kha... Você faz ideia do que é de repente se tornar um velho meio morto, quando um minuto atrás eu estava saudável e forte?\nJá vi muita coisa na minha vida. Achei que aquele antigo templo indígena que visitei na juventude tinha acabado com minha capacidade de me surpreender, mas isso... por que eu não percebi antes? Aquela maldita estátua era igualzinha ao velho ídolo que abriu a porta do templo!";
			link.l1 = "Certo, Nathan, vamos conversar. Permita-me apresentar, eu sou "+GetFullName(pchar)+" . Primeiro, eu entendo muito bem o que você sente, porque cheguei aqui do mesmo jeito que você – pelo portal de Kukulcan.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Sério?! Então por que você parece estar bem? Ou será que só eu fui ferido por esse... Kukulcan?";
			link.l1 = "Olho de Cobra, o xamã Miskito que te ajudou a escapar, me deu uma poção muito forte. Bebi assim que acordei em San Augustine. Ela me curou completamente. Tenho certeza de que Olho de Cobra pode te ajudar também. Só precisamos te levar até ele.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, aquele índio! Uma poção? E por que ele não me deu uma também?";
			link.l1 = "Ele disse que não havia tempo. Você estava sendo perseguido, e a única coisa que ele pôde fazer foi mostrar o caminho para fugir – o portal.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Fugir? Ah... Você não está vendo o estado em que eu estou? Mal consigo segurar um sabre. Como pode chamar isso de fuga? Graças a Deus, ainda existem pessoas boas neste mundo. Ole, que Deus o abençoe... Você conhece o Ole?";
			link.l1 = "Sim. Na verdade, foi ele quem me falou de você, contou como te alimentava com ratos e como você não para de beber, garrafa após garrafa...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "Eu vou morrer mais rápido que uma vela acesa se não beber rum. É a única coisa que me mantém vivo. Rum...";
			link.l1 = "Você ainda está se sentindo tão mal? Igual depois da teletransporte?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Bem, não estou me sentindo exatamente igual... Mas também não estou melhor. Amigo, me diz, por que você precisava ver o velho Nathan? Por que diabos veio aqui, pra esse barco velho e caindo aos pedaços? Só pra conversar comigo?";
			link.l1 = "Na verdade, sim. Você não vai acreditar, mas o motivo de toda aquela confusão com teletransporte foi para te encontrar. Eu trabalho para a Irmandade da Costa e represento Jan Svenson.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Droga... o Demônio da Floresta? Argh... Veio aqui pra me matar? Na verdade, não? Você fala demais pra um assassino. Por favor – não me torture. Se mandaram você arrancar alguma coisa de mim – eu mesmo conto tudo, não tenho nada a esconder.";
			link.l1 = "O que você quer dizer? A-ah, entendi. Você, assim como a Danielle, acha que foi o Svenson quem armou aquela emboscada contra você na selva. Posso garantir que o Jan não fez isso. Pelo contrário, ele está do seu lado e está muito preocupado com o seu desaparecimento.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Sério? Fico muito aliviado em saber disso. E já estive pensando... mas quem fez isso? Meu destacamento foi destruído em poucos minutos. Eles estavam nos esperando. Até tinham canhões de navio! Metade dos meus homens caiu sob a saraivada de balas, e depois terminaram o serviço com seus mosquetes...";
			link.l1 = "Para ser sincero, não sei os detalhes, mas tenho certeza de que o Jackman está por trás de tudo isso. Coincidências demais, primeiro o Blaze, depois você... Jackman quer tomar o poder e elimina todos que ficam no caminho dele. Agora é ele quem manda em Maroon Town, não você.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Desgraçado! Eh... a Irmandade se dividiu nos últimos anos, antes era tudo diferente. Zachariah ficou louco com suas obsessões religiosas, Tyrex não liga pra nada, e Barbazon só pensa em dobrões. Vinte anos atrás era tudo diferente...";
			link.l1 = "Como eles te capturaram? Me conte mais.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "Não há nada de interessante para contar! Como eu disse, aqueles bandidos planejaram tudo. Agiram com precisão, coordenados e claramente seguindo as ordens de alguém. Eles poderiam ter me matado cem vezes, mas não fizeram isso. Queriam que eu ficasse vivo. Me levaram para uma mina abandonada e me trancaram em uma das cabanas. 'Até o chefe chegar', disseram eles. Eu achei que Svenson fosse o chefe, mas parece que quem manda é o Jackman. Não sei o que ele poderia querer comigo, mas tenho certeza de que eu não teria vivido muito depois de conversar com ele.";
			link.l1 = "Não tenho dúvidas disso. Svenson tem certeza de que Jackman matou Blaze Sharp... Como você conseguiu escapar?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "Aquele índio Olho de Cobra conseguiu de algum jeito se infiltrar na mina. Pelo que entendi, os Miskitos não gostam de bandidos. De qualquer forma, Olho de Cobra armou minha fuga por algum motivo. Ele cavou um túnel até mim, entrou, cortou minhas cordas e nós fugimos para a selva.\nEle queria me levar para a aldeia dele, dos Miskitos. Mas parece que Jackman me queria de qualquer jeito, porque organizaram uma grande caçada. Estavam sempre no nosso encalço. Olho de Cobra fez de tudo para despistá-los, mas eles sempre conseguiam achar nossos rastros. Tinham batedores muito bons, sem dúvida.\nEstávamos perto da aldeia do Olho de Cobra quando finalmente nos acharam. Nessa altura, eu já estava há dois dias sem comer e completamente exausto, além de ter machucado feio a perna. Era meia-noite, e ainda me lembro de como a estrela sobre a estátua brilhava... Olho de Cobra disse que minha única chance era chegar até o ídolo e tocá-lo.\nAchei que ele era maluco, mas você sabe como é, a gente se agarra a qualquer esperança. Mancando, fui até a estátua, toquei nela... e aí coisas malucas começaram a acontecer!";
			link.l1 = "Não precisa continuar, eu já sei o que aconteceu depois.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "Me vi no porão úmido de um navio naufragado. Eu estava meio morto. Não conseguia andar, só rastejar. A cada minuto, minha situação piorava. Ole apareceu bem na hora. Ele me fez engolir uma mistura caribenha horrível, um pouco de antídoto e essência de cura. Depois me deu rum.  Na hora já me senti melhor. Depois ele achou um tronco velho e usou para me trazer até aqui. Já faz um tempo que estou vivendo aqui, embora eu não saiba dizer quanto—perdi a noção do tempo.";
			link.l1 = "Vai ficar tudo bem, Nathan. Svenson e eu temos grandes planos, e o seu papel neles é muito importante. Você precisa voltar para o seu posto em Maroon Town e nós vamos cuidar daquele canalha do Jackman.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? E como exatamente você acha que isso vai funcionar? Olhe pra mim, sou um trapo encharcado de rum! Inútil... Não, meus anos de autoridade sobre Maroon Town se foram pra sempre. Estou preso nesse maldito cemitério de navios. Quanto tempo vou aguentar? Um mês, dois, um ano?\nE então vou acabar largado nessas tábuas podres e Ole vai jogar o que sobrar de Nathaniel Hawk no mar. O pior é que não vou ver minha Dannie de novo. É, acabou, amigo.";
			link.l1 = "Não seja tão pessimista. Eu vou tirar você daqui.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Como você vai me tirar daqui? E como vamos sair deste lugar? Não há navios. Você quer construir uma jangada?";
			link.l1 = "Não. Vou sair daqui do mesmo jeito que cheguei. Eu sei onde está a estátua... bom, mais ou menos. Vou encontrá-la e depois volto para buscar você e o Shark Dodson. Depois disso, vamos levar vocês até o Snake Eye. Ele vai te curar.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "O que você disse? Shark Dodson? O Steve também está aqui? Que lugar estranho...";
			link.l1 = "Sim, ele está aqui. Ele é o 'governador' desta ilha, por assim dizer. Perguntei a ele sobre você, mas ele não sabe de nada.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "E ele não deveria. Não quero que ele me veja assim. Você disse que o xamã iria me curar... Mal consigo acreditar nisso. Você também mencionou a Dannie... Você a viu?";
			link.l1 = "Sim. Ela mesma me encontrou em Blueweld. Ouviu escondida minha conversa com Svenson e percebeu que Jan não tinha intenção de te matar e que está agindo contra Jackman. Ela entrou para minha tripulação como oficial para me ajudar a te encontrar.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Ah, minha querida Dannie! Ela não mudou nada... continua tão impulsiva quanto era na juventude... Você nem imagina o quanto eu quero vê-la e abraçá-la agora! Fiquei pensando muito enquanto estava deitado aqui. Sabe, amigo, quando a morte está por perto, a gente começa a enxergar as coisas de outro jeito. Passei tão pouco tempo com minha esposa! Saídas ao mar, assuntos oficiais da Irmandade, governar Maroon Town. E ela sempre me apoiou em tudo: ficava sozinha por semanas, brigava com outros piratas enquanto eu estava longe, comandava nosso navio... Minha Dannie é a melhor mulher do mundo! E eu... eu devia ter dito mais vezes que a amo! Lembro do dia em que decidimos ficar juntos! Na verdade, foi naquele dia que enfrentei coisas sobrenaturais pela primeira vez. Tudo aconteceu por causa daquele maldito ídolo que parecia exatamente com as estátuas. Você não se importa de ouvir uma história, né? É bem interessante.";
			link.l1 = "De jeito nenhum! Me conte!";
			link.l1.go = "story";
			link.l2 = "Nathan, não temos tempo para lembranças agradáveis. Me conta depois, quando estivermos sentados na aldeia Miskito com uma garrafa de vinho.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "It was twenty-five years ago... I was young, ardent and restless. The Caribbean was my playground. I already knew Dannie back then. I liked her, I truly did, and the feeling was mutual. But we often fought, quarrelled and jibed at each other. Foolish youth... I believe we were great entertainment for the respected sailors back then! Anyway, somehow Dannie and I became involved in the same story. We had found a map of Khael Roa, and were told it was THE place to find Indian gold. We had also discovered a strange-looking golden idol, a smaller copy of the top part of the statues. The idol was dangerous; it drained vitality from those who carried it. But we needed that cursed item in order to reach the treasury inside the temple. The only problem was that we had no idea how to properly use it. Dannie and I sailed to the island. There was an ancient temple, overgrown with grass and trees. Once we entered, we found ourselves inside a huge labyrinth. We managed to find the right path and reached the central part of the labyrinth. We thought it was a dead end, but when desperation began to overtake us, we saw a strange platform with a small socket and a picture on it. I put the idol into the socket and...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "The stone platform sank a few inches, and one of the walls turned out to be a secret passage. The idol was left inside the platform; I failed to pull it back out. Finally, we reached a giant hall. Such a beautiful sight!   The most magnificent structure I've ever seen. Carvings on the walls, huge statues... We searched the whole hall, but found no sign of treasure.";
			link.l1 = "Heh, isso acontece mesmo com gente como a gente. Muito esforço e no fim, nada de resultado...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "Não foi à toa. Afinal, entramos numa sala do trono com uma estátua gigante de um pássaro no fundo. Havia uma luz mística perto da estátua, parecia exatamente com a luz acima do ídolo à meia-noite. Chegamos mais perto e vimos uma esfera linda flutuando. Juro, estou te contando a mais pura verdade!\nEra real, mas ao mesmo tempo parecia que não era. Enquanto eu pensava nisso, Dannie – ah, aquela doida destemida – tocou na esfera. Ela começou a brilhar ainda mais forte e, por fim, virou um pequeno objeto nas mãos dela...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "Parecia que tínhamos cometido um sacrilégio. O templo ganhou vida: tudo ao nosso redor começou a se mover, as paredes tremiam e tudo desmoronava. Era como se tivéssemos despertado todos os demônios indígenas e eles estivessem liberando toda a sua fúria sobre nós...";
			link.l1 = "Estou pasmo!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "É difícil de acreditar, eu sei. Mas...";
			link.l1 = "Eu teria te chamado de mentiroso há seis meses. Mas já vivi tempo suficiente no Caribe pra saber que não tenho motivo pra duvidar de você. Continue. Como você sobreviveu?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "We ran out of the temple and were lucky enough to get aboard our ship in time. I ordered the anchor to be raised; we wanted to sail away from that place as soon as possible.";
			link.l1 = "Hein! Então, no fim das contas, você só encontrou um artefato estranho em vez de tesouros? Que bela e equivalente substituição, hein... E conseguiu descobrir pra que serve? Ou não serviu pra nada?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Espere um pouco. A história ainda não acabou. Dannie estava com o artefato e, assim que decidimos ir para a cabine estudá-lo, o céu escureceu e um navio apareceu. Meu Deus! Era...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... O próprio Van der Decken!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "E quem é ele?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Você nunca ouviu falar do Holandês Voador?";
			link.l1 = "Quem nunca ouviu falar do Holandês Voador! Eu já encontrei um holandês e mandei o capitão dele para o fundo do mar. Ele era só um pirata qualquer que enfeitava o navio com porcarias de baile de máscaras, como algas e velas rasgadas.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Sim, mas esse era o próprio Van der Decken, o capitão do Holandês Voador!";
			link.l1 = "Interessante. Por favor, continue. Como você conseguiu superar isso?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, amigo... Você afundou algum bobo, mas eu tô falando do verdadeiro Holandês Voador. Um navio de guerra gigantesco. Deus te livre de cruzar com ele em mar aberto. O capitão dele, Van der Decken, e a tripulação foram amaldiçoados a vagar pelos mares pra sempre, sem descanso.\nEu lembro das velas negras rasgadas, da tripulação de mortos em pé no convés com as espadas em punho, e do próprio capitão – um esqueleto assustador usando um chapéu preto de abas... Meu Deus...";
			link.l1 = "Você está dizendo a verdade?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "I can swear on the Bible that I am not lying... A meeting with the 'Flying Dutchman' only means certain death. She's powerful, very powerful; one volley from her guns can sink even a heavy frigate and its crew... but even worse, how are you supposed to fight the undead?";
			link.l1 = "Mas você sobreviveu a esse pesadelo!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "Foi tudo graças à minha querida Dannie e ao artefato indígena que pegamos no templo. Eu tinha mandado todos se prepararem para lutar, mas sabia que era o fim da linha. O 'Holandês Voador' estava vindo na nossa direção, e eu conseguia ver sua tripulação terrível e o próprio Van der Decken no convés. O navio começou a apontar seus canhões para nós, mas...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie levantou o artefato e o lançou. Eu não fazia ideia do porquê ela faria isso. Ela disse algo sobre intuição feminina... O artefato voltou a ser uma esfera brilhante e explodiu, causando danos críticos ao navio fantasma e desmoralizando sua tripulação. Dei a ordem para abrir fogo contra o Holandês.\nA primeira salva os fez estremecer. Atacamos de novo e atingimos o casco podre deles pela segunda vez, pouco antes que se recuperassem do efeito do artefato e começassem a revidar...";
			link.l1 = "Então, você teve que lutar contra eles de qualquer jeito?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "De fato. E juro que foi a luta mais difícil da minha vida. O maldito barco deles mal se mantinha flutuando, mas ainda assim conseguiram destruir metade do meu casco antes de mandarmos eles pelos ares explodindo o maldito paiol deles.";
			link.l1 = "Então você afundou mesmo? Afundou o Holandês Voador?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Sim, droga! Eu fiz!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "Aquela maldita nau afundou. O sol voltou a brilhar e o céu se abriu. E, finalmente, começamos a sentir uma felicidade verdadeira... ah, você nem imagina o quanto estávamos felizes. Tínhamos enganado a própria morte. Momentos assim unem as pessoas. E fizemos o que já devíamos ter feito muito antes daquele encontro – nos abraçamos, nos beijamos, confessamos nosso amor um pelo outro e juramos ficar juntos para sempre.";
			link.l1 = "E vocês ainda estão juntos...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Sim, somos nós. Eu e a Dannie nos casamos e nunca me arrependi disso. Você não vai encontrar esposa ou parceira melhor.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Então, agora finalmente sei quem é aquele capitão misterioso que conseguiu afundar o 'Holandês Voador' de verdade... Você é um verdadeiro herói!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "Então, vocês dois são verdadeiros heróis, não é? Conseguiram afundar o famoso navio fantasma. Espera aí! Você disse que o 'Holandês Voador' ainda está à deriva... Como isso é possível se ele está no fundo do mar?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Ah, camarada, você não sabe de nada... Você pode afundar o Van der Decken, mas não pode matá-lo. A maldição sobre ele e sua tripulação é forte demais, muito mais forte que a morte...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "Herói eu posso ser, mas Van der Decken não pode ser morto. A maldição que pesa sobre ele, sua tripulação e seu navio é mais forte do que a morte...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Toda vez que você afunda o navio, a tripulação conserta, remenda e segue sua viagem eterna.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Eu sei, Nathaniel, eu sei. Mas o Holandês Voador não vai incomodar mais ninguém.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Olha, você sabe, isso parece uma fábula. Consertar um navio que já foi desmontado e afundado...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "As pessoas já viram o navio muitas vezes depois que o afundamos... Você decide se acredita nesses relatos.";
			link.l1 = "E onde fica aquela ilha com o templo, aquela onde você encontrou o artefato?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "É uma ilha desconhecida, localizada em algum lugar no leste do Mar do Caribe. Deixei um mapa da ilha em Maroon Town, mas como você bem sabe, não posso navegar até lá agora. E, para ser sincero, nem quero. A única coisa de que me lembro é o nome dela – Khael Roa...";
			link.l1 = "Que história interessante. Eu adoraria encontrar essa ilha!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Ah, eu não recomendaria isso... Eu mesmo não vou voltar lá, com certeza.";
			link.l1 = "De qualquer forma, gostaria de visitar... Tudo bem, obrigado pela história fascinante! Agora sei mais sobre sua esposa. Vocês dois são verdadeiras lendas vivas!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "O que você está insinuando, camarada? Eu não acabei de dizer que ele não pode ser morto?";
			link.l1 = "Nathaniel, eu naveguei até Khael Roa. E visitei o templo dos Chavins, onde você, Danielle e um velho estiveram há um quarto de século. O artefato que vocês pegaram do templo naquela época se chamava 'orbe do sol nascente'. Foi esse artefato que atraiu a atenção do 'Holandês Voador' para vocês. O capitão dele era fascinado por artefatos Chavin.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "Você esteve em Khael Roa? Mas isso não pode ser! Você está mesmo dizendo a verdade?";
			link.l1 = "Eu juro. Quando você me contou sobre o labirinto e a estátua do pássaro gigante, percebi na hora onde ficava esse lugar. O xamã caribenho Tuttuathapak me falou das suas aventuras. Foi ele quem me indicou aquela ilha. Ela fica a leste de São Cristóvão. É bem pequena, em forma de anel. Tem rochedos ao redor e uma pequena enseada no meio. E só existe uma trilha tomada pelo mato levando até um templo, que é construído em forma de pirâmide.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Sim! Este é Khael Roa. Mas por que você foi até lá?";
			link.l1 = "Para quebrar a maldição do Caleuche... bem, do 'Holandês Voador'. Na verdade, o nome dela era 'Coração Voador', e o capitão era 'Balthazar de Cordes'. Cinquenta anos atrás, ele foi amaldiçoado por Yum Cimil, um deus da morte indígena. Eu peguei o crânio de jade de Yum Cimil, que havia sido roubado do templo pelo Balthazar há algum tempo, e coloquei de volta no pedestal em frente àquela estátua de condor...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...ao devolver o crânio, eu quebrei a maldição do Caleuche. E como eu estava com outros dois amuletos Chavin, ela me atacou perto da ilha, exatamente como aconteceu com você naquela época. Mas sem a maldição, Balthazar não era mais imortal, assim como Tuttuathapak disse. Então... o 'Holandês Voador' não existe mais. Eu mesmo cuidei dela.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Trovão e relâmpago! Estou pasmo! Você... Você não está brincando com o velho Nathan, está? Não, vejo nos seus olhos que está dizendo a verdade! Você é um verdadeiro herói!";
			link.l1 = "Herói ou não, já vivi minha cota de aventuras, assim como você. Bem, tenho certeza de que ainda vamos falar muito sobre o passado, já que agora temos um assunto em comum.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Você vai me deixar agora, amigo?";
			link.l1 = "Sim, Nathan. Por favor, aguente firme até eu voltar. Se cuide. E, acima de tudo, fique vivo até meu retorno e tudo vai dar certo. Os Irmãos da Costa precisam de você, a Danielle precisa de você.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "A Dannie está na sua tripulação agora? Por favor, cuide dela. Ela não mudou nada desde jovem, continua sendo uma destemida e não hesitará em passar pelo inferno. Diga a ela que eu a amo muito...";
			link.l1 = "Claro que vou. Nós vamos voltar juntos para te buscar, eu te prometo isso, Nathan. Aguente firme e mantenha a cabeça erguida. Ole vai cuidar de você. Até logo!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, é você, "+pchar.name+". Ainda não deixou a ilha?";
			link.l1 = "Não se preocupe, Nathan, está tudo saindo conforme o planejado. Descanse agora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! Minha Dannie!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Obrigado, meu amigo. Obrigado por tudo, e principalmente pela minha Dannie...";
			link.l1 = "De nada, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Olha só quem apareceu! É "+GetFullName(pchar)+"  ele mesmo! Entre, entre, meu amigo! Como vai você?";
			link.l1 = "Estou bem. E você, Nathan? Vejo que não resta mais nenhuma tristeza. Você está com ótima aparência. Olho de Cobra fez um ótimo trabalho!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Sim, o seu xamã é um verdadeiro milagreiro. Estou me sentindo até melhor do que antes daquela maldita teletransporte! Sinto como se tivesse dez anos a menos! "+pchar.name+", eu lhe devo muito. E estou impressionado: você ajudou um completo desconhecido, atravessou o portal amaldiçoado, me arrancou das mãos da morte e me trouxe de volta para minha esposa!\nE mais ainda! Você nos devolveu nosso navio e nosso lar. Agora você é nosso amigo mais querido. Para sempre. Se algum dia precisar de qualquer coisa - já sabe a quem pedir! Maroon Town sempre vai lhe oferecer proteção, apoio e abrigo, se precisar.\nToda a vila lutará por você se estiver em perigo. Em tempos de paz, você encontrará amizade aqui, o melhor rum, uma cama macia e um bom lugar para descansar. Dannie e eu vamos garantir isso.";
			link.l1 = "Obrigado, Barão! Fico realmente feliz em vê-lo com saúde e... com a Dannie.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "Estava esperando a sua visita, "+pchar.name+", e eu preparei um presente – uma arma rara e poderosa. Talvez, um dia, você precise derrubar vários inimigos com um único disparo, e este morteiro de mão vai te ajudar nisso. A 'Sclopetta' dispara granadas especiais, então também deixei instruções de como fabricá-las. Aqui, pode pegar.";
			link.l1 = "Que arma excelente! Obrigado!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "Venha nos visitar mais vezes, "+pchar.name+"! Dannie e eu sempre vamos ficar felizes em te ver a qualquer hora.";
			link.l1 = "Será um prazer. Espere me ver em breve!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, meu amigo "+GetFullName(pchar)+"! Entre, entre, Capitão! Como vai? Precisa de alguma ajuda?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, vim falar com você sobre um assunto muito importante. Você se lembra quando me contou, lá na Ilha dos Navios Abandonados, que você e a Dannie invadiram um templo indígena e afundaram o 'Holandês Voador'?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Obrigada, estou bem. Só queria ver vocês dois.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Claro, eu faço.";
			link.l1 = "Eu preciso chegar naquela ilha com o templo. Preciso encontrá-la desesperadamente. Você disse que tinha um mapa dela. Pode me dizer as coordenadas?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ah, amigo, isso é uma empreitada muito perigosa, sabia... o templo de Khael Roa é amaldiçoado. Se você soubesse quem habita seus corredores...";
			link.l1 = "No momento, o lugar está habitado por monstros muito mais assustadores do que aqueles que você viu naquela época. E mesmo assim, eu ainda vou até lá.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Eu nunca vou me perdoar se você morrer lá. "+pchar.name+", eu te imploro: desista dessa aventura! Além disso, é lá que o 'Holandês Voador' é visto com mais frequência...";
			link.l1 = "Eu já me deparei com isso, e sei como escapar. Nathan, por favor, me dê as coordenadas de Khael Roa e me conte tudo o que sabe sobre esse templo, além do fato de que ele é habitado por índios mortos-vivos.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Ah, tudo bem... Não posso te recusar, mas... você não faz ideia do que eu e a Dannie passamos lá! Khael Roa fica a leste de Antígua. Encontrei o mapa assim que voltei para Maroon Town, está em... (olhando) nas coordenadas: 19 graus 32' Norte, 62 graus 25' Oeste.";
			link.l1 = "Vou anotar a localização no meu diário... Obrigado, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "You can thank me later. Now the details. The island of Khael Roa is a ring of rocks with a cove inside. Seek for the passage between the crags - it's fairly deep there. In the cove, you should cast anchor and disembark at the beach. Look for an old path heading deeper into the island - there's only one there. It will lead you to an Indian pyramid - this is the temple you seek.\nThe island itself is quiet, but the temple is crawling with abominations of all sorts. The entrance is located at the top of the pyramid. There will be three passages inside; you should take the middle one. Then you walk down the corridor and you will find a platform with four entrances or exits. This is where the temple creatures attacked me for the first time, so you should be careful.\nThen there is a labyrinth. It's very complex, and I, for the life of me, can't remember the right route. There is a multitude of foul creatures in the labyrinth. You must kill them all, then walk up to a hall with two entrances, six columns and a platform with nine stone slabs. This is the vestibule of the sanctuary. Its stone wall is closed, and I have no idea how you're going to open it.\nThere is some kind of mechanism, but I swear to God that I have no clue how it functions! I used an idol as a key. I inserted it into the central slab, and the door opened. But you don't have such an idol, so you'll have to figure out how this mechanism functions.";
			link.l1 = "Certo, vou fazer o possível para entender isso. E quanto ao santuário?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "O santuário é um grande salão com um teto altíssimo e enormes escadarias de pedra. Você não pode usá-las – a maioria está velha demais e desabou. Mas os construtores do templo, ao que parece, também eram grandes feiticeiros. Existem portais, como os de Kukulcán, e eles vão te levar de um lugar para outro.\nVocê vai reconhecê-los facilmente – parecem redemoinhos coloridos. No primeiro andar haverá dois portais, mas um deles é uma armadilha, então tome cuidado! O portal certo vai te levar ao segundo andar. Lá, você precisa encontrar outro portal para subir ainda mais, e então ir direto ao coração do templo!\nLá, junto à grande estátua do pássaro, foi colocado aquele artefato mágico que Dannie e eu levamos conosco. E eu já te contei o que aconteceu depois disso.";
			link.l1 = "Vou me lembrar do que você acabou de me contar. Obrigado, Nathaniel. Você me ajudou muito.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Se cuida, "+pchar.name+". O labirinto e os salões do templo estão cheios de perigos. Basta um passo em falso e você vai ficar lá para sempre.";
			link.l1 = "Praemonitus praemunitus, amigo. Fui avisado, então estou preparado. Preciso ir agora. Até mais!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Boa sorte, "+pchar.name+"!";
			link.l1 = "Obrigado!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
