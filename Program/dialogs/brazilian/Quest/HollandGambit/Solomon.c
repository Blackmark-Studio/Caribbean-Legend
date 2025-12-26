// Соломон Шнеур - старый еврей
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
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "O que você quer deste velho judeu, rapaz?";
					link.l1 = "Solomon, preciso que você pense com calma e se lembre da ilha perdida onde você naufragou. Você escondeu um tesouro lá. Conversei com sua filha. Meu chefe, Lucas Rodenburg, me deu carta branca para agir no melhor interesse da sua família. Pelo que vejo, o mais importante para você agora é recuperar o patrimônio da sua família, e você não vai chegar nem perto desse ouro sem a minha ajuda.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, meu jovem, é você? Não pode me trazer uma boa notícia? Vieram de novo esses cristãos atormentar este pobre velho judeu com perguntas?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Encontrei a ilha, embora tenha sido bem difícil. Também achei o seu baú com o dinheiro e este crânio. Imagino que seja o crânio do seu avô-patriarca, seja lá o que você estava falando.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Encontrei a ilha, embora não tenha sido nada fácil. Também achei o seu baú com o dinheiro. Mas não havia caveiras naquele baú.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Não, não tenho perguntas no momento.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, meu jovem, é você? Tem alguma boa notícia para me dar? Ou vai atormentar este pobre velho judeu com perguntas de novo?";
					link.l1 = "Encontrei a ilha, embora tenha sido bem difícil. Também achei o seu baú de dinheiro. Aqui está.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Olá, jovem. O que você quer deste pobre velho judeu?";
				link.l1 = "Boa tarde. Não, nada, só vim cumprimentar.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Boa tarde, jovem. Vejo que você veio com um propósito... O que deseja? Vou ganhar algo com isso, ou perdi alguma coisa?";
					link.l1 = "Boa tarde, Solomon. Gostaria de falar com a Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Olá, rapaz. O que você quer deste pobre velho judeu?";
				link.l1 = "Boa tarde, Salomão. Nada, só vim dar um oi.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Boa tarde, jovem. Vejo que você veio aqui por um motivo... O que deseja? Vou ganhar algo com isso, ou estou deixando passar alguma coisa?";
					link.l1 = "Preciso falar com a Abigail. Tenho uma carta para ela.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Olá, rapaz. O que você quer? Mais uma carta para minha filha?";
					link.l1 = "Não. Onde está Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Ei... Você está falando do meu dinheiro, rapaz?";
					link.l1 = "Sim, senhor. Sobre o dinheiro que você escondeu em alguma ilha. É verdade que você e Abigail não conseguem se lembrar onde fica?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Certo. Eu me lembro do fluyt e do capitão dele. Cheguei a vê-lo uma vez em Amsterdã. O nome do fluyt era 'Leiden' e o capitão se chamava Toff Keller.";
					link.l1 = "Já é um começo! Agora tenho uma pista.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Ai ai, o que você quer deste pobre velho judeu agora?";
				link.l1 = "Boa tarde. Não, nada, só vim cumprimentar.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ai ai, o que você quer deste pobre velho judeu desta vez?";
			link.l1 = "Boa tarde. Não, nada, só vim cumprimentar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "E o que você quer de mim? Por acaso eu pareço alguém que sabe de alguma coisa? Como eu poderia imaginar que, num dia tão esquecido por Deus, haveria um pedaço de terra com mercadorias e ouro dando sopa por aí? Imagine só, todos esses gentios andando pelas ruas querendo passar a perna em um judeu como eu e levar meu dinheiro!\nTem uma ilha. Não tem viva alma lá, só eu e o Abi. Mais ninguém. Nenhum ser humano. No meio dela, tinha uma gruta. Eu escondi meu baú lá pra salvar ele daquele pirata goyim Amalek! Um baú cheio de ouro, não tem bugiganga nenhuma. Trouxe tudo arrastando desde a Velha Terra! Tudo que ganhei com o suor do meu rosto está lá. E ainda tem o crânio do meu avô... Pode acreditar, aquilo nos salvou, sim-sim\nOh-ho-ho, é um talismã antigo carregado de magia talmúdica! Deus nos livre do Amalek! Oy vey, como é difícil recomeçar nesta era dos gentios! Queria que você soubesse, rapaz! Ah, como eu queria que soubesse!";
			link.l1 = "O que diabos você está falando, seu maluco? Tanto faz. Eu resolvo isso sozinho. Tchau!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Oi, existe um Deus e você é um verdadeiro mensch! Você trouxe de volta não só meu ouro, mas também restaurou o nome Shneur! Que vergonha você evitou! Mynheer Rodenburg pode se orgulhar de ter capitães como você sob seu comando. Vou entregar o crânio ao mynheer Rodenburg, ele prometeu pagar uma boa quantia por ele. Quero agradecer pessoalmente, você é um ótimo shabbos goy – por favor, aceite este amuleto como um pequeno sinal da gratidão deste judeu.";
			link.l1 = "Ah, obrigado, eu acho.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Ah, existe um Deus e você é realmente um homem de valor! Você não só trouxe meu ouro de volta, como também salvou o nome dos Shneur! Que vergonha você evitou! Quanto ao crânio – deixa pra lá, ele era um idiota maluco mesmo! Mynheer Rodenburg pode se orgulhar de ter capitães como você sob seu comando. Quero agradecer pessoalmente, você é um verdadeiro amigo – por favor, aceite este amuleto como lembrança.";
			link.l1 = "Ah, obrigado, eu acho.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "O quê? O que você está dizendo, rapaz? Isso é verdade? Deixe-me ver... ";
			link.l1 = "Aqui está o seu dinheiro. Ele pertence a você e à Abigail. Mas, infelizmente, ainda não encontrei o crânio do seu avô.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Ah, dinheiro, dinheiro, dinheiro, maravilhoso dinheiro... Hmm, mas isso aqui não parece meu dinheiro... Não tem o cheiro do meu querido lucro. Mas, pensando bem – dinheiro é tudo igual, não é, rapaz? Não vou reclamar. 'Cavalo dado não se olha os dentes', como costumamos dizer! Muito obrigado por devolver minhas economias. Quero te agradecer também, por favor, aceite este amuleto. Agora vá contar a novidade para a Abi. Preciso conferir isso aqui.";
			link.l1 = "Muitos anos de vida, Salomão.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Vish, cuidado! O senhor Rodenburg está a um passo de virar meu genro. Se eu gritar por socorro, todos os soldados da guarnição aparecem aqui num instante!";
			link.l1 = "Quem diabos é você?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Escute-me, capitão. Eu sou o pai dela, Salomão. Faça o que é certo, traga-me minhas moedas perdidas e o crânio de jade do bisavô dela. Este velho judeu pode não ser tão astuto quanto você, mas até ele sabe que você quer algo da filha dele.\nTalvez você tenha sido mandado por alguém, por algum capitão que me conhece. Vou contar tudo para Abi, não se preocupe. Ela não está em casa agora, está rezando pelas almas dos pecadores gentios como você.";
			link.l1 = "Isso quase não fez sentido... Droga, você é mesmo um caso perdido. Adeus, seu velho pão-duro.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Uma carta? Não me diga! Escuta aqui, rapaz, o senhor Rodenburg está a um passo de ser meu genro. Pode dar o fora daqui porque eu gosto dele!";
			link.l1 = "Escute, não estou nem aí para quem é seu genro. Tenho que entregar esta carta para a Abigail. Sabe onde posso encontrá-la? E quem diabos é você?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Quem sou eu? Eu sou o pai dela, Salomão... E eu não gosto de você, goy.";
			link.l1 = "Eu ficaria mais preocupado se você dissesse que gosta de mim. Agora, vai continuar me tratando como criança ou vai chamar a Abigail? Repito, sou apenas um mensageiro! Tenho uma carta para sua filha!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Me dê essa carta. Eu mesmo vou entregá-la para minha filha.";
			link.l1 = "Vou raspar seu cabelo e puxar seu nariz antes de te entregar esta carta. Tenho ordens de entregar esta mensagem a ela pessoalmente. Não me disseram nada sobre o pai dela e não estou nem aí. Onde posso encontrar Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Assim que eu gritar, rapaz, todos os soldados da cidade vão aparecer na mesma hora. Não seja teimoso, você vê que eu tenho todas as cartas na mão.";
			link.l1 = "Jesus, Maria e José! Sério? E depois? Você acha que vão me prender só por entregar uma carta? Não seja ridículo!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Você ficou maluco? Você deixou minha pobre filha quase morta de preocupação com sua carta... Ela resolveu ir atrás daquele canalha do capitão inglês! Partiu no primeiro navio que encontrou! Ai, ai, minha pobre filha! O que esse velho judeu vai fazer agora? Minha vida acabou! Que vergonha! Me deixe com meu sofrimento, ou fique aí se divertindo, não me importa! Ohhh minha pobre Abigail! Você fez seu pai descer à sepultura de tanta tristeza!";
			link.l1 = "Olha só! Parece que ela não aguentou esperar nem mais um instante. Tchau, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "O que parece? É só uma ilha onde só estou eu e a Abigail. Foi lá que escondi meu baú, pra evitar que aquele pirata amaldiçoado, Amalek, o levasse. Tudo o que ganhei honestamente, com o suor do meu rosto, está naquele baú...";
			link.l1 = "Me diga, Salomão, você conseguiria lembrar o nome do fluyt que sua filha mencionou? E qual era o nome do capitão dele?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Bem, eu não sei. Esta pobre cabeça de judeu velho está mais confusa que uma panela de gefilte fish! E por que está perguntando, rapaz?";
			link.l1 = "Eu só quero ajudar sua filha, Solomon. Não posso prometer nada, mas gostaria de tentar. Meu antigo chefe a tratou mal, e depois disso me sinto na obrigação de ajudá-la a se estabelecer de alguma forma.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Ai ai, bom, se é assim...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Rapaz! Espere!";
			link.l1 = "Sim?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Rapaz! Quero lhe agradecer por tudo o que fez por mim e por minha filha. Você nos salvou. Me desculpe por ter sido tão ríspido quando nos conhecemos e por duvidar do seu desejo sincero de ajudar. Por favor, perdoe este velho judeu. Você é realmente um homem abençoado entre os gentios. Agora me diga, você não encontrou mais nada além do meu dinheiro na gruta?";
			link.l1 = "Não, Salomão. Só havia dinheiro. Tive que lutar contra os bandidos do van Berg – foi ele quem afundou seu navio meses atrás. Talvez eles já tivessem roubado alguma coisa... O que mais era pra estar lá?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Ah, nada de importante... Só uma relíquia antiga da família... Bem, deixa pra lá! Esqueça isso, ele era um tolo mesmo! E... Só mais uma coisa, rapaz... ";
			link.l1 = "Continue.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Você... bem, eu descobri algo sobre você. Nosso governador tem grande consideração por você, e você é um capitão de destaque. Vou te contar um segredo... minha filha gosta muito de você. Ela mesma me disse isso. Talvez... você pense a respeito? Abigail é uma moça excelente, te garanto, muito melhor do que qualquer uma dessas vadias que você pode ter conhecido por aí.";
			link.l1 = "Vish... Não é tão simples assim, Salomão. Sua filha é realmente uma joia rara. Você cuida muito bem dela.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Pense bem, rapaz. Reflita e volte! Adoraríamos vê-lo de novo!";
			link.l1 = "Certo... tchau, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Às vezes é impossível recomeçar, rapaz. Viver na pobreza... o que poderia ser pior para um velho tolo como eu?";
			link.l1 = "Sinto muito, Solomon. Mantenha-se firme e busque Cristo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("Ladrão, senhor! Guardas, peguem ele","Ladra, garota! Guardas, peguem ela")+"!!!","Olha só isso! No instante em que eu estava distraído, você resolveu mexer no meu baú! Peguem o ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Droga!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
