// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você precisa?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, que sorte! Estou procurando por você há meses!";
			link.l1 = "Meu caro, não compro mapas falsos, informações duvidosas, nem rum feito em casa – obrigado! Ou você é um caçador de recompensas? E quanto vale minha cabeça agora?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, monsieur, eu... eu não lido com tralha e não mato ninguém – não toque em sua espada, não vai precisar, não quero confusão! Tudo é bem mais simples – sou capitão de um navio de correio. Entrego correspondências. E para você, tenho uma carta importante!";
			link.l1 = "Uma carta? Quem é o remetente, posso saber?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Um abade me entregou isso e pediu que eu levasse pessoalmente ao Capitão de Maure, de mão em mão. Eu já tinha perdido toda a esperança de te encontrar e estava prestes a deixar a encomenda no escritório do porto em Saint Pierre, mas que sorte — aqui está você!";
			link.l1 = "Sim, estou aqui, estou esperando - me dê a carta.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Tem um problema... O abade disse que a entrega seria paga pelo destinatário. Então você deve nove mil e duzentos pesos.";
			link.l1 = "Por esse preço, deveriam ter me trazido isso em alto-mar, direto na minha cabine, junto com meu café da manhã! Pode ficar com a carta pra você.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "E por que eu não fui trabalhar nos correios?! Dá mais dinheiro do que pirataria! Aqui está sua prata, meu caro, entregue o envelope.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Foi um prazer fazer negócios com você! O Abade Benoit manda lembranças! Adeus, Monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Como quiser. Vou deixar o envelope no escritório do porto. Mas isso vai influenciar no preço, já vou avisando. E sim – o Abade Benoit manda lembranças.";
			link.l1 = "A carta do Abade Benoit? Por que não disse isso logo de cara! Deve ser importante!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "Então pegue com o mestre do porto. Não se esqueça de pegar um empréstimo antes. Adeus, Capitão de Maure.";
			link.l1 = "Já conheci piratas mais sinceros do que você. Boa sorte, meu caro.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Santo Padre, hoje o senhor chegou mais cedo que o habitual. Por favor, sua escolta está esperando. E você, senhor de Maure - o padre Vincento soube que está na cidade e faz questão de convidá-lo para jantar.";
			link.l1 = "Receio que o Inquisidor terá que jantar sozinho. Espero que isso não lhe tire o apetite. E o Abade Benoit também não fará companhia a ele. Você sabe quem eu sou, então lhe aconselho: deixe-nos passar sem problemas, e mande minhas saudações ao Padre Palotti.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Sim, já ouvi muito sobre você, e tenho ordens claras para não transformar a cidade em um banho de sangue se você insistir. Pode passar. Mas o Padre Vincento vai ficar... descontente. Tenha isso em mente.";
				link.l1 = "Você agiu com sensatez, monsieur. Vou sobreviver de algum jeito, embora meu coração doa com a decepção do padre-inquisidor. Tenha uma boa noite!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Sim, já ouvi falar de você... muitas coisas interessantes. No entanto, recusar convites assim é perigoso para a sua saúde, señor. Assim como sequestrar os convidados do Padre Vincento. Agarrem-nos!";
				link.l1 = "Cada um fez sua escolha. Lamento que tenha chegado a isso. Às armas, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, parabéns! Sabe, sempre gostei de você, e a Helen é como uma filha pra mim, então fico feliz por vocês dois. Poxa... derramar uma lágrima numa igreja era tudo o que eu queria. Será que estou ficando velho, hein?";
			link.l1 = "Está tudo bem, Jan, quase chorei no altar. Deve ter sido o incenso, né?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Certo, cânfora, droga. Eu estava me perguntando por que meus olhos estão ardendo e meu nariz coçando! Tá bom, vamos conversar em Sharptown, dar um abraço na Gladys e ir até os outros. Eles estão com uma cara como se a gente fosse assinar a Paz de Vestfália.";
			link.l1 = "Obrigado por ter vindo, Jan. Fico feliz em te ver, e isso significa muito para a Helen.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Finalmente você chegou, Charles! Minha corveta te ultrapassou por quase um dia – motivo e tanto para se orgulhar.";
			link.l1 = "De nada, Jan, mas onde está a Gladys, e a sua esposa?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Mandei a Gladys de volta para Blueveld num navio mercante – ela não gosta dessas festas agitadas. A Joanna não pôde vir – ah, nem tive tempo de te contar lá na Martinica! Imagina só – nessa minha idade, vou ser pai legítimo, acredita? Olha, se você se apressar, nossos filhos vão ter quase a mesma idade, hahaha!";
			link.l1 = "Jan, meus parabéns, isso é uma ótima notícia! Temos que brindar a isso!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Com certeza! Mas primeiro, um brinde a vocês dois! Ei, vocês aí, silêncio!!! O velho Diabo da Floresta precisa fazer um discurso!\nHum... Então, nossos queridos Monsieur e Madame de Maure... Droga! Não consigo falar assim! Charles, Helen – vocês dois, para mim, são como filhos, e eu sei que nesta sala não há ninguém que não esteja feliz pela união de vocês! Então vamos brindar, meus irmãos, à felicidade dos nossos fiéis amigos, a ventos favoráveis em suas velas e ao amor da Senhora Fortuna, tão forte quanto o sentimento que eles têm um pelo outro!!! Saúde!";
			link.l1 = "Saúde! Valeu, Jan... nossa, esse rum está bem mais forte que o normal... O que será que o Nathan colocou nele?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Não faço ideia, mas me parece certo. O Velho Hawk geralmente entende de bebidas. Vai lá, fala com os outros, preciso preparar drinks para umas cem almas sedentas querendo se fartar.";
			link.l1 = "O Diabo da Floresta servindo bebidas – que cena! Obrigado por assumir a organização da festa. Com certeza volto assim que terminar de dar uma volta – talvez alguém mais precise de ajuda.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Está tudo bem, Charles?";
			link.l1 = "Perfeito, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "E aqui está você, finalmente! Como foi em Martinica? Sente que sua vida mudou para sempre?";
			link.l1 = "Mudou muito antes, Jan. Mas tudo correu surpreendentemente bem. Onde está Johanna e...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? Assim que soube do que estávamos fazendo, a garota partiu e navegou rumo ao horizonte. Mandou muitos cumprimentos calorosos pra você, mas... você partiu o coração dela, de verdade. Mas vai ficar tudo bem, é só coisa de juventude.";
			link.l1 = "Bem, o coração quer o que quer, você entende.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Sim. Pois é, a Johanna não pôde vir, acredita? Olha só – já velho, vou virar pai de verdade, pode isso? Se você se apressar, nossos filhos vão ter quase a mesma idade, hahaha!";
			link.l1 = "Jan, meus parabéns, isso é uma ótima notícia! Temos que brindar a isso!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Com certeza! Mas primeiro, um brinde a vocês dois! Ei, você aí, silêncio!!! O velho Diabo da Floresta vai fazer um discurso!\nCharles e Mary, toda a Irmandade está erguendo seus cálices em homenagem a vocês! A felicidade dos verdadeiros amigos alegra a alma de qualquer lobo do mar, quase tanto quanto o brilho do ouro espanhol, ha-ha! Que naveguem bem, e que bons ventos acompanhem a jornada da família de vocês!!! Saúde!";
			link.l1 = "Saúde! Valeu, Jan... nossa, esse rum está bem mais forte que o normal... O que será que o Nathan misturou aqui?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Não faço ideia, mas me parece bem certo. O Velho Hawk geralmente entende de bebidas. Vai lá, fala com os outros, preciso preparar drinks para umas cem almas sedentas querendo se fartar.";
			link.l1 = "Esta taverna definitivamente precisa de um novo nome – 'O próprio Diabo da Floresta estava aqui atrás do balcão'! Obrigado, Jan, com certeza vou voltar assim que falar com todo mundo – talvez alguém precise de ajuda.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Como você está, Charles? E o casamento?";
			link.l1 = "Muito comovente, Jan. Fico feliz que conseguimos reunir todo mundo aqui. Parece que os barris de rum do Hawk já estão quase no fim, não é?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Sim, estão sim! Então, é hora de abrir o que você trouxe aqui. E outra coisa – aqueles caras que me ajudaram no começo já ficaram bêbados demais lá nos fundos. Você ainda está firme, noivo – pode trazer uma caixa de xerez?";
			link.l1 = "Claro, é só me dizer pra onde ir. Quem sabe eu encontre algumas cabeças sóbrias pelo caminho pra me ajudar. Embora, provavelmente, a maioria dos meus caras já esteja bêbada feito gambá.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "O vinho foi guardado nas adegas embaixo do estaleiro, lembra delas? O Hawk disse pra deixar no corredor do fundo, ''pra guardar até o feriado'' - foi o que ele falou. Também disse que a temperatura e a umidade lá são perfeitas, que seria o lugar ideal pra uma adega. Olha, ele é um verdadeiro metido.";
			link.l1 = "Ele tomou a decisão certa, Jan. Eu vou, mas antes, me diga – você viu minha esposa?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Ela e a Dannie foram para algum lugar. Deixa as garotas conversarem, Charles, a gente precisa começar uma festa de verdade. Vai até as adegas enquanto eu cuido da comida. Porque do jeito que está cheirando, daqui a pouco a gente vai comer carvão em vez de costela de carneiro!";
			link.l1 = "Certo, vá salvar a carne, eu vou buscar nosso vinho.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, o que aconteceu, vocês começaram uma briga de bêbados?!";
			link.l1 = "Não, Jan, nós lutamos juntos contra alguns batedores armados nas masmorras. Demos conta deles, mas eram apenas exploradores – o grupo principal está logo atrás de nós!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Esquadrão? Do que você está falando?! Marcus, vem aqui! Charles, vai, conta tudo pra gente.";
			link.l1 = "Como eu disse: tem uns desgraçados nas masmorras embaixo do estaleiro. Estão bem armados. O Nathan e eu lutamos com eles e, por milagre, derrubamos todo mundo. Mas tem mais vindo - ouvi um deles chamando reforço. E sim, um deles mencionou alguém chamado Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Eu reconheço esses rostos... esse aqui, e aquele desgraçado caído perto da porta. São capangas do Jacques, o Bondoso. Não lembro os nomes deles, mas tenho certeza disso.";
			link.l1 = "Então a culpa é do Barbazon? Ele ficou maluco ou o quê?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Não sei, mas parece que o Kindman decidiu aproveitar a oportunidade e promover uma mudança radical entre os barões da Irmandade.";
			link.l1 = "Neste caso, espero que ele apareça pessoalmente – faz tempo que sonho em encher o corpo dele de buracos. Desgraçado, arruinou meu casamento, só de pensar nisso! Vamos, para as ruas! Vamos receber nossos convidados como eles merecem!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "E aqui está o nosso herói exausto! Hah, Charles, essa foi boa! Jacques, que rato! Olha só como ele armou tudo – quase conseguiu!";
			link.l1 = "Sim, talvez devêssemos ter matado aquele desgraçado quando terminamos com o Jackman. Mas agora já era. Barbazon está morto.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Bem, não dá pra dizer que acabou – nossa vida continua! Mas eu estou completamente acabado. Já não tenho idade pra pular no mar de um navio em chamas e nadar até a praia por uma hora, de olho nos tubarões. Tomara que ainda tenha um pouco de rum...";
			else dialog.text = "Bem, não posso dizer que acabou - nossa vida continua! Droga, me sinto dez anos mais jovem! Faz tempo que não lutava assim! Espero que seu estoque de rum e vinho não tenha sido roubado no meio da confusão - precisamos brindar isso direito!";
			link.l1 = "Sim, eu também beberia, mas antes preciso verificar a residência, não sei se já te avisaram ou não...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "É sobre o seu amigo índio? Sim, eu soube, como foi que aconteceu?";
				link.l1 = "Ele pulou para proteger minha esposa e a Dannielle de uma bala disparada por um desgraçado. Vamos indo, eu te explico no caminho.";
			}
			else
			{
				dialog.text = "É sobre o Nathan? Sim, eu ouvi, só não entendi como aconteceu?";
				link.l1 = "Ele se jogou na frente para proteger nossas esposas de uma bala disparada por algum desgraçado. Vamos indo, eu te conto no caminho.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Fique firme, Charles. Sinto muito pelos seus rapazes. Hoje, muitos homens bons caíram, e por cada um deles, Barbazon terá mais combustível para sua caldeira no inferno.";
				link.l1 = "Não faz sentido... droga! É difícil, Jan... Já perdi amigos, mas não consigo me acostumar com isso. Não sei se consigo continuar.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Então aquele médico quieto? Sinto muito, Charles, de verdade. Ele era um bom homem.";
					link.l1 = "Sim, Jan, eu também. Mas temo que o mundo da ciência tenha perdido muito mais do que eu. Ele era um gênio... sofisticado, como todos eles, mas... porra...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Bem, parece que acabou. Hoje, muitos homens bons se foram, e por cada um deles, lá no inferno, Barbazon vai ter mais óleo na caldeira, mas "+sTemp+" vai ficar bem, e isso é o que importa.";
					link.l1 = "Você tem razão, Jan, e isso tira um grande peso da minha mente. E os outros barões? Estão todos bem?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "A última sujeira de Jacques Barbazon. Você tem razão, se tivéssemos matado ele antes, tudo poderia ter sido diferente.";
			link.l1 = "Mas de que adianta lamentar o passado? O que passou não pode ser mudado. E os outros barões? Todos sobreviveram?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Ninguém consegue se acostumar com isso. Vamos brindar aos nossos rapazes? Achei uma garrafa na mesa, milagrosamente sobreviveu a essa bagunça.";
			link.l1 = "Sirva, eu... Droga... mil maldições!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Me fale sobre eles. Esse médico parecia inteligente. Ele se expressou com tanta sabedoria.";
			link.l1 = "Ele fez isso. Mas, receio que o mundo da ciência tenha perdido muito mais do que apenas a mim. Ele era um gênio... sofisticado, como todos eles. O mestre dos milagres!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "Sobre o homem indígena? Onde você o encontrou?";
			link.l1 = "Rescued him from prison on Guadeloupe almost immediately after my arrival. Really funny and stupid story. So, he stayed with me. He chose to; I gave him freedom, but he stayed by my side – I saved him, and he thought he owed me till the end of his life. Terse, dressed oddly, but more loyal than any knight, he had a talent too – he could hit a coin with a musket mid-air at any distance.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Bem, ele te pagou a dívida, o que posso dizer. Salvou "+sld.name+" e Dannielle daquele desgraçado. Me parece um fim justo para um guerreiro tão corajoso.";
			link.l1 = "É sim, Jan. Vamos beber à memória dos que se foram... Que encontrem paz. E os outros barões? Estão todos bem?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Esta noite nos custou caro. Nem sei quando a Irmandade vai se recuperar desse massacre. Kindman escolheu o momento e o lugar perfeitos para atacar. Ele quase conseguiu — só mais um pouco e tudo teria sido perdido. Mas perdemos muito menos do que poderíamos.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "The Shark is in the infirmary, his ship took a volley from twenty-four pounders. He was thrown overboard, broke a couple of ribs, swallowed seawater, but he lives; in a few days he will be as good as new.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard só levou uns arranhões – ele estava defendendo a costa e limpando as catacumbas. Agora, está no porto, organizando hospitais para os feridos e funerais para os que não tiveram tanta sorte.";
			else dialog.text = "Bernard não teve sorte. Ele estava vasculhando as casas depois do ataque vindo das catacumbas e acabou topando com um bando daqueles desgraçados nos armazéns. Levou um tiro, bem na cabeça. É uma pena, era um bom capitão... Tyrex vai ficar furioso quando souber.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard só teve uns arranhões – ele estava defendendo a costa e limpando as catacumbas. Agora, está no porto, organizando hospitais para os feridos e funerais para os que não tiveram tanta sorte.";
			else dialog.text = "Bernard não teve sorte. Ele estava limpando as casas depois do ataque vindo das catacumbas e deu de cara com um bando daqueles desgraçados nos armazéns. Levou um tiro, direto na cabeça. É uma pena, ele era um bom capitão... Tyrex vai ficar furioso quando souber.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Sobre o Hawk, você sabe. A Dannie não vai deixar ele sair da ilha por pelo menos um mês, isso é certo. Ele só pensava em uma coisa... ah, deixa pra lá.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus continua tão firme como sempre. Assim que desembarcou, começou a arrancar a alma dos sentinelas que permitiram toda essa sujeira. Ainda consegue comandar a restauração da ordem na cidade. Um homem de ferro, sem dúvida.";
				link.l1 = "Ferro é mais macio. Acho que o nosso barão é feito de um metal que a ciência ainda nem conhece, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Only Marcus's situation is unclear; his ship was boarded, but the survivors claim he managed to jump overboard. I've already sent the longboats to search the bay. I hope it turns out our baron is tough enough not to give up so easily.";
				link.l1 = "Isso é ruim, mas ainda é cedo para lamentar por ele. Marcus não desistiria de nós tão fácil assim. Vamos esperar pelo resultado das buscas.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus nadou até a praia depois que seu navio afundou. Bem, você sabe, Tyrex não é do tipo que se afoga por tão pouca coisa. Agora ele deve estar em algum lugar da cidade. Provavelmente tirando o sossego dos sentinelas que deixaram passar toda essa sujeira. Um homem de ferro, sem dúvida.";
				link.l1 = "Ferro afundaria. Suponho que nosso barão seja feito de um material ainda desconhecido pela ciência, haha!";
			}
			else
			{
				dialog.text = "Marcus continua tão firme quanto sempre. Assim que pisou em terra, começou a arrancar a alma dos sentinelas que deixaram passar toda essa sujeira. Ainda consegue comandar a restauração da ordem na cidade. Um homem de ferro, sem dúvida.";
				link.l1 = "Ferro é mais macio. Acho que o nosso barão é feito de um metal que a ciência ainda nem conhece, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "É isso. Bem, podia ter sido pior. Até seu casamento, Charles, acabou sendo... turbulento. O importante é que vocês dois estão vivos. Um conselho, no geral... ame... e nem pense em desistir de lutar por isso!";
			link.l1 = "Obrigado, Jan. Obrigado a todos vocês... Preciso admitir, esqueci que começamos com uma comemoração.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Então, aqui vai um lembrete.";
			link.l1 = "É, aquilo foi uma... festa e tanto.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Ah sim, com certeza foi, espere um pouco. Tem uma coisa – parecia que você estava sempre com um homem indígena, não é? Sempre ao seu lado ou olhando em volta, como se alguém estivesse te mirando. Vestido de um jeito estranho, e chamava atenção no meio da multidão.";
			link.l1 = "Sim, Tichingitu, ele sumiu logo no começo dessa confusão. Pra ser sincero, já estou começando a me preocupar. Você sabe de alguma coisa?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Parece que sim. Nosso barman estava fazendo um escândalo porque a sobrinha dele foi sequestrada, supostamente antes do ataque. Ele diz que viram ela com um tipo de índio, que a carregou no ombro pela praia a leste da cidade. Eu não vi nenhum índio entre a escória do Kindman, mas lembrei do seu quando ouvi isso, então fiquei na minha. Você devia ir procurar por ele ou algo assim, antes que ele se meta em encrenca. Porque o barman ameaça matar ele se encontrar primeiro. Ele é gente boa, mas pela sobrinha ele arrancaria a cabeça de qualquer um.";
			link.l1 = "Sim, eu conheço esse tipo, pode deixar, e obrigado, Jan, vou procurar por ele agora mesmo.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Bem, no geral, é mais ou menos isso... Desculpe, não sou bom com discursos. E agora está ainda pior – essa noite esgotou todo mundo. Todos nós precisamos descansar pelo menos um dia – depois decidiremos como seguir em frente.";
			link.l1 = "Você tem razão, Jan. Eu devia ir, preciso esfriar a cabeça.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Está com boa aparência, Charles. Dormiu bem?";
			link.l1 = "Sim, nos deram uma casa aconchegante nos arredores da cidade. Até pensei que tinha sonhado toda a loucura que aconteceu ontem. E agora você aparece, Jan, com essa cara horrível. O que mais aconteceu?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Ah, não, não é nada, é só que ainda não dormi. Sabe... colocar a cidade em ordem depois de tudo o que aconteceu aqui não é tarefa fácil.";
			link.l1 = "Como estão Dannie e Nathan? Onde está todo mundo?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Descansando. Não incomode, Dannie avisou a todos que hoje levou as armas para a cama... Dodson está no mar, saiu para buscar mais navios para proteger a ilha e evitar que isso aconteça de novo, os outros estão enterrando os que partiram no norte da ilha.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus ainda não foi encontrado, mas a gente consegue lidar com isso, não se preocupe. Você já fez tanto por todos nós, então não se incomode. Tyrax vai voltar mais cedo ou mais tarde – nós vamos encontrá-lo.";
			else dialog.text = "Marcus terminou aqui e partiu às pressas no lugre de alguém para Hispaniola. Ele precisa resolver alguns problemas que surgiram depois da morte de Barbazon. Ele manda lembranças e deseja tudo de bom para você e sua esposa.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Well, the Brethren have withstood this blow. Soon, we shall rise even stronger than before. Kindman and Jackman have been undermining our unity for too long; now they're gone, and I feel in my heart that we shall make the Caribbean tremble more than once. The Golden Age is coming for those to whom laws and kings are no friends, remember my words.";
			link.l1 = "Seria bom. Não sei se conseguiria aguentar mais o Velho Mundo. Nunca imaginei, quando vim para cá, que me apaixonaria pela liberdade do mar, por essas cores selvagens dos pores e nasceres do sol, que encontraria a melhor mulher do mundo e... amigos em quem confiaria minha vida.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Bem, você já conhece o caminho, é só decidir. Em nossas casas, você será sempre bem-vindo.";
			link.l1 = "Obrigado, Jan. Isso significa muito pra mim.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "Mas antes, ainda falta uma coisa importante. Charles, enquanto você dormia, nós nos reunimos e decidimos\nComo Barbazon está morto, a Irmandade precisa de um novo barão. Como a maioria de nós estava aqui, e a decisão foi unânime, aqui está. Parabéns – você é o novo Barão de Le François. Mas espere... Eu entendo – você é um homem do mundo, e não tem tempo para cuidar dos assuntos deste belo lugar, então colocamos uma pessoa de confiança lá, e você pode fazer o que quiser. Só lembre-se – agora sua voz conta na Irmandade.";
			link.l1 = "Jan, eu... eu estou sem palavras... Isso é uma grande honra, eu nem sei...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Vamos lá! Você já provou seu valor com o Tyrex, e depois com toda aquela história do legado do Sharp. Você é uma bênção de Deus. Para você, nada muda – siga o plano, e na sua ausência, seu homem vai cuidar de tudo.\nTem um sujeito promissor, Jan David, ele é um dos Bucaneiros. Francês, um cara honesto, cabeça brilhante e sabe usar o que tem, igual a você. Mas vai levar um tempo pra eu encontrá-lo – parece que foi capturado pelos espanhóis, mas isso dá pra resolver, não se preocupe. Vou garantir que ele envie sua parte assim que estiver à vontade com o negócio.";
			link.l1 = "Eu realmente não esperava que as coisas acabassem assim. Bem, já que você já decidiu, que seja. O Barão Pirata Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Vida longa ao barão! Se alguém merece esse título, é você. Use-o com orgulho, e não se esqueça – agora você é um dos nossos, não importa quão bonito seja o uniforme que vista, aqui, bem debaixo dele, bate o coração de um verdadeiro pirata.";
			link.l1 = "Eu não sei, talvez você esteja exagerando... Mas vou fazer tudo o que puder para justificar sua confiança.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "O que você vai fazer agora? Voltar para a Europa, para o seu pai, para apresentá-lo à sua esposa?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Sim, mas antes preciso me despedir de alguém... Você sabe do que estou falando.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Talvez não tão cedo. Mais uma vez vou navegar pelo arquipélago, quero respirar esse ar de liberdade pela última vez.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Bem, você tem um navio, pode voltar pra casa quando quiser.";
			link.l1 = "Espero que sim. Obrigado, Jan, obrigado a todos vocês e até mais, meu velho amigo! Mande lembranças aos Hawks e ao Shark!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Sim, é difícil, mas precisamos fazer isso. Ao mar?";
			link.l1 = "Não, vou navegar para Antígua. "+sTemp+" descansar em paz em um lugar que foi nosso lar, por um tempo.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Diga algumas palavras gentis por mim também. E não se preocupe – daqui pra frente, nós damos conta sozinhos. Vai ficar tudo bem.";
			link.l1 = "Obrigado, Jan. Até logo, meu velho amigo! Mande lembranças aos Falcões e ao Tubarão!... Bem, então é Antígua.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Jovem, hoje você cresceu ainda mais aos meus olhos. Você fez tanto pela Helen que nenhuma palavra de gratidão seria suficiente. Só espero que continue cuidando dela. Se o pai dela estivesse vivo e visse isso, como ele ficaria feliz... ah, me desculpe.";
			link.l1 = "Está tudo bem, Gladys. Você atravessou o arquipélago para apoiar a Helen hoje. Nós dois realmente agradecemos sua visita com o Jan, obrigado.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, peço desculpas pela informalidade, mas vou dizer assim – Charles, meu amigo, fico realmente feliz por você! Se eu puder fazer algo por você ou por sua noiva, é só falar!";
			link.l1 = "Eu lhe agradeço, Barão, estou tão feliz, e quanto aos vinhedos que meu pai queria como dote, acredito que posso me redimir – felizmente, minha situação financeira durante meu tempo no Novo Mundo melhorou consideravelmente.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Sim, suponho que você pode comprar praticamente tudo o que quiser, Charles. Com licença, mas vou fazer minha parte como pai representante - Hoje mesmo vou escrever ao meu bom amigo, o Ministro das Finanças. Sua escolhida receberá um título de nobreza e, creio, vamos encontrar uma boa propriedade para ela, digamos, na Gasconha, entre aquelas confiscadas por dívidas, e atribuí-la a ela retroativamente. Assim, ninguém ousará dizer que o Chevalier de Monper encontrou uma esposa de posição inferior!";
			link.l1 = "Acho que não me preocupo com esse tipo de fofoca, mas obrigado, Barão. Mesmo assim, você não deveria";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Com certeza devo! Agora vá, Charles, dê atenção aos outros convidados. E mais uma vez, aceite meus mais sinceros parabéns!";
			link.l1 = "Minha esposa e eu agradecemos a você. Até logo, Barão.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, peço desculpas pela informalidade, mas vou dizer assim – Charles, meu amigo, fico realmente feliz por você! Se eu puder fazer algo por você ou por sua noiva, é só pedir!";
			link.l1 = "Obrigado, Barão, mas você já fez tanto por mim. Para nós, basta que tenha aceitado o convite.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Como eu não responderia, Charles! Mas escute – quero dar a você e à sua bela esposa um presente digno, mas não consigo pensar em nada que você não pudesse conseguir sozinho com dinheiro ou com a espada. Por isso, vou escrever ao meu amigo, o Ministro das Finanças em Paris, e quando você chegar à Europa, estará aguardando para assinar o rescrito real que eleva o nome de de Monper ao título de Barões de Monper! Não, nem uma palavra, isso é o mínimo que posso fazer por você.";
			link.l1 = "Eu nem sei o que dizer, Barão... Meu pai vai ficar tão feliz. Muito obrigado, de verdade.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, por favor, aceite meus sinceros parabéns! Sua escolhida é realmente uma maravilha! Acredito que hoje a moda colonial ganhou um belo... empurrão para um novo rumo. Sua originalidade sempre me fascinou! Que você e sua bela metade sejam muito felizes juntos!";
			link.l1 = "Obrigado, Barão. Você nos honrou com sua visita.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Como eu poderia ficar longe, meu amigo? Passamos por tanta coisa juntos e tenho orgulho de te chamar de amigo, Charles. Lembre-se – minhas portas estarão sempre abertas para você, aconteça o que acontecer.";
			link.l1 = "As portas da família de Monper estarão sempre abertas para você, Barão.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, meu amigo, este é um dia muito importante, e fico feliz que você tenha me convidado para compartilhá-lo com você. Nós dois percorremos um caminho longo e difícil, e tornar-me o pai representante da senhorita... por favor, me perdoe – Madame de Maure, é uma honra para mim, acredite. De todo o coração, desejo a vocês felicidade! E, por favor, me avise quando forem para a Europa – eu, como pai representante de sua escolhida, enviarei ao seu pai todos os presentes de casamento necessários. Acredite, ninguém dirá que a noiva do Chevalier de Monper é pobre ou indigna!";
			link.l1 = "Se me permite, Chevalier, a algumas milhas ao norte da propriedade Monper, há bons vinhedos, eles pertencem à família La Brigne e eu...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Nem mais uma palavra, meu amigo, nem mais uma palavra! Vou imediatamente escrever ao meu representante autorizado em Lyon – quando você chegar lá, esses vinhedos já terão sido entregues à pessoa que você escolher.";
			link.l1 = "Obrigada, Chevalier. Você tem razão – nossa... amizade já passou por muita coisa. Mas fico realmente feliz que você tenha compartilhado este dia conosco. Até logo, e mais uma vez, obrigada!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, meu amigo, este é um dia muito importante, e fico feliz que você tenha me convidado para compartilhá-lo com você. Passamos por uma longa e difícil jornada, e estar aqui hoje no seu casamento é uma honra para mim. De coração, desejo toda felicidade a você! E me avise quando for para a Europa – mandarei presentes de casamento dignos para o seu pai.";
			link.l1 = "Não há necessidade disso, Chevalier. Obrigado por aceitar o meu convite.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Como eu disse – é uma honra para mim! Mas espere, meu amigo, gostaria de lhe oferecer algo nesta ocasião – tenho certeza de que isso vai agradar tanto a você quanto à sua escolhida. Pedras lindas das nossas minas na Nova Guiana – mande engastar em uma bela moldura e Madame de Maure vai brilhar até mesmo na recepção real! Se conseguir convencê-la a usar um vestido, é claro...";
			link.l1 = "Oh, não precisava, chevalier. Muito obrigada mais uma vez.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, meu amigo, deixe-me te parabenizar! Passamos por um caminho longo e difícil, e fico sinceramente feliz de estar aqui hoje. Nosso Senhor é testemunha – você merece sua felicidade! Valorize e proteja isso – desejo muitos anos felizes pela frente!";
			link.l1 = "Obrigado, Chevalier, minha esposa e eu somos muito gratos.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, que festa maravilhosa, e quanta gente importante! Deixe-me desejar de coração muita felicidade, saúde e filhos que tragam alegria! Como dizemos - 'gor'ko'!";
			link.l1 = "Obrigado, Fadey, você me honrou ao aceitar vir.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Mas eu não entendo muito bem por que tem tanta gente aqui, como se a gente não fosse casar, mas fechar algum grande acordo comercial, e ainda assim não tem cerveja ou cachaça suficiente pro meu gosto... haha! Brincadeira, Charles, por que você ficou pálido desse jeito? Vem cá, me dá um abraço, seu capitão casado!";
			link.l1 = "Caramba... Fadey, você é forte como um urso!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Espere, Charles, não vá ainda – não é certo um convidado ir a um casamento sem presentes. Aqui, fique com estes. Sei que você tentou encontrar todas essas lâminas, e algumas delas claramente te agradaram. Então aceite – pendure-as na sua propriedade da família e lembre-se de Fadey Moskovit com carinho!";
			link.l1 = "Isto é um verdadeiro presente! Obrigado, Fadey. Estas são realmente armas maravilhosas, e prometo que ocuparão seu lugar de destaque na propriedade de Monper!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, que festa maravilhosa, e quanta gente importante! Deixe-me desejar de coração muita felicidade, saúde e filhos que tragam alegria! Como dizemos - 'gor'ko'! Me dá um abraço, capitão recém-casado!";
			link.l1 = "Caramba... Fadey, você é forte como um urso!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, eu não podia perder isso, parabéns a você e à sua escolhida de todo o coração! Sejam felizes! Sabe, há alguns meses casei minha filha com um bom homem, eles se amam, mas pra ser sincero, fiquei chateado por não ter sido você... Bem, deixa pra lá... nem sei por que estou falando isso - parabéns! Que vocês sejam felizes para sempre!";
			link.l1 = "Obrigado, Prosper, fico feliz que você tenha vindo.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Parabéns, capitão! Um ritual estranho, mas bonito – Tichingitu gostou. Embora, o capitão deveria simplesmente raptar sua índia e mandar um resgate para os parentes dela.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Bem, de certa forma, sim, e é só uma formalidade. Obrigado, meu amigo!";
			else link.l1 = "Bem, de certa forma, sim, foi só uma formalidade. Obrigado, meu amigo! Você e eu vamos conversar mais em Sharptown – lá vai ter bem menos assuntos oficiais e muito mais diversão de verdade, eu prometo!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Fogo-água de novo? Tichingitu não pode dizer que gosta disso. Talvez um saque comemorativo fosse melhor, ou pelo menos dançar ao redor de uma fogueira?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Espero mesmo que não acabe em danças ao redor da fogueira antes do final, e prefiro evitar abordagens. Tudo bem, tenha paciência – falta pouco, e vamos direto para a taverna.";
			else link.l1 = "Receio que acabaremos dançando em volta de fogueiras muito antes do fim, e eu prefiro evitar abordagens. Tudo bem, tenha paciência – falta pouco, e partiremos para Sharptown imediatamente.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitão, parabéns mais uma vez! Tichingitu está gostando desta celebração ainda mais do que da última. O capitão sabe escolher os amigos — aqui há mais sinceridade, menos hipocrisia e menos perucas falsas.";
			link.l1 = "Obrigado, meu amigo! Só não beba a aguardente – aqui ela é forte demais.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Obrigado, meu amigo! Vamos tomar uma bebida? Eu sei que você não gosta, mas hoje devia experimentar!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu não gosta de aguardente, mas se o capitão insiste, hoje pode ser. Pela sua felicidade, e pela sua mulher!";
			link.l1 = "E a você, Tichingitu! À sua amizade e lealdade!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Festa animada, capitão.";
			link.l1 = "Fico feliz que esteja satisfeito.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Capitão, veio admirar as estrelas? A noite promete ser muito bonita. Tichingitu ama a noite sobre o mar. É muito tranquila.";
			link.l1 = "Fico feliz em ver que você ainda está firme, meu amigo! Nathaniel e eu precisamos da sua ajuda – o pessoal na taverna ficou sem bebida, e precisamos trazer algumas caixas de aguardente do estoque embaixo do estaleiro.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Vamos em frente, capitão. Tichingitu te segue, como sempre.";
			link.l1 = "Beleza, vamos nessa!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Capitão, tem gente por aí, e estão armados. Tichingitu ouve o tilintar das armas deles, e está ficando mais alto a cada segundo. Não gosto disso. Vamos nos esconder.";
			link.l1 = "Vamos lá, camarada – isso aqui é Sharptown, até pra ir ao banheiro o pessoal leva pistola. Ei, Nathan... ah, droga! Lá se foi mais uma garrafa. Se continuar assim, você vai quebrar todas! Fica em pé, caramba! Ha-ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Capitão... você... a cabeça de Tichingitu está girando como um mastro em tempestade. O que aconteceu?";
			link.l1 = "Eu ia te perguntar o mesmo! Onde você esteve esse tempo todo?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu acordou há uma hora por causa dos gritos dessa garota. Ela correu pela praia quase nua, gritando algo sobre sequestradores e selvagens... Mas não há ninguém aqui além de nós. Você tem um pouco de água? Não daquele tipo ardente de novo, Tichingitu agora detesta aquilo.";
			link.l1 = "Tinha uma garrafa por aqui, se eu não a perdi na batalha... aqui está. Como você conseguiu fazer isso? O tio dela, que é um bartender local, está procurando o índio que sequestrou a sobrinha dele, e está ameaçando despedaçá-lo, cabeça de vento emplumada e tudo mais. De quem você acha que ele está falando?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu lembrou. Ela estava ajudando o Diabo da Floresta na taverna com o casamento. Nós bebemos aguardente juntos, e Tichingitu queria mais. E então, essa índia... ela era tão bonita e... Capitão, acho que lembrei! Tichingitu queria se casar com ela... Ele queria construir uma canoa e levá-la embora... Espíritos de misericórdia! Pessoas muito ruins apareceram com aguardente. Talvez demônios ou espíritos malignos! Tichingitu nunca mais vai...";
			link.l1 = "Levar ela embora? Construir uma canoa?! Ahah, você é um romântico, meu amigo... Ha-ha... ha-ha-ha-ha-ha-ha ai, eu não aguento... não consigo parar de rir!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Capitão, Tichingitu roubou a índia, sim... mas, será que a gente, bem... pode não se casar agora? Ela é... barulhenta como um papagaio e... não é tão bonita.";
			link.l1 = "Sim, meu amigo, mulheres que se divertem a noite toda não são um espetáculo bonito de manhã. Não se preocupe, herói-amante, vamos dar um jeito. Vamos, precisamos voltar para Sharptown, você perdeu o embarque das férias...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Um ataque? O capitão falou de uma batalha antes. Os pensamentos ainda não obedecem Tichingitu. O que aconteceu na cidade?";
			link.l1 = "Uma verdadeira batalha em terra e no mar. Os canhões dispararam a noite toda, imagino que até em San Jose dava pra ouvir. Mas você estava ocupado com outra 'batalha', tudo bem, eu entendo... Vamos, eu te conto tudo no caminho.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Obrigado, capitão... Tichingitu nunca vai...";
			link.l1 = "É, 'o garanhão das planícies distantes', você definitivamente não devia beber mais. Vai dormir um pouco. Eu mesmo já estou quase caindo de cansaço.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Capitão, parabéns mais uma vez! Tichingitu está gostando ainda mais desta celebração do que da última. O capitão sabe escolher os amigos – aqui há mais sinceridade, menos hipocrisia e menos perucas.";
			link.l1 = "E muito mais aguardente. Aliás, vai beber comigo? Eu sei que você não gosta, mas hoje temos uma ocasião especial!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu não gosta de aguardente, mas se o capitão insiste, hoje pode ser. À sua felicidade, e à sua mulher! Que caminhem juntos, e que o sol e a lua sempre iluminem o caminho de vocês.";
			link.l1 = "Obrigado, meu amigo. Um brinde a você, Tichingitu! À nossa amizade!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Grande ... celebração, estou muito feliz por você, Charles. Embora eu ainda não te entenda... Segurar uma rosa inestimável nas mãos e trocá-la por... uma flor do campo. Mas o coração quer o que quer... Seja feliz, meu amigo. Que você viva feliz para sempre!";
				link.l1 = "Na flor que você segura, o mais bonito é o sentimento que tem por ela. Sem isso, é só um pedaço de carne murchando. Fico feliz que tenha vindo, Sua Graça.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Que dia maravilhoso, meu amigo, e que ocasião especial! Aceite meus sinceros parabéns! Casei-me três vezes, e em cada uma tremi como se fosse a primeira, ah, juventude...";
				link.l1 = "Monsieur, você ainda está longe da velhice, não desanime. Obrigado por ter vindo, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Espere, Charles. Você me entendeu mal, eu estou sinceramente feliz de todo o coração! E sim... aqui, pegue. Nosso amigo em comum pediu especialmente que você recebesse isso hoje.";
			link.l1 = "Eu acho que sei de quem é. Obrigado, e até logo.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Uma cerimônia encantadora, não é, Charles? Estou realmente feliz por você! Em meu nome e em nome de todos os cidadãos de Basse-Terre, ofereço nossos parabéns a você e à sua... encantadora esposa. Vocês formam um casal maravilhoso! Que sejam felizes para sempre!";
			link.l1 = "Obrigado, Vossa Graça. Fico feliz que tenha gostado.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Que serviço maravilhoso, monsieur de Maure, simplesmente maravilhoso! E a noiva está tão... original com esse traje. Em nome de todos os moradores da nossa cidade - aceite meus mais sinceros parabéns! Desejo muitos anos felizes pela frente!";
			link.l1 = "Obrigado, Vossa Graça.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Tão encantadores – você e sua noiva, monsieur de Maure, formavam um casal único! Mas você é realmente um homem extraordinário. Desejo a vocês uma vida longa e feliz juntos. Que sejam felizes para sempre!";
			link.l1 = "Estou muito agradecido a você, Vossa Graça.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Pelo seu casamento, valeu a pena atravessar o Caribe! Parabéns, capitão, em nome de todos os habitantes das colônias inglesas! Você e sua noiva—desculpe, sua esposa agora—formam um casal maravilhoso!";
			link.l1 = "Muito obrigado pela visita e pelas palavras gentis, Coronel!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "E o que esse dândi casado está fazendo na minha praia de piratas, hein?! Me diga, monsieur, o que você fez com meu velho amigo - o temido Pirata Charlie Prince?";
					link.l1 = "Charlie Prince está morto, você se lembra disso, Marcus... Ha-ha-ha, vem cá, seu diabo do mar! Que bom te ver! Como vocês estão por aqui, já chegou todo mundo?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "E o que esse dândi casado está fazendo na minha praia de piratas, hein?! Me diga, monsieur, o que fez com meu velho amigo – o temido Capitão Charles de Maure?";
					link.l1 = "Ah, Marcus, que bom te ver também! Como vocês estão por aqui, já chegaram todos?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "E o que esse dândi casado está fazendo na minha praia de piratas, hein?! Diga-me, monsieur, o que fez com meu velho amigo – o temido Capitão Charles de Maure?";
				link.l1 = "Ah, Marcus, que bom te ver também! Como vocês estão por aqui, já chegaram todos?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Sim, o Diabo da Floresta chegou ontem mesmo e já começou a dar ordens — então os convidados estão aqui e tudo está pronto para a celebração. Seu navio foi visto perto dos recifes, e os rapazes não resistiram — correram para a taverna e, provavelmente, já abriram aquele barril do Falcão. Apresse-se, talvez ainda dê tempo de dividir um copo — Nathaniel se gabou dizendo que era um rum especial!";
			link.l1 = "É assim que a gente faz - direto do navio pra festa! Vou esperar minha cara-metade e já estamos logo atrás de você, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Sim, o Diabo da Floresta chegou ontem mesmo e já começou a dar ordens – então os convidados estão aqui e tudo está pronto para a celebração. Seu navio foi visto perto dos recifes, e os rapazes não resistiram – correram para a taverna e, provavelmente, já abriram aquele barril do Hawk. Apresse-se, talvez ainda dê tempo de bebermos um copo – Nathaniel se gabou dizendo que era um rum especial!";
			link.l1 = "É assim que a gente faz - do navio direto pra festa! Vou esperar minha cara-metade e já estamos logo atrás de você, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Casei com Charles de Maure – ainda não me acostumei com isso... Primeiro Svenson, agora você – e depois? O pastor Marlow, ou Jacques, o Bondoso?";
			link.l1 = "Você esqueceu dos Falcões. E você, Marcus? Não está cansado de ser um lobo do mar solitário?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie e Nathan já são um caso antigo – eu já me conformei com isso, mas você me surpreendeu, tenho que admitir! Agora, a pupila do Diabo da Floresta é uma beleza – de verdade, sempre pronta tanto com as palavras quanto com a pistola, e encara qualquer tempestade. Duvido que você encontre mulher mais valente. Você é um sortudo, capitão – cuide bem dela!";
			}
			else
			{
				dialog.text = "Dannie e Nathan já são um caso antigo – eu já me conformei com isso, mas você me surpreendeu, tenho que admitir! Embora, pelo que ouvi, sua Mary entende muito de espadas e sabe usá-las – meus respeitos! Uma verdadeira companheira de armas. Vou te contar um segredo: por uma moça dessas, até eu pensaria em largar a vida de solteiro. Você é um homem de sorte, capitão – cuide bem dela!";
			}
			link.l1 = "Eu sei, ela é um milagre e eu estou mais uma vez nas nuvens de felicidade – exatamente como naqueles dias em que nos conhecemos!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Então, um brinde!... Ao amor!... Mas não àquele que nos leva além do limite e até o horizonte!... E sim àquele que nos espera nesse limite! Ao amor que nos chama de volta, mesmo dos confins do mundo e das montanhas douradas! Viva com ele e seja feliz!";
			link.l1 = "Ótimo brinde, Marcus, obrigado!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Um brinde ao seu casamento, camarada!";
			link.l1 = "Obrigado, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? Isso definitivamente não é bom...";
			link.l1 = "Marcus, você acha...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Não há tempo! Eles estão atrás das portas! Todos, preparem-se para lutar!";
			link.l1 = "Lá vamos nós!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Não me lembro da última vez que me diverti tanto numa festa! Ainda não acabou! Está ouvindo isso? Tem alguém atirando lá fora! Vamos espalhar o sangue deles pelas ruas!";
			link.l1 = "Espera! Quem diabos são eles!? E o que, pelo amor de Deus, eles querem?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitão de Maure recém-casado, raramente encontrei motivos tão autênticos para um brinde. Levante seu copo – esta não é uma bebida de repolho qualquer. Está infusionada com chá preto da Índia Oriental e temperada com especiarias persas de verdade!";
			link.l1 = "E eu fico me perguntando por que arde na minha garganta como se eu tivesse bebido chumbo derretido. Bem, Nathan, saúde...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Espere, primeiro um brinde! Ei, senhores, levantem suas canecas! Hoje, nosso amigo e companheiro Charles de Maure está embarcando no caminho da vida em família. Aceite de nós nossos mais profundos pêsam... ah, Dannie, por favor, abaixe essa arma! Parabéns, claro! Agora vocês são as velas do mesmo navio, então naveguem juntos por qualquer tempestade até as costas mais férteis!";
			link.l1 = "Muito obrigado, Nathan, de coração. Você e Danielle são um exemplo para todos nós.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Que bom ouvir isso. Minha esposa e eu talvez não sejamos o melhor casal do mundo, mas somos felizes juntos, e você fez tanto por nós que, se quer saber, considero você parte da minha família. Estarei aqui sempre que precisar de mim. Seja feliz, e por favor, tome um drinque!";
			link.l1 = "Vamos beber então! Ah... esse rum devia estar no arsenal da Santa Inquisição. Maldição! Queima até a alma... aghhh! Ufa!... Eu gostei!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Você se parece tanto comigo e com o Dannie de vinte anos atrás!";
			link.l1 = "Mais uma caneca, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "O quê!? O Jan te mandou lá para os porões buscar vinho? Vamos dar uma volta, eu te ajudo, e um pouco de ar fresco vai nos fazer bem.";
			link.l1 = "Mas onde estão Dannie e "+sld.name+"? Jan me disse que eles foram conversar.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Sim, Dannie sabe que a presença até mesmo da melhor companheira de armas ainda não permite que os cavalheiros de fortuna relaxem completamente. Então, elas ouviram todos os elogios que receberam e foram para a residência, deixando os homens se divertirem.";
			link.l1 = "Então vamos nessa! Consegui tomar umas canecas, mas que droga, agora sim é hora de ficar realmente bêbado!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Então, aqui está o baú. Pegamos o máximo que conseguirmos carregar e depois voltamos, antes que esse velho rabugento nos tranque aqui dentro.";
			link.l1 = "Você exagera, Nathan. Ele não é tão ruim assim... Espera, você ouviu isso?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan provavelmente já encontrou mais homens e os mandou para nos ajudar. Droga!";
			link.l1 = "Vamos lá, as garrafas se quebram para dar sorte. Toma mais uma e vamos.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "O que diabos está acontecendo, quem são esses desgraçados? Você entende alguma coisa disso, Charles?";
			link.l1 = "Eu não sei, Nathan, mas um deles saiu correndo para buscar ajuda, e parece que estou ouvindo mais passos. Precisamos voltar para a taverna!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Acabamos com esses desgraçados, mas os canhões estão rugindo no mar, está ouvindo? Só temos duas tripulações prontas pra batalha, na fragata do Marcus e na corveta do Jan. Eu, Dannie e o resto desembarcamos nossos homens – afinal, é um casamento – então o Centurion está fora. E o seu navio? Temos que decidir o que fazer, e rápido!";
			link.l1 = "Desembarquei metade da tripulação, espero que o resto esteja sóbrio. Mas antes, preciso encontrar minha esposa e ter certeza de que ela está bem.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Sim, Dannie também sumiu. Então é o seguinte – Tyrex e Svenson já correram para o porto, vão chegar aos navios de bote. Nós vamos para a residência buscar as esposas, o resto deve organizar a defesa na praia. Você pode mandar alguns dos seus oficiais reunir a tripulação no seu navio? Uma ajuda lá não vai fazer mal.";
			link.l1 = "Certo, pessoal, vamos nos mexer! Cada segundo conta!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Mais rápido, lá em cima! Dannie e "+sld.name+" eles têm que estar lá! E se esses desgraçados fizerem algum mal a eles...";
			link.l1 = "Nem pense nisso! Lá pra cima! Vamos!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Droga! Seu amigo se jogou na frente da arma praquele desgraçado não atirar nas garotas!";
			link.l1 = "E ele levou um tiro... Espera, Nathan... ele está respirando! Ele ainda está vivo! Droga, preciso do Gino! "+sld.name+", querida, como você está?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Estamos bem, Charles! Vou desamarrá-la. Ouço tiros no porto – você e Nathan precisam ir até lá, senão Barbazon vai destruir todos os nossos navios. Não percam tempo!";
			link.l1 = "Vou encontrar o Gino e mandá-lo para cá, ele vai ajudar ... ele tem que ajudar! "+sld.name+", querida, fique aqui, cuide dele, vocês dois.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, anda logo! Seja qual for sua decisão, agora o tempo vale ouro! Se os navios do Jacques chegarem à costa, tudo terá sido em vão!";
			link.l1 = "Sim, eu sei. Maldito desgraçado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Mais rápido, não temos tempo para conversar!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Droga! Me perdoe, Charles. Ficamos presos lá em cima, havia uma dúzia daqueles desgraçados... É uma pena que não cheguei a tempo, mas vejo que você lidou com a situação da melhor forma possível.";
			link.l1 = "Não posso dizer que foi fácil, mas, caramba, senti um prazer enorme em matar aquele 'bom homem'! Está na hora de desembarcar, Nathan. Nosso pessoal está nos esperando lá!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Sim, precisamos visitar o seu garoto índio, terminar aqui e depois ir para Sharptown.";
			link.l1 = "Você tem razão, estou logo atrás de você.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Aliás, encontramos o Marcus! Ele estava no porão de carga, amarrado e desacordado.";
			link.l1 = "Ele está vivo?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Ele está bem machucado, mas vai ficar bem. Tyrex é duro na queda, então não se preocupe, ele já foi transferido para o seu navio e pediu um sabre.";
			link.l1 = "Finalmente, uma boa notícia! Certo, vamos terminar aqui e voltar.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Olá, Charles. Deixe-me dar uma olhada em você – ficou ainda mais bonito, não posso reclamar! Quase como o Nathan, uns dez anos atrás! Entre, não fique parado na porta, todos estavam esperando por você!";
			link.l1 = "Obrigada, Dannie, estou muito feliz em te ver! Vou até você e o Nathan daqui a pouco, aí a gente conversa!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, sente-se - Nathan e eu estamos muito felizes por você! Marcus, Jan e meu marido prepararam algo para você - mas os presentes vão esperar. Por agora, deixe-me te parabenizar e desejar toda felicidade! Sua amada é realmente uma maravilha! Me diga, você conseguiu fazer ela usar um vestido branco lá na Martinica, conseguiu?";
			link.l1 = "Obrigada, Dannie. Sim, toda essa história com o vestido acabou sendo bem divertida – tenho certeza de que nosso casamento gerou muitos boatos escandalosos na alta sociedade. Todo mundo fingiu não ver nada e agiu como se tudo estivesse perfeitamente normal. Etiqueta, essas coisas – mas não ligo para fofocas, eu amo ela, e isso é o que mais importa.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Você está absolutamente certo! Eu também fui ao altar, com uma espada e um par de pistolas escondidas atrás da faixa. Mas foi em Port Royal, antes mesmo de virar uma residência colonial respeitável. Naqueles tempos, a diversão era tanta, até mais do que em Tortuga sob Levasseur, e ninguém se espantava... eh. Mas veja só, fico aqui tagarelando – vá cumprimentar os convidados, todos estavam te esperando aqui, só me dá um abraço!";
			link.l1 = "Ah Dannie, como eu poderia te recusar, ha-ha! Você não faz ideia de como minha esposa e eu estamos felizes em ver todos vocês!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Vocês formam um belo casal, Charles!";
			link.l1 = "Obrigado, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, ele está certo... você não tem escolha. Não acredito na misericórdia de Jacques, o Bondoso, se ele lidar com Tyrex e o resto. Você sabe o que precisa ser feito.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Não dê ouvidos a ele! Se o Kingman resolveu fazer uma loucura dessas, não vai poupar ninguém!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Estamos bem, Charles! Vou soltá-la. Ouço canhões no porto, você e Nathan precisam ir até lá, senão Barbazon vai afundar nossos navios como patinhos em um barril. Não perca nem um minuto!";
			link.l1 = "Vou encontrar o Gino e mandá-lo para cá, ele vai ajudar ... ele tem que ajudar, droga! "+sld.name+", querida, fique aqui e cuide do Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, não!!!";
			link.l1 = "Ele aproveitou o momento e correu até o canhão para te proteger, Dannie... "+sld.name+", querida, como você está?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Sim, Charles, ele está vivo! O coração dele mal está batendo, mas ele está vivo! O que fazemos?!";
			link.l1 = "Precisamos do Gino, agora mesmo! Vou procurá-lo e mandá-lo pra cá, ele vai ajudar... ele tem que ajudar!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, não temos tempo! Se os navios do Jacques chegarem à costa, tudo terá sido em vão! Meu marido... ele fez o que precisava fazer. Agora é a sua vez. Eu vou ficar com ele. Vocês dois devem ir atrás do Gino!";
			link.l1 = "Sim, eu sei. Maldito desgraçado, ele vai pagar por isso!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Finalmente você chegou! Está todo mundo bem?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Estamos bem, Dannie, não se preocupe. Jacques está morto, os navios dele estão no fundo do mar. Como está Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Estamos bem, Dannie, não se preocupe. Jacques está morto, os navios dele estão no fundo do mar. E o Nathan?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Ele está bem! Seu médico italiano é um gênio! Nathan está dormindo lá em cima, mas, segundo o Gino, nada ameaça ele. Uma ou duas semanas de cama, vinho tinto e, como ele disse, 'a visita de uma dama bem disposta a ele' aham... Enfim – está tudo certo, você nos salvou de novo, Charles, como posso te agradecer?";
				link.l1 = "Foi o Nathaniel quem salvou minha esposa e você. E vou ser eternamente grato a ele por isso. Você nem imagina o quanto fico feliz em saber que ele está se recuperando. Deixe-o descansar, depois volto para ver como você está.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Ele está bem, a bala atravessou direto, e nosso cirurgião do 'Centurion' não estava longe. Ele estava se escondendo de toda essa confusão. Então o Nathan vai sobreviver, só precisa de umas semanas de repouso – nada demais!";
				link.l1 = "Dannie, ele protegeu minha esposa e você de uma bala, e vou ser eternamente grato a ele por isso. Você nem imagina o quanto fico aliviado em saber que ele está se recuperando. Deixe-o descansar, depois volto para ver como vocês estão.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Claro! Mas preciso ir agora, tenho que encontrar meu marido... Você se importa se levarmos seu amigo? Quando Nathan estiver melhor, eu mesma o levarei até Antígua. O Centurion sobreviveu milagrosamente, só precisa recrutar uma nova tripulação.";
			link.l1 = "Tá bom, Dannie, manda um oi pro Gino e pro Nathan. Eu já vou indo.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Claro, Charles, mas... eu tenho más notícias. Aquele italiano, Guineili, que esteve no seu casamento... Encontraram o corpo dele em um quarto da taverna. Eu... eu sinto muito, Charles.";
			link.l1 = "O quê? Gino?! Não! Como?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Não sei, provavelmente um daqueles desgraçados que passaram pelas catacumbas e atacaram a cidade. Pelo visto, eles estavam escondidos lá, esperando uma chance de fugir, e acabaram encontrando ele...";
			link.l1 = "Maldição! Não, não acredito nisso...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Me desculpe, Charles. Foi um massacre sangrento, e ele não era um lutador... Se quiser, podemos enviar o corpo dele para o seu navio, assim você pode levá-lo para casa e dar a ele um enterro digno. Sinto muito mesmo...";
			link.l1 = "Obrigado, Dannie. Dê a ordem para colocarem o corpo em um navio. Preciso ir agora... Tenho que pensar. E mande lembranças ao Nathan.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Ele está bem! Seu médico italiano é um gênio! Ele está dormindo no quarto lá em cima, e o Gino está cuidando dele. Ele disse que 'em uma ou duas semanas ele vai estar bem'.";
				link.l1 = "Ótima notícia! Mas acho que ainda não posso visitá-lo, certo?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Me desculpe, Charles. Encontrei o nosso cirurgião do Centurion, mas ele não pôde fazer nada... Seu amigo morreu há algumas horas.";
				link.l1 = "Tichingitu?! Não! Eu não acredito!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Não, o italiano proibiu terminantemente que o incomodassem, deixou-o descansar, e o Gino merece um descanso depois de tanta preocupação. Eu até disse "+sld.name+" sair para dar uma volta quando descobrimos que tudo ia ficar bem\nE mais uma coisa... seu amigo, ele me protegeu da bala. Nem sei como agradecer a ele. Diga que, a partir de agora, ele também faz parte da nossa família. E você – você nos salvou de novo, Charles!";
			link.l1 = "Está tudo bem quando termina bem, Dannie. Vá até o Nathan, ele está te esperando, e eu vou descansar um pouco aqui e procurar meu "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Desculpe, eu fiz tudo o que pude, e "+sld.name+", também. Ele nos protegeu daquela bala, e eu nunca vou esquecer isso, pode acreditar.";
			link.l1 = "... Há muito tempo ele disse que morreria por mim... Acho que ele nunca imaginou que sacrificaria a vida por todos nós... e agora ele é um herói, e vou me lembrar dele como nada menos que isso... Onde está "+sld.name+"? Ela está bem?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Não posso afirmar isso... Quer dizer, fisicamente, sim. Mas... sabe... Ela disse que saiu para caminhar, para esfriar a cabeça. Provavelmente viu seu navio ancorado e deve voltar logo.";
			link.l1 = "Maldito seja, Jacques Barbazon... Devíamos ter matado ele antes!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Espere... isso não é tudo ainda. Aquele italiano, Guineili, não é? Aquele rapaz quieto. Ele foi... encontraram o corpo dele numa taverna... Não sei, provavelmente foi um daqueles desgraçados que passaram pelas catacumbas e atacaram a cidade. Pelo visto, eles estavam escondidos lá, esperando uma chance de fugir, e acabaram encontrando ele...";
			link.l1 = "E o Gino também?! Hoje realmente é um dia de azar...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Me desculpe, Charles... Se quiser, podemos enviar os corpos deles para o seu navio, levar os homens para casa e enterrá-los como merecem. Sinto muito de verdade...";
			link.l1 = "Obrigado, Dannie. Faça isso... Eu preciso ir... Preciso... pensar.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, você faz ideia de quantos corações de moças você partiu com esse seu casamento? Aposto que metade das garotas do arquipélago ficou de luto depois do seu casamento, haha!";
			link.l1 = "O que posso fazer - eu só precisava de uma e consegui. Mas ainda é cedo para as garotas ficarem chateadas, porque elas ainda têm você, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "E é verdade! Vamos terminar aqui e eu cuido deles na hora, droga! Vamos lá, Charles, vamos brindar à sua sorte e à vida em família. Então, como dizem, felizes para sempre!";
			link.l1 = "Obrigado, meu amigo!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "A uma vida familiar feliz, ha-ha!";
			link.l1 = "Saúde!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, você faz ideia de quantos corações de moças você partiu com esse seu casamento? Aposto que metade das garotas do arquipélago ficou de luto depois do seu casamento, haha!";
			link.l1 = "O que eu posso fazer – eu só precisava de uma e consegui. Mas ainda é cedo pras garotas ficarem chateadas, porque elas ainda têm você, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "E é verdade! Vamos terminar aqui e eu cuido deles na hora, droga! Vamos, Charles, vamos brindar à sua sorte e à vida em família. Então, como dizem, felizes para sempre!";
			link.l1 = "Felizes para sempre!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Para uma vida familiar feliz, ha ha!";
			link.l1 = "Um brinde!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, então você também virou um homem casado e entediante, igual ao nosso velho Nathan! As aventuras e tudo mais ficaram no passado, hein? Agora é um homem de família de verdade!";
			link.l1 = "Espere aí, Bernard! Minha esposa não é dessas que ficam entediadas sentadas à janela de uma casa em ruínas! A única coisa que vai mudar é o peso das bolsas das garotas de bordel daqui até Curaçao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Não foi uma grande perda, eu digo! Melhor ter uma moeda de ouro do que um saco de trocados. Vamos beber! Um brinde a você e à sua esposa! Guarde bem seu ouro e seja feliz!";
			link.l1 = "Obrigada, Bernard. Nossa, esse rum é forte mesmo. Ufa!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "Para sua noiva, digo, já sua esposa!";
			link.l1 = "Obrigado!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Você chegou na hora certa, Charles, obrigado!";
			link.l1 = "Qual é a graça aqui? Achei que vocês já estivessem embarcando nos navios no porto.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus me deixou para organizar a defesa na praia. Estamos com poucos homens, o pessoal do porto precisa de pólvora. Pensei em passar aqui, pegar uns barris... e aí esses bandidos apareceram. Hah, deviam estar escondidos, esperando a poeira baixar ou prontos pra roubar alguém. E eu ainda tô cheio do rum do Hawk, então sem você, nem sei se estaria vivo agora.";
			link.l1 = "Você é sempre bem-vindo. Certo, Bernard, garanta que a cidade esteja segura, e eu preciso ir. Se cuide!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitão, permita-me parabenizá-lo de coração a você e à sua amada neste dia tão especial! Sejam felizes e cuidem um do outro!";
			link.l1 = "Obrigado, Gino. Fico feliz que você tenha decidido vir! Espero que o... colorido local não te incomode?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Esta é... uma viagem muito educativa. Preciso dizer - faz muito tempo que não saio de Antígua, e nesta sociedade não é fácil para mim me sentir à vontade. Mas você sempre soube entender as pessoas, então vou tentar ficar tranquila, porque confio em você.";
			link.l1 = "Talvez você precise beber algo mais forte? Relaxe e encontre alguém para conversar?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Thank you, captain, I've had enough watered wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for conversation, I tried to discuss the healing properties of Chirik-Sanango with that gentleman over there; it is also called Manaka. The natives of Maine use it for...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to have your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "À sua saúde, e à saúde da sua encantadora esposa!";
			link.l1 = "Obrigado, amigo!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Capitão, é você, graças a Deus! Aqueles mascarados, eu os vi e me escondi aqui, e eles tentaram arrombar a porta...";
			link.l1 = "Está tudo bem, Gino, ninguém vai te machucar mais. Foi uma sorte eu ter te encontrado, preciso da sua ajuda. Meu amigo está ferido – levou um tiro e perdeu muito sangue. Temos que nos apressar!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Tiro... sangue... Estou bem, capitão. No caminho pra cá, peguei meu baú de remédios com todos os instrumentos, caso alguém se ferisse. Me leve até ele, vou ver o que posso fazer. E aqueles... homens mascarados, talvez tenham se escondido em outro lugar?";
			link.l1 = "Tenho certeza de que eles foram os últimos. Gino, está acontecendo uma batalha no porto e eu preciso ir até lá agora. Você tem que ir para a residência sozinho, não é longe. A casa grande fica logo na esquina – você não vai errar. Não tenha medo – as ruas estão cheias dos nossos, e vá logo, estou te implorando!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Capitão, permita-me parabenizar de coração você e sua amada neste dia tão especial! Sejam felizes e cuidem um do outro.";
			link.l1 = "Obrigado, Gino. Fico feliz que você tenha decidido vir! Espero que a viagem tenha corrido bem?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Está tudo bem, capitão, obrigado pela sua preocupação. Preciso dizer - faz muito tempo que não saio de Antígua, e entre a elite eu... não me sinto muito à vontade. Mas o motivo da vinda não me deixou escolha. Aliás - o serviço foi excelente, fico muito feliz por vocês dois! A noiva está encantadora com esse traje - é uma nova moda? Acho que fiquei para trás na vida, mas gostei, de verdade.";
			link.l1 = "Moda... De certa forma, sim, ou pelo menos, em breve será. Tudo bem, divirta-se, Gino, e se os nobres interlocutores começarem a te entediar, venha para o porto. A tripulação toda está na taverna. Os rapazes vão ficar felizes em te ver.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Capitão, mais uma vez, parabéns para você e sua bela esposa! Desejo muitos anos longos e felizes juntos!";
			link.l1 = "Obrigado, Gino. Fico feliz que você veio! Espero que o... clima local não te incomode?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Essa sociedade não é fácil para eu me sentir à vontade. Mas, você sempre soube escolher as pessoas, então vou tentar ficar tranquilo, já que confio em você.";
			link.l1 = "Talvez você precise beber algo mais forte? Relaxe e encontre alguém para conversar?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Obrigado, capitão, já tomei vinho aguado o suficiente. O álcool, devo avisar, não faz muito bem ao fígado e talvez ao coração. Quanto à conversa, tentei discutir as propriedades curativas do Chirik-Sanango com aquele cavalheiro, também chamado de Manaka. Os nativos do Maine o utilizam para...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all of its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to be in your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Agora, sozinho em terra estranha, sentindo-me um estranho, neste dia de festa tão alegre, sinto ainda mais saudade dos meus parentes";
			link.l1 = "Longway, eu nunca imaginei que você fosse um mestre das palavras!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Desculpe, Capitão, estive pensando muito. Essas são palavras de Wang Wei – um poeta que viveu durante a dinastia Tang, que governou há muito tempo na minha terra natal.";
			link.l1 = "Essas palavras são tão bonitas. Espero que um dia você veja sua terra natal novamente...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''É possível garantir e saber que, sob o arco das misteriosas lajes de pedra, é impossível, ao tentar passar, encontrar uma passagem além da qual se encontra o vale U-lin?'\nNão, Capitão, você sabe disso – Longway não vai voltar para casa. Agora, aqui é meu lar e hoje temos um grande evento! Desejo tudo de melhor para você e sua linda noiva! Que a felicidade de vocês seja tão longa quanto o rio Yangtzé, salpicada de diamantes de estrelas, entre as pérolas de lótus.";
			link.l1 = "Obrigado, meu velho amigo. Suas palavras são tão belas quanto as de Wang Wei.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Vamos tomar um gole, Capitão! Este rum afasta a tristeza e traz de volta a alegria tão bem quanto o maotai.";
			link.l1 = "À sua saúde, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Grande casamento, capitão!";
			link.l1 = "Beba e divirta-se!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Dispare uma bala de corrente! Todos os nossos homens te parabenizam! Como foi o tiro?";
				link.l1 = "Está tudo certo, Charlie! Agora sou oficialmente casado e respeitável, e minha imediata é a Madame de Monper agora.";
			}
			else
			{
				dialog.text = "Me acerte com uma bala encadeada, que evento, capitão! Quase todo barão da Irmandade está aqui! Aposto que todo puritano espanhol imagina o Inferno assim! E o rum, isso sim é especial, uma bala encadeada no meu barril!";
				link.l1 = "Sim, as pessoas aqui não são as mais obedientes à lei, mas nós mesmos também não somos santos, Charlie, e cada uma dessas pessoas me é querida à sua maneira.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "É maravilhoso, tiro de corrente no meu traseiro! Capitão, quero dizer, esta celebração é em sua homenagem, bem, eu... eu parabenizo, quer dizer... também... Felicidades e... isso, não sou bom com discursos. Mas você precisa saber que todos nós amamos vocês dois e vamos segui-los até o inferno, capitão!";
				link.l1 = "Obrigado, velho amigo.";
			}
			else
			{
				dialog.text = "Espera, quero dizer... O que eu tô dizendo, bala encadeada no meu traseiro?! Capitão, eu quis dizer que este dia é em sua homenagem, bem, eu... eu te parabenizo... e também... te desejo felicidade e... e desculpa, Capitão, acho que tô bêbado demais pra fazer discurso, bala encadeada no meu pescoço, faz tempo que não fico sóbrio ha-ha-ha!";
				link.l1 = "Hah! Tudo bem... obrigado, velho amigo.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah! E sim, capitão, por favor, aceite isto. Para você e sua dama. Guardei essas pedras para um dia difícil... Sei que ouro não lhe falta, mas elas não vão ser demais, não é?";
			link.l1 = "Charlie, você é realmente uma alma generosa, e essas esmeraldas vão ficar deslumbrantes nos brincos de família da Madame de Monper!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Bem, vamos brindar a isso, bala encadeada no meu... hm. Sejam felizes, você e sua bela companhia, capitão!";
			link.l1 = "Vamos sim, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Ótimo casamento, capitão!";
			link.l1 = "Beba e divirta-se!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Eu nunca imaginei, capitão, que um dia veria você se casar. Normalmente, o caminho que escolhemos leva a uma estrada solitária, direto para um túmulo esquecido. Pelo que me lembro, você é o primeiro a conseguir escapar desse destino. Isso merece um brinde extra, não é?";
			link.l1 = "É isso aí, camarada! E sinceramente, fico feliz que essa parte da minha vida ficou para trás. Saúde!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Um brinde a vocês e a uma vida longa e feliz juntos! Poxa, olhando pra vocês, lembro que eu mesmo já fui casado um dia.";
			link.l1 = "Você? Casado? Que novidade interessante! Mas o que aconteceu?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "O que, acha que eu sempre fui esse velho ciclope cheirando a pólvora e sangue, capitão? Mas não. Madame Tonzag, ela... ela me amava, eu acho. Mas então, aconteceu uma história desagradável. Nela, o casal Tonzag morreu, e só o Gaston Careca, com um monte de cicatrizes, conseguiu sobreviver.";
			link.l1 = "Desculpe, Hercule, eu não sabia...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Esqueça isso, capitão, essa história aconteceu há muito tempo. Mas agora, olhando pra você, acho que minha história ainda pode ter um final feliz. Então, vamos brindar a isso!";
			link.l1 = "Vamos lá, camarada. Sabe, desde o dia em que te conheci, sempre te vi como se fosse meu próprio pai, então quem sabe um dia você ainda tenha a chance de ser bisavô. Enfim, saúde! Preciso cuidar do resto, depois a gente conversa.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Grande celebração, Capitão!";
			link.l1 = "Beba e divirta-se!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Aí está o nosso capitão! Parabéns, você e sua esposa formam um belo casal! Que sejam muito felizes juntos!";
			link.l1 = "Obrigado, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Parece que você está sóbrio demais para o seu próprio casamento, capitão. Quer dar um jeito nisso? Peguei uma garrafa de xerez excelente no bar. Misturá-lo com o rum local cai muito bem!";
			link.l1 = "Eu até gostaria, mas alguém precisa ficar de olho nas coisas aqui. Caso contrário, em "+sTemp+" não será só a taverna que vai fazer falta quando o dia amanhecer.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Comida excelente e rum excelente, capitão! Um brinde a você e à sua jovem esposa!";
			link.l1 = "Obrigado!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Jovens, por que estão invadindo, posso saber? O estaleiro está fechado, não é óbvio? Voltem amanhã.";
			link.l1 = "Mestre, me desculpe incomodar, só vamos passar pelas masmorras. Temos suprimentos para o casamento, e a taverna está quase sem bebidas.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure e Nathan Hawk em pessoa! Vieram comemorar o casamento de alguém, não foi? Tudo bem – vão lá pegar uma bebida. Jovens têm mais é que se divertir – essa é a lei em qualquer época. Só não façam barulho com as garrafas na volta – vou dormir!";
			link.l1 = "Obrigado, mestre, seremos tão silenciosos quanto o rio mais calmo.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Vamos, não fique aí parado, vá! Então, capitão, está satisfeito com tudo?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "O que diabos?! Jacques disse 'Ninguém desce aqui'! Hugo - volte correndo, chame os outros, vamos abrir caminho. Matem eles, rapazes!";
			link.l1 = "Merda!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Rapazes, esqueçam os baús, temos visitas!";
			link.l1 = "Eu achei que canalhas como você tinham morrido junto com o Jackman. Tudo bem, vamos acabar com isso!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Maldição... Fomos encontrados! Alarme!";
			link.l1 = "Sai da minha frente, seu idiota!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, boa noite, ou já está quase amanhecendo? Entre, sente-se.";
			link.l1 = "Angerran De Chievous! Não me surpreende nem um pouco te ver aqui! Um homem insignificante, só capaz de lutar contra mulheres! Amarrando elas também, foi? Agora vou terminar o que comecei naquele duelo na Martinica!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Calma, rapaz, está vendo esta pistola? Ela tem dois canos. Talvez eu não seja grande coisa com a espada, mas sou um ótimo atirador – abaixe sua lâmina, ou vai perder a chance de conhecer umas belas damas, pode apostar.";
			link.l1 = "Bastardo... Maldito seja.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "E você, monsieur pirata, abaixe sua arma também, assim mesmo, isso. E agora – sente-se, pode servir o vinho – está ali na mesa. Teremos que esperar um pouco até que monsieur Barbazon termine de destruir os navios dos seus amigos, os barões piratas. Depois decidiremos como você e eu vamos resolver as nossas... hm, desavenças.";
			link.l1 = "Resolver desentendimentos? E como? Você quer um duelo?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Não seja engraçado, Charles. Você e Madame Botot me deram muito trabalho, e pretendo retribuir à altura. Embora ela tenha me causado bem mais problemas do que você... porém, se você e o imponente Monsieur Pirate ficarem quietos, dou minha palavra de honra – suas esposas continuarão vivas. Acredito que nas colônias espanholas do continente, escravos assim têm valor. Mesmo que não seja oficialmente. Mas ainda é vida, não é?";
			link.l1 = "Angerran, você é um covarde, um canalha e... Droga, ainda não existem palavras à sua altura em nenhuma língua!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Você sabe disso, não tem escolha. Só posso prometer que será rápido. Então, se se importa com essas mulheres – comporte-se, poupe a vida delas e facilite o seu destino. E sim – tranque a porta, se não for pedir demais. Obrigado.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Tantas mulheres guerreiras. Ainda assim, peço que sejam prudentes. Nunca gostei de matar mulheres.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Merda...";
			link.l1 = "Morra, desgraçado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Capitão Charles de Maure, Barão Hawk – que surpresa agradável! Permita-me apresentar: Mauritz Dussak, esse é o meu nome.";
			link.l1 = "Saia da minha frente, desgraçado! Onde está minha esposa?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Calma, senhores! Estão vendo esta pistola? Tem dois canos. Não me chamam assim à toa – adoro sabres, claro... mas também atiro muito bem, acreditem. Larguem as espadas, ou podem acabar perdendo alguns dedos!";
			link.l1 = "Vou te massacrar como um porco, verme...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Mas você já vai ser viúvo. Não é isso que quer? Então se acalme e abaixe sua arma. Barão Hawk, por favor, tranque a porta. Vamos nos acomodar e esperar um pouco, enquanto Jacques Barbazon lá no porto acaba com os líderes da Irmandade.";
			link.l1 = "E o que vem agora? Vamos nos abraçar e cavalgar juntos rumo ao pôr do sol?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Acho que não. Pela sua captura, Jacques vai me encher de ouro. Com sorte, talvez eu até vire barão. Quanto às suas mulheres, talvez as deixemos ir, mas você... infelizmente não. Se eu tiver sorte, vou pedir o direito de te matar eu mesmo, capitão. Você é um espadachim famoso – seria interessante te enfrentar. Sabe, eu também me considero um mestre.";
			link.l1 = "Um mestre em invadir casas à noite e amarrar mulheres meio adormecidas? Você é um verme, aliás - um verme patético!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Escute, senhora, eu nunca matei mulheres, não me faça começar, tá bom? Você está deixando o capitão e seu marido nervosos... Droga!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merda...";
			link.l1 = "Morra, desgraçado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Maldito francês, não tinha uma espada ou uma bala?!";
			link.l1 = "Sabe, Jacques, tenho as duas coisas pra você. Pra ser sincero, quase me arrependi de ter te deixado vivo quando descobri suas armações com o Jackman. Mas agora, vou consertar isso.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Você só é corajoso quando está cercado pelos seus próprios homens? Vamos mudar isso! Eu resolvo com os barões depois, mas você não vai sair vivo daqui, rato!";
			link.l1 = "Esperado...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Capitão, socorro, esse selvagem me sequestrou! Eu... eu preciso voltar pra casa – meu tio provavelmente já revirou a cidade inteira!";
			link.l1 = "Calma, linda, vai ficar tudo bem. Afaste-se, preciso falar com o seu 'selvagem'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Obrigada, capitão! Você me salvou! Quando acordei hoje de manhã nesta praia, eu... não consigo acreditar que ia me casar com esse selvagem, ele...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Sim, a manhã é um martelo severo para o cristal de esperança da noite. Eu entendo. Mas ele é da tribo Muscogee e vive segundo as duras leis da sua terra. Ele te levou com o seu consentimento, e vocês passaram a noite juntos. Então agora, aos olhos dos deuses dele, vocês são marido e mulher. Vamos, arrume suas coisas, e eu resolvo a questão do resgate com seu tio.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Me desculpe por isso. Tichingitu vive segundo as leis da tribo dele, mas é uma boa pessoa. Por favor, esqueça essa história de sequestro.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Esposa? Aos olhos dos deuses dele?! Não, capitão, por favor, me salve disso! Foi só... uma aventura, ele era tão galante e gentil, diferente desses brutos... Mas casamento? Sou jovem demais pra ir morar numa cabana com um selvagem!";
			link.l1 = "Ele é meu oficial e meu melhor amigo, então não se preocupe, eu pago bem a ele, e você vai ter a melhor cabana que poderia desejar. Tichingitu é um caçador habilidoso, ele vai providenciar comida para você, e você vai dar à luz e cuidar das crianças.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Crianças? Procurar comida?! Não, capitão, por favor, não faça isso comigo, eu te imploro!";
			link.l1 = "Well, maybe I can convince him. But it won't be easy. The Muskogue tribe is very serious about such things; if someone finds out that he stole a squaw and didn't get married...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Você tem que tentar, por favor! Eu não vou contar pra ninguém, ninguém vai saber! Eu minto pro tio, não é a primeira vez!";
			link.l1 = "Tudo bem, pode ir, bela índia. Vou tentar manter meu amigo afastado.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Ele me roubou como... como uma cabra do curral! Eu vou contar pra todo mundo! Meu tio vai matar ele! Ele fica terrível quando está bravo! Ele costumava assaltar navios espanhóis – com ele não se brinca!";
			link.l1 = "Certo, silêncio, bela dama, silêncio. Talvez vinte mil 'razões' para perdoá-lo sejam mais convincentes do que minhas palavras? Ou devo entregá-las ao seu tio, como um resgate por uma esposa? Afinal, todos estão na ilha, não é? Amanhã podemos organizar outro casamento...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Não, não, capitão, espere! Você me convenceu. Vou dar um jeito para que meu tio não fique bravo. Adeus! E até logo para você também, meu garanhão das planícies distantes! Venha me ver da próxima vez que passar por aqui...";
			link.l1 = "Isso mesmo. Que bom que concordamos. Corre pra casa, beleza.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Então, Capitão, está satisfeito com tudo? O melhor rum, costelas de cordeiro, presuntos de porco e até um excelente vinho da minha reserva pessoal para o seu amigo cientista! E - meus parabéns para você e sua bela esposa!";
			link.l1 = "Obrigado! Tenho que admitir, você organizou tudo perfeitamente. Espero que tenha rum suficiente guardado nas suas adegas, ainda falta muito para o amanhecer.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Não se preocupe com isso, se os barris secarem, mando um ajudante ao depósito do porto. Aproveite, monsieur, e não se preocupe com nada.";
			link.l1 = "Tudo bem, "+npchar.name+". Então vou até meus convidados.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "O que vai querer, capitão? Costelas fritas, presunto defumado ou peito bovino? Talvez um vinho para a sua companhia?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("À saúde do capitão e de sua esposa!","Que você viva feliz para sempre, Capitão!","Vida longa e felicidade para vocês dois!"),LinkRandPhrase("Viva o capitão e sua bela!","Que a sorte acompanhe o capitão e sua esposa por toda a vida!","Que os ventos sejam favoráveis à sua vida em família, capitão!"));
			link.l1 = LinkRandPhrase("Obrigado!","Obrigado!","Saúde!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Queria bancar o açougueiro? Todos os piratas estão furiosos com você, camarada, então é melhor cair fora daqui.","Parece que você enlouqueceu, camarada. Queria se meter onde não foi chamado? Sem ofensa, mas você não tem nada pra fazer aqui. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero acertar as coisas...","Me ajude a resolver o problema...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, estava esperando a sua visita, chefe. Jan Svenson me avisou que você viria mesmo conferir como estão as coisas em Le Francois. Tomei conta de tudo por aqui, e juro pelo trovão, essa vila vai prosperar muito mais do que jamais prosperou sob aquele maldito Kindman. Que os demônios se divirtam com ele nas adegas mais sombrias do inferno!";
					link.l1 = "Você é Jean David, certo? Svenson comentou algo sobre a minha parte...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" chefe. Tudo está tranquilo em Le François, como sempre. Por que você veio? Posso ajudar em alguma coisa?";
					link.l1 = "Só passei aqui para ver como as coisas estão indo.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "E a minha parte?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" camarada. Por que você veio? Posso te ajudar com alguma coisa?";
				link.l1 = "Só passei aqui para dar um oi.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Aos seus serviços, chefe! Quanto à sua parte – no quinto dia de cada mês, uma parte das moedas de ouro das façanhas dos nossos rapazes será reservada para você, e ficará guardada o tempo que precisar. A partir do mês que vem, pode vir buscar quando quiser.";
			link.l1 = "Legal!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "E eu cuidarei do resto. O Diabo da Floresta disse que você não teria tempo para se preocupar com assuntos tão triviais quanto Le Francois...";
			link.l1 = "Você ouviu certo. Muito bem, Jean, estou contando com você, espero que não me decepcione.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Vai ficar tudo bem, chefe. Está tudo sob controle aqui, haha, e que eu nunca mais beba rum na vida se eu estragar alguma coisa!";
			link.l1 = "Tá bom, até mais!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Esperando por você, chefe. Enquanto isso, reunimos para você "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Pegue.";
			link.l1 = "Ha, nada mal. Muito bem, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Eu faço o meu melhor, chefe. Volte no próximo mês ou quando quiser – seu dinheiro estará seguro comigo.";
			link.l1 = "Tá bom, até mais, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Resolver o problema? Você faz ideia do que acabou de fazer? Enfim, traga-me um milhão de pesos e eu convenço os rapazes a esquecerem o que você fez. Se não gostar da ideia, pode ir para o inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Certo, estou pronto para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Entendi. Estou indo embora.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Ótimo! Considere-se limpo de novo. Mas espero que não faça mais coisas tão nojentas assim.";
			link.l1 = "Não vou. Muito caro pra mim. Adeus...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
