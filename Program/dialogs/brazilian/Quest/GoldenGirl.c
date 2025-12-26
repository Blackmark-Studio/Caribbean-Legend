// диалоги персонажей по квесту Дороже золота
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
			dialog.text = "O que você quer?";
			link.l1 = "Eu devo ir...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Capitão Charles de Maure! Finalmente! Sua Excelência Jacques Dille de Parkuet está exigindo vê-lo! É urgente!";
			link.l1 = "Por que não estou surpreso? Muito bem, por favor, diga a Sua Excelência que estou chegando em breve.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "Meus olhos devem estar me pregando peças se não é o próprio Charles de Maure! Não recebo visitas assim com frequência e fico muito feliz que tenha encontrado um tempo para vir ao meu humilde claustro. Que sorte a minha! Isso merece um brinde!";
			link.l1 = "Minhas saudações, senhora. Perdoe-me se meus modos a desapontam – faz muito tempo desde que participei de... eventos assim. A etiqueta a bordo de um navio se resume à subordinação, lenços limpos e uma boa xícara de café fresco toda manhã.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Tão encantador, Capitão, você ainda mantém esse brilho parisiense. Consigo ver seu leve fulgor por baixo dessa máscara calejada e salgada. Não se preocupe, estou tão feliz por finalmente conhecê-lo que posso perdoar muitas coisas. Por enquanto. Vamos ver como as coisas vão entre nós no futuro. Vinho? Tinto ou branco?";
			link.l1 = "Seria o momento perfeito para uma piada sobre rum, mas infelizmente não estou no clima. Me desculpe. Vou beber com prazer qualquer coisa que suas lindas mãos me servirem.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Boa escolha. Mas eu insisto. O gosto por vinho revela muito sobre um homem, e pretendo descobrir tudo sobre você esta noite. Então pergunto de novo: tinto ou branco?";
			link.l1 = "Como quiser. Vejo que está bebendo vinho tinto. O mesmo para mim – também gostaria de saber mais sobre você.";
			link.l1.go = "Julianna_3";
			link.l2 = "Nesse caso, eu fico com o branco, mas você escolhe. Isso deveria funcionar para os dois lados, não acha?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Excelente, então agora é a minha vez? Este aqui é um Pinot Noir da Borgonha, os vinicultores o chamam de 'menina levada'. Não é uma variedade fácil de lidar e o seu retrogosto também pode ser bastante enganador. Satisfeito?";
			link.l1 = "Pinot Noir, hein? Funciona pra mim. Inconstante e misterioso, um sabor áspero no começo, mas deixe respirar um pouco e você vai se surpreender. Uma dança leve de nuances e sabores, escolha de quem entende do assunto. As primeiras impressões enganam, não é? Eu brindo aos seus olhos, madame!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Excelente, então agora é minha vez? Tenho um Sauvignon Blanc maravilhoso, direto do Vale do Loire. Bem selvagem, você quase sente borbulhar na língua. E o toque final – uma nota de pólvora. Acho que temos algo em comum.";
			link.l1 = "Eu esperava algo melhor, talvez um Riesling. Bem, vamos com esse bruto simples, cheirando a verão e pólvora. Já ouviu dizer que tem gente que confunde com pipi de gato? Vou brindar ao seu sorriso, tão brilhante quanto essas safiras!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Remarkable, Charles! May I call you that? I wasn't wrong about you; on a different day, you'd be the star of my night. But alas, my Captain, today you have strong competition. It appears we are on the verge of a scandal over there, do you see?";
			link.l1 = "Estou ouvindo vozes irritadas. Quem é esse monsieur desagradável, e o que ele fez para desagradar nosso estimado governador?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "This 'unpleasant' monsieur is Angerran de Chievous, an unrecognised bastard of Count de Levi Vantadur. You are entertaining their topic of argument. De Chievous has been trying to earn my favour for years, and he followed me here, thinking he can replace his father for me. Even though he is not a lawful son, he is rich and powerful. Stubbornness is another of his traits; for some people, it replaces wisdom. Just before your arrival, he and Jacques started arguing about the obvious subject. His Excellency always protects me in a very touching way, you should see! Come on, let's observe and see how it ends this time.";
			link.l1 = "Sinto problemas no ar... Por que sempre tem uma pegadinha, mesmo numa noite tão maravilhosa...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Como é, Charles?";
			link.l1 = "Esqueça. Por favor, me apresente ao seu amigo insistente, depois veremos...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, permita-me apresentar-lhe meu estimado convidado – o Capitão Charles de Maure, em pessoa, que nos honra com sua visita! Tais figuras ilustres raramente aparecem por aqui.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, não gosto do rumo que isso está tomando! Jacques não ouve meus argumentos, enquanto Angerran com certeza está tramando alguma coisa. Essa briga tinha um propósito, e eu preciso da sua ajuda!";
			link.l1 = "Receio não estar entendendo... O que eu poderia fazer aqui? Ele já recusou duelar comigo...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Capitão, por favor, não me decepcione. Há pouco você era um mestre da conversa, e agora seu mundo se divide entre coisas que pode cutucar com a espada e coisas que não pode. Pense fora da caixa! Vamos estragar o jogo do Angerran. Ele quer desafiar o pobre Jacques sozinho, mas isso é tão sem graça! Vamos fazer um torneio! Vários cavalheiros aqui podem apostar alto, e sua sorte já é conhecida como lendária! Quem sabe as cartas estejam ao seu favor esta noite?";
			link.l1 = "Não vejo bem como isso vai impedir o de Chievous de brigar com o nosso querido governador, mas estou dentro, madame. Qualquer coisa para tirar aquele sorrisinho da cara dele.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Perfeito, agora vá até a mesa e coma alguma coisa, vai ser uma longa noite. Quando estiver pronto, me encontre no salão, vamos precisar de mais espaço para isso. Enquanto isso, vou dar um show, convencendo os outros a me oferecerem espetáculos e jogos de alto risco. Talvez eu até grite com eles para ver se esses idiotas percebem uma dama morrendo de tédio. Por favor, não se envolva, ninguém pode saber que estamos do mesmo lado esta noite. Até logo, meu Capitão!";
			link.l1 = "O que a senhora disser, o que a senhora disser...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Bem, me dê os parabéns, funcionou! Um pouco de orgulho, um pouco de preconceito, e voilà! Faça uma cara de tédio, estão nos observando. Deixe que pensem que você está interessado na bebida, não em mim\nUm torneio está prestes a começar, as apostas são altas, não há segundas chances nem revanche. De algum jeito, eu sei que você está acostumado com isso. Você vai dar conta. Lembre-se, Angerran com certeza está tramando algo, ele vai agir contra nosso amigo Jacques, mas não contou com a sua chegada. Seja meu trunfo, porque ver aquele rosto confiante e convencido dele nunca é bom sinal. Temos oito jogadores, mas eu garanti que você não vai enfrentá-lo até a final\nAh! Seu primeiro adversário! Coronel e nosso comandante do forte. Mar contra terra – um desafio à altura para convidados com experiência militar! Palmas!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Você foi incrível, Charles, simplesmente esplêndido. Angerran e Jacques estão prestes a se enfrentar a qualquer momento. Pena que não ouviram e adiaram o torneio por uma semana. Eu poderia ter reunido uma festa realmente estelar, sobre a qual fofocas chegariam até Paris! Bem, talvez na próxima vez. Parece que seu próximo adversário está à altura da sua sorte, um verdadeiro lobo do mar, Capitão Moreno! Capitães, por favor!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Infelizmente, a sorte te abandonou, Capitão. Sinto muito, mas o jogo acabou para você. Angerran já está jogando contra Jacques, então devo ir. Adeus.";
				link.l1 = "Foi um prazer... senhora.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Parabéns pela vitória merecida, Capitão! Ainda não está claro quem vai te enfrentar na nossa final... Vamos dar uma afastada. Abaixe a voz e observe aquela mesa. Olhe, lá vai ele! Estou começando a entender o que Angerran está tramando! Ele já arrancou todo o dinheiro do pobre Jacques, mas não deixa o coitado sair da mesa. Quando passei por lá, o infeliz estava apostando uns documentos valendo um navio inteiro com carga. Infelizmente, a sorte não está do lado dele hoje à noite. Ou alguém mandou ela não estar.";
				link.l1 = "Acha que o de Chievous está trapaceando?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Infelizmente, sua sorte acabou, Capitão. Sinto muito, mas o jogo terminou para você. Angerran já está jogando contra Jacques, então devo ir. Adeus.";
				link.l1 = "Foi um prazer... senhora.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Ele com certeza poderia se quisesse, mas não tenho provas. Nosso querido governador é bom nas cartas, mas o adversário dele também é. Angerran nem piscou quando apostou sua fragata, acredita nisso? Se esse duelo fosse em Paris ou Lyon, viraria lenda, Charles! Mas pode ser que ele só esteja com sorte hoje à noite. Vamos nos aproximar e ver com nossos próprios olhos.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, me segura ou eu vou cair... Ou talvez não - esses idiotas nem vão perceber se eu desmaiar. Você viu isso? Jacques, maldita seja sua estupidez! Parece uma criança, meu Deus! Uma criança imbecil!";
			link.l1 = "Marquesa, acho que não estou entendendo.  O que está acontecendo naquela mesa agora?  Em que eles estão apostando?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Foi por minha causa, Charles. Nosso doce e tolo Jacques apostou em mim. Angerran descobriu seu único ponto fraco e atacou no momento exato.";
			link.l1 = "Maldição! Mas eu sou o próximo no torneio, eu poderia recuperar o maldito navio dele! Por quê?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Porque Angerran pensou muito bem e planejou tudo nos mínimos detalhes. Ouça, não temos muito tempo. Você precisa fazer o mesmo com ele. Tire tudo dele, pegue todo o dinheiro, todos os navios, provoque-o! Faça ele perder a cabeça por reputação, honra, paixão, qualquer coisa! Você viu como se faz esta noite. Encurrale-o e force-o a apostar alto\nEu te imploro, Charles! Estou disposto a tudo, mas não vou até ele. Não desse jeito! Nem o Conde Vantadur vai se opor a uma vitória honesta nas cartas, ele nem vai mexer um dedo para me ajudar. Veja, cartas são quase sagradas para gente nobre, malditos sejam! Você é minha última e única esperança, Charles!";
			link.l1 = "Não enterre nosso governador ainda, madame. Talvez ele ainda recupere o navio dele? A sorte é uma mulher... bem volúvel.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Você ainda não entendeu, não é? Sorte não tem vez naquela mesa! Angerran de Chievous controla tudo. Ele encontrou um jeito de ficar comigo e ainda manter o pai dele fora disso. Não faço ideia de quanto tempo ele vem planejando isso, mas agora ele está quase vencendo. Ele está comandando o jogo e só temos uma chance de mudar tudo. Aqui, pegue isto! Vou fingir, isso vai te dar um ou dois minutos. Use bem esse tempo.";
			link.l1 = "Marquesa... Alguém, por favor, ajude! Madame não está se sentindo bem! Depressa!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Não, não, estou bem... Está um pouco abafado aqui... Me desculpem, senhores. Vou sair um instante para tomar um pouco de ar fresco. Podem continuar sem mim.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Não agora e não em St. Pierre, mas conheço alguém. Eu te prometo, Angerran, essa será uma pintura digna...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, você é impossível! Aprenda a perder! Isso é só um jogo e você não pode prever tudo. Termine seu vinho e se vista – as regras continuam as mesmas – quem perde sai da nossa festinha aconchegante.";
			link.l1 = "Marquesa, espere...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "Isso já passou dos limites, senhores! Parem com isso agora mesmo! Estamos todos muito cansados depois de uma noite exaustiva, e receio que preciso pedir aos meus convidados que se despeçam. Vocês podem continuar essa discussão amanhã, como homens de honra, a menos que mudem de ideia. Mas ninguém vai sacar armas aqui, está claro?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, receio que também vou ter que pedir que se retire. Suba e pegue um quarto para você. Eu vou cuidar de tudo. Sou imensamente grata por tudo o que fez por mim, mas preciso de um tempo sozinha, e você deve estar exausto.";
			link.l1 = "Não está tão ruim, madame, mas não vou recusar uma cama. Essa festinha me pegou mais forte do que uma esquadra inimiga inteira. Sei que tudo isso também não foi fácil pra você, marquesa. Descanse um pouco e não se preocupe, você não me deve nada. Tudo o que preciso agora é de um pouco de sono.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Vou garantir que te acordem ao meio-dia. Já está amanhecendo, então não posso mais te desejar boa noite. Durma bem.";
			link.l1 = "Você também, Marquesa.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Aí está você, Charles. Para ser sincero, não consegui dormir nada, mas você parece descansado. Como foi sua noite? O café da manhã já está vindo.";
			link.l1 = "Sua hospitalidade é lendária, madame, mas receio que não tenho tempo para aproveitá-la. Sua Excelência, os segundos de de Chievous, os navios que conquistei – tudo isso está à minha espera.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Você não ganhou só os navios. Tem outra coisa que eu queria te perguntar, Charles...";
			link.l1 = "Não sou nem Jacques nem Angerran, marquesa. Não aposto mulheres para conquistar o favor delas. Você não me deve nada.";
			link.l1.go = "Julianna_41";
			link.l2 = "Você está sob minha proteção, Marquesa. Nem Jacques nem Angerran vão te incomodar, posso te garantir isso.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Ou você é incrivelmente honrado ou está apaixonado, Charles. E não por mim. Mas, de novo, sou eternamente grata a você de todo o coração. Se eu puder te ajudar em algo – é só dizer.";
			link.l1 = "Julianne, o tempo está se esgotando e tenho pela frente uma tarefa das mais difíceis. De Chievous é um canalha, e até mesmo um duelo honesto pode acabar como aquele que vimos ontem à noite. Vamos conversar depois que tudo isso terminar de vez. Agradeço pela chance de dormir em paz e espero te ver novamente em breve.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Sou grata a você de todo o coração, Charles... Acredite, ser seu prêmio também é uma espécie de vitória para mim. Que tal continuarmos essa conversa em um lugar mais... reservado?";
			link.l1 = "Julianne, o tempo está se esgotando e tenho pela frente a tarefa mais difícil de todas. De Chievous é um canalha, e até um duelo honesto pode acabar como aquele que vimos ontem à noite. Vamos conversar depois que tudo isso finalmente terminar. Obrigado por me dar a chance de dormir em paz, e espero te ver de novo em breve.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Não vou te atrasar mais, meu Capitão. Mas lembre-se, Angerran é perigoso. Não posso julgar suas habilidades de combate, mas ele participou de várias guerras e lutou em Rocroi. Também ouvi falar de alguns duelos que ele venceu, principalmente com pistolas. Acima de tudo, ele é um sujeito traiçoeiro, como você mesmo percebeu. Peço que tenha cuidado, e por favor, venha me ver depois!";
			link.l1 = "O cuidado lhe cai muito bem, marquesa. Acredite, de Chievous não é o primeiro canalha a cruzar meu caminho. Eu vou me virar. Agora, preciso mesmo ir falar com Sua Excelência sobre essa história de duelo.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Boa sorte, meu Capitão! E diga ao Jacques para ficar o mais longe possível das portas da minha casa.";
			link.l1 = "Dou minha palavra. Até logo, Marquesa!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Capitão, você conseguiu, que alívio! Como foi? Está ferido?!";
			link.l1 = "Não é o meu sangue... pelo menos não todo. Marquesa, onde está de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Eu ia te perguntar exatamente a mesma coisa – você não pegou ele? O que aconteceu? Por que metade da guarda da cidade está lá fora?";
			link.l1 = "Eu contei ao governador que você poderia estar em perigo. De Chievous foi ferido e fugiu, soltando seus capangas contra nós. Foi um massacre. Mas histórias assim não são para seus ouvidos delicados. Acabou. Você está livre dele e do nosso 'doce' Jacques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "Isto é muito ruim, Charles. Inimigos como Angerran de Chievous devem ser eliminados de vez quando se tem a chance. Conheço esse homem há muitos anos – ele não é do tipo que perdoa. Mais cedo ou mais tarde, ele vai dar um jeito de se vingar. Mas não gosto de ver você assim curvado, já cuidaram do seu ferimento?";
			link.l1 = "É só um arranhão, já passei por coisa bem pior. Dói um pouco, só isso. Obrigado por se preocupar comigo, senhora, mas eu devo ir...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Captain, you gambled for me, risking your ships and wealth; you fought for me in a deal, risking your life and career. The least I can do for you is tend to your wounds and give you a safe place to rest. No! I don't want to hear any more of this. Take my hand and follow me upstairs. Your room is waiting for you.";
			link.l1 = "Eu aceito sua oferta, senhora, obrigado. Mas prefiro não incomodá-la. Eu mesmo subo.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marquesa, você é meu anjo da guarda. Acho que agora sou eu quem lhe deve uma.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, você é um exemplo de cavalheirismo! Juro por Deus, se continuar assim, vou perder a cabeça! Tudo bem, meu cavaleiro, vou mandar a Denise até você, ela vai cuidar dos seus ferimentos como uma verdadeira médica.";
			link.l1 = "Obrigada, marquesa. Se meu coração já não estivesse ocupado, eu entraria nessa brincadeira com prazer. Mas, infelizmente! Boa noite!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "Neste caso, exijo que você me obedeça imediatamente. Segure minha mão e faça o que eu mandar. Denise! Traga ataduras, vinho quente e algo para comer lá em cima! Vamos, meu Capitão. E lembre-se – nada de discussões desta vez!";
			link.l1 = "Como quiser, marquesa, sou todo seu.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Bom dia, Charles. Como estão esses seus 'arranhões'?";
				link.l1 = "Graças aos seus esforços, sinto-me renascido. Por favor, aceite minha sincera gratidão, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Bom dia, meu herói. Como estão esses seus 'arranhões'?";
				link.l1 = "Obrigado pela sua preocupação, senhora, estou perfeitamente bem. Eu pagaria uma fortuna para ter sua Denise como médica do meu navio. Ela é um milagre!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Receio que não será fácil resolver isso. Mas eu jamais ousaria acordá-lo sem um motivo sério. Acredite, protegi seu sono com toda a coragem, mas esse homem lá embaixo está sendo muito insistente. Ele diz que faz parte da sua tripulação e que é urgente.";
			link.l1 = "Minha tripulação? Você fez bem em me acordar, marquesa! Vou partir imediatamente.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "Em outras circunstâncias eu iria, meu capitão, mas teremos que adiar. Um certo monsieur pouco instruído está te esperando lá embaixo. Ele diz que faz parte da sua tripulação e que é urgente.";
			link.l1 = "Voltaremos a isso, Madame, quando eu voltar. Espero que não seja sobre os espanhóis cercando a cidade de novo.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, você voltou! Que notícias o seu homem trouxe? Você nem se despediu!";
			link.l1 = "Peço desculpas, marquesa. De Chievous jogou sujo de novo. Ele roubou meu navio e partiu esta noite. Uma das minhas oficiais de confiança estava naquele navio e não posso deixá-la nas mãos daquele desgraçado.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Ela? Você tem uma oficial mulher servindo no seu navio? Isso vai contra tudo o que eu sei sobre navegação. O que te faz pensar que ela ainda está viva?";
			link.l1 = "Eu espero. Julianna, esperança é tudo o que me resta até agora. Preciso descobrir mais sobre Angerran de Chievous. Eu simplesmente preciso saber para onde ele foi! Eu tenho que trazê-la de volta!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Agora eu entendo! Você está mesmo apaixonado, meu cavaleiro! Eu daria de bom grado metade da minha vida por tamanha lealdade e devoção, sem pensar duas vezes!";
			link.l1 = "Eu não fiz nenhum voto, mas essa mulher significa muito para mim, marquesa.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Isto é comovente de tão ciumento. Ouça, Charles, estou pronta para sentir ciúmes de você! Mas qual cortesã conseguiria ficar surda à voz do verdadeiro amor? Além disso, você me salvou, meu cavaleiro, é claro que vou te ajudar. Pergunte o que quiser.";
			link.l1 = "Obrigado. Você conhece o de Chievous há bastante tempo. Para onde ele poderia ter ido, depois de toda aquela confusão, para esperar a fúria do pai passar?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "E se eu te convidar para um brunch? Faz dois dias que você não pensa nessa... moça, talvez ela possa esperar mais um dia?";
			link.l1 = "Marquesa, eu entendo como posso parecer aos seus olhos, mas o que está feito, está feito. Mesmo sem ter feito nenhum juramento, meu coração pertence a ela. Peço que me compreenda e me ajude.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Vamos lá, Charles! Se defender falando de amor diante de uma cortesã? Faz tempo que eu não rio assim! Você é incrível! Fique tranquilo, o que aconteceu nesta casa, fica nesta casa. Eu não esqueço o que te devo. Pode pedir.";
			link.l1 = "Obrigado. Você conhece o de Chievous há bastante tempo. Para onde ele poderia ter ido, depois de toda aquela confusão, para esperar a raiva do pai passar?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Para ser sincero, embora convidar Angerran de Chievous talvez não seja a coisa mais agradável a se fazer, ainda é muito útil politicamente. Ele é bem-vindo em qualquer lugar, inclusive entre as nações aliadas da França. Mas eu conheço apenas um homem por perto que sempre vai lhe dar apoio e abrigo. Francois de Lyon, o governador da nossa colônia de Guadalupe. Ele é um velho conhecido do Conde de Levi Vantadur e sempre teve uma certa simpatia por esse bastardo.";
			link.l1 = "Guadalupe, então! Esta é a melhor pista que eu poderia esperar! Se zarparmos ainda hoje, estaremos apenas um dia atrás deles.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Espere, Charles, tem mais uma coisa. Recebi uma carta para você recentemente. Achei que tinha a ver com o duelo, mas já não tenho tanta certeza. Aqui está.";
			link.l1 = "Sem selo, mas o papel é caro. Não gosto disso...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Vamos, Charles! Não me deixe na expectativa, é dele?";
			link.l1 = "Sim, é dele. Ela está viva! Ele a capturou enquanto roubava meu navio. Agora ele sugere que nos encontremos e conversemos sobre isso em um ambiente civilizado. Assim como você disse, Guadalupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "O Monsieur de Lyons com certeza vai escolher o filho de Leve Vantadur em vez de você. De Chievous pode armar outra armadilha para você! Você fez um inimigo muito poderoso ao me defender, Charles. Queria poder te ajudar, mas receio que tudo o que posso fazer é pedir que tenha cuidado.";
			link.l1 = "Julianne, eu nunca teria sobrevivido no Novo Mundo se sempre escolhesse o caminho mais direto. Negócios escusos não são meu ponto forte, mas eu sei como jogar o jogo.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Alguma novidade, capitão?";
			link.l1 = "Infelizmente, nada...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Bem-vindo de volta, Charles! Fico feliz que esteja vivo e bem. Quais são as novidades?";
			link.l1 = "Tudo o que sabíamos sobre as habilidades de de Chievous acabou sendo uma grande subestimação. O desgraçado está mantendo meu... oficial como refém, e tenho apenas duas semanas para juntar o resgate. Receio que não vou conseguir sem a sua ajuda.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, seu amor é como uma flor ao vento, mas eu lhe devo muito e vou ajudar no que puder. Como posso ser útil a você?";
			}
			else
			{
				dialog.text = "Charles, já te disse que nunca vou esquecer o que fez por mim. Vou fazer o que puder para retribuir. Estou pronto, mas ainda não entendo direito como posso ser útil para você nisso?";
			}
			link.l1 = "Por favor, sente-se, Julianna. Veja, o resgate de Angerran... é você. E não estou falando de proteção oficial, quero dizer como uma prisioneira acorrentada no porão do navio dele.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Estou sem palavras... Mas seu rosto me diz que isso não é uma piada. Ele perdeu o juízo?";
			link.l1 = "Na verdade, ele acredita que fui eu. Está tão desesperado que é capaz de ultrapassar qualquer limite.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "E o quê, você está me pedindo? Para não gritar durante o meu sequestro? Capitão, não acha que está pedindo demais? Eu lhe devo muito, mas salvar o amor de outra pessoa entregando minha própria vida nas mãos de um canalha sem glória... Você é o cavalheiro aqui, enquanto eu sou uma mulher extremamente realista e materialista.";
			link.l1 = "Receio, senhora, que é exatamente isso que estou lhe pedindo. Arrume suas coisas, nós vamos partir. Sinto muito por isso, mas o tempo é curto.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marquesa, eu não sequestraria uma mulher que confia em mim. E talvez essa seja a nossa chance.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Você realmente me surpreende, Charles. Ouviu isso? Toda a minha paciência com você acabou de se esgotar. Amor ou não, não vou deixar você me sequestrar. Guardas! Socorro!!! Alguém!!!!";
			link.l1 = "E eu achando que éramos amigos.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "Isto é um absurdo! O que você fez com a minha sala?! Que tipo de horror demoníaco é esse? Charles, recobre o juízo! Você é um nobre, não um maldito pirata!!";
			link.l1 = "Eu já te pedi desculpas. Pedi para você não complicar mais as coisas – mas você não ouviu. Acredite, eu não gosto do que estou fazendo, mas não tenho escolha. Vou fazer o que for preciso por causa daquela mulher.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Que tipo de dama escolheria um cavalheiro como você? Eu mesma vou, tire suas mãos de mim! Você não está roubando uma vaca, então mostre um pouco de dignidade!";
			link.l1 = "Certo. Venha comigo, senhora. Fique atrás de mim e mantenha a cabeça baixa – talvez eles comecem a atirar.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Por um instante, achei que não te conhecia de verdade, Charles. Esse olhar... Mas o que você vai fazer então? Que chance foi essa que você mencionou?";
			link.l1 = "Por que esse desgraçado me usa pra chegar até você? Por que ele armou aquele jogo de cartas em vez de simplesmente pegar o que queria? Do que ele tem medo?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Nada. Infelizmente, os motivos por trás de tudo isso são banais e primitivos. O conde Henri ainda tem um certo carinho por mim. Angerran arriscaria muito se fizesse algo contra a minha vontade. Sinto muito, Charles, mas não há saída. Ele vai negar tudo e sair impune. Ninguém vai acreditar nas palavras de você, o sequestrador, enquanto o pai dele vai acabar com você.";
			link.l1 = "Droga! Eu queria que não tivesse chegado a isso... Prepare-se, marquesa, precisamos ir. E sim, peço que fique em silêncio.";
			link.l1.go = "Julianna_76";
			link.l2 = "Mas o desgraçado deve ter outras fraquezas além do pai dele, não é? Ele não é perfeito, muito pelo contrário, é o oposto de perfeito!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Não sei se isso vai ser útil para... nós. Angerran teve alguns negócios com o barão pirata local. Jacques Baraban?";
			link.l1 = "É Barbazon, madame. Um casal simpático, os dois! Mas Jacques, o Bondoso, não gosta de mim, e não posso atacar Le Francois sem ter certeza absoluta.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Você está sendo direto demais de novo, meu cavaleiro. Lembra do Capitão Moreno? Seu segundo adversário no jogo? Aposto que ele veio aqui por causa do Angerran. Ele deve saber de algo valioso para nós.";
				link.l1 = "Capitão Moreno, hah! Sim, claro. Ele ainda está na cidade? Onde posso encontrá-lo?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Você está sendo direto demais de novo, meu cavaleiro. Sempre tem alguém que sabe de alguma coisa, e nem todo mundo consegue ficar de boca fechada em certas situações. Meus... pupilos ouvem coisas, nesta casa. Me dê um dia e eu vou descobrir mais, ou então vou encontrar alguém que saiba.";
				link.l1 = "Marquesa, eu achava que a preocupação combinava com você, mas a raiva combina ainda mais. Obrigado, você está me dando esperança!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Sim, ele ainda está aqui e vou poupar você do trabalho de sair por aí procurando por ele. Venha aqui amanhã à noite – o Capitão Moreno estará esperando por você aqui, neste quarto. Gostaria de poder fazer mais do que isso, mas não posso, Charles.";
			link.l1 = "Já é mais do que suficiente, marquesa. Com ele ao meu lado, tudo vai ser muito mais fácil. Obrigado. Até amanhã à noite.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Queria ter ouvido isso de você em outra situação, Charles. Venha me ver amanhã à noite. Espero ter o que você precisa.";
			link.l1 = "Muito obrigado mais uma vez, Julianna! Então, até amanhã à noite.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Aqui está você, meu amigo! O Capitão Moreno já está esperando por você.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, acho que encontrei algo. Lembra do Capitão Moreno? Aquele que jogou contra você naquela noite fatídica?";
				link.l1 = "Eu sei, que sujeito vagabundo. E quanto a ele?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Sempre soube disso, Bartolomeo de la Cueva. É por isso que você foi convidado para a minha festa desde o início. Foi como colocar pimenta na comida. Sei que você e seus homens estão rondando esta ilha há algumas semanas. Imagino que isso tenha alguma ligação com o barão pirata de Le Francois e Angerran de Chievous. Conte tudo ao meu amigo e manteremos seu nome lendário em segredo. Caso contrário, vou chamar os guardas que já estão atrás das portas. Mandei chamá-los assim que você chegou.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Não só eles! Angerran me deu um colar, lindo demais! Pérolas grandes, perfeitas, incluindo essa aqui, escura como uma noite no sul, bem no centro. Mas ele encomendou de joalheiros locais!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Aposto que ele não fez isso só para me agradar com um presente luxuoso. Embora, aquele presente tenha sido sua última cartada para conquistar meu favor sem ultrapassar os limites da decência. Angerran não tem títulos nem terras, e até a fragata dele só é dele enquanto o pai permitir. Ele se aproveita do poder e da influência, mas não tem renda própria. Talvez tenha se cansado de esperar pelas esmolas do pai e resolveu dar um jeito na própria situação financeira?";
			link.l1 = "Espere, senhora! O jogo de cartas! Se estivermos certos, e de Chievous planejou tudo isso com antecedência, ele deve ter precisado de muito dinheiro para as apostas, para pressionar nosso governador de verdade. Pedir essa quantia aos pais poderia chamar atenção indesejada para o caso. Roubar tesouros já roubados de corsários parece um jeito discreto e seguro de conseguir o dinheiro necessário. Ninguém ficaria sabendo!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "A nós, Charles! Angerran não pode sair impune dessa vez. O poder que ele tem sobre mim já passou dos limites e quero ajudar você a acabar com isso.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Um pirata fracassado e uma cortesã quase apaixonada. Charles, você montou um verdadeiro time dos sonhos pra si mesmo!";
			link.l1 = "Mesmo assim, obrigado, a vocês dois. De coração! Agora preciso pensar um pouco e bolar um plano.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Esta casa tem tudo o que seus hóspedes desejam. Vou providenciar tudo. Junte-se a nós quando estiver pronto, Charles.";
			link.l1 = "Muito bem, senhora.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Nada, mas tem alguém na cidade procurando por ele. Estão perguntando ativamente sobre você e os outros hóspedes daquela noite. Ainda não sei o que está acontecendo, mas tenho certeza de que você se meteu em algo maior do que imagina. ";
			link.l1 = "Algo maior? O que você quer dizer com isso, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... Quero dizer, Monsieur de Chievous me deu um colar de pérolas maravilhoso de presente. Uma das pérolas era negra como a noite. Achei que fosse só uma imitação com uma bela história por trás. Nunca usei, não queria dar falsas esperanças, mas é tão hipnoticamente lindo.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "O que você vai fazer, Charles? Você faz ideia do que está acontecendo?";
			link.l1 = "Ainda não, mas vou conseguir. De Chievous está até o pescoço em alguma encrenca séria e essa é a minha chance. O país dele não ousa mexer com ele, mas as autoridades britânicas talvez sim. Prefiro não precisar te sequestrar, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Isso é muito gentil da sua parte, Charles, mas não tem muita graça.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, você descobriu alguma coisa? Você está nervoso... O que aconteceu?";
			link.l1 = "Droga! Queria que as coisas fossem diferentes... Arrume suas coisas, precisamos ir, marquesa. Por favor, não cause problemas.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, entre. O Baronet já chegou e tivemos uma conversa agradável. Eu estava justamente contando a ele sobre seu interesse nos acontecimentos recentes.";
			link.l1 = "Julianne, não tenho tanta certeza se isso foi sensato...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baroneto, parece que seus homens acabaram de deixar cair algo atrás da porta! Poderia pedir a eles que se comportem melhor?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Horrível! E agora, o que fazemos?!";
			link.l1 = "Droga! Queria que as coisas fossem diferentes... Arrume suas coisas, precisamos ir, marquesa. Por favor, não cause problemas.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Deus do céu! O que vocês fizeram com a minha sala, senhores?! Isso aqui parece um pesadelo medieval! Quem são essas pessoas? E onde estão os guardas?";
			link.l1 = "Está tudo bem com você, Julianne? Ótimo. Aposto que os guardas estão gastando o suborno bem merecido numa taverna. Barão, meus parabéns - você conseguiu irritar o Goodman Jack de verdade. Uma tentativa de assassinato tão bagunçada e mal planejada não é nada o estilo dele.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Peço desculpas por interromper essa conversa animada, mas a menos que alguém aqui esteja ferido, vamos para um gabinete. Uma cena dessas não é nada agradável para uma dama... Só o teto está sem sangue!";
			link.l1 = "Então suba, marquesa. Você realmente deveria se deitar um pouco e se afastar de todo esse sangue. O baronete Cortney e eu vamos conversar sobre isso. Podemos continuar?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, está pronto para compartilhar seu plano conosco?";
			link.l1 = "Quase isso. Me diga, o de Chievous é do tipo pedante? Ele mantém seus livros e registros em ordem?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran é a própria personificação da procrastinação quando se trata de dinheiro! Ele assina mais papéis do que qualquer banqueiro que conheço. Acho que ele sempre foi assim desde a infância, quando não sabia quem era seu pai e vivia na pobreza pelas ruas.";
			link.l1 = "Excelente! Agora, precisamos do diário e dos livros dele! Eles servirão como prova para os britânicos. Precisamos descobrir como conseguir isso! Queria ter sabido disso quando o navio dele estava em minhas mãos... ai.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Espere, Charles, você realmente acha que depois de tudo o que aconteceu eu vou me deixar ser vendida para o de Chievous como se fosse uma cabra de fazenda?";
			link.l1 = "Não se preocupe, Julianne, vai levar só alguns dias. Prometo que vão te tratar como um vaso chinês de valor inestimável. Me corrija se eu estiver errado, mas o de Chievous nunca aparece nessas trocas, não é?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Tenho certeza disso. Angerran vai ficar sob a proteção de François de Lyons e nunca vai ousar te enfrentar em alto-mar. Mas sobre essa minha captura...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, desculpe interromper, mas você não esqueceu de perguntar minha opinião sobre tudo isso? Semanas dentro desses caixotes apertados... Você tem ideia do que está me pedindo?! Está claro que você está apegado àquela... garota, mas eu não sou um dos seus marujos! Me desculpe, mas nada disso parece uma história de amor séria.";
				link.l1 = "Receio, marquesa, mas vou ter que insistir. Não posso me dar ao luxo de perdê-la.";
				link.l1.go = "Julianna_127";
				link.l2 = "Todos nós cometemos erros, Julianna. Se tem alguém que entende isso, é você. Estou pedindo a sua ajuda.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, me desculpe interromper, mas você não esqueceu de perguntar minha opinião sobre tudo isso? Semanas dentro desses caixões apertados... Você tem ideia do que está me pedindo?! Seus sentimentos são dignos dos romances de cavalaria, mas eu sou apenas uma cortesã comum. Eu admiro você e quero te ajudar, mas tudo tem um limite!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Eu entendo, Charles. Eu quero acreditar no amor verdadeiro e perfeito, mas acho que isso não existe neste mundo.";
				link.l1 = "Obrigada, marquesa. Desta vez, vou fazer tudo certo. Aprendi muito com essa história, e rezo para que eu não pague um preço alto demais pelo que fiz.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Você já tomou sua decisão, eu te apoiei o tempo todo, mas chega. Sacrificar tudo por um amor que você já tinha deixado para trás no meu quarto. Tudo isso é muito comovente, Charles, mas eu não sou mais tão jovem nem ingênua.";
				link.l1 = "Receio, marquesa, mas preciso insistir. Não posso me dar ao luxo de perdê-la.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Bem, Capitão, faça como quiser. Não vou resistir, mas saiba que estou fazendo isso contra a minha vontade.";
			link.l1 = "Pense de mim como quiser, Julianna, eu mereço. Mas eu vou trazê-la de volta, custe o que custar\nJulianna, escute, eu sei o que estou te pedindo. Deixar tudo para trás e deixar que outros te arrastem para uma aposta duvidosa. Mas agora, você é minha única esperança! Preciso da sua ajuda nisso, e vou te dever essa até o fim da minha vida!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Muito bem, Capitão. No fim das contas, Angerran precisa ser derrotado de uma vez por todas. Eu vou te ajudar, mas me diga, como você pretende me resgatar do navio dele?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Espere. Você pode levar meu colar de pérolas, os ingleses estão atrás de pérolas negras, não é? Esta aqui vai fazer eles te ouvirem. E agora, o que vem depois?";
			link.l1 = "Em seguida, vou levar o investigador a bordo e partiremos para Guadalupe. Faremos uma busca oficial na fragata de Chievous quando ela retornar com você a bordo. O caso do Mercury foi um incidente grave envolvendo nosso aliado, então De Lyon vai ter que permitir!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Ele vai contar para todo mundo que foram os homens dele que me salvaram do cativeiro. E fique sabendo, Capitão, ainda não decidi o que vou dizer para eles.";
				link.l1 = "Não contar nada estaria ótimo, marquesa. Acredite, eu vou tirar você daqui e fazer Angerran pagar por tudo.";
			}
			else
			{
				dialog.text = "Vou dizer a eles que fui sequestrado por estranhos, tirado da minha própria casa, para ser colocado a bordo do navio do Angerran. Vai parecer que ele pagou mercenários para me raptar.";
				link.l1 = "Mais um prego no caixão de Angerran, marquesa.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Me dê até amanhã de manhã, a menos que queira me carregar num saco. Mande alguns homens para me ajudar também – uma mulher de respeito não pode viajar sem um mínimo de conforto. Charles, você me salvou e eu vou te ajudar, além disso, aceite esta pérola negra inestimável, é meu presente para você. Se tudo der certo, estaremos quites.";
				link.l1 = "Como quiser, Marquesa. Que Deus acompanhe vocês dois! Nos vemos aqui de novo quando tudo acabar.";
			}
			else
			{
				dialog.text = "Estarei pronta para partir ao amanhecer. Não vou ficar me espremendo no porão de carga, então trate de preparar um quarto decente, ou seja lá como você chama isso, pra mim. Charles, aqui, pegue isto. Esta é uma pérola negra preciosa. Sei que ela vale mais do que este lugar, mas tem coisas que não se medem em ouro. Espero que lhe seja útil. Que Deus te ajude!";
				link.l1 = "Boa sorte, vocês dois! Nos vemos aqui de novo quando tudo acabar.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Parabéns, Capitão. Seu plano deu certo. Que escândalo enorme você armou! Os ingleses levaram Angerran e o navio com tudo dentro, menos eu.";
				link.l1 = "Sir William nem sequer veio se despedir. Ele prometeu que pediria desculpas.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, conseguimos! Eles vão te soltar a qualquer momento! Mas precisamos sair da ilha o quanto antes. O governador está furioso com a prisão recente de Angerran.";
				link.l1 = "Fico feliz em te ver, Julianne. Como você está? Como foi a troca? Ela está bem?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Imagino que ele estava ocupado demais para isso. Como o nosso governador agora. É melhor você sair da cidade antes que ele lembre que você existe. Ele gostava muito do filho do Henri, mas a imprensa britânica encurralou ele completamente. Eu não esperaria ele decidir descontar toda a frustração em você.";
			link.l1 = "Justo. Além disso, ela está me esperando na Martinica. Como foi a troca? Ela está bem?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Me perdoe, mas não quero falar sobre isso. Pergunte a ela, por favor. Adeus, Capitão. Vou voltar sozinho. Preciso descansar um pouco do mar – François é um ótimo anfitrião quando não está sendo incomodado por oficiais britânicos entediantes.";
			link.l1 = "Sinto muito por tudo isso, Madame. Agradeço sua colaboração, de qualquer forma. Fico feliz em saber que você fez um novo... amigo.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Obrigado a você também, Charles, por cumprir sua palavra. Encontre Bartholomew na minha casa em St. Pierre. Adeus. Nós nos veremos novamente.";
			link.l1 = "Adeus, Julianne. Que Deus te acompanhe.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Eu não a vi, mas o Bartholomew a levou viva e bem. Aquele inglês prendeu de Chievous e tomou os bens dele bem debaixo do nariz do governador local – e ele nem disse uma palavra! Incrível!";
			link.l1 = "Sabe, até que foi surpreendentemente tranquilo, considerando tudo o que estava por trás dessa prisão. Mas ainda acho que isso vai dar problema depois. Seja como for! Preciso ir para Martinica imediatamente, preciso vê-la o quanto antes!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Sem dúvida vocês dois têm muito o que conversar. Ah, Charles, queria tanto ter um homem com esse fogo nos olhos ao meu lado. Vamos logo, estou morrendo de saudade de um bom banho quente e lençóis limpos. Bartholomew vai estar nos esperando na minha casa em St. Pierre.";
			link.l1 = "Sim, o romantismo das viagens pelo mar é superestimado. Fique com minha cabine, marquesa, é o mínimo que posso fazer. Vamos.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Você já fez por mim tudo o que podia, Charles. Você fez uma mulher cínica voltar a acreditar.";
			link.l1 = "Eu também, Julianne. Eu também.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, que bom que você veio! E aquela sua dama, como está? Ela está bem?";
				link.l1 = "Está tudo bem, graças a você, Julianne. Queria te dizer isso de novo. Você é uma mulher incrível e serei eternamente grato por toda a sua coragem e engenhosidade.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, que bom que você veio! E aquela sua dama, como está? Ela está bem?";
				link.l1 = "Está tudo bem, graças a você, Julianne. Queria te dizer isso de novo. Você é uma mulher incrível e vou ser eternamente grato por toda a sua coragem e engenhosidade.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Talvez seja eu quem esteja em dívida com você. Afinal, você me salvou de dois clientes extremamente incômodos. Acho que ainda te devo uma. Peça o que quiser, Charles.";
			link.l1 = "Nesse caso, tenho um pequeno favor a pedir, minha senhora. Há algo que você poderia fazer para ficarmos quites.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Estou ouvindo, Capitão. O que foi?";
			link.l1 = "As pessoas cometem erros, mas isso não faz do mundo um lugar ruim. Lembre-se disso e seja feliz, Julianne. Você merece ser feliz.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Eu... Eu vou tentar, Charles. Obrigada. Você vai me visitar de vez em quando... como amigo? Você será sempre bem-vindo na minha casa!";
			link.l1 = "Agradeço, marquesa. Adeus, e lembre-se do que me prometeu.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Yet apparently not marvellous enough... but I am glad that it ended well for you. You owe me nothing; after what you did, I can't thank you enough! Come see me whenever you are ashore. You will always be welcome at my place, as a friend!";
			link.l1 = "Obrigado, Marquesa. Desejo tudo de bom para você. Adeus!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, meu amigo, você é tão descuidado – me visita tão pouco! Senti sua falta, sabia? Que tal um vinho? Estou louco para ouvir histórias emocionantes direto da fonte! E também para testar essa sua famosa sorte!";
			link.l1 = "Marquesa, só queria cumprimentá-la e me certificar de que está bem.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "E aí está você, meu amigo! Que bom te ver de novo!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Bem, do jeito que você trata meu amigo, não me resta outra opção, monsieur. Aceito seu desafio. Hora e lugar?";
			link.l1 = "Aqui e agora. Chame os criados, diga para trazerem velas, esse crepúsculo aconchegante não serve. Este lugar precisa estar claro como o dia!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Meu amigo, por favor, não leve isso tão para o lado pessoal. Angerran é um sujeito complicado, é verdade, mas você não deveria provocar ele. Deixe isso comigo.";
			link.l1 = "Tem certeza, excelência? Ele está tão bêbado quanto meu imediato depois de uma semana em terra, mas com certeza sabe manejar a espada. Consigo perceber esse tipo de coisa na hora.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Deus me livre, Charles! Não vou duelar com ele. Vamos apostar, cartas são as armas dos homens civilizados. Vou deixá-lo sem um tostão e mandá-lo até você, implorando por um empréstimo para voltar em segurança a Quebec.";
			link.l1 = "É um plano sólido, sem dúvida. Mas se quer saber, eu preferia ver aquele desgraçado morto, não pobre. Boa sorte, Sua Excelência!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Droga, Angerran, não tem como ser um dez aí! De jeito nenhum!";
			link.l1 = "Isso foi uma acusação? O acordo era seu, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Não foi isso. Eu só estou... um pouco empolgado demais e peço desculpas. Foi um acidente e exijo uma revanche! Este navio, eu... preciso recuperá-lo! Ou então, que se dane o jogo, apenas me diga por quanto você está disposto a vendê-lo? Diga seu preço e eu pago amanhã antes do meio-dia!";
			link.l1 = "Infelizmente, mas acredito de todo coração que não se pode recomprar o que se perdeu no jogo. Só dá pra ganhar de volta. Agora a flauta é minha e não pretendo vendê-la. Sinto muito que sua paixão tenha te colocado nessa situação, às vezes precisamos ser mais realistas sobre nossas capacidades... Talvez você tenha mais documentos de navio?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Você é um verme, Angerran, e me encurralou. Acho que posso te oferecer algo que vai te interessar.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, você é minha única esperança, eu imploro que me ajude! Aquela flauta e a... carga dela já foram vendidas para a Companhia Holandesa. Amanhã preciso entregar todos os documentos para eles. Achei que ficaria aqui a noite toda, então trouxe tudo comigo. Vou estar em uma situação desastrosa se o acordo não der certo!";
			link.l1 = "Mas 'meu doce Jacques', você não acha que a mulher que você protegeu está numa situação ainda mais desastrosa agora? Já apostei muito na vida e entendo o que é apostar um navio, mesmo que não seja seu. Mas apostar por causa de uma mulher?! Você realmente me surpreendeu! E agora tudo o que te importa é o destino do seu acordo?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Não me julgue, Charles. Proteger uma ex-amante de um conde poderoso e até se apaixonar por um tempo não é nada comparado a dever um milhão de pesos ao Peter Stuyvesant. Como vou explicar isso ao agente dele? Imagine o estrago na minha reputação!";
			link.l1 = "Eu já tive uma dívida parecida antes, mas naquela época eu não tinha absolutamente nada e mesmo assim me virei. Você também vai conseguir. Até mais, Jacques. Não prometo nada, e nem vou perguntar que tipo de carga vale um milhão, a ponto de você guardá-la na flauta.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Aí está você, Charles. Eu já ia mandar te chamar. De Chievous está insistindo em um duelo e já recusou qualquer chance de reconciliação. Você se saiu bem nas cartas, mas tem certeza de que quer continuar com isso?";
			link.l1 = "Tenho uma forte suspeita, Sua Excelência, de que era exatamente esse o resultado que queria desde o início. Então, eu aceito. Isso precisa ser resolvido de uma vez por todas. E quanto aos termos do duelo?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Você pensa demais, meu amigo. Ainda existem partes do nosso mundo que não giram ao seu redor. Acredite, estou profundamente decepcionado com o que aconteceu ontem à noite. Muito mesmo. Mas antes, vamos falar sobre o destino dos seus... ganhos.";
			link.l1 = "Certo. Você quer saber como recuperar sua flauta ou como está a Madame Julianne?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Vejo que você trocou sua ironia inadequada por rancor? Charles, estamos do mesmo lado, não se esqueça disso.";
			link.l1 = "Argumento discutível, Vossa Excelência. Para dizer o mínimo. Agora, por onde começamos: pelo navio ou pela dama?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "O acordo com Stuyvesant, claro – o agente dele está me esperando a manhã toda e eu já estou ficando sem desculpas. Eu preciso dos papéis da flauta, Charles.";
			link.l1 = "Certo. Ela é sua. Não acredito que de Chievous tenha jogado limpo, então pode recuperar sua propriedade pela metade do preço. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Ficarei feliz em ajudar. Qual foi o valor do navio que você mencionou? 500.000? Por mim está ótimo.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Agora, serão quatrocentos e sessenta mil pesos, já com os impostos. Fechado. 135.000.";
			link.l1 = "Escuta... Já estou cansado de discutir. Então paga logo, pega seus documentos e acaba com isso.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Você não tem pena dos velhos amigos, né Charles? Agora, com todos os impostos incluídos...";
			link.l1 = "Dívidas de jogo e amizade não têm nada a ver uma com a outra, Excelência. O senhor vai pagar os impostos como comprador, ou eu vendo o navio em Le Francois. E veja bem, ainda não estou me aproveitando da sua posição... ainda.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Certo, que seja. Agora, o duelo. Não quero problemas com o Conde de Levi Vantadur, então tudo precisa ser o mais legal possível. Ouviu bem, Charles? De acordo com a lei! Vou mandar dois oficiais da minha guarnição para acompanhá-lo – ambos são homens nobres e respeitados. Eles serão seus padrinhos no lugar dos seus... companheiros habituais. Quero que tudo fique absolutamente claro até que a questão esteja resolvida!";
			link.l1 = "Que gentileza a sua. E se o nosso bom amigo resolver jogar sujo? Prefiro confiar minhas costas a pessoas que chamo de amigas, e àqueles que sabem o que fazer nessas situações, do que a gente que só nasceu na família certa.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, pare de agir como se esse duelo fosse só entre você e eu. Isso é coisa séria. De Chievous não é alguém que você pode matar e sair impune. Qualquer resultado vai ser seguido de investigações, talvez até um julgamento. Vamos precisar de testemunhas confiáveis. Veja, estou cuidando de você! Mas o mais importante é que você não pode matá-lo. Eu entendo, Angerran é determinado e provavelmente um bom lutador, mas Charles, você não pode matá-lo! Fira-o, humilhe-o se for preciso, mas pare por aí. Se você o matar, haverá consequências, e nenhum de nós vai conseguir escapar ou sobreviver a elas. Mesmo que o Conde de Levi Vantadur nunca tenha reconhecido oficialmente seu bastardo, ele não tem outros filhos. A fúria dele não terá limites.";
			link.l1 = "Maravilhoso, então eu deveria deixar que me matem só para não permitir que o conde furioso te expulse do cargo de governador?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Receio que, se você não ouvir, não vamos sobreviver muito mais tempo que Angerran de Chievous. Lembre-se disso e tome cuidado. O duelo está marcado para as dez horas desta noite, depois dos portões da cidade. Meus oficiais vão te encontrar lá. Agora, o último assunto: Madame Julianne Botot – como ela está?";
			link.l1 = "Quer saber se eu já aproveitei meu prêmio? Não, Excelência, ainda não ou talvez nunca – isso não importa. O que importa é que você está fora da casa da marquesa para sempre. Ela foi bem clara sobre isso. Não posso julgá-la por isso. Julianne vai escolher o próximo protetor dela sozinha.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Você realmente sabe como surpreender, Charles. Enfim, tenho uma reunião entediante com o agente da Companhia para comparecer. Você também deveria ir, se preparar, e lembrar do que eu te avisei.";
			link.l1 = "Eu certamente vou tentar, Excelência. Mas é uma luta, então não posso prometer nada. Obrigado por me ajudar.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Você está vivo, Charles! Que alívio, como você se saiu? Isso é sangue?! O de Chievous conseguiu escapar?";
			link.l1 = "Infelizmente, sim. Ele está ferido, mas não gravemente. Teve que fugir, mas também mandou seus capangas atrás de nós. Resumindo, parte desse sangue não é meu.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Desgraçado! E os meus homens? Eles estão vivos para testemunhar o que aconteceu?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Eles estão bem, Excelência. Um pouco machucados, mas vão sobreviver.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Nem todos, Excelência. Um cavalheiro não conseguiu - de Chievous fez questão de trazer mosqueteiros. Eu não pude fazer nada.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "Foi um verdadeiro inferno lá, Excelência. Ambos os valentes cavalheiros caíram em combate. Se não fosse por eles, as coisas teriam ficado feias para mim. De Chievous armou uma emboscada sangrenta de verdade.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Excelente! Vou obter os depoimentos deles por escrito, na presença de testemunhas confiáveis. De Chievous vai pagar por isso!";
			link.l1 = "Eu duvido que a gente consiga sequer arranhar o nome dele. Prefiro encontrá-lo e acabar com isso eu mesmo, apesar de todos os seus avisos. Um covarde desses não merece viver.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Horrível. Mas vamos conseguir o depoimento escrito de pelo menos uma testemunha. De Chievous vai pagar por isso!";
			link.l1 = "Não acho que a gente consiga nem arranhar o nome dele. Prefiro encontrá-lo e terminar o serviço eu mesmo, apesar de todos os seus avisos. Um covarde desses não merece viver.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Maldito seja! Eles eram bons homens, Charles! Eu juro, aquele desgraçado vai pagar!";
			link.l1 = "Eu duvido que a gente consiga sequer arranhar o nome dele. Prefiro encontrá-lo e terminar o serviço eu mesmo, apesar de todos os seus avisos. Um covarde desses não merece viver.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Esqueça isso, Charles. O desgraçado já fez todo o estrago necessário sozinho. Aposto que agora está fugindo, escondido na lama de alguma colônia miserável. É improvável que ainda represente perigo para você. Essa vilania foi só a mordida de uma cobra em fuga. Você também parece ferido, precisa de um médico?";
			link.l1 = "Obrigado pela sua preocupação, Excelência, mas estou bem.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Bom saber. Agora pode respirar aliviado, essa história acabou. Relaxe e volte aos seus afazeres. Aliás, sobre isso... Não terminamos nossa conversa anterior sobre seus ganhos recentes. Já decidiu o que vai fazer com... isso?";
			link.l1 = "Não estou entendendo direito, Jacques. O que foi? Você está falando da marquesa? Droga! Madame Botot! De Chievous está foragido, não é mais uma ameaça para mim, mas está desesperado e pode fazer qualquer coisa! Preciso ir! Mande os guardas para a casa da marquesa! Agora!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Um capitão famoso, é isso? Aquele que enfrentou o ataque espanhol que quase queimou esta cidadezinha? Entendi. O que vai beber?";
			}
			else
			{
				dialog.text = "Capitão famoso, é? Nunca ouvi falar de você... O que vai beber?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, igual ao da nossa bela anfitriã? Tem certeza de que ainda consegue sentir algum sabor depois de tanto sal do mar? Normalmente, gente do seu calibre prefere beber coisas que poderiam dissolver uma bota velha.";
			link.l1 = "If this is a suggestion to walk past the gates together, then I am in. I don't like you either, and I am glad the feeling is mutual. Let's cut the talking; you're not good at it anyway. I leave the choice of terms and arms to you.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Um buquê de terra e mijo de gato? Encantador! Nem envelhecem essa porcaria azeda em barris, porque nunca vai virar vinho mesmo. Me diz, o sal do mar detona o gosto desse jeito?";
			link.l1 = "If this is a suggestion to walk past the gates together, then I am in. I don't like you either, and I am glad the feeling is mutual. Let's cut the talking; you are not good at it anyway. I leave the choice of terms and arms to you.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, such a brave boy! Now calm your temper and keep your distance. We are not in a tavern and I am not a drinking companion of yours. You are far beneath my station; we shouldn't even be speaking, but the lady requested it. Now, Jacques and I have unfinished business...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, você está bem? Água, seus idiotas! Tragam água!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Você tem toda razão, está abafado aqui. O jogo tem sido bem divertido até agora, mas vamos fazer uma pequena pausa antes do final. Tchau, tchau Jacques – lembra dos termos do nosso torneio? E aqui temos Charles de Maure, certo? Um capitão com gosto duvidoso para vinho, lembro de você. Não se preocupe, depois que eu terminar aqui, você só vai beber água. Então, aproveite, curta o momento, tome um gole. Quando estiver pronto, venha me encontrar nesta salinha. Vamos terminar a noite em um ambiente mais confortável...";
			link.l1 = "Estou ansioso por isso, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Aí está você, finalmente. Pronto para se despedir do seu dinheiro?";
			link.l1 = "Prefiro juntar o seu a eles. Por favor!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Bem dito, mas infelizmente nosso querido governador insistiu em mudar as regras logo antes de sua derrota vergonhosa. Agora somos obrigados a apostar algo além de dinheiro. As apostas precisam ser reconhecidas como iguais por ambas as partes. Minha aposta é a flauta de prata.";
			link.l1 = "Ah, qual é, isso é chato – consigo cinco desses com ouro em poucas semanas de pilhagem. Me dá algo maior.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Sim, eu vi seu navio, devo admitir que é realmente algo impressionante. Então vamos aumentar a aposta – dois navios contra um. Minha fragata e um fluyt carregados de prata contra o seu navio?";
				link.l1 = "Um jogo digno! Madame Botot estava enganada – ESTE duelo vai entrar para a lenda. Fechado!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Olha só, nosso capitão é um danadinho! Mas, corsar é coisa sagrada. Que tal então um navio de guerra? Uma fragata, 48 canhões. Mais rápida que muitas corvetas – obra dos estaleiros reais, ainda aprimorada pelos melhores construtores do mundo. Os culverins que ela carrega têm alcance e precisão excelentes. O que me diz?";
					link.l1 = "Bem melhor, tô dentro! Vamos nessa!";
				}
				else
				{
					dialog.text = "Ouvi dizer que você ancorou por aqui, Capitão. Agradeça por eu ter concordado em aceitar seu velho barco como aposta. Então venha, a menos que desista?";
					link.l1 = "Tá bom, você tem razão. Vamos lá.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Fim de jogo, Capitão, você conseguiu o que queria. Pode se gabar, se quiser. Sugiro que discutamos os termos da compra da minha fragata amanhã ao meio-dia.";
					link.l1 = "É só isso? Sinceramente acredito, como você, que o que se perde em uma aposta não se pode comprar de volta, só ganhar de novo. Ou então posso vendê-la como madeira para os pescadores daqui e contar a todos sobre sua generosa doação.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Então a sorte decidiu. Isso acabou sendo bem curioso. Parabéns, Capitão de Maure. Sugiro que discutamos os termos da compra da minha fragata amanhã ao meio-dia.";
						link.l1 = "Tão cedo? Estamos desapontando outros convidados, monsieur. Se não me engano, você ainda tem mais um navio. Sinceramente acredito, assim como você, que o que se perde em uma aposta não pode ser comprado de volta, só recuperado com outra vitória.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "So Fortune has spoken. This turned out most curiously. Congratulations, Captain de Maure. You've earned yourself a decent drink, try Sangiovese. I assume Jacques will pay you well for this tub; it seems he has feelings for it, feelings much stronger than for certain other things. That should be enough to buy a good wine.";
						link.l1 = "Já vai se render? Estamos decepcionando os outros convidados, monsieur. Se não me engano, você ainda tem mais um navio. Aposto sua fragata contra minha flauta de prata, já que achou meu próprio navio modesto demais.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Que azar, Capitão. Ainda assim, admiro sua coragem, e hoje estou de bom humor. Vou ficar com seu ouro, mas pode ficar com seu navio. Agora suma da minha frente, e tente não apostar de novo. Um dia, isso ainda vai acabar com você.";
				link.l1 = "Muito nobre da sua parte, não esperava por isso. Adeus, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Existe uma diferença notável entre se vangloriar e zombar do seu oponente derrotado, Monsieur de Maure.";
			link.l1 = "Já está se dando por vencido? Mas tudo começou tão bem... ah! Madame Botot, acredito que seu salão acaba de ganhar mais uma bela história sobre a diferença entre palavras e ações!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "O que mais você quer? Não tenho mais navios escondidos na manga, nem dinheiro suficiente pra bancar sequer um navio. Apostar doblões não é coisa séria, ainda mais depois de tudo que vimos esta noite.";
			link.l1 = "Você é menos engenhoso que o nosso doce Jacques Dille du Parkuet? Estou lhe dando uma oportunidade maravilhosa de provar que nem todo amor está à venda. A fortuna também não vende seu favor. O navio de prata e sua fragata contra aquilo que você valoriza mais do que ouro.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Capitão, isso nem tem graça. Vamos acabar logo com isso – o amanhecer está chegando. Amanhã discutiremos a compra do meu navio.";
			link.l1 = "Certo, está feito – três navios! Incluindo um verdadeiro navio de guerra contra a dama mais... bem, cara do Novo Mundo. Será que você consegue recusar uma aposta dessas?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Seria uma loucura. Mas, de fato, é uma loucura, monsieur de Maure. Por favor. Mas lembre-se, foi ideia sua.";
			link.l1 = "Essa vai ser a história que eles vão saborear por um ano inteiro, a portas fechadas! Ei você, mais vinho e velas! O jogo tem que continuar!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Até pouco tempo atrás, você achava esta flauta uma aposta indigna contra nossos navios. O que mudou?";
			link.l1 = "Fiquei entediado. Vamos apimentar nosso duelo – sua fragata e meu navio contra...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "Aquela flauta que você desprezava? Está com febre, por acaso? Você não parece muito bem.";
			link.l1 = "Estou perfeitamente bem, obrigado. Você não ouviu. Chances de dois contra um não são tão espetaculares assim, é verdade, então vamos equilibrar o jogo! Nem todos os valores podem ser medidos em ouro, concorda? Ou talvez você só prefira não lutar contra o vento, se algo não sair como planejou, então muda de rumo? Que pena, então, parece que me enganei sobre você. Madame Botot, acredito que seu salão acaba de ganhar mais uma história interessante sobre a diferença entre falar e agir...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Não tente me provocar, Monsieur de Maure, você é ingênuo demais para isso.";
			link.l1 = "De fato. Falta de vontade não é pecado... a menos que você seja um militar, claro. Ou um nobre — a honra da família, como deve saber, às vezes pesa demais. Mas não creio que você conheça esse tipo de dilema, não é mesmo.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Você está tentando começar um duelo ou continuar o jogo?";
			link.l1 = "Ambos servem. Vou aproveitar para apreciar a coleção de vinhos da marquesa enquanto você se recompõe.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Que assim seja. Esta noite deve terminar à altura. Dois grandes navios contra o velho casco cheio de prata e a mulher mais bela da Nova França! Respire fundo, monsieur de Maure, esta aposta vai virar lenda entre as fofocas da alta sociedade.";
			link.l1 = "Sua derrota será lendária, de fato, monsieur de Chievous. Traga mais vinho e velas! Vamos nessa!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "You've lost your head over luck, monsieur de Maure. You're taking a risk here; fortune's favour is fleeting.";
			link.l1 = "A brief favour is a path to true love. The same could be said of bought loyalty; it leads only to contempt or boredom.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Suas tentativas de me provocar me divertem. É melhor você perguntar à Madame Juliana sobre coisas como favor, amor e tudo o mais que se pode ou não comprar. Mas se apresse – ela vai embora da cidade amanhã.";
			link.l1 = "Pelo menos seu conhecimento sobre o assunto é unilateral. Você não pode conquistar o favor da Senhora Fortuna nem ganhando, nem pagando aqui, então não pode conhecer o amor dela. É preciso coragem, monsieur, e uma vontade inabalável para correr riscos. Sem falar que outras... damas terrenas também valorizam essas qualidades. Aposto duas das minhas embarcações contra uma sua, aceita?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Quer continuar com tanta vontade assim? Tudo bem, tanto faz. Mas pelo menos vamos colocar um pouco de drama nisso, monsieur de Maure. Você estava falando sobre amor e preços? Proponho então que igualemos nossas apostas – seu barco e a flauta de prata contra minha fragata e a mulher mais bela da Nova França. E agora, o que me diz?";
			link.l1 = "Tenho que admitir, você realmente sabe apostar com estilo, monsieur! Mais vinho e velas! Vamos nessa!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Inacreditável, Monsieur de Maure, isso é simplesmente inacreditável!";
				link.l1 = "Sim, de fato, a Europa não conhecia uma derrota assim desde a Batalha de Rocroi, monsieur de Chievous. O artista em mim estremece de vontade de registrar um momento tão histórico. É uma pena que eu já não desenhe como fazia na juventude. Mas talvez madame Julianne tenha um artista talentoso por perto, não é mesmo?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Azar o seu, Capitão. Ainda assim, admiro sua coragem, e hoje estou de bom humor. Vou ficar com seu ouro, mas pode ficar com seu navio. Agora suma da minha frente, e tente evitar jogos de azar no futuro. Um dia, isso ainda vai acabar com você.";
				link.l1 = "Muito nobre da sua parte, não esperava por isso. Adeus, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Não, você não entende. Isso é tão inacreditável que simplesmente não pode ser!";
			link.l1 = "Todos nós vimos as cartas, Monsieur de Chievous - a Fortuna nunca mente.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "A sorte não, mas você, monsieur de Maure, sim! Me parece que por trás da sua ousadia havia um plano, não só paixão. Você é um mentiroso e um trapaceiro – estou pronto para confirmar isso diante de todos os convidados.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, ouvi direito? Está disposto a sustentar suas suspeitas com mais do que palavras? Parece que suas ofensas passaram dos limites, e eu, ao contrário de você, valorizo a honra da minha família.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Segundo filho, um trapaceiro e vigarista não vai me dar lição sobre honra da família! Fique quieta, Julianne, falarei com você depois! Charles de Maure, exijo que me dê satisfação agora mesmo! Espada ou pistola?";
			link.l1 = "Ambos. Para ser sincero, fico feliz que você tenha mudado de ideia. Lembra que eu sugeri darmos uma volta além dos portões? O que foi mesmo que você disse sobre minha classe indigna? Talvez o jogo de cartas tenha lhe dado um pouco de coragem, afinal?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Uma honra grande demais, mas concordo com a marquesa. Vou acabar com você como um cavalheiro, de Maure, mesmo que não mereça. Desafio você para um duelo amanhã ao meio-dia, perante Sua Excelência, o Governador. Venha vê-lo pessoalmente ou envie seus segundos para discutir os termos. Até lá. Senhora, meus respeitos.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "E aí está você, o favorito da sorte. Cuidou dos seus assuntos, espero? Não esqueceu de se confessar? Dizem que o inferno pode ser bem desconfortável sem isso.";
			link.l1 = "Falar é fácil, monsieur. Você não sabe jogar cartas direito, então vamos ver como se sai na espada... Vamos dançar!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Boa... essa, maldito seja. Mas ainda estou vivo!";
			link.l1 = "Your wound doesn't look good, but you should see a doctor nevertheless. Clearly, you can't go on like this; you will die if you do. It looks like we are done here. I won, and I didn't cheat. I will return your ship to you, and you will leave St. Pierre. We will never see each other again.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Que cavalheirismo impressionante! Olha, monsieur de Maure, você pode até ser um espadachim nato, mas com certeza trapaceou nas cartas. Eu embaralhei o baralho três vezes. Três vezes, droga! Nenhum milagre no mundo poderia te salvar, mas mesmo assim você ganhou! Queria saber como fez isso... Tanto faz, logo você vai contar tudo isso pro Diabo. Acabem com eles, rapazes!";
			link.l1 = "Seu desgraçado! Eu te poupei e é assim que você me retribui?! Senhores, às armas!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Eu admito, Monsieur de Maure, estou um pouco surpreso em vê-lo aqui. Isso significa que eu não estava enganado sobre você, e aquela garota selvagem realmente significa algo para você?";
			link.l1 = "Será que o seu bom amigo de Lyons aprovaria sequestrar oficiais de capitães respeitados da nossa Marinha? Talvez devêssemos chamá-lo para se juntar a nós e contar toda a história?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Isso não vai te ajudar em nada, pode acreditar. E outra, tratei sua mulher melhor do que um general capturado. Por enquanto. Mas tudo pode mudar, e depende de você, Charles.";
			link.l1 = "Não me lembro de termos dividido um gole de amantes com você. Não venha com esse 'Charles' pra cima de mim, Monsieur de Chievous. Seja direto e diga logo o que você quer de mim?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "De você? Nada, Deus me livre! Nós só resolvemos uma briga infeliz depois de um jogo de cartas escandaloso, tomamos uns drinks e saímos deste quarto como velhos amigos.";
			link.l1 = "Angerran, você até que parece bem apesar do ferimento recente, e cada minuto dessa conversa inútil me dá vontade de mudar isso. Até a ideia de sujar esses tapetes finos do Francois de Lyons está começando a me parecer cada vez mais atraente.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Mas o bom e velho François adora esses tapetes, Charles. Todo mundo ama alguma coisa. Já que você está aqui, deve amar sua namoradinha de armas. Estou pronto para devolvê-la para você em troca do que é meu. Você bagunçou o jogo, e mesmo que eu normalmente não perdoe esse tipo de transgressão, posso abrir uma exceção para você. Você me dará o prêmio que tanto desejo, e eu lhe darei o mesmo. Então, nos despediremos em grande estilo. Eis o que é o amor.";
			link.l1 = "Você acha que eu ando por aí com a marquesa como se fosse uma joia preciosa no bolso? Que absurdo! Como eu poderia simplesmente entregá-la para você?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Eu não me importo nem um pouco, Charles. Você tem duas semanas para resolver isso. E sim, quero que esse prêmio seja recebido discretamente. Digamos, algum capitão que ganhou uma cortesã absurdamente cara, mas mesmo assim não conseguiu conquistar o favor dela, poderia acabar fazendo alguma besteira, não é? Já está tão desesperado assim, Charles?";
			link.l1 = "Quero ver minha oficial primeiro para ter certeza de que ela ainda está viva.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Sem chance. Você vai ter que confiar na minha palavra. Ela está em um lugar seguro e vai continuar lá até eu receber o que quero. Mas se continuar insistindo em vê-la antes da hora, vou ter o maior prazer em te mandar uma parte dela. O que prefere? Uma orelha, um nariz, uns dedos?";
			link.l1 = "Encoste nela, seu verme, e eu te estrangulo com as minhas próprias mãos, juro por Deus! Não ouse me testar!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Calm down. Everything that is about to happen is entirely your doing. I don't like violence; I use it only when I must. Don't make me. Just hand over my prize at Cape Scott Head on Dominica in less than two weeks and you will get what is yours. I don't care how you do it. If you want to steal - steal, you are a pirate after all, just better dressed.";
			link.l1 = "Você está completamente delirando, existe uma grande diferença entre um pirata e um maldito traficante de escravos...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Respire fundo, estamos prestes a fazer uma entrada elegante diante do velho François. Agora somos amigos, lembra? Sorria, Charles, vai lá! Vamos nos separar. Cabo Scott Head, Dominica, em duas semanas. Não se atrase.";
			link.l1 = "Te vejo lá.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Boa noite, Madame Botot, Capitão de Maure. Peço que mantenham a calma.";
			link.l1 = "Marquise, atrás de mim, agora! Monsieur, o que significa isso?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Tenho uma dúzia de homens atrás da porta e poderes de emergência autorizados pelo seu Estado. Os guardas não vão te ajudar. Portanto, por favor, guarde sua espada, senhor. Só quero conversar. Por enquanto.";
			link.l1 = "Monsieur, quem é você e como chegou aqui?! É melhor se explicar!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Permitam-me apresentar-me – Sir William Cortney, Barão Cortney. Agora vamos todos nos acalmar e conversar.";
			link.l1 = "Certo, Monsieur Cortney, estamos ouvindo.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Por favor, me desculpe por ouvir sua conversa, mas as circunstâncias não me deixam outra opção. Mesmo permanecendo anônimo aqui em St. Pierre, estou conduzindo uma investigação extremamente importante em nome da Coroa da Inglaterra. Trata-se de um navio-correio perdido no mar. Já ouviu falar de uma escuna chamada Regina? ";
			link.l1 = "Eu não, e não entendo essas suas insinuações, Monsieur. Sou um capitão honesto...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Eu não dou a mínima para os seus negócios suspeitos, senhor. Investiguei um pouco sobre você e, para ser sincero, fiz de você meu primeiro suspeito quando soube que esteve em Martinica logo depois que o Regina desapareceu. No entanto, você não é idiota e seus homens não brincaram com pérolas por aqui. Sendo assim, você está fora das minhas suspeitas, por enquanto.";
			link.l1 = "Pérolas? Que pérolas são essas de que você está falando?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Pérolas selecionadas a dedo, de tamanho grande, vindas das operações do Oeste Espanhol. E são negras também, o que as torna extremamente raras. Já ouviu falar de algo assim?";
			link.l1 = "Acho que sim, embora eu sempre tenha achado que era só mais uma história de marinheiro. Igual às lendas sobre o Holandês Voador. Julianne, o que foi?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Peço que a senhora o apresente aqui. Trata-se de uma questão de extrema importância. Enquanto isso, o senhor deve me contar tudo sobre o Capitão Moreno. Suspeito que foi ele quem lhe deu essa pista. Estou muito curioso para saber qual é o papel dele nessa história.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno não é o nome verdadeiro dele, Monsieur Cortney. O nome dele é Hernando Vasquez, também conhecido como Don Sangrento, um pirata espanhol que já foi imediato do Albatross – o navio do infame Bartholomew, o Português.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Troquei só algumas palavras com ele. Não tenho muito o que contar. Parecia um verdadeiro lobo do mar.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Ora, ora. E posso saber como você sabe disso?";
			link.l1 = "Eu conhecia o capitão dele. Na verdade, fui eu quem o capturou e entregou aos holandeses. É uma longa história. Pena que não consegui pegar o próprio Vasquez naquela época...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Você também é um lobo do mar, senhor. Não acredito que tenha deixado de perceber mais coisas.";
			link.l1 = "Só um leve sotaque, o jeito como ele olhava e se comportava. Aposto que ele é espanhol, Monsieur Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Isso muda tudo, senhor. E não é bom. Senhora, encontrou o colar? Deixe-me ver\nSim, de fato, esta é uma das pérolas negras espanholas. Veja só, essa história de marinheiro é bem real. Só falta descobrir como aquele de Chievous conseguiu uma dessas. Aliás, ele não é um bastardo do Duque de Levy Vantadur?";
			link.l1 = "É ele mesmo, sem dúvida. Pelo que sabemos, ele tinha negócios com o barão pirata local em Le Francois. Talvez tenha comprado essa pérola dele?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Talvez sim. Mas não gosto nem um pouco do rastro espanhol nisso tudo. De qualquer forma, obrigado pela sua colaboração. Receio que terei que visitá-lo novamente amanhã, neste mesmo horário. Gostaria também da presença do capitão de Maure. Talvez eu tenha mais perguntas para você. Agora devo ir para Le François.";
			link.l1 = "Monsieur Cortney, espere. Talvez eu possa me juntar a você? Jacques Barbazon não ganhou esse apelido por ser uma pessoa amável e gentil, e esse assunto também me interessa.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Capitão, fico comovida com sua preocupação, mas a resposta é não. Isto é um assunto de Estado. O canalha sabe o seu lugar e jamais ousaria tocar na enviada da Coroa, ou então sua vila miserável deixará de existir! Peço desculpas mais uma vez pela intromissão, senhora. Tenha uma boa noite.";
			link.l1 = "Até amanhã à noite, Barão.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Não fique bravo com ela, Capitão. Eu sei ser bem persuasivo. Sua história é impressionante, de verdade. Acho que posso encontrar uma utilidade para você.";
			link.l1 = "Você parece satisfeito. Como foi lá em Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Como eu esperava, esse seu barão foi manso como um cordeiro. Ele me contou tudo o que eu queria saber. Como eu disse, posso ser extremamente persuasivo.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Hoje eu vim aqui sozinho, não tem nenhum dos meus homens atrás daquela porta. Que diabos?!";
			link.l1 = "Estou com um mau pressentimento sobre isso. Julianne, fique atrás de mim, agora! Barão, os emissários da Coroa lutam tão bem quanto falam?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Você realmente sabe manejar uma espada, Capitão! Olha, pra ser sincero, não foi nada fácil. Quem diabos eram aquelas pessoas?!";
			link.l1 = "Devemos perguntar aos amigos deles – estou ouvindo mais passos. Queria que fossem os guardas...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Inacreditável! Você acha que aquele desgraçado teve coragem de fazer tudo isso?! Ele vai pagar, eu juro!";
			link.l1 = "Respire. Barbazon vai dar um jeito de escapar de qualquer acusação. Ele vai dizer que foi só um assalto comum de ladrõezinhos numa casa rica. Além disso, ele é um maldito pirata, por que se importaria com as autoridades! Ainda assim, agora tenho certeza de que você conseguiu descobrir algo realmente valioso. Peço que compartilhe esse conhecimento comigo.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Eu realmente não posso dizer não, posso? Caso contrário, da próxima vez pode dar certo, não é? Tá bom, vou fingir que não percebi uma certa ameaça no seu tom. Digamos que estou retribuindo um favor. Jacques, o Bondoso, não vendeu pérolas para o seu bastardo nobre. Ele estava comprando. Só isso.";
			link.l1 = "Então foi o de Chievous que interceptou a Regina? Ele é um canalha, mas é difícil acreditar que se rebaixaria à pirataria comum.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Seria difícil chamar a Regina de um prêmio típico de pirata, Capitão. Supomos que ela tinha pelo menos meia dúzia de pérolas negras. Mesmo uma única pérola negra já não tem preço. Eu preciso encontrar esse tal Sir de Chievous custe o que custar.";
			link.l1 = "Posso ajudar aqui, Monsieur. Mas deixe-me esclarecer uma coisa primeiro. Não parecia que eu me importava com o colar da Madame Botot, então as pérolas não são o motivo de você estar aqui. O que mais havia a bordo da Regina?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Very well, I suppose I'll have to tell you more, given the circumstances. You see, the cargo is not as important as the ship herself. The courier brigantine Regina had been assigned to the port of San Jose, Trinidad. Her captain used to gather intel and run some... errands for us.\nHis last errand was to transport spoils our capers managed to extract from the Spanish pearl operations. It took three years of our efforts to get that lead. Black pearls are certainly significant, but losing the Regina is disastrous. It wasn't an accident; someone who knew about her pearls must also have known about the rest.";
			link.l1 = "Excelente, então é mesmo coisa dos serviços de inteligência! Está com medo de que toda a rede de espiões que você construiu esteja em perigo? Agora consigo entender o tamanho do seu problema.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Já ouviu falar de John Thurloe? Ele é o chefe da inteligência da Coroa. Um dia estarei em Londres, relatando pessoalmente a ele sobre o destino da Regina. Preciso descobrir de onde veio a informação vazada e... lidar com a fonte. Além disso, tem também esse tal capitão Moreno, que é do seu círculo. Se os espanhóis descobrirem nossa rede de espiões coloniais, anos de trabalho duro e cuidadoso vão por água abaixo!";
			link.l1 = "Sabe, tudo isso começa a fazer sentido quando você olha para o quadro maior. Estou começando a achar que alguém com sotaque espanhol contou ao de Chievous sobre a Regina e as pérolas negras.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "We think alike. There is no better way to exploit an exposed spy network. A diplomatic incident with a man of such high standing involved... Such an incident could seriously damage relations between Britain and France; all you need is to feed the right leads and just wait for an international scandal. Perhaps even that lead about black pearls was deliberately fed to us as well.";
			link.l1 = "Aqueles malditos castelhanos, né? E o que a gente faz sobre o de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Para ser sincero, não faço ideia. Se for uma provocação espanhola, o melhor é simplesmente ignorar. Mas preciso descobrir como ele ficou sabendo da Regina e o quanto isso pode comprometer nossa rede nas colônias espanholas. Além disso, devo minha vida a você, e pretendo retribuir.";
			link.l1 = "Honestidade por honestidade, baronete. Aceito qualquer ajuda que puder conseguir. Já estou tão desesperado que penso até em sequestrar a marquesa.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Você percebe que é assim que o de Chievous apaga os rastros dele? Vai ser fácil demais jogar toda essa confusão em cima de você, inclusive o sumiço da Regina. Por isso, proponho o seguinte. O Marquês Botot me disse que o de Chievous não vai aparecer na troca e vai ficar seguro em Basse-Terre. Ou ele percebeu a encrenca em que se meteu, ou está começando a desconfiar de alguma coisa. Ele vai ficar mais cauteloso que um rato de cozinha. Por isso, vou para Dominica com você.";
			link.l1 = "Mas a prisioneira dele é minha prioridade, não posso arriscar a vida dela! Ela é uma refém aguardando uma troca!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Não se preocupe – vou pressionar Jacques Dille de Parkuet e conseguir um mandado de prisão para o navio de de Chievous. Duvido que os homens dele tenham plena noção da situação em que se meteram, caso contrário teriam sido mais cautelosos com essas pérolas. Iremos até eles em um bote e entregaremos o mandado diretamente.";
			link.l1 = "Sim, eu me lembro do seu dom de persuasão, Monsieur, mas é um risco. E dos grandes.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Você está certo, mas vai ter que aceitar isso se quiser a minha ajuda. Quando terminarmos em Dominica, irei a Basse-Terre exigir que o governador de Lyon entregue seu adversário. Tenho autoridade para isso. Não podemos deixar de Chievous escapar.";
			link.l1 = "Tem certeza de que está pronto para isso, Monsieur? Isso pode acabar causando uma guerra, não é?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Aposto que eles nunca vão permitir que isso aconteça. Não vai rolar, já que a verdade já veio à tona. Política é uma prostituta, Capitão. Prometo que vou apresentar o de Chievous às masmorras britânicas, só por você. Parece uma solução discreta, até o pai dele acharia um preço razoável.";
			link.l1 = "Não posso dizer que gosto do seu plano, mas não vejo outra saída.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Eu lhe asseguro que vamos conseguir. Preciso ir agora ver o governador e dar ordens aos meus homens. Se encontrar a marquesa, diga a ela que pode ficar com a pérola como um sinal de gratidão pela ajuda na investigação.";
			link.l1 = "Obrigado, Barão. Nos vemos a bordo do meu navio, vamos zarpar em breve.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Baronet Cortney, at your service. By the power vested in me by the British Empire, with the full support of her trusted ally France, your vessel is hereby under arrest. Here are the papers; please make sure to read them and tell your men to keep their hands away from their weapons. You are detained, but not yet arrested. If you don't do anything foolish, you will be released at the first port.";
			link.l1 = "Baronete, eu preciso resgatar meu... meu oficial!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Não se preocupe, Capitão, eu vou levar ela até o seu navio. Peço que volte ao bote agora. Vou assumir o comando deste navio e navegar até Basse-Terre. Fique à vontade para nos deixar se não pretende zombar pessoalmente do seu arqui-inimigo. Só peço que transfira alguns dos seus homens para me ajudar a chegar até Guadalupe.";
			link.l1 = "Muito bem, Monsieur. Prefiro não. Mande a ele meus piores cumprimentos. Adeus e mais uma vez, obrigado!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, fico feliz em te ver. Eu tinha esperança de que você voltasse, mas nunca acreditei de verdade que isso aconteceria.";
			link.l1 = "Da mesma forma, baronete. Veio fazer uma visita à marquesa? Aliás, onde ela está?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Você ainda não entendeu, não é? Ela fugiu. Além disso, Angerran de Chievous lhe manda sinceras desculpas. Consegui convencê-lo de que você nunca fez parte do jogo, só foi mais uma vítima dele. Assim como ele. O bom homem não se deu ao trabalho de escrever, mas está realmente arrependido de como as coisas terminaram.";
			link.l1 = "Está profundamente arrependido, é?! Do que você está falando, Monsieur?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Eu e você, nós deixamos passar o principal. Como ele ficou sabendo das pérolas? Quem convidou aquele capitão espanhol para esta casa? Quem poderia ter levado o desgraçado a correr atrás de um prêmio desses?";
			link.l1 = "Tá falando sério? Não pode ser...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Com certeza pode. A Marquesa desempenhou seu papel perfeitamente, quase conseguiu enganar todo mundo. Mas, graças à nossa investigação, eu me aproximei do de Chievous não como ladrão e pirata, mas como a vítima de uma armadilha que ele realmente era. Ele logo percebeu no que ela o tinha envolvido, mas não tinha provas e decidiu agir por conta própria. Você sabe o que aconteceu depois.";
			link.l1 = "Quer dizer que tudo aquilo foi armado pela Marquesa? De Chievous caiu feito uma criança descuidada!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Exatamente. A paixão é algo muito perigoso, Charles! Lembra daquela noite em que você jogou nesta mesma casa? Angerran queria conseguir as provas de que precisava da marquesa conquistando o patrocínio dela. Sim, ele trapaceou, mas estava desesperado depois de anos de uma paixão sem esperança que terminou na traição mais devastadora! Mas você interveio, se declarou o defensor dela e cumpriu esse papel. De Chievous achou que você e ela pensavam da mesma forma. Ele roubou um navio que tinha perdido para você para impedir que você pegasse os registros dele. Usou seu oficial para tentar colocar você e ela – seus inimigos mortais, como ele acreditava – um contra o outro.";
			link.l1 = "Estou sem palavras!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Agora você sabe como é, Charles! A marquesa é inteligente, deslumbrante e não menos perigosa. Não faço ideia de quanto tempo ela manipulou as pessoas mais influentes da Nova França. Muitos anos, eu diria. De qualquer forma, isso não te diz mais respeito. Foi um prazer te reencontrar, mas tenho mais quartos para revirar, a casa é grande. Provavelmente não vamos encontrar nada, mas temos que tentar pelo menos.  Mais uma coisa antes de nos despedirmos. Aqui, pegue isto. Uma lembrança para guardar. Talvez você entregue para sua amiga quando estiver pronto. Você tem muita sorte, sabia? Principalmente se comparar com o de Chievous, coitado!";
			link.l1 = "Você está certo, sou mesmo. Adeus, e que Deus te acompanhe na sua busca, baronete!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Que dia maravilhoso estamos tendo hoje, hein Capitão? Ouvi falar dos seus feitos, mas nunca imaginei que você fosse um pirata qualquer. Que ousadia – aparecer em St. Jones depois do que fez!";
			link.l1 = "Posso até ser um pirata, isso é verdade, senhor, mas pareço um idiota? Por que diabos eu viria aqui depois de saquear o Mercury e levar as pérolas espanholas dela?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Eu admito, é só por isso que você está tendo essa conversa agora em vez de balançar na forca. Veja, tem um pequeno detalhe que escondemos nesse caso. E não estou falando da pérola que encontramos com você. É o nome da brigantina.";
			link.l1 = "Como assim?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Uma escuna-correio, a Regina estava designada ao porto de San Jose pelos últimos dois anos. Seu capitão reunia informações para nós e também fazia... serviços de todo tipo. Oficialmente, estamos procurando por ela sob o pretexto da mala diplomática perdida que ela transportava. Não é uma desculpa muito convincente, admito. Ainda assim, você não conseguiria descobrir o verdadeiro nome do navio sem vasculhar direito a cabine do capitão.";
			link.l1 = "Eu estava cego, mas agora enxergo. Por favor, me escute, senhor, eu vou explicar!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Então, se esforce mais, capitão. Sua vida está por um fio.";
			link.l1 = "Eu não tenho nada a ver com essa história de espionagem! Nem os espanhóis. Sua rede está segura, pode ficar tranquilo. Mas houve uma brecha e alguém se aproveitou disso. Depois, acabei discutindo com essa pessoa. Descobri provas do envolvimento dele no negócio do Mercúrio e quis usá-las para derrotá-lo.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Deus é minha testemunha, achei que esse caso fosse só mais um ato comum de pirataria, jamais imaginei que a inteligência da Coroa estivesse envolvida nisso! Tudo que tenho é esta pérola, mas sei muito bem quando e onde você pode encontrar mais.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Já ouviu falar de John Thurloe? Ele é o chefe da inteligência da Coroa. Um dia estarei em Londres, relatando pessoalmente a ele o destino do Mercury. Portanto, me diga o nome desse seu desafeto miserável.";
			link.l1 = "Angerran de Chievous, bastardo do Conde de Levy Vantadur. Imagino que ele via o Mercury apenas como um navio de transporte para o saque dos corsários. Talvez soubesse das pérolas, mas não fazia ideia da ligação com a inteligência britânica.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Você não decepciona, Capitão, isso eu admito! Que escolha de diversão e de inimigos! Muito bem. Que outra prova além da pérola você tem?";
			link.l1 = "De Chievous has a frigate. I used to own it... for one night only, yet I managed to learn something. He is an extremely pedantic man; you will learn all about his attack on the Mercury from his log. I am quite sure that he still possesses a portion of the prize too. Maybe even more black pearls if there was more than one.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Mais de uma, pode ter certeza disso. Jamais arriscaríamos a Regina por um punhado de pérolas comuns. Espero que você entenda que eu preciso falar com o Monsieur de Chievous. Não dou a mínima para as pérolas, mas preciso descobrir mais sobre o vazamento. Meus superiores vão acabar comigo se eu não entregar um relatório completo para eles.";
			link.l1 = "Eu ficaria feliz em marcar um encontro para você, mas precisamos nos apressar! Neste exato momento, a fragata de Chievous está a caminho de Guadalupe, onde seu dono atualmente reside sob a proteção do governador local. Tenho certeza de que ele sabe o que fez e vai fugir do Novo Mundo assim que puder.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Essas são acusações muito graves contra pessoas muito poderosas, Capitão. Você tem ideia do tipo de... confusão que pode estourar depois? Um ataque de bandidos a um navio sob a bandeira de um aliado? Isso pode complicar seriamente as relações entre duas grandes nações. Fico imaginando o quanto esse sujeito conseguiu te irritar pra te deixar tão disposto a correr esse risco todo.";
			link.l1 = "Ele tirou algo de mim, milorde. Algo que eu valorizo mais do que a minha própria vida. Preciso corrigir isso. Se isso levar à guerra, então estarei servindo ao meu país sob sua bandeira. Ainda assim, de Chievous vai receber o que merece, e só ele é o culpado!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Já te disseram que você é um homem perigoso, Capitão? Pronto para começar uma guerra pelo mundo só para alcançar seu objetivo? Muito bem, vamos fazer do seu jeito. Vou a Basse-Terre com você. Não posso ignorar uma pista dessas. Vou mandar um escriba anotar suas provas enquanto preparo meu navio.";
			link.l1 = "Obrigado, senhor. Mas não temos tempo para ficar aqui, estou avisando!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Capitão de Maure, vamos chegar a tempo, não tenho dúvidas de você. Mas, se essa aventura não der certo... você me entende? Nem posso te prometer um enterro decente.	";
			link.l1 = "Sim, milorde. Eu entendo perfeitamente.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "O dado está lançado, Capitão. Exigi um encontro com Angerran de Chievous. A fragata dele será revistada assim que chegar. François de Lyon está desconfiado, mas os selos nos meus documentos o impedem de agir por enquanto. Peço que fique na cidade até que a situação se resolva.";
			link.l1 = "Certamente, milorde, eu entendo.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Então espero que você também entenda isso. Entregue sua espada aos cavalheiros ali e siga com eles, assim posso ter certeza de que vai cumprir sua promessa.";
			link.l1 = "Inacreditável... milorde Cortney, está falando sério?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Sério mesmo. Você ainda é um dos meus principais suspeitos, e te deixar ir nessas circunstâncias seria uma tolice da minha parte. Vou te pedir desculpas da forma que achar adequada, se e quando suas palavras se provarem verdadeiras.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Saudações, Monsieur de Maure. Vamos?";
			link.l1 = "Com prazer, quais são as regras? Para ser sincero, eu estava ocupado demais com a comida e provavelmente entendi errado as condições.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "As regras são simples. 10.000 pesos por carta, jogamos até que um de nós desista. Recibos e créditos não são aceitos.";
			link.l1 = "Por mim, tudo certo. Vamos nessa, Coronel.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Maldição! Nunca mais! Muito bem, monsieur de Maure, boa sorte na próxima rodada.";
				link.l1 = "Foi um prazer, coronel. Até logo.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Você lutou bem, mas a Senhora Fortuna tinha outros planos. Adeus, monsieur de Maure. Obrigado pelo jogo.";
					link.l1 = "É, acho que me superestimei nisso. Adeus, Coronel.";
				}
				else
				{
					dialog.text = "Você decidiu abandonar o jogo e assim admitiu a derrota! Lutou com bravura, mas a sorte não esteve ao seu lado. Adeus, monsieur de Maure, e obrigado pela partida.";
					link.l1 = "Sim, acho que me superestimei nisso. Adeus, Coronel.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Capitão Charles de Maure, que surpresa dos diabos!";
					link.l1 = "Capitão. Moreno, uma ova! O que te traz aqui?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Capitão Charles de Maure, é um prazer.";
						link.l1 = "Já nos conhecemos antes, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Capitão Charles de Maure, é um prazer.";
						link.l1 = "Já nos conhecemos antes, monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Capitão Charles de Maure, é um prazer.";
				link.l1 = "Já nos conhecemos antes, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "É uma longa história. O de sempre, capitão. Dá pra ver nos seus olhos que você tem perguntas. Só fique quieto e finja que está tirando sarro de um marinheiro qualquer.";
			link.l1 = "É, esse traje elegante ficou bem em você, meu amigo simples. Eu diria que você sabe como usá-lo.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Só em raras ocasiões, por sorte. Hoje é o dia. Vamos apostar, Capitão. As pessoas estão olhando, não é educado deixá-las esperando.";
			link.l1 = "Certo, conversamos depois. Combinado... Capitão Moreno, por favor.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Eu te conheço um pouco, mas isso não importa. Distribua as cartas, Capitão de Maure, o povo quer ver um espetáculo.";
			link.l1 = "Curioso. Especialmente o seu sotaque espanhol, junto com os elogios da Madame Botot. Muito bem. Mar contra mar, vamos lá!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Eu me lembrei de você, sim. Quando você e meu ex-capitão atravessaram meus rapazes em Le Francois. Aquele desgraçado teve o que merecia, com a sua ajuda, se não me engano. Mas não espere minha gratidão, você matou Franz Garke e isso eu não vou te perdoar.";
			link.l1 = "O intendente português? O Don Sangrento, né? Esta noite só está ficando melhor e melhor. Vamos nessa!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Você decidiu recusar continuar o jogo e assim admitiu a derrota! Imagino que a Senhora Sorte já deu o seu veredito. Até logo, Capitão.";
				link.l1 = "Da mesma forma, Monsieur Moreno. Obrigado pelo jogo.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Acredito que a Senhora Fortuna já deu o seu veredito. Adeus, Capitão, talvez nos encontremos novamente.";
					link.l1 = "Da mesma forma, monsieur Moreno. Obrigado pelo jogo.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Acredito que a Dona Sorte já deu o seu veredito. Adeus, Capitão, talvez nos encontremos de novo em outras circunstâncias, he-he.";
						link.l1 = "Estou ansioso por isso, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "É isso. A sorte foi lançada, Capitão. Adeus.";
						link.l1 = "Adeus, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "É isso. O destino decidiu, Capitão. Adeus.";
				link.l1 = "Adeus, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Que prazer vê-lo, Monsieur Capitão de Maure! Para ser sincero, eu esperava ver qualquer coisa, até uma guarda inteira, mas não você.";
			link.l1 = "Senhor Moreno, está tendo algum problema com as autoridades locais? Aliás, é bom te ver também, ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Olha, não dá pra recusar o convite da nossa anfitriã. Pelo menos, não um convite desses. Vamos, Charles, para com essa palhaçada. A marquesa fez questão de deixar claro que sabe quem eu sou de verdade.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Madame, você é encantadora! Esse seu novo amigo já tentou me entregar uma vez. Na verdade, não deu muito certo, e ele já salvou minha pele tantas vezes que até perdi a conta. De qualquer forma, agora estou devendo uma pra ele, então não precisa ameaçar, pode ficar tranquila.";
			link.l1 = "Obrigado, Bartholomew. Angerran de Chievous me colocou numa situação extremamente complicada e eu preciso derrubá-lo de qualquer jeito. A vida de... alguém que me é muito querido depende disso. Pode acreditar, desta vez nada vai me impedir.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Chega, Capitão, somos amigos, não somos? Lembra daquela corrida por metade do Arquipélago? Aquilo significou muito pra mim. Vou fazer o possível pra te ajudar. Já ouviu falar do Mercury?";
			link.l1 = "Agora, o que é aquilo? Um navio?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Um brigantim britânico, para ser exato. O papel dela era transportar o saque dos corsários do Coronel D'Oyley, que saquearam as operações espanholas de pérolas na Costa do Oeste. Aqueles que às vezes pescam as lendárias pérolas negras, já ouviu falar disso? Se minha fonte for confiável, várias dessas pérolas estavam guardadas no Mercury. Um mês atrás, preparei uma emboscada entre Martinica e Guadalupe, esperando por esses cavalheiros. Mas foi em vão! Passamos uma semana no mar até termos que admitir o fracasso.";
			link.l1 = "Certo, então sua fonte não era confiável afinal e você ficou sem prêmio. O que o de Chievous tem a ver com tudo isso?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Eu pensava o mesmo até descobrir que o Mercury nunca apareceu em Antígua. Imagina minha surpresa quando avistaram o navio perto de Curaçao, e não tinha como ele ter passado por mim perto da Martinica. Os ingleses estão furiosos! Imagina perder um prêmio desses! De qualquer forma, fiquei curioso e comecei a investigar sobre aquele sujeito especial que estragou a diversão de todo mundo. Um butim desses não se vende rápido, então fui até Le François atrás do desgraçado para cobrar o que ele me devia.";
			link.l1 = "Sua história me soa familiar. Já ouviu falar na palavra 'Karma'? Você realmente sabe como se meter em encrenca. Mas ainda não vejo como isso poderia me ser útil?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Não se apresse, Capitão, estou prestes a te contar a melhor parte da minha história. Aquele seu amigo mal lavado, mas bem vestido – os rapazes dele deixaram um rastro visível de pérolas finas nas lojas da cidade. Um tesouro de pérolas espanholas, desperdiçado em grande quantidade.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Ouviu, capitão?";
			link.l1 = "Você acha que o de Chievous comprou pérolas roubadas do Jacques, o Bondoso, e dos rapazes dele? Receio que isso... não seja suficiente.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "É isso mesmo, capitão. Ele não comprou, ele estava vendendo! Conversei com Barbazon sobre isso e ele confirmou que comprou um lote considerável de pérolas perfeitas de um parceiro dele. Depois, mandou tudo pra Europa. Também temos aquela pérola negra no colar e o fato de que o navio do de Chievous passou por reparos. Os trabalhadores me disseram que a fragata dele tinha buracos de balas de doze libras. Quem em sã consciência atacaria uma fragata com canhões desses?";
			link.l1 = "Parece o nosso brigantim! Além disso, lembro do de Chievous se gabando de como a fragata dele é rápida. Mas por que essa loucura? Estamos em paz com a Grã-Bretanha, por que arriscar tanto e por quê? Pérolas negras são extremamente raras, tudo bem, mas não são impossíveis de encontrar.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "E foi aí que ele se deu mal! Os britânicos já abriram uma investigação oficial sobre o desaparecimento do Mercury, embora chamem de navio-correio desaparecido com documentos importantes a bordo. Qualquer pista será generosamente recompensada, qualquer responsável será severamente punido. O melhor de tudo é que enviaram um oficial nobre especial para Antígua, que agora está investigando o caso sem descanso. Não lembro o nome dele—tão pomposo quanto a cara convencida dele—mas ainda bem que não está atrás de mim!";
			link.l1 = "Isso sim é interessante! Parece que eles querem muito essas pérolas negras. Fico pensando quantas tinham no Mercury, e como todo esse conhecimento pode ser útil pra mim?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Por quê, essa escória conseguiu te irritar também, marquesa? Maldito desgraçado! Estou com você nessa também, Capitão de Maure! Ninguém ousa roubar o saque de Bartolomeu, o Português!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Preciso de uma bebida de verdade depois de tanta conversa. Marquesa, já que agora somos amigos...";
			link.l1 = "Acho que não tem rum nenhum nesta casa, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Ah, claro, só falta chamar a atenção daquele investigador britânico para a fragata dele! Se esse é o nosso plano, então eu não reconheço mais o nosso bom e velho Capitão de Maure!";
			link.l1 = "Você vai rir, mas esse é o plano. Vou precisar da ajuda de vocês dois. Madame – você será prisioneira do pirata que contratei – Bartholomew, esse é o seu papel.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "E sobre essa tal vilania minha também! Bartolomeu, o Português, nunca sequestrou uma mulher!";
			link.l1 = "E ele não vai, mas é assim que vai parecer para os homens de de Chievous. Além disso, não precisa dizer seu nome a eles. Leve nossa dama a bordo e encontre a fragata de Angerran perto do Cabo Scott Head. Troque Julianna pelo meu oficial e volte para Martinica. Depois, espere pela marquesa e por mim.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Isso tudo foi muito interessante e tal, você é um verdadeiro cavalheiro, Charles. Mas como diabos a gente vai devolver ela depois da troca?";
			link.l1 = "Eu cuido disso. Não temos muito tempo, então vamos nos separar. Você e a marquesa vão para Dominica enquanto eu corro para St. John's. Vou encontrar o coronel D'Oyley ou aquele investigador britânico e contar a ele quem é o responsável pelo desaparecimento do Mercury.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Já pensou na confusão que vai explodir depois de um incidente desses, Capitão? Neste momento, Antígua é um ninho de vespas e você está me pedindo para jogar uma pedra nele. Eu já vi guerras começarem por muito menos!";
			link.l1 = "Um problema de cada vez... Vou trazê-la de volta, custe o que custar! Que o de Levy Vantadur limpe toda essa bagunça sozinho, se for tão poderoso quanto dizem! E o de Chievous vai ter trabalho pra explicar como a Madame Botot foi parar a bordo do navio dele.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Pronta? Com uma prece! Marquesa, está pronta para ser sequestrada?";
			}
			else
			{
				dialog.text = "Pronta? Por Deus! Marquesa, quanto tempo você vai levar para arrumar suas coisas?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. Meu nome é "+GetFullName(npchar)+", e este é "+GetFullName(characterFromId("GG_SecundantGG_2"))+". Sua Excelência nos pediu para testemunhar seu duelo com o Monsieur de Chievous.";
			link.l1 = "Boa noite, senhores. Espero que tudo corra bem e que ninguém morra esta noite. Mas fiquem preparados para qualquer coisa, por precaução. Este 'cavalheiro' pode acabar sendo uma decepção.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Sua preocupação é infundada. Pelas regras deste duelo, em nenhuma circunstância os segundos podem interferir. Mas agradeço pelo aviso mesmo assim. Seu oponente chegou. Boa sorte, Capitão. Sua Excelência pediu que eu lhe dissesse que rezará pela sua... prudência.";
			link.l1 = "Tenho certeza de que isso vai me ajudar bastante. Enfim, vamos começar.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Capitão, temos um problema. Nosso navio... bem, sumiu.";
			link.l1 = "Como assim, o quê?! Como, quem? Era pra ter uma patrulha inteira de olho nela, então do que diabos você está falando?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Não, capitão, não o navio. Ela está brilhando. A fragata que você ganhou ontem, então agora ela também é nossa, né? Mandamos só uma tripulação de prêmio de uma dúzia pra lá. Ela disse que isso bastava.";
			link.l1 = "Só para com isso e me conta exatamente o que aconteceu desde o começo!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Não faço ideia, capitão. A fragata zarpou na neblina da manhã. A guarda percebeu sua ausência algumas horas depois, quando a neblina já tinha se dissipado.";
			link.l1 = "Não pode ser! Ela nunca faria isso comigo! Embora... droga, nós brigamos há pouco tempo. Será que ela...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Temo que seja ainda pior, capitão. Pescadores encontraram dois dos nossos rapazes da tripulação do prêmio hoje cedo. Ambos mortos, com a garganta cortada.";
			link.l1 = "Maldito pesadelo! De Chievous! Ele roubou o navio enquanto eu estava ocupado com a marquesa! Espero que ela esteja bem... Se ela perder um fio de cabelo, eu...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Will you give the orders to the boys to get ready, Cap? We can set sail in two hours' time, everybody's been on edge all morning, your second-in-command especially; we barely managed to stop him from sailing after them.";
			link.l1 = "Cedo demais para isso. Eu preciso... pensar direito sobre tudo isso, e conversar com alguém. Isso! Preparem o navio! Quero todos prontos, vamos zarpar assim que eu voltar.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Capitão de Maure, o que está acontecendo? Alguém atacou a madame?";
			link.l1 = "Você não devia ter vindo aqui. Bem, Deus é minha testemunha, eu não queria isso.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monsieur, quase perdemos a esperança de vê-lo aqui. Vejo que a marquesa Botot está no seu bote. Nem vou perguntar como isso aconteceu. Sua companheira está esperando por você. Ela está sã e salva, leve-a e caia fora daqui.";
			link.l1 = "Se você encostou um dedo nela, eu vou despedaçar seu velho barco!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Que demonstração inesperada de preocupação. Não se preocupe, ela foi tratada como uma rainha prisioneira. Suas ameaças não me assustam. Aliás, o Chevalier de Chievous manda lembranças.";
			link.l1 = "Dane-se ele e os cumprimentos dele. Onde está o meu... oficial? Vamos começar a troca.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsieur, quase perdemos a esperança de vê-lo aqui. Sua companheira está esperando por você. Ela está sã e salva... espere, quem diabos é esse? Onde está a marquesa?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Sua espada, senhor. E nada de gracinha, meus rapazes andam meio nervosos ultimamente. Você não quer levar um tiro, quer?";
			link.l1 = "Está falando sério? Tudo bem, leve, mas cuidado, isso vale mais do que o seu quartel. Exijo uma audiência com o Barão Cortney, Sua Excelência!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Não se preocupe, tenho certeza de que ele vai arranjar um tempo para te fazer uma visita.";
			link.l1 = "Quando você tenta ajudar alguém...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Também não gosto disso, Monsieur. Infelizmente, esse britânico insolente tem tanta autoridade que nem mesmo Monsieur de Lyon pode fazer muita coisa. Me desculpe, Capitão, por favor entregue sua espada.";
			link.l1 = "Espero mesmo que o Monsieur de Chievous não vá dividir a cela comigo. Vamos, senhores, estou exausto. Finalmente, um pouco de sono.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Não quero ser indelicado, monsieur, mas não tenho tempo para conversar agora, como pode ver o que está acontecendo. Não quero perder nada!";
			link.l1 = "Como desejar, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Esta noite vai entrar para a história, eu sinto! As pessoas vão comentar sobre isso daqui até Versalhes! Minha Marianne vai ficar encantada e vai querer saber todos os detalhes. Por favor, monsieur, afaste-se, você está bloqueando minha visão.";
			link.l1 = "Já estou indo embora, monsieur, aproveite o espetáculo e mande lembranças para a inesquecível Marianne... seja lá quem for.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah! Então, aqui está o Monsieur de Maure! Perdão... Capitão Charles de Maure! Junte-se a mim, por favor, aqui tenho uma seleção magnífica de vinhos do bom Velho Mundo. Como prefere começar a noite: com uma novidade - Cabernet Sauvignon das margens da nossa querida Gironda, ou com o clássico atemporal - Sangiovese italiano?";
			link.l1 = "Obrigado, monsieur, vou beber com você, mas um pouco mais tarde.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, Capitão de Maure! Gostaria de mais um pouco de vinho... hic? Olha só o que acabaram de nos servir – um Syrah do ano de 1643, direto das colinas do norte do Vale do Rhône. Isso aqui, caramba, é uma verdadeira joia! E o ano foi excelente em todos os sentidos, te digo... só a derrota dos espanhóis no Cabo Gat já vale a pena! Aliás... por que está todo mundo tão agitado, você sabe? Alguém está passando mal? Bem – seja como for, saúde...";
			link.l1 = "Bem, pelo menos alguém aprecia os quitutes. Au revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, Capitão Charles de Maure, já ouvi falar de você, assim como todo mundo nesta cidade! Deixe-me me apresentar - "+GetFullName(npchar)+", conhecer você é uma grande honra, acredite! Você realmente tem uma boa relação com o nosso governador? Pode nos apresentar? Eu gostaria de expressar meu mais profundo respeito a ele e...";
			link.l1 = "Talvez mais tarde. Tenha uma boa noite, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, você viu isso?! Nosso estimado governador e o próprio Monsieur de Chievous – achei que iam se matar ali mesmo! Que espetáculo! A marquesa Botot se superou hoje – está tudo tão emocionante! Mal posso esperar pela continuação. Aliás, talvez agora seja o momento certo? Você prometeu me apresentar... ";
			link.l1 = "Eu não me lembro de ter prometido nada. Me desculpe, mas eu preciso ir.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, finalmente você chegou ao salão da brilhante Madame Botot! Ela já comentou algumas vezes que queria te ver. Conseguiu avaliar os 'alunos' dela? Pois é, estrelas como a marquesa não são para simples mortais como nós. Mas acredite: essas damas são verdadeiras obras de arte. Talvez menos impressionantes, mas ainda assim – como Michelangelo e, digamos, Ticiano.";
			link.l1 = "Uma comparação interessante, monsieur. Bem, vou deixá-lo aproveitar a noite....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Não, aqui sempre é animado, mas agora o ar está carregado com o cheiro de um grande escândalo, sente isso? Lady Jacqueline está me esperando lá em cima, mas ainda assim não consigo me afastar das mesas de jogo! Sua Senhoria e Monsieur de Chievous são adversários à altura e estão determinados como nunca. Parece que as apostas desta noite não vão só alcançar as estrelas, mas vão romper o próprio firmamento direto para o inferno!";
			link.l1 = "Os demônios estão lá embaixo, monsieur. Devem haver anjos por trás do firmamento do céu.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Bem, pelo menos um encontro agradável! Já nos conhecemos, Capitão de Maure, embora você provavelmente não se lembre. "+GetFullName(npchar)+" - Eu era o capitão da sexta companhia de infantaria da guarnição, lutei ao seu lado nas nossas ruas contra os espanhóis. Para ser sincero, levei um tiro no joelho e passei a maior parte da batalha assistindo este mesmo bordel pegar fogo, enquanto eu estava caído numa vala. E agora estou aqui – outra guerra civil, e mais uma vez eu admiro tudo isso, mas desta vez por dentro.";
			link.l1 = "Prazer em conhecê-lo, monsieur. Aquele dia estava realmente quente, mas devo admitir que, desde então, este lugar ficou muito mais bonito!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "E o que acha do clima por aqui, capitão? Parece que esses tolos mundanos resolveram transformar tudo numa confusão sangrenta! Fico pensando, será que o cargo de governador pode ser apostado como uma partida de cartas? Pode anotar: isso vai acabar em briga de espada. Uma pena, com meu joelho, esse tipo de diversão já não é pra mim. Mas vi a Jacqueline por aí – o cavalheiro dela está bem envolvido nessa confusão... Acho que vou lá tentar a sorte, enquanto ainda está tudo calmo por aqui.";
			link.l1 = "Boa decisão, desejo-lhe sucesso, monsieur. E preciso voltar para... os meus afazeres.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
